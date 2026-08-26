# OV5640 → STM32H7R7 bring-up guide (MIPI CSI-2)

How to bring an **OmniVision OV5640** (1/4", 5 MP, 2592×1944 CMOS) up on an
**STM32H7R7** over **MIPI CSI-2**, using the STM32Cube HAL, from power rails to
a frame sitting in your buffer.

Everything here traces back to *OV5640 datasheet, product specification version
2.03, may 2011* (`../docs/OV5640_datasheet.pdf`). Section numbers in parentheses
are datasheet sections.

> **NOTE :**  Mainly 


Companion files in this folder:

| File | What it is |
|---|---|
| `README.md` | this guide — the ordered procedure |
| `NOTES.md` | gotchas, pin tables and the worked calculations |
| `ov5640.h` | driver public API + register map |
| `ov5640.c` | driver implementation + register tables |

> **Scope.** This is the MIPI CSI-2 driver. The parallel DVP path is gone — the
> STM32H7R7 has a CSI-2 receiver, so there is no reason to use DVP, and carrying
> both would have doubled the clock arithmetic for no benefit. If you ever need
> the DVP variant back, the sensor-side register work is identical; only the
> clock tree and the host peripheral change.

---

## 0. What moving to CSI-2 buys you

The OV5640 has two output interfaces (§2.1):

- **MIPI CSI-2** — 1 clock lane + 2 data lanes, differential, serial
- **DVP** — 10-bit parallel: `D[9:0]`, `PCLK`, `HREF`, `VSYNC`

The STM32H7R7 has a **CSI-2 host with a D-PHY receiver** feeding **DCMIPP**
(Digital Camera Memory Interface Pixel Processor). That changes three things,
and all three are improvements:

**1. Pin count collapses.** DVP needs 8 data lines plus `PCLK`, `HREF` and
`VSYNC` — 11 fast signals routed as a matched parallel bus. CSI-2 needs 6 pins:
three differential pairs. On the sensor side you go from wiring `D[9:2]` (with
the two-bit offset trap that came with it) to wiring `MDP0/MDN0`, `MDP1/MDN1`
and `MCP/MCN`.

**2. The bandwidth ceiling lifts.** DVP tops out at 96 MHz of byte clock (§8.4),
which is why the datasheet tells you to use MIPI for 5 MP YUV at 15 fps — that
case needs 168 MHz of DVP byte clock and simply cannot be done in parallel. Over
2 CSI-2 lanes at 672 Mbps each, it fits with room to spare. Concretely, the
modes this driver ships:

| Mode | DVP (previous driver) | **CSI-2, 2 lanes** |
|---|---|---|
| VGA 640×480 | 30 fps | **30 fps** |
| 720p 1280×720 | 33 fps | **60 fps** |
| 1080p 1920×1080 | 15.7 fps | **30 fps** |
| 5 MP 2592×1944 | 6.7 fps | **15 fps** |

Those right-hand numbers are exactly the headline rates in the datasheet's
format table (§2.3, table 2-1). On DVP you could not reach them; on CSI-2 you
can.

**3. The reference register tables become usable verbatim.** This one matters
more than it sounds. `HTS` and `VTS` in OmniVision's published mode tables are
counted in **pixel** periods. On an 8-bit DVP one clock carries one *byte*, so a
2-bytes-per-pixel format needs twice the line budget and the published tables do
not fit — the previous driver had to re-derive every `HTS`/`VTS` for the byte
domain. CSI-2 serialises pixels, not bytes, so the pixel-domain tables are
correct as written and this driver uses them unchanged. One entire class of
bring-up bug goes away.

### The registers that select CSI-2

```
0x300E  bit[2]   1 = MIPI enable, 0 = DVP
        bit[3]   MIPI RX PHY power down
        bit[4]   MIPI TX PHY power down  (must be 0 to transmit)
        bit[7:5] lane mode: 000 = one lane, 001 = two lane
0x3034  bit[3:0] MIPI bit mode: 0x8 = 8-bit, 0xA = 10-bit
0x4800  bit[5]   clock lane gate (0 = continuous clock, 1 = gated)
        bit[4]   line sync short packets
        bit[2]   idle state: 0 = LP00, 1 = LP11
```

> **A wrinkle in `0x300E[7:5]`.** The datasheet documents 000 as one lane and
> 001 as two, with everything else "debug mode" — but the register's own reset
> default is `0x58`, whose `[7:5]` field is `010`, one of the supposedly-invalid
> values. Meanwhile the mainline Linux driver streams with `0x45` (`[7:5]` =
> `010`) and stops with `0x40`. The driver here builds the value from the
> documented fields and exposes `OV5640_MIPI_CTRL00_STREAM_ON` /
> `_STREAM_OFF` (`0x45`/`0x40`) as the field-proven fallback. **If your receiver
> never leaves LP-11 or sees no clock, try the fallback pair before you debug
> anything else.**

---

## 1. Power rails and the power-up sequence

The OV5640 wants these supplies (§8.3, table 8-3):

| Rail | Pins | Min | Typ | Max | Feeds |
|---|---|---|---|---|---|
| `AVDD` | A3, B10, C11 | 2.6 V | **2.8 V** | 3.0 V | analog / pixel array |
| `DVDD` | A9, B5, C1, D2, I11, J1, K1 | 1.425 V | **1.5 V** | 1.575 V | digital core |
| `DOVDD` | J2, J3, K2, K3 | 1.71 V | **1.8 V** | 3.0 V | I/O pads |
| `PVDD` | I10 | — | 1.5 V | — | PLL |
| **`EVDD`** | **J7** | — | **1.5 V** | — | **MIPI TX — now load-bearing** |

`EVDD` was decoration in the DVP build; it powers the MIPI transmitter. Tie it
to `DVDD` through its own ferrite and give it a local 0.1 µF. A noisy `EVDD`
shows up as D-PHY errors, not as a dead link, which makes it annoying to find.

`DOVDD` should be **1.8 V** here. It is the recommended level (§2.7), it lets
you use the internal `DVDD` regulator without the 2.8 V heat problem, and none
of the remaining digital signals — SCCB, `RESETB`, `PWDN`, `XVCLK` — need more.

### Ordering (§2.7.1, figure 2-3)

```
DOVDD ──┐
        └─ t0 ≥ 0 ms ─→ AVDD
                         └─ t2 ≥ 5 ms ─→ PWDN may go LOW
                                          └─ t3 ≥ 1 ms ─→ RESETB goes HIGH
                                                           └─ t4 ≥ 20 ms ─→ first SCCB access

XVCLK must be running ≥ 1 ms before you touch a register.
```

Power *down* is the mirror image: `RESETB` low, then `AVDD` off (t6 ≥ 0), then
`DOVDD` off (t5 ≥ 0).

**The reset pulse must be ≥ 1 ms** (§2.8), and a hard reset on power-up is
*required* even though there is an on-chip reset.

Pin defaults if you do not drive them:

- `PWDN` — active **high**, internal **pull-down**. Tie to DGND if unused.
- `RESETB` — active **low**, internal **pull-up**.

Both are asynchronous: they work with no clock present.

---

## 2. XVCLK

The sensor has no oscillator. You supply `XVCLK` on pin H11.

- Range: **6–27 MHz** (§8.4, table 8-5)
- Jitter tolerance: ≤ 1 ns
- **24 MHz** is the reference value and what every number below assumes

On the STM32H7R7 use an **MCO** output driven from RCC. Do not use a timer PWM:
the sensor PLL feeds the D-PHY serialiser, and clock jitter that a parallel bus
would have shrugged off turns into D-PHY timing errors here.

Scope it before you write a register. A wrong `XVCLK` scales the entire clock
tree in section 3 silently, and on CSI-2 the failure mode is a receiver that
reports ECC errors rather than an image that is merely the wrong speed.

---

## 3. The clock tree — the calculation that matters most

Two clocks come out of one PLL, and CSI-2 makes you care about both.

### The chain (§2.5, §7.1, §7.2)

```
XVCLK (24 MHz)
   │
   ├─ ÷ pre_div      0x3037[3:0]   {1, 2, 3, 4, 6, 8}
   ├─ × mult         0x3036[7:0]   4..127 any, 128..252 even only
   │                                ── VCO. HARD LIMIT 800 MHz ──
   ├─ ÷ sys_div      0x3035[7:4]   1..15 (0 means 16)
   ├─ ÷ root_div     0x3037[4]     0 -> ÷1, 1 -> ÷2
   │
   ├───────────────┬──────────────────────────────────┐
   │               │                                  │
   ÷ bit_div       ÷ mipi_div  0x3035[3:0]            │
   0x3034[3:0]     │                                  │
   ÷ sclk_root_div │                                  │
   0x3108[1:0]     │                                  │
   │               │                                  │
   ▼               ▼                                  │
  PCLK           SERCLK ── x2 (DDR) ──> LANE RATE ────┘
  (pixel clock,   (serial clock)         (bits/s per lane)
   HTS/VTS live
   in this domain)
```

As formulas:

```
VCO       = XVCLK × mult ÷ pre_div                                 ≤ 800 MHz
PCLK      = VCO ÷ sys_div ÷ root_div ÷ bit_div ÷ sclk_root_div
SERCLK    = VCO ÷ sys_div ÷ root_div ÷ mipi_div
lane_rate = 2 × SERCLK                                (DDR: 2 bits per clock)

fps       = PCLK ÷ (HTS × VTS)
```

`bit_div` is 2 in 8-bit MIPI mode (`0x3034 = 0x18`) and 2.5 in 10-bit mode
(`0x3034 = 0x1A`). Use 8-bit for YUV422 and RGB565; 10-bit only for RAW10.

### The bandwidth constraint

This is the one new thing CSI-2 asks of you. The transmitter serialises pixels
as they leave the pipeline, at the pixel clock, so the peak per-lane rate you
need is:

```
required_lane_rate = PCLK × bits_per_pixel ÷ num_lanes
```

Note what is **not** in that expression: `VTS`, and therefore frame rate.
Stretching `VTS` adds blank lines and lowers fps, but it does not slow down the
pixels inside an active line, so it does **not** reduce the peak lane rate.
If you are over budget, you must lower `PCLK`, not the frame rate.

The driver picks `mipi_div` to satisfy this and then re-checks:

```
mipi_div  = floor( (2 × VCO ÷ sys_div ÷ root_div) ÷ required_lane_rate )
```

and returns an error if the result still cannot carry the mode. That check is
worth having: it turns "the image is torn and I don't know why" into a return
code at init.

### Worked example — 1080p30, YUV422, 2 lanes

| Field | Register | Value |
|---|---|---|
| `pre_div` = 3, `root_div` = 2 | `0x3037` | `0x13` |
| `mult` = 84 | `0x3036` | `0x54` |
| `sys_div` = 1, `mipi_div` = 1 | `0x3035` | `0x11` |
| `bit_div` = 2 (8-bit MIPI) | `0x3034` | `0x18` |
| `sclk_root_div` = 2 | `0x3108` | `0x01` |
| 2 lanes, MIPI enabled | `0x300E` | see §0 |

```
VCO       = 24 MHz × 84 ÷ 3        = 672 MHz          ✓ under 800
PCLK      = 672 ÷ 1 ÷ 2 ÷ 2 ÷ 2    =  84 MHz
SERCLK    = 672 ÷ 1 ÷ 2 ÷ 1        = 336 MHz
lane_rate = 2 × 336                = 672 Mbps/lane

required  = 84 MHz × 16 bpp ÷ 2 lanes = 672 Mbps/lane ✓ exactly met

fps       = 84 000 000 ÷ (2500 × 1120) = 84e6 ÷ 2 800 000 = 30.0 fps   ✓
```

Every mode in `ov5640.c` closes like this — required and available lane rate
match to the megabit. Two PLL settings cover all nine: `mult = 56` (VCO 448 MHz,
PCLK 56 MHz, 448 Mbps/lane) for everything up to SXGA, and `mult = 84` (VCO
672 MHz, PCLK 84 MHz, 672 Mbps/lane) for 720p, 1080p and 5 MP.

### One lane instead of two

Halving the lanes halves your bandwidth, and because the ratio

```
available_max ÷ required = 2 × bit_div × sclk_root_div × num_lanes ÷ bpp
```

does not contain `VCO`, you **cannot** fix a 1-lane shortfall by retuning the
PLL multiplier — every setting fails by the same factor. The knob that does work
is `sclk_root_div`: taking it from ÷2 to ÷4 (`0x3108[1:0]` = `10`) halves `PCLK`
and brings the requirement back in range, at half the frame rate.

The driver does this automatically when you configure one lane. VGA drops from
30 to 15 fps, 1080p from 30 to 15, 5 MP from 15 to 7.5. Use two lanes unless
your board genuinely cannot route the second pair.

### Changing frame rate

Increase `VTS` (`0x380E/0x380F`):

```
VTS_new = PCLK ÷ (HTS × fps_target)
```

This adds blank lines. It lowers frame rate and buys headroom for longer
exposures, and — per the note above — it does not change the lane rate you need.

---

## 4. Windowing, subsampling and scaling (§4.2)

Three sizes, in order:

```
┌─ physical pixel size ── 2624 × 1964 (§3.1; 2592×1944 of it active) ──────┐
│  ┌─ ISP input size ── X_ADDR_ST..X_ADDR_END, Y_ADDR_ST..Y_ADDR_END ───┐  │
│  │  ┌─ pre-scaling size = ISP input − 2 × offset ──────────────────┐  │  │
│  │  │  ┌─ data output size ── X/Y_OUTPUT_SIZE (after the scaler) ┐ │  │  │
│  │  │  └─────────────────────────────────────────────────────────┘ │  │  │
│  │  └──────────────────────────────────────────────────────────────┘  │  │
│  └─────────────────────────────────────────────────────────────────────┘  │
└───────────────────────────────────────────────────────────────────────────┘
```

| Quantity | Registers |
|---|---|
| `X_ADDR_ST` / `Y_ADDR_ST` | `0x3800/0x3801`, `0x3802/0x3803` |
| `X_ADDR_END` / `Y_ADDR_END` | `0x3804/0x3805`, `0x3806/0x3807` |
| `X_OUTPUT_SIZE` / `Y_OUTPUT_SIZE` | `0x3808/0x3809`, `0x380A/0x380B` |
| `HTS` / `VTS` | `0x380C/0x380D`, `0x380E/0x380F` |
| `X_OFFSET` / `Y_OFFSET` | `0x3810/0x3811`, `0x3812/0x3813` |
| `X_INC` / `Y_INC` (subsample) | `0x3814`, `0x3815` |
| flip / mirror / binning | `0x3820`, `0x3821` |
| scaler enable | `0x5001[5]` |

`X_INC`/`Y_INC` are `{odd_inc[7:4], even_inc[3:0]}`. `0x11` reads every row and
column. `0x31` is odd increment 3, even increment 1 → average step 2 → **2×
subsample**.

The subsampled family reads the full array at 2× subsample — 2624×1944 becomes
1312×972 — and after the 16/6 offsets the pre-scaling size is exactly
**1280×960**. Every output up to that size is the ISP scaler working on the same
frame, so the field of view never changes between QQVGA and SXGA.

Three ways to get a smaller image:

| Method | Registers | Cost | Used for |
|---|---|---|---|
| **Crop** | `X/Y_ADDR_ST/END` | narrows field of view | 1080p, 720p |
| **Subsample / bin** | `X_INC`, `Y_INC`, `0x3821[0]` | aliasing; keeps FOV | VGA … SXGA |
| **Scale** | `X/Y_OUTPUT_SIZE` + `0x5001[5]` | ISP time; keeps FOV | QQVGA … XGA |

---

## 5. Exposure and gain (§4.6)

Unchanged from the parallel case — this is all sensor-internal.

### Manual exposure

```
0x3503[0] = 1                    enable manual AEC
exposure  = {0x3500[3:0], 0x3501[7:0], 0x3502[7:0]}    20 bits
```

Units are **1/16 of a line**, and `0x3502[3:0]` — the fractional nibble —
**must be zero**: the OV5640 does not support fractional-line exposure (§7.5).

```
exposure_register = exposure_lines × 16
t_row             = HTS ÷ PCLK
exposure_time     = exposure_lines × HTS ÷ PCLK
```

VGA example, 56 MHz PCLK, HTS = 1896:

```
t_row = 1896 ÷ 56e6 = 33.86 µs
1/60 s exposure -> 16 667 µs ÷ 33.86 µs = 492 lines -> register = 492 × 16 = 7872 = 0x1EC0
```

**Ceiling:** exposure must stay below `{0x380E,0x380F} + {0x350C,0x350D}` — that
is `VTS + extra_VTS`, in lines (§4.6.2). Keep 4 lines of margin. To expose longer
than one frame period, raise `VTS` **first**, then write the exposure.

### Manual gain

```
0x3503[1] = 1                    enable manual AGC
gain      = {0x350A[1:0], 0x350B[7:0]}    10 bits, unit 1/16
```

`gain_x = value ÷ 16`, maximum **64×** (§4.6.4). Prefer exposure over gain: gain
amplifies noise, exposure does not.

### Banding filter (flicker) (§4.6.1.1)

```
band_step(50 Hz) = (1/100 s) ÷ t_row    -> {0x3A08[1:0], 0x3A09}
band_step(60 Hz) = (1/120 s) ÷ t_row    -> {0x3A0A[1:0], 0x3A0B}
max_bands        = (VTS − 4) ÷ band_step -> 0x3A0E (50 Hz), 0x3A0D (60 Hz)
```

VGA example, `t_row = 33.86 µs`:

```
50 Hz: 10 000 µs ÷ 33.86 = 295 = 0x127  -> 0x3A08 = 0x01, 0x3A09 = 0x27
60 Hz:  8 333 µs ÷ 33.86 = 246 = 0x0F6  -> 0x3A0A = 0x00, 0x3A0B = 0xF6
max bands, both: (984 − 4) ÷ step = 3   -> 0x3A0E = 0x3A0D = 0x03
```

`OV5640_SetBandingFilter()` computes this at runtime from the live `HTS`/`VTS`,
so it stays correct across mode changes.

---

## 6. Output format and CSI-2 data types (§6.5)

Two things must agree now instead of one: the sensor's formatter, and the data
type the CSI-2 receiver is told to expect.

| Format | `0x4300` | `0x501F` | `0x3034` | CSI-2 data type | bpp |
|---|---|---|---|---|---|
| RGB565 `{b,g}{g,r}` | `0x6F` | `0x01` | `0x18` | `0x22` RGB565 | 16 |
| RGB565 `{r,g}{g,b}` | `0x61` | `0x01` | `0x18` | `0x22` RGB565 | 16 |
| YUV422 YUYV | `0x30` | `0x00` | `0x18` | `0x1E` YUV422-8 | 16 |
| YUV422 UYVY | `0x32` | `0x00` | `0x18` | `0x1E` YUV422-8 | 16 |
| RAW8 Bayer BGGR | `0x00` | `0x03` | `0x18` | `0x2A` RAW8 | 8 |
| RAW10 Bayer BGGR | `0x00` | `0x03` | `0x1A` | `0x2B` RAW10 | 10 |

`0x501F` is the ISP format MUX and it has to agree with `0x4300`. Set one and not
the other and you get well-formed nonsense: correct packet sizes, correct frame
timing, wrong pixels.

Three places a format now has to match, and all three must agree:

1. **`0x4300` / `0x501F`** — what the sensor formats
2. **`0x3034[3:0]`** — 8-bit vs 10-bit serialisation, which also sets `bit_div`
3. **The receiver's expected data type** — what DCMIPP is told to accept

Number 3 is the new failure mode. If the sensor sends `0x1E` and the receiver
filters for `0x22`, you get **no frames at all** and no error — the packets are
simply discarded. Check the data type first when a format change produces
silence rather than corruption.

**RAW10 costs you frame rate.** It forces `0x3034 = 0x1A`, which moves `bit_div`
from 2 to 2.5 and so drops `PCLK` by 20% for the same PLL. Every mode slows
accordingly: VGA 30 → 24 fps, 1080p 30 → 24 fps, 5 MP 15 → 12 fps. The driver
recomputes rather than assuming, so the numbers stay right — but if you
hand-tune registers, remember this one moves.

**RAW8 is close to free bandwidth.** At 8 bpp instead of 16 it halves the lane
rate — 448 → 224 Mbps for the small modes, 672 → 336 Mbps for the large ones —
at full frame rate, because `bit_div` stays at 2. If you are going to demosaic
on the STM32 anyway (DCMIPP Pipe 1 does it in hardware), this is the format to
send.

**JPEG** is not supported by this driver over CSI-2. It needs a user-defined
data type (`0x30`) and variable-length line handling, and the receiver-side work
is substantial. Capture RAW or YUV and compress on the host.

---

## 7. SCCB — the control bus (§2.6)

Unchanged from the parallel build.

| Property | Value |
|---|---|
| Slave ID (`0x3100` default) | `0x78` write / `0x79` read |
| 7-bit address | `0x3C` |
| HAL address argument | **`0x78`** — HAL takes the 8-bit shifted form |
| Register address width | **16 bits, big-endian** |
| Data width | 8 bits |
| Max clock | 400 kHz (§8.4, table 8-6) |
| Pins | `SIOC` (G10, input), `SIOD` (G11, I/O) |

Pull-ups to `DOVDD`: 4.7 kΩ at 100 kHz, 2.2 kΩ at 400 kHz. **Not** to 3.3 V when
`DOVDD` is 1.8 V.

**First thing to read, always:**

```
0x300A = 0x56    chip ID high
0x300B = 0x40    chip ID low       -> 0x5640
```

If that fails, stop. It is almost always: wrong address, missing pull-ups,
`RESETB` still low, `PWDN` still high, `XVCLK` not running, or you jumped the
20 ms `t4` delay.

### Group write (§2.6)

`0x3212` buffers writes and latches them at one frame boundary — the way to
change exposure and gain together without a torn frame:

```
0x3212 = 0x03    start group 3
...writes...
0x3212 = 0x13    end group 3
0x3212 = 0xA3    launch group 3
```

---

## 8. D-PHY timing registers (§7.19)

This block has no DVP equivalent and it is where CSI-2 bring-ups get stuck.

The OV5640 does not infer its D-PHY timing. You tell it the line rate and it
computes the transitions from a table of minimums held in `0x4818`–`0x4832`,
each expressed as a **nanosecond floor plus a unit-interval floor**:

```
parameter_real = parameter_min_ns + T_UI × parameter_min_UI
```

| Parameter | ns registers | UI register | Default |
|---|---|---|---|
| `hs_zero` | `0x4818/0x4819` | `0x482A` | 150 ns + 5 UI |
| `hs_trail` | `0x481A/0x481B` | `0x482B` | 60 ns + 4 UI |
| `clk_zero` | `0x481C/0x481D` | `0x482C` | 390 ns + 0 UI |
| `clk_prepare` | `0x481E/0x481F` | `0x482D` | 60 ns + 0 UI |
| `clk_post` | `0x4820/0x4821` | `0x482E` | 86 ns + 52 UI |
| `clk_trail` | `0x4822/0x4823` | `0x482F` | 60 ns + 0 UI |
| `lpx_p` | `0x4824/0x4825` | `0x4830` | 50 ns + 0 UI |
| `hs_prepare` | `0x4826/0x4827` | `0x4831` | 50 ns + 4 UI |
| `hs_exit` | `0x4828/0x4829` | `0x4832` | 100 ns + 0 UI |

**The defaults are the MIPI D-PHY specification minimums and you should leave
them alone.** They are correct for any line rate the OV5640 can produce.

What you **must** set is `0x4837`, and this is the single most commonly missed
register in an OV5640 CSI-2 bring-up:

```
0x4837  PCLK PERIOD - "period of pixel clock, pclk_div=1, and 1-bit decimal"
```

"1-bit decimal" means the LSB is 0.5 ns, so the value is the period in half-
nanoseconds:

```
0x4837 = round(2000 ÷ f_MHz)
```

That is the clock the sensor uses to convert every ns figure above into internal
cycles. Get it wrong and the ns floors are met at the wrong scale — the link
still runs, packets still arrive, but the receiver logs SoT errors or ECC errors
and frames come and go. The reset default `0x10` = 16 → 8 ns → 125 MHz, which
matches almost nothing you will actually configure.

For this driver's two clock settings:

```
SERCLK 336 MHz (672 Mbps/lane) -> 2000 ÷ 336 = 5.95 -> 0x06
SERCLK 224 MHz (448 Mbps/lane) -> 2000 ÷ 224 = 8.93 -> 0x09
```

`OV5640_ApplyDphyTiming()` computes and writes this from the lane rate it just
configured, so it cannot drift out of sync with the PLL.

---

## 9. STM32H7R7 side — CSI-2 host and DCMIPP

> **Read this before you copy the code.** The sensor-side material above is
> derived from the OV5640 datasheet and I have checked the arithmetic. The
> STM32-side HAL symbol names below are from STM32CubeH7RS and I could **not**
> verify their exact spelling against an installed Cube package while writing
> this. Treat section 9 and the `OV5640_Capture*` wrappers in `ov5640.c` as a
> porting layer: check every identifier against your `stm32h7rsxx_hal_dcmipp.h`
> and RM0477. The structure is right; a name may need adjusting. Everything
> above section 9 is version-independent.

### The pipeline

```
OV5640 ──3 differential pairs──> D-PHY ──> CSI-2 host ──> DCMIPP ──> memory
                                            │                │
                                    VC + data type      pipe + pixel
                                       filtering         processing
```

Three things get configured, in this order:

**1. The D-PHY.** Number of lanes and the line rate you computed in section 3.
The receiver's PHY has to be told the rate — it does not measure it.

```c
DCMIPP_CSI_ConfTypeDef csi = {0};
csi.NumberOfLanes = DCMIPP_CSI_TWO_DATA_LANES;
csi.DataLaneMapping = DCMIPP_CSI_PHYSICAL_DATA_LANES;
csi.PHYBitrate = DCMIPP_CSI_PHY_BT_672;   /* must match the sensor: 672 Mbps */
HAL_DCMIPP_CSI_SetConfig(&hdcmipp, &csi);
```

**2. Virtual channel and data type filtering.** The OV5640 transmits on
**virtual channel 0**. The data type must match section 6's table.

```c
DCMIPP_CSI_VCConfTypeDef vc = {0};
vc.DataTypeFormat = DCMIPP_CSI_DT_RGB565;   /* 0x22 - must match 0x4300 */
HAL_DCMIPP_CSI_SetVCConfig(&hdcmipp, DCMIPP_VIRTUAL_CHANNEL0, &vc);
```

**3. The DCMIPP pipe.** DCMIPP has several pipes with different capabilities:

| Pipe | What it does | Use when |
|---|---|---|
| **Pipe 0** — dump | writes the received bytes straight to memory | you want exactly what the sensor sent |
| **Pipe 1** — main | ISP: demosaic, colour conversion, downsize, crop, gamma, statistics | you want RAW in and RGB out, or hardware resize |

**Start with Pipe 0.** It is the simplest path, it works with YUV422 and RGB565
as-is, and it removes a whole layer from your first bring-up. Move to Pipe 1
once frames are arriving, if you want the on-chip ISP to debayer RAW for you —
which is genuinely useful, because it lets the OV5640 send RAW8 at half the lane
rate and does the demosaic on the STM32 for free.

```c
DCMIPP_PipeConfTypeDef pipe = {0};
pipe.FrameRate = DCMIPP_FRAME_RATE_ALL;
HAL_DCMIPP_PIPE_SetConfig(&hdcmipp, DCMIPP_PIPE0, &pipe);
HAL_DCMIPP_PIPE_Start(&hdcmipp, DCMIPP_PIPE0, (uint32_t)buffer,
                      DCMIPP_MODE_CONTINUOUS);
```

### What got easier

**No GPIO configuration for the data path.** The D-PHY pins are dedicated analog
pins, not GPIO alternate functions. There is no `GPIO_SPEED_FREQ_VERY_HIGH` to
forget, no AF number to look up, and no drive-strength trap. You still configure
GPIO for `RESETB`, `PWDN`, the I2C pins and the MCO output.

**No 65535-word DMA limit.** DCMIPP writes to memory through its own master
port with a full 32-bit address and byte count. The `NDTR` arithmetic and the
double-buffer gymnastics that VGA-and-above needed on DCMI + DMA are gone. A
5 MP frame is one destination address.

### What did not get easier

**The D-cache still bites.** DCMIPP writes go around the Cortex-M7 data cache
exactly as DMA did:

```c
/* Invalidate before the CPU reads. 32-byte aligned address, size rounded up
   to a multiple of 32. */
SCB_InvalidateDCache_by_Addr((uint32_t *)buffer, (int32_t)size);
```

Or mark the frame buffer non-cacheable in the MPU, which is simpler and always
correct at some read throughput.

**Memory sizing still matters.** A 5 MP RGB565 frame is 10 MB and belongs in
external memory. Check what your board populates — the H7R/S parts lean on
external memory through XSPI, and the numbers in NOTES.md §3.6 tell you which
modes fit where.

---

## 10. The bring-up order that actually works

Each step is independently verifiable. Skipping ahead is how you end up with
three overlapping bugs.

1. **Rails.** Scope `AVDD`, `DVDD`, `DOVDD`, `EVDD`. Confirm the §1 ordering.
2. **XVCLK.** Confirm 24 MHz, clean edges.
3. **Reset.** `PWDN` low, `RESETB` low ≥ 1 ms, `RESETB` high, wait 20 ms.
4. **Chip ID.** `0x300A`/`0x300B` → `0x5640`. **Do not proceed until this works.**
5. **Software reset.** `0x3103 = 0x11`, `0x3008 = 0x82`, wait 5 ms.
6. **Common init table.** `ov5640_init_common[]`.
7. **Clocks.** Apply the PLL. Verify the driver's computed lane rate matches what
   you configured in the D-PHY — a mismatch here is the most common cause of a
   link that never trains.
8. **D-PHY timing.** `0x4837` from the lane rate. See §8.
9. **LP-11.** With the sensor configured but not streaming, the data lanes should
   sit in **LP-11**. Scope them. This is the CSI-2 equivalent of checking that
   `VSYNC` toggles, and it is the cheapest possible check that the PHY is alive.
10. **Test pattern.** `0x503D = 0x80` (colour bar). Proves sensor → D-PHY →
    receiver → DCMIPP → memory with the pixel array out of the picture.
11. **Real frames.** `0x503D = 0x00`.
12. **Format and window.** `0x4300`/`0x501F`, then the mode table, then confirm
    the receiver's data type still matches.
13. **AEC/AGC/AWB.** Let the automatics settle, then tune.

### Symptom → cause

| Symptom | Look at |
|---|---|
| Chip ID read fails | address `0x78`, pull-ups, `RESETB`, `PWDN`, `XVCLK`, `t4` ≥ 20 ms |
| Lanes never leave LP-11 | `0x300E` (MIPI not enabled, or TX PHY powered down); try the `0x45`/`0x40` fallback from §0 |
| Lanes stuck in LP-00 | `0x4800[2]` idle state; `0x4805` lane disable bits |
| SoT / ECC errors at the receiver | **`0x4837`** first (§8), then the D-PHY rate mismatch between sensor and receiver, then `EVDD` decoupling |
| CRC errors, frames mostly OK | lane rate marginal; signal integrity on the pairs |
| No frames, no errors | data type mismatch — sensor sending `0x1E`, receiver filtering `0x22` (§6) |
| Frames arrive, image torn | required lane rate exceeds configured (§3); driver returns an error for this at init |
| Frame half garbage | D-cache not invalidated |
| Colours wrong / swapped | `0x4300` sequence nibble, or `0x501F` disagrees with `0x4300` |
| Dark, banded image | banding filter wrong for your mains frequency (§5) |
| Image too dark overall | AEC at its `VTS` ceiling — raise `VTS` before exposure |

---

## 11. What is deliberately not in the driver

- **Autofocus.** The OV5640's AF runs on an embedded 8051 needing an
  OmniVision-supplied firmware blob at `0x8000`, then commands via
  `0x3022..0x3029`. Not in the datasheet. The driver exposes the VCM registers
  (`0x3600..0x3606`, §3.3) for manual focus.
- **JPEG over CSI-2.** See §6.
- **DVP.** Removed. The H7R7 has CSI-2; use it.
- **Lens shading and colour tuning.** `ov5640_init_common[]` carries
  OmniVision's *reference* LENC, AWB, CMX, gamma and SDE values, tuned for a
  reference lens. A working starting point, not tuning for your module.

---

## References

- `../docs/OV5640_datasheet.pdf` — product specification v2.03, may 2011
- RM0477 — STM32H7Rx/Sx reference manual, DCMIPP and CSI-2 chapters
- STM32H7R7 datasheet — D-PHY electrical characteristics and the maximum
  supported line rate for your exact part
- MIPI Alliance D-PHY specification — for the `0x4818`–`0x4832` parameter
  meanings, if you ever need to move off the defaults
