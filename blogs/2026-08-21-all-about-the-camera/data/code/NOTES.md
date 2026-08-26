# OV5640 + STM32H7R7 (MIPI CSI-2) — notes, pin tables, calculations

Working notes to sit beside `README.md`. This is the reference half: the pin
tables you keep looking up, the numbers you keep re-deriving, and the things
that cost a day the first time.

Source: `../docs/OV5640_datasheet.pdf`, product specification v2.03, may 2011.

---

## 1. Key specifications worth memorising

| Parameter | Value | Where |
|---|---|---|
| Active array | 2592 × 1944 (5 038 848 px) | §3.1 |
| Physical array | 2624 × 1964 (5 153 536 px) | §3.1 |
| Pixel size | 1.4 µm × 1.4 µm | features |
| Optical format | 1/4" | features |
| Image area | 3673.6 µm × 2738.4 µm | features |
| CFA | Bayer **BG/GR** line-alternating | §3.1 |
| ADC | 10-bit, on-chip | §2.2 |
| Chief ray angle | 24° | §10.2 |
| Shutter | rolling shutter / frame exposure (FREX) | features |
| Max exposure | 1964 × t_ROW | features |
| Sensitivity | 600 mV/lux-sec | features |
| Max S/N | 36 dB | features |
| Dynamic range | 68 dB @ 8× gain | features |
| Dark current | 8 mV/s @ 60 °C junction | features |
| Operating temp | −30 °C to 70 °C junction | §8.2 |
| **Stable image temp** | **0 °C to 50 °C junction** | §8.2 |
| Active current | 140 mA typical | features |
| Standby current | 20 µA | features |
| **MIPI interface** | **1 clock lane + 2 data lanes, HS and LP** | §6.7 |
| Package | 71-pin CSP3, 5985 × 5835 µm, 0.5 mm pitch | §9.1 |

Note the gap between *operating* and *stable image* temperature. The part keeps
running from −30 °C, but OmniVision only guarantees image quality from 0 °C to
50 °C junction.

### Frame rate ceilings (§2.3, table 2-1) — and what CSI-2 actually delivers

| Format | Resolution | Datasheet fps | This driver, 2 lanes | Lane rate |
|---|---|---|---|---|
| 5 MP | 2592×1944 | 15 | **15** | 672 Mbps |
| 1080p | 1920×1080 | 30 | **30** | 672 Mbps |
| 1280×960 | 1280×960 | 45 | 30 | 448 Mbps |
| 720p | 1280×720 | 60 | **60** | 672 Mbps |
| VGA | 640×480 | 90 | 30 | 448 Mbps |
| QVGA | 320×240 | 120 | 30 | 448 Mbps |

The headline modes — 5 MP 15, 1080p 30, 720p 60 — are all reachable, which they
were not over DVP. The small modes are set to 30 fps because that is what a
sensible application wants; raise them by changing the mode's `VTS` if you
genuinely need 90 fps VGA, and re-check the lane budget in §3.3.

---

## 2. Pin configuration

### 2.1 OV5640 pins you wire for CSI-2 (§1, table 1-1)

Signal pins only; power and ground balls are in README §1.

| Pin | Signal | Type | Goes to | Note |
|---|---|---|---|---|
| H11 | `XVCLK` | input | STM32 MCO | 6–27 MHz, use 24 MHz |
| E2 | `RESETB` | input | STM32 GPIO out | active **low**, internal pull-up, ≥ 1 ms pulse |
| D1 | `PWDN` | input | STM32 GPIO out | active **high**, internal pull-**down** |
| G10 | `SIOC` | input | STM32 `I2C_SCL` | SCCB clock, ≤ 400 kHz |
| G11 | `SIOD` | I/O | STM32 `I2C_SDA` | SCCB data |
| **I9** | **`D7/MCP`** | I/O | **`CSI_CKP`** | MIPI clock lane + |
| **I8** | **`D6/MCN`** | I/O | **`CSI_CKN`** | MIPI clock lane − |
| **K7** | **`D5/MDP0`** | I/O | **`CSI_DP0`** | MIPI data lane 0 + |
| **K6** | **`D4/MDN0`** | I/O | **`CSI_DN0`** | MIPI data lane 0 − |
| **J10** | **`D9/MDP1`** | I/O | **`CSI_DP1`** | MIPI data lane 1 + |
| **J9** | **`D8/MDN1`** | I/O | **`CSI_DN1`** | MIPI data lane 1 − |
| J7 | `EVDD` | power | 1.5 V | **MIPI TX supply — decouple properly** |
| K8, K11 | `EGND` | ground | MIPI TX ground | |
| E1 | `STROBE` | I/O | LED/flash driver, or NC | §4.10 |
| F2 | `FREX` | I/O | GPIO, or NC | frame exposure §4.10.2 |
| F1, G1 | `GPIO0`, `GPIO1` | I/O | NC | |
| H1, H2, I1 | `VSYNC`, `HREF`, `PCLK` | output | **NC** | DVP only, unused |
| J5, H10, K4, K5 | `D2`, `D3`, `D1`, `D0` | I/O | **NC** | DVP only, unused |
| A2, B2 | `VCMSINK` | analog | VCM coil | autofocus actuator §3.3 |
| B3, B4 | `VCMGND` | analog | VCM ground | |
| B11 | `VN` | reference | 0.1 µF to AGND | internal analog reference |
| C10 | `VH` | reference | 0.1 µF to AGND | internal analog reference |

**Six pins carry the entire image.** That is the headline change from the
parallel build, which needed eleven fast single-ended signals. Note that the
MIPI pins are the *shared* ones — `MCP/MCN` are also `D7/D6`, `MDP0/MDN0` are
`D5/D4`, `MDP1/MDN1` are `D9/D8`. `0x300E[2]` decides which personality they
take, and the four DVP-only data pins (`D0`–`D3`) plus `PCLK`/`HREF`/`VSYNC`
simply go unconnected.

### 2.2 Differential pair routing

This is the part that has real rules, unlike the parallel bus which mostly
tolerated sloppiness.

- **100 Ω differential impedance** on every pair. Not 50 Ω single-ended each —
  the coupled pair impedance is what matters.
- **Intra-pair skew** as close to zero as you can manage. Target under 0.15 mm
  of length mismatch within a pair. At 672 Mbps the unit interval is 1.49 ns and
  a few millimetres of skew eats a meaningful fraction of the eye.
- **Inter-pair skew** is far less critical — CSI-2 deskews per lane at the start
  of each high-speed burst — but keep the clock pair within a few millimetres of
  the data pairs anyway.
- **Reference to a solid ground plane** for the whole run. No splits, no routing
  over a plane gap.
- **No stubs, no test points** on the pairs. If you must probe, use a proper
  differential probe on short exposed traces.
- **Keep the pairs away from `XVCLK` and the SCCB lines.** The clock in
  particular will couple.
- **No series termination.** D-PHY terminates at the receiver; adding series
  resistors the way you would on a parallel bus breaks it.

Length matching *between* the clock pair and data pairs is not required to the
same tolerance, which is a genuine relief compared with matching an 8-bit
parallel bus.

### 2.3 STM32H7R7 CSI-2 pins

**The D-PHY pins are dedicated.** They are not GPIO alternate functions, so
there is no AF number to configure, no `GPIO_SPEED_FREQ_VERY_HIGH` to forget,
and no port conflict to resolve. Check the pinout in your STM32H7R7 datasheet
for the exact ball names — they follow the pattern:

| STM32 pin | Connects to OV5640 |
|---|---|
| `CSI_CKP` / `CSI_CKN` | `MCP` (I9) / `MCN` (I8) |
| `CSI_DP0` / `CSI_DN0` | `MDP0` (K7) / `MDN0` (K6) |
| `CSI_DP1` / `CSI_DN1` | `MDP1` (J10) / `MDN1` (J9) |

The D-PHY also needs its own supply and decoupling on the STM32 side — check the
power-supply scheme section of the datasheet, it is a separate rail from `VDD`.

### 2.4 STM32H7R7 GPIO you *do* configure

Only the slow control signals now.

| Function | Mode | Notes |
|---|---|---|
| `XVCLK` (MCO) | `GPIO_MODE_AF_PP`, AF0 | 24 MHz out |
| `SIOC` / `SIOD` (I2C) | `GPIO_MODE_AF_OD` | external pull-ups to `DOVDD` |
| `RESETB` | `GPIO_MODE_OUTPUT_PP`, low speed | |
| `PWDN` | `GPIO_MODE_OUTPUT_PP`, low speed | |

```c
/* MCO for XVCLK */
GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
GPIO_InitStruct.Pull      = GPIO_NOPULL;
GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
GPIO_InitStruct.Alternate = GPIO_AF0_MCO;

/* I2C */
GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
GPIO_InitStruct.Pull      = GPIO_NOPULL;      /* external pull-ups */

/* RESETB, PWDN */
GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull      = GPIO_NOPULL;
GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
```

### 2.5 Decoupling

Follow the datasheet's reference schematic (figure 2-2): 0.1 µF at every supply
ball, 1 µF bulk per rail, 3.3 µH ferrites in series with `AVDD`, `DOVDD` and
`PVDD`. Connect the different ground planes at a **single point**. Do not fit
R1/R2 (the 10 Ω `PWDN`/`RESETB` series parts).

Add for the MIPI build: **`EVDD` gets its own ferrite and its own 0.1 µF**, and
`EGND` (K8, K11) ties to the analog ground pour, not the digital one. A shared,
noisy `EVDD` produces intermittent D-PHY errors rather than a clean failure,
which is a bad thing to debug at 2 a.m.

---

## 3. Calculations, all in one place

### 3.1 Clock tree

```
VCO       = XVCLK × mult ÷ pre_div                                ≤ 800 MHz
PCLK      = VCO ÷ sys_div ÷ root_div ÷ bit_div ÷ sclk_root_div
SERCLK    = VCO ÷ sys_div ÷ root_div ÷ mipi_div
lane_rate = 2 × SERCLK
```

| Term | Register | Field | Legal values |
|---|---|---|---|
| `pre_div` | `0x3037` | `[3:0]` | 1, 2, 3, 4, 6, 8 |
| `mult` | `0x3036` | `[7:0]` | 4–127 any; 128–252 even only |
| `root_div` | `0x3037` | `[4]` | 0 → ÷1, 1 → ÷2 |
| `sys_div` | `0x3035` | `[7:4]` | 1–15 (0 means 16) |
| `mipi_div` | `0x3035` | `[3:0]` | 1–15 |
| `bit_div` | `0x3034` | `[3:0]` | `0x8` → ÷2, `0xA` → ÷2.5 |
| `sclk_root_div` | `0x3108` | `[1:0]` | ÷1, ÷2, ÷4, ÷8 |

> The datasheet lists `pre_div` as {1, 2, 3, 4, 6, 8}. Some OmniVision
> application notes also use register values 5 and 7 for ÷1.5 and ÷2.5 taps.
> Those are not in the datasheet — stick to the documented six.

### 3.2 Frame rate and line time

```
fps     = PCLK ÷ (HTS × VTS)
t_row   = HTS ÷ PCLK
t_frame = HTS × VTS ÷ PCLK
```

`HTS` and `VTS` are in **pixel** periods here, which is why OmniVision's
published mode tables can be used as written on CSI-2. `HTS` must exceed the
readout width (ISP input width after subsampling), and `VTS` must exceed the
readout height.

To change frame rate without touching the PLL:

```
VTS = PCLK ÷ (HTS × fps_target)
```

### 3.3 The lane budget — the CSI-2-specific one

```
required_lane_rate = PCLK × bits_per_pixel ÷ num_lanes
```

**`VTS` and frame rate are not in this expression.** Blanking lines do not slow
the pixels inside an active line, so lowering the frame rate does not lower the
peak lane rate. Only lowering `PCLK` does.

Available:

```
available_lane_rate = 2 × VCO ÷ (sys_div × root_div × mipi_div)
mipi_div            = floor( (2 × VCO ÷ sys_div ÷ root_div) ÷ required_lane_rate )
```

The headroom ratio is worth internalising, because it explains the one-lane
problem:

```
available_max ÷ required = 2 × bit_div × sclk_root_div × num_lanes ÷ bpp
```

`VCO` cancels. So a one-lane shortfall **cannot be fixed by retuning the PLL** —
every multiplier fails by the same factor. With `bit_div` = 2, `sclk_root_div`
= 2 and 16 bpp, the ratio is `num_lanes ÷ 2`: exactly 1.0 for two lanes, 0.5 for
one. The fix for one lane is `sclk_root_div` = 4, which halves `PCLK` and the
frame rate with it.

### 3.4 D-PHY timing conversion

```
0x4837 = round(2000 ÷ SERCLK_MHz)         /* period in half-nanoseconds */

parameter_real = parameter_min_ns + T_UI × parameter_min_UI
T_UI           = 1 ÷ lane_rate
```

### 3.5 Exposure, gain, banding

```
t_row             = HTS ÷ PCLK
exposure_lines    = t_exposure ÷ t_row
exposure_register = exposure_lines × 16       /* low nibble MUST be 0 */
   constraint:      exposure_lines ≤ VTS + extra_VTS − 4

gain_register     = gain_x × 16               /* max 64x */

band_step_50 = (PCLK ÷ 100) ÷ HTS
band_step_60 = (PCLK ÷ 120) ÷ HTS
max_bands    = (VTS − 4) ÷ band_step
```

### 3.6 Frame buffer sizing

```
bytes_per_frame = width × height × bytes_per_pixel
byte_rate       = bytes_per_frame × fps
```

| Mode | Format | bytes/frame | fps | byte rate | Where it fits |
|---|---|---|---|---|---|
| QQVGA 160×120 | RGB565 | 38 400 | 30 | 1.2 MB/s | internal SRAM |
| QVGA 320×240 | RGB565 | 153 600 | 30 | 4.6 MB/s | internal SRAM |
| VGA 640×480 | RGB565 | 614 400 | 30 | 18.4 MB/s | internal SRAM if you have it, else external |
| VGA 640×480 | RAW8 | 307 200 | 30 | 9.2 MB/s | internal SRAM |
| SXGA 1280×960 | RGB565 | 2 457 600 | 30 | 73.7 MB/s | external |
| 720p 1280×720 | RGB565 | 1 843 200 | 60 | 110.6 MB/s | external |
| 1080p 1920×1080 | RGB565 | 4 147 200 | 30 | 124.4 MB/s | external |
| 5 MP 2592×1944 | RGB565 | 10 077 696 | 15 | 151.2 MB/s | external, stills |
| 5 MP 2592×1944 | RAW8 | 5 038 848 | 15 | 75.6 MB/s | external, stills |

Two things to notice:

**RAW8 halves everything** — frame size, byte rate, and lane rate. If you are
going to demosaic on the STM32 anyway (DCMIPP Pipe 1 will do it in hardware),
sending RAW8 instead of RGB565 is close to free bandwidth.

**Unlike the DVP build, there is no DMA transfer-size ceiling.** DCMIPP writes
through its own master port with a full byte count. The 65535-word `NDTR` limit
that forced double-buffering for anything VGA-and-above is gone.

---

## 4. Important points, in rough order of how much time they cost

1. **`0x4837` is the one everyone misses.** Set it from the actual SERCLK, not
   the reset default. Wrong value → SoT/ECC errors and intermittent frames.
   See README §8.
2. **The receiver's data type must match `0x4300`.** Mismatch gives you **no
   frames and no errors** — the packets are silently discarded.
3. **`0x300E` selects MIPI.** Bit[2] = 1, bit[4] = 0 so the TX PHY is alive. If
   the lanes never leave LP-11, this is the first suspect; try `0x45`/`0x40`
   (README §0).
4. **Read the chip ID first.** `0x300A`/`0x300B` = `0x5640`. Everything else is
   guesswork until this passes.
5. **Respect t4 ≥ 20 ms** between `RESETB` rising and the first SCCB access.
6. **Hard reset is mandatory on power-up**, even with the on-chip reset (§2.8).
   Pulse ≥ 1 ms.
7. **`0x3008[6]` is software power-down.** The init sets `0x3008 = 0x42` early
   and `0x3008 = 0x02` at the very end. Forget the last write and you get a
   perfectly configured sensor that transmits nothing.
8. **Configure the receiver's PHY bitrate to match the sensor's.** The D-PHY
   does not measure the incoming rate.
9. **One lane costs you half the frame rate**, and no PLL setting recovers it
   (§3.3).
10. **Invalidate the D-cache** after every frame, or make the buffer
    non-cacheable. 32-byte alignment, size a multiple of 32.
11. **`EVDD` decoupling matters now.** It powers the MIPI transmitter.
12. **100 Ω differential, minimal intra-pair skew, no series termination** (§2.2).
13. **Raise `VTS` before raising exposure**, never the other way round.
14. **RAW10 moves `bit_div` from 2 to 2.5**, dropping `PCLK` 20% for the same
    PLL: VGA 30 → 24 fps, 1080p 30 → 24, 5 MP 15 → 12. RAW8 has no such cost —
    it halves the lane rate at full frame rate. Recompute rather than assuming.
15. **Registers marked "Debug mode"**: leave them alone. The magic values in the
    init table (`0x3630`, `0x3631`, `0x3703`, `0x3715`, `0x3731`, `0x3905` …)
    are OmniVision's analog trim. Undocumented on purpose, and not optional.
16. **Settling time after a register change is up to 300 ms** (§8.4, table 8-4).
    Discard the first frames after any mode change.
17. **The ISP tuning tables are reference values.** LENC, AWB, CMX, gamma and
    SDE come from OmniVision's reference initialisation, not from your lens.

---

## 5. Register quick reference

| Range | Block | § |
|---|---|---|
| `0x3000`–`0x3052` | system and IO pad control, PLL | 7.1 |
| `0x3100`–`0x3108` | SCCB control, root dividers | 7.2 |
| `0x3200`–`0x3212` | SRB / group write | 7.3 |
| `0x3400`–`0x3406` | AWB gain | 7.4 |
| `0x3500`–`0x350D` | AEC/AGC (exposure, gain, VTS) | 7.5 |
| `0x3600`–`0x3606` | VCM driver (autofocus actuator) | 7.6 |
| `0x3800`–`0x3821` | timing: window, HTS/VTS, subsample, flip | 7.7 |
| `0x3A00`–`0x3A25` | AEC/AGC power-down domain, banding | 7.8 |
| `0x3B00`–`0x3B0C` | strobe / flash | 7.9 |
| `0x3C00`–`0x3C1E` | 50/60 Hz flicker detector | 7.10 |
| `0x3D00`–`0x3D21` | OTP memory | 7.11 |
| `0x4000`–`0x4033` | black level calibration | 7.13 |
| `0x4300`–`0x430D` | format control | 7.15 |
| **`0x4800`–`0x4837`** | **MIPI transmitter and D-PHY timing** | **7.19** |
| `0x5000`–`0x5063` | ISP top control | 7.21 |
| `0x5180`–`0x51D0` | AWB | 7.22 |
| `0x5300`–`0x530F` | colour interpolation (demosaic) | 7.23 |
| `0x5380`–`0x538B` | colour matrix | 7.24 |
| `0x5480`–`0x5490` | gamma | 7.25 |
| `0x5580`–`0x558C` | special digital effects | 7.26 |
| `0x5600`–`0x5606` | scaler | 7.27 |
| `0x5800`–`0x5849` | lens correction | 7.29 |
| `0x6000`–`0x603F` | autofocus control | 7.30 |

### MIPI transmitter registers (§7.19) — the block that is new

| Register | Field | Meaning |
|---|---|---|
| `0x4800` | `[5]` | clock lane gate: 0 = free running, 1 = gate when idle |
| | `[4]` | line sync: send a short packet per line |
| | `[3]` | lane select: default data lane |
| | `[2]` | idle status: 0 = LP00, 1 = LP11 |
| `0x4801` | `[4:2]` | packet-header bit/byte order for ECC |
| `0x4805` | `[7:6]` | lane disable (lane goes LP00) |
| | `[5]` | LPX global timing: 0 = auto, 1 = use `lp_p_min` |
| `0x480A` | `[2]` | bit order reverse |
| | `[1:0]` | bit position adjust |
| `0x4818`/`0x4819` + `0x482A` | | `hs_zero` min, ns + UI |
| `0x481A`/`0x481B` + `0x482B` | | `hs_trail` min, ns + UI |
| `0x481C`/`0x481D` + `0x482C` | | `clk_zero` min, ns + UI |
| `0x481E`/`0x481F` + `0x482D` | | `clk_prepare` min, ns + UI |
| `0x4820`/`0x4821` + `0x482E` | | `clk_post` min, ns + UI |
| `0x4822`/`0x4823` + `0x482F` | | `clk_trail` min, ns + UI |
| `0x4824`/`0x4825` + `0x4830` | | `lpx_p` min, ns + UI |
| `0x4826`/`0x4827` + `0x4831` | | `hs_prepare` min, ns + UI |
| `0x4828`/`0x4829` + `0x4832` | | `hs_exit` min, ns + UI |
| **`0x4837`** | `[7:0]` | **pixel clock period, half-nanosecond units** |

Leave the ns/UI pairs at their defaults — they are the D-PHY specification
minimums. Set `0x4837` from your actual clock, every time.

### Clock-lane mode: continuous or gated

`0x4800[5]` decides whether the clock lane free-runs or drops to LP between
packets.

- **Continuous (bit = 0)** — the clock lane stays in high-speed the whole time.
  Simpler for the receiver to lock to, more power, and the safer default for
  bring-up. **Start here.**
- **Gated (bit = 1)** — the clock lane goes LP when there is nothing to send.
  Lower power. Requires the receiver to support non-continuous clock mode and to
  re-acquire on each burst.

If your receiver reports intermittent SoT errors and you have `0x4800[5]` set,
clear it and see if they go away before you chase anything else.

### The ISP enable bits

```
0x5000  bit[7] LENC   bit[5] RAW gamma  bit[2] black pixel cancel
        bit[1] white pixel cancel       bit[0] colour interpolation (demosaic)

0x5001  bit[7] SDE    bit[5] scale      bit[2] UV average
        bit[1] colour matrix            bit[0] AWB

0x5003  bit[2] binning enable
```

`0x5000 = 0xA7` / `0x5001 = 0xA3` is the everything-on RGB/YUV configuration.
For RAW Bayer output use `0x5000 = 0x06` — demosaic and gamma off, so the mosaic
reaches you intact.

### Mapping the ISP pipeline onto registers

The pipeline described in `../../post.md` maps almost one-to-one onto the
OV5640's own ISP blocks:

| Pipeline stage (post.md) | OV5640 block | Registers | § |
|---|---|---|---|
| black level correction | BLC | `0x4000`–`0x4033` | 4.7 |
| defective pixel correction | DPC | `0x5000[2:1]`, `0x5300`+ | 5.5 |
| lens shading correction | LENC | `0x5800`–`0x5849` | 5.2 |
| white balance | AWB | `0x5180`–`0x51D0`, `0x3400`+ | 5.3 |
| **demosaic** | CIP | `0x5000[0]`, `0x5300`–`0x530F` | 5.6 |
| colour correction matrix | CMX | `0x5380`–`0x538B` | 5.7 |
| gamma | raw gamma / GMA | `0x5480`–`0x5490`, `0x5000[5]` | 5.4 |
| saturation, hue, contrast | SDE | `0x5580`–`0x558C` | 5.11 |
| RGB → YUV | ISP format | `0x501F`, `0x4300` | 5.12 |

Everything before CIP is single-channel Bayer; everything after is full colour.
Turning `0x5000[0]` off is literally the "stop before demosaic" switch — and on
this platform that is a practical choice, not just a teaching aid: send RAW8 at
half the lane rate and let DCMIPP's Pipe 1 do the demosaic in hardware.

---

## 6. Test patterns — bisecting a CSI-2 bring-up

```
0x503D = 0x80    ISP colour bar
0x503D = 0x00    normal output
```

With CSI-2 there are more layers than there were on DVP, so bisect in this
order:

1. **Lanes at LP-11 with the sensor idle?** No → sensor PHY not enabled
   (`0x300E`). This needs nothing but a scope and costs 30 seconds.
2. **Does the receiver report a locked PHY?** No → lane rate mismatch between
   what you configured in the sensor and in the D-PHY.
3. **Any packets at all, even errored?** No → `0x300E`, `0x4805` lane disables.
4. **Packets with ECC/SoT errors?** → `0x4837` first, then signal integrity,
   then `EVDD`.
5. **Clean packets but no frames?** → data type mismatch between `0x4300` and
   the receiver's filter.
6. **Colour bar good, real image bad?** → optics, exposure, or ISP tuning. The
   transport is fine; stop debugging the link.

The colour bar is generated inside the ISP, so a good bar proves everything from
the ISP output through the D-PHY, the receiver, DCMIPP and into memory. It
isolates the pixel array and the optics out of the problem entirely.

---

## 7. Autofocus, briefly

The OV5640 carries an embedded 8051 and a VCM driver, and can run closed-loop
autofocus without host involvement. What you need:

1. Hold the MCU in reset: `0x3000[5] = 1`.
2. Download the OmniVision AF firmware blob to `0x8000` onwards.
3. Release: `0x3000[5] = 0`, enable the MCU clock `0x3004[5] = 1`.
4. Poll `0x3029` for `0x70` (firmware ready).
5. Command through `0x3022` — `0x03` single focus, `0x04` continuous, `0x08`
   release, `0x06` pause.

The blob is not in the datasheet; get it from OmniVision or your module vendor.

Without the blob, drive the VCM manually (§3.3):

```
0x3603[5:0] = target[9:4]      VCM target value, 10 bits
0x3602[7:4] = target[3:0]
0x3602[3:0] = slew rate control
0x3603[7]   = PWDN VCM
```

Sweep the target, compute a focus metric (sum of absolute Laplacian, or read the
sensor's AFC statistics at `0x6000`–`0x603F`), pick the peak.

---

## 8. Errata-ish things noticed in the datasheet

- **`0x300E[7:5]`** is documented as 000 = one lane, 001 = two lane, "others:
  debug mode" — but the register's own reset default `0x58` puts `010` in that
  field, and the mainline Linux driver streams with `0x45` (also `010`). Either
  the encoding table is incomplete or the field is not really a lane selector.
  Treat `0x45`/`0x40` as the field-proven stream on/off pair. This is the single
  most likely thing to cost you time.
- **`0x4805`** lists bit[7] and bit[6] with *identical* descriptions ("MIPI
  lane1 disable"). Bit[6] is presumably lane 2. It then documents "Bit[6:0]:
  Debug mode" *after* describing bits 7, 6 and 5, so the field map contradicts
  itself. Leave `0x4805` at its default `0x10` unless you are deliberately
  disabling a lane.
- Table 1-1 (§1) lists pin K5 as `D0/GPIO2`; figure 1-1 labels the same ball
  `D0/GPIO4`. Table 1-1 agrees with the register descriptions (`0x3052[0]` =
  GPIO0, `[1]` = GPIO1), so the figure is the typo. Irrelevant for CSI-2, where
  K5 is unconnected.
- Register `0x3819` (HSYNC width low byte) is documented as `Bit[7:4]: Debug
  mode / Bit[3:0]: HSYNC width[7:8]`. That bit range makes no sense — it is
  almost certainly `[7:0]`, matching `0x3817`.
- Table 8-3, "720p @ 60 fps" row: `IDD-DO` max reads 42 mA against a typical of
  100 mA. The max column looks copied from the row above.
- §6.7 on MIPI is three sentences long and ends with "contact your local
  OmniVision FAE for more details." The register table in §7.19 is the real
  documentation; there is no MIPI timing diagram anywhere in the datasheet.
