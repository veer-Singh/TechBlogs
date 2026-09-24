# Device Tree (DTS and DTB)

## Contents

| # | Section | What you'll learn |
| --- | --- | --- |
| – | [Abbreviations](#abbreviations) | Every short form used in these notes, written in full |
| 1 | [What is a device tree?](#1-what-is-a-device-tree) | The definition, the block diagram and the journey from text to working devices |
| 2 | [Why do we need a device tree?](#2-why-do-we-need-a-device-tree) | Why embedded hardware can't describe itself, and what was used before |
| 3 | [The file types: DTS, DTSI, DTB, DTBO](#3-the-file-types-dts-dtsi-dtb-dtbo) | What each file is, who writes it, and how they fit together |
| 4 | [Writing a DTS: the syntax, step by step](#4-writing-a-dts-the-syntax-step-by-step) | Nodes, properties, values, labels, addresses and special nodes |
| 5 | [Properties you'll see everywhere](#5-properties-youll-see-everywhere) | The common properties and what each one tells the kernel |
| 6 | [A complete board example](#6-a-complete-board-example) | A small but real `.dts`, explained line by line |
| 7 | [From DTS to DTB: compiling](#7-from-dts-to-dtb-compiling) | Building with the kernel, building by hand, and decompiling |
| 8 | [Inside a DTB](#8-inside-a-dtb) | The binary format: header, memory reservation, structure and strings |
| 9 | [How the DTB reaches the kernel](#9-how-the-dtb-reaches-the-kernel) | What U-Boot does with the DTB before it starts Linux |
| 10 | [How the kernel uses the DTB](#10-how-the-kernel-uses-the-dtb) | Node-to-driver matching, and reading properties in driver code |
| 11 | [Overlays (DTBO)](#11-overlays-dtbo) | Patching the tree for add-on boards, without rebuilding it |
| 12 | [Bindings: the rulebook](#12-bindings-the-rulebook) | Where the allowed properties are documented, and how to check a DTS |
| 13 | [Debugging a device tree](#13-debugging-a-device-tree) | Commands on the running board, and the common errors |
| 14 | [Simple code examples](#14-simple-code-examples) | Eight small examples: LED, button, UART, I2C sensor, SPI flash, disabling a device, your own driver, an overlay |
| 15 | [Interview quick answers](#15-interview-quick-answers) | Short answers to say out loud |

---

## Abbreviations

| Short form | Full form | In one line |
| --- | --- | --- |
| ACPI | Advanced Configuration and Power Interface | How a PC's firmware describes its hardware to the OS |
| ARM / Arm | Advanced RISC Machines | The CPU family in most embedded chips |
| BSP | Board Support Package | The board-specific software (see [BSP.md](BSP.md)) |
| cpp | C Preprocessor | Expands `#include` and `#define` before `dtc` runs |
| CPU | Central Processing Unit | The processor core |
| DDR | Double Data Rate (memory) | The type of external DRAM |
| DRAM | Dynamic Random Access Memory | Large external working memory |
| DT | Device Tree | A data structure that describes the hardware of a board |
| DTB | Device Tree Blob | The compiled, binary device tree the kernel reads |
| DTBO | Device Tree Blob Overlay | A compiled patch applied on top of a DTB |
| dtc | Device Tree Compiler | Turns `.dts` text into a `.dtb` binary, and back |
| DTS | Device Tree Source | The human-readable text file for one board |
| DTSI | Device Tree Source Include | A shared text file, included by `.dts` files (usually the SoC) |
| DTSpec | Devicetree Specification | The official document that defines the device tree format |
| eMMC | embedded MultiMediaCard | Flash storage chip soldered on the board |
| FDT | Flattened Device Tree | The binary format of a DTB |
| FIT | Flattened Image Tree | A U-Boot image format that packs kernel, DTBs and overlays in one file |
| GIC | Generic Interrupt Controller | Arm's interrupt controller |
| GPIO | General-Purpose Input/Output | A pin controlled directly by software |
| GPS | Global Positioning System | Satellite positioning receiver |
| HAT | Hardware Attached on Top | A Raspberry Pi add-on board |
| I2C | Inter-Integrated Circuit | A two-wire bus for sensors and small chips |
| IRQ | Interrupt Request | A hardware signal that interrupts the CPU |
| LED | Light-Emitting Diode | An indicator light |
| MAC | Media Access Control (address) | The unique hardware address of a network interface |
| MMC | MultiMediaCard | The memory card standard behind SD and eMMC |
| MTD | Memory Technology Device | The Linux interface for raw flash chips |
| NOR | NOR flash (named after the NOR logic gate) | Flash that is read like memory; common as small SPI flash chips |
| OF | Open Firmware | The original standard the device tree comes from; kernel functions start with `of_` |
| OS | Operating System | The main software that manages the hardware (for example Linux) |
| PC | Personal Computer | A desktop or laptop computer |
| PCI / PCIe | Peripheral Component Interconnect / PCI Express | The PC expansion bus; its devices describe themselves |
| PHY | Physical layer (chip) | The chip that drives the actual network cable |
| PMIC | Power Management Integrated Circuit | The chip that provides the board's supply voltages |
| RAM | Random Access Memory | Working memory |
| RISC | Reduced Instruction Set Computer | The CPU design style of Arm and RISC-V |
| RTC | Real-Time Clock | A chip that keeps the time while the board is off |
| RTOS | Real-Time Operating System | A small OS for microcontrollers, such as FreeRTOS or Zephyr |
| SD | Secure Digital | Removable memory card |
| SoC | System on Chip | The main processor chip, with many peripherals inside |
| SoM | System on Module | A small board with the SoC, memory and PMIC, plugged into a carrier board |
| SPI | Serial Peripheral Interface / Shared Peripheral Interrupt | A four-wire bus; in `GIC_SPI` it means an interrupt shared by all CPUs |
| UART | Universal Asynchronous Receiver-Transmitter | The serial port used for the debug console |
| USB | Universal Serial Bus | The common plug-in bus; its devices describe themselves |
| YAML | YAML Ain't Markup Language | The text format of the device tree binding files |

---

## 1. What is a device tree?

> A **device tree** is a **data structure that describes the hardware of a board**: which devices exist, at which addresses, which interrupts, clocks, pins and power supplies they use, and how they are connected. The kernel reads it at boot, so the **hardware description is kept outside the kernel code**.

Two files are at the centre of it:

- **DTS** (Device Tree Source): the **text** version, written by a person. It is easy to read and edit.
- **DTB** (Device Tree Blob): the **binary** version, made from the DTS by a compiler. It is what the bootloader loads and the kernel reads.

The DTS is to the DTB what a `.c` file is to a compiled program: you write one and the machine uses the other.

### The device tree block diagram

![The device tree from a text file to working devices: the source files (.dtsi and .dts) go through the C preprocessor, which expands includes and macros, then the Device Tree Compiler dtc checks the syntax and makes the binary .dtb; the bootloader U-Boot loads the .dtb into RAM, may patch it and passes its address to the Linux kernel, which matches compatible strings and probes drivers so devices appear in /dev and /sys; optionally, overlays (.dtbo) are applied on top of the .dtb by the bootloader](images/device_tree_big_picture.svg)

The journey, step by step:

1. **Source files.** You describe the board in text:
   - the **`.dtsi`** file describes the SoC (everything inside the chip). The chip vendor writes it.
   - the **`.dts`** file describes your board. You write it, and it includes the `.dtsi`.
2. **C preprocessor (cpp).** It expands `#include` lines and `#define` names, such as `GPIO_ACTIVE_LOW`, into plain numbers. This is the same preprocessor used for C code.
3. **Device Tree Compiler (dtc).** It checks the syntax and turns the text into one binary file.
4. **The blob (`.dtb`).** A small binary (usually 20 to 100 KB), stored on the boot storage next to the kernel image, for example in `/boot`.
5. **The bootloader (U-Boot).** It loads the `.dtb` into RAM, may **patch** it (for example to add the real memory size or the MAC address), and passes its **address** to the kernel.
6. **The Linux kernel.** It reads the `.dtb`, finds a driver for each device by its `compatible` string, and starts the driver. The device then appears in `/dev` and `/sys`.
7. **Optional: overlays (`.dtbo`).** Small patches that the bootloader applies on top of the `.dtb`, for example when an add-on board is plugged in ([section 11](#11-overlays-dtbo)).

---

## 2. Why do we need a device tree?

### Some hardware can describe itself, embedded hardware can't

1. On a PC, most hardware **announces itself**:
   - A **PCI** (Peripheral Component Interconnect) card has ID registers that the OS reads.
   - A **USB** (Universal Serial Bus) device sends its descriptors when it is plugged in.
   - The motherboard firmware describes the rest through **ACPI** (Advanced Configuration and Power Interface) tables.
2. On an embedded board, most devices **can't be discovered**:
   - A temperature sensor on an **I2C** (Inter-Integrated Circuit) bus doesn't say "I'm here".
   - The UART inside the SoC is at a fixed memory address. Nothing tells the kernel that address.
   - An LED on a **GPIO** (General-Purpose Input/Output) pin is just a wire. The kernel can't see it.
3. So the kernel must be **told** what is on the board. The device tree is that description.

### What was used before: board files

1. Before about 2011, each Arm board had a **board file** in the kernel source, a C file such as `arch/arm/mach-xxx/board-myboard.c`.
2. It listed every device of the board as C structures, and was compiled **into the kernel**.
3. This caused three problems:
   - **One kernel per board.** A kernel built for board A didn't boot on board B.
   - **Every board change needed a kernel change**, even moving a sensor to another I2C address.
   - **The kernel source grew huge**, with thousands of nearly identical board files. Linus Torvalds complained about it publicly in 2011.
4. Arm Linux then moved to the device tree. The format already existed: it came from **Open Firmware (OF)** on PowerPC and Sun machines, which is why kernel functions for it start with `of_`.

### What the device tree gives you

| Without a device tree (board files) | With a device tree |
| --- | --- |
| Hardware described in C, inside the kernel | Hardware described in a separate data file |
| One kernel image per board | **One kernel image for many boards**; each board gets its own small `.dtb` |
| Changing a pin or address means rebuilding the kernel | Only the `.dtb` is rebuilt |
| Drivers contain board details | Drivers are generic; the details come from the tree |

> **Who uses it?** Linux on Arm, RISC-V and PowerPC, the U-Boot bootloader, and **Zephyr** (an RTOS, Real-Time Operating System, for microcontrollers). In Zephyr the device tree is used at **build time**: it is turned into a C header file, so there's no DTB on the device. PCs (x86) and Arm servers use ACPI instead.

---

## 3. The file types: DTS, DTSI, DTB, DTBO

### The four files

| File | Full name | Text or binary | Who writes it | What it holds |
| --- | --- | --- | --- | --- |
| `.dtsi` | Device Tree Source Include | Text | The chip vendor (or the SoM maker) | Everything **inside the SoC**: CPUs, memory map, UARTs, I2C, SPI, GPIO, clocks. Most blocks are `disabled`. |
| `.dts` | Device Tree Source | Text | **You**, for your board | `#include`s the `.dtsi`, **turns on** the blocks your board uses, and adds the chips **outside** the SoC |
| `.dtb` | Device Tree Blob | Binary | Made by `dtc` | The whole tree for one board, merged and compiled |
| `.dtbo` | Device Tree Blob Overlay | Binary | Made by `dtc` from an overlay `.dts` | A patch applied on top of a `.dtb` at boot |

### How the files fit together

![The device tree files: 1, soc.dtsi from the chip vendor with everything inside the chip and most blocks disabled; 2, an optional som.dtsi for a module many boards share, with memory size, PMIC and eMMC; 3, board.dts written by you, which includes the .dtsi files, turns on what this board uses and adds chips outside the SoC; cpp and dtc turn it into 4, board.dtb, one binary for this board; 5, an optional board-overlay.dtbo is applied on top of board.dtb at boot; the rule is that a later file wins](images/device_tree_file_layers.svg)

1. **`soc.dtsi`** describes the chip. Every board that uses this chip includes it.
2. **`som.dtsi`** (optional) describes a **SoM** (System on Module): a small plug-in board with the SoC, memory and PMIC. Many carrier boards share it.
3. **`board.dts`** includes the files above and describes **your** board.
4. **`cpp` and `dtc`** merge all of them into **one `board.dtb`**.
5. **An overlay** (`.dtbo`) can change that `.dtb` at boot, without rebuilding it.

**The rule: a later definition wins.** If a property is set in the `.dtsi` and set again in the `.dts`, the `.dts` value is used. That's how a board turns on a disabled block: the `.dtsi` says `status = "disabled"`, and the `.dts` says `status = "okay"`.

### Where they live in the kernel source

| Architecture | Folder | Example |
| --- | --- | --- |
| 64-bit Arm | `arch/arm64/boot/dts/<vendor>/` | `arch/arm64/boot/dts/freescale/imx8mm-evk.dts` |
| 32-bit Arm | `arch/arm/boot/dts/<vendor>/` (vendor folders since kernel 6.5) | `arch/arm/boot/dts/ti/omap/am335x-boneblack.dts` |
| RISC-V | `arch/riscv/boot/dts/<vendor>/` | `arch/riscv/boot/dts/starfive/jh7110-starfive-visionfive-2-v1.3b.dts` |

Shared macros such as `GPIO_ACTIVE_LOW` and `IRQ_TYPE_LEVEL_HIGH` come from header files in `include/dt-bindings/`.

---

## 4. Writing a DTS: the syntax, step by step

![Anatomy of a device tree node: in the code i2c1: i2c@30a20000 with compatible, reg, interrupts and status, and a child node sensor@48; 1, the label i2c1 is a nickname that other nodes use with &i2c1; 2, the node name is name@unit-address, the address being the first value of reg; 3, a property is name = value; compatible picks the driver; 4, reg says where the device is; 5, status okay means use it and disabled means skip it; 6, the child node sensor@48 is a device on this I2C bus at address 0x48; 7, every node and property ends with a semicolon](images/device_tree_node_anatomy.svg)

The numbers below follow the picture.

### 4.1 The tree: nodes inside nodes

1. The file starts with `/dts-v1/;`, which says "this is version 1 of the DTS format".
2. The **root node** is written `/ { ... };`. Everything else is inside it.
3. A **node** is one device, or one bus. Nodes contain **child nodes**, just like folders contain folders. That's why it's a *tree*.
4. A device sits under the bus it is connected to. An I2C sensor is a child of its I2C controller node.

```dts
/dts-v1/;

/ {                         /* the root node */
    soc {                   /* a child: the chip's internal bus */
        i2c@30a20000 {      /* a child of soc: an I2C controller */
            sensor@48 {     /* a child of the I2C controller: a device on that bus */
            };
        };
    };
};
```

### 4.2 Node names and unit addresses (picture: 2)

A node name has the form **`name@unit-address`**:

- **`name`** says what kind of device it is, using standard names: `serial`, `i2c`, `spi`, `ethernet`, `gpio`, `temperature-sensor`.
- **`unit-address`** is **the first address in the node's `reg` property**, written in hex without `0x`. It makes the name unique: two UARTs become `serial@30860000` and `serial@30890000`.
- A node without a `reg` has no `@` part, for example `chosen` or `leds`.

### 4.3 Properties and their values (picture: 3)

A **property** is a `name = value;` pair inside a node. The value can be one of these types:

| Type | Written as | Example |
| --- | --- | --- |
| String | `"text"` | `model = "MyCompany MyBoard";` |
| List of strings | `"a", "b"` | `compatible = "mycompany,myboard", "fsl,imx8mm";` |
| 32-bit numbers ("cells") | `<...>` | `reg = <0x48>;` or `clock-frequency = <400000>;` |
| Reference to another node | `<&label>` | `clocks = <&clk 42>;` |
| Bytes | `[...]` | `local-mac-address = [00 11 22 33 44 55];` |
| Empty (true/false flag) | only the name | `wakeup-source;` (present = true, missing = false) |

Every node and every property **ends with a semicolon** (picture: 7). A missing `;` is the most common `dtc` error.

### 4.4 Labels, references and phandles (picture: 1)

1. A **label** is a nickname for a node, written before its name: `i2c1: i2c@30a20000 { ... };`.
2. Anywhere else you can write **`&i2c1`** to mean "that node". There are two uses:
   - **To change a node from another file.** In your `.dts`, `&i2c1 { status = "okay"; };` edits the node defined in the `.dtsi`, without copying it.
   - **To point to a node from a property.** `clocks = <&clk IMX8MM_CLK_I2C1_ROOT>;` means "my clock comes from the `clk` node, output number `IMX8MM_CLK_I2C1_ROOT`".
3. `dtc` turns each reference inside `< >` into a **phandle**: a unique 32-bit number it gives the target node. The kernel follows phandles to find the clock, GPIO controller or regulator a device uses.

### 4.5 How addresses are counted: `#address-cells` and `#size-cells`

A **parent** node says how its children write their `reg`:

- **`#address-cells`**: how many 32-bit numbers make one address.
- **`#size-cells`**: how many 32-bit numbers make one size.

| Parent | Setting | A child's `reg` | Meaning |
| --- | --- | --- | --- |
| A 64-bit SoC bus | `<2>` and `<2>` | `reg = <0x0 0x30a20000 0x0 0x10000>;` | 64-bit address 0x30a20000, 64 KB of registers |
| A 32-bit SoC bus | `<1>` and `<1>` | `reg = <0x30a20000 0x10000>;` | Address and size, one number each |
| An I2C bus | `<1>` and `<0>` | `reg = <0x48>;` | Only the I2C address; there is no size |
| A SPI bus | `<1>` and `<0>` | `reg = <0>;` | The chip-select number |

If these don't match the number of values in `reg`, `dtc` prints a warning and the device gets the wrong address.

### 4.6 Turning devices on and off: `status` (picture: 5)

- `status = "okay";`: the kernel creates the device and looks for a driver.
- `status = "disabled";`: the kernel **skips** the node completely.
- A node with no `status` counts as `"okay"`.

The SoC `.dtsi` usually marks the blocks `"disabled"`, because not every board uses every UART or I2C bus. Your board file enables only what is wired.

### 4.7 Special nodes

A few nodes directly under the root have a fixed meaning:

| Node | What it holds | Example |
| --- | --- | --- |
| `memory@...` | Where the RAM is and how big it is. U-Boot usually corrects it with the real size. | `memory@40000000 { device_type = "memory"; reg = <0x0 0x40000000 0x0 0x80000000>; };` (2 GB at 0x40000000) |
| `chosen` | Settings passed to the kernel, not hardware: the console and the kernel command line | `chosen { stdout-path = &uart2; bootargs = "console=ttymxc1,115200"; };` |
| `aliases` | Fixed numbers for devices, so `serial0` or `ethernet0` doesn't change between boots | `aliases { serial0 = &uart2; ethernet0 = &fec1; };` |
| `cpus` | The CPU cores | one `cpu@0`, `cpu@1` ... per core |
| `reserved-memory` | RAM areas the kernel must leave alone, for example for a co-processor's firmware | `rproc_mem: rproc@b8000000 { reg = <...>; no-map; };` |

### 4.8 Removing things

- `/delete-property/ name;` removes a property that an included file set.
- `/delete-node/ &label;` removes a whole node, for example a device the reference board has and your board doesn't.

---

## 5. Properties you'll see everywhere

| Property | What it tells the kernel | Example |
| --- | --- | --- |
| `compatible` | **Which driver** should handle this node. A list from the most specific to the most generic, in the form `"vendor,device"`. | `compatible = "ti,tmp102";` |
| `reg` | **Where** the device is: a register address and size, or a bus address | `reg = <0x48>;` |
| `status` | Whether to use the node | `status = "okay";` |
| `interrupts` | **Which interrupt line** the device raises, and how. For the GIC (Generic Interrupt Controller) there are three numbers: the type (`GIC_SPI`, Shared Peripheral Interrupt), the number, and the trigger. | `interrupts = <GIC_SPI 35 IRQ_TYPE_LEVEL_HIGH>;` |
| `interrupt-parent` | Which interrupt controller those interrupts go to, when it isn't the parent's | `interrupt-parent = <&gpio1>;` |
| `clocks` / `clock-names` | Which clock(s) feed the device | `clocks = <&clk IMX8MM_CLK_I2C1_ROOT>;` |
| `pinctrl-names` / `pinctrl-0` | Which **pin configuration** to apply (which chip pins carry this device's signals) | `pinctrl-0 = <&pinctrl_i2c1>;` |
| `*-supply` | Which regulator powers the device | `vcc-supply = <&reg_3v3>;` |
| `*-gpios` | Which GPIO lines the device uses, and whether they are active high or low | `reset-gpios = <&gpio1 5 GPIO_ACTIVE_LOW>;` |
| `model` (root only) | The board's human-readable name; shown in `/proc/device-tree/model` | `model = "MyCompany MyBoard";` |

**Why `compatible` is a list.** The kernel tries each string in order. For `compatible = "fsl,imx8mm-i2c", "fsl,imx21-i2c";` it first looks for an i.MX 8M Mini driver. If there isn't one, it uses the older i.MX21 driver, which works because the hardware is the same.

---

## 6. A complete board example

A board with the i.MX 8M Mini SoC, a debug console on UART2, a TMP102 temperature sensor on I2C bus 1 and a status LED:

```dts
/dts-v1/;

#include <dt-bindings/gpio/gpio.h>        /* defines GPIO_ACTIVE_HIGH / LOW */
#include "imx8mm.dtsi"                    /* everything inside the SoC */

/ {
    model = "MyCompany MyBoard";
    compatible = "mycompany,myboard", "fsl,imx8mm";

    chosen {
        stdout-path = &uart2;             /* the kernel console */
    };

    memory@40000000 {
        device_type = "memory";
        reg = <0x0 0x40000000 0x0 0x40000000>;   /* 1 GB of DDR at 0x40000000 */
    };

    leds {
        compatible = "gpio-leds";
        status-led {
            label = "status";
            gpios = <&gpio1 13 GPIO_ACTIVE_HIGH>;  /* GPIO1, pin 13 */
            linux,default-trigger = "heartbeat";   /* blink to show Linux is alive */
        };
    };
};

&uart2 {
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_uart2>;
    status = "okay";                      /* was "disabled" in the .dtsi */
};

&i2c1 {
    clock-frequency = <400000>;           /* 400 kHz */
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_i2c1>;
    status = "okay";

    temperature-sensor@48 {
        compatible = "ti,tmp102";         /* the driver to use */
        reg = <0x48>;                     /* its I2C address */
    };
};

&iomuxc {
    pinctrl_i2c1: i2c1grp {
        fsl,pins = <
            MX8MM_IOMUXC_I2C1_SCL_I2C1_SCL  0x400001c3
            MX8MM_IOMUXC_I2C1_SDA_I2C1_SDA  0x400001c3
        >;
    };

    pinctrl_uart2: uart2grp {
        fsl,pins = <
            MX8MM_IOMUXC_UART2_RXD_UART2_DCE_RX  0x140
            MX8MM_IOMUXC_UART2_TXD_UART2_DCE_TX  0x140
        >;
    };
};
```

**Reading it from top to bottom:**

1. **`#include`** lines pull in the GPIO macros and the SoC description.
2. **The root node** names the board (`model`) and says which board and SoC it is (`compatible`).
3. **`chosen`** sends kernel messages to UART2.
4. **`memory`** says there is 1 GB of RAM starting at address 0x40000000.
5. **`leds`** is a board-level device. The generic `gpio-leds` driver turns it into `/sys/class/leds/status/`, and the `heartbeat` trigger makes it blink.
6. **`&uart2`** and **`&i2c1`** switch on two blocks that the `.dtsi` defined but disabled, and choose their pins.
7. **`temperature-sensor@48`** is a child of `&i2c1`, so the kernel knows it's on I2C bus 1 at address 0x48.
8. **`&iomuxc`** is the SoC's pin controller. Each line picks what a chip pin does (here: I2C clock and data, UART receive and transmit) and its electrical settings (the hex number: pull-up, drive strength).

---

## 7. From DTS to DTB: compiling

### 7.1 With the kernel build (the normal way)

1. Put your `.dts` in the right folder, for example `arch/arm64/boot/dts/freescale/myboard.dts`.
2. Add it to the `Makefile` in that folder:

   ```make
   dtb-$(CONFIG_ARCH_MXC) += myboard.dtb
   ```

3. Build all device trees, or just yours:

   ```bash
   make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- dtbs                     # all of them
   make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- freescale/myboard.dtb     # only yours
   ```

4. The result is `arch/arm64/boot/dts/freescale/myboard.dtb`.

The kernel build runs `cpp` and `dtc` for you, with the right include paths. In **Yocto**, the `KERNEL_DEVICETREE` setting lists which `.dtb` files to build (see [Yocto_fundamentals.md](Yocto_fundamentals.md)).

### 7.2 By hand

When the file uses `#include`, run the preprocessor first, then the compiler:

```bash
# 1. Preprocess: expand #include and #define
cpp -nostdinc -I include -I arch/arm64/boot/dts -undef -x assembler-with-cpp \
    myboard.dts > myboard.pre.dts

# 2. Compile the text into a blob
dtc -I dts -O dtb -o myboard.dtb myboard.pre.dts
```

A file with no `#include` can go straight to `dtc`. The `dtc` options read as: `-I` = input format, `-O` = output format, `-o` = output file.

### 7.3 Decompiling: from DTB back to text

`dtc` works in both directions, which is very useful when you only have the binary:

```bash
dtc -I dtb -O dts -o readable.dts myboard.dtb        # a .dtb file → text
dtc -I fs  -O dts -o live.dts /proc/device-tree      # the tree the running kernel has → text
fdtdump myboard.dtb                                  # dump the raw blob, with its header
```

The decompiled text has no comments, no labels (unless the blob was built with `-@`) and plain numbers instead of macro names, but it is the **exact** tree the kernel uses.

### 7.4 Warnings worth reading

`dtc` checks a lot and prints warnings. Don't ignore these:

| Warning | Meaning |
| --- | --- |
| `unit_address_vs_reg` | The `@address` in the name doesn't match `reg`, or one is missing |
| `reg_format` | `reg` has the wrong number of values for the parent's `#address-cells` / `#size-cells` |
| `Reference to non-existent node or label` | A `&label` doesn't exist: a typo, or a missing `#include` (this one is an error) |
| `duplicate_node_names` | Two nodes with the same name under one parent |

---

## 8. Inside a DTB

![Inside a .dtb file in the Flattened Device Tree format, from the start of the file to the end: the header with the magic number 0xd00dfeed, total size, offsets of the other blocks and version 17; the memory reservation block listing RAM areas the kernel must not use; the structure block, the tree itself as BEGIN_NODE, PROP and END_NODE tokens; and the strings block with every property name stored once, which PROP tokens point to; all numbers are big-endian 32-bit values; a binary format is small, needs no text parser, and the bootloader can read and patch it with the tiny libfdt library](images/dtb_layout.svg)

The DTB format is called the **FDT** (Flattened Device Tree): "flattened" because the tree is written out as one flat list. From the start of the file:

1. **Header.** Fixed-size, and always first. Its main fields:
   - **`magic`** = `0xd00dfeed`. Tools and bootloaders check it to confirm "this is a DTB".
   - **`totalsize`**: the size of the whole blob.
   - **Offsets** of the three blocks below.
   - **`version`** = 17, the current format version.
2. **Memory reservation block.** A list of (address, size) pairs of RAM the kernel must not use, for example where firmware lives. It ends with a (0, 0) pair.
3. **Structure block.** The tree itself, as a sequence of tokens:
   - `FDT_BEGIN_NODE` + the node name: a node starts
   - `FDT_PROP` + the value length + a pointer to the name + the value: one property
   - `FDT_END_NODE`: a node ends
   - `FDT_END`: the tree ends
4. **Strings block.** Every property name (`compatible`, `reg`, `status` ...) stored **once**. Properties point into it instead of repeating the name, which saves space.

**All numbers are big-endian** (the most significant byte first), even on little-endian CPUs such as Arm. The kernel converts them when it reads them.

**Why a binary format?** The bootloader and the early kernel need to read the tree **before** they have memory allocation or a text parser. The flat format can be read, searched and patched in place with a tiny C library, **libfdt**, which both U-Boot and Linux use.

---

## 9. How the DTB reaches the kernel

### 9.1 What U-Boot does, step by step

1. **Choose the file.** U-Boot's `fdtfile` setting holds the DTB's file name, for example `freescale/myboard.dtb`.
2. **Load it into RAM**, at the address in `fdt_addr_r`:

   ```text
   load mmc 0:1 ${fdt_addr_r} ${fdtfile}
   ```

3. **Apply overlays**, if any ([section 11](#11-overlays-dtbo)).
4. **Patch it (fix-ups).** Just before starting Linux, U-Boot edits the tree with things only it knows:
   - the **real RAM size** into the `memory` node
   - the **kernel command line** (`bootargs`) into `chosen`
   - the **MAC address** of each Ethernet port, from its settings or from a fuse
   - where the **initramfs** (initial RAM filesystem) was loaded, if one was loaded
5. **Start the kernel** with the DTB's address:

   ```text
   booti ${kernel_addr_r} - ${fdt_addr_r}     # 64-bit Arm; "-" means "no initramfs"
   bootz ${kernel_addr_r} - ${fdt_addr_r}     # 32-bit Arm (zImage)
   ```

### 9.2 How the address is handed over

The kernel receives the DTB's address in a **CPU register**, as agreed in each architecture's boot rules:

| Architecture | Register that holds the DTB address |
| --- | --- |
| 32-bit Arm | `r2` |
| 64-bit Arm | `x0` |
| RISC-V | `a1` |

### 9.3 Useful U-Boot commands

```text
fdt addr ${fdt_addr_r}     # tell the fdt commands where the tree is
fdt print /chosen          # print one node
fdt list /soc              # list the children of a node
fdt set /chosen bootargs "console=ttymxc1,115200"   # change a property
fdt resize 8192            # add free space (needed before applying overlays)
```

### 9.4 Other ways to ship the DTB

- **A FIT image** (Flattened Image Tree): one U-Boot file that holds the kernel, several DTBs and overlays, each with a hash or signature. It is used with **secure boot**, because the DTB is signed together with the kernel (see [Bootloader.md](Bootloader.md)).
- **A DTB built into U-Boot itself.** U-Boot uses its own device tree for its own drivers. It can pass that same tree on to Linux.
- **An appended DTB** (older 32-bit Arm): the DTB is glued to the end of the `zImage`, for bootloaders that don't know about device trees.

---

## 10. How the kernel uses the DTB

![How the kernel matches a device tree node to a driver: the kernel reads the .dtb at boot and builds a tree of device_node structures in RAM; for each enabled node on a bus, the bus creates a device; the tmp102 driver registers with a list of compatible strings it supports; the bus compares the node's compatible strings with each driver's list; when they match it calls the driver's probe function; probe reads reg, interrupts and clocks with the of_ and device_property_ functions; the device appears in /dev and /sys, and with no match there is no probe, often with no error message](images/device_tree_driver_match.svg)

### 10.1 From blob to devices, step by step

1. **Unflatten.** Early in boot the kernel reads the DTB and builds a tree of `struct device_node` structures in RAM (`unflatten_device_tree()`). After this, the blob itself isn't needed.
2. **Create devices.** For every node with `status = "okay"`:
   - nodes on the SoC's internal bus become **platform devices**
   - children of an I2C node become **I2C devices**, created by the I2C core
   - children of a SPI node become **SPI devices**, and so on
3. **Drivers register** with a table of `compatible` strings they support.
4. **Matching.** The bus compares each device's `compatible` list with each driver's table.
5. **Probe.** On a match, the bus calls the driver's `probe()` function. The driver reads what it needs from the node and starts the hardware.
6. **The device appears** in `/dev`, `/sys` or as a network interface.

### 10.2 The driver side

A driver says which nodes it handles with an **`of_device_id` table**, a list of the `compatible` strings it supports, linked from the driver structure through `.of_match_table`. A complete small driver is in [Example 7](#example-7-your-own-node-read-by-your-own-driver).

Inside `probe()`, the driver reads the node's properties with kernel helper functions:

| Property in the tree | Driver code that reads it |
| --- | --- |
| `reg` (registers) | `base = devm_platform_ioremap_resource(pdev, 0);` |
| `interrupts` | `irq = platform_get_irq(pdev, 0);` |
| `clocks` | `clk = devm_clk_get(dev, NULL);` |
| `vcc-supply` | `reg = devm_regulator_get(dev, "vcc");` |
| `reset-gpios` | `gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);` |
| any number | `device_property_read_u32(dev, "clock-frequency", &freq);` |
| a flag | `device_property_read_bool(dev, "wakeup-source");` |

The `device_property_*` functions work with both the device tree and ACPI, so one driver can run on Arm boards and on PCs. The older `of_property_read_*` functions work only with the device tree.

The driver never contains the board's addresses or pin numbers. **All of that comes from the tree**, which is why one driver works on every board. For the full driver model, see [Linux_device_drivers.md](Linux_device_drivers.md).

### 10.3 When there is no match

If no driver matches, **nothing happens and usually nothing is printed**. The three usual causes:

1. The driver isn't built: its `CONFIG_...` option is off in the kernel configuration.
2. A typo in `compatible`: one wrong letter and it doesn't match.
3. The node, or its **parent**, has `status = "disabled"`.

---

## 11. Overlays (DTBO)

### 11.1 What an overlay is

1. An **overlay** is a small device tree that **changes** an existing one: it adds nodes, changes properties or enables devices.
2. It is compiled to a **`.dtbo`** and applied on top of the base `.dtb`, usually by the bootloader, **without rebuilding the base**.
3. It's used when the hardware changes but the main board doesn't:
   - an add-on board: a Raspberry Pi **HAT** (Hardware Attached on Top), a BeagleBone "cape"
   - a different display or camera on the same board
   - one base `.dtb` for several product variants

### 11.2 Writing one

An overlay that adds an **RTC** (Real-Time Clock) chip on I2C bus 1:

```dts
/dts-v1/;
/plugin/;                          /* says: this is an overlay, not a full tree */

&i2c1 {                            /* the node in the BASE tree to change */
    #address-cells = <1>;
    #size-cells = <0>;
    status = "okay";

    rtc@68 {
        compatible = "dallas,ds1307";
        reg = <0x68>;
    };
};
```

### 11.3 Building and applying it

1. **Compile both files with `-@`.** It keeps the label names (the **symbols**) in the blob. The overlay needs them to find `&i2c1` in the base.

   ```bash
   dtc -@ -I dts -O dtb -o rtc-overlay.dtbo rtc-overlay.dts
   make ARCH=arm64 DTC_FLAGS=-@ dtbs        # the base must also have symbols
   ```

2. **Apply it in U-Boot**, before starting the kernel:

   ```text
   fdt addr ${fdt_addr_r}
   fdt resize 8192                                   # room for the new nodes
   load mmc 0:1 ${fdtoverlay_addr_r} rtc-overlay.dtbo
   fdt apply ${fdtoverlay_addr_r}
   ```

3. **On a Raspberry Pi**, the firmware does it for you. One line in `config.txt`:

   ```text
   dtoverlay=i2c-rtc,ds1307
   ```

Applying overlays **while Linux is running** (through configfs) isn't part of the standard kernel. Some vendor kernels add it, but most products apply overlays in the bootloader.

---

## 12. Bindings: the rulebook

1. A **binding** is the document that says which properties a node with a given `compatible` **must** and **may** have, and what their values mean.
2. Bindings live in the kernel source in `Documentation/devicetree/bindings/`. For example, `Documentation/devicetree/bindings/hwmon/ti,tmp102.yaml`.
3. Modern bindings are written in **YAML** (YAML Ain't Markup Language) as a **schema** that a tool can check automatically. Older ones are plain `.txt` files.
4. **Before writing a node, read its binding.** It tells you the exact `compatible` string, the required properties and a working example.

Two build targets check the files for you:

```bash
make dt_binding_check                              # checks the binding YAML files themselves
make ARCH=arm64 CHECK_DTBS=y freescale/myboard.dtb # checks your .dts against the bindings
```

`CHECK_DTBS=y` catches a missing required property or a wrong value **at build time**, instead of a driver silently failing at boot.

The general format rules (node names, standard properties, the DTB layout) are in the **DTSpec** (Devicetree Specification), published at devicetree.org.

---

## 13. Debugging a device tree

### 13.1 Commands on the running board

```bash
ls /proc/device-tree/                           # the tree the kernel actually received
cat /proc/device-tree/model                     # which board the kernel thinks it is
dtc -I fs -O dts /proc/device-tree > live.dts   # the whole live tree as text
ls /sys/bus/platform/devices/                   # devices created from the tree
ls /sys/bus/platform/drivers/<driver>/          # devices a driver has bound to
cat /sys/kernel/debug/devices_deferred          # devices waiting on something (needs debugfs)
dmesg | grep -i -E "of:|dt|probe"               # device tree and probe messages
```

`/proc/device-tree` is a link to `/sys/firmware/devicetree/base`. Each node is a folder and each property is a file.

**The first check, always:** decompile the live tree and look for your node. If your change isn't there, the kernel is using a **different `.dtb`** than the one you edited.

### 13.2 A method, step by step

1. **Is my node in the live tree?** If not, the wrong `.dtb` was loaded. Check `fdtfile` in U-Boot and the file in `/boot`.
2. **Is it `okay`?** Check the node's `status`, and its parent's.
3. **Is the driver built?** Check `zcat /proc/config.gz | grep <OPTION>`, or look for the module in `lsmod`.
4. **Does `compatible` match the driver exactly?** Compare with the `of_device_id` table or the binding.
5. **Did the driver probe?** Look in `dmesg` for errors, and check `devices_deferred`.
6. **Is the hardware set up?** Pins (`pinctrl`), power (`*-supply`), clocks and reset GPIOs. Compare with the schematic.

### 13.3 Common errors

| Symptom | What it means | Usual cause | Fix |
| --- | --- | --- | --- |
| `dtc`: `syntax error` | The text doesn't parse | A missing `;`, `}` or quote | Look at the line `dtc` names, and the line before it |
| `dtc`: `Reference to non-existent node or label` | A `&label` has no target | A typo, or a missing `#include` | Check the label name in the `.dtsi` |
| Device missing, **no error at all** | No driver matched, or the node was skipped | A `compatible` typo, `status = "disabled"`, or the driver isn't built | Follow the method above |
| Device in `devices_deferred` | The driver is waiting for something | A clock, regulator, GPIO or PHY it needs never appeared | Enable that provider's node and driver |
| `probe ... failed with error -22` | `-EINVAL`, invalid argument: the driver rejected the node | A missing or wrong property | Compare with the binding |
| `pin ... already requested` | Two nodes use the same pin | A pin given to two devices | Give each pin to one device only |
| Kernel hangs after `Starting kernel ...` | The kernel can't print or can't find its hardware | Wrong DTB for this board, or wrong `stdout-path` / `console=` | Check `fdtfile`; add `earlycon` to `bootargs` |
| Only part of the RAM is used | The `memory` node is wrong | U-Boot didn't fix it up, or the `reg` value is wrong | Check `cat /proc/meminfo` and the `memory` node |
| U-Boot `fdt apply`: `FDT_ERR_NOSPACE` | No room left in the blob | `fdt resize` wasn't run | Run `fdt resize` before `fdt apply` |
| U-Boot `fdt apply`: `FDT_ERR_NOTFOUND` | The overlay can't find its target | The base was built without `-@` | Rebuild the base with `DTC_FLAGS=-@` |

---

## 14. Simple code examples

Each example is small and complete, and follows the same three steps:

1. **The device tree code** to add to your board's `.dts`.
2. **What happens** at boot.
3. **How to check it** on the running board.

> **Before you start:** labels such as `&gpio1`, `&i2c1`, `&uart3` and `&ecspi1` come from your SoC's `.dtsi` (these are i.MX names). Other chips use other names, for example `&i2c0` or `&spi1`, so look them up in your SoC's `.dtsi`. After each change, rebuild the `.dtb`, copy it to the board, and reboot.

### Example 1: Blink an LED

The board has an LED on GPIO1, pin 13. No driver code is needed: Linux already has a generic LED driver.

```dts
#include <dt-bindings/gpio/gpio.h>

/ {
    leds {
        compatible = "gpio-leds";                  /* use the generic GPIO LED driver */

        led-status {
            label = "status";                      /* its name in /sys/class/leds/ */
            gpios = <&gpio1 13 GPIO_ACTIVE_HIGH>;  /* GPIO1, pin 13; HIGH = LED on */
            linux,default-trigger = "heartbeat";   /* blink like a heartbeat */
        };
    };
};
```

**What happens:** the `gpio-leds` driver matches the `compatible`, takes GPIO1 pin 13, and creates `/sys/class/leds/status/`. The `heartbeat` trigger makes the LED blink as long as Linux runs.

**Check it:**

```bash
ls /sys/class/leds/                                  # "status" is listed
echo none > /sys/class/leds/status/trigger           # stop the heartbeat
echo 1    > /sys/class/leds/status/brightness        # LED on
echo 0    > /sys/class/leds/status/brightness        # LED off
```

### Example 2: A push button

A button on GPIO1, pin 7. Pressing it connects the pin to ground, so it is **active low**.

```dts
#include <dt-bindings/gpio/gpio.h>
#include <dt-bindings/input/input.h>              /* defines KEY_ENTER and other key codes */

/ {
    gpio-keys {
        compatible = "gpio-keys";                  /* the generic button driver */

        button-user {
            label = "User button";
            gpios = <&gpio1 7 GPIO_ACTIVE_LOW>;    /* pressed = pin LOW */
            linux,code = <KEY_ENTER>;              /* acts like the Enter key */
            debounce-interval = <20>;              /* ignore contact bounce for 20 ms */
        };
    };
};
```

**What happens:** the `gpio-keys` driver turns the button into an **input device**, like a keyboard with one key.

**Check it:**

```bash
cat /proc/bus/input/devices      # find "gpio-keys" and its eventN number
evtest /dev/input/event0         # press the button: KEY_ENTER appears
```

### Example 3: Switch on a UART

The SoC has a third UART, but the `.dtsi` marks it `disabled`. The board uses it for an external module, such as a GPS receiver.

```dts
&uart3 {
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_uart3>;    /* which pins carry TX and RX (defined under &iomuxc) */
    status = "okay";                 /* was "disabled" in the .dtsi */
};
```

**What happens:** the node is no longer skipped, so the UART driver probes it and creates a serial port.

**Check it:**

```bash
ls /dev/ttymxc*                  # on i.MX, uart3 appears as /dev/ttymxc2 (numbering starts at 0)
dmesg | grep -i 30880000         # the probe message, with the UART's register address
```

### Example 4: Add an I2C temperature sensor

A TMP102 sensor on I2C bus 1, at address 0x48.

```dts
&i2c1 {
    clock-frequency = <100000>;          /* 100 kHz, standard I2C speed */
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_i2c1>;
    status = "okay";

    temperature-sensor@48 {
        compatible = "ti,tmp102";        /* must match the driver exactly */
        reg = <0x48>;                    /* the sensor's I2C address */
    };
};
```

**What happens:** the I2C core creates a device at address 0x48, the `tmp102` driver matches it, and the temperature appears through **hwmon** (the kernel's hardware monitoring framework).

**Check it:**

```bash
i2cdetect -y 1                                # "48" (or "UU" once the driver owns it)
cat /sys/class/hwmon/hwmon*/name              # "tmp102"
cat /sys/class/hwmon/hwmon0/temp1_input       # e.g. 24500 = 24.5 °C (in millidegrees)
```

If `i2cdetect` shows the chip but there is no `hwmon` entry, the driver isn't built: enable `CONFIG_SENSORS_TMP102` in the kernel configuration.

### Example 5: Add an SPI flash chip

A NOR flash chip on SPI bus 1, chip select 0.

```dts
&ecspi1 {
    pinctrl-names = "default";
    pinctrl-0 = <&pinctrl_ecspi1>;
    cs-gpios = <&gpio5 9 GPIO_ACTIVE_LOW>;   /* the chip-select line */
    status = "okay";

    flash@0 {
        compatible = "jedec,spi-nor";         /* generic driver for standard SPI NOR flash */
        reg = <0>;                            /* chip select 0 (not an address) */
        spi-max-frequency = <20000000>;       /* 20 MHz */
    };
};
```

**What happens:** the `spi-nor` driver reads the chip's ID, detects its size, and creates an **MTD** (Memory Technology Device) partition, the Linux interface for raw flash.

**Check it:**

```bash
cat /proc/mtd                     # e.g. mtd0: 01000000 00010000 "spi0.0" (16 MB)
dmesg | grep spi-nor              # the detected chip name and size
```

### Example 6: Turn a device off

The reference board has an Ethernet port, but your board doesn't. Two ways to remove it:

```dts
/* Way 1: keep the node, but switch it off */
&fec1 {
    status = "disabled";
};

/* Way 2: delete the node completely */
/delete-node/ &fec1;
```

**Which to use:** `status = "disabled"` is the normal way. It's easy to read and easy to switch back. `/delete-node/` is for removing something that would get in the way, such as a node that claims pins your board uses for something else.

**Check it:**

```bash
dtc -I fs -O dts /proc/device-tree 2>/dev/null | grep -A3 "ethernet@"   # way 1: status = "disabled"; way 2: not found
ip link                                                                  # no eth0
```

### Example 7: Your own node, read by your own driver

This example shows the **whole path**: a node you invent, and a small driver that reads its properties.

**Step 1: the device tree node.** Your own properties get your company's name as a prefix, as the binding rules require.

```dts
#include <dt-bindings/gpio/gpio.h>

/ {
    hello {
        compatible = "mycompany,hello";            /* our own compatible string */
        label = "my-first-node";                   /* a string property */
        mycompany,blink-rate-ms = <500>;           /* a number property */
        led-gpios = <&gpio1 13 GPIO_ACTIVE_HIGH>;  /* a GPIO, named "led" */
    };
};
```

> This node uses the same pin as Example 1. Don't add both: a pin can belong to only one device.

**Step 2: the driver** (`hello.c`). It matches the node, reads the three properties, and turns the LED on.

```c
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/gpio/consumer.h>

static int hello_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    const char *label = "unnamed";
    u32 rate = 1000;                              /* default if the property is missing */
    struct gpio_desc *led;

    /* 1. Read a string and a number from the node */
    device_property_read_string(dev, "label", &label);
    device_property_read_u32(dev, "mycompany,blink-rate-ms", &rate);

    /* 2. Get the GPIO from "led-gpios" (the "-gpios" part is added by the kernel) */
    led = devm_gpiod_get(dev, "led", GPIOD_OUT_LOW);
    if (IS_ERR(led))
        return dev_err_probe(dev, PTR_ERR(led), "no led-gpios in the device tree\n");

    /* 3. Use them */
    gpiod_set_value(led, 1);
    dev_info(dev, "label=%s, rate=%u ms, LED on\n", label, rate);
    return 0;
}

/* The link to the device tree: which compatible strings this driver handles */
static const struct of_device_id hello_of_match[] = {
    { .compatible = "mycompany,hello" },
    { }                                           /* end of the list */
};
MODULE_DEVICE_TABLE(of, hello_of_match);

static struct platform_driver hello_driver = {
    .probe  = hello_probe,
    .driver = {
        .name           = "hello",
        .of_match_table = hello_of_match,
    },
};
module_platform_driver(hello_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Reads a device tree node");
```

**What happens, step by step:**

1. At boot the kernel finds the `hello` node directly under the root, and creates a **platform device** for it.
2. When `hello.ko` is loaded, its `of_match_table` says `"mycompany,hello"`, which matches the node.
3. The kernel calls `hello_probe()`.
4. The driver reads `label`, `mycompany,blink-rate-ms` and `led-gpios`, and turns the LED on.

**Check it:**

```bash
insmod hello.ko
dmesg | tail -1                                   # hello hello: label=my-first-node, rate=500 ms, LED on
cat /proc/device-tree/hello/label                 # my-first-node
hexdump -C /proc/device-tree/hello/mycompany,blink-rate-ms
                                                  # 00 00 01 f4  = 500, stored big-endian (section 8)
```

**Try breaking it**, to learn the common errors:

| Change | What you'll see |
| --- | --- |
| Misspell the `compatible` in the node | Nothing at all: no probe, no error ([section 10.3](#103-when-there-is-no-match)) |
| Remove `led-gpios` | `no led-gpios in the device tree`, and probe fails |
| Set `status = "disabled"` | Nothing: the node is skipped, so there is no device to match |
| Remove `mycompany,blink-rate-ms` | The driver still works, using its default of 1000 ms |

### Example 8: The same LED as an overlay

Instead of editing the board's `.dts`, add the LED from Example 1 with an overlay ([section 11](#11-overlays-dtbo)).

```dts
/dts-v1/;
/plugin/;                                          /* this is an overlay */

#include <dt-bindings/gpio/gpio.h>

&{/} {                                             /* "&{/}" means: the root node of the base tree */
    leds {
        compatible = "gpio-leds";

        led-extra {
            label = "extra";
            gpios = <&gpio1 13 GPIO_ACTIVE_HIGH>;
            linux,default-trigger = "heartbeat";
        };
    };
};
```

**Build and apply it** with the `cpp`, `dtc -@` and U-Boot `fdt apply` steps from [section 11.3](#113-building-and-applying-it). Because this overlay uses `#include`, run `cpp` on it before `dtc`, as in [section 7.2](#72-by-hand).

**Check it:** after boot, `/sys/class/leds/extra/` exists, although the board's `.dtb` was never rebuilt.

---

## 15. Interview quick answers

**What is a device tree?**
A data structure that describes the board's hardware (devices, addresses, interrupts, clocks, pins, power) for the kernel. It keeps the hardware description out of the kernel code, so one kernel image can boot many boards.

**What is the difference between DTS, DTSI, DTB and DTBO?**
DTS is the board's source text. DTSI is a shared include file, usually for the SoC. DTB is the compiled binary that the bootloader passes to the kernel. DTBO is a compiled overlay that patches a DTB at boot.

**How does a DTS become a DTB?**
The C preprocessor expands `#include` and macros, then `dtc` (the Device Tree Compiler) compiles the text into the binary. In the kernel, `make dtbs` does both.

**How does the kernel get the DTB?**
The bootloader loads it into RAM, fixes it up (memory size, `bootargs`, MAC addresses) and passes its address in a register: `x0` on 64-bit Arm, `r2` on 32-bit Arm.

**How is a driver matched to a node?**
Through the `compatible` string. The driver lists the strings it supports in its `of_match_table`. When a node's string matches, the bus calls the driver's `probe()`.

**My device doesn't show up and there's no error. What do you check?**
First, whether the node is in `/proc/device-tree` (was the right DTB loaded?). Then its `status` and its parent's, whether the driver is enabled in the kernel configuration, whether `compatible` is spelled exactly right, and `devices_deferred` for a missing clock, regulator or GPIO.

**What do `#address-cells` and `#size-cells` do?**
They are set in a parent node and say how many 32-bit numbers the children use for an address and for a size in `reg`. An I2C bus uses 1 and 0, because a child has only an address.

**What is a phandle?**
A unique number `dtc` gives a node, so other nodes can point to it. In the source you write `&label`, and `dtc` replaces it with the phandle.

**What is an overlay, and why use one?**
A small compiled patch (`.dtbo`) applied on top of the base DTB, usually by the bootloader. It describes add-on hardware, like a HAT or a display, without rebuilding the base tree. Both files must be built with `-@`.

**Why is the DTB binary and not text?**
The bootloader and early kernel must read it before they have a text parser or memory allocation. The flat format can be read and patched in place with the small libfdt library.

**Device tree or ACPI?**
Both describe hardware the OS can't discover. The device tree is used by embedded Arm, RISC-V and PowerPC. ACPI is used by x86 PCs and Arm servers, and can also contain code the OS runs, not just data.
