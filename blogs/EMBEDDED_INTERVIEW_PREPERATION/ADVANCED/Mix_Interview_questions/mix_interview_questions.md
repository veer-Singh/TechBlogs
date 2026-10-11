# Mixed Embedded Interview Questions

## Contents

| # | Topic | Questions |
| --- | --- | --- |
| 1 | [I2C, SPI and GPIO](#1-i2c-spi-and-gpio) | Q1-Q5, Q7-Q9 |
| 2 | [BSP, HAL and RTOS layers](#2-bsp-hal-and-rtos-layers) | Q6 |
| 3 | [Interrupts and Linux drivers](#3-interrupts-and-linux-drivers) | Q10-Q14 |
| 4 | [Synchronization](#4-synchronization) | Q15-Q18 |
| 5 | [Memory: virtual memory, TLB and cache](#5-memory-virtual-memory-tlb-and-cache) | Q19-Q25 |
| 6 | [Debugging](#6-debugging) | Q26-Q27 |
| 7 | [BLE](#7-ble) | Q28-Q30 |
| 8 | [Coding and C memory](#8-coding-and-c-memory) | Q31-Q37 |
| 9 | [SPI, EEPROM and driver design](#9-spi-eeprom-and-driver-design) | Q38-Q40 |
| 10 | [C programming](#10-c-programming) | Q41-Q44 |
| 11 | [Bit manipulation](#11-bit-manipulation) | Q45-Q47 |
| 12 | [Debugging basics](#12-debugging-basics) | Q48-Q49 |
| 13 | [Bit manipulation patterns to remember](#13-bit-manipulation-patterns-to-remember) | – |
| 14 | [I2C in depth](#14-i2c-in-depth) | Q50-Q55 |
| 15 | [I2C speed](#15-i2c-speed) | Q56-Q58 |
| 16 | [SPI modes and choosing an interface](#16-spi-modes-and-choosing-an-interface) | Q59-Q60 |
| 17 | [1-Wire protocol](#17-1-wire-protocol) | Q61-Q63 |
| 18 | [USB](#18-usb) | Q64-Q67 |
| 19 | [Register-level GPIO driver (no HAL)](#19-register-level-gpio-driver-no-hal) | Q68-Q71 |
| 20 | [C strings: array vs pointer](#20-c-strings-array-vs-pointer) | Q72 |
| 21 | [RTOS, interrupts and context switching](#21-rtos-interrupts-and-context-switching) | Q73-Q78 |
| 22 | [FreeRTOS heap](#22-freertos-heap) | Q79 |
| 23 | [BLE in practice](#23-ble-in-practice) | Q80-Q83 |
| 24 | [Firmware update and bootloader](#24-firmware-update-and-bootloader) | Q84-Q87 |
| 25 | [Networking: OSPF](#25-networking-ospf) | Q88-Q89 |
| 27 | [Linux I2C stack: device tree to application](#27-linux-i2c-stack-device-tree-to-application) | Q90-Q95 |
| 28 | [Embedded Linux boot and STM32 bring-up debugging](#28-embedded-linux-boot-and-stm32-bring-up-debugging) | Q96-Q98 |
| 29 | [C strings, arrays and pointers](#29-c-strings-arrays-and-pointers) | Q99-Q101 |
| 30 | [C code review: strings and returning buffers](#30-c-code-review-strings-and-returning-buffers) | Q102-Q105 |
| 31 | [Bit macros and bitwise arithmetic](#31-bit-macros-and-bitwise-arithmetic) | Q106-Q107 |
| 32 | [C++: copy constructor vs copy assignment](#32-c-copy-constructor-vs-copy-assignment) | Q108 |
| 33 | [Multithreading: even and odd threads](#33-multithreading-even-and-odd-threads) | Q109-Q110 |
| 34 | [Quick revision sheet](#34-quick-revision-sheet) | – |

## Abbreviations

| Short | Full form | Short | Full form | Short | Full form |
| --- | --- | --- | --- | --- | --- |
| **ACK / NACK** | Acknowledge / Negative Acknowledge | **GAP** | Generic Access Profile | **OTA** | Over The Air |
| **ADC** | Analog-to-Digital Converter | **GATT** | Generic Attribute Profile | **OTG** | USB On-The-Go |
| **AF** | Alternate Function (pin mux) | **GDB** | GNU Debugger | **PHY** | Physical layer |
| **ATT** | Attribute Protocol | **GIC** | Generic Interrupt Controller (Arm) | **RDSR / WREN** | Read Status Register / Write Enable (SPI memory) |
| **BCD** | Binary-Coded Decimal | **GPIO** | General-Purpose Input/Output | **RMW** | Read-Modify-Write |
| **BLE** | Bluetooth Low Energy | **HAL** | Hardware Abstraction Layer | **ROM** | Read-Only Memory |
| **BSP** | Board Support Package | **HCI** | Host Controller Interface | **RTC** | Real-Time Clock |
| **CCCD** | Client Characteristic Configuration Descriptor | **I2C** | Inter-Integrated Circuit | **RTOS** | Real-Time Operating System |
| **CDC / HID** | Communication Device Class / Human Interface Device (USB) | **IMU** | Inertial Measurement Unit | **SCL / SDA** | Serial Clock / Serial Data (I2C) |
| **CPHA / CPOL** | Clock Phase / Clock Polarity (SPI) | **IRQ / ISR** | Interrupt Request / Interrupt Service Routine | **SCLK / MOSI / MISO** | SPI clock / Master Out Slave In / Master In Slave Out |
| **CPU** | Central Processing Unit | **JTAG / SWD** | Joint Test Action Group / Serial Wire Debug | **SMP** | Security Manager Protocol (BLE) |
| **CRC** | Cyclic Redundancy Check | **L2CAP** | Logical Link Control and Adaptation Protocol | **SoC** | System on Chip |
| **CS** | Chip Select | **LR / PC / SP** | Link Register / Program Counter / Stack Pointer | **SPI** | Serial Peripheral Interface |
| **DFU** | Device Firmware Upgrade (USB) | **LSA** | Link-State Advertisement (OSPF) | **TCB** | Task Control Block |
| **DMA** | Direct Memory Access | **LSB / MSB** | Least / Most Significant Bit | **TLB** | Translation Lookaside Buffer |
| **DR** | Designated Router (OSPF) | **MCU** | Microcontroller Unit | **UART** | Universal Asynchronous Receiver-Transmitter |
| **EEPROM** | Electrically Erasable Programmable Read-Only Memory | **MMU** | Memory Management Unit | **USB** | Universal Serial Bus |
| **FPU** | Floating-Point Unit | **MSP / PSP** | Main / Process Stack Pointer | **UUID** | Universally Unique Identifier |
| **NVIC** | Nested Vectored Interrupt Controller | **MTU** | Maximum Transmission Unit | **VID / PID** | Vendor ID / Product ID (USB) |
| **OSPF** | Open Shortest Path First | **PMIC** | Power Management IC | **WIP** | Write In Progress (status bit) |
| **xPSR** | Program Status Register (Cortex-M) | **DTS / DTB** | Device Tree Source / Device Tree Blob | **dtc** | Device Tree Compiler |
| **HSE / HSI** | High-Speed External / Internal oscillator (STM32) | **IIO** | Industrial I/O (Linux subsystem) | **KMP** | Knuth-Morris-Pratt (string search) |
| **NRST** | Reset pin (STM32) | **PID 1** | Process ID 1, the first user process (init) | **POSIX** | Portable Operating System Interface |
| **SMBus** | System Management Bus | **SPL** | Secondary Program Loader | **U-Boot** | Universal Boot Loader |
| **EOI / IAR** | End Of Interrupt / Interrupt Acknowledge Register (GIC) | **GIC_SPI** | Shared Peripheral Interrupt (a GIC interrupt type, not the SPI bus) | **hwirq** | Hardware IRQ number (as the interrupt controller numbers it) |
| **VFS** | Virtual File System (Linux) | **VTOR** | Vector Table Offset Register | **eMMC** | Embedded MultiMediaCard |

---

## 1. I2C, SPI and GPIO

### Q1. How do you configure an I2C or SPI peripheral?

**In simple words:** Before an I2C or SPI device can work, three things must be correct:

- **The pins.** The right MCU pins must be used, and they must be set to the I2C or SPI alternate function.
- **The peripheral settings.** The peripheral clock must be on, and the speed, SPI mode or I2C address must be right.
- **The device protocol.** The commands and register addresses must match the device's datasheet.

Reading a register whose value is known, such as the device ID, checks all three at once.

**Example:** An MPU6050 sensor on I2C1 (PB6/PB7), address 0x68. My first test is reading its WHO_AM_I register (0x75). It should return 0x68. If it does, the wiring and configuration are right.

> "The first thing I open is the **schematic**, not the code. I want to know exactly which pins the device is on, whether there are pull-ups, and if there's a chip select, a reset line or an interrupt line.
>
> Then I go to the MCU's **reference manual**, to see which alternate function those pins need, and to the **sensor's datasheet** for the address, the register map, the init sequence and the timing.
>
> After I configure the peripheral, the very first thing I do is read the **device ID** register, the WHO_AM_I. If the right value comes back, I know the bus is fine and I build the rest of the driver. If it doesn't, I put a logic analyzer on the lines before touching the code again."

| For SPI, check | For I2C, check |
| --- | --- |
| SCLK, MOSI, MISO, CS pins | SDA, SCL pins |
| Clock frequency | Slave address |
| CPOL and CPHA (the SPI mode) | Pull-up resistors |
| MSB or LSB first | Bus speed (100 kHz / 400 kHz) |
| Data width | Register address format (8 or 16 bits) |
| CS timing | START / STOP, ACK / NACK, repeated START |

**Cross-questions:**

1. **Why read the device ID first?**
   "It's the simplest transaction there is, and the answer is fixed and known. If it comes back right, the wiring, address, SPI mode and clock are all correct, and any later problem is in my logic, not the bus."
2. **The ID read returns 0xFF or 0x00. What does that tell you?**
   "On SPI, 0xFF usually means nobody is driving MISO: CS isn't reaching the chip, it has no power, or the mode is wrong. 0x00 can mean MISO is stuck low. On I2C, a NACK on the address means a wrong address or no device, so I scan the bus: `i2cdetect` on Linux, or a loop over all addresses on an MCU."
3. **In which order do you configure things?**
   "Clocks first: the GPIO port clock and the peripheral clock. Then the pins to their alternate function, then the peripheral registers, and enable it last. If the peripheral clock is off, register writes are silently ignored. That's a very common bring-up bug."
4. **Polling, interrupt or DMA?**
   "Polling for a few bytes at init. Interrupts for small, occasional transfers. DMA for big or continuous streams, so the CPU is free while the data moves."

### Q2. What if two I2C slave devices have the same address?

**In simple words:** After START, the master sends an address. Every slave compares it with its own address, and only the slave that matches answers.

So each address must be unique on one bus. If two slaves have the same address, both answer and both drive SDA at the same time, and the data gets corrupted.

**Example:** Two TMP102 temperature sensors: tie ADD0 to GND on one (address 0x48) and to VCC on the other (address 0x49).

> "Then I can't talk to them separately on the same bus, because both will answer.
>
> So first I check the datasheet for **address-select pins**. Most sensors have one or two, so I just strap one device differently and the problem is gone.
>
> If the address is fixed, I have a few options: put the second device on **another I2C controller**, use an **enable pin** to switch one off, or add an **I2C multiplexer** like the TCA9548A. Basically, either I change the address or I isolate the devices electrically."

**Cross-questions:**

1. **How does an I2C multiplexer work?**
   "The TCA9548A has its own address. I write one control byte to it to choose which downstream channel is connected, and then the devices on that channel appear on the main bus. In Linux the i2c-mux driver turns each channel into its own bus, like `/dev/i2c-3`."
2. **What actually happens if two devices with the same address answer?**
   "Both ACK and both drive data. The bus is open-drain, so the result is the AND of the two. The read is silently corrupted, with no error at all, which is why it's dangerous."
3. **The datasheet says the address is 0xD0, but your scan finds 0x68. Why?**
   "Some datasheets give the 8-bit form, which includes the R/W bit: 0x68 shifted left is 0xD0. The STM32 HAL also wants the shifted address, `0x68 << 1`. Mixing these up is a classic reason for a NACK."

### Q3. What is the sequence for reading a register over I2C?

**In simple words:** Reading a register needs two steps:

1. A **write** that tells the slave which register you want. This sets the slave's internal register pointer.
2. A **read** that returns the data from that register.

A **repeated START** joins the two steps into one transaction, so the bus is not released in between.

**Example:** Reading WHO_AM_I from an MPU6050: `START, 0x68+W, 0x75, RESTART, 0x68+R, [0x68 comes back], NACK, STOP`.

Example: slave address `0x68`, register `0x10`.

> "It's actually a write followed by a read. First I have to tell the slave which register I want, so I send START, the slave address with the **write** bit, and the register address. Then, without releasing the bus, I send a **repeated START** and the address again, this time with the **read** bit. The slave sends the data, I NACK the last byte to say 'that's enough', and then STOP."

```text
START → 0x68 + WRITE → ACK → 0x10 (register) → ACK
      → REPEATED START → 0x68 + READ → ACK → data → NACK → STOP
```

**Cross-questions:**

1. **Why a repeated START, and not STOP and then START?**
   "A STOP releases the bus, so another master could take it in between, and some devices reset their internal register pointer on STOP. A repeated START keeps the bus and keeps the pointer."
2. **How do you read several registers in a row?**
   "Most devices **auto-increment** the register address. I keep ACKing each byte and NACK the last one. Some devices need a special bit set in the register address to enable auto-increment, so I check the datasheet."
3. **What if the register address is 16 bits?**
   "Then I send two address bytes, high byte first. Bigger EEPROMs like the 24C256 work this way."
4. **What if the master ACKs the last byte instead of NACKing?**
   "The slave thinks I want more, so it starts driving the next byte. If that bit is 0, it holds SDA low, and I can't generate STOP. The bus is stuck until I recover it with 9 clocks ([Q58](#q58-i2c-is-set-to-400-khz-but-communication-is-unreliable-what-do-you-check))."

### Q4. Can you write to a register of an I2C slave?

**In simple words:** Writing a register is one write transaction. The master sends the slave address, then the register address, and then one or more data bytes.

**Example:** Waking up an MPU6050: write 0x00 to register 0x6B (PWR_MGMT_1): `START, 0x68+W, 0x6B, 0x00, STOP`.

> "Yes, and it's simpler than a read. START, slave address with the write bit, then the register address, then the data, then STOP. The address picks the device, and the first byte after it picks the register inside the device."

Example: slave `0x68`, register `0x10`, data `0x55`:

```text
START → 0x68 + WRITE → ACK → 0x10 → ACK → 0x55 → ACK → STOP
```

**Cross-questions:**

1. **How do you write several registers at once?**
   "Same as the read: one transaction, register address first, then data bytes, and the device auto-increments."
2. **How do you know the write worked?**
   "I read it back. But some registers are write-only or self-clearing, like a reset bit, so for those I check the effect instead, for example a status bit."
3. **How do you write to an I2C EEPROM safely?**
   "After a write, the EEPROM is busy for a few milliseconds and **NACKs its address**. So I do ACK polling: keep sending the address until it ACKs, then continue. And I never cross a page boundary in one write, the same as for SPI in [Q39](#q39-for-an-spi-eeprom-write-how-does-the-frame-depend-on-the-way-you-write)."

### Q5. Where is the register actually written: host or device?

**In simple words:** The register is memory **inside the slave chip**. The master only sends bytes over the bus. The slave's own logic reads those bytes and updates its register.

**Example:** Writing 0x00 to register 0x6B changes the sensor's own power register. Nothing in the MCU's memory changes.

> "In the slave. The host doesn't have any copy of that register. The host just sends the address and the data over the wire, and the slave's own logic decodes it and writes into its own register."

**Cross-questions:**

1. **What if you write a read-only register?**
   "Usually the slave still ACKs, but the write is ignored. So an ACK only means 'I received the byte', not 'I did what you asked'."
2. **Does the driver ever keep its own copy of the slave's registers?**
   "Yes, a **shadow** or cache. It's useful for write-only registers, or to change one bit without an extra I2C read. In Linux, `regmap` does exactly that with its register cache."

### Q7. How do you check the state of a GPIO?

**In simple words:** The real level of a pin is in the **input data register (IDR)**. The hardware updates this register from the pin on every clock cycle.

The output data register (ODR) is different. It only shows the level the software asked the pin to output.

**Example:** A button on PA0 with a pull-up: released reads 1, pressed reads 0.

> "In software I just read the pin's **input data register**, or call `HAL_GPIO_ReadPin()`, which reads the same register. On the board, if it's a static level a **multimeter** is enough, but if I need to see edges or timing I use a **logic analyzer** or an **oscilloscope**."

```c
GPIO_PinState state;

state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);     /* reads bit 5 of the GPIOA input data register (IDR) */

if (state == GPIO_PIN_SET)                       /* explicit comparison, no "if (state)" */
{
    /* pin is HIGH */
}
else
{
    /* pin is LOW */
}
```

**Cross-questions:**

1. **IDR vs ODR: what's the difference?**
   "ODR is what I **asked** the pin to output. IDR is the **actual** level on the pin. If a pin is an output and IDR doesn't match ODR, something external is pulling it, like a short or too much load."
2. **What do you read from a floating input?**
   "Random values, because it picks up noise. Inputs need a pull-up or pull-down, internal or external."
3. **How do you read a button reliably?**
   "With **debouncing**: a button bounces for a few milliseconds. I either sample it twice about 10 to 20 ms apart, or take an interrupt on the first edge and confirm the level with a timer."
4. **How do you get an interrupt from a pin?**
   "On STM32 through **EXTI**: I select the port for that line, choose rising or falling edge, and enable the line in EXTI and in the NVIC."

### Q8. How do you configure a pin from GPIO to I2C SDA/SCL?

**In simple words:** Inside the MCU, each pin is connected to several peripherals through a **multiplexer**. The pin's mode register and alternate-function register choose which peripheral controls the pin.

**Example:** On an STM32F4, PB7 can be GPIO, USART1_RX or I2C1_SDA. Choosing alternate function AF4 connects it to I2C1_SDA.

> "The schematic only tells me which pin is wired to SDA or SCL. It doesn't make the pin an I2C pin. That's the job of the **pin mux**. So I look up the alternate-function table, find the AF number for I2C on that pin, and set the pin to that alternate function instead of plain GPIO.
>
> And for I2C the pin has to be **open-drain**. That part gets missed a lot: the bus only ever pulls the line low, and the pull-up brings it high. Then I check the registers, and look at real traffic on a logic analyzer."

Example on an STM32F4: **PB7 → I2C1_SDA** and **PB6 → I2C1_SCL**, both alternate function **AF4**.

| Setting | Value for I2C |
| --- | --- |
| Mode | Alternate function (AF4 for I2C1) |
| Output type | **Open-drain** (I2C lines are only ever pulled low) |
| Pull-up | External resistors (or internal ones, for slow buses) |
| Voltage level, speed | To match the bus and the slave |

```c
GPIO_InitTypeDef gpio_init = {0};

__HAL_RCC_GPIOB_CLK_ENABLE();                     /* 1. clock for port B first, or the writes are ignored */

gpio_init.Pin       = GPIO_PIN_6 | GPIO_PIN_7;    /* 2. PB6 = I2C1_SCL, PB7 = I2C1_SDA                    */
gpio_init.Mode      = GPIO_MODE_AF_OD;            /*    alternate function, open-drain (I2C only pulls low) */
gpio_init.Pull      = GPIO_NOPULL;                /*    external 4.7 kOhm pull-ups on the board              */
gpio_init.Speed     = GPIO_SPEED_FREQ_HIGH;       /*    fast edges for 400 kHz                              */
gpio_init.Alternate = GPIO_AF4_I2C1;              /*    AF4 connects these pins to I2C1                     */
HAL_GPIO_Init(GPIOB, &gpio_init);
```

**Cross-questions:**

1. **Why open-drain? Why not push-pull?**
   "With push-pull, if one device drives high while another drives low, you get a short circuit. Open-drain makes the bus a **wired-AND**, which is also what makes ACK, clock stretching and arbitration possible."
2. **Are the internal pull-ups enough?**
   "They're around 40 kΩ, which is far too weak for 400 kHz. They're OK for a slow, short bus or a quick test. For a real design I use external 2.2 to 4.7 kΩ."
3. **What happens if you forget the alternate function and leave it as GPIO?**
   "The I2C peripheral isn't connected to the pin at all. The peripheral thinks it's sending, but the scope shows the line sitting idle."
4. **How is pin muxing done on Linux?**
   "With **pinctrl** in the device tree. The I2C controller node points to a pin group that sets the mux for SDA and SCL, as in [Q90](#q90-how-do-you-write-the-device-tree-entry-for-an-i2c-device-for-example-one-using-pin-46)."

### Q9. What is I2C arbitration?

**In simple words:** I2C lines are **open-drain**. A device can only pull a line low. The pull-up resistor is what makes the line high. So if any master drives a 0, the line reads 0.

Each master reads back every bit it sends. If the bit it reads is different from the bit it sent, another master is using the bus.

**Example:** Master A sends address 0x50 (1010000) and master B sends 0x48 (1001000) at the same time. The first two bits match. On the third bit A sends 1, B sends 0, the bus shows 0, so A loses and B continues without any damage.

> "It's needed when there are two or more masters on the same bus and they start at the same time. The trick is that the lines are **open-drain**: anyone can pull a line low, but nobody drives it high. So a **low always wins**.
>
> Each master reads SDA back while it's sending. If I send a 1 but read a 0, I know someone else is talking, so I've **lost arbitration**, and I stop and let the other master finish. The nice part is that the winner never even notices: its data was on the bus the whole time."

```text
Master A sends 1, Master B sends 0  →  bus = 0
Master A reads 0 but sent 1  →  A loses and stops; B continues
```

**Cross-questions:**

1. **The clock comes from two masters too. How does that work?**
   "That's **clock synchronization**. SCL is also wired-AND, so it stays low as long as any master holds it low, and goes high only when all of them release it. So the low period is the longest of the masters', and the high period the shortest. They end up with one common clock, and arbitration happens on SDA."
2. **What if two masters send exactly the same bytes?**
   "Then nobody loses, and both think they succeeded. That's fine, because the bus saw exactly the same data either way."
3. **What must the losing master do?**
   "Stop driving, and **switch to slave mode** right away, because the winner might be addressing it."
4. **Does a single-master system care about arbitration?**
   "Not by design, but I still handle the arbitration-lost flag, because noise or a glitch on SDA can trigger it."

---

## 2. BSP, HAL and RTOS layers

### Q6. What is the difference between BSP, HAL and RTOS?

**In simple words:** These are three different layers:

- The **HAL** is code for the **chip**. It turns the MCU's registers into functions.
- The **BSP** is code for the **board**. It knows which pins and external devices the board has.
- The **RTOS** schedules tasks and provides synchronization. It is optional: BSP and HAL also work without it.

**Example:** `HAL_GPIO_WritePin()` is HAL. `BSP_LED_On(LED_GREEN)` is BSP, because it knows the green LED is on PD12. FreeRTOS tasks run on top of both.

> "They're three different layers, and BSP and HAL don't need an RTOS at all.
>
> The **HAL** hides the chip's registers behind APIs, like 'write this pin' or 'send these bytes on I2C'. The **BSP** is about the **board**: clocks, which pins go where, and the devices soldered on it, like 'the LED is on PA5' or 'the sensor is on I2C1'. The **RTOS** sits on top and gives you tasks, scheduling and synchronization.
>
> So the same HAL can be used on ten boards, each with its own BSP, and the code can run bare-metal or with an RTOS."

```text
Application
     ↓
RTOS / services
     ↓
Drivers
     ↓
HAL / BSP
     ↓
MCU registers
     ↓
Hardware
```

**Cross-questions:**

1. **Give a concrete example of HAL vs BSP on STM32.**
   "`stm32f4xx_hal_gpio.c` is the HAL: it works on any F4 chip. The Discovery board's BSP has `BSP_LED_On(LED3)` and `BSP_ACCELERO_Init()`: it knows that LED3 is on PD13 and which accelerometer is fitted."
2. **What is the BSP in embedded Linux?**
   "Everything to bring Linux up on that board: the U-Boot configuration, the kernel configuration, the **device tree**, board-specific drivers, and often the root filesystem build, like a Yocto layer."
3. **Why keep them separate?**
   "For porting. A new board with the same chip means changing only the BSP. A new chip means changing the HAL. The application doesn't change at all."
4. **Where does a driver for an external sensor go?**
   "Above the HAL. It calls the HAL's I2C functions, and the BSP or the application calls it."

---

## 3. Interrupts and Linux drivers

### Q10. How does an interrupt from a peripheral reach the driver?

**In simple words:** A peripheral cannot call a driver. It can only raise an interrupt signal. Then:

1. The **interrupt controller** turns that signal into a CPU interrupt.
2. The CPU jumps into the kernel's interrupt code.
3. The kernel looks up which function the driver **registered** for that interrupt number, and calls it.

**Example:** The UART receives a byte → the UART interrupt line goes active → GIC interrupt 33 → Linux IRQ 45 → the serial driver's ISR reads the byte.

> "The peripheral never calls the driver directly. It just raises an interrupt line, and from there it's a chain of handovers. I'd explain it in two parts: what's set up at boot, and what happens when the interrupt actually fires.
>
> **At boot**, the device tree says which interrupt the device uses, for example 'GIC interrupt 33'. That's the **hardware IRQ number**. The kernel maps it to its own **Linux IRQ number**, and in my driver's `probe()` I get that number and call `request_irq()`. That stores my handler function in the kernel's table for that IRQ.
>
> **When it fires**, the peripheral raises its line. The **GIC** marks it pending, checks it's enabled and its priority, picks a CPU, and signals that CPU. The CPU stops what it's doing, saves the state, and jumps through its **exception vector** into the kernel's common IRQ entry. The GIC driver then **reads the acknowledge register** to find out which interrupt it was. Linux translates that hardware number to the Linux IRQ number, looks up the handler that was registered, and **calls my ISR**.
>
> In my ISR I read the device's status register, **clear the interrupt in the device**, otherwise it fires again straight away, and return `IRQ_HANDLED`, or `IRQ_WAKE_THREAD` if the heavy work goes to a threaded handler. Then the kernel sends **end-of-interrupt** to the GIC, and the CPU returns to whatever it was doing."

```text
SETUP (once, at boot / probe)
  DTS: interrupts = <GIC_SPI 33 ...>   →  kernel maps hwirq 33 → Linux IRQ e.g. 45
  driver probe(): irq = platform_get_irq(pdev, 0); devm_request_irq(dev, irq, my_isr, ...)
                                       →  my_isr stored in the IRQ descriptor for IRQ 45

RUN TIME (every interrupt)
  1. Peripheral asserts its interrupt line
  2. GIC: pending → enabled? priority? → picks a target CPU → signals IRQ to that CPU
  3. CPU: saves state, jumps through the exception vector → kernel IRQ entry
  4. GIC driver reads the acknowledge register (IAR) → hwirq 33   (now "active" in the GIC)
  5. irq_domain: hwirq 33 → Linux IRQ 45 → its irq_desc
  6. Flow handler calls the registered action → my_isr()
  7. my_isr(): read status, clear the device's interrupt, return IRQ_HANDLED / IRQ_WAKE_THREAD
  8. End-of-interrupt (EOI) written to the GIC → threaded handler runs later if requested
  9. Return from exception → the interrupted code continues (or the scheduler switches)
```

| Step | Who | Job |
| --- | --- | --- |
| Raise the line | **Peripheral** | Signals "I need attention"; keeps it asserted until the driver clears it |
| Route | **GIC** (interrupt controller) | Pending/enable state, priority, which CPU gets it |
| Enter | **CPU** | Exception entry through the vector table into the kernel |
| Identify | **GIC driver** | Reads which hardware IRQ fired (acknowledge), sends EOI at the end |
| Translate | **irq_domain** | Hardware IRQ number → Linux IRQ number |
| Dispatch | **Linux IRQ core** | Finds the `irq_desc` and calls the handler(s) registered with `request_irq()` |
| Handle | **My driver's ISR** | Clears the device's interrupt, does the minimum, defers the rest |

```c
/* Hard IRQ handler: runs with interrupts off, must be short and must not sleep */
static irqreturn_t my_isr(int irq, void *dev_id)
{
    struct my_dev *dev = dev_id;                        /* the pointer given to request_irq() */
    u32 status = readl(dev->base + STATUS_REG);         /* what does the device want?         */

    if (!(status & MY_IRQ_PENDING))
        return IRQ_NONE;                                /* not ours (shared line)             */

    writel(MY_IRQ_PENDING, dev->base + CLEAR_REG);      /* clear it in the device, or it fires again */
    return IRQ_WAKE_THREAD;                             /* heavy work runs in my_thread_fn()  */
}

/* In probe(): get the Linux IRQ number from the device tree and register both handlers */
irq = platform_get_irq(pdev, 0);
ret = devm_request_threaded_irq(&pdev->dev, irq, my_isr, my_thread_fn,
                                IRQF_ONESHOT,           /* keep the line masked until the thread is done */
                                "my-dev", dev);
```

**If they ask: what if the device's interrupt pin goes to a GPIO, not directly to the GIC?**

> "Then there's one more level. The sensor's INT pin goes to a **GPIO controller**, and the GPIO controller's own interrupt goes to the GIC. The GPIO driver is a **chained** interrupt controller: when the GIC calls it, it reads its own status register to see which pin fired, maps that pin to its own Linux IRQ number, and calls the handler registered for that pin. That's why the device tree says `interrupt-parent = <&gpio1>` in that case."

```text
Sensor INT pin → GPIO controller → GIC → CPU → GIC driver → GPIO chained handler → my_isr()
```

**If they ask: how do you check it's working?**

> "`cat /proc/interrupts`. It shows each IRQ, its count per CPU, the controller and the driver name. If my count isn't going up, the interrupt isn't reaching Linux: wrong device tree entry, wrong trigger type, or the device isn't asserting the line, so I put a scope on the pin. If the count goes up like crazy, I'm probably not clearing the interrupt in the device."

**Cross-questions:**

1. **Edge-triggered vs level-triggered: what's the difference?**
   "**Level**: the line stays asserted until the driver clears the cause, so it can't be missed, but if I don't clear it, it fires forever. **Edge**: a single pulse marks the event. It's simpler, but if a second edge comes while the first is still being handled, it can be lost. The trigger type is set in the device tree and must match the device."
2. **Which CPU handles the interrupt on a multicore SoC?**
   "The GIC routes it according to the **IRQ affinity**, which I can see and change in `/proc/irq/<n>/smp_affinity`. For example, I can pin a busy network interrupt to one core."

### Q11. Does the interrupt vector table come into the picture?

**In simple words:** The vector table is an **array of addresses**. It has one entry for each exception or interrupt.

When interrupt N happens, the CPU reads entry N from the table and jumps to the address stored there.

**Example:** USART1 is IRQ 37. Its entry is at offset 0x40 + 37 × 4 = **0xD4**, and that entry holds the address of `USART1_IRQHandler`.

> "Yes, always at the CPU level. The difference is how direct it is.
>
> On a Cortex-M MCU, the vector table points **straight at my ISR**: the I2C interrupt goes to `I2C1_EV_IRQHandler()`. On a Linux processor, the vector only takes you into the kernel's **common** IRQ entry, and from there Linux dispatches to whichever driver registered for that IRQ."

```text
MCU:    I2C peripheral → NVIC → vector table → I2C1_EV_IRQHandler()
Linux:  peripheral → GIC → CPU exception entry → Linux IRQ subsystem → driver handler
```

**Cross-questions:**

1. **Where is the vector table on a Cortex-M, and can it move?**
   "At reset it's at address 0, which on STM32 is aliased to flash at 0x08000000. The **VTOR** register can move it. A bootloader relies on this: the application sets VTOR to its own table."
2. **What's in the first two entries?**
   "Entry 0 is the initial stack pointer, and entry 1 is the Reset_Handler address. Details are in the [bootloader notes](../BOOTLOADER/bootloader.md)."
3. **How does an IRQ number map to the table?**
   "Exception number = IRQ number + 16, because the first 16 entries are system exceptions. The offset in the table is the exception number × 4. So IRQ 0 is at offset 0x40."
4. **And on a Linux arm64 processor?**
   "The vector base is in **VBAR_EL1**, with 16 entries: synchronous, IRQ, FIQ and SError, for 4 different situations. The IRQ entry calls the GIC driver, and from there it's the path in [Q10](#q10-how-does-an-interrupt-from-a-peripheral-reach-the-driver)."

### Q12. What is the structure of a Linux device driver?

**In simple words:** A Linux driver doesn't run on its own. It is a group of functions, and the kernel calls each one at the right time:

- When the kernel finds a device that matches the driver, it calls **`probe()`**. Here the driver sets up the device.
- When the device is removed, or the driver is unloaded, the kernel calls **`remove()`**. Here the driver cleans up.
- When an application uses the device, the kernel calls the driver's **operation functions**, such as `read()`, `write()` and `ioctl()`.

**Example:** The device tree says `compatible = "bosch,bme280"`. The BME280 driver has the same string, so its probe runs, and an IIO device appears under `/sys/bus/iio/devices/`.

> "I'll go in the order things happen. The device is described in the **device tree**, with a `compatible` string. My driver has the same string in its match table, so when the kernel finds a match it calls my **`probe()`**.
>
> In probe I allocate my private data, get my resources (the IRQ, GPIOs, clocks, regulators), initialize the hardware, and then **register with the right subsystem**: input, IIO, a char device, whatever fits. When the device or the module is removed, **`remove()`** undoes all of that. I use the `devm_` functions wherever I can, so most of the clean-up happens automatically."

```text
Device tree → driver match → probe() → allocate private data
→ get GPIO / IRQ / clocks / regulators → initialize the hardware
→ register with a Linux subsystem → runtime operation → remove() / shutdown()
```

A minimal I2C driver:

```c
/* Called when a device tree node with a matching compatible string is found */
static int my_device_probe(struct i2c_client *client)
{
    /* 1. allocate private data (devm_kzalloc)
     * 2. get resources: IRQ, GPIOs, clocks, regulators
     * 3. check the chip ID, initialize the device
     * 4. register with a subsystem (IIO, input, char device ...) */
    return 0;
}

/* Called when the device or the driver goes away: undo probe() */
static void my_device_remove(struct i2c_client *client)
{
    /* unregister from the subsystem; devm_ resources are freed automatically */
}

/* The compatible strings this driver supports */
static const struct of_device_id my_device_of_match[] = {
    { .compatible = "vendor,my-device" },
    { }                                                 /* end of the table */
};
MODULE_DEVICE_TABLE(of, my_device_of_match);            /* lets udev auto-load the module */

static struct i2c_driver my_device_driver = {
    .driver = {
        .name           = "my-device",
        .of_match_table = my_device_of_match,
    },
    .probe  = my_device_probe,
    .remove = my_device_remove,
};
module_i2c_driver(my_device_driver);                    /* registers the driver at module load */
MODULE_LICENSE("GPL");
```

**Cross-questions:**

1. **What do the `devm_` functions do?**
   "They're 'managed' resources: memory, IRQs, clocks and GPIOs get freed **automatically** when probe fails or the device is removed. That removes a whole class of leaks in error paths."
2. **What does `-EPROBE_DEFER` mean?**
   "Probe needs something that isn't ready yet, like a regulator or a GPIO controller whose driver hasn't loaded. The driver returns `-EPROBE_DEFER`, and the kernel retries the probe later."
3. **Platform driver vs I2C driver?**
   "A **platform driver** is for memory-mapped peripherals inside the SoC, which sit on no discoverable bus. An **i2c_driver** is for a device on an I2C bus, and it gets an `i2c_client`."
4. **How does an app talk to a char-device driver?**
   "The driver fills a `file_operations` structure, with `open`, `read`, `write` and `unlocked_ioctl`, and registers it with `cdev_add()` or `misc_register()`. Then the app's system calls on `/dev/mydev` land in those functions."

### Q13. What about interrupt handlers inside a Linux driver?

**In simple words:** The hard IRQ handler runs immediately, and interrupts are disabled while it runs. So it must be short.

Any slow work is moved to a place where the code is allowed to sleep. That is a **threaded IRQ** or a **workqueue**.

**Example:** A touchscreen interrupt: the ISR just acknowledges it, and the threaded handler reads the touch coordinates over I2C.

> "In probe I get the IRQ number from the device tree and register my handler, usually with `devm_request_irq()`. The rule I follow is: the **hard IRQ handler stays tiny**. I acknowledge the interrupt, maybe grab a status value, and that's it. The real work goes to a **threaded IRQ** or a **workqueue**, because there I'm allowed to sleep and take my time."

```text
Hardware IRQ → ISR → clear / acknowledge → workqueue or threaded IRQ → process the data
```

**Cross-questions:**

1. **What are the top half and the bottom half?**
   "The **top half** is the hard IRQ handler: fast, with interrupts off. The **bottom half** is the deferred part: softirq, tasklet, workqueue or threaded IRQ."
2. **Tasklet vs workqueue?**
   "A tasklet runs in softirq context, so it **can't sleep**. A workqueue runs in a kernel thread, in process context, so it **can sleep**. Tasklets are being phased out, so for new code I use workqueues or threaded IRQs."
3. **What's `IRQF_ONESHOT` for?**
   "It keeps the interrupt line **masked until the thread function finishes**. With a level-triggered interrupt and a threaded handler, without it the line would fire again as soon as the hard handler returns, causing an interrupt storm."
4. **What is `IRQF_SHARED`?**
   "Several devices share one line. Every handler gets called, so each must check its own device's status and return `IRQ_NONE` if the interrupt wasn't its own."

### Q14. Can you perform an I2C transfer inside a hard IRQ handler?

**In simple words:** Hard IRQ context is **atomic**. The scheduler cannot run there, so the code must never sleep.

An I2C transfer sleeps while it waits for the controller to finish. That is why it is not allowed in a hard IRQ handler.

**Example:** A touch controller interrupt needs 10 bytes over I2C. At 400 kHz that's about 250 µs of waiting, so the read goes in a threaded IRQ handler.

> "No, and it's a common mistake. An I2C transfer can **sleep**, because it waits for the bus to finish, and you can't sleep in hard IRQ context. The kernel will complain, or worse.
>
> What I do is use `request_threaded_irq()` and do the I2C read in the **thread function**, where sleeping is fine. That's actually the standard pattern for I2C sensors with an interrupt pin."

| Context | I2C transfer? |
| --- | --- |
| Hard IRQ handler | **No**: it may sleep |
| Threaded IRQ / workqueue | **Yes** |

**Cross-questions:**

1. **What can't you do in atomic context?**
   "Anything that might sleep: `mutex_lock()`, `msleep()`, `kmalloc(GFP_KERNEL)`, `copy_to_user()`, and I2C or SPI transfers. In atomic context, memory allocation must use `GFP_ATOMIC`."
2. **What happens if you sleep in an ISR?**
   "The kernel prints **'BUG: scheduling while atomic'**, and the system can hang, because there's no task to switch back to."
3. **How does a threaded IRQ work inside?**
   "The kernel creates a thread called `irq/<n>-<name>`. When the hard handler returns `IRQ_WAKE_THREAD`, the thread is woken. It runs as a real-time `SCHED_FIFO` thread, so it gets the CPU quickly, but it can sleep."

---

## 4. Synchronization

### Q15. Is there a semaphore that can be used inside an ISR?

**In simple words:** Taking a semaphore can **block**: the caller waits until the semaphore is available.

An ISR is not a task, and it must never block. So an ISR can only **give** a semaphore, and it must use the non-blocking `FromISR` version of the function.

**Example:** The UART receive ISR calls `xSemaphoreGiveFromISR()`, and the protocol task that was blocked in `xSemaphoreTake()` wakes up and processes the data.

> "You can **give** a semaphore from an ISR. In FreeRTOS that's `xSemaphoreGiveFromISR()`, and it's the normal way to wake a task. But you can't **take** one in an ISR, because taking may block, and an ISR must never block.
>
> In a Linux hard IRQ handler it's the same idea: for protecting shared data I use a **spinlock** or an atomic operation, not a semaphore."

```c
unsigned long flags;

spin_lock_irqsave(&dev->lock, flags);       /* take the lock and disable local interrupts */
/* short critical section: no sleeping here */
spin_unlock_irqrestore(&dev->lock, flags);  /* release and restore the interrupt state    */
```

**Cross-questions:**

1. **In FreeRTOS, semaphore or task notification from an ISR?**
   "A **task notification** where possible. It's faster and uses no separate object, because the notification lives in the TCB. The limit is one receiving task; if several tasks might wait, I use a semaphore or a queue."
2. **Why can't an ISR use a mutex?**
   "A mutex is about ownership and priority inheritance, and an ISR isn't a task. It can't own anything and can't block, so FreeRTOS doesn't allow it."
3. **What's an atomic operation?**
   "An operation that can't be interrupted halfway, like `atomic_inc()`. On Arm it's built on **LDREX/STREX**, or single instructions on newer cores. It's perfect for counters and flags shared with an ISR."

### Q16. What happens if another CPU tries to acquire a lock held by an interrupt handler on another core?

**In simple words:** A spinlock is a **busy-wait lock**. If a CPU cannot get the lock, it keeps trying in a loop until the other CPU releases it.

This is only acceptable when the lock is held for a very short time.

**Example:** On CPU 0, an ISR updates a ring-buffer index under a spinlock for 1 µs. CPU 1 wants the same lock, so it spins for that 1 µs and then continues.

> "If it's a spinlock, the second CPU just **spins**, busy-waiting, until the first one releases it. It's not a deadlock, it's just wasted cycles. That's exactly why a critical section under a spinlock has to be really short, especially inside an ISR."

```text
Core 0: ISR takes the spinlock → critical section → releases
Core 1: tries the same spinlock → spins → gets it after Core 0 releases → continues
```

**Cross-questions:**

1. **Why spin instead of sleeping?**
   "When the lock is held for less time than two context switches, spinning is cheaper. And in interrupt context you can't sleep at all."
2. **What does a spinlock do on a single-core system?**
   "There's no other CPU to wait for, so it compiles down to **disabling preemption**, and with `irqsave`, disabling interrupts too. There's no actual spinning."
3. **How is a spinlock implemented?**
   "An atomic test-and-set loop, LDREX/STREX on Arm, plus memory barriers so the protected data isn't reordered outside the lock. Linux uses ticket or queued spinlocks, so the waiters get the lock in order."
4. **What if the holder never releases it?**
   "The other CPU spins forever. The kernel's **soft-lockup detector** prints a warning with a backtrace after about 20 seconds."

### Q17. Can the same core be interrupted while holding a lock?

**In simple words:** Suppose code on a CPU holds a spinlock, and then an interrupt **on the same CPU** tries to take the same lock. The ISR spins forever. The code that would release the lock cannot run until the ISR returns, and the ISR never returns.

To prevent this, the code disables local interrupts while it holds the lock.

**Example:** A task holds the lock protecting `rx_count`. The UART ISR fires on the same CPU and also wants that lock: deadlock. Using `spin_lock_irqsave()` in the task prevents it.

> "Yes, and that's the dangerous case. Say my normal code holds a spinlock with plain `spin_lock()`, and an interrupt comes in on the **same CPU**, and the ISR wants the same lock. The ISR spins forever, because the code that holds the lock can't run until the ISR finishes. That's a **deadlock**.
>
> So whenever data is shared with an interrupt handler, the normal code uses **`spin_lock_irqsave()`**, which also disables interrupts on that CPU while it holds the lock."

```text
Normal code takes the spinlock → interrupt on the same CPU → ISR tries the same lock → spins forever
```

```c
unsigned long flags;

spin_lock_irqsave(&lock, flags);            /* also disables interrupts on this CPU */
/* critical section */
spin_unlock_irqrestore(&lock, flags);       /* restores the previous interrupt state */
```

**Cross-questions:**

1. **`spin_lock_irq()` vs `spin_lock_irqsave()`?**
   "`_irq` unconditionally **re-enables** interrupts on unlock. `_irqsave` **restores** whatever state they were in before. So `irqsave` is the safe choice when I don't know whether interrupts were already off."
2. **What about data shared with a softirq or tasklet?**
   "`spin_lock_bh()`, which disables bottom halves while I hold the lock."
3. **What's the equivalent on an MCU with FreeRTOS?**
   "`taskENTER_CRITICAL()` / `taskEXIT_CRITICAL()`, which mask interrupts up to the kernel's priority level, or `__disable_irq()` on bare metal. Kept very short."

### Q18. Difference between a mutex and a semaphore?

**In simple words:** A **mutex** is a lock with an **owner**. The task that takes it must give it back. The RTOS can also raise the owner's priority while it holds the mutex (priority inheritance).

A **semaphore** is a **counter with no owner**. It is used to send signals between tasks or from ISRs, or to count resources.

**Example:** Two tasks printing on one UART share a **mutex**. The UART ISR telling a task "data arrived" uses a **semaphore**. A pool of 5 DMA buffers is a **counting semaphore** that starts at 5.

> "The simplest way I put it: a **mutex is a lock**, a **semaphore is a signal**.
>
> A mutex has an **owner**. The task that locks it must unlock it, and I use it to protect a shared resource like a UART or an I2C bus. A semaphore has no owner. One task or an ISR gives it, another task takes it, so I use it for 'hey, data is ready'. A counting semaphore can also count resources, like free buffers.
>
> And one important thing: a mutex in FreeRTOS has **priority inheritance**, which a semaphore doesn't."

| Mutex | Semaphore |
| --- | --- |
| Protects a shared resource | Signaling or resource counting |
| Has an owner | No owner |
| Binary | Binary or counting |
| Lock / unlock | Take / give |
| Usually supports **priority inheritance** | Not meant for ownership |

**If they ask: can a binary semaphore replace a mutex?**

> "In a simple case it works, but I wouldn't do it. Without priority inheritance you can get **priority inversion**: a low-priority task holds the lock, a medium-priority task keeps preempting it, and the high-priority task waiting for the lock is stuck. That's the classic Mars Pathfinder bug."

**Cross-questions:**

1. **What is a recursive mutex?**
   "One the same task can take several times, for example when a locked function calls another function that takes the same lock. It must be given back the same number of times."
2. **Give a real example of a counting semaphore.**
   "A pool of 5 DMA buffers: the count starts at 5, each user takes one, and returns it when done. When the count is 0, the next task waits."
3. **How do you avoid deadlock?**
   "Always take locks in the **same order** everywhere, hold them as briefly as possible, use timeouts instead of waiting forever, and avoid holding a lock while calling unknown code."
4. **Can an ISR give a mutex?**
   "No, only the task that owns the mutex can give it. From an ISR I give a semaphore or a notification instead."

---

## 5. Memory: virtual memory, TLB and cache

### Q19. What are virtual memory and memory translation?

**In simple words:** Programs use **virtual addresses**. On every memory access, the **MMU** translates the virtual address into a physical address. It uses page tables that the OS sets up.

Each process has its own page tables, so each process has its own private address space.

**Example:** Two processes both use address 0x400000, but the MMU maps them to completely different places in physical RAM, so they can't see or damage each other's data.

> "With virtual memory, every process thinks it has its own private address space. The addresses the CPU uses are **virtual**, and the **MMU** translates each one to a real physical address using **page tables**. That gives each process isolation and protection, and the OS can put pages anywhere in RAM."

```text
CPU → virtual address → MMU (page table) → physical address → RAM
```

**Cross-questions:**

1. **Do microcontrollers have virtual memory?**
   "Cortex-M parts don't have an MMU, so there's no address translation. Many have an **MPU**, which only checks permissions per region, for example making the stack guard region non-accessible."
2. **What is a page fault?**
   "An access to a page that isn't mapped, or isn't allowed. The CPU raises an exception, and the kernel either fixes it, by loading the page or allocating it on first use, or kills the process with SIGSEGV."
3. **What's the usual page size?**
   "4 KB, with huge pages of 2 MB or 1 GB for big buffers, which also saves TLB entries."

### Q20. What is a page table?

**In simple words:** Memory is divided into fixed-size **pages**, usually 4 KB each.

A page table entry maps one virtual page to one physical frame. It also holds the permission bits for that page.

The lowest bits of the address, the offset inside the page, are not translated.

**Example:** With 4 KB pages, virtual address 0x00403A10 is page 0x403, offset 0xA10. The page table says page 0x403 → frame 0x1F2, so the physical address is 0x001F2A10.

> "It's the lookup table the MMU uses: virtual page in, physical frame out. Each entry also has the permissions, like read, write and execute, and whether the page is actually in memory right now."

```text
Virtual page 0x100 → physical frame 0x500, read + write
```

**Cross-questions:**

1. **Why are page tables multi-level?**
   "A single flat table for a 48-bit address space would be enormous. With levels, the tables only exist for the parts of the address space that are actually used. arm64 typically uses 4 levels."
2. **Who walks the page table: the OS or the hardware?**
   "The **hardware** MMU walks it on a TLB miss. The OS only builds and updates the tables."
3. **How does a Linux driver access a physical register address?**
   "It can't use the physical address directly. It calls `ioremap()` (or `devm_platform_ioremap_resource()`) to create a mapping, then uses `readl()` / `writel()` on the returned virtual address."

### Q21. What is a TLB?

**In simple words:** The **TLB** is a small cache inside the MMU. It stores recent virtual-to-physical translations.

- On a **TLB hit**, the translation costs no extra memory access.
- On a **TLB miss**, the MMU has to read the page tables from RAM.

**Example:** A loop reads an array on the same page 1000 times: the first access is a TLB miss (page-table walk), and the next 999 are TLB hits.

> "Walking the page table on every access would be slow, so the CPU keeps a small cache of recent translations: the **TLB**. If the translation is there, it's a TLB hit and it's basically free. If not, the hardware walks the page table and then saves the result in the TLB."

```text
Virtual address → TLB → hit: physical address
                      → miss: page-table walk, then store the result in the TLB
```

**Cross-questions:**

1. **What happens to the TLB on a context switch?**
   "Either it's flushed, or, on modern Arm, entries are tagged with an **ASID**, an address-space ID, so entries from different processes can coexist and no flush is needed."
2. **What does a TLB miss cost?**
   "A page-table walk, which is several memory accesses, one per level, unless the table entries are in the cache."
3. **What is a TLB shootdown?**
   "When the kernel changes a mapping on a multicore system, other CPUs might still have the old entry in their TLB. It sends an inter-processor interrupt telling them to invalidate it."

### Q22. What is cache memory?

**In simple words:** Cache is a **small, fast memory (SRAM) between the CPU and main memory**. It keeps copies of recently used memory in fixed-size blocks called **cache lines**, usually 32 or 64 bytes each.

When the CPU needs data, it checks the cache first. It goes to RAM only if the data is not in the cache.

**Example:** Reading RAM takes about 100 CPU cycles; reading L1 cache takes 1 to 4. When the CPU reads `array[0]`, the cache loads a whole 64-byte line, which is 16 ints. So `array[1]` to `array[15]` are cache hits, served in 1 to 4 cycles.

> "Cache is a small, fast memory right next to the CPU that keeps recently used data and instructions. RAM is slow compared to the CPU, so the cache hides that delay, because programs tend to reuse the same data and nearby addresses."

```text
CPU → L1 → L2 → L3 → RAM      (each level bigger and slower)
```

**Cross-questions:**

1. **Write-through vs write-back?**
   "**Write-through** writes to the cache and to RAM every time: simple, but slower. **Write-back** writes only to the cache and updates RAM later, when the line is evicted: faster, but RAM can be stale."
2. **What's the problem with cache and DMA?** (very common in embedded)
   "DMA talks to RAM, not the cache. If the CPU wrote a buffer that's still only in the cache, DMA sends old data, so before a DMA transmit I **clean** (flush) the cache for that buffer. After a DMA receive, the cache may hold old data, so I **invalidate** it before reading. On a Cortex-M7 that's `SCB_CleanDCache_by_Addr()` and `SCB_InvalidateDCache_by_Addr()`. Or I put DMA buffers in non-cacheable memory with the MPU. In Linux, the DMA API, `dma_map_single()` or `dma_alloc_coherent()`, handles it."
3. **Why must peripheral registers never be cached?**
   "Because every read must actually reach the hardware, to see a status change. The MMU or MPU marks that region as **device memory**, which isn't cached and keeps accesses in order."

### Q23. What is a cache hit and a cache miss?

**In simple words:** - A **hit** means the data is already in the cache. It is returned in a few cycles.
- A **miss** means the data is not in the cache. It must be fetched from the next cache level or from RAM, which takes tens to hundreds of cycles.

**Example:** With 95 % hits at 1 cycle and 5 % misses at 100 cycles, the average is 0.95 × 1 + 0.05 × 100 ≈ **6 cycles**, instead of 100 cycles for every access.

> "Hit means the data is already in the cache, so you get it fast. Miss means it isn't, so the CPU has to go to the next level, or all the way to RAM, which costs a lot more cycles."

**Cross-questions:**

1. **What kinds of cache misses are there?**
   "**Compulsory**: the first access ever. **Capacity**: the working set is bigger than the cache. **Conflict**: two addresses map to the same cache set and keep evicting each other."
2. **How can code improve the hit rate?**
   "The cache loads whole **lines**, typically 32 or 64 bytes, so I access memory sequentially. For a 2D array I loop over rows in the inner loop, because C stores arrays row by row. I keep hot data together, and keep tight loops small."
3. **What is false sharing?**
   "Two CPUs write different variables that happen to sit in the **same cache line**. The line bounces between the cores and performance drops. I fix it by padding or aligning the variables to separate lines."

### Q24. Is virtual memory the same as cache memory?

**In simple words:** They solve different problems:

- **Virtual memory** is about **address translation and protection**. The MMU does it.
- **Cache** is about **speed**. It keeps a fast copy of part of memory.

They are separate hardware blocks.

**Example:** A Cortex-M7 has a cache but no virtual memory. An old PC without cache could still have virtual memory, just slower.

> "No, they solve completely different problems. Virtual memory is about **addressing and protection**: translating addresses. Cache is about **speed**: making memory access faster. They work together, but they're not the same thing."

**Cross-questions:**

1. **Can a system have a cache but no virtual memory?**
   "Yes. A Cortex-M7 has caches and an MPU, but no MMU."
2. **Is swap the same as virtual memory?**
   "No. Swap is one optional feature built on virtual memory: pages are moved to disk. Embedded Linux systems usually run without swap, because flash wears out and the timing becomes unpredictable."

### Q25. What is the relationship between the TLB, virtual memory and cache?

**In simple words:** On every memory access, three steps happen in order:

1. The **MMU/TLB** converts the virtual address to a physical address.
2. The **cache** is checked using that physical address.
3. Only if the cache misses, the data is read from **RAM**.

**Example:** The CPU reads virtual 0x00403A10 → the TLB gives physical 0x001F2A10 → L1 cache hit → the data arrives in about 4 cycles.

> "They're steps in the same path. The CPU makes a virtual address, the TLB or MMU turns it into a physical address, and then the cache is checked for the data before going to RAM. On real processors some of these lookups happen in parallel, but that's the logical order."

```text
CPU → virtual address → TLB / MMU → physical address → cache → RAM
```

**Cross-questions:**

1. **Does the cache lookup wait for the TLB?**
   "Not always. Many L1 caches are **VIPT**, virtually indexed and physically tagged: the cache set is selected with the virtual address while the TLB translates in parallel, and the physical tag is compared at the end. That hides the translation time."
2. **Where does the MPU fit on a Cortex-M?**
   "There's no translation: the address is already physical. The MPU only checks the permissions and the memory type (cacheable or device) of each region."

---

## 6. Debugging

### Q26. How would you use GDB to debug a crash?

**In simple words:** When a Cortex-M faults, the CPU saves registers on the stack and writes the **cause** of the fault into the fault status registers.

With the debugger, I read these registers. They tell me which instruction faulted and why.

**Example:** CFSR shows a precise bus fault and BFAR = 0x00000004. Address 4 is "NULL + 4", so the code read a struct member through a NULL pointer.

> "On an MCU I connect GDB through **SWD or JTAG**. When it hits the HardFault, I halt and look at **PC, LR and SP** first, then the **backtrace** to see how it got there.
>
> Then I read the **fault status registers**. They tell me what kind of fault it was: a bad memory access, an unaligned access, a divide by zero, things like that. I also look at the stacked PC, which is the actual instruction that faulted. Most of the time it ends up being a NULL pointer, a stack overflow, or memory corruption."

```text
info registers      # PC, LR, SP and the rest
bt                  # backtrace: how we got here
frame 1             # move to a caller
info locals         # its local variables
x/16wx $sp          # 16 words of the stack
```

**Cross-questions:**

1. **How do you find the exact instruction that caused a HardFault?**
   "On exception entry the hardware pushed 8 registers. The stacked **PC** is at offset 0x18 in that frame: R0, R1, R2, R3, R12, LR, **PC**, xPSR. Bit 2 of the EXC_RETURN value in LR tells me whether the frame is on the MSP or the PSP. Then I look up that PC in the map file or with `addr2line`."
2. **Which fault bits do you look at?**
   "**CFSR** has three parts. MemManage: an MPU violation. BusFault: a bad address, with **BFAR** holding the address if it's precise. UsageFault: an undefined instruction, **INVSTATE**, unaligned access or divide by zero. INVSTATE almost always means a function pointer without the Thumb bit, or a corrupted LR."
3. **What is an imprecise bus fault?**
   "A buffered write failed after the CPU had already moved on, so the stacked PC isn't the guilty instruction. For debugging I disable write buffering with the DISDEFWBUF bit in ACTLR, and the fault becomes precise."
4. **What if there's no debugger, in the field?**
   "My HardFault handler saves the stacked registers and fault registers to a reserved RAM area or flash, then resets. After reboot I send that log out over UART or the network."
5. **A Linux user-space crash?**
   "I enable core dumps with `ulimit -c unlimited` and open the core file with GDB. For a kernel oops, I decode the call trace with `addr2line` or `faddr2line` on vmlinux."

### Q27. Have you worked with a backtrace / call trace?

**In simple words:** Every function call leaves a **return address** on the stack.

A backtrace follows these saved return addresses, one by one. That gives the list of function calls that led to the current point.

**Example:** `main → app_task → sensor_task → sensor_read`, crashed at line 42. The pointer was NULL because the sensor's init had failed earlier and nobody checked the return value.

> "Yes, it's usually the first thing I look at. The backtrace is the chain of calls that got us to the crash. Frame 0 is where it stopped, and as I go up I see who called it. Here it's app_task, then sensor_task, then sensor_read crashed.
>
> And if the backtrace itself looks like garbage, with random addresses or no sensible frames, that already tells me something: the **stack is probably corrupted**, or it overflowed."

```text
#0 sensor_read()        ← crashed here
#1 sensor_task()
#2 app_task()
#3 vPortTaskWrapper()

Read it bottom-up: app_task() → sensor_task() → sensor_read() → crash
```

**Cross-questions:**

1. **The backtrace looks wrong in a release build. Why?**
   "Optimization inlines functions, turns calls into jumps (tail calls) and drops frame pointers, so frames disappear. I build with `-g` even for release, keep the ELF file for every version, and use the map file."
2. **How do you get a call trace from a device in the field?**
   "I save PC, LR and part of the stack in the fault handler. Later, on my PC, I run `addr2line` with the matching ELF to turn those addresses into function names and line numbers."

---

## 7. BLE

### Q28. Where did you work with BLE? Which protocol layer?

**Also asked as:** *Do you have experience with the Bluetooth stack?* · *What did you do in the BLE part of your project?*

**In simple words:** - **GAP** is the part of the BLE host that handles advertising, scanning and setting up connections.
- **GATT** defines how data is offered and accessed after the devices are connected.

**Example:** A fitness band advertises as "HR Band", the phone connects (GAP), then the phone reads and subscribes to the heart-rate value (GATT).

> "Mostly on the **host side, GAP and GATT**. GAP is everything before and around the connection: advertising, scanning, connecting. GATT is how the data is organized once you're connected: services and characteristics. Underneath GATT there's ATT, which does the actual reads and writes of attributes. The lower layers, like the link layer and the radio, I used through the vendor's stack."

```text
Application → GATT → ATT → L2CAP → HCI → Link Layer → PHY
```

**Cross-questions:**

1. **Central vs peripheral?**
   "The **peripheral** advertises and accepts connections, like a sensor or a watch. The **central** scans and starts the connection, like a phone. Broadcaster and observer are the connectionless versions."
2. **What's in an advertising packet?**
   "Up to **31 bytes** in legacy advertising: flags, the device name, service UUIDs, and manufacturer data. If I need more, the scanner can ask for a **scan response**, which is another 31 bytes."
3. **How do advertising and connection intervals affect power?**
   "Longer intervals mean the radio wakes less often, so less power, but slower discovery and higher latency. I tune both: fast advertising for the first seconds, then slower; and a connection interval that fits the data rate."
4. **Which stack did you use?**
   *(Fill in your own project, for example nRF Connect SDK / Zephyr, Nordic SoftDevice, ESP-IDF NimBLE or STM32WB.)*

### Q29. What is GATT?

**Also asked as:** *What is a BLE service?* · *What is a BLE characteristic?*

**In simple words:** GATT stores a device's data as a **table of attributes**. The attributes are grouped into:

- **Services**: each service is one function of the device, such as Heart Rate.
- **Characteristics**: each characteristic is one value inside a service. It has properties that say whether it can be read, written or notified.

**Example:** The Heart Rate service (0x180D) contains Heart Rate Measurement (0x2A37, notify) and Body Sensor Location (0x2A38, read).

> "GATT defines how the data is structured and exchanged after you connect. You have **services**, which group related things, like a Heart Rate service, and inside them **characteristics**, which are the actual values the phone can read, write, or get notified about."

```text
Service
 ├── Characteristic
 ├── Characteristic
 └── Characteristic
```

**Cross-questions:**

1. **Handle vs UUID?**
   "The **UUID** says **what** the attribute is, its type. The **handle** is its 16-bit **address** in the server's attribute table. The client discovers the handles once, then reads and writes by handle."
2. **16-bit vs 128-bit UUIDs?**
   "16-bit UUIDs are reserved for services adopted by the Bluetooth SIG, like Heart Rate 0x180D. Custom services must use a random 128-bit UUID."
3. **Is the GATT server always the peripheral?**
   "Usually, but not by definition. Client and server are GATT roles, central and peripheral are GAP roles, and they're independent. A phone can also host a GATT server."

### Q30. What is MTU in BLE?

**In simple words:** The ATT MTU is the **largest ATT packet** that both devices agree to use.

The ATT header takes 3 bytes, so the data per packet is MTU − 3. The default MTU is 23, which leaves 20 bytes of data.

**Example:** Sending 200 bytes: with the default 23-byte MTU it takes 10 packets of 20 bytes. With an MTU of 247 (244 bytes of data) it's one packet.

> "MTU is the biggest ATT packet the two sides agree to exchange. The default is **23 bytes**, and ATT takes 3 bytes of header, so you get **20 bytes** of actual data. That's where the famous 20-byte limit comes from. If I need more throughput, I **negotiate a bigger MTU** after connecting, for example 247. And the ATT MTU isn't the same as the radio packet size; those are different layers."

**Cross-questions:**

1. **How do you get more throughput?**
   "A bigger **ATT MTU**, **Data Length Extension** (link-layer packets from 27 up to 251 bytes), the **2M PHY**, a shorter connection interval, several packets per connection event, and notifications or write-without-response instead of acknowledged operations."
2. **Who negotiates the MTU?**
   "The client sends an Exchange MTU Request with its maximum, the server replies with its own, and both use the **smaller** of the two."
3. **What if my data is bigger than the MTU?**
   "For writes there's the **long write** (prepare and execute write). Otherwise I split it into chunks at the application level, with a small header for sequence or length."

---

## 8. Coding and C memory

### Q31. Merge two sorted linked lists

**In simple words:** Both lists are already sorted. So the smallest remaining element is always at the **front of one of the two lists**.

The algorithm compares the two front nodes and takes the smaller one. It repeats this until one list is empty. This builds the sorted result in a single pass.

**Example:** `1→3→5` and `2→4→6`: take 1, then 2, 3, 4, 5, 6. Result: `1→2→3→4→5→6`.

**Question:** given `head1` and `head2`, two sorted linked lists, merge them into one sorted list.

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

struct Node
{
    int32_t      data;
    struct Node *next;
};

/* Merges two sorted lists into one sorted list by re-linking the nodes (no allocation) */
struct Node *mergeList(struct Node *head1, struct Node *head2)
{
    struct Node  dummy;            /* placeholder: the merged list starts at dummy.next */
    struct Node *tail = &dummy;    /* last node of the merged list so far               */
    struct Node *p1   = head1;     /* working copies: parameters are not modified       */
    struct Node *p2   = head2;

    dummy.next = NULL;

    while ((p1 != NULL) && (p2 != NULL))
    {
        if (p1->data <= p2->data)  /* <= keeps equal values in order (stable)            */
        {
            tail->next = p1;       /* take the smaller node from list 1                  */
            p1 = p1->next;
        }
        else
        {
            tail->next = p2;       /* take the smaller node from list 2                  */
            p2 = p2->next;
        }
        tail = tail->next;         /* move the tail to the node just added               */
    }

    if (p1 != NULL)                /* one list is finished: attach the rest of the other */
    {
        tail->next = p1;
    }
    else
    {
        tail->next = p2;
    }

    return dummy.next;
}

/* Prints a list as: 1 -> 2 -> NULL */
static void printList(const char *name, const struct Node *head)
{
    const struct Node *cur = head;

    (void)printf("%s", name);
    while (cur != NULL)
    {
        (void)printf("%ld -> ", (long)cur->data);
        cur = cur->next;
    }
    (void)printf("NULL\n");
}

int main(void)
{
    /* Nodes in arrays, so the demo needs no malloc() */
    struct Node list1[3] = { {1, NULL}, {3, NULL}, {5, NULL} };
    struct Node list2[4] = { {2, NULL}, {4, NULL}, {6, NULL}, {8, NULL} };
    struct Node *merged;

    list1[0].next = &list1[1];     /* 1 -> 3 -> 5      */
    list1[1].next = &list1[2];
    list2[0].next = &list2[1];     /* 2 -> 4 -> 6 -> 8 */
    list2[1].next = &list2[2];
    list2[2].next = &list2[3];

    printList("List 1: ", &list1[0]);
    printList("List 2: ", &list2[0]);

    merged = mergeList(&list1[0], &list2[0]);
    printList("Merged: ", merged);

    return 0;
}
```

**Output:**

```text
List 1: 1 -> 3 -> 5 -> NULL
List 2: 2 -> 4 -> 6 -> 8 -> NULL
Merged: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 8 -> NULL
```

> "Both lists are already sorted, so I don't need to sort anything. I just walk both lists, compare the two current nodes, and take the smaller one. I use a **dummy node** at the start so I don't need a special case for the first node. When one list runs out, the rest of the other list is already sorted, so I attach it in one go. It's O(n + m) time, and no extra memory."

**Cross-questions:**

1. **Can you do it recursively?**
   "Yes, and it's shorter, but each node costs a stack frame, so a long list can overflow the stack. On embedded I prefer the iterative version."
2. **Without the dummy node?**
   "Then I pick the head first by comparing the two first nodes, and start the tail from there. The dummy just removes that special case."
3. **Is it stable when values are equal?**
   "Yes, because I use `<=`: with equal values, list 1's node goes first."
4. **How would you merge k sorted lists?**
   "Merge them in pairs, like merge sort, which is O(N log k), or use a min-heap of the k current heads."

### Q32. What happens when one list reaches NULL first?

**In simple words:** When one list ends, the nodes left in the other list are already sorted. They are also not smaller than anything merged so far. So the rest of that list can be attached as it is.

**Example:** `1→3` and `2→4→6→8`: after 1, 2, 3, list 1 is empty, so `4→6→8` is attached in one step.

> "The loop stops, and whatever's left in the other list is already in order, so I just hook it onto the tail in one line: `tail->next = head1 ? head1 : head2`. No need to loop over it."

**Cross-questions:**

1. **What if one list is empty from the start, or both are?**
   "The loop doesn't run at all, and `tail->next` gets the other list, or NULL if both are empty. `dummy.next` then returns the right answer, so no special case is needed."

### Q33. Does the merge code allocate a new node?

**In simple words:** The merge only changes the **`next` pointers** of the existing nodes. The nodes themselves stay where they are in memory. So no new memory is needed.

**Example:** Node 1's `next` changes from node 3 to node 2. No `malloc()` anywhere.

> "No, there's no malloc at all. I'm only re-linking the existing nodes by changing their `next` pointers. The dummy node is a local variable on the stack, and I return `dummy.next`, so it's never part of the result."

**Cross-questions:**

1. **What if the original lists must stay unchanged?**
   "Then I `malloc` a new node for each element, copy the data, and check every malloc for NULL. The caller must free the new list later."

### Q34. Where is a node pointer stored: heap or stack?

**In simple words:** A pointer is a **variable that holds an address**.

Where the pointer variable is stored (stack, data section or a register) is one question. Where the memory it points to was allocated (for example, the heap) is a different question.

**Example:** `node` (8 bytes, stack) holds 0x5600A0, the address of a 16-byte node on the heap.

> "Two different things. The **pointer variable**, if it's a local, lives on the **stack**. The **node** it points to, if I got it from malloc, lives on the **heap**. So the stack just holds an address that points into the heap."

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Node
{
    int32_t      data;
    struct Node *next;
};

int main(void)
{
    /* MISRA Rule 21.3 bans malloc() in safety-critical code; it's used here because the question is about the heap */
    struct Node *node = malloc(sizeof(struct Node));   /* 'node' is on the stack, the struct on the heap */
    int          status = 1;

    if (node != NULL)                                  /* malloc can fail: always check */
    {
        node->data = 42;
        node->next = NULL;

        (void)printf("address of the pointer variable (stack): %p\n", (void *)&node);
        (void)printf("value of the pointer = node address (heap): %p\n", (void *)node);
        (void)printf("node->data = %ld\n", (long)node->data);

        free(node);                                    /* give the memory back           */
        node   = NULL;                                 /* no dangling pointer left behind */
        status = 0;
    }

    return status;
}
```

**Output:**

```text
address of the pointer variable (stack): 000000ef521ffb20   (addresses vary per run)
value of the pointer = node address (heap): 000002c7bcc024f0
node->data = 42
```

```text
 Stack                      Heap
+---------+               +---------+
| node    | ------------> | data    |
+---------+               | next    |
                          +---------+
```

**Cross-questions:**

1. **What are the risks of using the heap on embedded?**
   "Fragmentation, unpredictable timing, and allocation failing at run time. So I check every malloc for NULL, free memory exactly once, and set the pointer to NULL after freeing. In many projects I avoid the heap after start-up completely."
2. **Which way does the stack grow?**
   "Downward on Arm, from high addresses to low. The heap usually grows upward toward it, so a stack overflow can silently overwrite heap or global data, unless an MPU guard region catches it."

### Q35. Is the new node pointer itself on the stack?

**In simple words:** Where a variable is stored depends on **how it is declared**, not on whether it is a pointer:

- A **local** variable is on the stack.
- A **global** or **`static`** variable is in `.data` or `.bss`.

**Example:** `struct Node *head;` at file level is in `.bss`, not on the stack. `struct Node *tmp;` inside a function is on the stack (or in a register).

> "If it's a local variable, yes, typically. But it depends on how it's declared: a global or a `static` pointer is in the data section, not the stack. And with optimization, the compiler might keep it in a register and never put it in memory at all."

**Cross-questions:**

1. **Can a function return a pointer to its local variable?**
   "No, the local is gone after the return. That's exactly the bug in [Q102](#q102-what-is-wrong-with-get_status_message)."

### Q36. Calculate the size of this structure

**In simple words:** The compiler places each member at an offset that is a multiple of its **alignment**, which is usually its size. Where needed, it adds unused **padding** bytes to reach that offset.

The total size of the structure is rounded up to a multiple of the largest alignment.

**Example:** `int` (0-3), `b[5]` (4-8), `c[2]` (9-10), then 5 empty bytes (11-15), then the pointer at 16-23: 24 bytes.

```c
#include <stdio.h>
#include <stddef.h>

struct sample
{
    int a;
    char b[5];
    char c[2];
    struct sample *next;
};

int main(void)
{
    /* offsetof() shows where the compiler placed each member, padding included */
    (void)printf("offset of a    = %zu\n", offsetof(struct sample, a));
    (void)printf("offset of b    = %zu\n", offsetof(struct sample, b));
    (void)printf("offset of c    = %zu\n", offsetof(struct sample, c));
    (void)printf("offset of next = %zu\n", offsetof(struct sample, next));
    (void)printf("sizeof(struct sample) = %zu\n", sizeof(struct sample));

    return 0;
}
```

**Output:**

```text
offset of a    = 0
offset of b    = 4
offset of c    = 9
offset of next = 16
sizeof(struct sample) = 24
```

On a typical **64-bit** system:

| Offset | Member | Size |
| --- | --- | --- |
| 0 | `int a` | 4 |
| 4 | `char b[5]` | 5 |
| 9 | `char c[2]` | 2 |
| 11 | padding | 5 |
| 16 | `struct sample *next` | 8 |
| | **Total** | **24 bytes** |

> "If you just add them up it's 4 + 5 + 2 = 11, plus 8 for the pointer, which is 19. But the pointer needs to start on an 8-byte boundary, so the compiler adds 5 bytes of padding after `c` to get to offset 16. Then the pointer takes 8, so it's **24 bytes**."

### Q37. What if the pointer is 4 bytes?

**In simple words:** On a 32-bit target, a pointer is 4 bytes and needs only 4-byte alignment. So less padding is needed before it.

**Example:** 11 bytes of members, 1 empty byte to reach 12, the 4-byte pointer at 12-15: 16 bytes.

> "Then the pointer only needs 4-byte alignment. After 11 bytes, I need just **1 byte** of padding to reach 12, plus the 4-byte pointer, so it's **16 bytes**. That's why I never hard-code struct sizes; I always use `sizeof`."

| | Pointer | Padding | `sizeof` |
| --- | --- | --- | --- |
| Typical 64-bit | 8 bytes | 5 | **24** |
| Typical 32-bit | 4 bytes | 1 | **16** |

**Cross-questions:**

1. **How do you reduce padding?**
   "Order members from largest alignment to smallest. Here it doesn't help much, but in `struct { char a; int b; char c; }` the size is 12, while `struct { int b; char a; char c; }` is only 8."
2. **Why does padding exist at all?**
   "The CPU reads aligned data faster, and some cores fault on unaligned access. A Cortex-M0, for example, can't do an unaligned word load."
3. **Why is the size rounded up at the end too?**
   "So that in an **array** of structs, every element is still aligned. The size is a multiple of the largest member alignment."
4. **What does `__attribute__((packed))` do, and what's the risk?**
   "It removes all padding, which is useful for protocol frames that must match byte for byte. But the members can become unaligned: slower access, a fault on some cores, and taking a pointer to a packed member is dangerous. I use it only for wire formats, and copy into a normal struct for processing."
5. **How do you check a member's offset?**
   "`offsetof(struct sample, next)`, which gives 16 on 64-bit and 12 on 32-bit."

---

## 9. SPI, EEPROM and driver design

### Q38. How do you split ("bifurcate") an SPI frame? How many bytes are command, address and data?

**In simple words:** SPI itself has **no frame format**. It only shifts bytes out on MOSI and in on MISO while CS is low.

The device's datasheet decides what the bytes mean. For SPI memories, the frame is usually: an opcode byte, then the address bytes, then the data.

**Example:** Reading 2 bytes from a 25LC256 at address 0x0123: send `03 01 23`, then two dummy bytes `FF FF`, and the two data bytes come back on MISO.

> "SPI itself doesn't have any frame format. It just shifts bytes while CS is low. The **device datasheet** decides what the bytes mean. For an SPI EEPROM or flash it's always the same pattern: one **opcode** byte, then the **address**, then the **data**.
>
> How many address bytes depends on the memory size. A small EEPROM needs 1, a 32 KB one needs 2, and most SPI flash needs 3. And since SPI is full duplex, whatever comes back on MISO while I'm sending the command is junk. To read, I send dummy bytes, usually 0xFF, just to clock the data in."

```text
CS low → [ opcode ] [ address: 1-3 bytes ] [ data: 1..N bytes ] → CS high
```

| Memory size | Address bits | Address bytes | Example part |
| --- | --- | --- | --- |
| Up to 256 bytes | 8 | 1 | 25AA020 (256 B) |
| Up to 64 KB | 16 | 2 | 25LC256 (32 KB) |
| Up to 16 MB | 24 | 3 | 25LC1024 (128 KB), most SPI NOR flash |
| Above 16 MB | 32 | 4 | Large NOR flash in 4-byte address mode |

Common 25xx EEPROM opcodes: **READ `0x03`**, **WRITE `0x02`**, **WREN `0x06`** (write enable), **RDSR `0x05`** (read status: bit 0 = write in progress).

**Cross-questions:**

1. **Does the value of the dummy byte matter?**
   "Usually not, the device ignores MOSI while it's sending. I use 0xFF so MOSI stays high, but a few devices treat incoming bytes as commands, so I check the datasheet."
2. **How fast can SPI go?**
   "Up to the device's maximum clock, the MCU's prescaler options, and what the traces allow. Typically 10 to 50 MHz on a board. Long wires or fly-leads usually force it lower."
3. **What are Dual and Quad SPI?**
   "They use 2 or 4 data lines instead of one, mostly for flash. QSPI controllers can even map the flash into memory, so code runs from it directly: XIP, execute in place."

### Q39. For an SPI EEPROM write, how does the frame depend on the way you write?

**In simple words:** An SPI EEPROM accepts a write only after a **Write Enable** command.

During one write command, the internal address counter only moves **inside the current page**. If the data goes past the end of the page, the address wraps back to the start of the same page.

**Example:** 64-byte pages, write 10 bytes at address 60. Done wrong, bytes go to 60-63 and then wrap to 0-5 of the same page. Done right, the driver splits it: 4 bytes at 60, then 6 bytes at 64.

> "Before any write, I have to send **WREN**, the write enable, as its own little transaction with its own CS cycle. Then I can do a **byte write**, which is opcode, address, one byte, or a **page write**, which is opcode, address, and up to a full page, like 64 bytes.
>
> The catch with page writes is the **page boundary**. If I start in the middle of a page and send too much, it doesn't move to the next page; it **wraps around** and overwrites the start of the same page. I've seen this bug in real code. So my driver always splits writes at page boundaries.
>
> After CS goes high, the EEPROM needs about 5 ms to actually write, so I poll the status register until the busy bit clears. Reads are easy: no page limit, I can read the whole chip in one go."

```text
Byte write:  [WREN]   then   [0x02][addr hi][addr lo][data]                    → wait for WIP = 0
Page write:  [WREN]   then   [0x02][addr hi][addr lo][d0][d1]...[up to 64]      → wait for WIP = 0
Read:                        [0x03][addr hi][addr lo][dummy → d0][dummy → d1]...
```

**Cross-questions:**

1. **Why do you need WREN before every write?**
   "It's a safety latch. The write-enable latch clears itself after each write, so a glitch on the bus can't accidentally overwrite data."
2. **EEPROM vs flash?**
   "EEPROM can be written **byte by byte** and lasts about a million cycles. Flash must be **erased in sectors** before writing, because a write can only turn 1s into 0s, and lasts about 10 to 100 thousand cycles. But flash is much bigger and cheaper."
3. **How do you protect parts of the EEPROM?**
   "With the **WP pin** and the block-protect bits in the status register."
4. **What if power fails during the 5 ms write cycle?**
   "That page can end up corrupted. That's why important data gets a CRC and two copies, as in [Q43](#q43-how-would-you-save-a-number-for-example-a-file-number-so-it-survives-reset)."

### Q40. Several devices on one SPI bus, with separate read/write operations: how do you design the driver?

**In simple words:** The driver has two layers:

- The **bus layer** owns the SPI controller. It does the transfers, drives CS, locks the bus, and sets each device's mode and speed.
- The **device layer** is written once per chip. It builds that chip's command frames and calls the bus layer to send them.

**Example:** An EEPROM (mode 0, 10 MHz, CS on PA4) and a display (mode 3, 20 MHz, CS on PA5) share SPI1. Each transfer locks the bus, sets that device's mode and speed, and drives only its CS.

> "I split it into **two layers**. At the bottom there's a generic **bus driver**. It knows the SPI controller and nothing about the devices. It does the transfer, drives the right chip select, sets the mode and speed for that device, and holds a **lock**, so two devices can never mix their transfers.
>
> On top, each device has its own **device driver**, like `eeprom_read()` and `eeprom_write()`, which knows the opcodes and page size and just builds frames. Each device is a small handle with its bus, CS pin, mode and speed. It's the same design Linux uses: the controller driver is the bus layer, and each device driver calls `spi_sync()` on its own `spi_device`."

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef enum
{
    SPI_OK = 0,
    SPI_ERR_PARAM,          /* NULL pointer or zero length */
    SPI_ERR_BUS             /* transfer failed or timeout  */
} spi_status_t;

/* ======================= Platform layer =======================
 * On the MCU these drive the SPI controller and a GPIO.
 * For this PC demo they simulate a 25LC256 EEPROM (32 KB, 64-byte pages). */

#define SIM_EE_SIZE    (32768U)
#define SIM_EE_PAGE    (64U)

static uint8_t  sim_mem[SIM_EE_SIZE];    /* the EEPROM's memory            */
static uint8_t  sim_frame[80];           /* bytes received during one CS   */
static size_t   sim_len = 0U;
static uint8_t  sim_wel = 0U;            /* write-enable latch             */
static uint16_t sim_rd_addr = 0U;        /* address counter for reads      */

static void bus_lock(uint8_t bus)   { (void)bus; }   /* RTOS mutex on the MCU */
static void bus_unlock(uint8_t bus) { (void)bus; }

static void bus_configure(uint8_t bus, uint8_t mode, uint32_t speed_hz)
{
    (void)bus;
    (void)mode;
    (void)speed_hz;
}

/* CS pin: low starts a frame, high ends it (the EEPROM acts on the frame at CS high) */
static void gpio_write(uint8_t pin, uint8_t level)
{
    (void)pin;
    if (level == 0U)
    {
        sim_len = 0U;
    }
    else if ((sim_len == 1U) && (sim_frame[0] == 0x06U))           /* WREN */
    {
        sim_wel = 1U;
    }
    else if ((sim_len > 3U) && (sim_frame[0] == 0x02U) && (sim_wel == 1U))   /* WRITE */
    {
        uint16_t addr = (uint16_t)(((uint16_t)sim_frame[1] << 8U) | sim_frame[2]);
        size_t   k;

        for (k = 3U; k < sim_len; k++)
        {
            /* the address wraps inside the page, like the real chip */
            uint16_t page_start = (uint16_t)(addr & (uint16_t)~(SIM_EE_PAGE - 1U));
            uint16_t in_page    = (uint16_t)((addr + (k - 3U)) % SIM_EE_PAGE);
            sim_mem[page_start + in_page] = sim_frame[k];
        }
        sim_wel = 0U;
        (void)printf("  [EEPROM] page write at %u, %u bytes\n", (unsigned)addr, (unsigned)(sim_len - 3U));
    }
    else
    {
        /* nothing to do */
    }
}

static spi_status_t bus_xfer(uint8_t bus, const uint8_t *tx, uint8_t *rx, size_t len)
{
    size_t k;

    (void)bus;
    if (tx != NULL)                                    /* bytes from the MCU */
    {
        (void)memcpy(&sim_frame[sim_len], tx, len);
        sim_len += len;
        if ((sim_frame[0] == 0x03U) && (sim_len == 3U))
        {
            sim_rd_addr = (uint16_t)(((uint16_t)sim_frame[1] << 8U) | sim_frame[2]);
        }
    }
    if (rx != NULL)                                    /* bytes back to the MCU */
    {
        for (k = 0U; k < len; k++)
        {
            if (sim_frame[0] == 0x05U)
            {
                rx[k] = 0x00U;                         /* status: never busy in the simulation */
            }
            else
            {
                rx[k] = sim_mem[sim_rd_addr % SIM_EE_SIZE];
                sim_rd_addr++;
            }
        }
    }
    return SPI_OK;
}

/* ======================= Generic bus layer ======================= */
typedef struct
{
    uint8_t  bus;           /* which SPI controller (0, 1 ...) */
    uint8_t  cs_pin;        /* this device's chip-select GPIO  */
    uint8_t  mode;          /* SPI mode 0-3 (CPOL / CPHA)      */
    uint32_t speed_hz;      /* maximum clock for this device   */
} spi_device_t;

/* One transaction with CS held low the whole time: send tx_len bytes, then read rx_len bytes */
spi_status_t spi_write_then_read(const spi_device_t *dev,
                                 const uint8_t *tx, size_t tx_len,
                                 uint8_t *rx, size_t rx_len)
{
    spi_status_t status = SPI_ERR_PARAM;

    if ((dev != NULL) && (tx != NULL) && (tx_len > 0U))
    {
        bus_lock(dev->bus);                                    /* no other device may use the bus now */
        bus_configure(dev->bus, dev->mode, dev->speed_hz);     /* this device's mode and speed        */
        gpio_write(dev->cs_pin, 0U);                           /* CS low: select only this device     */

        status = bus_xfer(dev->bus, tx, NULL, tx_len);         /* opcode + address (+ data)           */

        if ((status == SPI_OK) && (rx != NULL) && (rx_len > 0U))
        {
            status = bus_xfer(dev->bus, NULL, rx, rx_len);     /* dummy bytes out, data in            */
        }

        gpio_write(dev->cs_pin, 1U);                           /* CS high: end of the frame           */
        bus_unlock(dev->bus);
    }

    return status;
}

/* ======================= Device layer: 25LC256 ======================= */
#define EE_CMD_READ     (0x03U)     /* read data                        */
#define EE_CMD_WRITE    (0x02U)     /* write data (needs WREN first)    */
#define EE_CMD_WREN     (0x06U)     /* write enable                     */
#define EE_CMD_RDSR     (0x05U)     /* read status register             */
#define EE_SR_WIP       (0x01U)     /* status bit 0: write in progress  */
#define EE_PAGE_SIZE    (64U)       /* bytes per page                   */
#define EE_HDR_SIZE     (3U)        /* opcode + 2 address bytes         */
#define EE_POLL_MAX     (10000U)    /* poll limit (a real driver uses a timer) */

spi_status_t eeprom_read(const spi_device_t *ee, uint16_t addr, uint8_t *buf, size_t len)
{
    uint8_t cmd[EE_HDR_SIZE];

    cmd[0] = (uint8_t)EE_CMD_READ;
    cmd[1] = (uint8_t)(addr >> 8U);         /* address high byte */
    cmd[2] = (uint8_t)(addr & 0xFFU);       /* address low byte  */

    return spi_write_then_read(ee, cmd, EE_HDR_SIZE, buf, len);   /* a read may cross pages */
}

/* Polls the status register until the internal write cycle (~5 ms) is finished */
static spi_status_t eeprom_wait_ready(const spi_device_t *ee)
{
    const uint8_t cmd    = (uint8_t)EE_CMD_RDSR;
    uint8_t       sr     = (uint8_t)EE_SR_WIP;
    uint32_t      polls  = 0U;
    spi_status_t  status = SPI_OK;

    while ((status == SPI_OK) && ((sr & EE_SR_WIP) != 0U) && (polls < EE_POLL_MAX))
    {
        status = spi_write_then_read(ee, &cmd, 1U, &sr, 1U);
        polls++;
    }

    if ((status == SPI_OK) && ((sr & EE_SR_WIP) != 0U))
    {
        status = SPI_ERR_BUS;                                   /* timeout: still busy */
    }

    return status;
}

/* Writes len bytes, split at page boundaries so the page never wraps */
spi_status_t eeprom_write(const spi_device_t *ee, uint16_t addr, const uint8_t *data, size_t len)
{
    uint8_t       frame[EE_HDR_SIZE + EE_PAGE_SIZE];
    const uint8_t wren   = (uint8_t)EE_CMD_WREN;
    uint16_t      cur    = addr;        /* current EEPROM address     */
    size_t        done   = 0U;          /* bytes already written      */
    spi_status_t  status = SPI_OK;

    if (data == NULL)
    {
        status = SPI_ERR_PARAM;
    }

    while ((status == SPI_OK) && (done < len))
    {
        size_t room  = EE_PAGE_SIZE - ((size_t)cur % EE_PAGE_SIZE);    /* bytes left in this page */
        size_t chunk = ((len - done) < room) ? (len - done) : room;    /* never cross the page    */
        size_t i;

        status = spi_write_then_read(ee, &wren, 1U, NULL, 0U);         /* 1. WREN, own CS cycle   */

        if (status == SPI_OK)
        {
            frame[0] = (uint8_t)EE_CMD_WRITE;                           /* 2. opcode + address + data */
            frame[1] = (uint8_t)(cur >> 8U);
            frame[2] = (uint8_t)(cur & 0xFFU);
            for (i = 0U; i < chunk; i++)
            {
                frame[EE_HDR_SIZE + i] = data[done + i];
            }
            status = spi_write_then_read(ee, frame, EE_HDR_SIZE + chunk, NULL, 0U);
        }

        if (status == SPI_OK)
        {
            status = eeprom_wait_ready(ee);                             /* 3. wait for WIP = 0 */
        }

        cur  = (uint16_t)(cur + (uint16_t)chunk);
        done = done + chunk;
    }

    return status;
}

/* ======================= Application ======================= */
int main(void)
{
    const spi_device_t eeprom = { 0U, 4U, 0U, 10000000U };   /* SPI1, CS on pin 4, mode 0, 10 MHz */
    uint8_t      wr_buf[100];
    uint8_t      rd_buf[100];
    spi_status_t status;
    size_t       i;

    for (i = 0U; i < sizeof(wr_buf); i++)
    {
        wr_buf[i] = (uint8_t)i;                              /* test pattern 0, 1, 2 ... 99 */
    }

    (void)printf("Writing 100 bytes at address 60:\n");
    status = eeprom_write(&eeprom, 60U, wr_buf, sizeof(wr_buf));
    (void)printf("write status = %d\n", (int)status);

    status = eeprom_read(&eeprom, 60U, rd_buf, sizeof(rd_buf));
    (void)printf("read status  = %d\n", (int)status);

    if (memcmp(wr_buf, rd_buf, sizeof(wr_buf)) == 0)
    {
        (void)printf("readback OK: all 100 bytes match\n");
    }
    else
    {
        (void)printf("readback FAILED\n");
    }

    return 0;
}
```

**Output:**

```text
Writing 100 bytes at address 60:
  [EEPROM] page write at 60, 4 bytes
  [EEPROM] page write at 64, 64 bytes
  [EEPROM] page write at 128, 32 bytes
write status = 0
read status  = 0
readback OK: all 100 bytes match
```

| Layer | Knows | Functions |
| --- | --- | --- |
| **Bus driver** (generic) | The SPI controller, CS, locking | `spi_write_then_read()`, `spi_transfer()` |
| **Device driver** (specific) | The device's opcodes, addresses, page size, timing | `eeprom_read()`, `eeprom_write()`, `flash_erase()` ... |

**Cross-questions:**

1. **Why does the bus layer need a lock?**
   "With an RTOS, two tasks might use two devices on the same bus. The whole transaction, CS low to CS high, must be atomic; otherwise one task's bytes go to the other task's device."
2. **What if the devices use different SPI modes or speeds?**
   "That's why each handle stores its mode and speed, and the bus layer reconfigures the controller at the start of every transaction."
3. **Why drive CS with a GPIO instead of the hardware NSS pin?**
   "Hardware NSS on STM32 only supports one device and may toggle between bytes in some modes. With a GPIO I get one CS per device and full control over when it goes high."
4. **Can you use DMA in this design?**
   "Yes. The bus layer starts the DMA and waits on a semaphore that the DMA-complete interrupt gives. CS goes high only after the transfer is really finished."

---

## 10. C programming

### Q41. What are bit fields in a structure?

**In simple words:** A bit field is a structure member with a **width given in bits**.

The compiler packs several bit fields into one storage unit. It generates the shift-and-mask code for every access automatically.

**Example:** Four 1-bit flags plus a 3-bit mode fit in one byte, instead of five separate bytes.

> "Bit fields let me give a struct member an exact number of bits, so several small values can share one word. It's handy for packing flags, say a 1-bit ready flag, a 1-bit error flag, and a 3-bit mode.
>
> But I'm careful with them. The **bit order and packing are up to the compiler**, so I don't use bit fields to map hardware registers or protocol packets that must match exactly. For those I use masks and shifts. And you can't take the address of a bit field."

```c
#include <stdio.h>

struct status
{
    unsigned int ready : 1;     /* 1 bit:  0 or 1   (unsigned: a signed 1-bit field holds 0 and -1) */
    unsigned int error : 1;     /* 1 bit            */
    unsigned int mode  : 3;     /* 3 bits: 0 to 7   */
    unsigned int count : 4;     /* 4 bits: 0 to 15  */
};                              /* 9 bits, packed into one unsigned int (layout is compiler-defined) */

int main(void)
{
    struct status s = {0U, 0U, 0U, 0U};

    s.ready = 1U;
    s.mode  = 5U;
    s.count = 15U;              /* the largest value 4 bits can hold */

    (void)printf("ready = %u, error = %u, mode = %u, count = %u\n",
                 (unsigned int)s.ready, (unsigned int)s.error,
                 (unsigned int)s.mode, (unsigned int)s.count);
    (void)printf("sizeof(struct status) = %zu bytes\n", sizeof(struct status));

    return 0;
}
```

**Output:**

```text
ready = 1, error = 0, mode = 5, count = 15
sizeof(struct status) = 4 bytes
```

**Cross-questions:**

1. **What's `sizeof(struct status)`?**
   "Usually 4, because the bit fields are packed into one `unsigned int`. But the C standard leaves it to the compiler, so I don't rely on it."
2. **Why use `unsigned int` for bit fields?**
   "A 1-bit **signed** field can only hold 0 and −1, which surprises people. Unsigned fields give 0 and 1."
3. **Is writing a bit field atomic?**
   "No. The compiler reads the whole word, changes the bits and writes it back, so it has the same race as [Q71](#q71-software-xor-toggle-vs-a-hardware-toggle-register-whats-wrong-with-read-modify-write) if an ISR touches another field."

### Q42. Are function pointers basically used for callbacks?

**In simple words:** A function pointer stores the **address of a function**. This lets the program choose which function to call at run time.

A callback is one use of this. The driver stores the address of the application's function, and calls that function when an event happens.

**Example:** `uart_register_callback(on_frame);`. Later, when a frame arrives, the UART driver calls `on_frame()` without knowing anything about the application.

> "Callbacks are the most common use, yes. For example, my UART driver lets the application register a function, and when a frame arrives, the ISR calls it back, so the driver doesn't need to know anything about the application.
>
> But I use them in other places too: **state machines**, where I have a table of handler functions indexed by state; **command dispatch tables**; and **ops structures** for driver abstraction, like `file_operations` in Linux. And the interrupt **vector table** is literally an array of function pointers."

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* ======================= UART driver ======================= */
typedef void (*rx_callback_t)(const uint8_t *data, size_t len);   /* type: pointer to a function */

static rx_callback_t g_rx_cb = NULL;       /* the registered callback; NULL = none */
static uint8_t       g_rx_buf[64];         /* filled by the UART driver            */
static size_t        g_rx_len = 0U;        /* number of valid bytes in g_rx_buf    */

/* The application registers its function once, at start-up */
void uart_register_callback(rx_callback_t cb)
{
    g_rx_cb = cb;
}

/* Called by the driver when a frame is complete.
 * Runs in interrupt context on the MCU, so the callback must be short and must not block. */
void uart_rx_complete_isr(void)
{
    if (g_rx_cb != NULL)                   /* never call through a NULL pointer */
    {
        g_rx_cb(g_rx_buf, g_rx_len);
    }
}

/* ======================= Application ======================= */
static void on_frame(const uint8_t *data, size_t len)
{
    size_t i;

    (void)printf("on_frame(): %zu bytes:", len);
    for (i = 0U; i < len; i++)
    {
        (void)printf(" %02X", (unsigned int)data[i]);
    }
    (void)printf("\n");
}

int main(void)
{
    uart_register_callback(on_frame);      /* the driver now knows which function to call */

    /* Simulate the UART receiving 3 bytes, then the "frame complete" interrupt */
    g_rx_buf[0] = 0xAAU;
    g_rx_buf[1] = 0x01U;
    g_rx_buf[2] = 0x55U;
    g_rx_len    = 3U;
    uart_rx_complete_isr();

    return 0;
}
```

**Output:**

```text
on_frame(): 3 bytes: AA 01 55
```

**Cross-questions:**

1. **How do you declare a pointer to a function taking two ints and returning an int? And an array of them?**
   "`int (*fp)(int, int);` and `int (*ops[4])(int, int);`. With a `typedef` it's much easier to read: `typedef int (*op_t)(int, int); op_t ops[4];`."
2. **What are the dangers?**
   "Calling a NULL pointer, so I always check. On Cortex-M, a function address without the Thumb bit causes an INVSTATE fault. And a callback called from an ISR runs in **interrupt context**, so it must be short and must not block. I document that for whoever writes the callback."

### Q43. How would you save a number (for example a file number) so it survives reset?

**In simple words:** The value is saved in non-volatile memory together with three extra fields:

- A **magic number** shows that the record was really written.
- A **CRC** shows whether the record is corrupted.
- A **sequence counter** shows which copy is newer.

Two copies are kept, so one copy is always intact.

**Example:** File number 1234 is saved with magic, sequence 7 and a CRC. A power cut corrupts copy A during the write, so at boot copy A fails its CRC and copy B (sequence 6, still valid) is used.

> "It goes into **non-volatile memory**, EEPROM or flash, as a plain binary integer, not as a string.
>
> But I don't just write the raw value. I wrap it in a small record with a **magic number** and a **CRC**, so on boot I can tell a valid record from erased or half-written memory. And I keep **two copies**, so if power goes off in the middle of a write, the other copy is still good.
>
> If it's flash, I also think about **wear**: I don't erase the sector every time; I append new records and only erase when the sector is full."

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define RECORD_MAGIC   (0xA5A5F11EUL)      /* marks a record that was really written */

typedef struct
{
    uint32_t magic;          /* RECORD_MAGIC                                     */
    uint32_t sequence;       /* +1 on every save: the higher valid copy is newer */
    uint32_t file_number;    /* the value itself, in binary                      */
    uint32_t crc;            /* CRC-32 over the fields above, written last       */
} saved_record_t;

/* Standard CRC-32 (polynomial 0xEDB88320, as used by Ethernet and zip) */
static uint32_t crc32(const uint8_t *data, size_t len)
{
    uint32_t crc = 0xFFFFFFFFUL;
    size_t   i;
    uint32_t bit;

    for (i = 0U; i < len; i++)
    {
        crc ^= (uint32_t)data[i];
        for (bit = 0U; bit < 8U; bit++)
        {
            if ((crc & 1UL) != 0UL)
            {
                crc = (crc >> 1U) ^ 0xEDB88320UL;
            }
            else
            {
                crc = crc >> 1U;
            }
        }
    }
    return ~crc;
}

/* Fills a record; on the MCU this would then be written to flash, CRC last */
static void record_make(saved_record_t *rec, uint32_t sequence, uint32_t value)
{
    rec->magic       = RECORD_MAGIC;
    rec->sequence    = sequence;
    rec->file_number = value;
    rec->crc         = crc32((const uint8_t *)rec, offsetof(saved_record_t, crc));
}

/* A record is usable only if both the magic value and the CRC are correct */
static bool record_is_valid(const saved_record_t *rec)
{
    bool valid = false;

    if ((rec != NULL) && (rec->magic == RECORD_MAGIC))
    {
        valid = (crc32((const uint8_t *)rec, offsetof(saved_record_t, crc)) == rec->crc);
    }
    return valid;
}

/* Returns the newest valid copy, or NULL if neither copy is valid */
static const saved_record_t *record_pick(const saved_record_t *a, const saved_record_t *b)
{
    const saved_record_t *best    = NULL;
    const bool            a_valid = record_is_valid(a);
    const bool            b_valid = record_is_valid(b);

    if (a_valid && b_valid)
    {
        best = (a->sequence > b->sequence) ? a : b;
    }
    else if (a_valid)
    {
        best = a;
    }
    else if (b_valid)
    {
        best = b;
    }
    else
    {
        /* no valid copy: use a default value */
    }
    return best;
}

static void show(const char *label, const saved_record_t *rec)
{
    if (rec != NULL)
    {
        (void)printf("%s: file number %lu (sequence %lu)\n", label,
                     (unsigned long)rec->file_number, (unsigned long)rec->sequence);
    }
    else
    {
        (void)printf("%s: no valid record\n", label);
    }
}

int main(void)
{
    saved_record_t copy_a;
    saved_record_t copy_b;

    record_make(&copy_b, 6U, 1233U);        /* older save                */
    record_make(&copy_a, 7U, 1234U);        /* newest save               */
    show("Both copies good  ", record_pick(&copy_a, &copy_b));

    copy_a.file_number = 9999U;             /* simulate a power cut corrupting copy A */
    show("Copy A corrupted  ", record_pick(&copy_a, &copy_b));

    copy_b.magic = 0xFFFFFFFFUL;            /* copy B erased as well     */
    show("Both copies bad   ", record_pick(&copy_a, &copy_b));

    return 0;
}
```

**Output:**

```text
Both copies good  : file number 1234 (sequence 7)
Copy A corrupted  : file number 1233 (sequence 6)
Both copies bad   : no valid record
```

**Cross-questions:**

1. **Why a CRC and not a simple checksum?**
   "A sum misses errors like two swapped bytes, or two errors that cancel out. A CRC catches all burst errors up to its width, and nearly everything else."
2. **With two copies, how do you know which one is newer?**
   "Each record has a **sequence counter**. At boot I take the valid copy, with a good CRC, that has the highest counter."
3. **In what order do you write the record?**
   "The data first, and the CRC or 'valid' marker **last**. If power fails in the middle, the record simply looks invalid, and the other copy is used."
4. **How long will the flash last?**
   "I calculate it. With a 10,000-cycle sector, writing once a minute, and rotating through 64 slots per erase, that's 64 × 10,000 minutes, about a year. If that's not enough, I write less often or use more space."

### Q44. How would you store a mobile number in flash using the minimum memory?

**In simple words:** One decimal digit (0 to 9) fits in **4 bits**. So two digits fit in one byte. This format is called **packed BCD**.

**Example:** "9876543210" as a string is 11 bytes. As packed BCD it's `98 76 54 32 10`: 5 bytes.

> "A 10-digit number can go up to 9,999,999,999, which needs 34 bits, so it doesn't fit in a `uint32_t`. As a string it would take 11 bytes, and as a `uint64_t` 8 bytes, but then I lose leading zeros and the plus sign.
>
> I'd use **packed BCD**: 4 bits per digit, two digits per byte, so 10 digits fit in **5 bytes**. It keeps every digit, it's easy to convert back, and if I add a country code like +91 it's just 6 bytes."

| Format | Size for 10 digits | Notes |
| --- | --- | --- |
| String (`"9876543210"`) | **11 bytes** (with `'\0'`) | Easy to print; wasteful |
| `uint64_t` | **8 bytes** | Compact, but loses leading zeros and the `+` |
| **Packed BCD** (2 digits per byte) | **5 bytes** | Keeps every digit, including leading zeros; easy to unpack |

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Packs ASCII digits two per byte: "9876543210" -> {0x98, 0x76, 0x54, 0x32, 0x10}.
 * out must hold (n_digits + 1) / 2 bytes; an odd count is padded with 0xF. */
void pack_bcd(const char *digits, uint8_t *out, size_t n_digits)
{
    size_t i;

    if ((digits != NULL) && (out != NULL))
    {
        for (i = 0U; i < n_digits; i += 2U)
        {
            uint8_t hi = (uint8_t)((uint8_t)digits[i] - (uint8_t)'0');          /* first digit: high nibble */
            uint8_t lo = 0x0FU;                                                  /* padding by default       */

            if ((i + 1U) < n_digits)
            {
                lo = (uint8_t)((uint8_t)digits[i + 1U] - (uint8_t)'0');         /* second digit: low nibble */
            }

            out[i / 2U] = (uint8_t)((uint8_t)(hi << 4U) | lo);
        }
    }
}

/* Unpacks back to a string; stops at a 0xF padding nibble. text must hold n_bytes * 2 + 1 chars. */
void unpack_bcd(const uint8_t *in, size_t n_bytes, char *text)
{
    size_t i;
    size_t pos = 0U;

    if ((in != NULL) && (text != NULL))
    {
        for (i = 0U; i < n_bytes; i++)
        {
            uint8_t hi = (uint8_t)(in[i] >> 4U);
            uint8_t lo = (uint8_t)(in[i] & 0x0FU);

            text[pos] = (char)('0' + (char)hi);
            pos++;
            if (lo != 0x0FU)
            {
                text[pos] = (char)('0' + (char)lo);
                pos++;
            }
        }
        text[pos] = '\0';
    }
}

int main(void)
{
    const char number[] = "9876543210";        /* 10 digits: 11 bytes as a string */
    uint8_t    packed[5];                      /* 10 digits: 5 bytes as BCD       */
    char       text[11];
    size_t     i;

    pack_bcd(number, packed, 10U);

    (void)printf("string : \"%s\" uses %zu bytes\n", number, sizeof(number));
    (void)printf("BCD    :");
    for (i = 0U; i < sizeof(packed); i++)
    {
        (void)printf(" %02X", (unsigned int)packed[i]);
    }
    (void)printf("  uses %zu bytes\n", sizeof(packed));

    unpack_bcd(packed, sizeof(packed), text);
    (void)printf("unpack : \"%s\"\n", text);

    return 0;
}
```

**Output:**

```text
string : "9876543210" uses 11 bytes
BCD    : 98 76 54 32 10  uses 5 bytes
unpack : "9876543210"
```

**Cross-questions:**

1. **How do you unpack it?**
   "For each byte: the high digit is `b >> 4`, the low digit is `b & 0x0F`, and I add `'0'` to turn each into a character. A nibble of 0xF means padding, so I stop there."
2. **Could you go even smaller?**
   "One 10-digit number needs 34 bits, which still takes 5 bytes. But if I store many numbers, I can bit-pack them at 34 bits each instead of 40, saving about 15 %. It's usually not worth the complexity."

---

## 11. Bit manipulation

### Q45. How do you extract a byte from a 32-bit value and store it in a one-byte variable?

**In simple words:** - A **right shift** moves the wanted byte down to bits 0-7.
- An **AND with 0xFF** then clears all the other bits.

**Example:** `0x12345678 >> 16` = `0x1234`, then `& 0xFF` = **0x34**.

> "Shift it down, then mask it. If I want byte 2, I shift right by 16 so that byte lands at the bottom, then AND with 0xFF to throw away everything else. In general, byte N is `(x >> (8 * N)) & 0xFF`."

```c
#include <stdio.h>
#include <stdint.h>

/* Returns byte n (0 = lowest byte) of value */
uint8_t get_byte(uint32_t value, uint8_t n)
{
    uint8_t result = 0U;

    if (n < 4U)                                      /* shifting by 32 or more is undefined */
    {
        result = (uint8_t)((value >> (8U * (uint32_t)n)) & 0xFFUL);
    }

    return result;
}

int main(void)
{
    const uint32_t x = 0x12345678UL;
    uint8_t        n;

    for (n = 0U; n < 4U; n++)
    {
        (void)printf("byte %u of 0x%08lX = 0x%02X\n", (unsigned int)n, (unsigned long)x,
                     (unsigned int)get_byte(x, n));
    }

    return 0;
}
```

**Output:**

```text
byte 0 of 0x12345678 = 0x78
byte 1 of 0x12345678 = 0x56
byte 2 of 0x12345678 = 0x34
byte 3 of 0x12345678 = 0x12
```

**Cross-questions:**

1. **The cast to `uint8_t` already truncates. Why mask too?**
   "The result is the same, but the mask shows the intent, and it matters if the result goes into a wider variable. I also keep the value **unsigned**, because right-shifting a negative signed number is implementation-defined."
2. **How do you put a byte back at position N?**
   "Clear the old byte, then OR in the new one: `x = (x & ~(0xFFU << (8U * N))) | ((uint32_t)b << (8U * N));`."
3. **How do you swap the byte order of a 32-bit value?**
   "Move each byte to the opposite position with shifts and masks, or use `__builtin_bswap32()`, which compiles to the single **REV** instruction on Arm."

### Q46. How do you extract one bit and store it in a one-byte variable?

**In simple words:** - A **right shift** moves the wanted bit down to bit 0.
- An **AND with 1** then clears all the other bits. The result is 0 or 1.

**Example:** x = 0b1011_0100, bit 2: `x >> 2` = 0b10_1101, then `& 1` = **1**.

> "Same idea: shift the bit down to position 0 and mask with 1. Then the variable is just 0 or 1."

```c
#include <stdio.h>
#include <stdint.h>

/* Returns bit pos (0..31) of value as 0 or 1 */
uint8_t get_bit(uint32_t value, uint8_t pos)
{
    uint8_t result = 0U;

    if (pos < 32U)                                   /* shifting by 32 or more is undefined */
    {
        result = (uint8_t)((value >> pos) & 0x01UL);
    }

    return result;
}

int main(void)
{
    const uint32_t x = 0xB4UL;                       /* binary 1011 0100 */
    int8_t         pos;

    (void)printf("bits of 0x%02lX from bit 7 to bit 0: ", (unsigned long)x);
    for (pos = 7; pos >= 0; pos--)
    {
        (void)printf("%u", (unsigned int)get_bit(x, (uint8_t)pos));
    }
    (void)printf("\n");
    (void)printf("bit 2 = %u, bit 3 = %u\n", (unsigned int)get_bit(x, 2U), (unsigned int)get_bit(x, 3U));

    return 0;
}
```

**Output:**

```text
bits of 0xB4 from bit 7 to bit 0: 10110100
bit 2 = 1, bit 3 = 0
```

**Cross-questions:**

1. **Checking a bit vs extracting it?**
   "`if (x & (1U << n))` is non-zero when the bit is set, but the value is the mask, like 8, not 1. If I need exactly 0 or 1, I shift down, or use `!!(x & mask)`."
2. **How do you count the set bits?**
   "`while (x) { x &= x - 1; count++; }`. `x & (x - 1)` clears the lowest set bit, so the loop runs once per set bit."
3. **How do you check whether a number is a power of two?**
   "`x != 0 && (x & (x - 1)) == 0`. A power of two has exactly one bit set."

### Q47. Is there another way to extract a byte from a 32-bit variable?

**In simple words:** A 32-bit value is stored in memory as 4 bytes. The order of the bytes depends on the CPU:

- **Little-endian** stores the lowest byte at the lowest address.
- **Big-endian** stores the highest byte first.

Reading the bytes through memory, with a union or a `uint8_t` pointer, depends on this order. Shift-and-mask does not.

**Example:** 0x12345678 stored at address 0x100 on a little-endian CPU: 0x100 = 78, 0x101 = 56, 0x102 = 34, 0x103 = 12. On big-endian it's 12 34 56 78.

> "Yes, with a **union** or by casting to a `uint8_t` pointer. But then the answer depends on **endianness**. On a little-endian CPU like ARM, `bytes[0]` is the lowest byte; on big-endian it's the highest. Shift-and-mask gives the same answer on any CPU, so that's what I use in portable code."

```c
#include <stdio.h>
#include <stdint.h>

/* For explaining endianness only: MISRA Rule 19.2 (advisory) discourages unions,
 * so production code uses shift-and-mask (Q45) instead. */
typedef union
{
    uint32_t word;
    uint8_t  bytes[4];
} word_bytes_t;

int main(void)
{
    const word_bytes_t data = { 0x12345678UL };       /* initializes the first member, word */
    const uint32_t     x    = 0x12345678UL;
    const uint8_t     *p    = (const uint8_t *)&x;    /* Rule 11.3: a cast to a character-type pointer is allowed */
    const uint32_t     one  = 1UL;
    uint32_t           i;

    /* Endianness check: is the lowest byte of 1 stored first? */
    if (*(const uint8_t *)&one == 1U)
    {
        (void)printf("This CPU is little-endian\n");
    }
    else
    {
        (void)printf("This CPU is big-endian\n");
    }

    for (i = 0U; i < 4U; i++)
    {
        (void)printf("union bytes[%lu] = 0x%02X   pointer p[%lu] = 0x%02X   shift-and-mask byte %lu = 0x%02X\n",
                     (unsigned long)i, (unsigned int)data.bytes[i],
                     (unsigned long)i, (unsigned int)p[i],
                     (unsigned long)i, (unsigned int)((x >> (8UL * i)) & 0xFFUL));
    }

    return 0;
}
```

**Output:**

```text
This CPU is little-endian
union bytes[0] = 0x78   pointer p[0] = 0x78   shift-and-mask byte 0 = 0x78
union bytes[1] = 0x56   pointer p[1] = 0x56   shift-and-mask byte 1 = 0x56
union bytes[2] = 0x34   pointer p[2] = 0x34   shift-and-mask byte 2 = 0x34
union bytes[3] = 0x12   pointer p[3] = 0x12   shift-and-mask byte 3 = 0x12
```

| Method | Portable across endianness? |
| --- | --- |
| **Shift + mask** | **Yes**: the preferred way |
| Union | No: depends on the byte order |
| `uint8_t *` pointer | No: depends on the byte order |

**Cross-questions:**

1. **How do you detect endianness at run time?**
   "`uint32_t one = 1;` then look at the first byte through a `uint8_t *`: if it's 1, the CPU is little-endian."
2. **Is reading a different union member legal?**
   "In C, yes: the bytes are reinterpreted, though the result depends on the platform. In C++ it's undefined behaviour, so there I use `memcpy`."
3. **What is network byte order?**
   "Big-endian. That's why socket code uses `htonl()` and `ntohl()` to convert between host and network order."

---

## 12. Debugging basics

### Q48. What is `break`, and how is it different from a breakpoint?

**In simple words:** - `break` is a **C statement**. At run time, it exits the innermost loop or `switch`.
- A **breakpoint** is a **debugger feature**. It stops the CPU at a chosen instruction.

**Example:** A search loop uses `break` as soon as it finds the value. A breakpoint on line 20 in the debugger stops the whole program at that line.

> "They just share a name. `break` is a **C keyword**: it jumps out of the innermost loop or switch. A **breakpoint** is a **debugger** thing: it stops the whole program at a line so I can look at variables and registers. One changes the program's flow; the other pauses it from outside."

```c
#include <stdio.h>
#include <stdint.h>

#define BUF_LEN  (8U)

int main(void)
{
    const uint8_t buf[BUF_LEN] = { 5U, 9U, 3U, 0U, 7U, 0U, 2U, 1U };
    uint32_t      i;

    for (i = 0U; i < BUF_LEN; i++)
    {
        if (buf[i] == 0U)
        {
            break;              /* leaves only this loop (one break per loop: Rule 15.4) */
        }
    }

    if (i < BUF_LEN)
    {
        (void)printf("first 0 found at index %lu\n", (unsigned long)i);
    }
    else
    {
        (void)printf("no 0 in the buffer\n");
    }

    return 0;
}
```

**Output:**

```text
first 0 found at index 3
```

**Cross-questions:**

1. **How do you break out of two nested loops?**
   "`break` only leaves the inner loop. I use a flag checked by the outer loop, or move the loops into a function and `return`. A `goto` to a single exit label is also accepted in kernel-style C, for clean-up."
2. **What happens if you forget `break` in a switch?**
   "Execution falls through into the next case. Sometimes that's intended, so I mark it with a `/* fall through */` comment, and the compiler's `-Wimplicit-fallthrough` warning catches the accidental ones."

### Q49. What is a breakpoint, and how does it work?

**In simple words:** There are three kinds:

- A **software breakpoint** replaces an instruction in memory with a `BKPT` instruction. So it needs memory that can be written, such as RAM.
- A **hardware breakpoint** uses address comparators inside the CPU's debug unit. It works in flash too, but there are only a few of them.
- A **watchpoint** uses a comparator on a data address. It stops the CPU when that variable is read or written.

**Example:** "Who keeps setting `motor_speed` to 0?" A write watchpoint on `motor_speed` stops the CPU exactly at the line that writes it.

> "It halts the CPU at a specific instruction so I can inspect everything. There are two kinds.
>
> A **software breakpoint**: the debugger replaces the instruction with a `BKPT` instruction. That needs writable memory, so it works in RAM. A **hardware breakpoint** uses comparators inside the CPU's debug unit, so it works in flash too, but you only get a few, like 6 on a Cortex-M4. That's why sometimes the debugger tells you you're out of breakpoints.
>
> And there's the **watchpoint**, which I find really useful: it stops when a specific variable is **written**. It's perfect for 'who's corrupting this variable?'"

| Type | How it works | Limits |
| --- | --- | --- |
| **Software breakpoint** | The debugger replaces the instruction with a `BKPT` instruction | Needs writable memory (RAM); doesn't work in flash |
| **Hardware breakpoint** | The CPU's debug comparators match the address | Works in flash; only a few (e.g. 6 on Cortex-M4) |
| **Watchpoint** | Halts when a given **data address** is read or written | "Who changed this variable?" |

**Cross-questions:**

1. **How many breakpoints and watchpoints does a Cortex-M4 have?**
   "The **FPB** unit has 6 instruction comparators (plus 2 for literals), so 6 hardware breakpoints. The **DWT** unit has 4 comparators for watchpoints."
2. **Why are conditional breakpoints slow?**
   "The CPU really stops every time, the debugger evaluates the condition on the PC, and resumes if it's false. In a hot loop, that slows the program down enormously."
3. **Stepping through code with interrupts and timers: what goes wrong?**
   "The peripherals keep running while the CPU is halted. Timers overflow, the **watchdog** resets the chip, and communication times out. On STM32 I set the `DBGMCU` freeze bits, so the watchdog and timers stop while the core is halted."

---

## 13. Bit manipulation patterns to remember

```c
/* x is a uint32_t, n is 0..31 (0..3 for bytes) */
uint8_t byte_n = (uint8_t)((x >> (8U * n)) & 0xFFU);   /* extract byte n */
uint8_t bit_n  = (uint8_t)((x >> n) & 0x01U);          /* extract bit n  */

x |=  (1U << n);                                       /* set bit n      */
x &= ~(1U << n);                                       /* clear bit n    */
x ^=  (1U << n);                                       /* toggle bit n   */

if ((x & (1U << n)) != 0U)                             /* check bit n (explicit comparison: Rule 14.4) */
{
    /* bit n is 1 */
}
```

---

## 14. I2C in depth

The basic read and write sequences are [Q3](#q3-what-is-the-sequence-for-reading-a-register-over-i2c) and [Q4](#q4-can-you-write-to-a-register-of-an-i2c-slave), and arbitration is [Q9](#q9-what-is-i2c-arbitration).

### Q50. How does the master talk to one particular slave when many share the bus?

**Also asked as:** *What is required to select a particular I2C slave?*

**In simple words:** After START, the master sends the 7-bit address. Every slave compares it with its own address. **Only the slave that matches pulls SDA low** on the ACK bit.

**Example:** The master sends 0x68. The MPU6050 at 0x68 ACKs; the BME280 at 0x76 stays silent and ignores the rest.

> "Through the **address**. After START, the master sends the 7-bit address plus the read/write bit. Every slave on the bus listens, compares it with its own address, and only the one that matches sends ACK. All the others just ignore the rest of the transaction until the next START. That's why every slave on one bus needs a unique address."

**Cross-questions:**

1. **How many devices can a 7-bit address support?**
   "128 addresses, minus 16 reserved ones (0x00 to 0x07 and 0x78 to 0x7F), so **112**. The real limit is usually the 400 pF bus capacitance."
2. **How does 10-bit addressing work?**
   "The first byte is `11110` plus the top 2 address bits and R/W, and the second byte has the remaining 8 bits. It's rarely used."
3. **What is the general call address?**
   "0x00 is a broadcast to all devices, for example a reset command. Devices that support it ACK it."

### Q51. What happens when a slave doesn't acknowledge (NACK)?

**In simple words:** The ACK is SDA pulled **low by the receiver on the 9th clock**.

If SDA stays high, it is a NACK. It means the receiver is missing, busy, or refusing the data.

There is one exception: at the end of a read, the master sends a NACK on purpose to say it wants no more data.

**Example:** An EEPROM at 0x50 NACKs its address for about 5 ms after every write, while it's busy writing internally.

> "It depends on when it happens.
>
> If the slave NACKs the **address**, it usually means nothing is there: wrong address, the device isn't powered, or it's busy. An EEPROM, for example, NACKs while it's doing its internal write. If it NACKs a **data byte** during a write, it can't accept more data. In both cases the master sends STOP and the driver returns an error, and maybe retries.
>
> But a NACK at the **end of a read** is completely normal. That's the master saying 'that was my last byte'."

| NACK on... | Meaning | What the master does |
| --- | --- | --- |
| **The address byte** | No device at that address, it's busy (e.g. an EEPROM in its write cycle), or the address is wrong | Sends STOP; the driver returns an error (e.g. `-ENXIO` on Linux, `HAL_ERROR` on STM32) and may retry |
| **A data byte, during a write** | The slave can't accept more (buffer full, invalid register, error) | Sends STOP and reports the error |
| **The last byte, during a read** | **Normal**: the **master** NACKs to say "that's the last byte" | Sends STOP |

**Cross-questions:**

1. **What's a good retry strategy after a NACK?**
   "A few retries with a short delay, especially for EEPROMs in their write cycle. Then return a clear error to the caller. Never loop forever, because one missing sensor must not hang the whole system."
2. **The bus is stuck after errors. How do you recover it?**
   "Toggle SCL up to 9 times until the slave releases SDA, then send STOP. The details are in [Q58](#q58-i2c-is-set-to-400-khz-but-communication-is-unreliable-what-do-you-check)."

### Q52. How are bytes sent over I2C? For example, how is a 10-byte buffer transferred, bit by bit?

**Also asked as:** *How many bits/clocks are needed for the address and 10 bytes?* · *How are the 80 data bits physically shifted onto the bus?* · *How does the I2C peripheral convert bytes into bits?* · *How does the slave rebuild the bits into bytes?*

**In simple words:** The I2C peripheral loads each byte into a **shift register**. It shifts the bits out one per SCL clock, MSB first.

After the 8 data clocks, there is a **9th clock for the ACK bit**. So each byte takes 9 clocks.

**Example:** 0xA5 = 1010 0101 goes out MSB first: 1, 0, 1, 0, 0, 1, 0, 1, then the ACK clock. 10 bytes plus the address is 99 clocks: about 1 ms at 100 kHz, or 0.25 ms at 400 kHz.

> "Each byte goes out **MSB first**, one bit per clock, and then there's a **9th clock for the ACK**. Data on SDA only changes while SCL is low, and the receiver samples it while SCL is high.
>
> Inside the chip, the driver writes a byte into the data register, and the hardware moves it into a **shift register**, which pushes the bits out one by one. When it's free again, it raises a flag, the interrupt or DMA puts in the next byte, and so on. The slave does the opposite: it shifts in 8 bits, then pulls SDA low on the 9th clock to ACK.
>
> So for 10 bytes it's 9 clocks for the address, plus 10 times 9 for the data. That's **99 clocks**, about 1 millisecond at 100 kHz."

| Part | Bits | SCL clocks |
| --- | --- | --- |
| START | – | (a condition, not a clock) |
| Address (7 bits) + W (1 bit) + ACK | 8 + 1 | 9 |
| 10 data bytes, each + ACK | 10 × (8 + 1) | 90 |
| STOP | – | (a condition) |
| **Total** | **80 data bits** + 8 address bits + 11 ACKs | **99 clocks** |

If the slave needs a register address first, add one more byte: 108 clocks.

**Cross-questions:**

1. **Why may SDA only change while SCL is low?**
   "Because a change of SDA while SCL is high is, by definition, a **START** (falling SDA) or a **STOP** (rising SDA). That's how those conditions are recognized."
2. **Is there a maximum number of bytes per transaction?**
   "The protocol has no limit. The device sets it, for example an EEPROM's page size."
3. **10 bytes: interrupt or DMA?**
   "10 bytes is fine with interrupts. I use DMA for large blocks, or when the CPU has better things to do."

### Q53. How does the ACK bit work? Who generates it?

**Also asked as:** *Who generates the ACK during an I2C write?* · *Who generates the ACK during an I2C read?*

**In simple words:** The device that **receives** the byte sends the ACK:

- On a **write**, the slave receives, so the slave sends the ACK.
- On a **read**, the master receives, so the master sends the ACK.

**Example:** Writing 3 bytes to a sensor: the sensor ACKs the address and all 3 bytes. Reading 3 bytes: the sensor ACKs the address, the MCU ACKs bytes 1 and 2, and NACKs byte 3 before STOP.

> "The simple rule is: **whoever receives the byte sends the ACK**. On the 9th clock, the sender lets go of SDA, and the receiver pulls it low to say 'got it'. If SDA stays high, that's a NACK.
>
> So on a **write**, the slave ACKs every byte. On a **read**, the slave ACKs the address, but then the **master** ACKs each data byte, and NACKs the last one to end the read."

| Transfer | Address byte ACKed by | Data bytes ACKed by |
| --- | --- | --- |
| **Write** (master → slave) | Slave | **Slave** |
| **Read** (slave → master) | Slave | **Master**, except the last byte, which the master NACKs |

**Cross-questions:**

1. **What exactly is the timing of the ACK?**
   "The receiver pulls SDA low before the 9th clock goes high and holds it low for the whole high period, so the transmitter reads a stable 0."
2. **Is there an ACK for START and STOP?**
   "No. They're conditions, not bytes, so there's nothing to acknowledge."

### Q54. What is clock stretching, why is it needed, and how does the slave hold SCL low?

**Also asked as:** *Why is clock stretching required?* · *How does a slave physically hold SCL low?*

**In simple words:** SCL is open-drain, so a slave can **hold it low** after the master releases it.

The master reads SCL back, and it does not continue until SCL goes high. This lets a slow slave pause the transfer.

**Example:** An SHT31 humidity sensor in clock-stretching mode holds SCL low during the measurement, for about 15 ms, and the master simply waits.

> "Clock stretching is the slave saying 'wait, I'm not ready'. It does that by **holding SCL low**. For example, a sensor that's still doing a conversion, or a small MCU acting as a slave that needs time to handle the byte.
>
> It works because SCL is **open-drain**. The master doesn't drive SCL high; it just releases it and expects the pull-up to bring it up. Then it reads SCL back. If the slave is still holding it low, the master sees low and waits. When the slave releases it, the clock continues.
>
> In my drivers I always put a **timeout** on it, because a stuck slave can otherwise hang the whole bus."

```text
Master releases SCL → pull-up should raise it → slave still holds it LOW → master reads LOW, waits
                    → slave releases → SCL goes HIGH → transfer continues
```

**Cross-questions:**

1. **How long can a slave stretch the clock?**
   "The I2C spec has no limit. SMBus defines a timeout of 25 to 35 ms, and I add my own timeout in the driver."
2. **Do all masters support clock stretching?**
   "No. The Raspberry Pi's original I2C controller famously had a bug with it. A bit-banged master must read SCL back after releasing it, otherwise it ignores stretching."
3. **When in a byte does a slave usually stretch?**
   "Most often after the ACK, between bytes: the slave holds SCL low while it processes the byte it just received, or prepares the next one to send."

### Q55. With several masters, how does arbitration work, and how does a master know it lost?

**Also asked as:** *What is I2C arbitration?* · *How does a master know that it has lost arbitration?*

**In simple words:** Each master compares the level it reads on SDA with the bit it sent. If they are different, the hardware sets an **arbitration-lost flag** and stops driving the bus.

**Example:** Two MCUs share a battery fuel gauge. MCU A gets the ARLO flag, waits until the bus is free, and retries 1 ms later.

> "Like I said in [Q9](#q9-what-is-i2c-arbitration): each master checks SDA while it sends, and if it sent a 1 but sees a 0, it has lost. In practice the I2C peripheral detects that for me. On an STM32 it sets the **ARLO**, arbitration lost, flag and fires an interrupt. My driver then backs off, waits until the bus is free again, meaning a STOP has been seen, and **retries** the transfer."

**Cross-questions:**

1. **Can arbitration continue into the data bytes?**
   "Yes. If both masters address the same slave, arbitration simply continues bit by bit into the data, until one of them sends a different bit."
2. **What about the clock with two masters?**
   "That's clock synchronization, explained in the [Q9 cross-questions](#q9-what-is-i2c-arbitration)."

---

## 15. I2C speed

### Q56. What are the I2C speed modes, and what limits the speed?

**Also asked as:** *What factors determine I2C bus speed?* · *What are Standard mode, Fast mode, Fast-mode Plus and High-speed mode?*

**In simple words:** The bus speed is the **SCL frequency**. Two things limit it:

- The **slowest device** on the bus.
- The **rise time** of the lines. This depends on the pull-up resistance multiplied by the bus capacitance.

**Example:** A bus with a sensor rated for 400 kHz and an old EEPROM rated for 100 kHz has to run at 100 kHz.

> "The common ones are **Standard mode at 100 kHz** and **Fast mode at 400 kHz**, which most sensors support. Then there's **Fast-mode Plus at 1 MHz** and **High-speed mode at 3.4 MHz**, but those are less common.
>
> What really limits the speed is the **rise time**. Because the bus is open-drain, the line is pulled high only by a resistor, and the bus capacitance slows it down. So the pull-up value, the trace length and the number of devices all matter. And of course the **slowest device** on the bus sets the limit."

| Mode | Speed | Max rise time |
| --- | --- | --- |
| **Standard mode** | 100 kHz | 1000 ns |
| **Fast mode** | 400 kHz | 300 ns |
| **Fast-mode Plus** | 1 MHz | 120 ns |
| **High-speed mode** | 3.4 MHz | Special start sequence, active pull-ups |

**Cross-questions:**

1. **What's special about High-speed mode?**
   "The master first sends a special **master code** at fast-mode speed, which also does the arbitration. Then it switches to 3.4 MHz, with current-source pull-ups to make the edges fast enough. After STOP, the bus drops back to normal speed."
2. **What makes up the bus capacitance?**
   "About 10 pF per device pin, plus the traces (roughly 1 pF per cm) and any cable. The limit is 400 pF in standard and fast mode."
3. **What's different about Fast-mode Plus?**
   "Its drivers can sink 20 mA instead of 3 mA, so I can use much stronger pull-ups, which make the edges fast enough for 1 MHz on a normal bus."

### Q57. How do you switch I2C from 100 kHz to 400 kHz?

**Also asked as:** *What needs to change in the MCU configuration to change the I2C speed?* · *What electrical factors must be checked when increasing the I2C speed?*

**In simple words:** Changing the speed has two parts:

1. **Software:** recalculate the SCL high and low times from the peripheral clock, and write them to the timing registers.
2. **Hardware:** check that the rise time of the lines meets the limit of the faster mode.

**Example:** 200 pF bus with 4.7 kΩ pull-ups: rise time = 0.8473 × 4.7 kΩ × 200 pF ≈ **800 ns**, too slow (the limit is 300 ns). With 1.5 kΩ: ≈ **254 ns**, OK.

> "There are two sides to it.
>
> **In software**, I change the I2C timing registers. With the STM32 HAL it's just `ClockSpeed = 400000` in the init struct. Underneath, on an F4, that sets fast mode and recalculates the clock divider and the rise-time register from the peripheral clock. On newer STM32s it's one TIMINGR value, which I generate with CubeMX.
>
> **In hardware**, I make sure every slave on the bus supports 400 kHz, and that the signal edges are fast enough. That usually means **smaller pull-ups**, like going from 4.7k to 2.2k. Then I check the edges on a scope to confirm the rise time is under 300 ns."

Largest pull-up that still meets the rise time: **Rp(max) = tr / (0.8473 × Cbus)**. For 300 ns and 200 pF: about **1.8 kΩ**.

**Cross-questions:**

1. **Where does the pull-up formula come from?**
   "The rise time is measured from 30 % to 70 % of VDD, and for an RC circuit that's **tr = 0.8473 × Rp × Cb**. Solve for Rp to get the largest allowed value."
2. **Is there a minimum pull-up value?**
   "Yes. When a device pulls the line low, it must sink the current within its rating, 3 mA in standard and fast mode: **Rp(min) = (VDD − 0.4 V) / 3 mA**, about 1 kΩ at 3.3 V. Below that, the low level isn't low enough."
3. **How do you know the bus capacitance?**
   "Estimate it from the pins and trace length, or measure the rise time on a scope with a known pull-up and solve the formula for Cb."

### Q58. I2C is set to 400 kHz but communication is unreliable. What do you check?

**In simple words:** At a higher speed, each signal edge has less time to rise. If the rise time is too long, because the pull-ups are too weak or the capacitance is too high, the bits are sampled at the wrong level.

This shows up as random NACKs and corrupted data.

**Example:** The scope shows rising edges taking 600 ns. Changing the pull-ups from 10 kΩ to 2.2 kΩ makes them sharp, and the errors disappear.

> "First thing, I put a **scope** on SCL and SDA. If the rising edges look like shark fins, slow and rounded, the pull-ups are too weak or there's too much capacitance, so I go to stronger pull-ups or a shorter bus.
>
> Then I check that every device really supports 400 kHz, and whether one of them is doing clock stretching that the master doesn't handle. I also check ground and noise.
>
> A quick test is to drop back to 100 kHz. If it works there, it's almost certainly signal integrity. And if SDA gets stuck low after an error, I recover the bus by toggling SCL nine times."

**Cross-questions:**

1. **Why does SDA get stuck low?**
   "If the master resets in the middle of a read, the slave is still halfway through sending a byte, and if its current bit is 0 it keeps holding SDA low. It just needs more clocks to finish. So I toggle SCL up to 9 times until SDA goes high, then send STOP."
2. **What if devices run at different voltages, like 1.8 V and 3.3 V?**
   "Then I need a **level shifter** made for I2C, like the PCA9306 or the classic MOSFET circuit. It's bidirectional and keeps the open-drain behaviour."
3. **What about long cables?**
   "Plain I2C isn't meant for that. I'd use a bus buffer or extender, like the P82B715, or a differential I2C extender. Or switch to a protocol built for distance, like RS-485 or CAN."

---

## 16. SPI modes and choosing an interface

The SPI pins and checklist are in [Q1](#q1-how-do-you-configure-an-i2c-or-spi-peripheral), and SPI frames in [Q38](#q38-how-do-you-split-bifurcate-an-spi-frame-how-many-bytes-are-command-address-and-data).

### Q59. What are CPOL and CPHA, and what are the four SPI modes?

**Also asked as:** *What is SPI clock phase (CPHA)?* · *What is the difference between SPI Mode 0 and Mode 1?*

**In simple words:** - **CPOL** is the level of SCLK when it is **idle**.
- **CPHA** decides whether data is read on the **first or the second** clock edge after CS goes low.

The master and the slave must use the same CPOL and CPHA. Otherwise they read the data at the wrong moment.

**Example:** Mode 0: the clock idles low, and data is read on the rising edge. The MCP3008 ADC supports mode 0 and mode 3, so the master must use one of those.

> "**CPOL** is where the clock sits when it's idle: low for 0, high for 1. **CPHA** says which edge the data is sampled on: the first edge for 0, the second edge for 1. Two bits give four modes.
>
> **Mode 0** is the most common: the clock idles low and data is sampled on the rising edge. **Mode 1** also idles low, but samples on the falling edge.
>
> The device datasheet tells you which mode it uses, and if the master gets it wrong you usually see data that's shifted by one bit, or just garbage. That's one of the first things I check when SPI doesn't work."

| Mode | CPOL | CPHA | Clock idle | Data sampled on | Data changes on |
| --- | --- | --- | --- | --- | --- |
| **0** | 0 | 0 | Low | **Rising** edge (first) | Falling edge |
| **1** | 0 | 1 | Low | **Falling** edge (second) | Rising edge |
| **2** | 1 | 0 | High | Falling edge (first) | Rising edge |
| **3** | 1 | 1 | High | Rising edge (second) | Falling edge |

**Cross-questions:**

1. **How do you find the mode in a datasheet?**
   "From the **timing diagram**: the clock level when CS goes low gives CPOL, and the edge where the data is stable, in the middle of the bit, is the sampling edge, which gives CPHA. Many datasheets also just say 'supports mode 0 and 3'."
2. **What do you see if the mode is wrong?**
   "Typically the data is shifted by one bit, so values look doubled or halved, or the first bit is lost. Sometimes it works at low speed and fails at high speed, because the timing margin is gone."
3. **Can devices with different modes share one bus?**
   "Yes, as long as the master switches modes before each transaction, as in [Q40](#q40-several-devices-on-one-spi-bus-with-separate-readwrite-operations-how-do-you-design-the-driver)."
4. **What else besides the mode must match?**
   "The bit order (MSB or LSB first), the frame size (8 or 16 bits), the maximum clock speed, and the CS setup and hold times."

### Q60. A sensor supports both I2C and SPI. Which would you choose?

**Also asked as:** *What factors do you consider when choosing between I2C and SPI?* · *When would you prefer SPI over I2C, and when I2C over SPI?*

**In simple words:** - **SPI** is faster and simpler. It is push-pull, full duplex and has no addressing. But it needs one CS pin for each device.
- **I2C** needs only two wires for many devices, and every byte is acknowledged. But it is slower, and device addresses can clash.

**Example:** A BMI270 IMU sampling at 1.6 kHz → SPI. A temperature sensor read once a second → I2C.

> "It depends on the application, but my thinking goes like this.
>
> If I need **speed**, like an IMU sampling at a few kHz, or a display, or flash, I go with **SPI**. It runs at tens of MHz, it's full duplex, and it's push-pull, so the edges are clean.
>
> If the data is slow, like reading a temperature once a second, and I'm short on pins, I go with **I2C**. Two wires for any number of devices, and I get an ACK on every byte, so I know the device is there.
>
> The downside of SPI is one extra CS pin per device. The downside of I2C is the speed, and possible address conflicts."

| Factor | SPI | I2C |
| --- | --- | --- |
| Speed | Fast: tens of MHz, full duplex | 100 kHz to 1 MHz typically |
| Pins | 4, plus one CS per device | 2 for any number of devices |
| Addressing | CS pin per device: no conflicts | Address per device: conflicts possible |
| Acknowledge | None (check with a status/ID read) | ACK on every byte |
| Typical devices | IMUs, displays, flash, ADCs | Temperature sensors, EEPROMs, RTCs, PMICs |

**Cross-questions:**

1. **SPI has no ACK. How do you know the device is there?**
   "I read the device-ID register at start-up and check it. Some devices also have a status register or a CRC on the data, which I check during operation."
2. **What's daisy-chaining in SPI?**
   "Connecting MISO of one device to MOSI of the next, all sharing one CS. The data shifts through all the devices like one long shift register. LED drivers and shift registers often work like this."
3. **Which one uses less power?**
   "I2C pull-ups burn current every time a line is low, so for very low power SPI can be better, or I use higher-value pull-ups at a lower speed."

---

## 17. 1-Wire protocol

### Q61. What is the 1-Wire protocol?

**In simple words:** 1-Wire uses **one data line** with a pull-up resistor. The line is open-drain, and the bits are coded only by **timing**.

Each device has a unique **64-bit ID**, set in the factory. The master uses this ID to address the device.

**Example:** Ten DS18B20 sensors on one wire in a cold-storage room, each read by its own 64-bit ID.

> "It's a Maxim protocol, now Analog Devices, that uses just **one data wire plus ground**. The line is open-drain with a pull-up, and some devices even take their power from the data line itself.
>
> There's one master and as many slaves as you like, and each slave has a unique **64-bit ID** burned in at the factory, so you never get address conflicts. It's slow, around 15 kbps, but it's great for things like temperature sensors over long wires. The DS18B20 is the classic example."

**Cross-questions:**

1. **What is parasitic power?**
   "The device charges an internal capacitor from the data line while it's high, so it needs no separate power wire. During heavy work, like a temperature conversion, the master must give it a **strong pull-up**, usually a MOSFET, because the resistor alone can't supply enough current."
2. **How do you find all the devices on the bus?**
   "With the **Search ROM** command. It's a binary-tree search: for each bit of the 64-bit ID, all devices send the bit and its complement, the master detects conflicts, and it picks a branch. Repeating it finds every ID."
3. **How do you check the data is correct?**
   "Both the ROM ID and the DS18B20 scratchpad end with a **CRC-8** (polynomial X⁸ + X⁵ + X⁴ + 1). I always check it, because long wires pick up noise."

### Q62. How does the master start communication, and what happens in software?

**Also asked as:** *How does communication happen between a 1-Wire master and slave?*

**In simple words:** Every transaction starts the same way:

1. **Reset:** the master pulls the line low for at least 480 µs.
2. **Presence:** every device answers by pulling the line low for a short time.
3. **ROM command:** the master selects a device.
4. **Function command:** the master tells that device what to do.

**Example:** Reset → presence → 0xCC (Skip ROM) → 0x44 (Convert T) → wait 750 ms → reset → presence → 0xCC → 0xBE (Read Scratchpad) → read 9 bytes.

> "Every transaction starts with a **reset**. The master pulls the line low for at least 480 microseconds and releases it. If there's a device, it answers with a **presence pulse**, pulling the line low for a short time. That's how I know something is there.
>
> Then I send a **ROM command** to choose the device. With only one device I use Skip ROM, 0xCC; with several I use Match ROM, 0x55, plus the 64-bit ID. After that comes the **function command**, like Convert T, 0x44, and then Read Scratchpad, 0xBE, on a DS18B20.
>
> In software I usually **bit-bang** a GPIO in open-drain mode with microsecond delays, and I **disable interrupts** during each bit, because the timing is tight."

```text
Reset (≥480 µs low) → presence pulse → ROM command (0xCC / 0x55 + ID) → function command (0x44, 0xBE ...)
```

**Cross-questions:**

1. **Why disable interrupts, and what's the cost?**
   "If an ISR delays me even a few microseconds at the wrong moment, a 'write 1' becomes a 'write 0'. The cost is up to about 70 µs of interrupt latency per bit, so I disable interrupts **per bit**, not for a whole byte, to keep the latency bounded."
2. **How does the UART trick work?**
   "For the reset I set 9600 baud and send 0xF0: the start bit plus the zero bits make the long low pulse, and a device's presence pulse changes the byte I read back. For the bits I switch to 115200 baud: sending 0xFF makes a short low pulse, which is a 1, and 0x00 makes a long one, which is a 0. To read, I send 0xFF: if it comes back as 0xFF the bit was 1, otherwise 0. The UART does all the timing in hardware."
3. **How long does a DS18B20 conversion take?**
   "Up to 750 ms at 12-bit resolution. So I start the conversion, do other work, and read the result later. I don't block for 750 ms."

### Q63. How is a byte sent, and how does the receiver tell a 0 from a 1?

**Also asked as:** *How are the timing and high/low levels handled so the receiver can interpret the byte?*

**In simple words:** Every bit is a **time slot**, and the master starts each slot by pulling the line low.

- A **short** low pulse (about 6 µs) means 1.
- A **long** low pulse (about 60 µs) means 0.

The slave checks the line about 15 to 30 µs after the falling edge. If the line is already high, the bit is 1; if it is still low, the bit is 0.

**Example:** Sending 0xCC (1100 1100) LSB first gives the bits 0, 0, 1, 1, 0, 0, 1, 1, which is long, long, short, short, long, long, short, short.

> "There's no clock line, so it's all about **timing**. Every bit is a time slot of about 60 microseconds, and the master always starts it by pulling the line low.
>
> To write a **1**, the master pulls low just briefly, a few microseconds, and lets go. To write a **0**, it holds the line low for the whole slot. The slave looks at the line about 15 to 30 microseconds after the falling edge: if it's already high, it's a 1; if it's still low, it's a 0.
>
> To **read**, the master pulls low briefly and releases, then samples within 15 microseconds. If the slave wants to send a 0, it holds the line low; for a 1 it does nothing. Bytes go **LSB first**."

| Slot | Master does | Line during the sample window | Meaning |
| --- | --- | --- | --- |
| **Write 1** | Pulls low **1-15 µs**, then releases | High (pulled up) | 1 |
| **Write 0** | Pulls low for the **whole slot (60-120 µs)** | Low | 0 |
| **Read** | Pulls low **≥1 µs**, releases, **samples within 15 µs** | Slave holds it low = **0**, leaves it high = **1** | The slave's bit |

```c
#include <stdio.h>
#include <stdint.h>

/* ======================= Platform layer =======================
 * On the MCU these drive an open-drain GPIO, a microsecond timer and the interrupt mask.
 * For this PC demo they simulate the line and one 1-Wire slave that decodes the pulse widths. */

static uint32_t sim_time_us   = 0U;     /* simulated time                          */
static uint32_t sim_low_start = 0U;     /* when the master last pulled the line low */
static uint8_t  sim_rx_byte   = 0U;     /* byte the slave is receiving             */
static uint8_t  sim_rx_bits   = 0U;
static uint8_t  sim_tx_byte   = 0xA5U;  /* byte the slave will send when read      */
static uint8_t  sim_tx_bits   = 0U;
static uint8_t  sim_reading   = 0U;     /* 1 while the master is in a read slot    */

static void __disable_irq(void) { }
static void __enable_irq(void)  { }

static void delay_us(uint32_t us)
{
    sim_time_us += us;
}

static void ow_line_low(void)
{
    sim_low_start = sim_time_us;
}

/* The slave measures how long the line was low: short = 1, long = 0 */
static void ow_line_release(void)
{
    if (sim_reading == 0U)
    {
        const uint32_t low_us = sim_time_us - sim_low_start;
        const uint8_t  bit    = (low_us < 15U) ? 1U : 0U;

        sim_rx_byte |= (uint8_t)(bit << sim_rx_bits);     /* LSB first */
        sim_rx_bits++;
    }
}

/* In a read slot the slave holds the line low for ~30 us to send a 0, or leaves it high for a 1 */
static uint8_t ow_line_read(void)
{
    const uint8_t bit = (uint8_t)((sim_tx_byte >> sim_tx_bits) & 0x01U);
    uint8_t       level = 1U;

    if ((bit == 0U) && ((sim_time_us - sim_low_start) < 30U))
    {
        level = 0U;
    }
    sim_tx_bits++;
    return level;
}

/* ======================= 1-Wire bit and byte layer ======================= */
#define OW_W1_LOW_US    (6U)     /* write 1: short low pulse               */
#define OW_W1_REST_US   (64U)    /*          rest of the slot + recovery    */
#define OW_W0_LOW_US    (60U)    /* write 0: low for the whole slot         */
#define OW_W0_REST_US   (10U)    /*          recovery                       */
#define OW_R_LOW_US     (6U)     /* read:    master starts the slot         */
#define OW_R_SAMPLE_US  (9U)     /*          sample ~15 us after the edge   */
#define OW_R_REST_US    (55U)    /*          finish the slot                */

static void ow_write_bit(uint8_t bit)
{
    __disable_irq();                        /* an ISR here would stretch the timing */
    ow_line_low();
    if (bit != 0U)
    {
        delay_us(OW_W1_LOW_US);             /* short pulse = 1 */
        ow_line_release();
        delay_us(OW_W1_REST_US);
    }
    else
    {
        delay_us(OW_W0_LOW_US);             /* long pulse = 0  */
        ow_line_release();
        delay_us(OW_W0_REST_US);
    }
    __enable_irq();
}

static uint8_t ow_read_bit(void)
{
    uint8_t bit;

    __disable_irq();
    sim_reading = 1U;
    ow_line_low();
    delay_us(OW_R_LOW_US);
    ow_line_release();
    delay_us(OW_R_SAMPLE_US);
    bit = ow_line_read();                   /* slave holds low = 0, released = 1 */
    delay_us(OW_R_REST_US);
    sim_reading = 0U;
    __enable_irq();

    return bit;
}

/* Bytes go LSB first */
static void ow_write_byte(uint8_t value)
{
    uint8_t i;

    for (i = 0U; i < 8U; i++)
    {
        ow_write_bit((uint8_t)((value >> i) & 0x01U));
    }
}

static uint8_t ow_read_byte(void)
{
    uint8_t i;
    uint8_t value = 0U;

    for (i = 0U; i < 8U; i++)
    {
        value |= (uint8_t)(ow_read_bit() << i);     /* first bit received is bit 0 */
    }

    return value;
}

int main(void)
{
    uint8_t received;

    ow_write_byte(0xCCU);                                         /* Skip ROM command */
    (void)printf("master sent 0xCC, slave decoded 0x%02X\n", (unsigned int)sim_rx_byte);

    received = ow_read_byte();
    (void)printf("slave sent 0x%02X, master read 0x%02X\n", (unsigned int)sim_tx_byte, (unsigned int)received);
    (void)printf("16 bit slots took %lu us\n", (unsigned long)sim_time_us);

    return 0;
}
```

**Output:**

```text
master sent 0xCC, slave decoded 0xCC
slave sent 0xA5, master read 0xA5
16 bit slots took 1120 us
```

**Cross-questions:**

1. **How do you make microsecond delays?**
   "Not with `HAL_Delay()`, that's in milliseconds. I use a hardware timer, or the Cortex-M **DWT cycle counter**, which counts CPU cycles, so at 100 MHz, 100 counts is 1 µs."
2. **What is the recovery time?**
   "At least 1 µs with the line high between slots, so the pull-up can recharge the line, and the parasitic-powered devices their capacitor."

---

## 18. USB

### Q64. USB host vs USB device?

**Also asked as:** *Do you have experience with USB peripherals?*

**In simple words:** USB is **controlled by the host**. The host starts every transfer by sending a token packet. A device sends data only when it receives an IN token from the host.

**Example:** A PC (host) sends an IN token to a keyboard's interrupt endpoint every 10 ms. The keyboard returns a key report, or NAK if no key changed.

> "The **host** is the boss. It powers the bus, enumerates the devices, and starts every single transfer; a device can never just send data on its own, it waits to be polled. A PC is a host, a keyboard is a device. An **OTG** port can switch between the two roles.
>
> On MCUs I've mostly done the **device** side, like a virtual COM port with CDC, or a HID device."

**Cross-questions:**

1. **What are the USB speeds?**
   "Low speed 1.5 Mbit/s, Full speed 12 Mbit/s, High speed 480 Mbit/s, and SuperSpeed 5 Gbit/s and up with USB 3. Most MCUs have Full speed built in; High speed usually needs an external PHY."
2. **How much current can a bus-powered device take?**
   "On USB 2.0, 100 mA before it's configured, and up to 500 mA after, if its configuration descriptor asks for it."
3. **Can two USB devices talk to each other directly?**
   "No, there must always be a host. That's why OTG and dual-role ports exist: one side becomes the host."
4. **What did you do with USB?**
   *(Fill in your own project, for example a CDC virtual COM port with the STM32 USB device middleware, or a HID device.)*

### Q65. How does USB enumeration work? What happens when a device is plugged in?

**Also asked as:** *What happens when a USB device is connected to the host?*

**In simple words:** Enumeration is the setup the host does when a device is connected:

1. The host reads the device's **descriptors**, using the default address 0.
2. It gives the device a **unique address**.
3. It selects a **configuration** and loads a driver.

**Example:** You plug in an STM32 CDC device, and a few hundred milliseconds later Windows shows "USB Serial Device (COM5)".

> "When I plug it in, the device turns on a pull-up on D+ or D−, and that's how the host knows something is connected, and at what speed. The host resets it, and the device starts at **address 0**.
>
> Then the host asks for the **device descriptor**, gives it a unique address with **SET_ADDRESS**, and reads the rest: the configuration, interface, endpoint and string descriptors. Using the VID and PID, or the class, the host loads the right driver. Finally it sends **SET_CONFIGURATION**, and the device is ready to use."

```text
Attach (pull-up on D+/D−) → bus reset → address 0 → GET device descriptor → SET_ADDRESS
→ GET configuration / interface / endpoint / string descriptors → load driver → SET_CONFIGURATION
```

**Cross-questions:**

1. **Why does the host first ask for only 8 bytes?**
   "Those first 8 bytes contain `bMaxPacketSize0`, the size of endpoint 0's packets, which the host needs to know before it can read the rest correctly."
2. **Enumeration fails on Windows with 'device descriptor request failed'. What do you check?**
   "First the **clock**: Full-speed USB needs 48 MHz within ±0.25 %, so a crystal, or HSI48 with clock recovery (CRS) on parts that have it. Then the D+ pull-up, VBUS sensing, and the descriptors: wrong lengths or a wrong total length in the configuration descriptor break enumeration. A USB protocol analyzer or Wireshark with USBPcap shows exactly which request failed."
3. **What are the VID and PID for?**
   "The host uses them to choose the driver. A product needs its own VID from the USB-IF, or a PID from the chip vendor's range."

### Q66. What are descriptors and endpoints?

**In simple words:** - **Descriptors** are data structures stored in the device's firmware. They describe the device, its configurations, its interfaces and its endpoints.
- An **endpoint** is a buffer in the device's USB hardware. It has a number and a direction, and it is where a transfer starts or ends.

**Example:** A CDC device: EP0 for control, EP1 IN bulk (data to the PC), EP1 OUT bulk (data from the PC), EP2 IN interrupt (status notifications).

> "**Descriptors** are basically the device's CV. They tell the host who the device is, the VID and PID, what it can do, how much power it needs, and which endpoints it has.
>
> An **endpoint** is a buffer on the device side, a source or destination for data. Each one has a number and a direction: IN means to the host, OUT means from the host. **Endpoint 0** is always there, it's bidirectional, and it's used for control and enumeration."

| Descriptor | Describes |
| --- | --- |
| **Device** | VID, PID, USB version, class, endpoint 0's packet size, number of configurations |
| **Configuration** | Power needs, and the interfaces it contains |
| **Interface** | One function and its class (CDC, HID, mass storage ...) |
| **Endpoint** | Address, direction, transfer type, maximum packet size, polling interval |
| **String** | Human-readable names: manufacturer, product, serial number |

**Cross-questions:**

1. **How many endpoints can a device have?**
   "The protocol allows 16 numbers, each IN and OUT. The MCU's hardware usually supports fewer, for example 4 to 6 on a Full-speed STM32."
2. **What is a device class, and why use one?**
   "A standard behaviour, like CDC, HID, mass storage, audio or DFU. The OS already has the driver, so the user doesn't need to install anything."
3. **What is a composite device?**
   "One device with several interfaces, like CDC plus HID together. It uses an **interface association descriptor** to group the interfaces of one function."
4. **What are the maximum packet sizes?**
   "64 bytes for bulk at Full speed, 512 bytes at High speed. Endpoint 0 is 8 to 64 bytes at Full speed."

### Q67. What are the USB transfer types?

**In simple words:** USB has four transfer types. They differ in what they guarantee:

- **Control:** reliable; used for setup and commands.
- **Bulk:** reliable, but with no timing guarantee.
- **Interrupt:** reliable, with a guaranteed maximum delay.
- **Isochronous:** guaranteed bandwidth, but lost data is not resent.

**Example:** USB stick → bulk. Mouse → interrupt. USB microphone → isochronous. Enumeration → control.

> "There are four. **Control** is for setup and commands, on endpoint 0. **Bulk** is for large amounts of data where timing doesn't matter, like a USB stick or a virtual COM port; it's reliable, but it only uses spare bandwidth. **Interrupt** is for small data that needs a guaranteed polling interval, like a keyboard or mouse. And **isochronous** gets fixed bandwidth but no retries, for audio and video, because late data is useless anyway."

| Type | Guarantees | Used for |
| --- | --- | --- |
| **Control** | Reliable, error-checked; on endpoint 0 | Enumeration, configuration commands |
| **Bulk** | Reliable, but **no timing guarantee** | Mass storage, CDC serial data, printers |
| **Interrupt** | Reliable, with a **maximum polling interval** | Keyboards, mice, HID devices |
| **Isochronous** | **Fixed bandwidth**, no retries | Audio, video |

**Cross-questions:**

1. **Which type for a sensor streaming data?**
   "Bulk if every sample must arrive and timing is loose. Interrupt for small, regular readings with bounded latency. Isochronous for audio-like streams, where late data is useless."
2. **Why is it called 'interrupt' if the host polls?**
   "Because a USB device can never interrupt the host. The host polls the endpoint at the `bInterval` rate, so the device gets guaranteed, regular service, which works like an interrupt."
3. **How does a device send data on a bulk IN endpoint?**
   "It loads the data into the endpoint buffer. When the host sends an IN token, the hardware sends it. If nothing is loaded, the device answers NAK, and the host tries again later."

---

## 19. Register-level GPIO driver (no HAL)

### Q68. An MCU has no vendor library, only a register map. How do you write a GPIO driver?

**Also asked as:** *If the GPIO base address is 0x80040000, how would you create a C structure for the registers?* · *How would you implement GPIO read, write and toggle functions?*

**In simple words:** Peripheral registers sit at **fixed addresses** in the memory map.

I write a struct with one `volatile uint32_t` member per register, in the same order as the registers. Then I cast the base address to a pointer to that struct. Now each register can be accessed by name.

**Example:** Base 0x80040000, OUT at offset 0x08. So `GPIOA->OUT = x;` writes to address **0x80040008**.

> "I start from the reference manual: the GPIO **base address** and the **register offsets**. Then I write a C **struct** with one `volatile uint32_t` per register, in the same order as the manual, and cast the base address to a pointer to that struct. Now `GPIOA->OUT` reads and writes the real hardware register.
>
> On top of that I write small functions: set the direction, write, read and toggle a pin. If the chip has separate set and clear registers, I use them, because they're atomic."

Example with a GPIO block at **`0x80040000`** (the register layout is an example; use the one in your chip's manual):

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Register layout: an example; take the real one from the chip's reference manual */
typedef struct
{
    volatile uint32_t DIR;      /* 0x00: direction, 1 = output, 0 = input */
    volatile uint32_t IN;       /* 0x04: input level (read-only)          */
    volatile uint32_t OUT;      /* 0x08: output level                     */
    volatile uint32_t SET;      /* 0x0C: write 1 = drive the pin high     */
    volatile uint32_t CLR;      /* 0x10: write 1 = drive the pin low      */
    volatile uint32_t TGL;      /* 0x14: write 1 = toggle the pin         */
} gpio_regs_t;

/* Catch a wrong layout at compile time */
_Static_assert(offsetof(gpio_regs_t, TGL) == 0x14U, "GPIO register layout does not match the manual");

#ifdef TARGET_HW
/* On the MCU: the struct sits on the real registers */
#define GPIOA         ((gpio_regs_t *)0x80040000UL)   /* Rule 11.4 deviation: integer to pointer, needed for hardware access */
#define SIM_STEP()    ((void)0)
#else
/* PC demo: the registers are a normal variable, and sim_step() does what the hardware would do */
static gpio_regs_t sim_gpioa;
#define GPIOA         (&sim_gpioa)
#define SIM_STEP()    sim_step()

static void sim_step(void)
{
    sim_gpioa.OUT |= sim_gpioa.SET;                    /* SET bits drive pins high          */
    sim_gpioa.OUT &= ~sim_gpioa.CLR;                   /* CLR bits drive pins low           */
    sim_gpioa.OUT ^= sim_gpioa.TGL;                    /* TGL bits flip pins                */
    sim_gpioa.SET = 0U;                                /* these registers read back as 0    */
    sim_gpioa.CLR = 0U;
    sim_gpioa.TGL = 0U;
    sim_gpioa.IN  = sim_gpioa.OUT & sim_gpioa.DIR;     /* outputs are seen on the input too */
}
#endif

#define GPIO_MAX_PIN  (31U)

typedef enum
{
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
} gpio_level_t;

/* Read-modify-write on DIR: call it during initialization only */
void gpio_set_output(gpio_regs_t *port, uint32_t pin)
{
    if ((port != NULL) && (pin <= GPIO_MAX_PIN))
    {
        port->DIR |= (1U << pin);
    }
}

void gpio_write(gpio_regs_t *port, uint32_t pin, gpio_level_t level)
{
    if ((port != NULL) && (pin <= GPIO_MAX_PIN))
    {
        if (level == GPIO_HIGH)
        {
            port->SET = (1U << pin);        /* one write: atomic, other pins untouched */
        }
        else
        {
            port->CLR = (1U << pin);
        }
    }
}

gpio_level_t gpio_read(const gpio_regs_t *port, uint32_t pin)
{
    gpio_level_t level = GPIO_LOW;

    if ((port != NULL) && (pin <= GPIO_MAX_PIN))
    {
        if (((port->IN >> pin) & 1U) != 0U)
        {
            level = GPIO_HIGH;
        }
    }

    return level;
}

void gpio_toggle(gpio_regs_t *port, uint32_t pin)
{
    if ((port != NULL) && (pin <= GPIO_MAX_PIN))
    {
        port->TGL = (1U << pin);            /* hardware toggle: atomic */
    }
}

int main(void)
{
    const uint32_t led = 5U;                /* an LED on pin 5 */

    gpio_set_output(GPIOA, led);
    SIM_STEP();
    (void)printf("DIR = 0x%08lX\n", (unsigned long)GPIOA->DIR);

    gpio_write(GPIOA, led, GPIO_HIGH);
    SIM_STEP();
    (void)printf("after write HIGH: OUT = 0x%08lX, read = %d\n", (unsigned long)GPIOA->OUT, (int)gpio_read(GPIOA, led));

    gpio_toggle(GPIOA, led);
    SIM_STEP();
    (void)printf("after toggle    : OUT = 0x%08lX, read = %d\n", (unsigned long)GPIOA->OUT, (int)gpio_read(GPIOA, led));

    gpio_toggle(GPIOA, led);
    SIM_STEP();
    (void)printf("after toggle    : OUT = 0x%08lX, read = %d\n", (unsigned long)GPIOA->OUT, (int)gpio_read(GPIOA, led));

    gpio_write(GPIOA, led, GPIO_LOW);
    SIM_STEP();
    (void)printf("after write LOW : OUT = 0x%08lX, read = %d\n", (unsigned long)GPIOA->OUT, (int)gpio_read(GPIOA, led));

    return 0;
}
```

**Output:**

```text
DIR = 0x00000020
after write HIGH: OUT = 0x00000020, read = 1
after toggle    : OUT = 0x00000000, read = 0
after toggle    : OUT = 0x00000020, read = 1
after write LOW : OUT = 0x00000000, read = 0
```

**Cross-questions:**

1. **Why a struct and not `#define` offsets?**
   "It's more readable, the compiler calculates the offsets, and I get type checking. It's also exactly how CMSIS defines the registers, so it's the standard style."
2. **How do you enable the GPIO clock without a HAL?**
   "Find the clock or power control register in the manual and set the enable bit for that port, for example `RCC->AHB1ENR |= (1U << 0);` for GPIOA on an STM32F4. If I forget it, every register write is ignored."
3. **How do you handle gaps in the register map?**
   "With reserved members, like `uint32_t RESERVED[3];`, and I verify with a static assert: `_Static_assert(offsetof(gpio_regs_t, TGL) == 0x14U, "bad layout");`."
4. **What else would a full GPIO driver configure?**
   "Pull-up and pull-down, output type (push-pull or open-drain), speed, the alternate function, and interrupts if the chip has them."

### Q69. Why `volatile`, and how does a structure map onto the registers?

**In simple words:** `volatile` tells the compiler that **every read and write of this variable must really happen, in order**. Hardware or an ISR can change the value at any time.

Without `volatile`, the optimizer may keep the value in a CPU register, or remove reads and writes it thinks are not needed.

**Example:** `while ((UART->SR & RXNE) == 0U) {}`. Without `volatile`, the compiler may read SR once, keep it in a register, and loop forever, even after a byte arrives.

> "`volatile` tells the compiler: this value can change behind your back, and every access matters. Without it, the optimizer might read the register once and keep it in a CPU register, so my polling loop never sees the change. Or it might merge two writes into one. The code works in debug and breaks in release, which is a really annoying bug to find.
>
> For the struct: the members are laid out in order, 4 bytes each, so each member lands exactly at base plus its offset. If the register map has gaps, I add **reserved** members to fill them, and I like to check the offsets with `offsetof` or a static assert."

**Cross-questions:**

1. **Does `volatile` make access atomic or thread-safe?**
   "**No**, and that's a common misunderstanding. It only stops the compiler from optimizing the accesses away. A read-modify-write on a volatile is still three steps, and on multicore it doesn't give any memory ordering. For that I need atomics, critical sections or barriers."
2. **Where else do you use `volatile`?**
   "For variables shared between an ISR and the main code, like a flag, and for memory written by DMA."
3. **What does `const volatile` mean?**
   "'I won't write it, but it can change by itself.' For example, a read-only status register."
4. **`volatile uint32_t *p` vs `uint32_t * volatile p`?**
   "The first is a pointer to volatile data, which is what registers need. The second is a volatile pointer to normal data: the pointer variable itself can change."

### Q70. What does `1U << pin` do, and why `1U` and not `1`?

**Also asked as:** *Why do we use a left shift to select a GPIO pin?* · *What is the result of 1U << 0, 1U << 1, 1U << 2 ...?* · *How do you set, clear, read and toggle a particular GPIO bit?*

**In simple words:** `1U << n` creates a 32-bit value where **only bit n is 1**.

This value is called a mask. It is used with OR, AND-NOT and XOR to change only that one bit.

**Example:** `1U << 5` = 0x20 = binary 0010 0000. `reg |= 0x20` turns on pin 5 and leaves the other 31 alone.

> "It builds a **mask** with only that pin's bit set. So `1U << 3` is 0x8, binary 1000, and when I OR it into a register, only bit 3 changes.
>
> I use `1U` because it's **unsigned**. A plain `1` is a signed int, and `1 << 31` shifts into the sign bit, which is **undefined behaviour** in C. Registers are unsigned, so my masks are unsigned too. MISRA requires it as well."

| Expression | Value | Binary |
| --- | --- | --- |
| `1U << 0` | `0x1` | `...0001` |
| `1U << 1` | `0x2` | `...0010` |
| `1U << 2` | `0x4` | `...0100` |
| `1U << 3` | `0x8` | `...1000` |
| `1U << 31` | `0x80000000` | bit 31 |

> "And with that mask, the four basic operations are one line each: **OR** to set, **AND with the inverted mask** to clear, **shift and AND with 1** to read, and **XOR** to toggle."

```c
/* reg is a volatile uint32_t register, pin is 0..31 */
reg |=  (1U << pin);                       /* set: only this bit becomes 1          */
reg &= ~(1U << pin);                       /* clear: ~mask has a 0 only at this bit */
bit  = (uint8_t)((reg >> pin) & 1U);       /* read: move the bit to position 0      */
reg ^=  (1U << pin);                       /* toggle: XOR with 1 flips the bit      */
```

**Cross-questions:**

1. **What is `1U << 32`?**
   "Undefined behaviour: you can't shift by the type's width or more. For 64-bit masks I use `1ULL << n`."
2. **How do you set a field wider than one bit?**
   "Clear the field, then OR in the value. For example, STM32 MODER has 2 bits per pin: `reg = (reg & ~(3U << (pin * 2U))) | (mode << (pin * 2U));`."
3. **Any operator-precedence traps?**
   "Yes. `<<` binds tighter than `&`, so `x & 1U << n` works, but `x & mask == 0` means `x & (mask == 0)`. I always add brackets."

### Q71. Software XOR toggle vs a hardware toggle register? What's wrong with read-modify-write?

**In simple words:** `OUT ^= mask` becomes three instructions: **load, XOR, store**. If something changes OUT between the load and the store, the store overwrites that change.

A SET, CLR or TGL register avoids this, because it makes the change with **one single write**.

**Example:** The main code reads OUT = 0001, the ISR sets bit 2 (OUT = 0101), then the main code writes back its old copy with bit 1 toggled: 0011. Bit 2 is lost.

> "`OUT ^= mask` looks like one line, but it's really three steps: **read** the register, **change** it, **write** it back. If an interrupt comes in between my read and my write, and the ISR changes a different pin on the same port, then my write puts back the **old value** and the ISR's change is just lost. It's a nasty bug, because it happens maybe once in a million toggles.
>
> A hardware **SET, CLEAR or TOGGLE register** fixes that, because it's a single write and only the bits I write as 1 are affected. On STM32 that's the **BSRR** register. If the chip doesn't have one, I disable interrupts around the read-modify-write."

```text
Main code: reads OUT = 0b0001                        ISR: sets bit 2 → OUT = 0b0101
Main code: writes 0b0001 ^ 0b0010 = 0b0011  →  bit 2 set by the ISR is LOST
```

**Cross-questions:**

1. **Is `OUT |= mask` atomic?**
   "No, `|=` is also read, change, write. Only the dedicated SET/CLR/TGL registers are a single write."
2. **What is bit-banding?**
   "On Cortex-M3 and M4, every bit in the peripheral and SRAM regions has its own word address in an **alias region**. Writing 1 or 0 to that word sets or clears just that bit, atomically. The address is `0x42000000 + (offset × 32) + (bit × 4)` for peripherals. Cortex-M7 and newer cores don't have it."
3. **Does the same race happen between two RTOS tasks?**
   "Yes. A preemption between the read and the write has the same effect as an interrupt. So it's the same fix: an atomic register, or a critical section."
4. **How do you make a normal variable update atomic?**
   "LDREX/STREX in a loop, or C11 `atomic_fetch_or()`, which the compiler turns into exactly that."

---

## 20. C strings: array vs pointer

### Q72. `char str[] = "Hello"` vs `const char *p = "Hello"`: what's the difference, and can you modify them?

**Also asked as:** *Can you modify a character array containing a string?* · *Can you modify a string literal?* · *What happens with char *p = "Hello" if you try to modify the string?*

**In simple words:** - `char str[]` is an **array**. It is filled with a **copy** of the string, so it can be changed.
- `const char *p` holds the **address of a string literal**. The compiler puts string literals in **read-only memory**, so they cannot be changed.

**Example:** `str[0] = 'J';` gives "Jello". `p[0] = 'J';` crashes on Linux, or HardFaults on an MCU.

> "`str` is an **array**. The compiler makes my own copy of the string, 6 bytes with the null terminator, in RAM, so I can change it: `str[0] = 'J'` is fine.
>
> `p` is just a **pointer** to a **string literal**, and the literal lives in **read-only memory**, which on an MCU is flash. If I try to modify it, that's **undefined behaviour**: on Linux it's usually a segfault, and on an MCU it's a HardFault, or the write is silently ignored. That's why I always declare it `const char *`, so the compiler stops me.
>
> If someone writes `char *p = "Hello"` without the `const`, it still compiles in C, but it's the same thing: `p[0] = 'J'` is still undefined behaviour. The `const` just makes the compiler catch it.
>
> And a small trick question they like: `sizeof(str)` is 6, but `sizeof(p)` is just the size of a pointer, 4 or 8."

| | `char str[] = "Hello";` | `const char *p = "Hello";` |
| --- | --- | --- |
| What it is | An array holding a copy | A pointer to a string literal |
| Where the characters are | RAM (stack or `.data`) | Read-only memory (`.rodata` / flash) |
| Can modify the characters? | **Yes** | **No**: undefined behaviour |
| Can point it elsewhere? | No: an array isn't assignable | **Yes**: `p = "World";` |
| `sizeof` | 6 (the whole array) | 4 or 8 (just the pointer) |

**Cross-questions:**

1. **Where does the array's copy of "Hello" come from?**
   "For a **local** array, the compiler generates code that copies the literal onto the stack every time the function runs. For a **global** array, it goes into `.data`, which the startup code copies from flash to RAM once."
2. **Do two identical literals share the same address?**
   "Maybe: the compiler is allowed to merge them, but it's not guaranteed. So I never compare strings with `==`; I use `strcmp`."
3. **Is `char s[5] = "Hello";` valid?**
   "In C, yes, but there's no room for the `'\0'`, so it's not a string, and `strlen` or `printf` will run past the end. In C++ it's a compile error."
4. **`sizeof` vs `strlen` for `str`?**
   "`sizeof(str)` is 6, including the terminator, and known at compile time. `strlen(str)` is 5, counted at run time."

---

## 21. RTOS, interrupts and context switching

### Q73. What is a context switch, and what is saved?

**Also asked as:** *What happens during a context switch?* · *Does a context switch copy the entire task memory/RAM?*

**In simple words:** A context switch has four steps:

1. Save the running task's CPU registers on **its own stack**.
2. Store that task's stack pointer in its TCB.
3. Load the next task's stack pointer from its TCB.
4. Restore the next task's registers from its stack.

Only the registers are saved. No memory is copied.

**Example:** Task A is paused at the line `x = x + 1;` with x = 5 in R0. Task B runs for a while. When A resumes, R0 is 5 again, and it continues exactly from that line.

> "A context switch is the RTOS pausing one task and running another. To be able to come back later exactly where it stopped, it saves the task's **CPU registers**: R0 to R12, the stack pointer, LR, PC and the status register, plus the FPU registers if the task used floating point.
>
> They're pushed onto **that task's own stack**, and the stack pointer is saved in its TCB. And it does **not** copy any RAM. Each task's stack and data just stay where they are; only the registers are saved and restored. That's why a context switch takes microseconds, not milliseconds."

**Cross-questions:**

1. **How long does a context switch take on a Cortex-M?**
   "Roughly a hundred to a few hundred cycles, so around a microsecond at 100 MHz or more. It's small, but it's why I don't make the tick rate unnecessarily high."
2. **What causes a context switch?**
   "Four things: the **tick** interrupt at the end of a time slice, a task **blocking** (on a delay, queue or semaphore), a task calling **yield**, or an **ISR waking a higher-priority task**."
3. **What's in the TCB?**
   "The saved stack pointer, which is the most important field, the priority, the state lists it's in (ready, blocked, suspended), the stack's start address for overflow checks, the name, and the notification value."
4. **How do you size a task's stack?**
   "Start generously, run the worst case, then check `uxTaskGetStackHighWaterMark()` and trim, keeping a margin. And I enable `configCHECK_FOR_STACK_OVERFLOW` with the overflow hook during development."

### Q74. How does a bare-metal superloop handle an external interrupt, compared with an RTOS?

**In simple words:** - In a **superloop**, the ISR sets a flag, and the main loop checks it. So the delay can be up to one full loop.
- With an **RTOS**, the ISR wakes up a task, and the scheduler runs that task right after the ISR. So the delay depends only on task priorities.

**Example:** A button press: the superloop only notices the flag after the 50 ms display update finishes. With an RTOS, the button task runs within microseconds of the interrupt.

> "In a **superloop**, the ISR does the minimum, like setting a flag or putting a byte in a buffer, and the main loop sees the flag the next time it goes around. So my response time depends on how long one loop takes, which can be a lot if some function is slow.
>
> With an **RTOS**, the ISR gives a semaphore or a task notification using a `FromISR` API. That wakes the task that handles the event, and if that task has higher priority, the scheduler switches to it **right when the ISR ends**. So the response is fast and predictable, no matter what the other tasks are doing."

**Cross-questions:**

1. **When is a superloop the better choice?**
   "For small, simple systems: it's deterministic, uses very little memory, has no RTOS overhead, and is easy to test and certify. Once there are several independent timing requirements, an RTOS gets easier to manage."
2. **How do you share data safely between an ISR and the main loop?**
   "A `volatile` flag for simple events, a **ring buffer** with one writer and one reader for data, and a short interrupt disable when reading a multi-byte value, so the ISR can't change it halfway through."
3. **What is deferred interrupt processing?**
   "The ISR only captures the event and wakes a task; the task does the real processing. It keeps ISRs short and lets the work run at a chosen task priority."

### Q75. When an interrupt arrives, what happens to the running task, and what does the hardware save?

**Also asked as:** *Does the RTOS scheduler save the task context before entering the ISR?* · *What is saved on a Cortex-M exception entry?* · *How does the CPU jump from the interrupt source to the ISR?*

**In simple words:** When an interrupt happens, the Cortex-M hardware does three things automatically:

1. It **pushes 8 registers** (R0-R3, R12, LR, PC and xPSR) onto the current stack.
2. It loads a special **EXC_RETURN** value into LR.
3. It reads the handler's address from the **vector table** and jumps there.

**Example:** The task is at PC 0x08001234 → interrupt → the hardware pushes R0-R3, R12, LR, PC (0x08001234) and xPSR onto the task's stack → jumps to the ISR. After the ISR, it pops them, and the task continues at 0x08001234.

> "The task just gets interrupted. The RTOS doesn't do anything yet. The **Cortex-M hardware** itself automatically pushes **8 registers** onto the task's stack: R0 to R3, R12, LR, PC and xPSR, plus the FPU registers if they were in use.
>
> Then it puts a special value, **EXC_RETURN**, in LR, switches to the main stack, looks up the ISR address in the **vector table**, and jumps there. The nice thing is that those 8 registers are exactly the ones a C function is allowed to trash, so the ISR can be a normal C function. No assembly wrapper needed."

```text
Interrupt → hardware stacks R0-R3, R12, LR, PC, xPSR (+ FPU) on the task's stack
          → LR = EXC_RETURN → read the handler from the vector table → run the ISR
```

**Cross-questions:**

1. **Why do tasks use the PSP and interrupts the MSP?**
   "Each task has its own stack through the **PSP**, and all ISRs share one stack through the **MSP**. So I don't have to add ISR space to every task's stack: I size the MSP once for the worst-case nesting."
2. **What are tail-chaining and late arrival?**
   "**Tail-chaining**: if another interrupt is pending when one ISR ends, the core skips the unstack and restack and jumps straight to the next ISR, in about 6 cycles instead of 12 + 12. **Late arrival**: if a higher-priority interrupt arrives while the core is still stacking for a lower one, it reuses the same stacking and runs the higher one first."
3. **What is the interrupt latency on a Cortex-M3/M4?**
   "12 cycles from the interrupt to the first ISR instruction, with zero-wait-state memory."
4. **What is lazy FPU stacking?**
   "If the task used the FPU, the core reserves space for the FPU registers but doesn't actually save them unless the ISR also uses the FPU. That keeps the latency low for ISRs that don't use floating point."
5. **What does an EXC_RETURN value like 0xFFFFFFFD mean?**
   "Return to **thread mode**, using the **PSP**, with a basic frame (no FPU registers). 0xFFFFFFF9 would be thread mode with the MSP, and 0xFFFFFFF1 back to handler mode, for a nested interrupt."

### Q76. What happens after the ISR finishes, with and without waking a higher-priority task?

**Also asked as:** *How does the RTOS perform a context switch after an ISR?* · *What happens if the ISR does not wake a higher-priority task?*

**In simple words:** When the ISR ends, there are two possible cases:

- **No switch needed:** the hardware restores the registers, and the **same task** continues.
- **A higher-priority task was woken:** **PendSV** is pending. It runs after the ISR and switches to that task.

**Example:** A priority-2 task is running. The UART ISR gives a semaphore to the priority-5 protocol task and calls `portYIELD_FROM_ISR()`. When the ISR ends, PendSV switches straight to the priority-5 task.

> "**If nothing important was woken**, the ISR returns, the hardware pops the 8 registers back, and the **same task** continues like nothing happened.
>
> **If the ISR woke a higher-priority task**, I call `portYIELD_FROM_ISR()` at the end of the ISR. That doesn't switch right away; it **pends PendSV**. Once the ISR and any other interrupts are done, PendSV runs. It saves the rest of the current task's registers, R4 to R11, on its stack, stores the stack pointer in its TCB, picks the new task, loads that task's stack pointer and registers, and returns. The hardware pops the new task's 8 registers, and now the **higher-priority task** is running."

**Cross-questions:**

1. **What if you forget `portYIELD_FROM_ISR()`?**
   "Nothing crashes. The woken task just doesn't run until the next tick or the next yield, which adds up to one tick of latency."
2. **Why can't an ISR call the normal `xSemaphoreGive()`?**
   "The normal APIs may try to block or switch tasks directly, which is illegal in an ISR and corrupts the kernel's state. The `FromISR` versions never block. They just report through `pxHigherPriorityTaskWoken` whether a switch is needed."
3. **What is `configMAX_SYSCALL_INTERRUPT_PRIORITY`?** (a very common STM32 bug)
   "ISRs that call FreeRTOS APIs must have a priority **numerically equal to or higher** than this value, meaning logically lower or equal in urgency, because the kernel masks only up to that level in its critical sections. STM32 interrupts default to priority 0, the most urgent. If such an ISR calls a `FromISR` function, it can corrupt the kernel, and `configASSERT` catches it. Interrupts above that level can't use the API, but the kernel never masks them, so they get zero added latency."

### Q77. What is PendSV, and why does FreeRTOS use it on Cortex-M?

**In simple words:** PendSV is an exception that software can trigger, and it is set to the **lowest priority**.

FreeRTOS does its context switches inside PendSV. Because it has the lowest priority, a task switch never happens while another ISR is still running.

**Example:** SysTick fires while the UART ISR is running. SysTick only pends PendSV. The UART ISR finishes, then PendSV runs and switches tasks safely.

> "PendSV is an exception that software can request, or 'pend'. FreeRTOS gives it the **lowest priority** of all interrupts. That's the whole point: the context switch only happens **after every other interrupt is finished**. You never switch tasks in the middle of a nested ISR, which would mess up the interrupted handler.
>
> SysTick uses it too: at the end of a time slice, the tick handler just pends PendSV. So every context switch goes through one single place."

**Cross-questions:**

1. **Why not switch tasks directly inside SysTick?**
   "SysTick might have interrupted another ISR. If it switched tasks then, it would return to a task while that ISR is still half done. Cortex-M doesn't even allow returning to thread mode with another exception active; it faults. PendSV at the lowest priority waits until all ISRs are finished."
2. **What does FreeRTOS use SVC for?**
   "To **start the first task**. `vPortSVCHandler` loads the first task's context and switches the core to use the PSP."
3. **What priority do SysTick and PendSV get in FreeRTOS?**
   "Both get the lowest priority, so the kernel's own work never delays application interrupts."

### Q78. Hardware context saving vs RTOS context saving?

**In simple words:** The saving is split in two:

- The **hardware** saves the **caller-saved** registers on every exception.
- The **RTOS** saves the **callee-saved** registers (R4-R11), but only when it switches tasks.

**Example:** Every interrupt: the hardware saves 8 registers. Only on a task switch: PendSV also saves R4-R11.

> "The hardware saves half and the RTOS saves the other half. The **hardware** saves R0 to R3, R12, LR, PC and xPSR on **every** interrupt, so the ISR can be plain C. The **RTOS**, in PendSV, saves R4 to R11, and only when it's actually **switching tasks**, and it stores the stack pointer in the TCB so it can resume that task later."

| | Hardware (exception entry) | RTOS (PendSV) |
| --- | --- | --- |
| Who | The Cortex-M core, automatically | The RTOS port code |
| When | On every interrupt | Only when switching tasks |
| What | R0-R3, R12, LR, PC, xPSR (+ S0-S15, FPSCR) | R4-R11 (+ S16-S31) |
| Where | The current task's stack (PSP) | The task's stack; the stack pointer goes into the TCB |

**Cross-questions:**

1. **Why doesn't the hardware save R4 to R11 too?**
   "Because of the Arm calling convention, **AAPCS**: R4 to R11 are **callee-saved**. Any C function, including an ISR, that uses them pushes and pops them itself. So they only need saving when we actually switch to a different task, and that's the RTOS's job."
2. **How does the RTOS know whether to save the FPU registers?**
   "Bit 4 of EXC_RETURN tells it whether the task used the FPU. If it did, PendSV also saves S16 to S31. If not, it skips them."

---

## 22. FreeRTOS heap

### Q79. Which FreeRTOS heap implementations are there, and which would you use?

**Also asked as:** *Why would you choose heap_4?* · *How does heap_4 reduce fragmentation?* · *Why would you use heap_1 instead of heap_4?*

**In simple words:** The FreeRTOS heap files are **different memory allocators** that share one RAM array. They differ in two ways:

- Whether memory can be **freed**.
- Whether neighbouring free blocks are **merged**.

Together, these decide how badly the heap **fragments** over time.

**Example:** Three neighbouring 100-byte blocks are freed. heap_4 joins them into one 300-byte block, so a 250-byte request succeeds. heap_2 keeps three separate 100-byte blocks, and the 250-byte request fails.

> "There are five, and the difference is mostly whether you can free memory, and what happens to fragmentation.
>
> **heap_1** only allocates and never frees, so it can't fragment. It's great when I create everything at start-up and never delete anything, and it's easy to certify. **heap_2** can free, but doesn't merge free blocks, so it fragments; it's basically legacy now. **heap_3** just wraps the standard malloc and free and makes them thread-safe. **heap_4** can free and **merges neighbouring free blocks**, so fragmentation stays low; that's the one I'd normally use. And **heap_5** is heap_4, but it can spread the heap over **several RAM regions**, like internal RAM plus external RAM.
>
> And honestly, where I can, I avoid the heap completely and use **static allocation**, like `xTaskCreateStatic()`."

| File | Frees memory? | Merges free blocks? | Use it when |
| --- | --- | --- | --- |
| **heap_1** | No | – | Everything is created at start-up and never deleted |
| **heap_2** | Yes | No | Legacy; replaced by heap_4 |
| **heap_3** | Yes | Library-dependent | You must use the toolchain's `malloc()` |
| **heap_4** | Yes | **Yes** | **The usual choice** |
| **heap_5** | Yes | Yes | The RAM is split over several regions |

**Cross-questions:**

1. **What exactly is fragmentation?**
   "The free memory is split into many small, non-adjacent blocks. The total free space might be 10 KB, but if the biggest single free block is 1 KB, a 2 KB allocation fails."
2. **How does heap_4 merge blocks?**
   "It keeps the free list **sorted by address**. When a block is freed, it checks whether it touches the free block just before it or just after it, and if so, joins them into one bigger block."
3. **How do you monitor heap usage?**
   "`xPortGetFreeHeapSize()` for now, `xPortGetMinimumEverFreeHeapSize()` for the worst case so far, and `vApplicationMallocFailedHook()` to catch a failed allocation immediately."
4. **Where is the heap memory?**
   "For heap_1, 2 and 4, it's a static array, `ucHeap[configTOTAL_HEAP_SIZE]`, in `.bss`. For heap_5, I describe the RAM regions with `vPortDefineHeapRegions()` before creating anything."
5. **Why is the standard `malloc` a problem in real-time code?**
   "Its execution time isn't bounded, it may not be thread-safe, and it fragments. heap_4 is also not constant time, which is one more reason to allocate everything at start-up."

---

## 23. BLE in practice

The BLE stack, GATT and MTU are [Q28](#q28-where-did-you-work-with-ble-which-protocol-layer)-[Q30](#q30-what-is-mtu-in-ble).

### Q80. What does each layer of the BLE stack do?

**Also asked as:** *Can you explain the Bluetooth/BLE stack?* · *What are GAP, GATT, ATT, L2CAP, HCI, Link Layer and PHY?*

**In simple words:** The BLE stack has two parts:

- The **controller** contains the radio and the link layer. This is the timing-critical part.
- The **host** contains L2CAP, ATT, GATT, SMP and GAP.

The two parts talk through a standard interface called **HCI**.

**Example:** A phone reading a heart rate uses all of them: GAP to connect, SMP to pair, GATT/ATT to read the value, carried over L2CAP, the link layer and the radio.

> "I'll go from the top. **GAP** handles roles, advertising and connecting. **GATT** organizes the data into services and characteristics, and **ATT** underneath does the actual reads and writes. **SMP** handles pairing and encryption keys. **L2CAP** multiplexes all of that over one link.
>
> Then **HCI** is the standard interface between the host and the controller; on a two-chip design it's literally a UART. In the controller, the **link layer** handles advertising, connections, timing, ACKs and channel hopping, and the **PHY** is the 2.4 GHz radio itself."

| Layer | Part | Job |
| --- | --- | --- |
| **GAP** | Host | Roles, advertising, scanning, connecting, security modes |
| **GATT** | Host | Services and characteristics |
| **ATT** | Host | Reads and writes attributes (handle, UUID, value, permissions) |
| **SMP** | Host | Pairing, bonding, encryption keys |
| **L2CAP** | Host | Multiplexes ATT, SMP and signaling; fragments large packets |
| **HCI** | Between | Host ↔ controller interface (UART, USB or SPI) |
| **Link Layer** | Controller | Advertising and connection states, timing, ACKs, CRC, channel hopping |
| **PHY** | Controller | The 2.4 GHz radio: 40 channels, 1 or 2 Mbit/s |

**Cross-questions:**

1. **Single-chip vs two-chip BLE design?**
   "Single-chip: the host and the controller run on the same SoC, like an nRF52 or ESP32. Two-chip: my MCU runs the host stack and talks over **HCI**, usually UART, to a separate radio module that runs the controller."
2. **How many channels does BLE use?**
   "40 channels of 2 MHz. 3 are advertising channels (37, 38, 39), placed to avoid the busiest Wi-Fi channels, and 37 are data channels with adaptive frequency hopping."
3. **What are the L2CAP fixed channels?**
   "0x0004 for ATT, 0x0005 for LE signaling and 0x0006 for SMP."
4. **Which PHYs are there?**
   "1M, the default; 2M, for double the speed; and **Coded** PHY (S2 or S8), which trades speed for about 4 times the range."

### Q81. Did you create custom BLE services? Which services and characteristics?

**In simple words:** A custom service is a group of characteristics under **your own 128-bit UUID**.

For each characteristic, you choose its **properties** (read, write, notify) and its **permissions** (for example, encryption required).

**Example:** A custom "Sensor Service" with three characteristics: Temperature (read + notify), Sample Interval (read + write), and Command (write without response: 0x01 = start, 0x02 = stop).

Note: this is a sample answer. Change it to match your own project.

> "Yes. For our sensor product I made a **custom service with a 128-bit UUID**. Inside it there were three characteristics. A **sensor data** characteristic with **read and notify**, so the phone gets new readings without polling. A **configuration** characteristic with **read and write**, for things like the sampling interval. And a **command** characteristic with **write without response**, for quick commands like start and stop.
>
> Alongside that I used the standard **Battery Service** and **Device Information Service**, so any generic BLE app could read the battery level and firmware version."

**Cross-questions:**

1. **Why a 128-bit UUID for a custom service?**
   "16-bit UUIDs are reserved for the Bluetooth SIG's standard services, so a custom service uses a random 128-bit one to avoid clashes."
2. **How do you protect a characteristic?**
   "With its **permissions**: for example 'read requires encryption' or 'write requires authenticated pairing'. Then the phone has to pair before it can access it."
3. **What other descriptors are there besides the CCCD?**
   "Characteristic User Description (0x2901), a text label, and Presentation Format (0x2904), which gives the unit and format of the value."
4. **How did you define the service in code?**
   *(Fill in your own stack, for example `BT_GATT_SERVICE_DEFINE` in Zephyr, or an attribute table in ESP-IDF.)*

### Q82. Read vs Write vs Notify: what's the difference?

**In simple words:** - **Read** and **write** are started by the client, and the server acknowledges them.
- **Notify** is sent by the server whenever it wants, with no acknowledgment.
- **Indicate** is like notify, but the client must confirm it.

**Example:** The phone reads the battery level once (read), sets the sampling rate (write), and then receives the temperature every second (notify).

> "It's about who starts the transfer. With **read**, the phone asks and the device answers. With **write**, the phone sends a value and gets a response back; **write without response** skips that, so it's faster. With **notify**, the **device** pushes the value whenever it changes, and the phone doesn't have to ask, so it's the fastest and the most power-efficient for streaming. **Indicate** is like notify, but the phone has to confirm it, so I use it when the data must not be lost."

| Property | Who starts it | Acknowledged? | Use |
| --- | --- | --- | --- |
| **Read** | Client asks, server answers | Yes (the response) | Read a value on demand |
| **Write** | Client sends | Yes: Write Response | Settings, configuration |
| **Write Without Response** | Client sends | No: faster | Fast commands |
| **Notify** | **Server** sends when the value changes | No: fastest | Sensor data streaming |
| **Indicate** | Server sends | Yes: client confirms | Events that must not be lost |

**Cross-questions:**

1. **Notify vs Indicate: when do you choose Indicate?**
   "When the data must not be lost, like an alarm. Indications need a confirmation, and only one can be outstanding at a time, so they're much slower than notifications."
2. **How much data fits in one notification?**
   "MTU minus 3 bytes: 20 bytes by default, 244 with a 247-byte MTU."
3. **What if you send notifications faster than the link can carry them?**
   "The stack's transmit buffers fill up and the send call returns an error, like 'no buffers'. I wait for the 'TX complete' event and send the next one then, which is basic flow control."

### Q83. How does a notification work, and what is the CCCD?

**Also asked as:** *Why is the CCCD required for notifications?*

**In simple words:** Every characteristic that supports notifications has a **CCCD** descriptor.

The server sends notifications only to a client that has written **0x0001** to that CCCD.

**Example:** The phone writes `01 00` to the CCCD of the heart-rate characteristic, and from then on the device sends the heart rate every second without being asked.

> "The device isn't allowed to just push data at the phone. The phone has to **subscribe** first. It does that by writing **0x0001** to the characteristic's **CCCD**, the Client Characteristic Configuration Descriptor, UUID 0x2902; 0x0002 means indications.
>
> From then on, whenever the value changes, my firmware sends a notification with the new value. A common bug I've seen is 'notify doesn't work', and it's just because the app never wrote the CCCD. The CCCD is per connection, and for bonded devices it's remembered across reconnects."

```text
Client writes 0x0001 to the CCCD  →  server: "notifications on for this client"
Value changes  →  server sends Notification(handle, value)  →  client app gets the new value
```

**Cross-questions:**

1. **Why is the CCCD per connection?**
   "Because each client chooses for itself. If two phones are connected, one may want notifications and the other may not."
2. **What's the CCCD value format?**
   "Two bytes: bit 0 enables notifications, bit 1 enables indications. So 0x0001, 0x0002, or 0x0000 to turn them off."
3. **How do you debug BLE issues?**
   "The **nRF Connect** app on a phone to browse services and enable notifications by hand, and a **BLE sniffer** (an nRF dongle with Wireshark) to see the actual packets, including MTU exchange and CCCD writes."

---

## 24. Firmware update and bootloader

The full topic, with diagrams and code, is in the [bootloader notes](../BOOTLOADER/bootloader.md).

### Q84. What is a bootloader, and what is its purpose?

**In simple words:** The bootloader is the **first program in flash** that runs after reset. It does three things:

1. It checks whether the application image is valid.
2. If a new image is waiting, it installs it.
3. It sets up the CPU and jumps to the application's reset handler.

**Example:** On an STM32F4: bootloader at 0x08000000 (48 KB), application at 0x0800C000. After reset the bootloader checks the app's CRC, then jumps to it.

> "The bootloader is the small program that runs first after reset. It decides what to run: it checks that the application is **valid**, installs an **update** if there's one waiting, and then **jumps** to the application.
>
> Its main purpose is updating firmware in the field without a debugger, and recovering if an update goes wrong. With secure boot, it also makes sure only our signed firmware runs. I keep it small, simple and write-protected, because if the bootloader breaks, the device is bricked."

**Cross-questions:**

1. **How do you jump from the bootloader to the application?**
   "Disable interrupts and SysTick, de-initialize the peripherals, set VTOR to the app's vector table, load the MSP from the app's word 0, and jump to the address in word 1. The full sequence is in the [bootloader notes](../BOOTLOADER/bootloader.md)."
2. **How does the device enter bootloader mode?**
   "A button held at reset, a flag the application sets in RAM or a backup register before resetting, or automatically when there's no valid application."
3. **How do you protect the bootloader itself?**
   "Write-protect its flash sectors with the option bytes, never update it in the field, or only through a safe two-stage scheme."
4. **How big is a typical MCU bootloader?**
   "Usually 16 to 64 KB, depending on the update interface and on whether it does signature checking."

### Q85. How is new firmware received?

**Also asked as:** *Can firmware be received through USB, UART or OTA?*

**In simple words:** New firmware can arrive over any interface the device has. It is sent in **chunks, each with a sequence number and a CRC**.

It is written into a flash area that is **not being executed** at that moment.

**Example:** An ESP32 downloads the new firmware over HTTPS into its `ota_1` partition while it keeps running from `ota_0`, then switches on the next reboot.

> "It depends on what the product has. On the wired side, **UART**, **USB DFU**, or **CAN** in automotive; those are mostly used in the factory or for recovery. In the field it's usually **OTA**, over Wi-Fi, BLE or cellular.
>
> For OTA, typically the **application** downloads the new image into the spare slot while the device keeps working normally, and the bootloader only has to verify it and switch over on the next reset."

**Cross-questions:**

1. **How does the application hand over to the bootloader?**
   "It writes an 'update requested' flag somewhere that survives a reset, a backup register or a reserved flash word, and resets. The bootloader sees the flag and stays in update mode."
2. **What does the update protocol look like?**
   "Packets with a command, a sequence number, the length, the data and a CRC. The receiver ACKs or NACKs each packet, and the sender retransmits on NACK or timeout. The details are in the [bootloader notes](../BOOTLOADER/bootloader.md)."
3. **Is the STM32 built-in USB/UART bootloader the same as yours?**
   "No. That's ST's **system bootloader** in ROM, entered with BOOT0. It's the vendor's code. My bootloader lives in flash and implements my own update logic."

### Q86. The update is interrupted: slot B is only 50 % written and the device reboots. What happens?

**Also asked as:** *What happens if the firmware download is interrupted?* · *How does the bootloader know that slot B is incomplete?* · *How do you prevent an incomplete image from being booted?* · *How can the download be resumed after a reboot?*

**In simple words:** The safety comes from the **order of the steps**:

1. The new image is written into the inactive slot.
2. It is verified.
3. Only then is the metadata changed to point to the new slot.

Until step 3, the old slot stays active. So an interrupted update never affects the running firmware.

**Example:** A 256 KB image, 128 KB written when the power fails. The metadata still says "active = A", so the device boots A. The app then resumes the download from offset 128 KB, using an HTTP request for `bytes=131072-`.

> "If it's designed properly, nothing bad. While slot B is being written, the metadata still says **slot A is active**, and B is never marked as ready. So after the reboot, the bootloader just boots A again, and the user doesn't notice anything.
>
> Even if the bootloader did look at B, the **size and CRC or signature** in its header wouldn't match, so it would never boot a half-written image. The rule is: you mark the new image valid **only at the very end**, after the whole thing is written and verified.
>
> To **resume**, the app saves its progress in flash: the version it's downloading, and how many bytes are safely written. After the reboot it checks that the server still has the same version, re-erases the sector where it stopped, and continues from that offset instead of starting from zero."

```text
Writing slot B → power lost at 50 %
Reboot: metadata still says active = A (B never marked pending)  →  boot slot A
App: same version on the server? → yes → erase the last partial sector → continue from offset 50 %
```

**Cross-questions:**

1. **What if power fails while the bootloader is copying the new image over the old one?**
   "With a copy or swap design, I need a **progress record** in flash, so the bootloader can continue the copy after a reset; MCUboot's swap mode works this way. With a true A/B design, the app runs from either slot, so there's no copy at all, which is safer."
2. **Where is the metadata stored?**
   "In its own flash sector, as two copies with sequence numbers and CRCs, the same technique as [Q43](#q43-how-would-you-save-a-number-for-example-a-file-number-so-it-survives-reset)."
3. **What if a flash write itself fails?**
   "I read back and verify each block after writing it. If it doesn't match, I retry, and if it keeps failing I abort the update and leave the slot marked invalid."

### Q87. What is A/B updating, and how do you ensure integrity and rollback?

**Also asked as:** *How do you verify firmware integrity and authenticity?* · *How do you roll back to the previous known-good firmware?*

**In simple words:** A/B means there are **two flash slots**, so a valid image always exists.

The bootloader verifies the new image's hash and signature. It then boots the new image in a **trial state**. If the new image does not confirm itself, the bootloader switches back to the old slot.

**Example:** v2 boots in trial mode, but it crashes, and the watchdog resets it 3 times without v2 ever confirming itself. The bootloader then goes back to v1.

> "A/B means two slots. The device runs from one and writes the update into the other, so there's always a working image.
>
> For **integrity**, a CRC or a hash catches corruption, and a **signature**, checked with a public key stored in the device, proves the image really came from us.
>
> For **rollback**, the new image boots in a **trial** state, with the watchdog on and a boot counter. After it starts, it runs a self-test and **confirms** itself. If it crashes, hangs, or never confirms, the next reset the bootloader sees that and goes **back to the old slot**. So a bad update can never brick the device."

Details: [fail-safe updates](../BOOTLOADER/bootloader.md#8-fail-safe-updates-ab-and-rollback) and [secure boot](../BOOTLOADER/bootloader.md#9-secure-boot).

**Cross-questions:**

1. **CRC vs hash vs signature?**
   "A **CRC** catches accidental corruption only. A **SHA-256 hash** detects any change, but an attacker can simply calculate a new hash. A **signature** needs the private key, which only we have, so it proves who made the image."
2. **Where are the keys?**
   "The **private** key stays on a secure build server, never on the device. The device stores only the **public** key, in the write-protected bootloader or in OTP memory."
3. **What is anti-rollback?**
   "Refusing to install an **older** version, even if it's correctly signed, because an old version might have a known security hole. The minimum allowed version is kept in OTP or secure storage, and only goes up."
4. **What's the watchdog's role in rollback?**
   "If the new firmware hangs, the watchdog resets the board. The bootloader sees that the image was never confirmed, or that the boot counter ran out, and boots the old slot."

---

## 25. Networking: OSPF

### Q88. What is OSPF, and what is it for?

**In simple words:** OSPF routers send **LSAs** that describe their links. Every router in an area builds the same **link-state database** from these LSAs.

Each router then runs **Dijkstra's shortest-path algorithm** on that database, using costs based on link bandwidth. The result is its routing table.

**Example:** R1 → R3 directly over a 10 Mbit/s link costs 10. R1 → R2 → R3 over two 100 Mbit/s links costs 1 + 1 = 2. OSPF picks the route through R2.

> "OSPF, Open Shortest Path First, is a **routing protocol** that routers inside one network use to find the best path to every subnet automatically. It's **link-state**: each router tells all the others about its own links, using LSAs, so every router ends up with the **same map** of the whole network. Then each router runs **Dijkstra's algorithm** on that map to work out its shortest paths. The cost is based on bandwidth, so faster links are preferred.
>
> It reacts quickly when a link goes down, and for big networks you split it into **areas**, all connected to the backbone, area 0."

| Fact | Value |
| --- | --- |
| Type | Link-state, interior gateway protocol |
| Runs over | IP directly, protocol number **89** |
| Multicast addresses | 224.0.0.5 (all OSPF routers), 224.0.0.6 (designated routers) |
| Metric | Cost = reference bandwidth / link bandwidth |
| On shared networks | Elects a Designated Router (DR) and a Backup DR |

**Cross-questions:**

1. **OSPF vs RIP?**
   "RIP is **distance-vector**: it counts hops, has a maximum of 15, and converges slowly. OSPF is **link-state**: it uses a bandwidth-based cost, every router knows the whole topology, and it converges fast."
2. **Why area 0, and what's an ABR?**
   "Area 0 is the **backbone**: every other area must connect to it, which prevents routing loops between areas. A router with interfaces in two areas is an **Area Border Router**, and it summarizes routes between them."
3. **Why elect a DR on Ethernet?**
   "Without it, every router on a shared segment would form a full adjacency with every other one. With a **DR** and a backup, each router only syncs with those two, which cuts the traffic a lot."
4. **OSPF vs BGP?**
   "OSPF routes **inside** one organization. BGP routes **between** organizations, across the internet."

### Q89. How do you configure OSPF? What's required?

**In simple words:** To configure OSPF, you start the OSPF process, set a **router ID**, and assign interfaces to **areas**.

Two routers become neighbours only if these settings **match** on the link: the area, the subnet, the timers, the authentication and the MTU.

**Example:** R1 has hello = 10 s and R2 has hello = 5 s. They never become neighbours until the timers match.

> "On each router I start an OSPF process, give it a unique **router ID**, and say which **networks or interfaces** take part, and in which **area**.
>
> The part that usually causes problems is the neighbour relationship. Two routers only become neighbours if things **match** on that link: the area, the subnet and mask, the hello and dead timers, authentication, and the MTU. If one of those is off, they get stuck. So after configuring, I check that the neighbours reach the **FULL** state and that the routes show up in the routing table."

```text
router ospf 1
 router-id 1.1.1.1
 network 192.168.1.0 0.0.0.255 area 0      ! LAN, area 0
 network 10.0.0.0    0.0.0.3   area 0      ! point-to-point link to the next router

show ip ospf neighbor       ! neighbours should be FULL
show ip route ospf          ! routes learned through OSPF
```

Neighbour states, in order: Down → Init → 2-Way → ExStart → Exchange → Loading → **Full**.

**Cross-questions:**

1. **Neighbours are stuck in ExStart or Exchange. Why?**
   "Almost always an **MTU mismatch** on the link. If they're stuck in Init, the hellos only work in one direction, for example because of an ACL or a multicast problem."
2. **How is the router ID chosen?**
   "The manually configured `router-id` first; if there isn't one, the highest loopback IP address, then the highest IP on an active interface."
3. **What is the wildcard mask in the `network` command?**
   "The inverse of the subnet mask: 0.0.0.255 matches any address in a /24."
4. **What is a passive interface?**
   "An interface whose network is still advertised, but no hellos are sent on it, for example a LAN with only PCs and no other routers."

---

## 27. Linux I2C stack: device tree to application

How the driver is matched to the device tree is in [Q12](#q12-what-is-the-structure-of-a-linux-device-driver). The sections below follow one sensor from the DTS file to the application.

### Q90. How do you write the device tree entry for an I2C device, for example one using pin 46?

**In simple words:** An I2C device node is placed **inside its I2C controller's node**. It has three important properties:

- **`reg`**: the 7-bit I2C address.
- **`compatible`**: the string that selects the driver.
- **`interrupts`** and **`interrupt-parent`**: the pin used for the device's interrupt.

**Example:** A TMP117 temperature sensor at 0x48 on I2C1, with its ALERT pin on GPIO 46 = bank 1, pin 14.

> "The I2C device doesn't get its own top-level node. It goes **inside the node of the I2C controller** it's wired to, because that controller is its parent bus. In the controller node I enable it, set the bus speed, and point to the **pinctrl** group that muxes the SDA and SCL pins.
>
> Then the device node has three important things: **`compatible`**, which is how my driver finds it; **`reg`**, which for I2C is the **slave address**; and, if the sensor has an interrupt line, the **GPIO and IRQ** it's connected to.
>
> For 'pin 46': GPIO banks usually have 32 pins each, so pin 46 is bank 1, pin 14, because 46 = 32 + 14. If pin 46 is the interrupt pin, that's what goes in `interrupts`. If 46 is an SDA or SCL pin, it goes in the pinctrl group instead."

```dts
&i2c1 {                                         /* the controller the sensor is wired to */
    pinctrl-names = "default";
    pinctrl-0 = <&i2c1_pins>;                   /* muxes the SDA / SCL pins to I2C */
    clock-frequency = <400000>;                 /* 400 kHz fast mode */
    status = "okay";

    temp_sensor: sensor@48 {                    /* @48 = the I2C address */
        compatible = "vendor,tmp-sensor";       /* the driver matches on this string */
        reg = <0x48>;                           /* I2C slave address */
        interrupt-parent = <&gpio1>;            /* pin 46 = bank 1 (46 / 32), pin 14 (46 % 32) */
        interrupts = <14 IRQ_TYPE_EDGE_FALLING>;
    };
};
```

**Cross-questions:**

1. **What does the `@48` in `sensor@48` mean?**
   "It's the **unit address**, and it must match the first value of `reg`. It makes the node name unique, and `dtc` warns if they don't match."
2. **What are `#address-cells` and `#size-cells` in the I2C controller node?**
   "They define how the children's `reg` is read. For I2C they're 1 and 0: one cell for the address and no size."
3. **What is a phandle, like `&gpio1`?**
   "A reference to another node. Here it says 'my interrupt comes from the gpio1 controller'."
4. **How do you add a device without rebuilding the whole device tree?**
   "With a **device tree overlay**, a `.dtbo` file that U-Boot or the kernel applies on top of the base tree. Raspberry Pi and BeagleBone use these a lot."
5. **How does the driver read a custom property?**
   "With `device_property_read_u32(dev, "vendor,sample-rate", &val)` or `of_property_read_u32()`, usually in probe."

### Q91. How does the application access the I2C device? How does the driver get called?

**In simple words:** An application can reach the device in two ways:

- It opens **`/dev/i2c-N`** and does raw transfers with `ioctl()`, `read()` and `write()`.
- It uses the **files a kernel driver creates**, in sysfs, IIO or `/dev`. In this case, the kernel calls the driver's functions.

**Example:** With a driver: `cat /sys/bus/iio/devices/iio:device0/in_temp_input` prints `25125`, which means 25.125 °C.

> "There are two ways.
>
> **Without a kernel driver**, through `/dev/i2c-1`, using the `i2c-dev` interface. The app opens the device file, sets the slave address with `ioctl(I2C_SLAVE)`, and then calls `read()` and `write()`. That's quick for testing, but the app has to know the sensor's registers.
>
> **The proper way** is a kernel driver for the sensor. It exposes the data through a standard interface, like **IIO** in sysfs, hwmon, input, or a char device. The app just reads a file, for example `/sys/bus/iio/devices/iio:device0/in_temp_raw`, and the kernel calls my driver's callback, like `read_raw()`, which does the I2C transfer. So the app never calls the driver directly: it goes through the VFS, and the subsystem calls my function."

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

/* Option 1: user space talks to the bus directly (i2c-dev).
 * Reads 2 bytes from register 0x00 of the device at 0x48 on bus 1. Returns 0 on success. */
int read_sensor_raw(uint8_t data[2])
{
    int     result = -1;
    uint8_t reg    = 0x00U;
    int     fd     = open("/dev/i2c-1", O_RDWR);        /* opens the bus, not the device */

    if (fd >= 0)
    {
        if ((ioctl(fd, I2C_SLAVE, 0x48) >= 0) &&         /* 1. select the slave address   */
            (write(fd, &reg, 1U) == 1) &&                /* 2. send the register address  */
            (read(fd, data, 2U) == 2))                   /* 3. read the register value    */
        {
            result = 0;
        }
        (void)close(fd);
    }

    /* Note: write() and read() are two transfers with a STOP between them;
     * for a repeated START, use ioctl(fd, I2C_RDWR, ...) with two messages. */
    return result;
}
```

**Cross-questions:**

1. **Which approach is better, and when?**
   "**i2c-dev** for prototyping and simple polling: no kernel code at all. A **kernel driver** for a product: interrupts, power management, several apps sharing the device, and a standard interface that other software understands."
2. **How do you do a register read with a repeated START from user space?**
   "With `ioctl(fd, I2C_RDWR, ...)` and two messages, the write of the register address and the read, which the kernel sends as one combined transaction."
3. **How can you test a device without writing any code?**
   "With i2c-tools: `i2cdetect -y 1` to scan, `i2cget` and `i2cset` for single registers, and `i2cdump` to dump all of them."

### Q92. What is the code flow for an I2C read or write, from the application down to the hardware?

**In simple words:** A request goes down through fixed layers:

**VFS → subsystem → sensor driver → I2C core → controller driver → hardware**

Each layer only calls the layer directly below it, through a defined API.

**Example:** `cat in_temp_input` → `read_raw()` → `i2c_smbus_read_word_data(client, 0x00)` → `stm32f7_i2c_xfer()` → bytes on SDA/SCL → 25125 back to the terminal.

> "It goes through four layers. The app calls `read()`. The **VFS** passes it to the subsystem, which calls my **sensor driver**. My driver doesn't touch any registers; it calls the **I2C core**, with something like `i2c_smbus_read_byte_data()` or `i2c_transfer()`. The I2C core passes the message to the **controller driver** for that SoC, through the adapter's `master_xfer` function. The controller driver programs the I2C peripheral's registers, the bytes go out on the wire, and when the transfer completes, an interrupt wakes up the waiting thread and the data travels back up the same path."

```text
App: read("/sys/.../in_temp_raw")
  → VFS → IIO subsystem → sensor driver's read_raw()
  → I2C core: i2c_smbus_read_word_data(client, reg) / i2c_transfer()
  → adapter->algo->master_xfer()      (the SoC's controller driver, e.g. i2c-imx, i2c-stm32f7)
  → I2C controller registers → SDA/SCL → sensor
  ← interrupt: transfer complete → data returned up the same path
```

| Layer | Knows about | Example |
| --- | --- | --- |
| **Application** | Files | `read()` on sysfs or `/dev` |
| **Sensor (client) driver** | The sensor's registers | `tmp_read_raw()` |
| **I2C core** | Generic I2C messages | `i2c_transfer()`, `i2c_smbus_*()` |
| **Controller (adapter) driver** | The SoC's I2C registers | `stm32f7_i2c_xfer()` |

**Cross-questions:**

1. **Is the calling thread blocked during the transfer?**
   "Yes. The controller driver starts the transfer and sleeps on a **completion**; the controller's interrupt wakes it. That's exactly why I2C can't be used in a hard IRQ ([Q14](#q14-can-you-perform-an-i2c-transfer-inside-a-hard-irq-handler))."
2. **What's the difference between SMBus and I2C?**
   "SMBus is a stricter subset, with defined command formats, timeouts and voltage levels. The `i2c_smbus_*()` helpers use those formats, and the I2C core emulates them on a plain I2C adapter."
3. **What is regmap?**
   "A layer over I2C and SPI register access, with caching, range checks and debugfs access. Many drivers use `regmap_read()` and `regmap_write()` instead of raw I2C calls, so the same driver code works on both buses."
4. **How do errors come back up?**
   "As negative error codes: `-ENXIO` or `-EREMOTEIO` for a NACK, `-ETIMEDOUT`, `-EAGAIN` for lost arbitration. The app finally sees `-1` from `read()`, with `errno` set."

### Q93. How does the middle layer connect to the platform layer? How does it know which I2C controller driver to use?

**In simple words:** The controller driver registers an **`i2c_adapter`**. The adapter has an **`i2c_algorithm`** structure that holds the controller's `master_xfer` function.

Each I2C device keeps a pointer to its adapter. So `i2c_transfer()` simply calls `adapter->algo->master_xfer()`.

**Example:** A sensor under `&i2c2` in the device tree → its client points to adapter i2c-2 → `i2c_transfer()` calls i2c-2's `master_xfer`.

> "Through **registration and a pointer**. When the SoC's I2C **controller driver** probes, it registers an **`i2c_adapter`** with the I2C core, and that adapter carries an ops structure, `i2c_algorithm`, with a function pointer to its `master_xfer`.
>
> Then each device node that's a **child** of that controller in the device tree becomes an **`i2c_client`**, and the client keeps a pointer to its adapter. So when my sensor driver calls `i2c_transfer(client->adapter, ...)`, the core simply calls `adapter->algo->master_xfer()`. The sensor driver never knows which SoC it's on; the device tree's parent-child structure decides it.
>
> It's the same idea I'd use on an MCU without Linux: a struct of **function pointers** filled in by the platform layer, like in [Q42](#q42-are-function-pointers-basically-used-for-callbacks)."

```c
/* Platform (controller) side: filled in once, in the controller driver's probe() */
static const struct i2c_algorithm stm32_i2c_algo = {
    .master_xfer   = stm32f7_i2c_xfer,              /* the SoC-specific transfer function */
    .functionality = stm32f7_i2c_func,              /* what this controller supports      */
};
adap->algo = &stm32_i2c_algo;
i2c_add_adapter(adap);                              /* now the I2C core knows this bus    */

/* Middle layer (I2C core), simplified: locking and retries are left out */
int i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
    return adap->algo->master_xfer(adap, msgs, num);    /* calls whichever SoC registered */
}
```

**Cross-questions:**

1. **What if the SoC has several I2C controllers?**
   "Each one registers its own adapter: i2c-0, i2c-1 and so on. Each device node belongs to whichever controller is its parent in the device tree, so its client points to that adapter."
2. **What else does the I2C core do?**
   "It locks the bus so one transfer runs at a time, handles retries and bus recovery, creates the clients from the device tree, and matches them with drivers."
3. **Is SPI built the same way?**
   "Yes: `spi_controller` with its `transfer_one()` on the platform side, `spi_device` for each chip, and `spi_sync()` in the middle."
4. **Why all this layering?**
   "So the same sensor driver works on any SoC. Only the controller driver is chip-specific."

### Q94. What is the complete flow of a sensor defined in the DTS, from the device tree to the data in the application?

**In simple words:** The flow has five steps:

1. The **DTB** describes the hardware, and the kernel creates devices from it.
2. The I2C controller's probe registers the bus.
3. The bus creates a device for each child node.
4. The `compatible` string selects the driver.
5. The driver's probe makes the data available to user space.

**Example:** A BME280 node in the DTS → after boot, `/sys/bus/iio/devices/iio:device0/` exists, and reading `in_pressure_input` returns the pressure.

> "I'll go from build time to run time.
>
> 1. I describe the sensor in the **DTS** under its I2C controller, and the device tree compiler turns it into a **DTB**.
> 2. The **bootloader**, U-Boot, loads the kernel and the DTB and passes the DTB's address to the kernel.
> 3. The kernel parses the DTB into a tree of device nodes.
> 4. The **I2C controller** node matches its controller driver, which probes and registers an **adapter** for that bus.
> 5. While registering, the I2C core walks the controller's **child nodes** and creates an **`i2c_client`** for each one, with its address from `reg`.
> 6. The bus compares the client's **`compatible`** string with every I2C driver's match table. When it matches my sensor driver, it calls my **`probe()`**.
> 7. In probe, I read the chip ID to check it's really there, configure it, request the IRQ, and register with a subsystem like **IIO**, which creates the sysfs files.
> 8. The **app** reads a sysfs file, and the call goes down through my driver and the I2C core to the controller, as in [Q92](#q92-what-is-the-code-flow-for-an-i2c-read-or-write-from-the-application-down-to-the-hardware)."

```text
DTS → dtc → DTB → U-Boot passes DTB → kernel parses it
→ I2C controller probe → i2c_adapter registered → child nodes become i2c_clients
→ compatible matches → sensor probe() → register IIO / input / char device
→ app reads /sys or /dev → driver → I2C core → controller → sensor → data back up
```

**Cross-questions:**

1. **When is the DTS compiled?**
   "During the kernel build, with `make dtbs`. The `.dtb` files end up under `arch/arm64/boot/dts/<vendor>/`."
2. **How do you confirm the node reached the running kernel?**
   "Look in `/proc/device-tree/` (or `/sys/firmware/devicetree/base/`): every node and property is there. If the node is missing, the bootloader loaded an old DTB."
3. **The driver is a module. Who loads it?**
   "**udev**. The device has a modalias generated from the `compatible` string, and `MODULE_DEVICE_TABLE` puts the same string in the module, so udev runs `modprobe` for the matching module."
4. **What if the sensor isn't actually connected?**
   "Probe reads the chip ID, the read fails or returns a wrong value, and probe returns `-ENODEV`. No device is registered, and `dmesg` shows the error."

### Q95. How does the driver get matched with the device tree node?

**In simple words:** The bus compares the device's **`compatible`** string with every driver's **`of_match_table`**. When it finds a match, the kernel calls that driver's `probe()` function with the device.

**Example:** The DTS says `compatible = "ti,tmp117"`, and the tmp117 driver's table contains `"ti,tmp117"`, so the kernel calls its `probe()`.

> "By the **`compatible` string**. My driver has an `of_device_id` table with the same string as the DTS node. When either one appears, the device when the DTB is parsed or the driver when the module is loaded, the bus compares the strings, and on a match it calls `probe()` with that device.
>
> `MODULE_DEVICE_TABLE(of, ...)` exports the table, so **udev** can auto-load the right module. If probe never gets called, I check: does the string match exactly, is the node `status = "okay"`, is it under the right parent bus, and is the driver actually built and loaded. `/sys/bus/i2c/devices/` tells me whether the client was created at all."

**Cross-questions:**

1. **What other ways can a driver be matched?**
   "Besides the device tree's `compatible`, there's ACPI on x86 systems, and the old `i2c_device_id` table, which matches by name. The kernel tries the device tree first, then ACPI, then the ID table."
2. **Can one driver support several chips?**
   "Yes: several `compatible` entries, each with a `.data` pointer to that variant's details. In probe I call `of_device_get_match_data()` to get the right one."
3. **What's the format of a compatible string?**
   "`"vendor,device"`. A node can list several, most specific first, like `"vendor,tmp117", "vendor,tmp-generic"`, so a generic driver can take over if no specific one exists."

---

## 28. Embedded Linux boot and STM32 bring-up debugging

### Q96. What happens when an embedded Linux system powers on? What is the boot flow?

**In simple words:** Each boot stage sets up a bit more hardware, then loads the next stage:

1. **ROM** loads the SPL.
2. **SPL** sets up DRAM and loads U-Boot.
3. **U-Boot** loads the kernel and the DTB.
4. The **kernel** starts the drivers and mounts the root filesystem.
5. **init** starts user space.

**Example:** On a BeagleBone: ROM → MLO (SPL) → u-boot.img → zImage + am335x-boneblack.dtb → systemd → the app, all visible on the serial console.

> "It's a chain where each stage loads the next one.
>
> 1. **Boot ROM**: the SoC vendor's code, built into the chip. It reads the boot-mode pins and loads the first stage from eMMC, SD, NAND or SPI flash into internal SRAM, because DRAM isn't set up yet.
> 2. **SPL**, the first-stage loader: it initializes the clocks and **DRAM**, then loads the full bootloader into DRAM.
> 3. **U-Boot**: it initializes more hardware, reads its environment, and loads the **kernel image**, the **DTB** and maybe an initramfs into RAM. Then it jumps to the kernel and passes the kernel command line and the DTB address.
> 4. **Kernel**: it decompresses itself, sets up the MMU, memory and the scheduler, parses the DTB, probes the drivers, and **mounts the root filesystem**.
> 5. **init**: the kernel starts the first user process, PID 1, which is systemd, BusyBox init or SysV init. That starts the services, and finally **my application**.
>
> When a board doesn't boot, I check the serial console to see which stage it stopped in."

```text
Power on → Boot ROM → SPL (DRAM init) → U-Boot → kernel + DTB (+ initramfs)
→ drivers probe, rootfs mounted → init (PID 1) → services → application
```

More detail: [Linux and IoT bootloader notes](../Linux_and_IoT/Bootloader.md).

**Cross-questions:**

1. **What's in the kernel command line?**
   "Things like `console=ttyS0,115200` for the log output, `root=` for the root filesystem, `rootfstype=`, `init=` and `loglevel=`. U-Boot passes it in the `bootargs` variable."
2. **What is an initramfs for?**
   "A small root filesystem in RAM for early user space: loading modules or unlocking storage before the real root filesystem can be mounted."
3. **How does U-Boot pass the DTB to the kernel?**
   "In a register: **x0** on arm64, **r2** on 32-bit Arm, holding the DTB's address in RAM."
4. **How do you make it boot faster?**
   "Skip stages, like U-Boot's Falcon mode, where SPL loads the kernel directly. Remove unused drivers, use an uncompressed or faster-decompressing kernel, and delay non-critical services. I measure with `systemd-analyze` or timestamps on the console."
5. **How does secure boot fit in?**
   "Each stage verifies the signature of the next one before running it: ROM checks SPL, SPL checks U-Boot, U-Boot checks the kernel and DTB, usually as a signed FIT image."

### Q97. A brand-new STM32 board: the firmware flashes successfully, but it doesn't come up. How do you debug it?

**Also asked as:** *How would you debug it as someone who knows both the hardware and the software?*

**In simple words:** If flashing works, the CPU core, the SWD connection and the power are basically fine. That leaves three likely causes:

- **Boot configuration:** BOOT0 or the option bytes.
- **Clock start-up:** HSE, PLL or flash wait states.
- **Early firmware faults.**

The debugger can show all three.

**Example:** The halted PC is in `HAL_RCC_OscConfig()`, waiting for the HSE-ready flag. Switching to the internal HSI makes the board run, so the crystal circuit is the problem.

> "Since flashing worked, I know power is there and SWD works, so the chip is alive. Now I split the problem in two: **is it hardware, or is it my firmware?**
>
> **Hardware first, because it's quick with a multimeter and a scope:**
>
> - The **supply rails**: is 3.3 V really 3.3 V, including VDDA. On an F4, are the **VCAP** capacitors fitted?
> - **NRST**: is it high, or is something holding the chip in reset?
> - **BOOT0**: is it pulled **low**? If it's floating or high, the chip boots the system memory bootloader instead of my flash.
> - The **crystal**: is it oscillating, with the right load capacitors? A dead HSE is the most common bring-up problem I've seen.
>
> **Then firmware, with the debugger:**
>
> - I connect **without resetting**, halt, and look at the **PC**. That tells me straight away where it's stuck: a HardFault handler, the `Error_Handler()` loop, or a wait loop in the clock setup.
> - If it's stuck in **`SystemClock_Config()`** waiting for HSE ready, it's the crystal. As a test I switch to the **internal HSI** oscillator: if the board then runs, the problem is confirmed.
> - If it's in **HardFault**, I read the fault registers and the stacked PC.
> - And I add an **early sign of life**: toggle an LED as the very first thing in `main()`, before the clock setup, so I know how far it gets."

**Cross-questions:**

1. **Flashing works but running doesn't. How can that be?**
   "Flashing runs on the default internal clock through SWD. My firmware then switches to the **HSE and PLL**. If the crystal doesn't start, it hangs there. If the **flash wait states** aren't set for the higher clock, the CPU reads garbage from flash and faults."
2. **How do you check whether the crystal oscillates?**
   "Measuring it directly with a scope can stop it, because the probe adds capacitance, so I use a 10x probe. Better: route the clock to the **MCO pin** and measure it there."
3. **After running your firmware, the debugger can't connect any more. Why?**
   "The firmware might reconfigure the SWD pins (PA13 and PA14) as GPIO, or enter a low-power mode. I connect with **'connect under reset'**, which holds NRST low and halts the core before my code runs."
4. **What about the power-up itself?**
   "A slow or noisy supply ramp can keep the chip in reset, or make it reset repeatedly. I check the brown-out reset level in the option bytes, and look at the supply with a scope during power-up."

### Q98. Fresh board, nothing connected, and the firmware never reaches `main()`. How do you debug it?

**In simple words:** Several steps happen before `main()`:

1. The CPU loads SP and PC from the **vector table**.
2. `Reset_Handler` runs `SystemInit()`.
3. It copies `.data` from flash to RAM.
4. It fills `.bss` with zeros.
5. It runs the C++ constructors and calls `main()`.

If any of these steps fails, the code never reaches `main()`.

**Example:** A linker script for a 128 KB-RAM part is used on a 64 KB-RAM part. `_estack` is 0x20020000, which doesn't exist, so the very first stack push faults before `main()`.

> "If it never reaches main, the problem is between reset and main, so I follow the reset sequence with the debugger.
>
> 1. **The vector table.** I read the first two words at 0x08000000. Word 0 is the initial stack pointer, so it must point to the end of RAM, like 0x20020000. Word 1 is the Reset_Handler address, and it must be odd, for Thumb mode, and inside flash. If they're 0xFFFFFFFF, the code isn't where the chip boots from.
> 2. **The linker script.** It must match the exact part number. A really common mistake is a linker script for a bigger chip: then `_estack` points beyond the real RAM, and the very first push to the stack HardFaults. Or the flash origin is wrong, for example the app is linked for 0x08008000 but there's no bootloader there to jump to it.
> 3. **A breakpoint on `Reset_Handler`.** If it's never hit, it's the boot mode (BOOT0 or the option bytes) or the vector table. If it is hit, I step through it: `SystemInit()`, the `.data` copy loop, the `.bss` zero loop, the C++ constructors, and see which one doesn't return.
> 4. **`SystemInit()`.** It enables the FPU and sets VTOR. If the code uses floating point and the FPU isn't enabled, it faults right away.
> 5. **If there's a bootloader jumping to my app**, I check that the app's VTOR is set to its own vector table, that the MSP is loaded from the app's word 0, and that interrupts and SysTick were stopped before the jump."

```text
Reset → read MSP (word 0) and Reset_Handler (word 1) from the vector table
      → Reset_Handler → SystemInit() → copy .data → zero .bss → constructors → main()
Check each arrow with the debugger; where it stops is the bug.
```

**Cross-questions:**

1. **The vector table reads 0xFFFFFFFF. What does that mean?**
   "That flash is **erased**: the code was programmed somewhere else, or not at all. I check the linker script's flash origin and the address the programmer used."
2. **Why must the Reset_Handler address be odd?**
   "Bit 0 is the **Thumb** bit, and Cortex-M only runs Thumb code. An even address gives an INVSTATE fault immediately. The toolchain sets the bit automatically, as long as the symbol is marked as a function."
3. **What is lockup?**
   "A fault inside the HardFault handler, or a fault before the HardFault handler can even be fetched. The core just stops, and the debugger shows a PC like 0xFFFFFFFE. It usually points to a broken vector table or stack pointer."
4. **How do you see where it stopped without any breakpoint?**
   "Halt the core, read the PC, and look it up in the map file or with `addr2line`. That one address usually tells me which function is stuck."

---

## 29. C strings, arrays and pointers

### Q99. How do you find whether string 2 is inside string 1, without library functions?

**In simple words:** Try every starting position `i` in string 1. From that position, compare string 2 one character at a time.

If every character of string 2 matches before its `'\0'`, string 2 was found at position `i`.

**Example:** "Singh" in "Rajbir Singh": at index 0, 'R' ≠ 'S', move on... at index 7, 'S', 'i', 'n', 'g', 'h' all match, so the answer is 7.

Example: `STR1 = "Rajbir Singh"`, `STR2 = "Singh"`.

> "I try each starting position in string 1. From there, I compare character by character with string 2. If I reach the end of string 2 with no mismatch, it's found, and I return that start index. If there's a mismatch, I move to the next start position. For 'Singh' in 'Rajbir Singh' it returns 7. It's O(n × m), which is fine for short strings; for long texts there's KMP, which is O(n + m)."

```c
#include <stdio.h>
#include <stdint.h>

/* Returns the index of the first occurrence of sub in str, or -1 if not found */
int32_t find_sub_string(const char *str, const char *sub)
{
    int32_t result = -1;
    int32_t i      = 0;

    if ((str != NULL) && (sub != NULL))
    {
        while ((str[i] != '\0') && (result < 0))                 /* each start position, until found */
        {
            int32_t j = 0;

            while ((sub[j] != '\0') && (str[i + j] == sub[j]))   /* compare while characters match   */
            {
                j++;
            }

            if (sub[j] == '\0')                                  /* reached the end of sub: match    */
            {
                result = i;
            }
            i++;
        }
    }

    return result;                                               /* single exit point                */
}

int main(void)
{
    int32_t pos = find_sub_string("Rajbir Singh", "Singh");

    if (pos >= 0)
    {
        (void)printf("Found at index %ld\n", (long)pos);         /* 7 */
    }
    else
    {
        (void)printf("Not found\n");
    }

    return 0;
}
```

**Output:**

```text
Found at index 7
```

**Cross-questions:**

1. **What's the idea behind KMP?**
   "It precomputes, for every prefix of the pattern, how far you can fall back when a mismatch happens. So it never moves backwards in the text, giving O(n + m)."
2. **How do you find all the occurrences?**
   "Don't return at the first match. Print or store the index, and continue with the next start position."
3. **What edge cases do you check?**
   "An empty pattern, which matches at 0; a pattern longer than the text, which returns −1; and NULL pointers, which I check at the start."
4. **Case-insensitive search?**
   "Compare `tolower()` of both characters instead of the characters themselves."

### Q100. What is an array of pointers?

**In simple words:** An array of pointers is an array where **each element is an address**.

With strings, each element points to a separate string, and the strings can have different lengths.

**Example:** `msgs[2]` holds the address of "CRC ERROR", so `printf("%s", msgs[2])` prints CRC ERROR.

> "It's an array where every element is a pointer. The most common use is a table of strings, like error messages or command names: each element points to a string of a different length, so I don't waste memory the way a 2D char array would. A table of function pointers is also an array of pointers.
>
> It's easy to mix up with a **pointer to an array**, so I read the declaration carefully: `int *p[3]` is three pointers, but `int (*p)[3]` is one pointer to an array of three ints."

```c
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /* Array of 3 pointers, each to a string of any length.
     * const char * const msgs[3] would also make the table itself read-only, so it can live in flash. */
    const char *msgs[3] = { "OK", "TIMEOUT", "CRC ERROR" };

    int32_t  values[3] = { 10, 20, 30 };
    int32_t  *a[3];             /* array of 3 pointers to int32_t       */
    int32_t (*b)[3];            /* one pointer to an array of 3 int32_t */
    uint32_t i;

    for (i = 0U; i < 3U; i++)
    {
        (void)printf("msgs[%lu] = \"%s\"\n", (unsigned long)i, msgs[i]);
    }

    for (i = 0U; i < 3U; i++)
    {
        a[i] = &values[i];      /* each element points to one int */
    }
    b = &values;                /* points to the whole array      */

    (void)printf("*a[1]   = %ld\n", (long)*a[1]);
    (void)printf("(*b)[2] = %ld\n", (long)(*b)[2]);
    (void)printf("sizeof(a) = %zu (3 pointers), sizeof(b) = %zu (1 pointer)\n", sizeof(a), sizeof(b));

    return 0;
}
```

**Output:**

```text
msgs[0] = "OK"
msgs[1] = "TIMEOUT"
msgs[2] = "CRC ERROR"
*a[1]   = 20
(*b)[2] = 30
sizeof(a) = 24 (3 pointers), sizeof(b) = 8 (1 pointer)
```

**Cross-questions:**

1. **Array of pointers vs a 2D char array: how much memory?**
   "`const char *msgs[3]` is 3 pointers plus each string at its exact length. `char msgs[3][10]` is always 30 bytes, every row padded to the longest. The 2D array wastes space but its strings are writable."
2. **How do you pass an array of pointers to a function?**
   "As `const char *arr[]` or `const char **arr`, which mean the same thing, plus the count. `main`'s `argv` is exactly this."
3. **Can you change `msgs[0][0]`?**
   "No, the strings are literals in read-only memory, as in [Q72](#q72-char-str--hello-vs-const-char-p--hello-whats-the-difference-and-can-you-modify-them). But I can make `msgs[0]` point to a different string."

### Q101. What is the difference between an array and a pointer? What is array-to-pointer conversion?

**In simple words:** - An **array** is a block of memory that holds its elements.
- A **pointer** is a variable that holds one address.

In most expressions, the name of an array is **automatically converted to a pointer** to its first element.

**Example:** `int arr[5]`: `sizeof(arr)` = 20, the whole row. `int *ptr = arr`: `sizeof(ptr)` = 8, just the paper.

> "An **array** is a block of memory that holds the elements. A **pointer** is a variable that holds an address. They look alike, because in most expressions the array's name **decays** into a pointer to its first element. That's why `arr[i]` and `*(arr + i)` mean the same thing, and why I can pass an array to a function that takes a pointer.
>
> But they're not the same. `sizeof(arr)` gives the whole array, while `sizeof(ptr)` gives just the pointer size. I can't assign to an array name, but I can move a pointer. And inside a function, an `int a[]` parameter is really just a pointer, so `sizeof` there gives 4 or 8, not the array size. That's why I always pass the length as well."

| | `int arr[5];` | `int *ptr = arr;` |
| --- | --- | --- |
| What it is | 5 ints of storage | A variable holding an address |
| `sizeof` | 20 (5 × 4) | 4 or 8 |
| Can be reassigned? | No | Yes: `ptr++`, `ptr = other` |
| `&arr` / `&ptr` | Pointer to the whole array (`int (*)[5]`) | Address of the pointer variable |
| As a function parameter | Decays to `int *` | `int *` |

Where an array does **not** decay: `sizeof arr`, `&arr`, and a string literal used to initialize a `char` array.

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* An array parameter is really a pointer: the size is lost, so the length is passed separately.
 * (gcc even warns: sizeof on an array parameter returns the size of a pointer.) */
static int32_t sum(const int32_t arr[], size_t len)
{
    int32_t total = 0;
    size_t  i;

    (void)printf("inside sum(): sizeof(arr) = %zu (just a pointer)\n", sizeof(arr));
    for (i = 0U; i < len; i++)
    {
        total += arr[i];
    }
    return total;
}

int main(void)
{
    int32_t  arr[5] = { 1, 2, 3, 4, 5 };
    int32_t *ptr    = arr;                     /* the array name converts to &arr[0] */

    (void)printf("sizeof(arr) = %zu (the whole array)\n", sizeof(arr));
    (void)printf("sizeof(ptr) = %zu (one pointer)\n", sizeof(ptr));
    (void)printf("arr[2] = %ld, *(arr + 2) = %ld, ptr[2] = %ld\n",
                 (long)arr[2], (long)*(arr + 2), (long)ptr[2]);

    /* Same address, different types: arr + 1 moves one int, &arr + 1 moves the whole array */
    (void)printf("(char *)(arr + 1)  - (char *)arr = %ld bytes\n", (long)((char *)(arr + 1) - (char *)arr));
    (void)printf("(char *)(&arr + 1) - (char *)arr = %ld bytes\n", (long)((char *)(&arr + 1) - (char *)arr));

    (void)printf("sum = %ld\n", (long)sum(arr, 5U));

    return 0;
}
```

**Output:**

```text
sizeof(arr) = 20 (the whole array)
sizeof(ptr) = 8 (one pointer)
arr[2] = 3, *(arr + 2) = 3, ptr[2] = 3
(char *)(arr + 1)  - (char *)arr = 4 bytes
(char *)(&arr + 1) - (char *)arr = 20 bytes
inside sum(): sizeof(arr) = 8 (just a pointer)
sum = 15
```

**Cross-questions:**

1. **`arr` and `&arr` print the same address. What's the difference?**
   "They have different **types**. `arr` decays to `int *`, so `arr + 1` moves 4 bytes. `&arr` is `int (*)[5]`, a pointer to the whole array, so `&arr + 1` moves 20 bytes. It's a classic trick question."
2. **How do you pass a 2D array to a function?**
   "The column count must be known: `void f(int a[][COLS], int rows)`, which is really `int (*a)[COLS]`."
3. **Is `i[arr]` valid?**
   "Yes, believe it or not: `arr[i]` is defined as `*(arr + i)`, and addition is commutative. It's never something to write in real code."

---

## 30. C code review: strings and returning buffers

The code these questions refer to typically looks like this (reconstructed):

```c
#include <string.h>

/* The code under review: find the problems */
char *get_status_message(int status)
{
    char msg[20];                           /* local array: lives on the stack */

    if (status == 0)
    {
        (void)strcpy(msg, "OK");
    }
    else
    {
        (void)strcpy(msg, "ERROR");
    }
    return msg;                             /* BUG: msg is destroyed on return (dangling pointer) */
}

/* Returns the length of str, like strlen() */
int smallFunction(const char *str)
{
    const char *pt = str;

    while (*pt != '\0')                     /* move pt to the terminating '\0' */
    {
        pt++;
    }
    return pt - str;                        /* pointer difference = number of characters */
}

/* Appends src to the end of dst, like strcat() */
void BigFunction(char *dst, const char *src)
{
    char *end = dst + smallFunction(dst);   /* first byte after dst's text */

    while (*src != '\0')
    {
        *end++ = *src++;                    /* RISK: nothing checks that dst is big enough */
    }
    *end = '\0';
}
```

### Q102. What is wrong with `get_status_message()`?

**In simple words:** A local array exists only **while its function is running**. After the function returns, its stack memory is reused.

So returning the array's address gives the caller a pointer to memory that no longer belongs to it.

**Example:** `printf("%s", get_status_message(0));` might print "OK" in a quick test, but after one more function call the same stack area is reused and it prints garbage.

> "It returns a pointer to **`msg`, which is a local array on the stack**. As soon as the function returns, that stack memory is gone, so the caller gets a **dangling pointer**. It might even print correctly in a quick test, because nothing has overwritten that memory yet. But the next function call reuses the same stack area and the message turns into garbage. It's undefined behaviour, and the compiler usually warns: 'function returns address of local variable'."

**Cross-questions:**

1. **Why does it sometimes work in testing?**
   "The stack memory isn't cleared after the return; it's just free. Until another function call reuses it, the old text is still there, so a quick test can pass."
2. **How do you catch this kind of bug?**
   "Compiler warnings (`-Wall` gives 'returns address of local variable'), static analysis, and AddressSanitizer on a PC build, which catches stack-use-after-return at run time."

### Q103. If you don't want to pass another buffer, how would you fix it? Can it be one line?

**In simple words:** String literals have **static storage duration**: they exist for the whole time the program runs. So returning a pointer to a string literal is always safe.

**Example:** `get_status_message(0)` returns the address of "OK" in flash, which stays valid for the whole run of the program.

> "The messages are fixed text, so I don't need a buffer at all. I just return the **string literal**. String literals live in read-only memory for the whole program, so the pointer stays valid. I make the return type `const char *`, so nobody can try to modify it. And yes, then it's one line."

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Fixed: string literals live for the whole program, so returning a pointer to one is safe */
const char *get_status_message(int32_t status)
{
    return (status == 0) ? "OK" : "ERROR";
}

/* Returns the length of str, like strlen() */
size_t smallFunction(const char *str)
{
    const char *pt = str;

    while (*pt != '\0')                     /* move pt to the terminating '\0' */
    {
        pt++;
    }
    return (size_t)(pt - str);              /* pointer difference = number of characters */
}

/* Appends src to the end of dst, like strcat(); dst must be big enough (see Q105 for a safe version) */
void BigFunction(char *dst, const char *src)
{
    size_t end = smallFunction(dst);        /* index of dst's '\0' */
    size_t i   = 0U;

    while (src[i] != '\0')
    {
        dst[end] = src[i];
        end++;
        i++;
    }
    dst[end] = '\0';
}

int main(void)
{
    char text[32] = "Status: ";             /* big enough for both parts */

    (void)printf("get_status_message(0) = %s\n", get_status_message(0));
    (void)printf("get_status_message(5) = %s\n", get_status_message(5));

    (void)printf("smallFunction(\"Hello\") = %zu\n", smallFunction("Hello"));

    BigFunction(text, get_status_message(0));
    (void)printf("BigFunction result = \"%s\" (length %zu)\n", text, smallFunction(text));

    return 0;
}
```

**Output:**

```text
get_status_message(0) = OK
get_status_message(5) = ERROR
smallFunction("Hello") = 5
BigFunction result = "Status: OK" (length 10)
```

> "The other fix is a **`static char msg[20]`**: it's not on the stack, so it survives. But then every call overwrites the same buffer, and it's not thread-safe, so I'd only do that if the message really has to be built at run time. For many status codes, I'd use a `const char *` table indexed by the status, like [Q100](#q100-what-is-an-array-of-pointers)."

**Cross-questions:**

1. **What goes wrong with the `static` buffer version?**
   "Every call returns the **same buffer**. `printf("%s %s", f(0), f(1))` prints the same message twice, because the second call overwrote the first. And two threads calling it at once corrupt each other's text."
2. **And if the message really has to be built at run time?**
   "Then the caller passes the buffer and its size: `int get_status_message(int status, char *buf, size_t len)`, and inside I use `snprintf(buf, len, ...)`, which never overflows."

### Q104. What do `smallFunction()` and `BigFunction()` do? How does `pt - str` give the length?

**In simple words:** Subtracting two pointers into the same array gives the **number of elements between them**. For `char`, each element is one character, so the result is the length of the string.

**Example:** `str` is at 1000, `pt` stops on the `'\0'` at 1005: 1005 − 1000 = **5** characters.

> "**`smallFunction()` is `strlen()`.** It starts a pointer `pt` at the beginning of the string and moves it forward until it reaches the `'\0'`. Then `pt - str` is **pointer subtraction**: when you subtract two pointers into the same array, C gives you the **number of elements between them**. For `char`, one element is one byte, so it's simply the byte difference. So if `str` is at 1000 and `pt` stopped at 1005 on the terminator, the length is 5.
>
> **`BigFunction()` is `strcat()`.** It uses `smallFunction()` to find the end of `dst`, then copies `src` character by character from there, and finally writes a new `'\0'`."

```text
str = "Hello":   H   e   l   l   o   \0
address:        1000 1001 1002 1003 1004 1005
                 ↑ str                      ↑ pt
pt - str = 1005 - 1000 = 5
```

**Cross-questions:**

1. **What type does `pt - str` have?**
   "`ptrdiff_t`, a signed type. A length should really be `size_t`, so the function should return `size_t` and cast. `int` would overflow for strings over 2 GB, which matters on 64-bit systems."
2. **What if `str` is NULL?**
   "It dereferences NULL and crashes. Library `strlen` doesn't check either, but in my own code I add the check, or document that NULL isn't allowed."
3. **What if `src` and `dst` overlap in `BigFunction()`?**
   "That's undefined, exactly like `strcat`: the copy could overwrite the source before reading it, and never find the end."

### Q105. What can go wrong with returning local buffers, and with appending when the destination is too small?

**In simple words:** C's copy functions **do not check the size of the destination**.

If you write past the end of an array, you overwrite whatever comes next in memory. That can be other variables, or the function's return address.

**Example:** `char buf[8] = "abc"; strcat(buf, "defghij");` writes 11 bytes into an 8-byte buffer, and the 3 extra bytes overwrite the next variable on the stack.

> "**Returning a local** gives a dangling pointer: it works by luck in testing and corrupts later. The fixes are returning a literal, a `static` buffer, a buffer the caller passes in, or `malloc`, but then the caller has to free it.
>
> **Appending into a buffer that's too small** is a **buffer overflow**. `BigFunction()` has no idea how big `dst` is, so it just keeps writing past the end, over other variables, the return address, or other data on the stack. That causes crashes much later, in some unrelated place, and it's a classic security hole. The fix is to pass the **destination size** and stop when it's full, always leaving room for the `'\0'`."

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Appends src to dst without ever writing past dst_size bytes; always terminates dst.
 * Returns 0 if all of src fitted, -1 if it was truncated or a parameter is invalid. */
int32_t safe_append(char *dst, size_t dst_size, const char *src)
{
    int32_t result = -1;

    if ((dst != NULL) && (src != NULL) && (dst_size > 0U))
    {
        size_t len = 0U;        /* current length of dst */
        size_t i   = 0U;        /* index into src        */

        while ((len < (dst_size - 1U)) && (dst[len] != '\0'))   /* find the end of dst, within the buffer */
        {
            len++;
        }

        while ((src[i] != '\0') && ((len + 1U) < dst_size))     /* copy while there is room for '\0'      */
        {
            dst[len] = src[i];
            len++;
            i++;
        }
        dst[len] = '\0';

        if (src[i] == '\0')
        {
            result = 0;                                         /* everything fitted */
        }
    }

    return result;
}

int main(void)
{
    char    small[8] = "abc";       /* room for 7 characters + '\0' */
    char    big[16]  = "abc";
    int32_t rc;

    rc = safe_append(big, sizeof(big), "def");
    (void)printf("big  : \"%s\", result %ld\n", big, (long)rc);

    rc = safe_append(small, sizeof(small), "defghij");          /* 10 characters don't fit in 8 bytes */
    (void)printf("small: \"%s\", result %ld (truncated, no overflow)\n", small, (long)rc);

    return 0;
}
```

**Output:**

```text
big  : "abcdef", result 0
small: "abcdefg", result -1 (truncated, no overflow)
```

**Cross-questions:**

1. **Aren't `strncpy` and `strncat` the safe versions?**
   "Not really. `strncpy` doesn't add a `'\0'` if the source is too long. `strncat`'s `n` is the number of characters to **append**, not the buffer size, which people get wrong all the time. I prefer `snprintf`, or `strlcpy`/`strlcat` where available."
2. **How do you detect stack buffer overflows?**
   "`-fstack-protector` puts a canary value before the return address and checks it when the function returns. On an MCU, an **MPU guard region** below the stack faults immediately on overflow, and FreeRTOS can check the stack's high-water mark."

---

## 31. Bit macros and bitwise arithmetic

### Q106. An 8-bit register has an LED on bit 3 and a buzzer on bit 5. How do you write macros for LED ON, OFF and TOGGLE?

**In simple words:** Each macro uses a **one-bit mask** with one bitwise operator:

- **OR** sets the bit.
- **AND** with the inverted mask clears the bit.
- **XOR** toggles the bit.

All the other bits stay unchanged.

**Example:** The register is 0x20 (buzzer on). `LED_ON` → 0x28 (both on). `LED_TOGGLE` → 0x20 (LED off, buzzer still on).

> "I define the bit positions once, so nobody has magic numbers in the code. Then ON is an **OR** with the mask, OFF is an **AND with the inverted mask**, and TOGGLE is an **XOR**. I put brackets around every macro parameter and the whole expression, and use `1U`. Because these only touch their own bit, the buzzer on bit 5 is never affected when I switch the LED."

```c
#include <stdio.h>
#include <stdint.h>

#define LED_BIT          (3U)                       /* LED on bit 3      */
#define BUZZER_BIT       (5U)                       /* buzzer on bit 5   */
#define BIT_MASK(b)      ((uint8_t)(1U << (b)))     /* a 1 at bit b only */

/* Dir 4.9 (advisory) prefers functions to function-like macros; macros are used here because the question asks for them */
#define LED_ON(reg)      ((reg) |= BIT_MASK(LED_BIT))                     /* set bit 3    */
#define LED_OFF(reg)     ((reg) &= (uint8_t)(~BIT_MASK(LED_BIT)))         /* clear bit 3  */
#define LED_TOGGLE(reg)  ((reg) ^= BIT_MASK(LED_BIT))                     /* toggle bit 3 */

#define BUZZER_ON(reg)   ((reg) |= BIT_MASK(BUZZER_BIT))
#define BUZZER_OFF(reg)  ((reg) &= (uint8_t)(~BIT_MASK(BUZZER_BIT)))

/* The MISRA-preferred alternative: type-checked, and the argument is evaluated once */
static inline void led_on(volatile uint8_t *reg)
{
    *reg |= BIT_MASK(LED_BIT);
}

/* On the MCU the register would be: #define PORT_REG (*(volatile uint8_t *)<register address>) */
static volatile uint8_t port = 0x00U;

static void show(const char *step)
{
    (void)printf("%-12s port = 0x%02X\n", step, (unsigned int)port);
}

int main(void)
{
    show("start");
    LED_ON(port);       show("LED_ON");        /* 0x08 */
    BUZZER_ON(port);    show("BUZZER_ON");     /* 0x28 */
    LED_TOGGLE(port);   show("LED_TOGGLE");    /* 0x20: only the LED changed */
    led_on(&port);      show("led_on()");      /* 0x28 */
    LED_OFF(port);      show("LED_OFF");       /* 0x20 */
    BUZZER_OFF(port);   show("BUZZER_OFF");    /* 0x00 */

    return 0;
}
```

**Output:**

```text
start        port = 0x00
LED_ON       port = 0x08
BUZZER_ON    port = 0x28
LED_TOGGLE   port = 0x20
led_on()     port = 0x28
LED_OFF      port = 0x20
BUZZER_OFF   port = 0x00
```

> "Why the `(uint8_t)` cast on the inverted mask? `~` works on an `int`, so `~0x08` is 0xFFFFFFF7. On an 8-bit register it gets truncated anyway, but the cast makes it clear and keeps MISRA and the compiler happy."

The general set, clear and toggle patterns are in [section 13](#13-bit-manipulation-patterns-to-remember).

**Cross-questions:**

1. **Why so many brackets in the macros?**
   "Because a macro is plain text substitution. Without brackets, `LED_ON(*p)` or `LED_ON(a + b)` can expand with the wrong operator precedence. So: brackets around every parameter and around the whole expression."
2. **Macro vs inline function?**
   "An `static inline` function checks the types and evaluates its argument exactly once. A macro can evaluate an argument **twice**: `LED_ON(reg++)` would be a bug. In new code I prefer inline functions; macros are fine for simple constants and register access."
3. **How do you switch the LED and the buzzer on in one write?**
   "Combine the masks: `reg |= (uint8_t)(BIT_MASK(LED_BIT) | BIT_MASK(BUZZER_BIT));`. That's one read-modify-write instead of two."

### Q107. How do you add two numbers without the `+` operator?

**In simple words:** For each bit, binary addition has two results:

- The **sum bit** is `a XOR b`.
- The **carry** is `a AND b`, moved one position to the left.

Add the sum and the carry again, and repeat until the carry is zero. The result is the full sum.

**Example:** 5 + 3: 0101 ^ 0011 = 0110, carry = 0001 << 1 = 0010; repeat until the carry is 0, and the result is 1000 = **8**.

> "I do it the way the hardware adder does. **XOR** adds the bits **without the carry**: 1 + 0 is 1, and 1 + 1 is 0. **AND** finds the positions where **both bits are 1**, which is exactly where a carry is produced, and shifting it left by one moves the carry to the next column. Then I add the sum and the carry again, and repeat until there's no carry left.
>
> I use unsigned numbers, because left-shifting a negative signed value is undefined in C."

```c
#include <stdio.h>
#include <stdint.h>

/* Adds two numbers using only bitwise operators */
uint32_t add(uint32_t a, uint32_t b)
{
    uint32_t sum   = a;     /* working copies: parameters are not modified */
    uint32_t carry = b;

    while (carry != 0U)
    {
        uint32_t next_carry = (sum & carry) << 1U;   /* where both bits are 1: carry into the next bit */
        sum   = sum ^ carry;                         /* add without the carry                        */
        carry = next_carry;                          /* now add the carry                            */
    }

    return sum;
}

int main(void)
{
    (void)printf("5 + 3           = %lu\n", (unsigned long)add(5U, 3U));
    (void)printf("123456 + 654321 = %lu\n", (unsigned long)add(123456U, 654321U));
    (void)printf("0 + 7           = %lu\n", (unsigned long)add(0U, 7U));

    /* Subtraction with the same function: a - b = a + (~b + 1), two's complement */
    (void)printf("10 - 4          = %lu\n", (unsigned long)add(10U, add(~4U, 1U)));

    return 0;
}
```

**Output:**

```text
5 + 3           = 8
123456 + 654321 = 777777
0 + 7           = 7
10 - 4          = 6
```

```text
a = 5 (0101), b = 3 (0011)
1: carry = 0001 << 1 = 0010,  a = 0110,  b = 0010
2: carry = 0010 << 1 = 0100,  a = 0100,  b = 0100
3: carry = 0100 << 1 = 1000,  a = 0000,  b = 1000
4: carry = 0000,              a = 1000,  b = 0000   → 8
```

**Cross-questions:**

1. **How do you subtract without `-`?**
   "Add the two's complement: `a - b` is `add(a, add(~b, 1))`."
2. **How do you multiply without `*`?**
   "Shift and add: for every set bit `i` of `b`, add `a << i` to the result. That's how simple hardware multipliers work."
3. **What about negative numbers?**
   "With unsigned arithmetic the bit pattern wraps around, which gives exactly the right two's complement result when it's converted back to signed."
4. **How many times does the loop run at most?**
   "At most 32 times for 32-bit values, because the carry moves at least one bit to the left each time."

---

## 32. C++: copy constructor vs copy assignment

### Q108. What is a copy constructor, what is a copy assignment operator, and what's the difference?

**In simple words:** Both functions copy one object into another:

- The **copy constructor** sets up a **new** object.
- **Copy assignment** overwrites an object that **already exists**. So it must first free what that object already owns.

**Example:** `Buffer b = a;` makes a brand-new `b` (copy constructor). `c = a;`, where `c` already holds "x", frees "x" and copies "hello" (copy assignment).

> "Both copy one object into another. The difference is whether the target **already exists**.
>
> The **copy constructor** creates a **new** object as a copy of an existing one. It runs for `Buffer b = a;` or `Buffer b(a);`, when you pass an object by value, and when you return one by value.
>
> The **copy assignment operator** copies into an object that **already exists**: `b = a;`, where b was created earlier. Because b already owns some resources, assignment has two extra jobs: **free the old resource**, and handle **self-assignment**, `a = a`, which would otherwise free the data before copying it.
>
> This really matters when the class owns a pointer. The compiler's default versions just copy the pointer, a **shallow copy**, so two objects point to the same memory and both delete it: a double free. So I write a **deep copy**. And that's the **rule of three**: if a class needs a custom destructor, it also needs a custom copy constructor and copy assignment."

```cpp
#include <cstdio>
#include <cstring>
#include <cstddef>

class Buffer {
public:
    explicit Buffer(const char *s)                    /* normal constructor */
        : len_(std::strlen(s)), data_(new char[len_ + 1U]) {
        std::memcpy(data_, s, len_ + 1U);
        std::printf("  constructor      \"%s\"\n", data_);
    }

    Buffer(const Buffer &other)                       /* copy constructor: builds a NEW object */
        : len_(other.len_), data_(new char[other.len_ + 1U]) {
        std::memcpy(data_, other.data_, len_ + 1U);   /* deep copy: own memory, not a shared pointer */
        std::printf("  copy constructor \"%s\"\n", data_);
    }

    Buffer &operator=(const Buffer &other) {          /* copy assignment: the object ALREADY exists */
        if (this != &other) {                         /* 1. a = a must not free its own data          */
            char *copy = new char[other.len_ + 1U];   /* 2. allocate first: if new throws, *this is unchanged */
            std::memcpy(copy, other.data_, other.len_ + 1U);
            std::printf("  copy assignment  \"%s\" -> \"%s\"\n", data_, copy);
            delete[] data_;                           /* 3. free the old data                         */
            data_ = copy;
            len_  = other.len_;
        }
        return *this;                                 /* 4. allows a = b = c                          */
    }

    ~Buffer() {                                       /* destructor: frees what the object owns */
        std::printf("  destructor       \"%s\"\n", data_);
        delete[] data_;
    }

    const char *c_str() const { return data_; }
    void set_first(char ch) { data_[0] = ch; }

private:
    std::size_t len_;
    char       *data_;
};

int main() {
    std::printf("Buffer a(\"hello\");\n");
    Buffer a("hello");

    std::printf("Buffer b = a;   (b is being created)\n");
    Buffer b = a;

    std::printf("Buffer c(\"x\"); c = a;   (c already exists)\n");
    Buffer c("x");
    c = a;

    b.set_first('J');                                 /* proves b has its own memory */
    std::printf("after b[0] = 'J': a = \"%s\", b = \"%s\", c = \"%s\"\n", a.c_str(), b.c_str(), c.c_str());

    std::printf("end of main:\n");
    return 0;
}
```

**Output:**

```text
Buffer a("hello");
  constructor      "hello"
Buffer b = a;   (b is being created)
  copy constructor "hello"
Buffer c("x"); c = a;   (c already exists)
  constructor      "x"
  copy assignment  "x" -> "hello"
after b[0] = 'J': a = "hello", b = "Jello", c = "hello"
end of main:
  destructor       "hello"
  destructor       "Jello"
  destructor       "hello"
```

| | Copy constructor | Copy assignment operator |
| --- | --- | --- |
| Signature | `T(const T &other)` | `T &operator=(const T &other)` |
| Target object | Being **created** | **Already exists** |
| Called by | `T b = a;`, `T b(a);`, pass/return by value | `b = a;` |
| Frees old resources? | No: there are none yet | **Yes** |
| Self-assignment check? | Not needed | **Needed** |
| Returns | Nothing | `*this`, so `a = b = c` works |

**Cross-questions:**

1. **Why must the copy constructor take a reference?**
   "If it took the object **by value**, passing the argument would itself need a copy, which calls the copy constructor again, forever. The compiler doesn't allow it."
2. **When is the copy constructor called without you noticing?**
   "When an object is passed or returned by value. That's why I pass objects as `const Buffer &`."
3. **What are move semantics?**
   "Since C++11, a **move constructor**, `Buffer(Buffer &&other)`, can just take the other object's pointer and set the other's pointer to null, with no allocation and no copying. With move constructor and move assignment, the rule of three becomes the **rule of five**."
4. **How do you stop a class from being copied?**
   "`Buffer(const Buffer &) = delete;` and the same for `operator=`. I do that for classes that own hardware, like a UART driver object, where two copies make no sense."
5. **What is copy-and-swap?**
   "Write the assignment operator as: take the parameter **by value** (which makes the copy), then swap its contents with `*this`. It's automatically safe against self-assignment and exceptions, and the old data is freed when the parameter goes out of scope."

---

## 33. Multithreading: even and odd threads

### Q109. Thread 1 prints even numbers and Thread 2 prints odd numbers. How do you make the output come in order: 1, 2, 3, 4...?

**Also asked as:** *Can you write the code?* · *How would you synchronize the two threads?* · *Why a mutex and a condition variable?*

**In simple words:** The two threads share a counter, and a **mutex** protects it.

Each thread waits on a **condition variable** until the counter's parity matches its own. Then it prints the number, increments the counter, and signals the other thread.

**Example:** Thread 2 prints 1 and tells Thread 1 "your turn". Thread 1 prints 2 and tells Thread 2 "your turn", and so on: 1, 2, 3, 4...

> "The two threads have to **take turns**, so I need a shared counter and a way for each thread to **sleep until it's its turn**.
>
> I use one **mutex** to protect the counter, and one **condition variable** for waiting. Each thread locks the mutex and checks: is the counter odd or even, is it my turn? If not, it calls `wait()`, which **releases the mutex and sleeps** in one atomic step. When it's its turn, it prints the number, increments the counter, and **signals** the other thread, which wakes up, sees it's now its turn, and prints the next number.
>
> Why not just a mutex? A mutex only stops both threads touching the counter at the same time; it doesn't decide **who goes next**. One thread could grab the mutex again and again while it isn't its turn, just spinning and wasting CPU. The condition variable lets it sleep until the other thread says 'your turn'. Two semaphores would also work, one per thread, each thread posting the other's."

```c
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_NUM  (10U)

static uint32_t        g_count = 1U;                           /* next number to print           */
static pthread_mutex_t g_lock  = PTHREAD_MUTEX_INITIALIZER;    /* protects g_count               */
static pthread_cond_t  g_turn  = PTHREAD_COND_INITIALIZER;     /* signaled when the turn changes */

/* arg points to the parity this thread prints: 0 = even (Thread 1), 1 = odd (Thread 2) */
static void *print_numbers(void *arg)
{
    const uint32_t parity = *(const uint32_t *)arg;

    (void)pthread_mutex_lock(&g_lock);
    while (g_count <= MAX_NUM)
    {
        /* Sleep until it is this thread's turn: "while", not "if" (see Q110) */
        while ((g_count <= MAX_NUM) && ((g_count % 2U) != parity))
        {
            (void)pthread_cond_wait(&g_turn, &g_lock);         /* unlocks, sleeps, re-locks */
        }

        if (g_count <= MAX_NUM)
        {
            (void)printf("%s: %u\n", (parity == 0U) ? "Thread 1 (even)" : "Thread 2 (odd)",
                         (unsigned int)g_count);
            g_count++;
            (void)pthread_cond_signal(&g_turn);                /* now it's the other thread's turn */
        }
    }
    (void)pthread_cond_signal(&g_turn);                        /* let the other thread finish too  */
    (void)pthread_mutex_unlock(&g_lock);

    return NULL;
}

int main(void)
{
    static uint32_t even = 0U;
    static uint32_t odd  = 1U;
    pthread_t       t1;
    pthread_t       t2;
    int             rc1;
    int             rc2;

    rc1 = pthread_create(&t1, NULL, print_numbers, &even);    /* Thread 1: even numbers */
    rc2 = pthread_create(&t2, NULL, print_numbers, &odd);     /* Thread 2: odd numbers  */

    if (rc1 == 0)
    {
        (void)pthread_join(t1, NULL);
    }
    if (rc2 == 0)
    {
        (void)pthread_join(t2, NULL);
    }

    return ((rc1 == 0) && (rc2 == 0)) ? 0 : 1;
}
```

**Output:**

```text
Thread 2 (odd): 1
Thread 1 (even): 2
Thread 2 (odd): 3
Thread 1 (even): 4
Thread 2 (odd): 5
Thread 1 (even): 6
Thread 2 (odd): 7
Thread 1 (even): 8
Thread 2 (odd): 9
Thread 1 (even): 10
```

> "On FreeRTOS I'd do the same with **task notifications** or two binary semaphores: the odd task gives the even task's semaphore after printing, and the other way round."

**Cross-questions:**

1. **Can you do it with semaphores instead?**
   "Yes, two semaphores: `sem_odd` starts at 1 and `sem_even` at 0. The odd thread waits on `sem_odd`, prints, then posts `sem_even`; the even thread does the opposite. It's simpler, and the order is forced by construction."
2. **Why `signal` and not `broadcast`?**
   "With only two threads there's only one waiter, so `signal` is enough. With more threads waiting on the same condition I'd use `broadcast`, so the right one is sure to wake."
3. **How could this deadlock?**
   "If the last thread to finish didn't signal, the other one would wait forever for a turn that never comes. That's why there's a final `pthread_cond_signal()` after the loop."
4. **How would you extend it to three threads printing 1, 2, 3 in rotation?**
   "Give each thread an ID from 0 to 2, have it wait while `count % 3 != id`, and use `broadcast`, because the next thread to run isn't necessarily the one that `signal` would wake."

### Q110. Why check the condition with `while` instead of `if` after `wait()`?

**In simple words:** There are two reasons to check again after waking up:

- `pthread_cond_wait()` can return even when the condition is not true. This is called a **spurious wake-up**.
- Another thread may change the state before the woken thread gets the mutex back.

So the condition must be **checked again in a loop**.

**Example:** The odd thread wakes up, checks `count % 2`, sees it's still the even thread's turn, and goes back to sleep. With `if` instead of `while`, it would print out of order.

> "For two reasons. First, **spurious wake-ups**: POSIX allows `pthread_cond_wait()` to return even when nobody signaled. Second, even after a real signal, by the time my thread gets the mutex back, **another thread might already have changed the condition**. With more than two threads, a third thread could have taken the turn.
>
> So waking up only means 'something might have changed, check again'. With `if`, the thread would continue even though it's not its turn, and the order breaks. With `while`, it re-checks and goes back to sleep if needed."

**Cross-questions:**

1. **What does `pthread_cond_wait()` do exactly?**
   "Atomically, it **unlocks the mutex and puts the thread to sleep**. When it wakes up, it **locks the mutex again** before returning. Doing those two steps as one is what prevents a lost wake-up."
2. **What's a lost wake-up?**
   "If a thread checked the condition without the mutex, the other thread could change it and signal between the check and the wait. The signal would be missed, and the thread would sleep forever."
3. **Do you have to hold the mutex when signaling?**
   "It's allowed without it, but the **condition itself** must always be changed while holding the mutex. I usually signal while holding it, which is the simplest pattern to reason about."

---

## 34. Quick revision sheet

| Area | Topics |
| --- | --- |
| **I2C** | Configuration, register read/write, addressing, NACK, ACK on write vs read, 9 clocks per byte, clock stretching, arbitration, speed modes, pull-ups and rise time |
| **SPI** | Pins, CPOL/CPHA and the 4 modes, CS, frame split (command, address, data), EEPROM page writes |
| **1-Wire** | Reset and presence pulse, ROM commands, write and read time slots, LSB first |
| **USB** | Host vs device, enumeration, descriptors, endpoints, the 4 transfer types |
| **GPIO** | Register map as a `volatile` struct, `1U << pin`, set/clear/read/toggle, RMW races vs SET/CLR registers |
| **BSP / HAL** | Board initialization, hardware abstraction, driver layering |
| **Linux drivers** | Device tree, `probe()`, driver registration, IRQ handling, workqueue, threaded IRQ, clean-up |
| **Interrupts** | Vector table, NVIC/GIC, ISR, Cortex-M exception stacking, EXC_RETURN |
| **RTOS** | Context switch, PendSV, waking a task from an ISR, mutex, semaphore, spinlock, FreeRTOS heap_1-5 |
| **Memory** | Stack, heap, pointers, string literals, virtual memory, MMU, page table, TLB, cache, structure padding |
| **C** | Bit fields, function pointers, bit manipulation, unions and endianness, `char[]` vs `const char *` |
| **Bootloader** | Purpose, update sources, interrupted update, A/B, integrity, signatures, rollback |
| **Debugging** | GDB, JTAG/SWD, breakpoints and watchpoints, backtrace, HardFault |
| **BLE** | Stack layers, GATT services and characteristics, Read/Write/Notify, CCCD, MTU |
| **Networking** | OSPF: link-state, LSAs, Dijkstra, areas, neighbour requirements |
| **Linux I2C stack** | DTS node under the controller, `compatible` / `reg` / `interrupts`, i2c-dev vs kernel driver, VFS → client driver → I2C core → adapter `master_xfer` |
| **Boot and bring-up** | Boot ROM → SPL → U-Boot → kernel + DTB → init; STM32 not booting: power, NRST, BOOT0, crystal, vector table, linker script, Reset_Handler |
| **C++** | Copy constructor vs copy assignment, deep copy, self-assignment, rule of three |
| **Threads** | Mutex + condition variable, `while` around `wait()`, spurious wake-ups |
| **Coding** | Merge two sorted linked lists, SPI EEPROM driver, register-level GPIO driver, substring search, LED macros, add without `+`, even/odd threads, `strlen`/`strcat` code review |

**Revise these first** (asked most often):

1. I2C: ACK/NACK, clock stretching, arbitration, speed and pull-ups ([Q50-Q58](#14-i2c-in-depth))
2. SPI modes and I2C vs SPI ([Q59-Q60](#16-spi-modes-and-choosing-an-interface))
3. Register-level GPIO driver and `volatile` ([Q68-Q71](#19-register-level-gpio-driver-no-hal))
4. RTOS context switch, PendSV and ISR-to-task wake-up ([Q73-Q78](#21-rtos-interrupts-and-context-switching))
5. Bootloader update, interruption and rollback ([Q84-Q87](#24-firmware-update-and-bootloader))
6. BLE GATT, notify and CCCD ([Q80-Q83](#23-ble-in-practice))
7. USB enumeration and transfer types ([Q64-Q67](#18-usb))
8. FreeRTOS heap choice ([Q79](#22-freertos-heap))
9. 1-Wire timing ([Q61-Q63](#17-1-wire-protocol))
10. Device tree → driver → I2C → application flow ([Q90-Q95](#27-linux-i2c-stack-device-tree-to-application))
11. STM32 not reaching `main()`: hardware and firmware debugging ([Q97-Q98](#28-embedded-linux-boot-and-stm32-bring-up-debugging))
12. Pointers, strings and code review ([Q99-Q105](#29-c-strings-arrays-and-pointers))
13. Bit macros, copy constructor vs assignment, thread synchronization ([Q106-Q110](#31-bit-macros-and-bitwise-arithmetic))
