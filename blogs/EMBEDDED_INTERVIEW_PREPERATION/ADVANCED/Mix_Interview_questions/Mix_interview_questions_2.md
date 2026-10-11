# Embedded Interview Questions 2

## Contents

| # | Topic | Questions |
| --- | --- | --- |
| 1 | [Embedded C fundamentals](#1-embedded-c-fundamentals) | Q1-Q40 |
| 2 | [C coding and problem-solving exercises](#2-c-coding-and-problem-solving-exercises) | Q41-Q64 |
| 3 | [RTOS, FreeRTOS and scheduling](#3-rtos-freertos-and-scheduling) | Q65-Q106 |
| 4 | [Interrupts, DMA, ADC and peripherals](#4-interrupts-dma-adc-and-peripherals) | Q107-Q130 |
| 5 | [CAN, Ethernet and communication protocols](#5-can-ethernet-and-communication-protocols) | Q131-Q152 |
| 6 | [USB Type-C Power Delivery and battery management](#6-usb-type-c-power-delivery-and-battery-management) | Q153-Q178 |
| 7 | [BLE and Bluetooth](#7-ble-and-bluetooth) | Q179-Q201 |
| 8 | [IoT, MQTT and networking](#8-iot-mqtt-and-networking) | Q202-Q222 |
| 9 | [Bootloader, secure boot and OTA](#9-bootloader-secure-boot-and-ota) | Q223-Q243 |
| 10 | [Testing, MISRA, code review and CI/CD](#10-testing-misra-code-review-and-cicd) | Q244-Q275 |
| 11 | [Linux, system architecture and board bring-up](#11-linux-system-architecture-and-board-bring-up) | Q276-Q294 |
| 12 | [Electronics, displays and hardware interfaces](#12-electronics-displays-and-hardware-interfaces) | Q295-Q303 |
| 13 | [C++ and object-oriented programming](#13-c-and-object-oriented-programming) | Q304-Q321 |
| 14 | [Firmware architecture and technical leadership](#14-firmware-architecture-and-technical-leadership) | Q322-Q344 |
| 15 | [Additional interview questions and scenarios](#15-additional-interview-questions-and-scenarios) | Q345-Q363 |
| 16 | [General technical questions](#16-general-technical-questions) | Q364-Q380 |

## Abbreviations

| Short | Full form | Short | Full form | Short | Full form |
| --- | --- | --- | --- | --- | --- |
| **A2DP** | Advanced Audio Distribution Profile | **ACK / NACK** | Acknowledge / Negative Acknowledge | **ACL** | Asynchronous Connection-Less (HCI data packets) |
| **ACM** | Abstract Control Model (USB CDC) | **ADC** | Analog-to-Digital Converter | **AES** | Advanced Encryption Standard |
| **AHB** | Advanced High-performance Bus | **AI / ML** | Artificial Intelligence / Machine Learning | **API** | Application Programming Interface |
| **ARP** | Address Resolution Protocol | **ASIL** | Automotive Safety Integrity Level | **ATT** | Attribute Protocol |
| **AVRCP** | Audio/Video Remote Control Profile | **BCD** | Binary-Coded Decimal | **BFAR** | BusFault Address Register |
| **BLE** | Bluetooth Low Energy | **BMC** | Biphase Mark Coding | **BR/EDR** | Basic Rate / Enhanced Data Rate (Bluetooth Classic) |
| **BRS** | Bit Rate Switch (CAN FD) | **BSP** | Board Support Package | **BSRR** | Bit Set/Reset Register (STM32) |
| **CA** | Certificate Authority | **CAN / CAN FD** | Controller Area Network / CAN with Flexible Data-rate | **CBOR** | Concise Binary Object Representation |
| **CC** | Configuration Channel (USB Type-C) | **CC / CV** | Constant Current / Constant Voltage (charging) | **CCCD** | Client Characteristic Configuration Descriptor |
| **CDC** | Communications Device Class (USB) | **CFSR** | Configurable Fault Status Register | **CI / CD** | Continuous Integration / Continuous Delivery |
| **CLZ** | Count Leading Zeros (instruction) | **CMSIS** | Common Microcontroller Software Interface Standard | **CRC** | Cyclic Redundancy Check |
| **CS** | Chip Select | **CSI / DSI** | Camera / Display Serial Interface (MIPI) | **DLC** | Data Length Code (CAN) |
| **DMA** | Direct Memory Access | **DNS** | Domain Name System | **DTR** | Data Terminal Ready |
| **DTS / DTB** | Device Tree Source / Device Tree Blob | **DWT** | Data Watchpoint and Trace unit | **ECDSA** | Elliptic Curve Digital Signature Algorithm |
| **ECO** | Engineering Change Order | **ECU** | Electronic Control Unit | **EEPROM** | Electrically Erasable Programmable Read-Only Memory |
| **ELF** | Executable and Linkable Format | **EMC / EMI** | Electromagnetic Compatibility / Interference | **EOF / SOF** | End Of Frame / Start Of Frame |
| **ESD** | Electrostatic Discharge | **ESI** | Error State Indicator (CAN FD) | **EXTI** | Extended Interrupt and Event Controller (STM32) |
| **FDF** | FD Format bit (CAN FD) | **FPSCR** | Floating-Point Status and Control Register | **FPU** | Floating-Point Unit |
| **GAP** | Generic Access Profile | **GATT** | Generic Attribute Profile | **GDB** | GNU Debugger |
| **GPIO** | General-Purpose Input/Output | **HAL** | Hardware Abstraction Layer | **HCI** | Host Controller Interface |
| **HFP** | Hands-Free Profile | **HFSR** | HardFault Status Register | **HID** | Human Interface Device (USB) |
| **HMI** | Human-Machine Interface | **HSE / HSI** | High-Speed External / Internal oscillator | **HSM** | Hardware Security Module |
| **HTTP(S)** | Hypertext Transfer Protocol (Secure) | **I2C** | Inter-Integrated Circuit | **IC** | Integrated Circuit |
| **ICSR** | Interrupt Control and State Register | **IDE** | Integrated Development Environment; also Identifier Extension bit (CAN) | **IFS** | Inter-Frame Space (CAN) |
| **IIO** | Industrial I/O (Linux subsystem) | **IMU** | Inertial Measurement Unit | **IoT** | Internet of Things |
| **IP** | Internet Protocol | **IPC** | Inter-Process Communication | **IRQ / ISR** | Interrupt Request / Interrupt Service Routine |
| **ITM** | Instrumentation Trace Macrocell | **IWDG / WWDG** | Independent / Window Watchdog (STM32) | **JEITA** | Japan Electronics and IT Industries Association (battery temperature charging guideline) |
| **JSON** | JavaScript Object Notation | **JTAG** | Joint Test Action Group (debug interface) | **L2CAP** | Logical Link Control and Adaptation Protocol |
| **LCD** | Liquid Crystal Display | **LR** | Link Register (R14) | **LTE-M / NB-IoT** | LTE for Machines / Narrowband IoT (cellular) |
| **LVDS** | Low-Voltage Differential Signalling | **MAC** | Media Access Controller (Ethernet) | **MC/DC** | Modified Condition/Decision Coverage |
| **MCO** | Microcontroller Clock Output | **MCU** | Microcontroller Unit | **MDIO / MDC** | Management Data Input/Output / Management Data Clock |
| **MII / RMII** | Media Independent Interface / Reduced MII | **MIPI** | Mobile Industry Processor Interface | **MISO / MOSI** | Master In Slave Out / Master Out Slave In |
| **MISRA** | Motor Industry Software Reliability Association | **MMFAR** | MemManage Fault Address Register | **MMU / MPU** | Memory Management Unit / Memory Protection Unit |
| **MQTT** | Message Queuing Telemetry Transport | **MSP / PSP** | Main / Process Stack Pointer | **MTU** | Maximum Transmission Unit |
| **NRST** | Reset pin (STM32) | **NTC** | Negative Temperature Coefficient (thermistor) | **NVIC** | Nested Vectored Interrupt Controller |
| **OLED** | Organic Light-Emitting Diode | **OS** | Operating System | **OTA** | Over The Air (update) |
| **OTP** | One-Time Programmable (memory) | **PC** | Program Counter (R15) | **PCB** | Printed Circuit Board |
| **PCROP** | Proprietary Code Read-Out Protection | **PD / USB-PD** | USB Power Delivery | **PDO / APDO** | Power Data Object / Augmented PDO |
| **PHY** | Physical-layer transceiver | **PLL** | Phase-Locked Loop | **PMIC** | Power Management IC |
| **PPS** | Programmable Power Supply (USB-PD) | **PS_RDY** | Power Supply Ready (USB-PD message) | **PWM** | Pulse-Width Modulation |
| **QoS** | Quality of Service (MQTT) | **RAII** | Resource Acquisition Is Initialization | **RAM / ROM** | Random-Access Memory / Read-Only Memory |
| **RDP** | Read-out Protection (STM32) | **RFCOMM** | Radio Frequency Communication (serial-port emulation) | **RS-485** | Recommended Standard 485 (differential serial bus) |
| **RTC** | Real-Time Clock | **RTOS** | Real-Time Operating System | **RTR** | Remote Transmission Request (CAN) |
| **RTS / CTS** | Request To Send / Clear To Send | **RTT** | Real-Time Transfer (SEGGER) | **RTU** | Remote Terminal Unit (Modbus RTU) |
| **SBC** | Single-Board Computer | **SBSFU** | Secure Boot and Secure Firmware Update (ST) | **SCL / SDA** | Serial Clock / Serial Data (I2C) |
| **SCLK** | Serial Clock (SPI) | **SDK** | Software Development Kit | **SHA-256** | Secure Hash Algorithm, 256-bit |
| **SMP** | Security Manager Protocol (BLE) | **SoC** | State of Charge (battery); also System on Chip | **SPI** | Serial Peripheral Interface |
| **SPP** | Serial Port Profile | **SRAM** | Static RAM | **STL** | Standard Template Library |
| **SVC** | Supervisor Call | **SWD / SWO** | Serial Wire Debug / Serial Wire Output | **SYN / FIN** | Synchronize / Finish (TCP flags) |
| **TCB** | Task Control Block | **TCP** | Transmission Control Protocol | **TCPC** | Type-C Port Controller |
| **TF-M** | Trusted Firmware-M | **TFT** | Thin-Film Transistor (display) | **TLS** | Transport Layer Security |
| **TPM** | Trusted Platform Module | **TTL** | Time To Live (IP) | **UART** | Universal Asynchronous Receiver-Transmitter |
| **UDP** | User Datagram Protocol | **UI** | User Interface | **ULPI** | UTMI+ Low Pin Interface (USB PHY) |
| **USB** | Universal Serial Bus | **UUID** | Universally Unique Identifier | **VBUS / VCONN** | USB bus power / Type-C cable power |
| **VDDA** | Analog supply voltage | **VFS** | Virtual File System (Linux) | **VID / PID** | Vendor ID / Product ID (USB) |
| **VTOR** | Vector Table Offset Register | **WRP** | Write Protection (STM32) | **XOFF / XON** | Software flow control: stop / resume |

---

## 1. Embedded C fundamentals

### Q1. What is the purpose of the volatile keyword?

> "`volatile` tells the compiler: this variable can change outside the normal flow of my code, so don't optimize its reads and writes away. Every time the code reads it, the compiler must really read it, and every time it writes it, it must really write it.
>
> I use it in three places: **hardware registers**, **variables shared between an ISR and the main code**, and **memory changed by DMA**."

**Example:** without `volatile`, the compiler may read `g_data_ready` once, see it's 0, and turn the loop into an endless loop.

```c
static volatile uint8_t g_data_ready = 0U;   /* set by the ISR, read by main */

void UART_IRQHandler(void)
{
    g_data_ready = 1U;                       /* the ISR changes it */
}

void wait_for_data(void)
{
    while (g_data_ready == 0U)               /* volatile: re-read on every loop pass */
    {
        /* wait */
    }
    g_data_ready = 0U;
}
```

### Q2. Does volatile force every variable access to come directly from RAM?

> "Not exactly. `volatile` only controls the **compiler**: it must generate a real load or store instruction for every access, in program order. It says nothing about the **hardware**. If the variable sits in cacheable memory, the load can still be served from the CPU's data cache.
>
> That's why, on a Cortex-M7 with cache, a DMA buffer needs cache maintenance or a non-cacheable MPU region. `volatile` alone isn't enough. Peripheral registers are fine, because their memory region is marked as device memory, which is never cached."

### Q3. Can volatile guarantee atomicity or thread safety?

> "No. `volatile` only stops the compiler from optimizing the access away. It doesn't make an operation atomic.
>
> For example, `counter++` on a volatile variable is still three steps: read, add, write. If an ISR changes `counter` between the read and the write, one update is lost. For that I need a critical section, an atomic instruction, or a mutex between tasks."

```c
static volatile uint32_t g_counter = 0U;

void task_code(void)
{
    __disable_irq();          /* make the read-modify-write atomic against the ISR */
    g_counter++;
    __enable_irq();
}
```

### Q4. Have you used volatile and const together?

> "Yes. `const volatile` means: **my code must not write it, but it can still change by itself.** A typical example is a read-only status register, or an input data register. `const` stops me from writing it by mistake, and `volatile` makes sure every read really goes to the hardware."

```c
/* A read-only status register at 0x40011000 */
#define UART_SR   (*(const volatile uint32_t *)0x40011000UL)

uint32_t status = UART_SR;     /* allowed: read  */
/* UART_SR = 0U; */            /* compile error: it's const */
```

### Q5. What is the difference between a global variable and a static local variable?

> "Both live for the **whole program**: they're in `.data` or `.bss`, not on the stack, and they keep their value between function calls. The difference is **who can see them**.
>
> A global variable can be used by any function, and even by other files with `extern`. A static local variable can only be used **inside the function** where it's declared. So when only one function needs to remember a value, I use a static local, which keeps it private."

```c
uint32_t g_total_packets = 0U;          /* global: visible everywhere */

void count_calls(void)
{
    static uint32_t call_count = 0U;    /* static local: only this function sees it */
    call_count++;                       /* keeps its value between calls: 1, 2, 3 ... */
}
```

### Q6. What does the static keyword do inside a function?

> "It changes the variable's **lifetime**, not its visibility. A normal local is created on the stack every time the function runs and destroyed when it returns. A `static` local is created **once**, initialized once before the program starts, and keeps its value between calls.
>
> I use it for things like a call counter, a one-time init flag, or a state machine's current state."

```c
void sensor_task(void)
{
    static uint8_t initialized = 0U;    /* initialized once, not on every call */

    if (initialized == 0U)
    {
        sensor_init();                  /* runs only on the first call */
        initialized = 1U;
    }
    sensor_read();
}
```

### Q7. What does static mean at file scope?

> "At file scope, `static` means **internal linkage**: the variable or function is visible only inside that `.c` file. Other files can't see it, even with `extern`.
>
> I use it a lot for encapsulation: a driver's internal state and helper functions are `static`, and only the public API is declared in the header. It also avoids name clashes between modules, since two files can both have a `static int count;`."

```c
/* uart_driver.c */
static uint8_t s_rx_buffer[64];             /* private to this file */
static void uart_clear_errors(void) { }     /* private helper       */

void uart_init(void)                        /* public: declared in uart_driver.h */
{
    uart_clear_errors();
}
```

### Q8. Can a static variable have a non-constant initializer?

> "In C, **no**. A static variable is initialized before `main()` runs, by the startup code copying `.data`, so the initializer must be a **constant expression** known at compile time. `static int x = get_value();` is a compile error in C.
>
> In C++ it's allowed: the static local is initialized the first time the function runs. In C, if I need a run-time value, I initialize it to a constant and set it on the first call."

```c
static uint32_t s_timeout = 100U;           /* OK: constant                    */
/* static uint32_t s_ticks = get_tick(); */ /* error in C: not a constant      */
```

### Q9. What are the storage classes in C?

> "There are four classic storage-class specifiers: **`auto`**, **`register`**, **`static`** and **`extern`**. C11 also added `_Thread_local`. A storage class decides three things about a variable: where it's stored, how long it lives, and who can see it."

| Storage class | Where | Lifetime | Visibility | Default value |
| --- | --- | --- | --- | --- |
| `auto` | Stack | Until the block ends | Inside the block | Garbage |
| `register` | CPU register (a hint only) | Until the block ends | Inside the block | Garbage |
| `static` | `.data` / `.bss` | Whole program | The block, or the file | 0 |
| `extern` | Defined in another file | Whole program | All files that declare it | 0 |

### Q10. What is the difference between auto, register, static and extern?

> "**`auto`** is the default for local variables: on the stack, gone when the block ends. Nobody writes it explicitly.
>
> **`register`** is a hint to keep the variable in a CPU register for speed. Modern compilers ignore it, because they allocate registers better than we can. The one real effect is that you can't take its address.
>
> **`static`** keeps a local alive for the whole program, or makes a global private to its file.
>
> **`extern`** doesn't create a variable. It says 'this variable is defined in another file, let me use it'."

```c
void demo(void)
{
    auto int a = 1;            /* same as: int a = 1; (stack)          */
    register int b = 2;        /* hint only; &b is not allowed         */
    static int c = 3;          /* keeps its value between calls        */
    extern int d;              /* defined in another .c file           */
}
```

### Q11. How do you access a variable defined in one source file from another source file?

> "I **define** it once in one `.c` file, and **declare** it with `extern` in a header that the other files include. The definition allocates the memory; the `extern` declaration just tells the compiler it exists, and the linker connects them.
>
> The variable must not be `static`, otherwise it's private to its file. And I keep shared globals to a minimum; usually I'd rather expose a getter function."

```c
/* config.c: the definition (memory is allocated here) */
uint32_t g_baud_rate = 115200U;

/* config.h: the declaration */
extern uint32_t g_baud_rate;

/* main.c */
#include "config.h"
void print_baud(void) { printf("%lu\n", (unsigned long)g_baud_rate); }
```

### Q12. Why do we use macros?

> "Mainly for four things:
>
> - **Named constants**, like `#define BUFFER_SIZE 64U`, so there are no magic numbers.
> - **Register addresses and bit masks**, like `#define GPIOA_ODR (*(volatile uint32_t *)0x40020014UL)`.
> - **Conditional compilation**, like `#ifdef DEBUG` or selecting code per board.
> - **Include guards** in headers.
>
> I avoid function-like macros where an `inline` function would do, because macros have no type checking and can evaluate an argument twice. MISRA also prefers functions."

```c
#define LED_PIN        (5U)
#define BIT(n)         (1UL << (n))
#define SQUARE(x)      ((x) * (x))     /* SQUARE(i++) evaluates i++ twice: a classic bug */

#ifdef DEBUG
#define LOG(msg)       printf("%s\n", (msg))
#else
#define LOG(msg)       ((void)0)       /* compiled out in release */
#endif
```

### Q13. At what stage are macros expanded?

> "In the **preprocessing** stage, before the actual compilation. The preprocessor does pure text replacement: it replaces every macro, handles `#include` and `#ifdef`, and removes comments. The compiler then only sees the expanded code.
>
> If I want to see the result, I run `gcc -E file.c`, which stops after preprocessing."

```text
.c file → Preprocessor (macros, #include, #ifdef) → Compiler (→ assembly) → Assembler (→ .o) → Linker (→ .elf)
```

### Q14. What happens when a signed integer is assigned to an unsigned integer?

> "The value is converted **modulo 2ⁿ**, where n is the number of bits of the unsigned type. Positive values that fit stay the same. A negative value wraps around to a big positive number: in practice the bit pattern stays the same (two's complement), it's just read as unsigned.
>
> So `int32_t a = -1;` assigned to `uint32_t` becomes `4294967295`, which is `0xFFFFFFFF`."

```c
int32_t  s = -5;
uint32_t u = (uint32_t)s;     /* 2^32 - 5 = 4294967291 = 0xFFFFFFFB */
```

### Q15. What happens when -1 is assigned to uint8_t?

> "It becomes **255**. The conversion is modulo 2⁸ = 256, so −1 + 256 = 255, or `0xFF`. In bits, −1 is all ones, and eight ones in an unsigned byte is 255."

```c
uint8_t x = (uint8_t)-1;      /* x = 255 (0xFF) */
```

### Q16. What happens when a signed integer is compared with an unsigned integer?

> "The signed value is **converted to unsigned** before the comparison, if both are the same size or the unsigned type is bigger. So a negative number becomes a huge positive number, and the comparison gives the 'wrong' answer.
>
> This is a classic interview trap. The compiler warns with `-Wsign-compare`, and MISRA forbids mixing signedness without a cast."

```c
int32_t  a = -1;
uint32_t b = 1U;

if (a < b)             /* a is converted to 0xFFFFFFFF, so this is FALSE */
{
    /* not reached */
}

if (a < (int32_t)b)    /* fixed: compare as signed, now TRUE */
{
    /* reached */
}
```

### Q17. What is little-endian and big-endian representation?

> "It's the order in which a multi-byte value is stored in memory.
>
> - **Little-endian**: the **least significant byte** goes at the **lowest address**.
> - **Big-endian**: the **most significant byte** goes at the **lowest address**.
>
> Network protocols use big-endian ('network byte order'), while most MCUs are little-endian. That's why I always convert when I build or parse a protocol frame."

**Example:** `0x12345678` stored at address 0x100:

| Address | 0x100 | 0x101 | 0x102 | 0x103 |
| --- | --- | --- | --- | --- |
| Little-endian | 78 | 56 | 34 | 12 |
| Big-endian | 12 | 34 | 56 | 78 |

### Q18. Which endianness does ARM use?

> "ARM cores can technically support both, but in practice almost every ARM system runs **little-endian**. Cortex-M parts like the STM32 are little-endian, fixed in hardware. Cortex-A cores running Linux or Android are configured little-endian too."

### Q19. How do you convert a little-endian value to big-endian?

> "I swap the bytes: byte 0 goes to byte 3, byte 1 to byte 2, and so on. I can do it with shifts and masks, which is portable. On Arm, the compiler builtin `__builtin_bswap32()`, or CMSIS `__REV()`, compiles to a single **REV** instruction. For network code there's `htonl()`."

```c
#include <stdint.h>

/* 0x12345678 -> 0x78563412 */
uint32_t swap32(uint32_t value)
{
    return ((value & 0x000000FFUL) << 24U) |    /* byte 0 -> byte 3 */
           ((value & 0x0000FF00UL) <<  8U) |    /* byte 1 -> byte 2 */
           ((value & 0x00FF0000UL) >>  8U) |    /* byte 2 -> byte 1 */
           ((value & 0xFF000000UL) >> 24U);     /* byte 3 -> byte 0 */
}
```

### Q20. What is the difference between a pointer to a variable and a pointer to an array?

> "A pointer to a variable, like `int *p`, points to **one element**, so `p + 1` moves by one `int`, 4 bytes. A pointer to an array, like `int (*p)[5]`, points to the **whole array** as one object, so `p + 1` moves by the whole array, 20 bytes.
>
> Both can hold the same address, but their types are different, so pointer arithmetic is different. Pointers to arrays are mostly used for 2D arrays."

```c
int32_t arr[5] = {1, 2, 3, 4, 5};

int32_t  *p1 = arr;        /* pointer to the first element   */
int32_t (*p2)[5] = &arr;   /* pointer to the whole array     */

/* p1 + 1 -> address + 4 bytes  (next element)           */
/* p2 + 1 -> address + 20 bytes (just past the array)     */
/* (*p2)[2] == 3                                          */
```

### Q21. How do you declare a function pointer?

> "The pattern is: return type, then `(*name)`, then the parameter list. In real code I always use a `typedef`, because it's much easier to read."

```c
/* A function that takes two ints and returns an int */
int32_t add(int32_t a, int32_t b) { return a + b; }

int32_t (*op)(int32_t, int32_t) = add;            /* plain declaration       */

typedef int32_t (*binary_op_t)(int32_t, int32_t); /* with a typedef: clearer */
binary_op_t op2 = add;

int32_t result = op2(3, 4);                       /* calls add(): result = 7 */
```

### Q22. Why do we put parentheses around the function pointer name in its declaration?

> "Because of **operator precedence**. The function-call parentheses `()` bind tighter than `*`.
>
> - `int *fp(int);` declares a **function** called `fp` that returns an `int *`.
> - `int (*fp)(int);` declares a **pointer** called `fp` to a function that returns an `int`.
>
> The parentheses force `*` to attach to the name first, so the name becomes a pointer."

### Q23. What is a callback function? Can you write an example?

> "A callback is a function that I pass to another module as a function pointer, so that module can **call it back later**, when an event happens. The lower layer doesn't need to know anything about the application.
>
> For example, my UART driver lets the application register a function. When a full frame arrives, the driver calls it."

```c
#include <stdint.h>
#include <stddef.h>

typedef void (*uart_rx_cb_t)(const uint8_t *data, size_t len);  /* callback type */

static uart_rx_cb_t s_rx_cb = NULL;          /* stored by the driver */

void uart_register_rx_callback(uart_rx_cb_t cb)
{
    s_rx_cb = cb;                            /* the application registers its function */
}

static void uart_frame_complete(const uint8_t *frame, size_t len)   /* called from the driver's ISR */
{
    if (s_rx_cb != NULL)                     /* never call a NULL pointer */
    {
        s_rx_cb(frame, len);                 /* call the application back */
    }
}

/* ---- application ---- */
static void on_uart_frame(const uint8_t *data, size_t len)
{
    (void)data;
    (void)len;                               /* parse the frame here; keep it short (ISR context) */
}

void app_init(void)
{
    uart_register_rx_callback(on_uart_frame);
}
```

### Q24. What happens when a function returns the address of a local variable?

> "It's a bug: the caller gets a **dangling pointer**. The local variable lives on the stack, and its memory is released as soon as the function returns. The pointer still holds that address, but the memory now belongs to whatever function runs next.
>
> It's undefined behaviour. It might even seem to work in a quick test, and then break when another function call overwrites that stack area. The compiler warns: 'function returns address of local variable'."

```c
char *get_name(void)
{
    char name[16] = "sensor";
    return name;                  /* BUG: name is destroyed on return */
}

/* Fixes: return a string literal, use a static buffer, or let the caller pass a buffer */
const char *get_name_fixed(void)
{
    return "sensor";              /* a literal lives for the whole program */
}
```

### Q25. What happens to the local variable's lifetime after the function returns?

> "Its lifetime **ends** at the return. The stack pointer moves back up, and that stack area is free to be reused. The value isn't erased; it just stays there until the next function call or interrupt writes over it. Any access to it after the return is undefined behaviour."

### Q26. Is the returned address necessarily an invalid numerical address?

> "No, and that's what makes this bug dangerous. The address is still a **valid stack address** inside RAM, so reading it won't fault, and it may even still contain the old value. What's wrong is that the memory **no longer belongs** to that variable. So the pointer looks fine, the program may print the right value once, and then the data changes when the next function call reuses the stack."

### Q27. What is recursion?

> "Recursion is when a function **calls itself**, each time with a smaller problem, until it hits a **base case** that stops it. Classic examples are factorial, tree traversal, and quicksort.
>
> In embedded code I'm careful with it, because every call uses stack space, and the depth may depend on the input, so a stack overflow is possible. MISRA C forbids recursion (Rule 17.2) for that reason. I usually write the iterative version instead."

```c
/* Recursive: each call adds a stack frame */
uint32_t factorial(uint32_t n)
{
    return (n <= 1U) ? 1U : n * factorial(n - 1U);   /* base case: n <= 1 */
}

/* Iterative: constant stack usage (preferred in embedded) */
uint32_t factorial_iter(uint32_t n)
{
    uint32_t result = 1U;
    uint32_t i;
    for (i = 2U; i <= n; i++)
    {
        result *= i;
    }
    return result;
}
```

### Q28. What are the risks of uninitialized local variables and pointers?

> "A local variable on the stack isn't initialized: it holds **whatever was left** in that memory. So the code may behave differently on each run, or work in debug and fail in release.
>
> An uninitialized **pointer** is worse. It holds a random address. Dereferencing it can read garbage, corrupt some unrelated variable, or cause a HardFault. So I always initialize locals, and set pointers to `NULL` until they're valid. `-Wall` and static analysis catch most of these."

```c
void bad(void)
{
    uint32_t count;               /* garbage value */
    uint8_t *p;                   /* random address */
    count++;                      /* undefined result */
    *p = 5U;                      /* writes to a random address: corruption or HardFault */
}

void good(void)
{
    uint32_t count = 0U;
    uint8_t *p = NULL;            /* check before use */
}
```

### Q29. What is the purpose of MISRA C guidelines?

> "MISRA C is a set of coding rules for **safety-critical** C, originally from the automotive industry. C has many undefined and implementation-defined behaviours, and MISRA restricts the language to a safer subset, so the code is predictable, portable and easy to analyse.
>
> Examples: no implicit conversions between signed and unsigned, braces on every `if` and loop, no recursion, no dynamic memory, no unchecked return values. Each rule is 'mandatory', 'required' or 'advisory', and any deviation has to be documented. Tools like PC-lint, Polyspace or Cppcheck check it."

### Q30. Why are dynamic memory allocation functions restricted or discouraged under some MISRA rules?

> "MISRA Rule 21.3 bans `malloc` and `free`, because they bring problems that are hard to test away:
>
> - **Fragmentation**: after many allocations and frees, a big request can fail even though there's enough free memory in total.
> - **Non-deterministic timing**: the time `malloc` takes isn't bounded, which is bad for real-time code.
> - **Run-time failure**: `malloc` can return NULL in the field, in a situation the test never hit.
> - **Bugs**: leaks, double free, use after free.
>
> So in safety code all memory is allocated **statically**, and its worst case is known at compile time."

### Q31. How can we implement flexible packet queuing while following MISRA C?

> "I use a **static pool of fixed-size buffers** instead of `malloc`. The pool size is decided at compile time from the worst case. A 'free list' or a bitmap tracks which buffers are in use. Allocating means taking a free buffer from the pool, and freeing means returning it. Both are O(1) and can't fragment.
>
> Then the queue itself is a ring buffer of buffer indexes or pointers. If the pool runs out, I return an error and count it, so it's visible, instead of failing silently."

```c
#include <stdint.h>
#include <stdbool.h>

#define PKT_SIZE     (64U)     /* bytes per packet buffer */
#define PKT_COUNT    (16U)     /* worst-case number of packets in flight */

typedef struct
{
    uint8_t  data[PKT_SIZE];
    uint16_t len;
} packet_t;

static packet_t s_pool[PKT_COUNT];      /* all memory allocated at compile time */
static bool     s_in_use[PKT_COUNT];    /* which buffers are taken */

/* Returns a free packet, or NULL if the pool is empty (caller must handle it) */
packet_t *pkt_alloc(void)
{
    packet_t *pkt = NULL;
    uint32_t  i;

    for (i = 0U; (i < PKT_COUNT) && (pkt == NULL); i++)
    {
        if (!s_in_use[i])
        {
            s_in_use[i] = true;
            pkt = &s_pool[i];
        }
    }
    return pkt;
}

void pkt_free(const packet_t *pkt)
{
    uint32_t i;

    for (i = 0U; i < PKT_COUNT; i++)
    {
        if (&s_pool[i] == pkt)
        {
            s_in_use[i] = false;        /* buffer goes back to the pool */
        }
    }
}
```

In an RTOS, `pkt_alloc()` and `pkt_free()` are protected with a critical section, and the packet pointers are passed between tasks with a queue.

### Q32. How would you optimize embedded code for memory and performance?

> "First I **measure**, I don't guess: the map file for memory, and a cycle counter or a GPIO toggle on a scope for timing. Then I fix the biggest item.
>
> **For memory:** put constant tables in flash with `const`, use the smallest type that fits, order struct members to reduce padding, size task stacks from the high-water mark, avoid big local arrays, and use `-Os`.
>
> **For performance:** use DMA instead of CPU copying, interrupts instead of polling, lookup tables instead of heavy math, fixed-point instead of float on a core without FPU, move hot code to RAM or enable the cache, and avoid division in tight loops, using shifts for powers of two."

**Example:** a sine table of 256 `int16_t` values in flash (`static const int16_t sine_lut[256]`) replaces `sinf()` calls: 512 bytes of flash, no RAM, and a lookup instead of hundreds of cycles.

### Q33. What is the difference between stack and heap memory?

| | Stack | Heap |
| --- | --- | --- |
| Used for | Local variables, return addresses, saved registers | Memory from `malloc()` / `new` |
| Managed by | The compiler, automatically | The programmer: `malloc` and `free` |
| Speed | Very fast: just moves the stack pointer | Slower: searches for a free block |
| Lifetime | Until the function returns | Until `free()` is called |
| Problems | Stack overflow | Fragmentation, leaks, NULL return |
| In embedded | One stack per RTOS task | Often avoided, or only used at start-up |

> "The stack is automatic and fast, but limited, and each task has its own. The heap is flexible, but it can fragment and its timing isn't predictable, so in embedded I mostly allocate statically."

### Q34. How does free() know how much memory to release?

> "When `malloc()` gives you a block, it stores a small **header just before** the returned pointer. The header holds the block's size, and sometimes flags or a link to the next block. When you call `free(p)`, the allocator looks just before `p`, reads the size from the header, and puts that whole block back on the free list.
>
> That's also why writing before the start of a malloc'd buffer, or freeing a pointer that didn't come from `malloc`, corrupts the heap."

```text
          header           your data
      +--------------+-----------------------+
      | size = 32    |   32 bytes usable     |
      +--------------+-----------------------+
                     ^
                     p = malloc(32) returns this address
```

### Q35. How do you extract a byte from a 32-bit integer?

> "I shift the byte down to the lowest position and mask it with `0xFF`. Byte N is `(value >> (8 * N)) & 0xFF`. This works the same on any endianness, unlike using a union or a `uint8_t` pointer."

```c
uint32_t value = 0x12345678UL;

uint8_t byte0 = (uint8_t)( value         & 0xFFUL);   /* 0x78 */
uint8_t byte1 = (uint8_t)((value >>  8U) & 0xFFUL);   /* 0x56 */
uint8_t byte2 = (uint8_t)((value >> 16U) & 0xFFUL);   /* 0x34 */
uint8_t byte3 = (uint8_t)((value >> 24U) & 0xFFUL);   /* 0x12 */
```

### Q36. How do you save a mobile number using minimum memory?

> "A 10-digit number as a string takes 11 bytes. As a `uint64_t` it takes 8 bytes, but leading zeros and the `+` are lost. I'd use **packed BCD**: each digit 0 to 9 needs only 4 bits, so two digits fit in one byte, and 10 digits fit in **5 bytes**. It keeps every digit and is easy to convert back."

```c
#include <stdint.h>
#include <stddef.h>

/* "9876543210" -> {0x98, 0x76, 0x54, 0x32, 0x10}; an odd digit count is padded with 0xF */
void pack_bcd(const char *digits, uint8_t *out, size_t n_digits)
{
    size_t i;

    for (i = 0U; i < n_digits; i += 2U)
    {
        uint8_t hi = (uint8_t)(digits[i] - '0');                       /* first digit -> high nibble  */
        uint8_t lo = ((i + 1U) < n_digits) ? (uint8_t)(digits[i + 1U] - '0')
                                           : 0x0FU;                    /* second digit, or padding    */
        out[i / 2U] = (uint8_t)((uint8_t)(hi << 4U) | lo);
    }
}
```

### Q37. How do you extract specific bits from a hardware register?

> "Two steps: **shift** the field down to bit 0, then **mask** it with as many 1s as the field is wide. The mask for a field of width W is `(1U << W) - 1U`. I usually define the position and the mask as macros, so the code reads like the datasheet."

```c
/* Field MODE is bits 4..6 (3 bits wide) of a status register */
#define MODE_POS     (4U)
#define MODE_MASK    (0x7U)                        /* (1 << 3) - 1 = 0b111 */

uint32_t reg  = 0x000000D0UL;                      /* binary 1101 0000 */
uint32_t mode = (reg >> MODE_POS) & MODE_MASK;     /* 0b101 = 5 */
```

### Q38. How do you declare and access a 32-bit memory-mapped register?

> "I cast the register's address to a pointer to `volatile uint32_t`, and dereference it. Usually I wrap it in a macro, or I use a struct for the whole peripheral, like CMSIS does."

```c
#include <stdint.h>

#define GPIOA_ODR   (*(volatile uint32_t *)0x40020014UL)   /* GPIOA output data register */

void led_on(void)
{
    GPIOA_ODR |= (1UL << 5U);       /* set bit 5: PA5 high */
}

uint32_t read_odr(void)
{
    return GPIOA_ODR;               /* real read from the hardware every time */
}
```

### Q39. Why should a memory-mapped register pointer be declared volatile?

> "Because the hardware can change the register at any moment, and reads or writes can have side effects, like clearing a flag. Without `volatile`, the compiler may:
>
> - read a status register **once** and loop on the cached value forever,
> - **merge or remove** writes, for example two writes to a data register become one,
> - **reorder** register accesses.
>
> All of these break a driver, and usually only with optimization on."

```c
#define UART_SR    (*(volatile uint32_t *)0x40011000UL)
#define SR_TXE     (1UL << 7U)

while ((UART_SR & SR_TXE) == 0UL)   /* without volatile, this could become an endless loop */
{
}
```

### Q40. Why is casting an integer address to a pointer necessary?

> "Because in C, `0x40020014` is just an **integer**, and you can't dereference an integer. The cast tells the compiler: treat this number as the address of a `volatile uint32_t`. Then the compiler knows the size of the access (32 bits) and how to generate the load or store instruction.
>
> MISRA Rule 11.4 discourages integer-to-pointer casts, so register definitions like this are a documented deviation, usually kept in one header such as the CMSIS device file."

---

## 2. C coding and problem-solving exercises

### Q41. Write a function to reverse a string in-place.

> "I use two indexes, one at the start and one at the last character. I swap the two characters and move both indexes toward the middle, until they meet. It's O(n) time and needs no extra buffer, just one temporary `char` for the swap. I also handle NULL and the empty string."

```c
#include <stdio.h>
#include <stddef.h>

/* Reverses a string in place by swapping characters from both ends */
void reverse_string(char *str)
{
    size_t left  = 0U;
    size_t right = 0U;

    if (str != NULL)
    {
        while (str[right] != '\0')          /* find the length (index of '\0') */
        {
            right++;
        }

        if (right > 0U)
        {
            right--;                        /* last real character, not the '\0' */

            while (left < right)            /* stop when the two indexes meet */
            {
                char tmp   = str[left];     /* swap the two ends */
                str[left]  = str[right];
                str[right] = tmp;
                left++;
                right--;
            }
        }
    }
}

int main(void)
{
    char text[] = "Embedded";               /* an array: writable copy of the string */
    char empty[] = "";

    reverse_string(text);
    reverse_string(empty);                  /* edge case: empty string */
    (void)printf("reversed: \"%s\"\n", text);
    (void)printf("empty   : \"%s\"\n", empty);

    return 0;
}
```

**Output:**

```text
reversed: "deddebmE"
empty   : ""
```

### Q42. Why might a string-reversal program fail to produce the expected output?

> "The usual mistakes I've seen are:
>
> - **Modifying a string literal**: `char *s = "hello"; reverse(s);` crashes or does nothing, because the literal is in read-only memory. It must be an array: `char s[] = "hello";`.
> - **Swapping the `'\0'`**: starting `right` at `strlen(s)` instead of `strlen(s) - 1` moves the terminator to the front, so the result prints as an empty string.
> - **Looping to the end instead of the middle**: if the loop runs the whole length, every pair is swapped twice, and the string comes back unchanged.
> - **Unsigned underflow**: with `size_t`, `strlen("") - 1` wraps to a huge number. That's why I check for an empty string.
> - **Missing terminator**: a buffer that was never terminated, so `strlen` runs past the end."

### Q43. Reverse the order of words in a sentence without reversing the characters inside each word.

> "I do it in two passes, in place. First I reverse the **whole sentence**, which puts the words in the right order, but each word is now spelled backwards. Then I reverse **each word** back. It's O(n) and needs no extra buffer."

```text
"I love embedded C"
step 1, reverse all   -> "C deddebme evol I"
step 2, reverse words -> "C embedded love I"
```

```c
#include <stdio.h>
#include <stddef.h>

/* Reverses the characters between str[start] and str[end] (inclusive) */
static void reverse_range(char *str, size_t start, size_t end)
{
    size_t left  = start;
    size_t right = end;

    while (left < right)
    {
        char tmp   = str[left];
        str[left]  = str[right];
        str[right] = tmp;
        left++;
        right--;
    }
}

/* "I love embedded C" -> "C embedded love I"
 * Step 1: reverse the whole sentence  -> "C deddebme evol I"
 * Step 2: reverse each word back      -> "C embedded love I" */
void reverse_words(char *str)
{
    size_t len = 0U;
    size_t start = 0U;
    size_t i;

    if (str != NULL)
    {
        while (str[len] != '\0')
        {
            len++;
        }

        if (len > 1U)
        {
            reverse_range(str, 0U, len - 1U);           /* step 1 */

            for (i = 0U; i <= len; i++)                 /* step 2: walk to each space or the end */
            {
                if ((str[i] == ' ') || (str[i] == '\0'))
                {
                    if (i > start)
                    {
                        reverse_range(str, start, i - 1U);  /* the word is str[start .. i-1] */
                    }
                    start = i + 1U;                     /* next word starts after the space */
                }
            }
        }
    }
}

int main(void)
{
    char sentence[] = "I love embedded C";

    (void)printf("before: \"%s\"\n", sentence);
    reverse_words(sentence);
    (void)printf("after : \"%s\"\n", sentence);

    return 0;
}
```

**Output:**

```text
before: "I love embedded C"
after : "C embedded love I"
```

### Q44. Convert a binary number to a hexadecimal number.

> "Every **4 binary digits** make exactly **one hex digit**, because 2⁴ = 16. So I group the bits in fours starting from the right, pad the leftmost group with zeros if needed, and convert each group to 0 to F."

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Converts a binary string such as "11010110" to a hex string such as "D6".
 * Every group of 4 bits (from the right) becomes one hex digit.
 * hex must have room for (number of bits + 3) / 4 digits + '\0'. Returns 0 on success, -1 on a bad character. */
int32_t binary_to_hex(const char *bin, char *hex)
{
    static const char HEX_DIGITS[] = "0123456789ABCDEF";
    size_t  len = 0U;
    size_t  n_digits;
    size_t  d;
    int32_t result = 0;

    while (bin[len] != '\0')
    {
        len++;
    }
    n_digits = (len + 3U) / 4U;                     /* round up: 6 bits -> 2 hex digits */

    for (d = 0U; (d < n_digits) && (result == 0); d++)
    {
        uint8_t nibble = 0U;
        size_t  b;

        /* hex digit d (counted from the right) uses bits 4d .. 4d+3 (counted from the right) */
        for (b = 0U; b < 4U; b++)
        {
            size_t pos_from_right = (4U * d) + b;
            if (pos_from_right < len)
            {
                char c = bin[len - 1U - pos_from_right];
                if (c == '1')
                {
                    nibble |= (uint8_t)(1U << b);    /* bit b of this nibble is set */
                }
                else if (c != '0')
                {
                    result = -1;                     /* not a binary digit */
                }
                else
                {
                    /* '0': nothing to add */
                }
            }
        }
        hex[n_digits - 1U - d] = HEX_DIGITS[nibble]; /* fill the hex string from the right */
    }
    hex[n_digits] = '\0';

    return result;
}

int main(void)
{
    const char *inputs[] = { "11010110", "101", "1111111100000001" };
    char        hex[8];
    size_t      i;

    for (i = 0U; i < 3U; i++)
    {
        if (binary_to_hex(inputs[i], hex) == 0)
        {
            (void)printf("%-18s -> 0x%s\n", inputs[i], hex);
        }
    }

    return 0;
}
```

**Output:**

```text
11010110           -> 0xD6
101                -> 0x5
1111111100000001   -> 0xFF01
```

### Q45. Explain the binary-to-hexadecimal conversion algorithm.

> "1. Start from the **rightmost** bit, because that's bit 0.
> 2. Split the bits into **groups of 4**. If the last group on the left is short, pad it with zeros.
> 3. Convert each group to its value 0 to 15, and write it as a hex digit: 10 = A, up to 15 = F.
> 4. Write the hex digits in the same order as the groups.
>
> If the number is already in an integer, it's even simpler: hex digit N is `(value >> (4 * N)) & 0xF`."

```text
1101 0110
  |    |
  D    6     ->  0xD6     (1101 = 8+4+1 = 13 = D,  0110 = 4+2 = 6)
```

### Q46. Write code to read a value from a specified memory address.

> "I cast the address to a pointer to `volatile uint32_t` and dereference it. `volatile` makes sure the read really happens, which matters for registers. I also make sure the address is **4-byte aligned** for a 32-bit access, because an unaligned access faults on some cores, like Cortex-M0, and on device memory."

```c
#include <stdio.h>
#include <stdint.h>

/* Reads a 32-bit value from any address. volatile: the read really happens (registers can change). */
static inline uint32_t mem_read32(uintptr_t address)
{
    return *(volatile const uint32_t *)address;
}

/* Writes a 32-bit value to any address. */
static inline void mem_write32(uintptr_t address, uint32_t value)
{
    *(volatile uint32_t *)address = value;
}

int main(void)
{
    /* On the MCU the address would be a register or RAM location, e.g. 0x40020014UL (GPIOA_ODR).
     * On a PC we can only touch our own memory, so the demo uses the address of a variable. */
    static uint32_t fake_register = 0x00000000UL;
    const uintptr_t addr = (uintptr_t)&fake_register;

    mem_write32(addr, 0xDEADBEEFUL);
    (void)printf("wrote 0xDEADBEEF, read back 0x%08lX\n", (unsigned long)mem_read32(addr));

    mem_write32(addr, mem_read32(addr) | (1UL << 4U));   /* read-modify-write: set bit 4 */
    (void)printf("after setting bit 4:        0x%08lX\n", (unsigned long)mem_read32(addr));

    return 0;
}
```

**Output:**

```text
wrote 0xDEADBEEF, read back 0xDEADBEEF
after setting bit 4:        0xDEADBEFF
```

### Q47. Write code to write a value to a specified memory address.

> "Same idea: cast the address to a `volatile uint32_t *` and assign through it. The `mem_write32()` function is in the [Q46](#q46-write-code-to-read-a-value-from-a-specified-memory-address) program. For a register, I usually define a macro once, like `#define GPIOA_ODR (*(volatile uint32_t *)0x40020014UL)`, and then just write `GPIOA_ODR = value;`.
>
> For a register with other bits I must not touch, I do a read-modify-write, or better, use the atomic set/reset register if the chip has one, like `BSRR` on STM32."

### Q48. Implement a circular buffer with Put() and Get() APIs.

> "A circular buffer is a fixed array with two indexes: **head**, where the next byte is written, and **tail**, where the next byte is read. Both move forward and wrap around to 0 at the end. I keep one slot empty, so that 'full' and 'empty' can be told apart without an extra counter.
>
> `Put()` writes the data first and then moves head. `Get()` reads the data first and then moves tail. That order matters when an ISR is the producer: the other side never sees an index pointing to data that isn't written yet."

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define CB_SIZE   (8U)          /* power of two: lets us use & instead of % */

typedef struct
{
    uint8_t           data[CB_SIZE];
    volatile uint32_t head;     /* next position to write (only Put() changes it) */
    volatile uint32_t tail;     /* next position to read  (only Get() changes it) */
} circ_buf_t;

/* One slot is always left empty, so that full and empty can be told apart:
 *   empty: head == tail
 *   full:  next(head) == tail                                                  */
static bool cb_is_empty(const circ_buf_t *cb)
{
    return cb->head == cb->tail;
}

static bool cb_is_full(const circ_buf_t *cb)
{
    return ((cb->head + 1U) % CB_SIZE) == cb->tail;
}

/* Adds one byte. Returns false (and keeps the old data) if the buffer is full. */
bool cb_put(circ_buf_t *cb, uint8_t byte)
{
    bool ok = false;

    if (!cb_is_full(cb))
    {
        cb->data[cb->head] = byte;                   /* 1. write the data first     */
        cb->head = (cb->head + 1U) % CB_SIZE;        /* 2. then publish it (wraps)  */
        ok = true;
    }
    return ok;
}

/* Removes one byte into *byte. Returns false if the buffer is empty. */
bool cb_get(circ_buf_t *cb, uint8_t *byte)
{
    bool ok = false;

    if (!cb_is_empty(cb))
    {
        *byte = cb->data[cb->tail];                  /* 1. read the data first      */
        cb->tail = (cb->tail + 1U) % CB_SIZE;        /* 2. then free the slot       */
        ok = true;
    }
    return ok;
}

int main(void)
{
    circ_buf_t cb = { {0U}, 0U, 0U };
    uint8_t    value;
    uint8_t    i;
    uint32_t   dropped = 0U;

    for (i = 1U; i <= 10U; i++)                      /* try to put 10 bytes into 7 free slots */
    {
        if (!cb_put(&cb, i))
        {
            dropped++;                               /* count overflows, don't hide them */
        }
    }
    (void)printf("put 10 bytes, capacity %u, dropped %lu\n", (unsigned)(CB_SIZE - 1U), (unsigned long)dropped);

    (void)printf("get:");
    while (cb_get(&cb, &value))
    {
        (void)printf(" %u", (unsigned)value);
    }
    (void)printf("\n");

    (void)cb_put(&cb, 42U);                          /* indexes have wrapped around by now */
    (void)cb_get(&cb, &value);
    (void)printf("after wrap-around: got %u, empty = %d\n", (unsigned)value, (int)cb_is_empty(&cb));

    return 0;
}
```

**Output:**

```text
put 10 bytes, capacity 7, dropped 3
get: 1 2 3 4 5 6 7
after wrap-around: got 42, empty = 1
```

### Q49. How do you detect a full or empty circular buffer?

> "There are two common ways:
>
> - **Keep one slot empty** (what I did in Q48): **empty** when `head == tail`; **full** when `(head + 1) % SIZE == tail`. It wastes one slot, but head is only written by the producer and tail only by the consumer, which makes it safe for one ISR and one task.
> - **Keep a count** of stored items: empty when `count == 0`, full when `count == SIZE`. All slots are used, but `count` is changed by both sides, so it needs a critical section."

### Q50. Why is the modulo operator used in circular-buffer indexing?

> "To make the index **wrap around**. When the index reaches the end of the array, `(index + 1) % SIZE` brings it back to 0, so the buffer behaves like a ring.
>
> If `SIZE` is a power of two, I use `(index + 1) & (SIZE - 1)` instead. It gives the same result, and it's a single AND instruction instead of a division, which matters on small cores without a hardware divider."

```text
SIZE = 8:   index 6 -> 7 -> (7 + 1) % 8 = 0 -> 1 ...
```

### Q51. How would you prevent buffer overflow in a circular buffer?

> "`Put()` always **checks for full** before writing, and returns an error instead of overwriting. Then I size the buffer properly: at least the producer's rate multiplied by the longest time the consumer might not run, plus a margin. And I add an **overflow counter**, so in testing I can see if it ever happens.
>
> Indexes are always kept inside 0 to SIZE − 1 by the wrap, so writing outside the array is impossible."

### Q52. How would you make a circular buffer safe for an ISR producer and task consumer?

> "With **one producer and one consumer**, I can make it lock-free:
>
> - Only the ISR writes `head`, and only the task writes `tail`.
> - The indexes are `volatile`, and each is a 32-bit variable, so reading or writing one is atomic on a 32-bit MCU.
> - The producer writes the data **before** updating head; the consumer reads the data **before** updating tail.
> - I use the 'one empty slot' method, not a shared count.
>
> On a multicore system, or a CPU that reorders memory accesses, I'd also add a memory barrier (`__DMB()`) before updating the index. If the design needs a shared count, I protect it with a short critical section."

### Q53. How would you protect a circular buffer if multiple tasks call Get() concurrently?

> "With several consumers, two tasks can read the same `tail`, both take the **same byte**, and both increment `tail`, so one byte is returned twice and another is skipped. The lock-free trick only works for one consumer.
>
> So I protect the whole `Get()` with a **mutex**: take it, check empty, read the byte, move tail, give it back. If `Get()` is very short, a critical section works too. Or I avoid the problem by using a FreeRTOS **queue**, which is already safe for multiple readers and writers."

### Q54. Where would you use a mutex in the circular-buffer implementation?

> "Around the **read-and-advance** in `Get()` when several tasks consume, and around `Put()` when several tasks produce. The mutex covers the check, the data copy and the index update, together as one unit.
>
> I don't use a mutex on the **ISR side**: an ISR can't take a mutex. If an ISR is one of the producers, the task-side code uses a critical section instead of a mutex."

### Q55. Why should a mutex not be used inside a normal ISR?

> "Three reasons:
>
> - Taking a mutex can **block**, and an ISR must never block; there's no task to switch away from.
> - A mutex has an **owner** and uses **priority inheritance**, which only makes sense for tasks; an ISR isn't a task.
> - If a task holds the mutex when the ISR runs, the ISR could never get it, and the system would **deadlock**.
>
> In FreeRTOS, mutex functions don't even have `FromISR` versions. From an ISR I give a semaphore or send a notification, and let a task do the locked work."

### Q56. How would you handle buffer overflow without silently losing unread data?

> "First, I make it **visible**: `Put()` returns an error and increments an overflow counter, and I log it or raise a fault flag. Then I choose a policy that fits the data:
>
> - **Reject new data** (the default): unread data is kept; the producer knows it failed.
> - **Back-pressure**: tell the sender to stop, with UART RTS/CTS flow control or an XOFF, or a 'busy' reply in the protocol.
> - **Overwrite the oldest** only when old data has no value, like a live sensor stream, and then I still count it.
>
> And the long-term fix is a bigger buffer, a faster consumer, or DMA."

### Q57. Write C logic to check bit 4 of a 32-bit hardware status register.

> "I AND the register with a mask that has only bit 4 set, `1U << 4` = `0x10`, and compare the result with zero. I compare explicitly, `!= 0U`, because the AND gives 0x10, not 1."

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define STATUS_READY_BIT   (4U)
#define STATUS_READY_MASK  (1UL << STATUS_READY_BIT)      /* 0x00000010 */

/* On the MCU: #define STATUS_REG (*(volatile const uint32_t *)0x40001000UL) */

static bool is_ready(uint32_t status)
{
    return (status & STATUS_READY_MASK) != 0UL;           /* explicit comparison, gives true/false */
}

int main(void)
{
    const uint32_t samples[] = { 0x00000010UL, 0x000000EFUL, 0xFFFFFFFFUL, 0x00000000UL };
    uint32_t       i;

    for (i = 0U; i < 4U; i++)
    {
        (void)printf("status 0x%08lX -> bit 4 is %s\n", (unsigned long)samples[i],
                     is_ready(samples[i]) ? "SET" : "CLEAR");
    }
    return 0;
}
```

**Output:**

```text
status 0x00000010 -> bit 4 is SET
status 0x000000EF -> bit 4 is CLEAR
status 0xFFFFFFFF -> bit 4 is SET
status 0x00000000 -> bit 4 is CLEAR
```

### Q58. Extract a 12-bit sensor code from bits 8–19 of a 32-bit register.

> "The field is 19 − 8 + 1 = **12 bits** wide and starts at **bit 8**. So I shift right by 8 to bring it down to bit 0, and AND with twelve 1s, `0xFFF`."

```c
uint32_t sensor_code = (reg >> 8U) & 0xFFFUL;   /* bits 8..19 -> bits 0..11 */
```

The full program (it also covers Q59):

```c
#include <stdio.h>
#include <stdint.h>

/* Generic field extraction: width bits starting at bit pos */
static uint32_t get_field(uint32_t value, uint32_t pos, uint32_t width)
{
    const uint32_t mask = (width >= 32U) ? 0xFFFFFFFFUL : ((1UL << width) - 1UL);  /* width ones */
    return (value >> pos) & mask;
}

/* Q58: 12-bit sensor code in bits 8..19 of a 32-bit register */
#define SENSOR_POS    (8U)
#define SENSOR_WIDTH  (12U)                                  /* 19 - 8 + 1 = 12 bits */
#define SENSOR_MASK   ((1UL << SENSOR_WIDTH) - 1UL)          /* 0xFFF */

/* Q59: 16-bit packet: temperature in bits 0..5, pressure in bits 6..15 */
#define TEMP_POS      (0U)
#define TEMP_MASK     (0x3FU)                                /* 6 bits:  0b11_1111      = 63   */
#define PRESS_POS     (6U)
#define PRESS_MASK    (0x3FFU)                               /* 10 bits: 0b11_1111_1111 = 1023 */

int main(void)
{
    const uint32_t reg    = 0xABCDE5F0UL;
    const uint16_t packet = 0xA5D7U;                         /* 1010 0101 11 | 01 0111 */

    uint32_t sensor   = (reg >> SENSOR_POS) & SENSOR_MASK;
    uint16_t temp     = (uint16_t)((packet >> TEMP_POS)  & TEMP_MASK);
    uint16_t pressure = (uint16_t)((packet >> PRESS_POS) & PRESS_MASK);

    (void)printf("register 0x%08lX: sensor code (bits 8-19) = 0x%03lX = %lu\n",
                 (unsigned long)reg, (unsigned long)sensor, (unsigned long)sensor);
    (void)printf("same with get_field()             = 0x%03lX\n",
                 (unsigned long)get_field(reg, SENSOR_POS, SENSOR_WIDTH));
    (void)printf("packet 0x%04X: temperature (bits 0-5) = %u, pressure (bits 6-15) = %u\n",
                 (unsigned)packet, (unsigned)temp, (unsigned)pressure);

    return 0;
}
```

**Output:**

```text
register 0xABCDE5F0: sensor code (bits 8-19) = 0xDE5 = 3557
same with get_field()             = 0xDE5
packet 0xA5D7: temperature (bits 0-5) = 23, pressure (bits 6-15) = 663
```

### Q59. Extract temperature from bits 0–5 and pressure from bits 6–15 of a 16-bit packet.

> "Temperature is 6 bits at bit 0, so it's `packet & 0x3F`. Pressure is 10 bits starting at bit 6, so it's `(packet >> 6) & 0x3FF`. In the program above, packet `0xA5D7` gives temperature **23** and pressure **663**."

```c
uint16_t temperature = (uint16_t)(packet & 0x3FU);           /* bits 0..5  (6 bits)  */
uint16_t pressure    = (uint16_t)((packet >> 6U) & 0x3FFU);  /* bits 6..15 (10 bits) */
```

### Q60. How do you calculate the correct bit mask for a field?

> "For a field that is **W bits wide** and starts at **bit P**:
>
> - The width is `W = high bit − low bit + 1`.
> - The mask at bit 0 is `(1U << W) - 1U`: that's W ones.
> - The mask in place is `((1U << W) - 1U) << P`.
>
> For example, bits 8 to 19: W = 12, mask = 0xFFF, mask in place = 0x000FFF00. One trap: for W = 32, `1U << 32` is undefined, so a full 32-bit mask is just `0xFFFFFFFF`."

| Field | Width | Mask at bit 0 | Mask in place |
| --- | --- | --- | --- |
| Bits 0-5 | 6 | `0x3F` | `0x0000003F` |
| Bits 6-15 | 10 | `0x3FF` | `0x0000FFC0` |
| Bits 8-19 | 12 | `0xFFF` | `0x000FFF00` |

### Q61. What is the digital ADC count for a 13-bit ADC with a 3.3 V reference and a 1.6 V input?

> "A 13-bit ADC has 2¹³ = 8192 levels, from 0 to 8191. The formula is:
>
> **count = Vin / Vref × (2ᴺ − 1) = 1.6 / 3.3 × 8191 ≈ 3971**
>
> Some datasheets use 2ᴺ = 8192 instead, which gives about 3972; the difference is one count. I'd mention both and say I follow the formula in the ADC's datasheet. One count is 3.3 V / 8191 ≈ 0.4 mV."

```c
#include <stdio.h>
#include <stdint.h>

#define ADC_BITS     (13U)
#define ADC_MAX      ((1UL << ADC_BITS) - 1UL)    /* 8191 */
#define VREF_MV      (3300UL)                     /* 3.3 V reference, in millivolts */

/* count = Vin / Vref * (2^N - 1), in integer math (rounded) */
static uint32_t mv_to_count(uint32_t vin_mv)
{
    return ((vin_mv * ADC_MAX) + (VREF_MV / 2UL)) / VREF_MV;    /* + Vref/2 rounds to nearest */
}

/* Back the other way: Vin = count * Vref / (2^N - 1) */
static uint32_t count_to_mv(uint32_t count)
{
    return ((count * VREF_MV) + (ADC_MAX / 2UL)) / ADC_MAX;
}

int main(void)
{
    const uint32_t count = mv_to_count(1600UL);

    (void)printf("13-bit ADC, Vref 3.3 V, Vin 1.6 V -> count = %lu\n", (unsigned long)count);
    (void)printf("check: count %lu -> %lu mV\n", (unsigned long)count, (unsigned long)count_to_mv(count));
    (void)printf("(with 2^N = 8192 instead of 8191 the count would be %lu)\n",
                 (unsigned long)((1600UL * 8192UL + 1650UL) / 3300UL));

    return 0;
}
```

**Output:**

```text
13-bit ADC, Vref 3.3 V, Vin 1.6 V -> count = 3971
check: count 3971 -> 1600 mV
(with 2^N = 8192 instead of 8191 the count would be 3972)
```

### Q62. How would you implement a callback using a function pointer?

> "Three steps: define a **function-pointer type**, let the lower layer **store** a pointer of that type through a register function, and have the lower layer **call it** when the event happens, after checking it isn't NULL. Here a button driver calls the application's handler from its interrupt."

```c
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* ---------------- Button driver (lower layer) ---------------- */
typedef void (*button_cb_t)(uint8_t button_id);    /* callback type: what the app must provide */

#define MAX_BUTTONS  (2U)

static button_cb_t s_callbacks[MAX_BUTTONS] = { NULL, NULL };

/* The application registers which function to call for each button */
void button_register(uint8_t id, button_cb_t cb)
{
    if (id < MAX_BUTTONS)
    {
        s_callbacks[id] = cb;
    }
}

/* Called from the EXTI interrupt on the MCU; here main() calls it to simulate a press */
void button_isr(uint8_t id)
{
    if ((id < MAX_BUTTONS) && (s_callbacks[id] != NULL))
    {
        s_callbacks[id](id);                       /* the driver calls the app back */
    }
}

/* ---------------- Application (upper layer) ---------------- */
static void on_start_pressed(uint8_t id) { (void)printf("button %u: START motor\n", (unsigned)id); }
static void on_stop_pressed(uint8_t id)  { (void)printf("button %u: STOP motor\n",  (unsigned)id); }

int main(void)
{
    button_register(0U, on_start_pressed);
    button_register(1U, on_stop_pressed);

    button_isr(0U);                                /* simulate pressing button 0 */
    button_isr(1U);                                /* simulate pressing button 1 */
    button_isr(5U);                                /* invalid id: safely ignored  */

    return 0;
}
```

**Output:**

```text
button 0: START motor
button 1: STOP motor
```

### Q63. What is the difference between integer promotion and type conversion?

> "**Integer promotion** is automatic: before any arithmetic, types smaller than `int`, like `uint8_t`, `int8_t` and `uint16_t`, are first converted to `int`. So `uint8_t` 200 + 100 is calculated as an `int` and gives 300, not 44.
>
> **Type conversion** is the broader idea: changing a value from one type to another. It can be **implicit**, like assigning an `int` to a `uint8_t`, or the 'usual arithmetic conversions' when a signed value meets an unsigned one, or **explicit**, with a cast.
>
> Promotion is one specific kind of implicit conversion. The classic surprises are `~` on a `uint8_t`, which gives a 32-bit result, and signed/unsigned comparisons."

```c
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t  a = 200U;
    uint8_t  b = 100U;
    uint8_t  c = (uint8_t)(a + b);     /* a and b are promoted to int: 300, then converted to uint8_t: 44 */
    int      sum_int = a + b;          /* promotion: the int result keeps 300 */

    uint8_t  x = 0x0FU;
    uint32_t inverted = (uint32_t)~x;  /* x is promoted to int first: ~0x0000000F = 0xFFFFFFF0 */

    int32_t  s = -1;
    uint32_t u = 1U;

    (void)printf("uint8 200 + 100 as int      = %d (integer promotion)\n", sum_int);
    (void)printf("stored back into uint8_t    = %u (conversion, modulo 256)\n", (unsigned)c);
    (void)printf("~0x0F after promotion       = 0x%08lX (not 0xF0)\n", (unsigned long)inverted);
    (void)printf("-1 < 1 compared as signed   : %s\n", (s < (int32_t)u) ? "true" : "false");
    (void)printf("-1 < 1U compared as unsigned: %s (-1 becomes 0xFFFFFFFF)\n", ((uint32_t)s < u) ? "true" : "false");

    return 0;
}
```

**Output:**

```text
uint8 200 + 100 as int      = 300 (integer promotion)
stored back into uint8_t    = 44 (conversion, modulo 256)
~0x0F after promotion       = 0xFFFFFFF0 (not 0xF0)
-1 < 1 compared as signed   : true
-1 < 1U compared as unsigned: false (-1 becomes 0xFFFFFFFF)
```

### Q64. How would you implement bit manipulation without unnecessary library functions?

> "Everything can be done with the bitwise operators `&`, `|`, `^`, `~`, `<<` and `>>`. I define a few small macros or inline functions once and reuse them, so the code is readable and doesn't need any library."

```c
#define BIT(n)              (1UL << (n))

#define SET_BIT(reg, n)     ((reg) |=  BIT(n))       /* set bit n    */
#define CLEAR_BIT(reg, n)   ((reg) &= ~BIT(n))       /* clear bit n  */
#define TOGGLE_BIT(reg, n)  ((reg) ^=  BIT(n))       /* toggle bit n */
#define READ_BIT(reg, n)    (((reg) >> (n)) & 1UL)   /* 0 or 1       */

/* Write a value into a field of width w at position p, leaving the other bits alone */
static inline uint32_t write_field(uint32_t reg, uint32_t p, uint32_t w, uint32_t value)
{
    const uint32_t mask = ((1UL << w) - 1UL) << p;   /* w ones, moved to position p */
    return (reg & ~mask) | ((value << p) & mask);    /* clear the field, then insert */
}

/* Count the set bits without a library call */
static inline uint32_t count_bits(uint32_t x)
{
    uint32_t count = 0U;
    while (x != 0UL)
    {
        x &= (x - 1UL);                              /* clears the lowest set bit */
        count++;
    }
    return count;
}
```

---

## 3. RTOS, FreeRTOS and scheduling

### Q65. What experience do you have with FreeRTOS?

*(Adapt this to your own projects.)*

> "I've used FreeRTOS on STM32 in production projects. I designed the task structure, typically separate tasks for communication, sensor acquisition, control and logging, each with its own priority and stack size. For communication between tasks I used **queues** for data, **task notifications** and **binary semaphores** for events from ISRs, and **mutexes** for shared resources like the I2C bus and the debug UART.
>
> I've also tuned things: sizing stacks with `uxTaskGetStackHighWaterMark()`, enabling stack-overflow checking and `configASSERT`, choosing heap_4, and fixing the classic interrupt-priority problem with `configMAX_SYSCALL_INTERRUPT_PRIORITY`."

### Q66. What are the common task-scheduling schemes in an RTOS?

> "The main ones are:
>
> - **Preemptive priority-based**: the highest-priority ready task always runs. This is the default in FreeRTOS.
> - **Round-robin / time slicing**: tasks with the **same** priority share the CPU, each for one tick at a time.
> - **Cooperative**: a task runs until it gives up the CPU itself, by blocking or yielding.
>
> In real-time theory there are also **rate-monotonic** (a shorter period gets a higher priority) and **earliest-deadline-first** scheduling. In FreeRTOS I use preemptive priorities and assign them rate-monotonically: the fastest, most time-critical task gets the highest priority."

### Q67. What is preemptive scheduling?

> "In preemptive scheduling, the RTOS can **stop a running task at any time** to run a higher-priority task that has become ready. The running task doesn't have to cooperate. For example, if a low-priority logging task is running and a UART interrupt wakes the high-priority protocol task, the RTOS switches to the protocol task immediately when the ISR ends.
>
> It gives good response times for important tasks, but shared data needs protection, because a task can be interrupted in the middle of anything."

### Q68. What is cooperative scheduling?

> "In cooperative scheduling, a task keeps the CPU **until it gives it up by itself**: by calling `taskYIELD()`, a delay, or a blocking call like waiting on a queue. The scheduler never interrupts it. In FreeRTOS that's `configUSE_PREEMPTION = 0`.
>
> It's simpler and has fewer race conditions between tasks, but one task that loops for a long time without yielding blocks everyone else."

### Q69. When would you use cooperative scheduling?

> "When the system is **simple**, the tasks are **short**, and I want to avoid the complexity of protecting shared data. For example, a small device with a few periodic jobs and no hard deadlines, or a very small MCU where I want minimal RAM and overhead.
>
> It's also useful when porting an existing superloop design step by step. For anything with real deadlines, I prefer preemptive scheduling."

### Q70. At what point can a task be preempted under cooperative versus preemptive scheduling?

> "- **Preemptive**: at **almost any instruction**. Whenever a tick or an interrupt makes a higher-priority task ready, the switch happens as soon as the interrupt returns. The only exceptions are while interrupts are disabled, or inside a critical section.
> - **Cooperative**: **only at points the task chooses**, when it calls `taskYIELD()`, a delay, or a blocking API. Interrupts still run in between, but they don't cause a task switch."

### Q71. What is context switching?

> "Context switching is when the CPU **stops running one task and starts running another**. The RTOS saves the current task's registers, its 'context', on that task's stack, and stores its stack pointer in its task control block. Then it loads the next task's stack pointer and restores its registers, so the next task continues exactly where it stopped. Only registers are saved; no memory is copied."

### Q72. How does context switching differ between bare-metal and RTOS systems?

> "In **bare metal** there are no tasks, so there's no real context switch. The only switch is into and out of an **interrupt**: the hardware saves some registers, runs the ISR, and returns to the exact same place in the main loop.
>
> In an **RTOS**, after the interrupt, or when a task blocks, the RTOS can return to a **different task**. That needs a separate stack per task, a TCB per task, and the RTOS's own switch code (PendSV on Cortex-M) to save and restore the rest of the registers."

### Q73. Does the hardware or the RTOS save the CPU registers during a context switch?

> "**Both**, and they split the work. On Cortex-M, when an exception happens, the **hardware** automatically pushes R0-R3, R12, LR, PC and xPSR onto the task's stack. When the RTOS decides to switch tasks, its **PendSV handler** saves the rest, R4-R11 (plus S16-S31 if the task used the FPU), and stores the stack pointer in the TCB. Then it restores the next task in reverse order."

### Q74. Which registers does Cortex-M hardware automatically save during exception entry?

> "Eight registers, called the **basic stack frame**: **R0, R1, R2, R3, R12, LR, PC and xPSR**, in that order on the stack. If the FPU is enabled and the interrupted code used it, the hardware also reserves space for **S0-S15 and FPSCR** (with lazy stacking, they're only saved if the ISR uses the FPU). These are exactly the registers a C function is allowed to change, so an ISR can be written as a normal C function."

### Q75. Which additional registers does FreeRTOS save?

> "In its PendSV handler, FreeRTOS saves the **callee-saved registers R4-R11**. On a Cortex-M4F or M7 with the FPU in use, it also saves **S16-S31**. It also saves the **EXC_RETURN** value, which tells it later whether the task's frame includes FPU registers. Then it writes the task's stack pointer (PSP) into the task's TCB."

```text
Task stack after a switch (top of stack at the bottom):
  xPSR, PC, LR, R12, R3, R2, R1, R0    <- saved by hardware
  R11 ... R4, (S31 ... S16), EXC_RETURN <- saved by FreeRTOS in PendSV
  TCB->pxTopOfStack points here
```

### Q76. What is PendSV, and is it RTOS-specific?

> "PendSV, 'pendable service call', is a **standard Cortex-M system exception**. It's part of the ARMv7-M and ARMv8-M architecture, not something FreeRTOS invented. Software can **pend** it by setting a bit in the ICSR register, and it then runs when no higher-priority exception is active.
>
> It's *designed* for operating systems, though. RTOSes like FreeRTOS, Zephyr and RTX give it the **lowest priority** and do the context switch inside it. That way, the switch only happens after every other interrupt has finished."

### Q77. How does the CPU know when Task A should be replaced by Task B?

> "The CPU itself doesn't know; the **scheduler** decides. A switch is triggered by one of these events:
>
> - The **tick interrupt**: a delay expires and a higher-priority task becomes ready, or a time slice ends for equal-priority tasks.
> - **Task A blocks**: it waits on a queue, a semaphore or a delay, so it can't run.
> - An **ISR wakes a higher-priority task**, for example by giving a semaphore.
> - Task A **yields** or changes priorities.
>
> In each case the scheduler picks the highest-priority ready task. If it's not the current one, it pends PendSV, and the switch happens there."

### Q78. What is the role of the scheduler during context switching?

> "The scheduler decides **which task runs next**. FreeRTOS keeps a **ready list per priority level**. The scheduler finds the highest priority that has a ready task, quickly, using a bitmap and the CLZ instruction on Cortex-M, and takes the next task from that list, which gives round-robin for equal priorities. It then sets `pxCurrentTCB` to that task. The PendSV code does the actual saving and restoring of registers, and uses `pxCurrentTCB` to know which task to resume."

### Q79. What is the Link Register (LR)?

> "LR, which is R14, holds the **return address** of a function call. When the CPU executes `BL function`, it stores the address of the next instruction in LR and jumps. The function returns with `BX LR`.
>
> In an exception, LR has a different job: it holds a special **EXC_RETURN** value, like `0xFFFFFFFD`, that tells the CPU how to return: to thread or handler mode, using MSP or PSP, and with or without an FPU frame."

### Q80. What happens to LR during nested function calls?

> "LR holds only **one** return address. So when function A calls function B, and B calls function C, B would lose its own return address when it calls C. To prevent that, the compiler makes B **push LR onto the stack** in its prologue, and pop it back into PC in its epilogue. A 'leaf' function, one that calls nothing else, can leave LR in the register.
>
> That's also why a stack overflow or a buffer overrun on the stack can overwrite a saved LR, and the function then 'returns' to a garbage address and HardFaults."

```text
main   -> BL A   : LR = return into main
A      : PUSH {LR}        ; save main's return address
A      -> BL B   : LR = return into A
B      : (leaf: uses LR directly) BX LR
A      : POP {PC}         ; return to main
```

### Q81. What is the purpose of the SVC handler?

> "SVC is the **supervisor call** exception. The `SVC #n` instruction triggers it on purpose, from software. It's used to request a privileged service: user-mode code calls SVC, and the handler runs in privileged mode, like a system call.
>
> FreeRTOS uses SVC to **start the first task**: `vPortSVCHandler` loads the first task's context and switches the CPU to using the PSP. In systems with an MPU, SVC is also the gate from unprivileged tasks into kernel functions."

### Q82. What happens when multiple interrupts occur in a bare-metal application?

> "The **NVIC** handles it by priority:
>
> - If two interrupts are pending at the same time, the one with the **higher priority** (lower number) runs first. If the priorities are equal, the lower IRQ number goes first.
> - If a **higher-priority** interrupt arrives while an ISR is running, it **preempts** it: nesting.
> - A **lower or equal** priority interrupt waits until the current ISR finishes. Then the CPU **tail-chains** into it directly, without returning to main in between.
>
> The main loop only continues when no interrupt is pending."

### Q83. What is interrupt latency?

> "Interrupt latency is the time from when the interrupt **signal arrives** to when the **first instruction of the ISR** executes. On a Cortex-M3/M4 it's **12 clock cycles** in the best case, for the hardware stacking and vector fetch.
>
> In practice it's longer, because of things the software does: interrupts being disabled in a critical section, a higher-priority ISR running, flash wait states, or the RTOS masking interrupts. That's why I keep critical sections and ISRs short."

### Q84. How do you enable and disable interrupts at the correct time?

> "My rules:
>
> - **During init**, I configure the peripheral completely, clear any pending flag, and only then enable the interrupt in the peripheral and in the NVIC. Otherwise an old pending flag fires immediately.
> - **To protect shared data**, I disable interrupts for the **shortest possible** time: only around the few lines that touch the data.
> - I **save and restore** the previous state, instead of blindly re-enabling, so nested critical sections work.
> - With FreeRTOS, I use `taskENTER_CRITICAL()` and `taskEXIT_CRITICAL()`, which only mask interrupts up to the kernel's priority level, so very high-priority interrupts still run."

```c
uint32_t primask = __get_PRIMASK();   /* remember whether interrupts were already off */
__disable_irq();                      /* start of the critical section */
shared_counter++;                     /* keep this part as short as possible */
__set_PRIMASK(primask);               /* restore the previous state, don't just enable */
```

### Q85. What is a critical section?

> "A critical section is a piece of code that accesses a **shared resource** and must not be interrupted in the middle, by an ISR or another task. Otherwise the shared data can be left half-updated. Example: updating a 64-bit timestamp on a 32-bit MCU takes two writes, and an ISR reading it in between gets half old, half new."

### Q86. How do you protect a critical section from concurrent task execution?

> "It depends on who shares the data and how long the code takes:
>
> - **Shared with an ISR, short code**: disable interrupts, or `taskENTER_CRITICAL()` in FreeRTOS.
> - **Shared only between tasks, short code**: suspend the scheduler with `vTaskSuspendAll()`, or a critical section.
> - **Shared between tasks, longer code** (like an I2C transaction): a **mutex**.
>
> Or I avoid sharing completely: one task owns the resource, and others send it requests through a queue."

### Q87. What is the difference between a critical section and a mutex?

| | Critical section | Mutex |
| --- | --- | --- |
| How | Disables interrupts / the scheduler | RTOS object that tasks take and give |
| Blocks other code | Everything (or everything up to a priority level) | Only tasks that want the same mutex |
| Use from an ISR | Yes (protects against ISRs) | No |
| Duration | Must be very short (microseconds) | Can be longer (an I2C transfer) |
| Waiting task | Never waits, nothing else can run | Sleeps until the mutex is free |
| Priority inheritance | Not needed | Yes |

> "A critical section is a big hammer for a few lines. A mutex is targeted: only tasks that need the same resource wait, and everything else keeps running."

### Q88. What is a semaphore?

> "A semaphore is an RTOS object that holds a **count**. `Take` decrements it, and if it's already 0, the task **blocks** until someone gives. `Give` increments it and wakes a waiting task. It has no owner, so one task or ISR can give it and a different task can take it.
>
> I use it mainly for **signaling**, like 'data is ready', from an ISR to a task, and for **counting** limited resources."

### Q89. What is the difference between binary and counting semaphores?

> "A **binary** semaphore can only be 0 or 1: it's like a flag. If it's given twice before anyone takes it, the second give is lost.
>
> A **counting** semaphore can go up to a maximum N. It remembers how many gives happened, or how many resources are free."

| | Binary | Counting |
| --- | --- | --- |
| Values | 0 or 1 | 0 to N |
| Repeated gives | Collapse into one | Each one is counted |
| Typical use | Signal one event | Count events or free resources |
| FreeRTOS | `xSemaphoreCreateBinary()` | `xSemaphoreCreateCounting(max, initial)` |

### Q90. Give suitable scenarios for binary and counting semaphores.

> "**Binary**: the ADC-complete interrupt gives the semaphore, and the processing task, blocked on `xSemaphoreTake()`, wakes up and processes the samples. One event, one wake-up.
>
> **Counting, for resources**: a pool of 4 DMA buffers. The semaphore starts at 4; each task takes one before using a buffer and gives it back after. The fifth task waits.
>
> **Counting, for events**: a button ISR that can fire several times before the task runs. A counting semaphore remembers that there were 3 presses, where a binary one would only remember 1."

```c
/* Binary: ISR -> task signal */
static SemaphoreHandle_t s_adc_done;

void ADC_IRQHandler(void)
{
    BaseType_t woken = pdFALSE;
    xSemaphoreGiveFromISR(s_adc_done, &woken);   /* signal: data ready         */
    portYIELD_FROM_ISR(woken);                   /* switch now if needed       */
}

void adc_task(void *arg)
{
    for (;;)
    {
        xSemaphoreTake(s_adc_done, portMAX_DELAY);   /* sleep until the ISR signals */
        process_samples();
    }
}
```

### Q91. What is the difference between a semaphore and a mutex?

> "A **mutex** is for **mutual exclusion**: protecting a shared resource. It has an **owner**: the task that takes it must give it back. And it supports **priority inheritance**.
>
> A **semaphore** is for **signaling** or **counting**. It has **no owner**: an ISR or one task gives it, and another task takes it. No priority inheritance.
>
> So: two tasks sharing the I2C bus use a mutex. An ISR telling a task 'data arrived' uses a semaphore. And a mutex can never be used from an ISR."

### Q92. What is priority inheritance?

> "Priority inheritance means: when a **high-priority task is waiting** for a mutex that a **low-priority task holds**, the RTOS temporarily **raises the low-priority task to the high priority**. So it can finish its work and release the mutex quickly. When it gives the mutex back, its priority returns to normal. FreeRTOS mutexes do this automatically; semaphores don't."

### Q93. How does priority inversion occur?

> "It needs three tasks: High, Medium and Low.
>
> 1. **Low** takes a mutex for a shared resource.
> 2. **High** becomes ready, preempts Low, and tries to take the same mutex. It blocks, waiting for Low.
> 3. **Medium** becomes ready. It doesn't need the mutex, but its priority is higher than Low's, so it preempts Low.
> 4. Now Medium runs for as long as it likes. Low can't run to release the mutex, so **High is effectively blocked by Medium**, a lower-priority task.
>
> That's priority inversion. The famous example is the Mars Pathfinder rover, which kept resetting because of it."

### Q94. How does priority inheritance resolve priority inversion?

> "At step 2, when High blocks on the mutex, the RTOS raises **Low to High's priority**. Now, at step 3, Medium can't preempt Low, because Low is temporarily running at High's priority. Low finishes its short critical section, gives the mutex, drops back to its own priority, and High immediately gets the mutex and runs. The delay for High is limited to Low's critical section, not Medium's whole run time."

```text
Without inheritance:  L(lock) -> H blocks -> M runs ... long ... -> L unlocks -> H runs
With inheritance:     L(lock) -> H blocks -> L runs at H's priority -> L unlocks -> H runs -> M runs
```

### Q95. How do you transfer data between producer and consumer tasks?

> "My default is a **FreeRTOS queue**. The producer calls `xQueueSend()`, and the consumer blocks in `xQueueReceive()` until an item arrives. The queue copies the data, so there's no shared buffer to protect, and it handles the synchronization and blocking for me.
>
> For large data, like a 1 KB frame, I don't copy the whole frame through the queue. I send a **pointer** or a buffer index from a static pool. For a byte stream from an ISR, I use a **stream buffer** or a ring buffer plus a task notification."

```c
typedef struct { uint16_t id; int32_t value; } sample_t;

static QueueHandle_t s_queue;     /* created once: xQueueCreate(16, sizeof(sample_t)) */

void producer_task(void *arg)
{
    sample_t s = { 1U, 0 };
    for (;;)
    {
        s.value = read_sensor();
        (void)xQueueSend(s_queue, &s, pdMS_TO_TICKS(10));    /* copy into the queue */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void consumer_task(void *arg)
{
    sample_t s;
    for (;;)
    {
        if (xQueueReceive(s_queue, &s, portMAX_DELAY) == pdPASS)   /* sleeps until data arrives */
        {
            log_sample(&s);
        }
    }
}
```

### Q96. Which IPC mechanisms have you used?

> "In FreeRTOS: **queues** for passing data, **binary and counting semaphores** for signaling, **mutexes** for shared resources, **task notifications** as a fast lightweight signal from ISRs, **event groups** to wait on several conditions at once, and **stream and message buffers** for byte streams from one ISR or task to one task.
>
> On Linux: pipes, message queues, shared memory with semaphores, Unix and TCP sockets, and signals."

### Q97. When would you use a queue instead of a semaphore?

> "When I need to send **data**, not just an event. A semaphore only says 'something happened'. A queue says 'something happened, and here's the value', and it buffers several items in order.
>
> For example: a button press just needs a semaphore or a notification. ADC readings that the consumer needs to process one by one need a queue."

### Q98. How do you synchronize multiple tasks accessing a shared resource?

> "My first choice is to **give the resource to one task**: a 'gatekeeper' task owns the I2C bus or the UART, and the other tasks send it requests through a queue. Then nothing is shared, and there are no locks to get wrong.
>
> If several tasks really must use it directly, I protect it with a **mutex**, held for the whole transaction and released quickly, with a timeout instead of waiting forever. I always take multiple mutexes in the **same order** everywhere, to avoid deadlock."

### Q99. What happens if a higher-priority task becomes ready while a lower-priority task is running?

> "With preemptive scheduling, the lower-priority task is **preempted immediately**. If the higher-priority task was made ready by an ISR, the switch happens as soon as the ISR exits, via `portYIELD_FROM_ISR` and PendSV. If it was made ready by the running task itself, for example by giving a semaphore, the switch happens inside that API call. The lower-priority task stays in the ready list and continues later, exactly where it was stopped.
>
> With cooperative scheduling, the higher-priority task waits until the running task yields or blocks."

### Q100. How would you port FreeRTOS to an MCU that has no existing FreeRTOS port?

> "First I check whether a port for the **same CPU core** already exists, because ports are per **core and compiler**, not per chip. If the MCU has a Cortex-M4 core, the existing GCC/ARM_CM4F port works; I only need the chip's startup code and a tick timer.
>
> If the core is really new, I write a port by copying the closest existing one and adapting it:
>
> 1. `portmacro.h`: data types, stack growth direction, critical-section macros, yield macro.
> 2. `port.c`: initializing a new task's stack, starting the first task, the context-switch interrupt, and the tick interrupt.
> 3. `FreeRTOSConfig.h`: clock frequency, tick rate, priorities, heap size.
> 4. Then test step by step: one task, two tasks with delays, then queues and interrupts."

### Q101. What low-level components must be implemented in a new RTOS port?

> "The port layer must provide:
>
> - **Stack initialization**: `pxPortInitialiseStack()` builds a fake saved context on a new task's stack, so the first switch to it 'returns' into the task function.
> - **Start of scheduler**: `xPortStartScheduler()` sets up the tick and starts the first task.
> - **Context switch**: save and restore registers, usually in a software interrupt like PendSV.
> - **Tick interrupt**: calls `xTaskIncrementTick()` and requests a switch if needed.
> - **Critical sections**: enter/exit macros that disable or mask interrupts, with nesting.
> - **Yield**: `portYIELD()` and `portYIELD_FROM_ISR()`.
> - Optionally, **tickless idle** for low power."

### Q102. What would you do if the MCU has no SysTick or dedicated system timer?

> "The RTOS only needs **some periodic interrupt**. So I'd use any **general-purpose hardware timer**: configure it for a periodic interrupt at the tick rate, for example 1 kHz, and call the RTOS tick handler from its ISR. FreeRTOS lets the application provide `vPortSetupTimerInterrupt()` for exactly this.
>
> If there's no free timer at all, a low-power timer or RTC periodic interrupt can work, at a lower tick rate. And it must run at the **lowest interrupt priority**, like SysTick normally does."

### Q103. How would you generate the RTOS tick using another hardware timer?

> "I configure the timer in periodic mode, so its period equals one tick, and in its ISR I clear the flag and call the kernel's tick function."

```c
/* Example: TIM2 on a 72 MHz clock as the FreeRTOS tick (1 kHz) */
void vPortSetupTimerInterrupt(void)                    /* FreeRTOS calls this at scheduler start */
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;               /* 1. clock for TIM2                     */
    TIM2->PSC = 72U - 1U;                              /* 2. 72 MHz / 72 = 1 MHz timer clock    */
    TIM2->ARR = (1000000U / configTICK_RATE_HZ) - 1U;  /* 3. 1 MHz / 1000 = 1 ms period          */
    TIM2->DIER |= TIM_DIER_UIE;                        /* 4. update (overflow) interrupt         */
    NVIC_SetPriority(TIM2_IRQn, configKERNEL_INTERRUPT_PRIORITY >> (8U - __NVIC_PRIO_BITS)); /* lowest */
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1 |= TIM_CR1_CEN;                          /* 5. start the timer                      */
}

void TIM2_IRQHandler(void)
{
    TIM2->SR = ~TIM_SR_UIF;                            /* clear the update flag first */
    if (xTaskIncrementTick() != pdFALSE)               /* advance the tick; a task became ready? */
    {
        portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT; /* request a context switch (PendSV) */
    }
}
```

### Q104. How would you validate a newly ported RTOS?

> "Step by step, from simple to stressful:
>
> 1. **Tick**: toggle a GPIO in the tick ISR and check 1 kHz on a scope.
> 2. **One task** running and blinking with `vTaskDelay()`: timing must be exact.
> 3. **Two tasks** with different priorities: check preemption and that the context is preserved, for example with known values in registers and local variables.
> 4. **IPC**: queues, semaphores, mutexes, and calls from ISRs with `FromISR`.
> 5. **Interrupt nesting** at different priorities, including the FPU if the core has one.
> 6. **Stress test** for hours: many tasks, high interrupt load, with `configASSERT`, stack-overflow checking and run-time stats on.
>
> The FreeRTOS demo projects also include standard test tasks that are exactly for this."

### Q105. How do you choose an RTOS for an embedded system?

> "I look at:
>
> - **Hardware**: does it support my core, and how much flash and RAM does it need?
> - **Real-time needs**: latency, determinism, priority inheritance.
> - **Features**: networking (TCP/IP, MQTT), file system, USB, BLE stacks, security, power management.
> - **Certification**: for safety products, a certified RTOS like SAFERTOS, or Zephyr or ThreadX with safety artefacts.
> - **License and cost**: MIT (FreeRTOS), Apache (Zephyr), or commercial.
> - **Ecosystem**: vendor support, documentation, the team's experience, debug tool awareness.
>
> For a typical STM32 product, FreeRTOS is the default choice: small, well known, and supported by ST's tools. If I need a big integrated stack, Zephyr is a strong option."

### Q106. How do you measure worst-case execution time and verify real-time deadlines?

> "I measure on the real hardware:
>
> - **GPIO toggling**: set a pin at the start of the code and clear it at the end, and measure the pulse with a scope or logic analyzer over many runs. I trigger on the longest pulse.
> - **The DWT cycle counter** on Cortex-M: read `DWT->CYCCNT` before and after, and keep the maximum.
> - **Tracing tools** like Percepio Tracealyzer or SEGGER SystemView, which show every task switch and interrupt over time.
>
> I test under worst-case conditions: maximum interrupt load, all caches cold, every error path. Then I check that each task's worst-case response time, including preemption by higher-priority tasks, is within its deadline, with some margin."

```c
CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;   /* enable the DWT unit           */
DWT->CYCCNT = 0U;
DWT->CTRL  |= DWT_CTRL_CYCCNTENA_Msk;             /* start the cycle counter        */

uint32_t start = DWT->CYCCNT;
control_loop();                                   /* code under test                */
uint32_t cycles = DWT->CYCCNT - start;            /* at 168 MHz: cycles / 168 = µs   */
if (cycles > s_max_cycles) { s_max_cycles = cycles; }   /* keep the worst case     */
```

---

## 4. Interrupts, DMA, ADC and peripherals

### Q107. How does an external interrupt reach the CPU?

> "On an STM32, for example a button on PA0:
>
> 1. The pin changes level. The **GPIO** input is routed through the **SYSCFG** multiplexer to **EXTI line 0**.
> 2. **EXTI** detects the edge I configured (rising, falling or both), and sets its pending bit, if that line is unmasked.
> 3. EXTI raises the **EXTI0 interrupt request** to the **NVIC**.
> 4. The NVIC checks that the IRQ is enabled and its priority is high enough, and signals the **CPU**.
> 5. The CPU stacks the registers, reads the handler address from the **vector table**, and runs `EXTI0_IRQHandler()`. The ISR must clear the EXTI pending bit."

```text
Pin PA0 -> SYSCFG mux -> EXTI (edge detect, pending bit) -> NVIC (enable, priority) -> CPU -> vector table -> EXTI0_IRQHandler()
```

### Q108. What happens internally when a Cortex-M interrupt occurs?

> "1. The NVIC sees the pending interrupt has a higher priority than the current code.
> 2. The hardware **pushes 8 registers** (R0-R3, R12, LR, PC, xPSR) onto the current stack, and FPU registers if needed.
> 3. It writes an **EXC_RETURN** value into LR.
> 4. It switches to **handler mode**, using the main stack (MSP).
> 5. It **fetches the ISR address** from the vector table, at VTOR + 4 × exception number, and jumps there. This takes about 12 cycles.
> 6. When the ISR executes `BX LR` with EXC_RETURN, the hardware **pops** the saved registers and the interrupted code continues. If another interrupt is pending, it **tail-chains** straight into it instead."

### Q109. How does the NVIC handle multiple pending interrupts?

> "It always serves the **highest priority first**, meaning the **lowest priority number**. If two pending interrupts have the same priority, the one with the **lower IRQ number** wins. The others stay pending and run one after another through **tail-chaining**, without returning to thread mode in between.
>
> Priorities can also be split into **group priority**, which decides preemption, and **sub-priority**, which only decides the order between pending interrupts of the same group."

### Q110. Can a higher-priority interrupt preempt a lower-priority ISR?

> "Yes, that's **interrupt nesting**, and the NVIC does it automatically. If an ISR at priority 5 is running and an interrupt at priority 2 arrives, the CPU stacks the priority-5 ISR's registers, runs the priority-2 ISR, and then returns to the priority-5 ISR.
>
> An interrupt with **equal or lower** priority can't preempt; it waits until the current ISR finishes."

### Q111. How have you used ISRs in your FreeRTOS projects?

> "I keep ISRs very short and use the **deferred interrupt processing** pattern. The ISR only reads or clears the hardware, maybe puts a byte into a ring buffer, and then wakes a task with a task notification or a semaphore, using the `FromISR` API and `portYIELD_FROM_ISR()`. The actual processing, like parsing a UART frame or filtering ADC data, runs in a task at the right priority.
>
> I also set every ISR that calls FreeRTOS APIs to a priority numerically at or above `configMAX_SYSCALL_INTERRUPT_PRIORITY`. That was a real bug I fixed once: an ISR left at priority 0 calling `xQueueSendFromISR()` caused random crashes."

### Q112. How do you communicate from an ISR to a task?

> "Using the **`FromISR`** versions of the FreeRTOS APIs:
>
> - **Task notification**: `vTaskNotifyGiveFromISR()`. The fastest and lightest, for one receiving task.
> - **Binary or counting semaphore**: `xSemaphoreGiveFromISR()`.
> - **Queue**: `xQueueSendFromISR()`, when I need to pass data.
> - **Stream buffer**: `xStreamBufferSendFromISR()`, for byte streams.
>
> Each takes a `pxHigherPriorityTaskWoken` flag, and at the end of the ISR I call `portYIELD_FROM_ISR()` with it, so the woken task runs immediately."

```c
static TaskHandle_t s_rx_task;          /* set when the task is created */

void USART2_IRQHandler(void)
{
    BaseType_t woken = pdFALSE;
    uint8_t    byte  = (uint8_t)USART2->DR;           /* reading DR also clears RXNE */

    ring_buffer_put(&s_rx_ring, byte);                /* store the byte quickly      */
    vTaskNotifyGiveFromISR(s_rx_task, &woken);        /* wake the processing task    */
    portYIELD_FROM_ISR(woken);                        /* switch to it on ISR exit if it's higher priority */
}
```

### Q113. Why should an ISR be kept short?

> "Because while an ISR runs:
>
> - **Lower and equal-priority interrupts can't run**, so their latency grows, and they can even miss events, like UART bytes overrunning.
> - **No task can run**, so the RTOS's timing gets worse.
> - You **can't block** or wait, so long operations like I2C transfers or `printf` don't belong there.
>
> So the ISR just captures the event and hands it to a task."

### Q114. Which FreeRTOS APIs can be used from an ISR?

> "Only the APIs that end in **`FromISR`**, for example `xQueueSendFromISR()`, `xQueueReceiveFromISR()`, `xSemaphoreGiveFromISR()`, `vTaskNotifyGiveFromISR()`, `xTaskNotifyFromISR()`, `xEventGroupSetBitsFromISR()`, `xTimerStartFromISR()` and `xStreamBufferSendFromISR()`. Plus `portYIELD_FROM_ISR()` and `taskENTER_CRITICAL_FROM_ISR()`.
>
> The normal APIs must never be called from an ISR, because they may block or switch context directly. Mutexes can't be used from ISRs at all."

### Q115. What is DMA?

> "DMA, **Direct Memory Access**, is a hardware controller that **moves data by itself**, between a peripheral and memory, or memory to memory, without the CPU copying each byte. The CPU just configures the transfer (source, destination, length) and starts it. Then it's free to do other work, and the DMA raises an interrupt when it's done.
>
> For example, a UART receiving at 1 Mbaud would interrupt the CPU 100,000 times a second without DMA. With DMA, the CPU gets one interrupt per buffer."

### Q116. How does DMA work internally?

> "A DMA controller has several **channels** or **streams**. Each one has registers for the source address, the destination address, the number of items, the data size, and whether each address increments.
>
> 1. A peripheral, like the ADC, raises a **DMA request** when it has data.
> 2. The DMA controller becomes **bus master** for one transfer, reads from the source and writes to the destination.
> 3. It updates the addresses and decrements the counter.
> 4. When the counter reaches **half** and then **zero**, it raises the half-transfer and transfer-complete interrupts. In **circular mode**, it reloads automatically and starts again."

### Q117. Is DMA another CPU?

> "No. It doesn't execute instructions and has no program. It's a simple **hardware state machine** that copies data according to the registers the CPU configured. It's a second **bus master**, though, so it competes with the CPU for the bus and memory. The bus matrix arbitrates between them."

### Q118. How does a DMA controller obtain access to memory and peripherals?

> "Through the MCU's **bus matrix**, for example the AHB matrix on STM32. The DMA controller is a **bus master**, like the CPU. When it needs to transfer, it requests the bus, and the **arbiter** grants access according to priority, usually round-robin. The CPU and DMA can access different slaves at the same time, like the CPU in flash and the DMA in SRAM. If they want the same slave, one waits a few cycles.
>
> That's why the memory layout matters: putting DMA buffers in a different SRAM bank than the CPU's stack can reduce contention."

### Q119. How does DMA notify the CPU that a transfer is complete?

> "With **interrupts**. The DMA sets a **transfer-complete** flag (and a **half-transfer** flag in the middle, and an **error** flag if something goes wrong), and if those interrupts are enabled, the NVIC raises the DMA channel's interrupt. In the ISR I clear the flag and signal a task. Alternatively, the CPU can poll the flag or the remaining-count register, but the interrupt is the normal way."

### Q120. Should you use ADC polling or DMA, and why?

> "It depends on the **sample rate** and **how many channels**:
>
> - **Polling** is fine for a **slow, occasional** reading, like a battery voltage once a second. Simple code, no setup.
> - **DMA** is best for **continuous or multi-channel** sampling, like audio, motor current or a 1 kHz sensor array. The ADC is triggered by a timer, and the DMA fills a buffer without any CPU work per sample.
>
> If I sampled at 10 kHz with polling or an interrupt per sample, the CPU would spend a large share of its time just collecting samples."

### Q121. When is polling more appropriate than DMA?

> "Polling is better when:
>
> - the data is **small and rare**, like reading one register at start-up, or a battery reading every few seconds;
> - the **wait is very short**, shorter than setting up a DMA transfer and taking its interrupt;
> - the code runs **before the system is fully up**, like in a bootloader;
> - or simplicity matters more than CPU time."

### Q122. How would you implement continuous ADC acquisition using DMA?

> "I use a **timer** to trigger the ADC at an exact sample rate, the **DMA in circular mode** to write into a buffer, and the **half-transfer and transfer-complete interrupts** for double buffering: while the DMA fills the second half, my task processes the first half, and the other way round. That way no sample is ever lost, and the CPU only works once per half-buffer."

```c
#define ADC_BUF_LEN   (512U)                     /* two halves of 256 samples */
static uint16_t s_adc_buf[ADC_BUF_LEN];          /* DMA writes here continuously */

void adc_start(void)
{
    /* TIM3 TRGO triggers one conversion every 100 µs (10 kHz) - set up in CubeMX/init code */
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)s_adc_buf, ADC_BUF_LEN);   /* DMA in circular mode */
    HAL_TIM_Base_Start(&htim3);                                       /* start the sample clock */
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)   /* first half is full */
{
    (void)hadc;
    notify_processing_task(&s_adc_buf[0], ADC_BUF_LEN / 2U);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)       /* second half is full */
{
    (void)hadc;
    notify_processing_task(&s_adc_buf[ADC_BUF_LEN / 2U], ADC_BUF_LEN / 2U);
}
```

On a Cortex-M7 with data cache, the buffer must be in non-cacheable memory, or each half must be invalidated before it's read.

### Q123. What is the difference between SPI and I2C?

| | SPI | I2C |
| --- | --- | --- |
| Wires | 4: SCLK, MOSI, MISO, CS (+1 CS per device) | 2: SCL, SDA, for all devices |
| Speed | Tens of MHz | 100 kHz, 400 kHz, 1 MHz typically |
| Duplex | Full duplex | Half duplex |
| Device selection | Chip-select pin per device | 7-bit address in every transfer |
| Acknowledge | None | ACK/NACK on every byte |
| Drive | Push-pull | Open-drain with pull-ups |
| Distance | Short, on-board | Short, on-board |

> "SPI is faster and simpler, but costs pins. I2C needs only two wires for many devices and confirms each byte, but it's slower."

### Q124. Why might SPI be preferable to I2C?

> "When I need **speed or throughput**: displays, external flash, high-rate IMUs, fast ADCs. SPI runs at tens of MHz, full duplex, with no address and ACK overhead, and push-pull drivers give clean edges. It also has no address conflicts, and the protocol is simpler, so the driver is simpler too.
>
> The cost is more pins: one chip select per device."

### Q125. When would you choose I2C for a display?

> "When the display is **small and updates slowly**: a 16×2 character LCD with an I2C backpack, or a small 128×64 OLED showing text and status. The data is tiny, a few bytes per update, so 400 kHz is more than enough, and I save pins.
>
> For a colour TFT, or anything with graphics and frequent refresh, I'd use SPI or a parallel interface. A full 320×240 colour frame is about 150 KB, which would take several seconds over I2C."

### Q126. Would you still use I2C if the display is on a separate PCB?

> "I'd be careful. I2C was designed for **on-board** communication. Over a cable, the extra capacitance slows the edges, and noise can corrupt the open-drain lines. For a short cable, say 10 to 20 cm, with good grounding and proper pull-ups, at 100 kHz, it usually works.
>
> For a longer cable or a noisy environment, I'd add an **I2C bus buffer/extender** like the P82B715 or PCA9615 (differential I2C), or switch to SPI with series resistors and short traces, or to a robust link like **RS-485 or CAN** to a small MCU on the display board."

### Q127. When would you choose CAN or RS-485 instead of I2C/SPI for board-to-board communication?

> "When the boards are **far apart** (meters, not centimetres), in a **noisy** environment like motors, vehicles or industrial plants, or when **several boards** share the bus. Both use **differential signalling**, which rejects noise, and they work over tens or hundreds of meters.
>
> - **CAN**: multi-master, built-in arbitration, CRC, error handling and automatic retransmission. My choice for vehicles, drones and robotics.
> - **RS-485**: a simple physical layer for UART, up to 32+ nodes and 1,200 m, but the protocol (like Modbus) is up to me."

### Q128. How would you interface a screen using SPI or I2C?

> "1. Read the display controller's datasheet: the SSD1306, ST7735 or ILI9341, for example. It tells me the interface, the init sequence and the command set.
> 2. Wire it: SPI needs SCLK, MOSI, CS, plus a **D/C pin** (data or command) and **RESET**. I2C needs SDA and SCL, and the display's address.
> 3. Write a small driver: hardware reset, send the **init command sequence**, then functions to set the drawing window and send pixel data.
> 4. Keep a **frame buffer** in RAM, draw into it, and send the changed area. For large screens, send the frame buffer with **DMA**.
> 5. On top, use a graphics library like LVGL or u8g2 for text and widgets."

```c
/* Sending a command vs data on an SPI display: the D/C pin tells the controller which one it is */
static void lcd_write_cmd(uint8_t cmd)
{
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);   /* D/C low  = command */
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);   /* select the display */
    (void)HAL_SPI_Transmit(&hspi1, &cmd, 1U, 10U);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

static void lcd_write_data(const uint8_t *data, uint16_t len)
{
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);     /* D/C high = data    */
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    (void)HAL_SPI_Transmit(&hspi1, (uint8_t *)data, len, 100U);        /* use DMA for big frames */
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
```

### Q129. What is a watchdog timer, and why is it important?

> "A watchdog is a hardware counter that **resets the MCU if the software stops refreshing it** in time. It's the last line of defence: if the firmware hangs in an endless loop, deadlocks, or gets corrupted, the watchdog brings the device back by itself, without anyone pressing a button. For a device in the field, that's essential.
>
> STM32 has two: the **IWDG**, independent, on its own clock, which works even if the main clock fails; and the **WWDG**, window, which also resets if the refresh is too **early**, catching code that runs too fast or skips work."

### Q130. What happens if the watchdog is not refreshed?

> "When the counter reaches its timeout, the watchdog **resets the MCU**, just like a power-on reset, except the reset-cause register shows a watchdog reset (`RCC_CSR_IWDGRSTF` on STM32). At boot, I check that flag, log it, and count it, so in the field we can see that the device recovered from a hang.
>
> A good design refreshes the watchdog only when **all important tasks** have checked in, not from a timer interrupt. Otherwise the watchdog keeps getting refreshed while the main task is stuck."

```c
/* Supervisor task: refresh only if every task reported alive in this period */
#define ALL_TASKS_ALIVE   (TASK_COMM_BIT | TASK_SENSOR_BIT | TASK_CONTROL_BIT)

void watchdog_task(void *arg)
{
    for (;;)
    {
        EventBits_t bits = xEventGroupWaitBits(s_alive, ALL_TASKS_ALIVE,
                                               pdTRUE, pdTRUE, pdMS_TO_TICKS(500));
        if ((bits & ALL_TASKS_ALIVE) == ALL_TASKS_ALIVE)
        {
            HAL_IWDG_Refresh(&hiwdg);         /* everyone is alive: kick the dog */
        }
        /* else: don't refresh, and the IWDG resets the MCU */
    }
}
```

---

## 5. CAN, Ethernet and communication protocols

### Q131. What is CAN FD?

> "CAN FD, **CAN with Flexible Data-rate**, is the newer version of the CAN bus, from Bosch, standardized in ISO 11898-1:2015. It keeps the same arbitration and wiring as classic CAN, but adds two things: a **payload of up to 64 bytes** instead of 8, and a **faster bit rate for the data phase**, typically 2 to 5 Mbit/s, instead of a maximum of 1 Mbit/s. It's widely used in modern cars, for ECU flashing and for sensors that send more data."

### Q132. What does Flexible Data Rate mean in CAN FD?

> "It means **one frame uses two bit rates**. The **arbitration phase** (the ID) runs at the normal nominal rate, for example 500 kbit/s, because all nodes must be able to arbitrate over the whole bus length. After arbitration, only one node is transmitting, so the **data phase** switches to a much **higher rate**, for example 2 or 5 Mbit/s. The **BRS** (bit rate switch) bit in the frame tells everyone when to switch. At the end, for the ACK, it goes back to the slow rate."

### Q133. What is the difference between Classical CAN and CAN FD?

| | Classical CAN | CAN FD |
| --- | --- | --- |
| Payload | 0-8 bytes | 0-8, 12, 16, 20, 24, 32, 48, 64 bytes |
| Bit rate | One rate, max 1 Mbit/s | Nominal rate + faster data rate (up to ~8 Mbit/s) |
| New control bits | — | FDF (FD format), BRS (bit-rate switch), ESI (error state) |
| CRC | 15-bit | 17-bit (≤16 bytes) or 21-bit (>16 bytes) |
| Remote frames | Yes | No |
| Compatibility | — | An FD controller can talk classic CAN; a classic-only node sees FD frames as errors |

### Q134. What is a CAN data frame?

> "A data frame is the normal CAN message that **carries data**. It has an **identifier**, which says what the data is and also sets the priority, then up to 8 bytes of data (64 in CAN FD), a CRC, and an acknowledge slot. CAN is message-based: frames have no destination address; every node receives every frame, and each node's filter decides whether it cares about that ID."

### Q135. What are the fields of a CAN data frame?

| Field | Bits | Purpose |
| --- | --- | --- |
| SOF | 1 | Start of frame (dominant bit), synchronizes all nodes |
| Identifier | 11 (standard) or 29 (extended) | Message ID and priority |
| RTR | 1 | Data frame (0) or remote request (1) |
| IDE, r0 | 1 + 1 | Standard or extended ID; reserved |
| DLC | 4 | Data length code: 0-8 bytes |
| Data | 0-64 | The payload |
| CRC | 15 + delimiter | Error detection |
| ACK | 1 + delimiter | Any receiver that got it correctly pulls this bit dominant |
| EOF | 7 | End of frame (recessive bits) |
| IFS | 3 | Inter-frame space |

### Q136. What is the purpose of the CAN identifier?

> "The identifier does two jobs:
>
> - It **identifies the content**: ID 0x120 might mean 'engine speed', and every node that needs engine speed filters for 0x120.
> - It sets the **priority** during arbitration: a **lower ID wins**, because a dominant 0 overwrites a recessive 1 on the bus. Each node compares what it sent with what it reads, and the node that sent a 1 but reads a 0 stops transmitting. So the most important messages get the lowest IDs, and the bus never has collisions that destroy data."

### Q137. What is the purpose of CRC and ACK in CAN?

> "**CRC** protects the frame's content: the sender calculates a 15-bit CRC over the frame, and every receiver recalculates it. If it doesn't match, the receiver sends an **error frame**, and the sender retransmits automatically.
>
> **ACK**: the sender transmits the ACK slot as recessive, and **any node** that received the frame correctly overwrites it with a dominant bit. If nobody does, the sender knows that no node got the frame, for example it's alone on the bus, and treats it as an error and retries. Note that ACK only means 'at least one node received it', not that the intended node got it."

### Q138. Explain Ethernet from the physical layer to the application layer.

> "I'll go up the stack, using the example of my device sending a sensor reading to a server over TCP:
>
> 1. **Physical (PHY chip, cable)**: turns bits into electrical signals on twisted-pair copper, at 10/100/1000 Mbit/s, and handles link negotiation.
> 2. **Data link (MAC in the MCU)**: builds **Ethernet frames** with destination and source MAC addresses, an EtherType, the payload and a CRC.
> 3. **Network (IP)**: adds the **IP header** with source and destination IP addresses, so the packet can be routed across networks. ARP maps IP addresses to MAC addresses.
> 4. **Transport (TCP or UDP)**: adds **ports** to reach the right application. TCP adds sequence numbers, acknowledgments and retransmission for reliable delivery.
> 5. **Application**: the protocol my firmware speaks, like HTTP, MQTT, Modbus TCP, or my own message format.
>
> On an MCU, a stack like **lwIP** implements layers 3 and 4, the MAC driver handles layer 2, and the PHY is a separate chip connected over RMII."

```text
Application:  MQTT message "temp=25.1"
Transport:    [TCP header: ports, seq, ack] + message
Network:      [IP header: src/dst IP] + TCP segment
Data link:    [Ethernet header: dst/src MAC, type] + IP packet + [CRC]
Physical:     electrical signals on the cable
```

### Q139. What are the roles of the Ethernet PHY and MAC?

> "The **MAC** (Media Access Controller) is usually **inside the MCU**. It works with **frames**: it adds the preamble and CRC when sending, checks the CRC and filters by MAC address when receiving, and moves the frames to and from RAM with its own DMA.
>
> The **PHY** is usually a **separate chip** (like the LAN8742 or DP83848). It works with **signals**: it converts the MAC's digital data into the analog signals on the cable and back, and does auto-negotiation of speed and duplex. The MAC and PHY connect through **MII or RMII** for data and **MDIO/MDC** for the PHY's configuration registers, like link status."

### Q140. What are Ethernet frames and IP packets?

> "An **Ethernet frame** is the unit at layer 2, on one local network: destination MAC (6 bytes), source MAC (6), EtherType (2, for example 0x0800 for IPv4), a payload of 46 to 1500 bytes, and a 4-byte CRC. It only travels as far as the next switch or router.
>
> An **IP packet** is the unit at layer 3, and it's carried **inside** the Ethernet frame's payload. It has source and destination IP addresses, a TTL and a protocol field (6 for TCP, 17 for UDP), so routers can forward it across many networks to the final destination. At every router, the Ethernet frame is replaced, but the IP packet stays the same."

### Q141. What is the difference between TCP and UDP?

| | TCP | UDP |
| --- | --- | --- |
| Connection | Connection-oriented (3-way handshake) | Connectionless |
| Reliability | Guaranteed, in order, retransmits lost data | No guarantee, no ordering |
| Flow / congestion control | Yes | No |
| Overhead | 20-byte header, ACKs | 8-byte header |
| Latency | Higher | Lower |
| Use | Firmware updates, file transfer, MQTT, HTTP | Live audio/video, DNS, sensor streams, discovery |

> "TCP when every byte must arrive, UDP when speed matters more and the occasional loss is acceptable."

### Q142. Why would you use TCP/IP for embedded data acquisition?

> "Because it's **standard and everywhere**: any PC, SBC or cloud server can receive the data without special hardware. Ethernet gives **high bandwidth**, far more than UART or CAN, and **long cable runs** (100 m per segment). TCP takes care of reliable, in-order delivery, so I don't have to write my own retransmission. And it scales: many devices on one switch, each with its own IP address, reachable remotely for diagnostics and updates.
>
> If the data is a live stream where losing a packet is acceptable, I'd use UDP on the same Ethernet link instead."

### Q143. How did Ethernet/TCP-IP work in your railway project?

*(Adapt this to your real project.)*

> "In the railway project, the embedded unit collected data from on-board sensors and sent it over Ethernet to the main control computer. On the MCU side we used the **STM32's Ethernet MAC with an external PHY over RMII**, and **lwIP on FreeRTOS** for the TCP/IP stack.
>
> The unit worked as a **TCP server**: the control computer connected to it, and we sent fixed-format binary messages with a header, a message ID, a sequence number, a length, the data and a CRC. The sequence number let the receiver detect gaps after a reconnection. We had a **heartbeat** every second, and if the link or the connection dropped, the firmware buffered data in RAM and the client reconnected automatically. I worked on the message layer and on the reconnection and buffering logic."

### Q144. How would you transfer high-speed sensor or camera data to an SBC?

> "First I calculate the data rate. For example, a 640×480 camera, 8-bit, 30 fps is about 9 MB/s, which rules out UART and I2C.
>
> - For **very high rates** (camera), I'd use the interface the SBC is built for: **MIPI CSI-2** for a camera, or **USB 2.0 High Speed** (about 35-40 MB/s in practice), or **Ethernet**.
> - For **sensor data** of a few MB/s: **SPI** at 20-50 MHz with DMA on both ends, or **USB** with the MCU as a bulk device, or **Ethernet with UDP** for a continuous stream.
>
> On the MCU side I use **DMA and double buffering**, and packets with a sequence number and CRC, so the SBC can detect loss. I also leave 30-50 % margin on the bandwidth."

### Q145. What happens if the network connection drops during data transfer?

> "With TCP, the stack retries for a while, and then the socket returns an error or a timeout. My firmware must handle that properly:
>
> 1. **Detect** it quickly: socket errors, a heartbeat or TCP keep-alive, and the PHY's link-down status.
> 2. **Don't lose data**: keep writing new data into a buffer, in RAM or flash, with a bounded size and a clear policy when it's full.
> 3. **Reconnect** automatically, with exponential back-off, so I don't flood the network.
> 4. **Resume**: after reconnecting, send the buffered data first, with sequence numbers, so the server can detect gaps and drop duplicates.
>
> And the application must never block forever on a dead socket: every send and receive has a timeout."

### Q146. What is the difference between UART, SPI, I2C and Ethernet?

| | UART | SPI | I2C | Ethernet |
| --- | --- | --- | --- | --- |
| Wires | 2 (TX, RX) + GND | 4 + CS per device | 2 | 2 twisted pairs (or 4) |
| Clock | None: both sides agree on the baud rate | Shared clock from the master | Shared clock from the master | Embedded in the signal |
| Topology | Point to point | One master, many slaves | Multi-master, many slaves | Switched network |
| Speed | Up to a few Mbit/s | Tens of MHz | 100 kHz - 1 MHz | 10/100/1000 Mbit/s |
| Distance | Meters (RS-232/485 for more) | Centimetres | Centimetres | 100 m per segment |
| Typical use | Debug console, GPS, modems | Flash, displays, fast sensors | Sensors, EEPROM, PMIC | Networking, cloud, high data rates |

### Q147. What is USB?

> "USB, **Universal Serial Bus**, is a standard for connecting devices to a **host**, like a PC. It's **host-controlled**: the host powers the bus, discovers each device through **enumeration**, and starts every transfer. It also supplies power (5 V, 500 mA on USB 2.0, much more with USB-PD).
>
> Devices describe themselves with **descriptors**, and use standard **classes** like HID, CDC, mass storage or audio, so the OS already has the drivers. On an MCU I usually implement a USB **device**, like a virtual COM port."

### Q148. What is the difference between USB 2.0 and USB 3.0?

| | USB 2.0 | USB 3.0 (USB 3.2 Gen 1) |
| --- | --- | --- |
| Max speed | 480 Mbit/s (High Speed) | 5 Gbit/s (SuperSpeed) |
| Data lines | One pair (D+/D−), half duplex | Two extra pairs added, full duplex |
| Power | 500 mA | 900 mA |
| Host behaviour | Polling | Asynchronous notifications, less polling |
| Compatibility | — | Backward compatible with USB 2.0 |

> "Most MCUs only have USB 2.0, Full Speed (12 Mbit/s) built in. High Speed needs an external ULPI PHY, and USB 3 is mostly found on application processors."

### Q149. How would you design a USB CDC device?

> "On STM32, I'd:
>
> 1. Set the **48 MHz USB clock** accurately: from the PLL with an HSE crystal, or HSI48 with clock recovery.
> 2. Add the **USB device middleware** with the **CDC class** in CubeMX. That generates the device, configuration, interface and endpoint descriptors: one interrupt IN endpoint for notifications and two bulk endpoints for data.
> 3. Set my **VID/PID** and the product strings in the descriptors.
> 4. Implement the callbacks: `CDC_Receive_FS()` puts incoming data into a ring buffer and signals a task, and transmit uses `CDC_Transmit_FS()`, which must wait until the previous transfer is finished.
> 5. Handle the control requests like `SET_LINE_CODING` (the baud rate is just stored; it doesn't matter for a virtual port) and `SET_CONTROL_LINE_STATE`, which tells me when a terminal opens the port (DTR).
>
> Windows 10 and Linux load the standard driver, and the device appears as COMx or /dev/ttyACM0."

### Q150. What is USB CDC ACM?

> "**CDC** is the USB **Communications Device Class**, and **ACM**, the **Abstract Control Model**, is the CDC subclass for a **virtual serial port**, originally for modems. The device appears on the PC as a normal COM port, or `/dev/ttyACM0` on Linux, using the OS's built-in driver. So any terminal program can talk to my firmware, at full USB speed, with no USB-to-UART chip."

### Q151. What are USB control, bulk and interrupt endpoints?

> "- **Control** (always **endpoint 0**): for setup and commands. The host uses it for enumeration, reading descriptors and class requests. Reliable, small packets.
> - **Bulk**: for **large data**, where every byte must arrive, but the timing doesn't matter. It uses the bandwidth left over. Mass storage and CDC data use bulk.
> - **Interrupt**: for **small data with guaranteed latency**. The host polls it at a fixed interval, like every 10 ms. Keyboards, mice and CDC notifications use it.
>
> There's also isochronous, for audio and video, with fixed bandwidth and no retries."

### Q152. What are USB device, configuration, interface and endpoint descriptors?

| Descriptor | Describes | Key fields |
| --- | --- | --- |
| **Device** | The whole device (one per device) | VID, PID, USB version, class, max packet size of EP0, number of configurations |
| **Configuration** | One way the device can operate | Total length, number of interfaces, power needed (bMaxPower), self/bus powered |
| **Interface** | One function inside that configuration | Class/subclass/protocol (e.g. CDC, HID), number of endpoints |
| **Endpoint** | One data pipe | Address and direction (IN/OUT), transfer type, max packet size, polling interval |

> "They're nested: a device has configurations, a configuration has interfaces, and an interface has endpoints. The host reads them during enumeration to know what the device is and which driver to load."

---

## 6. USB Type-C Power Delivery and battery management

### Q153. What is your experience with USB Type-C Power Delivery?

*(Adapt this to your own project.)*

> "I worked on a battery-powered product that charges over USB Type-C with Power Delivery. The device acted as a **sink**. A dedicated **USB-PD controller IC** handled the low-level CC-line protocol, and our MCU talked to it over **I2C**, with an interrupt line.
>
> My part was the firmware state machine: handling attach and detach, reading the charger's **Source Capabilities**, choosing the best PDO for our battery (for example 9 V at 2 A for fast charging, or 5 V as fallback), sending the **Request**, waiting for **Accept** and **PS_RDY**, and then configuring the **charger IC** with the right input current limit and charge current. I also handled the error cases: rejects, timeouts, hard resets, and chargers that don't support PD at all."

### Q154. How does USB-PD negotiation work?

> "It's a message exchange on the **CC line**, after the Type-C attach:
>
> 1. **Attach**: the source sees the sink's Rd pull-down on CC and turns on **VBUS at 5 V**.
> 2. The source sends **Source_Capabilities**: the list of voltages and currents it can provide (its PDOs).
> 3. The sink picks one and sends a **Request** for that PDO, with the current it needs.
> 4. The source checks it and replies **Accept** (or **Reject**, or **Wait**).
> 5. The source changes VBUS to the new voltage, and when it's stable, sends **PS_RDY**.
> 6. Now the sink may draw the new power. Every message is acknowledged with **GoodCRC** at the protocol layer."

```text
Source                                  Sink
  | ---- VBUS 5 V on (after attach) ---->  |
  | ---- Source_Capabilities (PDOs) ----> |
  | <--- Request (PDO #2: 9 V, 2 A) ----- |
  | ---- Accept ------------------------> |
  |      (VBUS ramps 5 V -> 9 V)          |
  | ---- PS_RDY ------------------------> |   sink may now draw 9 V / 2 A
```

### Q155. What are Source Capabilities and Request messages?

> "**Source_Capabilities** is the message the **charger** sends to advertise what it can supply: a list of up to 7 **PDOs**, for example 5 V 3 A, 9 V 3 A, 15 V 3 A, 20 V 2.25 A.
>
> **Request** is the **sink's** answer: it says 'I want PDO number 2', together with the operating current and the maximum current it will draw. It also has flags, like 'capability mismatch' if none of the offered PDOs is good enough."

### Q156. What are PDOs?

> "PDO stands for **Power Data Object**. Each PDO is a 32-bit value describing one power option. The main types are:
>
> - **Fixed supply**: a fixed voltage and a maximum current, like 9 V at 3 A. Every source must offer 5 V as the first PDO.
> - **Variable** and **Battery**: a voltage range with a maximum current or power.
> - **APDO / PPS** (Programmable Power Supply): a voltage range the sink can adjust in 20 mV steps, used for direct fast charging.
>
> The firmware decodes each PDO's bit fields, for a fixed PDO: voltage in 50 mV units in bits 10-19, and current in 10 mA units in bits 0-9."

```c
/* Decode a Fixed Supply PDO (USB-PD 3.0) */
#define PDO_TYPE(pdo)         (((pdo) >> 30U) & 0x3UL)           /* 0 = fixed supply */
#define PDO_FIXED_MV(pdo)     ((((pdo) >> 10U) & 0x3FFUL) * 50UL) /* bits 10-19, 50 mV units */
#define PDO_FIXED_MA(pdo)     (((pdo) & 0x3FFUL) * 10UL)          /* bits 0-9, 10 mA units   */

/* Example: 0x0002D12C -> type 0, 180 * 50 mV = 9000 mV, 300 * 10 mA = 3000 mA */
```

### Q157. What happens during Accept and PS_RDY?

> "**Accept** means the source has agreed to my request, and it's about to change VBUS. At that point the sink must still be careful: the voltage is in transition, so the sink limits its current draw.
>
> The source then ramps VBUS to the new voltage, and when it's stable, it sends **PS_RDY**, 'power supply ready'. Only after PS_RDY does the sink start drawing the full new power. In my firmware, that's when I reconfigure the charger IC's input current limit and enable fast charging. If PS_RDY doesn't arrive within the timeout (about 500 ms, tPSTransition), that's an error, and the sink sends a **Hard Reset**."

### Q158. What are the CC pins, and what role do they play in USB-PD?

> "A Type-C connector has two **CC** (Configuration Channel) pins, CC1 and CC2. They do several jobs:
>
> - **Attach detection**: the source has pull-ups (Rp), the sink has pull-downs (Rd). When the voltage on CC changes, both sides know a cable is connected.
> - **Orientation**: only one CC pin is connected through the cable, which tells which way the plug is inserted, so the data lines can be switched.
> - **Current advertisement** without PD: the Rp value tells the sink whether it can draw default USB power, 1.5 A or 3 A at 5 V.
> - **PD communication**: the PD messages themselves are sent over the active CC line, using BMC encoding at 300 kbit/s.
>
> The other CC pin may become **VCONN**, to power an electronically marked cable."

### Q159. How does the MCU communicate with the USB-PD controller?

> "Usually over **I2C** (sometimes SPI), plus an **interrupt (ALERT) pin**. The PD controller handles the physical layer, BMC encoding, CRC and GoodCRC by itself, and many controllers implement the full policy engine in their own firmware.
>
> The MCU's job is: when the ALERT pin goes low, read the interrupt status registers over I2C, find out what happened (attach, new Source_Capabilities received, contract done, hard reset), read the relevant data, like the PDO list, and write commands like 'request PDO 2'. Some controllers follow the standard **TCPC (Type-C Port Controller)** register interface, and then the MCU runs the PD policy engine itself."

### Q160. What happens during a USB-PD Hard Reset?

> "A Hard Reset is the **last resort** when the PD protocol has failed: a timeout, too many retries, or an invalid message. Either side sends a special Hard Reset signal on CC. Then:
>
> 1. Both sides **reset their PD protocol state** completely. Any power contract is gone.
> 2. The source **drops VBUS** to 0 V (vSafe0V), waits, and then restores **5 V** (vSafe5V).
> 3. Negotiation **starts again from the beginning**, with Source_Capabilities.
>
> In my firmware, a hard reset means: immediately reduce the charge current to the 5 V default, reset my state machine to 'attached, waiting for capabilities', and count the event. If it repeats, I stay at 5 V instead of looping forever."

### Q161. How do you handle negotiation failures with different chargers?

> "Chargers don't all behave the same, so I make the firmware **tolerant**:
>
> - Always have a **safe fallback**: if negotiation fails, charge at 5 V with the current the Type-C Rp advertises, so the device still charges.
> - **Choose PDOs sensibly**: only request what the charger offers, and stay within its current limit.
> - **Timeouts and retries** for every step, with a limit, then fall back to 5 V.
> - **Log** every message and state change, with the charger's PDOs, so I can analyse failures from field units.
> - **Test with many chargers**: Apple, Samsung, Anker, laptop chargers, cheap non-PD ones, and use a **PD analyzer** like a Twinkie or Total Phase sniffer to capture the CC traffic when one fails."

### Q162. How do you handle multiple attach/detach interrupts?

> "When a cable is plugged in, the contacts **bounce**, so the PD controller may raise several attach/detach interrupts within milliseconds. I handle that by:
>
> - Keeping the **ISR minimal**: it only notifies a task, it never runs the state machine.
> - In the task, **reading the current status register** instead of trusting each interrupt event: what matters is the state now, not how many edges happened.
> - **Debouncing**: the Type-C spec requires tCCDebounce (100-200 ms). I wait until the CC state has been stable for that time before acting on attach or detach.
> - Clearing the interrupt flags after reading, so no event is lost."

### Q163. How do you prevent repeated state transitions caused by multiple interrupts?

> "I make the state machine **event-driven and idempotent**:
>
> - All events go into **one queue**, and **one task** processes them in order. There's no state change in ISRs, so there are no races.
> - Each event is only valid in certain states. For example, 'attach' while I'm already in ATTACHED is ignored, and a 'contract done' that arrives in DETACHED is dropped as stale.
> - I compare the **new state with the current state**, and only run the entry actions, like reconfiguring the charger, when it really changes.
> - A debounce timer filters the burst of attach/detach events."

```c
typedef enum { PD_DETACHED, PD_ATTACHED, PD_NEGOTIATING, PD_CONTRACT } pd_state_t;

static pd_state_t s_state = PD_DETACHED;

static void pd_handle_event(pd_event_t ev)            /* called only from the PD task */
{
    switch (s_state)
    {
        case PD_DETACHED:
            if (ev == EV_ATTACH_STABLE)                /* only after the debounce time */
            {
                s_state = PD_ATTACHED;
                charger_set_input_limit_ma(500U);      /* safe default until a contract exists */
            }
            break;                                     /* any other event here is ignored */

        case PD_CONTRACT:
            if (ev == EV_DETACH_STABLE)
            {
                s_state = PD_DETACHED;
                charger_disable();
            }
            else if (ev == EV_HARD_RESET)
            {
                s_state = PD_ATTACHED;                 /* back to 5 V, renegotiate */
                charger_set_input_limit_ma(500U);
            }
            else
            {
                /* repeated attach or stale events: no change */
            }
            break;

        default:
            /* PD_ATTACHED and PD_NEGOTIATING handled the same way: check the event, ignore the rest */
            break;
    }
}
```

### Q164. What happens if a requested power profile is rejected?

> "If the source sends **Reject**, the current contract stays as it was (or 5 V default if there was none). My firmware then:
>
> 1. Keeps charging at the **current safe level**.
> 2. Tries a **lower PDO**, for example 9 V at a lower current, or 5 V.
> 3. If the source sends **Wait**, retries after the specified time, a limited number of times.
>
> And I log it, because a reject often means the sink asked for more current than the PDO allows, which is a firmware bug."

### Q165. How do you handle timeout, detach and re-attach events?

> "- **Timeout** (no Source_Capabilities, no Accept, no PS_RDY in time): retry a limited number of times, then send a soft or hard reset, and finally fall back to 5 V charging.
> - **Detach**: immediately **stop charging**, disable the charger IC's input, cancel all PD timers, and reset the state machine. Any half-finished negotiation is dropped.
> - **Re-attach**: treated as a completely **new** connection, starting from debounce, with no assumptions from the previous charger, because it could be a different charger."

### Q166. What challenges did you face during USB-PD implementation?

*(Adapt this to your own experience.)*

> "A few real ones:
>
> - **Chargers that behave differently**: some sent Source_Capabilities late, or several times, or needed a retry. I made the state machine tolerant and added fallbacks.
> - **Interrupt bursts** on attach, which caused repeated state transitions until I moved all logic into one task with debouncing.
> - **Timing**: some responses must be sent within tens of milliseconds, so the PD task needed a high priority and the I2C accesses had to be fast.
> - **Coordinating with the charger IC**: if I raised the charge current before PS_RDY, the charger could overload and the source would hard-reset. The order of steps matters.
> - **Debugging**: without a PD analyzer, it's guesswork. Capturing the CC traffic showed exactly which message was wrong."

### Q167. What is a PMIC?

> "A PMIC, **Power Management IC**, is a chip that combines several power functions in one package: multiple **voltage regulators** (buck converters and LDOs) for the different rails, **power sequencing** (which rail turns on first), often a **battery charger**, and sometimes supervisors, a watchdog, an RTC or ADC channels. The processor configures it over **I2C** or SPI. They're common with application processors, which need many rails in a precise order."

### Q168. What is a battery fuel-gauge IC?

> "A fuel gauge is an IC that measures the battery and **calculates how much charge is left**: the **State of Charge** in %, the remaining capacity in mAh, the time to empty, and the battery health. It measures the voltage, the current (through a small sense resistor), and the temperature continuously, and runs an algorithm with a model of the battery. The MCU just reads the results over I2C. Examples are the TI BQ27xxx and the Maxim MAX17048."

### Q169. What is State of Charge (SoC)?

> "SoC is the **remaining charge as a percentage of the full capacity**: 100 % is full and 0 % is empty. For example, a 3000 mAh battery with 1500 mAh left is at 50 % SoC. It's the battery equivalent of a fuel level, and it's what the user sees as the battery percentage."

### Q170. How does a fuel-gauge IC calculate or provide SoC?

> "It combines two methods:
>
> - **Coulomb counting**: it integrates the current over time. Charge in adds, charge out subtracts. It's accurate in the short term, but small errors accumulate.
> - **Voltage-based estimation**: when the battery is resting, the open-circuit voltage maps to an SoC through a known curve for that chemistry. It corrects the drift, but only works when the current is low.
>
> Advanced gauges, like TI's Impedance Track or Maxim's ModelGauge, also model the battery's internal resistance, temperature and ageing. The MCU just reads the SoC register over I2C. The gauge usually needs to be configured for the specific battery: its capacity, chemistry and termination settings."

### Q171. What is the difference between instantaneous current and SoC?

> "**Instantaneous current** is what flows **right now**, in mA: like the speedometer in a car. It changes all the time, depending on the load.
>
> **SoC** is how much charge is **left in the tank**, in %. It changes slowly.
>
> They're related: SoC changes by the integral of the current over time. For example, a 3000 mAh battery discharging at 300 mA loses about 10 % SoC per hour."

### Q172. How do you interpret negative battery-current values?

> "It depends on the sign convention of the gauge, which I check in the datasheet. Most fuel gauges, like the TI BQ27 series, report **positive current while charging** and **negative while discharging**. So −250 mA means the battery is supplying 250 mA to the system.
>
> The register is usually a **signed 16-bit** value, so I must read it as `int16_t`, not `uint16_t`. Otherwise −250 shows up as 65286."

```c
uint8_t raw[2];
fuel_gauge_read(REG_AVG_CURRENT, raw, 2U);                     /* little-endian, 2 bytes */
int16_t current_ma = (int16_t)((uint16_t)raw[0] | ((uint16_t)raw[1] << 8U));   /* signed! */

if (current_ma < 0)
{
    /* discharging: the battery supplies -current_ma mA */
}
```

### Q173. How do you configure the charging voltage and current?

> "Through the **charger IC's registers**, over I2C, based on the battery datasheet. For a typical single-cell Li-ion:
>
> - **Charge voltage**: 4.20 V (or 4.35 V for a high-voltage cell, never more than the datasheet says).
> - **Fast-charge current**: usually 0.5C to 1C. For a 2000 mAh cell, 1 A to 2 A.
> - **Pre-charge current** for a deeply discharged cell, around 0.1C, and **termination current**.
> - **Input current limit**: set from the USB-PD contract, so we never draw more than the charger offers.
> - **Temperature limits** (JEITA): reduce or stop charging when cold or hot.
>
> I configure safe defaults at boot, and only raise the current after a PD contract is established."

### Q174. What are termination voltage and termination current?

> "Li-ion charging has two phases: **constant current (CC)**, then **constant voltage (CV)**.
>
> - **Termination (charge) voltage** is the **maximum** cell voltage, typically 4.2 V. When the cell reaches it, the charger switches from CC to CV and holds the voltage there.
> - **Termination current**: during CV, the current slowly drops. When it falls below the termination current, typically **C/10 or C/20** (100 to 200 mA for a 2000 mAh cell), the battery is considered **full**, and the charger stops."

### Q175. How does the MCU coordinate the USB-PD controller and charging ICs?

> "The MCU sits in the middle and makes sure the steps happen in the **right order**:
>
> 1. **Attach**: the PD controller reports a source. The MCU sets the charger's input limit to a safe 5 V default.
> 2. **Negotiation**: the PD controller and source agree on a contract; the MCU waits for PS_RDY.
> 3. **Contract done**: the MCU reads the new voltage and current, and programs the charger's **input current limit** to match, then enables the higher **charge current**.
> 4. **Monitoring**: the MCU reads the fuel gauge and the charger status, and reduces current if the temperature is out of range.
> 5. **Detach or hard reset**: the MCU immediately drops back to safe settings or disables charging.
>
> The key rule: **never draw more than the contract allows**, and never raise the current before PS_RDY."

### Q176. How do normal charging and fast charging differ in your implementation?

*(Adapt this to your own project.)*

> "**Normal charging** used the default 5 V, with the input limited to 500 mA to 1.5 A depending on what the Type-C source advertised. The charge current was limited accordingly, so a full charge took several hours.
>
> **Fast charging** was enabled when the PD negotiation gave us a **9 V** contract. Then I raised the charger's input current limit and the charge current, up to 1C, so the battery reached about 80 % in under an hour. Fast charging was only allowed within the temperature window: between 10 °C and 45 °C, otherwise the firmware fell back to a reduced current. Near the end, in the CV phase, the charger itself reduced the current."

### Q177. How do you monitor battery voltage, current and temperature?

> "I read them **periodically** from the fuel gauge over I2C: voltage, average current, temperature from the battery's NTC thermistor, SoC and status flags. A monitoring task runs every 1 to 5 seconds, more often while charging.
>
> I also use the **interrupts** from the charger and fuel gauge for urgent events, like a temperature fault or a low-SoC alarm. The firmware compares the readings against limits: over-temperature stops charging, low SoC triggers a warning and then a controlled shutdown, and all values are logged for diagnostics."

### Q178. What battery chemistry and capacity were used in your project?

*(Fill in your real values; example answer:)*

> "We used a **single-cell lithium-ion** (Li-ion) battery, **3.7 V nominal, 4.2 V maximum**, with a capacity of about **3000 mAh**, with a built-in protection circuit and an NTC thermistor for temperature. The charger was configured for 4.2 V charge voltage and up to 1.5 A charge current, which is 0.5C."

---

## 7. BLE and Bluetooth

### Q179. What is your experience with Bluetooth and BLE?

*(Adapt this to your own projects.)*

> "I've worked mainly with **BLE** on the device (peripheral) side. I designed and implemented **custom GATT services** for device control and status, handled advertising, connections, MTU exchange and notifications, and worked with a mobile app team to define the data format. I've also worked with Bluetooth controllers at the **HCI level**, and debugged connection problems with the nRF Connect app and a BLE sniffer."

### Q180. What work did you implement at the BLE application layer?

*(Adapt this to your own project.)*

> "At the application layer I:
>
> - Defined a **custom service** with characteristics for commands, configuration and live status data.
> - Implemented the **GATT callbacks**: handling writes from the phone (parsing and validating commands), and sending **notifications** with sensor data and status.
> - Set up **advertising** data (name, service UUID) and the advertising intervals for a good balance of discovery speed and power.
> - Handled **connection events**: connect, disconnect, MTU exchange, connection parameter updates, and pairing.
> - Made the data flow robust: queuing notifications when the stack's buffers were full, and resuming cleanly after a reconnect."

### Q181. What is the BLE architecture?

> "The BLE stack has two main parts, connected by **HCI**:
>
> - The **Controller**, close to the radio: the **PHY** (2.4 GHz radio, 40 channels) and the **Link Layer** (advertising, connections, timing, ACKs, channel hopping).
> - The **Host**: **L2CAP** (multiplexing and fragmentation), **ATT** (attribute read/write), **GATT** (services and characteristics), **SMP** (pairing and keys), and **GAP** (roles, advertising, connection setup).
>
> On top sits the **application**, which uses GAP and GATT."

```text
Application
GAP | GATT
ATT | SMP
L2CAP
---------- HCI ----------
Link Layer
PHY (radio)
```

### Q182. What are GAP and GATT?

> "**GAP** (Generic Access Profile) controls **how devices find and connect** to each other: roles (peripheral, central, broadcaster, observer), advertising and scanning, connection setup and parameters, and security modes.
>
> **GATT** (Generic Attribute Profile) controls **how data is exchanged after connecting**: it organizes data into **services** and **characteristics**, and defines read, write, notify and indicate.
>
> In short: GAP is about the connection, GATT is about the data."

### Q183. What is the difference between a profile, service and characteristic?

> "- A **profile** is a **specification of a use case**: it says which services a device must have and how they're used. For example, the Heart Rate Profile.
> - A **service** is a **group of related data** on the device, identified by a UUID. For example, the Heart Rate Service (0x180D).
> - A **characteristic** is **one value** inside a service, with properties saying what you can do with it. For example, Heart Rate Measurement (0x2A37), which supports notify.
>
> So a profile uses one or more services, and a service contains one or more characteristics."

### Q184. What are characteristic read, write, notify and indicate operations?

> "- **Read**: the client asks for the value, and the server responds with it. Example: reading the battery level.
> - **Write**: the client sends a new value. **Write with response** is acknowledged by the server; **write without response** isn't, so it's faster. Example: setting the sampling rate.
> - **Notify**: the **server pushes** the value to the client when it changes, without the client asking and **without acknowledgment**. Example: live sensor data.
> - **Indicate**: like notify, but the client must **confirm** each one. Example: an alarm that must not be lost.
>
> Notify and indicate only work after the client has enabled them in the CCCD descriptor."

### Q185. What is the difference between notification and indication?

| | Notification | Indication |
| --- | --- | --- |
| Acknowledged | No | Yes, the client sends a confirmation |
| Speed | Fast: several per connection event | Slow: one at a time, wait for the confirmation |
| Reliability | Link layer still retransmits, but no app-level confirmation | Confirmed at the ATT level |
| Enabled by | Writing 0x0001 to the CCCD | Writing 0x0002 to the CCCD |
| Use | Streaming sensor data | Important events, alarms |

### Q186. What is the difference between Central and Peripheral roles?

> "- The **peripheral** **advertises** and **waits** for a connection. It's usually the small, low-power device: a sensor, a watch, a fitness band.
> - The **central** **scans** for advertisements and **initiates** the connection. It's usually the phone or gateway, and it controls the connection timing.
>
> These are GAP roles. They're separate from the GATT roles: usually the peripheral is the GATT server, but not always."

### Q187. How does BLE advertising work?

> "The peripheral sends small **advertising packets** on the three advertising channels, **37, 38 and 39**, at a regular interval, like every 100 ms to a few seconds. Each packet carries up to **31 bytes** (legacy advertising): flags, the device name, service UUIDs, manufacturer data. A central that's scanning receives them, and can ask for a **scan response** with another 31 bytes, or send a **connection request**.
>
> A shorter interval means faster discovery but more power. I usually advertise fast for the first 30 seconds, then slow down."

### Q188. What happens during BLE connection establishment?

> "1. The peripheral **advertises** a connectable advertisement.
> 2. The central, which is scanning, receives it and sends a **CONNECT_IND** (connection request) on the same channel. It contains the connection parameters: interval, latency, supervision timeout, the channel map for hopping, and the access address.
> 3. Both devices now meet at the agreed times, in **connection events**, hopping across the 37 data channels.
> 4. Then usually: **MTU exchange**, **service discovery** by the central, maybe **pairing**, and enabling notifications in the CCCDs."

### Q189. What is the difference between pairing and bonding?

> "**Pairing** is the process of **creating the encryption keys** for the current connection: the devices exchange their capabilities, authenticate (for example with a passkey or numeric comparison), and generate keys. Then the link is encrypted.
>
> **Bonding** is **storing those keys** permanently, in flash, so the next time the same devices connect, they can encrypt immediately without pairing again.
>
> So: pairing without bonding means pairing again on every connection. Bonding means pairing once and remembering."

### Q190. What is BLE security?

> "BLE security is handled by **SMP**, the Security Manager Protocol, and covers:
>
> - **Encryption**: AES-128-CCM on the link, once the devices are paired.
> - **Authentication**: protection against man-in-the-middle attacks, depending on the pairing method. **Just Works** has no protection. **Passkey entry**, **numeric comparison** and **out-of-band** do.
> - **LE Secure Connections** (BLE 4.2+): uses Elliptic-Curve Diffie-Hellman for key exchange, much stronger than the old Legacy pairing.
> - **Privacy**: random, resolvable private addresses that change, so a device can't be tracked.
> - **Permissions** on characteristics, like 'encryption required to read'.
>
> On top of that, I often add application-level protection, like authenticating commands."

### Q191. What are ATT and L2CAP?

> "**L2CAP** (Logical Link Control and Adaptation Protocol) sits just above the link layer. It **multiplexes** several protocols over one connection using channel IDs: ATT on channel 0x0004, SMP on 0x0006, and LE signaling on 0x0005. It also **fragments** large packets.
>
> **ATT** (Attribute Protocol) is the simple client-server protocol that GATT is built on. The server holds a table of **attributes**, each with a 16-bit **handle**, a UUID type, a value and permissions. The client reads and writes them by handle, and the server can notify or indicate. GATT gives that table its structure of services and characteristics."

### Q192. What is HCI in Bluetooth?

> "HCI, the **Host Controller Interface**, is the **standard interface between the Bluetooth host stack and the controller**. It defines **commands** the host sends (like 'start advertising' or 'create connection'), **events** the controller sends back (like 'connection complete'), and **ACL data packets** that carry the actual data. Because it's standardized, any host stack can work with any controller."

### Q193. How does HCI connect the host stack and controller?

> "In a **two-chip** design, the host runs on the MCU or application processor, and the controller is a separate Bluetooth chip. HCI runs over a **physical transport** between them: usually **UART** (the H4 protocol, with a 1-byte packet type in front of each packet), or USB, or SPI.
>
> Every packet starts with a type: 0x01 for a command, 0x02 for ACL data, 0x04 for an event. For example, to start advertising, the host sends the HCI command `LE Set Advertising Enable`, and the controller answers with a `Command Complete` event.
>
> In a **single-chip** design, like an nRF52, HCI may just be function calls inside the same firmware."

```text
H4 over UART, command "LE Set Advertising Enable (on)":
01        packet type = command
0A 20     opcode 0x200A (OGF 0x08 LE, OCF 0x000A)
01        parameter length
01        advertising enable = 1
```

### Q194. Have you implemented the HCI layer directly?

*(Adapt this to your own experience.)*

> "Yes, at the transport level. I worked with a separate Bluetooth controller connected over **UART using H4**. I implemented the HCI transport driver: sending command packets, receiving and parsing events and ACL data, flow control with the controller's buffer counts, and the controller's start-up sequence, including **vendor-specific commands** to load the controller's patch or firmware and set the baud rate. The host stack above it then used HCI commands to advertise and connect."

### Q195. What is the difference between BLE and Bluetooth Classic?

| | Bluetooth Classic (BR/EDR) | BLE |
| --- | --- | --- |
| Purpose | Continuous streaming | Small, periodic data at low power |
| Data rate | 1-3 Mbit/s | 1 or 2 Mbit/s PHY, lower real throughput |
| Power | Higher | Very low: years on a coin cell |
| Connection setup | Slower (seconds) | Fast (milliseconds) |
| Channels | 79 × 1 MHz | 40 × 2 MHz |
| Data model | Profiles like A2DP, HFP, SPP over RFCOMM | GATT services and characteristics |
| Typical use | Audio headsets, speakers, car kits | Sensors, wearables, beacons, IoT |

### Q196. What are A2DP, AVRCP, HFP, RFCOMM and SPP?

> "These are Bluetooth **Classic** profiles and protocols:
>
> - **A2DP** (Advanced Audio Distribution Profile): high-quality **stereo audio streaming**, like music to headphones.
> - **AVRCP** (Audio/Video Remote Control Profile): **remote control** of media: play, pause, next track, volume.
> - **HFP** (Hands-Free Profile): **phone calls** through a headset or car kit, including call control and voice.
> - **RFCOMM**: a protocol that **emulates serial ports** (RS-232) over Bluetooth. Other profiles use it.
> - **SPP** (Serial Port Profile): a **virtual serial cable** over RFCOMM, used to send raw data between devices."

### Q197. What is the BLE connection interval?

> "The connection interval is **how often the two connected devices meet** to exchange data. It can be set from **7.5 ms to 4 s**, in 1.25 ms steps. At every interval, there's a connection event, where the central and peripheral exchange packets, and then both radios sleep until the next one.
>
> It's a trade-off: a short interval, like 15 ms, gives low latency and high throughput but uses more power. A long interval, like 1 s, saves a lot of battery but adds latency. The **slave latency** setting lets the peripheral skip some events when it has nothing to send."

### Q198. What is the purpose of the BLE MTU?

> "The ATT MTU is the **largest ATT packet** the two devices agree to exchange. The default is **23 bytes**, which leaves **20 bytes of data** per notification or write, after the 3-byte ATT header. After connecting, the devices can do an **MTU exchange** to increase it, up to 247 or more. A bigger MTU means fewer packets and less overhead, so **higher throughput**, especially combined with Data Length Extension."

### Q199. How would you implement a custom BLE service for device control and status?

> "I'd design one **custom service** with a random **128-bit UUID**, and a few characteristics, each with a clear job:
>
> - **Command** (write): the phone sends commands like start, stop, or set mode, as a small binary format with an opcode and parameters. I validate every command.
> - **Status** (read + notify): the device's state, like mode, errors and battery, notified whenever it changes.
> - **Data** (notify): live sensor readings.
> - **Configuration** (read + write): settings that are saved in flash.
>
> Writes that change behaviour require **encryption**, so only a paired phone can control the device. I'd also include a protocol version, so the app and firmware can evolve without breaking each other."

```text
Service  "Device Control"    UUID 6E400000-B5A3-F393-E0A9-E50E24DCCA9E (example)
 ├── Command        (Write, encrypted)       [opcode][params...]
 ├── Status         (Read, Notify)           [state][error][battery %]
 ├── Sensor Data    (Notify)                 [timestamp][values...]
 └── Configuration  (Read, Write, encrypted) [sample rate][thresholds]
```

### Q200. How would you debug a BLE connection or data-transfer failure?

> "Step by step:
>
> 1. **Is it advertising?** Check with the **nRF Connect** app: does the device appear, with the right name and UUID?
> 2. **Does it connect?** Look at the disconnect **reason code**. 0x08 is supervision timeout, often a timing or range problem. 0x13 means the remote user ended it. 0x3E means the connection failed to be established.
> 3. **Does service discovery work?** Browse the services in nRF Connect, and read and write characteristics by hand.
> 4. **Do notifications arrive?** Usually the app never wrote the **CCCD**.
> 5. **Data loss or slowness?** Check the MTU, the connection interval, and whether the stack's TX buffers are full.
> 6. Then capture the air traffic with a **BLE sniffer** (nRF Sniffer + Wireshark), and check the firmware's logs of BLE events and error codes."

### Q201. What is your experience with Infineon Bluetooth controllers?

*(Adapt this to your own experience.)*

> "I've worked with Infineon (formerly Cypress) Bluetooth controllers, the **CYW20xxx / AIROC** family, as a separate controller connected to the host MCU over **HCI UART**. That included the controller start-up: sending the **patch/firmware (the 'hcd' file) through vendor-specific HCI commands**, then changing the UART baud rate, setting the Bluetooth address, and then using the host stack for BLE advertising, connections and GATT. I used Infineon's tools for testing and their **BTSpy** trace tool to debug the HCI traffic."

---

## 8. IoT, MQTT and networking

### Q202. What is IoT architecture?

> "I think of it in four layers:
>
> 1. **Device layer**: the sensors and actuators with their MCU firmware, which read data and control things.
> 2. **Connectivity layer**: how the device talks to the network: Wi-Fi, BLE, cellular (LTE-M, NB-IoT), LoRaWAN, or Ethernet. Sometimes through a **gateway** that collects local devices.
> 3. **Cloud / platform layer**: an MQTT broker or IoT hub (AWS IoT, Azure IoT Hub), plus data storage, rules, device management and OTA updates.
> 4. **Application layer**: dashboards, mobile apps, analytics and alerts for the user.
>
> **Security** runs through every layer: device identity, encrypted communication, secure boot and signed updates."

### Q203. How does device-to-cloud communication work?

> "1. The device **connects to the network** (Wi-Fi, cellular...) and gets an IP address.
> 2. It opens a **secure connection** to the cloud endpoint: TCP, then a **TLS** handshake, where the device checks the server's certificate and usually authenticates itself with its **own client certificate**.
> 3. It connects with an application protocol, usually **MQTT**, sometimes HTTPS or CoAP.
> 4. It **publishes telemetry** to topics, like `site1/pump3/telemetry`, and **subscribes** to command topics to receive commands from the cloud.
> 5. It keeps the connection alive, and **reconnects** with back-off if it drops, buffering data meanwhile."

### Q204. What is MQTT?

> "MQTT is a **lightweight publish-subscribe messaging protocol**, built on TCP, designed for devices with little memory and unreliable networks. Its header can be as small as 2 bytes. Devices don't talk to each other directly: they publish messages to **topics** on a central **broker**, and the broker delivers each message to every client subscribed to that topic. It's the most common protocol for IoT device-to-cloud communication."

### Q205. How does MQTT publish-subscribe communication work?

> "1. Every client opens one TCP connection to the **broker** and sends **CONNECT**.
> 2. A client that wants data **subscribes** to a topic, for example `pool1/+/temperature`, where `+` matches one level and `#` matches everything below.
> 3. A client that has data **publishes** a message to a topic, like `pool1/sensor2/temperature` with payload `26.5`.
> 4. The broker checks which subscriptions match and **forwards** the message to those clients.
>
> The publisher and subscriber don't know about each other, so they're **decoupled** in space and time: new subscribers can be added without changing the publisher."

### Q206. What are an MQTT broker, publisher, subscriber and topic?

> "- **Broker**: the server in the middle that receives all messages and routes them to subscribers, like Mosquitto, EMQX or AWS IoT Core. It also handles authentication, retained messages and sessions.
> - **Publisher**: a client that sends messages to a topic, like a sensor publishing its temperature.
> - **Subscriber**: a client that has registered interest in a topic and receives the matching messages, like a dashboard.
> - **Topic**: the message's address, a hierarchical string like `company/site1/pump3/status`. Topics are created on the fly, just by publishing to them."

### Q207. What are MQTT QoS 0, QoS 1 and QoS 2?

| QoS | Name | Guarantee | Messages | Use |
| --- | --- | --- | --- | --- |
| 0 | At most once | May be lost, never duplicated | PUBLISH | Frequent telemetry, where one lost reading doesn't matter |
| 1 | At least once | Always delivered, may be duplicated | PUBLISH → PUBACK | Commands, events (with duplicate handling) |
| 2 | Exactly once | Delivered exactly once | PUBLISH → PUBREC → PUBREL → PUBCOMP | Billing, critical one-time actions |

> "Higher QoS means more reliability, but more messages, more memory and more latency. I mostly use QoS 1 with idempotent handling."

### Q208. Why can QoS 1 produce duplicate messages?

> "Because with QoS 1, the sender keeps the message until it gets a **PUBACK**. If the message arrives but the **PUBACK is lost**, for example the connection drops right then, the sender doesn't know the message arrived. So it **resends** it, with the DUP flag set, and the receiver gets it twice. QoS 1 guarantees 'at least once', not 'exactly once'."

### Q209. What does QoS 2 guarantee?

> "QoS 2 guarantees **exactly-once delivery** between the sender and the receiver. It uses a four-step handshake: PUBLISH, PUBREC (received), PUBREL (release), PUBCOMP (complete). The receiver stores the packet ID after PUBREC and won't deliver the same message twice, even if the PUBLISH is repeated. The cost is two round trips per message, and more state in memory."

### Q210. What is a retained MQTT message?

> "A retained message is one that the **broker stores** as the 'last known good value' for that topic. When a new client subscribes to that topic later, the broker **immediately sends it** the retained message, instead of the client waiting for the next publish.
>
> I use it for **state**, like `pump3/status = ON` or a device's configuration, so a dashboard that connects shows the current state right away. Publishing an empty retained message clears it."

### Q211. What is MQTT Keep Alive?

> "Keep Alive is a time, in seconds, that the client sets in its CONNECT message, for example 60 s. It's the **maximum time without any communication**. If the client has nothing to send, it sends a small **PINGREQ**, and the broker answers **PINGRESP**.
>
> If the broker hears **nothing for 1.5 times the keep-alive**, it considers the client dead, closes the connection, and publishes its Last Will. On the device side, a missing PINGRESP tells me the connection is broken, so I reconnect."

### Q212. What is Last Will and Testament?

> "The **Last Will** is a message the client registers with the broker **when it connects**: a topic, a payload, a QoS and a retain flag. If the client **disconnects unexpectedly** (a power loss, network drop, or keep-alive timeout), the broker publishes that message for it. If the client disconnects cleanly with DISCONNECT, the will isn't sent.
>
> Typical use: the will is `device42/status = offline` (retained), and right after connecting, the device publishes `device42/status = online`. So the dashboard always knows whether the device is alive."

### Q213. What happens if an MQTT connection is lost?

> "On the **broker side**: after 1.5 × keep-alive, it closes the session, publishes the client's **Last Will**, and, if the client used a **persistent session** (clean session = false), it keeps the subscriptions and queues QoS 1/2 messages for when it comes back.
>
> On the **device side**, my firmware:
>
> 1. Detects it: a socket error, or no PINGRESP.
> 2. Keeps collecting data into a **local buffer**.
> 3. **Reconnects** with exponential back-off and jitter, so a thousand devices don't reconnect at the same second.
> 4. Re-subscribes if needed, then sends the buffered data, and resends any unacknowledged QoS 1 messages."

### Q214. How would you buffer sensor data when the network is unavailable?

> "I use a **store-and-forward** buffer:
>
> - **In RAM**, a ring buffer for short outages.
> - **In flash**, for longer outages: records appended in a circular log, with a timestamp, a sequence number and a CRC, with wear in mind.
> - Each record has a **timestamp from the time it was measured**, not when it's sent.
> - When the connection is back, I send the oldest data first, at a controlled rate, and only delete a record after the broker **acknowledges** it (QoS 1).
> - When storage is full, I follow a defined policy: drop the oldest, or keep a summary like min/max/average, and record that data was lost."

### Q215. How do you secure MQTT communication?

> "- **Encryption**: always **MQTT over TLS** (port 8883), never plain port 1883 on the internet.
> - **Authentication**: each device has its **own X.509 client certificate** and private key (mutual TLS), or at least a unique username and token. No shared passwords.
> - **Authorization**: broker **ACLs**, so a device can only publish and subscribe to its own topics, like `devices/<device-id>/#`.
> - **Key storage**: the private key in a secure element or protected flash, not in plain firmware.
> - **Validation**: the device checks the server certificate against a trusted CA, and the firmware validates every incoming command."

### Q216. What is MQTT over TLS?

> "It's MQTT running inside a **TLS-encrypted** connection, usually on port **8883**. Before any MQTT packet is sent, the client and broker do a TLS handshake: the client verifies the broker's certificate, optionally the broker verifies the client's certificate, and they agree on session keys. After that, all MQTT traffic is **encrypted and integrity-protected**.
>
> On an MCU, it's done with a library like **mbedTLS** or wolfSSL, and it needs some resources: roughly 30-50 KB of RAM for the handshake, and a correct time source to check certificate validity."

### Q217. What is the difference between MQTT and HTTP?

| | MQTT | HTTP |
| --- | --- | --- |
| Model | Publish-subscribe, through a broker | Request-response, client to server |
| Connection | Long-lived, always open | Usually one request per connection (or keep-alive) |
| Server → device | Easy: device is subscribed, gets messages instantly | Hard: device must poll, or use WebSockets |
| Overhead | 2-byte minimum header | Large text headers |
| Delivery guarantees | QoS 0/1/2 built in | None beyond TCP |
| Best for | Telemetry, commands, many devices | REST APIs, file downloads, firmware images |

> "I typically use MQTT for telemetry and commands, and HTTPS for downloading OTA images."

### Q218. How would you avoid duplicate processing of MQTT messages?

> "Because QoS 1 can deliver a message twice, I make the receiver **idempotent**:
>
> - Every message carries a unique **message ID** or a **sequence number**, generated by the sender.
> - The receiver remembers the **last processed IDs** (a small table, or the last sequence number per sender), and ignores a message it has already processed.
> - Where possible, commands are designed to be naturally idempotent: 'set pump speed to 50 %' gives the same result if applied twice, unlike 'increase speed by 10 %'."

```c
/* Ignore a command whose sequence number we've already processed */
static uint32_t s_last_seq = 0U;

void on_command(uint32_t seq, const command_t *cmd)
{
    if (seq > s_last_seq)            /* new message: process it */
    {
        execute_command(cmd);
        s_last_seq = seq;            /* store in flash too if it must survive a reset */
    }
    /* else: duplicate or old message, ignore (but still acknowledge it) */
}
```

### Q219. How would you follow an existing cloud team's MQTT topic and payload standards?

> "First I'd **get their specification**: the topic hierarchy, payload format (JSON, CBOR, protobuf), field names, units, timestamp format, QoS and retain rules, and error codes. If there isn't a written spec, I'd ask for one, or write it with them.
>
> Then I'd implement it in **one module** in the firmware, so topic strings and payload building are in one place, not spread through the code. I'd test against **their broker** in a staging environment, or with their test client, and get sign-off. For any change, we'd agree on it together and **version** the payload, so old and new devices keep working."

### Q220. How would you design a scalable IoT architecture for pumps, lights, sensors and multiple swimming pools?

> "I'd structure it like this:
>
> - **Devices**: each pump, light and sensor controller runs firmware with a common communication module. Devices in one pool area connect to a **local gateway** (over RS-485/Modbus, BLE or Wi-Fi), or directly over Wi-Fi if they're IP-capable.
> - **Gateway per pool or site**: it collects the local devices, runs **local automation** (like 'turn on the pump if the temperature is too high'), so it keeps working even if the internet is down, and buffers data.
> - **Cloud**: an MQTT broker or IoT hub. Topics are hierarchical: `customer/site/pool/device-type/device-id/telemetry` and `.../cmd`. Each device has its own certificate.
> - **Backend services**: time-series database for telemetry, a device registry, rules and alerts, OTA update service.
> - **Apps**: web dashboard and mobile app per customer, with role-based access.
>
> It scales because each pool is independent, devices are identified by ID and not hard-coded, and adding a new pool is just provisioning new devices under a new topic branch."

```text
[pump][light][sensor] --RS-485/Wi-Fi--> [Pool gateway] --MQTT/TLS--> [Cloud broker] --> DB, rules, OTA
                                         (local control,                    |
                                          buffering)                        +--> dashboard / mobile app
topic: acme/site-07/pool-2/pump/P-0012/telemetry
```

### Q221. How would you support customer-specific product configurations without maintaining separate firmware branches?

> "**One firmware, configured by data**, not by branches:
>
> - **Configuration data** stored in flash or EEPROM: features enabled, sensor types, limits, protocol options. It's written in production or provisioned from the cloud.
> - **Feature flags** checked at run time, and a **board/variant ID** read at boot to choose drivers.
> - A **driver abstraction**, so different sensor models plug in behind the same interface.
> - If something must be compiled differently, a **build-time configuration** from the same branch, like Kconfig or a per-product header, built by CI.
>
> One codebase means one set of bug fixes and one test process."

### Q222. How would you maintain backward compatibility across a product lifetime of five to ten years?

> "- **Version everything**: the protocol messages, the configuration format in flash, and the APIs. Each has a version number.
> - **Only add, don't change**: new fields are added at the end, with defaults; old fields aren't removed or redefined. Receivers ignore unknown fields.
> - **Migration code**: when new firmware finds an old configuration version in flash, it converts it, instead of erasing it.
> - **Keep the bootloader and update path stable**: devices that skipped several versions must still be updatable.
> - **Automated regression tests** against old protocol versions and old app versions.
> - **Hardware abstraction**, so components that go end-of-life can be replaced with little firmware change.
> - **Documentation and long-term toolchain archiving**, so the build is reproducible years later."

---

## 9. Bootloader, secure boot and OTA

### Q223. What is your bootloader experience, and on which platform did you develop it?

*(Adapt this to your own experience.)*

> "I developed a custom bootloader on **STM32**, a Cortex-M4. It lives at the start of flash, checks the application image's header and CRC, and supports firmware updates over **UART** with our own packet protocol, and over the air through the application. It uses **A/B slots** with a metadata record, so an interrupted update can never brick the device, and it rolls back if the new image doesn't confirm itself. I've also worked with ST's **SBSFU** for secure boot with signature verification."

### Q224. Explain your STM32 bootloader architecture.

*(Adapt the sizes to your project.)*

> "The flash is split into areas:
>
> - **Bootloader** (48 KB at 0x08000000): write-protected.
> - **Metadata** (16 KB): which slot is active, image versions, CRCs, trial state, boot counter. Two copies with sequence numbers.
> - **Slot A** and **Slot B**: two application images.
>
> At reset the bootloader reads the metadata, checks the active slot's image (size, CRC or signature, version), and jumps to it: it disables interrupts, sets **VTOR** to the image's vector table, loads the **MSP** from word 0 and jumps to the **Reset_Handler** in word 1.
>
> The application downloads a new image into the **inactive slot** and marks it 'pending'. On the next reset the bootloader verifies it and boots it in **trial mode**; the app must confirm it after a self-test, otherwise the bootloader goes back to the old slot."

```text
0x08000000  Bootloader (48 KB, write-protected)
0x0800C000  Metadata   (16 KB: active slot, versions, CRC, trial flags)
0x08010000  Slot A     (application)
0x08080000  Slot B     (update target)
```

### Q225. What is the STM32 SBSFU framework?

> "SBSFU, **Secure Boot and Secure Firmware Update**, is ST's reference package (X-CUBE-SBSFU) for STM32 parts without TrustZone, and its successor on newer parts is TF-M / STM32Trust with SBSFU-like flows. It gives:
>
> - **Secure Boot**: the first code that runs after reset is always the SBSFU, and it checks that the active firmware is **authentic** (signed) and **intact** before running it.
> - **Secure Firmware Update**: installs new firmware images that are **signed** (ECDSA), optionally **encrypted** (AES), and checks them before installing.
> - **Protections**: it uses the chip's hardware security: RDP (readout protection), WRP (write protection), PCROP, MPU and the 'firewall', to isolate the secure code and keys.
> - **Tools** to sign and encrypt images on the PC side.
>
> I'd use it as a starting point rather than writing crypto and protection from scratch."

### Q226. How does secure boot work?

> "Secure boot builds a **chain of trust**, starting from code that can't be modified:
>
> 1. The **first-stage bootloader** is immutable: in ROM, or in write-protected flash locked by RDP.
> 2. It contains the **public key** of the manufacturer.
> 3. Before running the application, it calculates the image's **SHA-256 hash**, and verifies the image's **digital signature** with the public key.
> 4. Only if the signature is valid does it jump to the image. If not, it refuses: it tries the other slot, or stays in recovery mode.
> 5. Each stage can verify the next one in the same way.
>
> The result: only firmware signed with our private key can run on the device."

### Q227. What is the role of SHA-256 in firmware verification?

> "SHA-256 creates a **32-byte fingerprint** of the whole firmware image. If even one bit of the image changes, the hash is completely different. So it detects **any corruption or modification**.
>
> But a hash alone doesn't prove **who** made the image, because an attacker could modify the image and simply recompute the hash. That's why the hash is **signed**: the signature is created over the hash with our private key, so the device can trust it."

### Q228. What is ECDSA, and how does digital-signature verification work?

> "ECDSA is the **Elliptic Curve Digital Signature Algorithm**, an asymmetric signature scheme. A typical choice is the P-256 curve, which gives strong security with small keys: 32-byte keys, 64-byte signatures.
>
> - **Signing**, on our build server: compute the SHA-256 of the image, and sign that hash with the **private key**. The signature is stored in the image header.
> - **Verifying**, in the bootloader: compute the SHA-256 of the received image again, and check the signature with the **public key** stored in the device. The math confirms that only someone with the private key could have produced that signature for that exact hash.
>
> If the image or the signature has been changed, verification fails."

```text
Build server:  image --SHA-256--> hash --sign with PRIVATE key--> signature (stored with the image)
Device:        image --SHA-256--> hash --verify signature with PUBLIC key--> valid / invalid
```

### Q229. Where is the trusted public key stored?

> "Somewhere the attacker **can't change**:
>
> - Inside the **immutable bootloader** in flash that's write-protected and locked with RDP level 2, or
> - In **OTP** (one-time programmable) memory or eFuses, often just a hash of the key, or
> - In a **secure element** or a TrustZone secure area.
>
> It doesn't need to be secret, only **protected from modification**. If an attacker could replace the public key, they could sign their own firmware."

### Q230. Why must the private signing key be protected?

> "Because whoever has the private key can **sign any firmware**, and every device in the field will accept it as genuine. A leaked key means the whole product line can be taken over, and since the public key is locked in the devices, it's very hard to fix.
>
> So the private key **never goes into the firmware or the source repository**. It's kept in an **HSM** (hardware security module) or a secure signing server, with restricted access, and signing is done only by the release pipeline, with an audit log."

### Q231. How does a dual-bank or A/B OTA bootloader work?

> "There are **two slots** for firmware, A and B. The device runs from one, the **active** slot, and an update is always written into the other, **inactive** slot, while the device keeps working.
>
> When the download is complete, the image is verified (CRC or hash, and signature), and the metadata is changed to mark the new slot 'pending'. On the next reset the bootloader boots it in **trial mode**. If the new firmware passes its self-test, it confirms itself and becomes active. If it fails, the bootloader goes back to the old slot. There's always one working image, so an update can't brick the device.
>
> On STM32 parts with **dual-bank flash**, the hardware can even swap the banks with one option-byte bit, so both slots can run from the same address."

### Q232. What are active and inactive firmware partitions?

> "The **active** partition holds the firmware that's **currently running**, the known-good image. The **inactive** partition is the spare one: it holds either the previous version (for rollback) or the new image being downloaded. The bootloader decides which is active from the metadata. After a successful update, their roles swap."

### Q233. How do you switch from the active partition to the inactive partition?

> "By updating the **metadata**, never by touching the running image:
>
> 1. The new image is fully written into the inactive slot and **verified**.
> 2. The application writes the metadata: 'slot B pending, trial', with a new sequence number. I write the metadata as **two copies**, so a power cut during this write is safe.
> 3. The device resets.
> 4. The bootloader reads the metadata, verifies slot B again, and boots it in trial mode.
> 5. After a successful self-test, the application marks slot B **confirmed**, so it's now the active slot.
>
> On dual-bank STM32 parts, step 2 can be just toggling the **BFB2 / SWAP_BANK** option bit, and the hardware maps bank 2 to the boot address."

### Q234. How do you roll back if the new firmware fails?

> "I use **trial boot with confirmation**:
>
> - The bootloader starts the new image with a **boot counter** and the **watchdog** enabled.
> - The new application must run its **self-test** (peripherals OK, connected to the server, main tasks running) and then write 'confirmed' to the metadata.
> - If it crashes, hangs (the watchdog resets it), or doesn't confirm within N boots, the bootloader sees the counter run out and **switches back to the previous slot**, which still holds the old, known-good image.
>
> I also report the rollback to the server, so we know that update failed."

### Q235. What happens if power fails during a firmware update?

> "With a correct design: **nothing bad**. The new image was being written into the **inactive** slot, and the metadata still points to the old, active slot. So after power returns, the bootloader simply boots the old firmware.
>
> Even if the bootloader looked at the half-written slot, the image's **length and CRC or signature wouldn't match**, so it would never run it. The download can then **resume** from where it stopped, or restart. The key rule: switch the metadata only after the new image is complete and verified, and write the metadata safely, with two copies."

### Q236. How do you handle a corrupted or partially downloaded image?

> "Every image has a **header** with its size, version, hash and signature. The device verifies the **whole** image after downloading it, and again in the bootloader before booting it. A partial or corrupted image fails that check, so:
>
> - It's **never marked as pending**, and never booted.
> - The device **reports** the failure to the server, erases or ignores the slot, and **retries** the download, ideally **resuming** from the last good chunk, using the stored offset and an HTTP range request.
> - During download, each chunk has its own CRC and sequence number, so most errors are caught early and only that chunk is resent."

### Q237. How do you verify the firmware image before booting it?

> "The bootloader checks, in this order:
>
> 1. The **header** is valid: a magic number, the header version, and a sensible image size that fits the slot.
> 2. The **image's integrity**: compute the **SHA-256** (or a CRC-32 on simpler devices) over the image and compare it with the header.
> 3. The **authenticity**: verify the **ECDSA signature** over the hash with the stored public key.
> 4. The **version**: not older than the minimum allowed version (anti-rollback).
> 5. The **vector table looks sane**: the initial stack pointer is inside RAM, and the reset handler is inside the slot and has the Thumb bit set.
>
> Only if all of these pass does it jump to the image."

### Q238. How do you prevent unauthorized firmware from executing?

> "Several layers together:
>
> - **Secure boot**: only images with a valid signature from our private key run.
> - **Locked bootloader**: write protection on the bootloader and the key, so they can't be replaced.
> - **Debug port locked**: RDP level 1 or 2 on STM32, so nobody can flash or read the device through SWD.
> - **Signed updates**: the update path also checks signatures before installing anything.
> - **Anti-rollback**: old, vulnerable but genuinely signed images are refused.
> - **Encrypted images**, if the firmware's content itself must stay confidential."

### Q239. How would you implement anti-rollback protection?

> "Each image has a **security version number** in its signed header. The device stores the **minimum allowed version** in memory that can **only increase**: OTP bits, eFuses, a monotonic counter in a secure element, or at least write-protected flash.
>
> The bootloader refuses any image with a version **lower** than that stored minimum, even if its signature is valid. After a new version has booted and confirmed itself, the stored minimum is raised, so the old, possibly vulnerable version can never be installed again. I only raise it for releases that fix security issues, so normal rollback to the previous version still works for non-security releases."

### Q240. How do you manage firmware versions across production devices?

> "- Every build has a **semantic version** (major.minor.patch) plus the **Git commit hash** and a build number, embedded in the image header and readable through the device's diagnostics.
> - The **release** is tagged in Git, and the CI pipeline produces the signed binary, with checksums, release notes and the version, stored in an artifact repository.
> - A **device management** system (the cloud or a database) records which version each device runs; devices report their version at every connection.
> - **OTA updates are staged**: first a few internal devices, then a small percentage of the field, then everyone, with monitoring at each step."

### Q241. What is the difference between secure boot and secure OTA?

> "- **Secure boot** protects the device **at every start-up**: it verifies that the firmware already in flash is authentic and intact before running it.
> - **Secure OTA** protects the **update process**: the new image is downloaded over an **encrypted, authenticated** connection, its signature is verified **before it's installed**, it's optionally encrypted so it can't be read in transit, and the update is fail-safe with rollback.
>
> They complement each other: secure OTA makes sure only genuine updates get installed, and secure boot makes sure only genuine code runs, even if someone writes flash directly."

### Q242. How would you update firmware on a device with limited Flash memory and no flexible A/B partitioning?

> "Then I can't keep two full images, so I have a few options:
>
> - **External storage**: download the new image into an **external SPI flash** first, verify it there, then let the bootloader copy it into internal flash. Even a cheap 1 MB SPI flash solves the problem.
> - **Bootloader-driven, single-slot update**: the bootloader receives the image directly and writes it over the application. The bootloader itself stays intact, so if the update is interrupted, the device stays in bootloader mode and can retry. It's safe, but the device can't do its normal job during the update.
> - **Compression or delta updates**: send only the differences, so the download fits in a smaller staging area.
> - **Swap with a scratch sector**, like MCUboot's swap mode, which swaps the images sector by sector using one spare sector and a progress record."

### Q243. How would you validate OTA recovery and rollback mechanisms?

> "With deliberate **fault-injection testing**, ideally automated:
>
> - **Power cut** at random moments during download, during the metadata write, and during the first boot. I use a relay or programmable power supply controlled by a script, and run it hundreds of times.
> - **Network drop** in the middle of a download: does it resume correctly?
> - **Corrupted image** (flipped bits), **wrong signature**, **wrong device type**, and **older version** (anti-rollback): all must be rejected.
> - **A bad firmware** that crashes or never confirms: the device must roll back automatically.
> - **Many updates in a row**, and updates that skip versions.
>
> After each test, the device must come back running a valid image, and must report the result correctly."

---

## 10. Testing, MISRA, code review and CI/CD

### Q244. What testing methods do you use during embedded software development?

> "I use several levels:
>
> - **Static analysis** on every commit: compiler warnings as errors, MISRA checks, Cppcheck or SonarQube.
> - **Unit tests** on the PC, with Unity or GoogleTest, for the logic: parsers, state machines, calculations, with the hardware mocked.
> - **Integration tests** on the target: drivers with real peripherals, and modules working together.
> - **Functional and system tests** on the complete device, against the requirements, including stress tests, long-duration tests and fault injection (power cuts, bad messages, disconnected sensors).
> - **Hardware-in-the-loop** tests in CI where possible: a test rig flashes the board and runs scripted tests automatically.
> - **Code reviews** for every change."

### Q245. What is unit testing?

> "Unit testing is testing **one small piece of code**, usually one function or one module, **in isolation**, with all its dependencies replaced by fakes or mocks. In embedded, I run unit tests **on the PC**, where they're fast, and replace the hardware functions with mocks.
>
> For example, I test a checksum function with known inputs, or a protocol parser with valid, too-short and corrupted frames, and check the outputs and return codes."

```c
/* Unity test for a CRC-8 function (runs on the PC) */
void test_crc8_known_value(void)
{
    const uint8_t data[] = { 0x31, 0x32, 0x33 };          /* "123" */
    TEST_ASSERT_EQUAL_HEX8(0x48, crc8(data, sizeof(data)));
}

void test_parser_rejects_short_frame(void)
{
    const uint8_t frame[] = { 0xAA, 0x02 };                /* header only, no payload */
    TEST_ASSERT_EQUAL(PARSE_ERR_LENGTH, parse_frame(frame, sizeof(frame)));
}
```

### Q246. What is functional testing?

> "Functional testing checks that a **feature does what the requirement says**, from the outside, as a **black box**, without looking at the code. For example: 'when the temperature goes above 50 °C, the fan turns on within 1 second'. I set up the input, trigger the condition, and check the output: on the real device, or a simulator."

### Q247. What is integration testing?

> "Integration testing checks that **modules work correctly together**: the interfaces between them. Each module may pass its unit tests, but the integration can still fail, for example because of wrong units, byte order, timing or a misunderstood API.
>
> Examples: the sensor driver plus the filter plus the communication module, sending real readings to the server; or the bootloader together with the application during an update."

### Q248. What is system testing?

> "System testing tests the **complete product**, hardware and software together, in conditions close to real use, against the **system requirements**. It includes functional tests, performance, power consumption, long-run stability, environmental conditions like temperature, EMC, and error and recovery scenarios. It's the last stage before release."

### Q249. What are statement coverage, branch coverage and condition coverage?

> "They measure **how much of the code the tests exercise**:
>
> - **Statement coverage**: has every **line** been executed at least once?
> - **Branch (decision) coverage**: has every decision gone **both ways**: every `if` true and false, every `case` taken?
> - **Condition coverage**: in a decision with several conditions, like `if (a && b)`, has **each condition** been both true and false?
> - For safety standards (DO-178C level A, ISO 26262 ASIL D) there's also **MC/DC**: each condition must be shown to change the decision's result by itself.
>
> 100 % statement coverage can still miss bugs, because an `if` without an `else` might never be tested in its false case. That's why branch coverage matters more."

```c
if ((temp > 50) && (fan_ok))     /* two conditions in one decision */
{
    fan_on();
}
/* Statement coverage: one test with temp = 60, fan_ok = true runs every line.
 * Branch coverage:    also need a test where the if is false (temp = 40).
 * Condition coverage: temp > 50 true and false, AND fan_ok true and false. */
```

### Q250. For the condition temperature > 50, what input values make it true or false?

> "For `temperature > 50` with integers: **51 and above** make it true, **50 and below** make it false. The important test values are at the **boundary**: **50** (false, because 50 is not greater than 50) and **51** (true), plus one typical value on each side, like 0 and 100, and the type's extremes. If the variable is a float, the boundary values are 50.0 (false) and something just above, like 50.1 (true)."

### Q251. How do you perform boundary-value testing?

> "Bugs often happen **at the edges** of ranges: off-by-one errors, `>` versus `>=`. So for each range in the requirements, I test **at the boundary, just below it and just above it**, plus the minimum and maximum of the type.
>
> For example, a valid input range of 10 to 100: I test **9, 10, 11, 99, 100, 101**, plus 0, negative values and the maximum value of the type. For a buffer of 64 bytes: lengths 0, 1, 63, 64 and 65."

### Q252. What defects do you commonly find during code reviews?

> "The ones I see most often:
>
> - **Missing error handling**: return values not checked, no timeouts on waits.
> - **Race conditions**: variables shared with an ISR without `volatile` or without protection.
> - **Buffer problems**: no length check, off-by-one, missing `'\0'`.
> - **Integer issues**: signed/unsigned mixing, overflow, wrong types for register values.
> - **Uninitialized variables** and NULL pointers.
> - **Blocking calls in ISRs**, or ISRs that are too long.
> - **Magic numbers** and duplicated code.
> - **Resource leaks**: a mutex not released on an error path.
> - Comments and documentation that don't match the code."

### Q253. How do you review embedded code for safety and reliability?

> "I go through a checklist, beyond 'does it work':
>
> - **Every failure path**: what happens if this call fails, this sensor disconnects, or this message is corrupted?
> - **Concurrency**: what's shared between tasks and ISRs, and how is it protected?
> - **Timing**: worst-case execution time, blocking calls, timeouts.
> - **Memory**: stack usage, buffer sizes and bounds, no dynamic allocation after start-up.
> - **Input validation**: everything from outside (UART, BLE, network) is checked.
> - **Coding standard**: MISRA findings handled or justified.
> - **Testability**: are there unit tests, and do they cover the edge cases?
> - **Safe defaults**: on an unexpected state, the system goes to a safe state, and the watchdog can still catch a hang."

### Q254. What MISRA C violations have you encountered?

> "The most common ones in real code:
>
> - **Rule 10.x (essential types)**: mixing signed and unsigned, or assigning a wider type to a narrower one without a cast.
> - **Rule 15.6**: `if` or loop bodies without braces.
> - **Rule 17.7**: ignoring a function's return value, so I add `(void)` or handle it.
> - **Rule 11.x**: casts between pointers and integers, for register access. These become documented deviations.
> - **Rule 21.3**: `malloc`/`free`, replaced with static pools.
> - **Rule 15.5**: multiple returns in one function (advisory).
> - **Rule 8.4 / 8.7**: global variables without a declaration in a header, or that should be `static`.
> - **Rule 2.x**: unused code, variables or parameters."

### Q255. Why does MISRA discourage certain uses of dynamic memory allocation?

> "Same as [Q30](#q30-why-are-dynamic-memory-allocation-functions-restricted-or-discouraged-under-some-misra-rules): heap fragmentation, non-deterministic timing, allocation that can fail at run time in situations testing never hit, and bugs like leaks, double free and use-after-free. So memory is allocated statically, and the worst case is known at build time."

### Q256. How do you implement runtime packet queues while following coding standards?

> "With a **static pool of fixed-size buffers** and a ring buffer of indexes, as in [Q31](#q31-how-can-we-implement-flexible-packet-queuing-while-following-misra-c). Allocation and release are O(1), there's no fragmentation, the maximum number of packets is fixed at compile time, and running out returns an error instead of crashing."

### Q257. What is your process when production firmware crashes?

> "1. **Contain**: understand the impact (how many devices, is it a safety issue) and stop any rollout of that version.
> 2. **Collect data**: crash logs, fault registers, PC/LR and the stack dump from affected devices, the firmware version, and the conditions when it happened.
> 3. **Reproduce** it in the lab, with the same version and conditions.
> 4. **Find the root cause**: with the map file and `addr2line` for the crash address, the debugger, and the logs.
> 5. **Fix**, with a test that reproduces the bug, a review and a regression run.
> 6. **Release** the fix with a staged rollout, and confirm the crash rate drops.
> 7. **Learn**: a short post-mortem, and add checks so this class of bug is caught earlier."

### Q258. What is your first response when you receive a production defect?

> "First I **understand the impact and the facts**: what exactly happens, how many devices, which firmware and hardware version, since when, and is it a safety risk. I ask for logs and, if possible, a failed unit.
>
> Then I **acknowledge it** to the reporter, say when they'll hear from me next, and decide the priority with my lead. If it's urgent, I look for a quick **mitigation** first, like a configuration change or holding back an update, before the full fix. I don't jump to changing code before I understand the problem."

### Q259. Would you investigate a production issue alone or involve other teams?

> "I'd start the investigation myself, but **involve other teams early** whenever the issue might cross boundaries. Production issues are often not only firmware: they can be a hardware batch problem, a manufacturing step, a cloud change, or the app. So I'd bring in hardware, test, manufacturing or the cloud team as soon as the data points that way, and keep everyone updated in one shared place. Solving it alone isn't the goal; solving it quickly and correctly is."

### Q260. How do you collect crash logs, fault registers, PC/LR and stack information?

> "I build it into the firmware before it's needed:
>
> - The **HardFault handler** reads the stacked registers (R0-R3, R12, **LR**, **PC**, xPSR), the fault status registers (**CFSR**, **HFSR**, **MMFAR**, **BFAR**), and a part of the stack.
> - It saves them in a **reserved RAM area** that isn't cleared at reset, or in a flash log sector, with the firmware version and an uptime timestamp.
> - Then it **resets**. At the next boot, the firmware finds the crash record and sends it to the server or writes it to the debug UART.
> - In the lab I use `addr2line -e firmware.elf <PC>` with the exact ELF of that version to find the file and line."

```c
/* Saves the crash context; called from HardFault_Handler with the stacked frame */
typedef struct
{
    uint32_t magic;            /* marks a valid record after reset */
    uint32_t r0, r1, r2, r3, r12, lr, pc, xpsr;
    uint32_t cfsr, hfsr, mmfar, bfar;
} crash_record_t;

__attribute__((section(".noinit"))) static crash_record_t s_crash;   /* survives a reset */

void hardfault_save(const uint32_t *frame)          /* frame = MSP or PSP at the time of the fault */
{
    s_crash.r0   = frame[0];  s_crash.r1 = frame[1];  s_crash.r2  = frame[2];
    s_crash.r3   = frame[3];  s_crash.r12 = frame[4]; s_crash.lr  = frame[5];
    s_crash.pc   = frame[6];                          /* the instruction that faulted */
    s_crash.xpsr = frame[7];
    s_crash.cfsr  = SCB->CFSR;                        /* why it faulted   */
    s_crash.hfsr  = SCB->HFSR;
    s_crash.mmfar = SCB->MMFAR;                       /* bad address, if valid */
    s_crash.bfar  = SCB->BFAR;
    s_crash.magic = 0xDEADC0DEUL;
    NVIC_SystemReset();                               /* report it after the reboot */
}
```

### Q261. How do you reproduce and isolate a production failure?

> "- **Match the conditions**: the same firmware version, hardware revision, configuration, and the same inputs: the same charger, network, sensor values, temperature.
> - **Use the logs** to see what happened just before the crash, and replay that sequence.
> - **Stress it** if it's rare: run the scenario many times, raise the load, use temperature cycling, or speed up timers.
> - **Isolate**: once I can reproduce it, I remove parts until it disappears. I disable a task, use a fixed input, or bisect firmware versions with `git bisect` to find the commit that introduced it.
> - **Instrument**: add a trace, a watchpoint on the corrupted variable, or toggle GPIOs to see the timing on a logic analyzer."

### Q262. How do you perform root-cause analysis?

> "I keep asking **why** until I reach the real cause, not just the symptom, the '5 Whys'. For example:
>
> 1. Why did it crash? A HardFault on a NULL pointer in `sensor_read()`.
> 2. Why was the pointer NULL? The sensor init had failed.
> 3. Why wasn't that handled? The return value of `sensor_init()` wasn't checked.
> 4. Why did init fail? A new sensor batch needs a longer power-up delay.
> 5. Why didn't testing catch it? We only tested with the old batch.
>
> So the fix is the delay **and** checking the return value, and the process change is testing with parts from each new batch. I write it down with the evidence for each step."

### Q263. What do you do after identifying the defect?

> "1. **Write a test** that reproduces the bug and fails.
> 2. **Fix** the root cause, with the smallest safe change, and check the same bug pattern elsewhere in the code.
> 3. **Verify**: the new test passes, and the full regression suite still passes.
> 4. **Review** the fix with a colleague.
> 5. **Release** it through the normal pipeline with a new version and release notes, and update affected devices with a staged rollout.
> 6. **Document** the root cause and the fix in the ticket, and share the lesson with the team."

### Q264. How do you ensure the fix does not introduce regressions?

> "- Keep the fix **small and focused**.
> - Run the **full automated regression suite**: unit tests on every commit, and hardware-in-the-loop tests on the target.
> - Add the **new test** for this bug to the suite permanently, so it can't come back.
> - **Review** what else uses the changed code, and test those paths too.
> - **Staged rollout**: release to a small group of devices first and watch the metrics before releasing to everyone."

### Q265. How do you manage code reviews?

> "Every change goes through a **pull request**: a small, focused change, with a description of what and why, a link to the ticket, and evidence of testing. CI must pass first: build, static analysis and unit tests, so reviewers focus on the logic. At least one reviewer approves; for critical code like the bootloader, two.
>
> As a reviewer, I check correctness, error handling, concurrency, memory and readability, using a checklist, and I keep comments specific and respectful, with suggestions. I try to review within a day, so nobody is blocked."

### Q266. What review feedback have you received?

*(Adapt this to your own experience; be honest and show what you learned.)*

> "Early on, I got feedback that my pull requests were **too large**, mixing a feature, a refactor and formatting, which made them hard to review. Since then I split changes into small, focused commits and PRs, and reviews go much faster.
>
> Another one was about **error handling**: in a driver I hadn't handled a timeout on an I2C read. Now I check every failure path explicitly, and I review others' code for the same thing."

### Q267. How do you create a production firmware binary?

> "Production binaries are built **only by the CI pipeline**, never on someone's laptop:
>
> 1. Build from a **tagged commit** in Git, in a fixed build environment (a Docker image with a pinned compiler version), so the build is reproducible.
> 2. Use the **release configuration**: optimization on, debug logging off, asserts handled, and the version and Git hash embedded.
> 3. Produce the ELF, plus `.bin` and `.hex` files, and the map file.
> 4. **Sign** the image (for secure boot) and calculate checksums.
> 5. Run the automated tests on the result.
> 6. Store everything in the artifact repository, with release notes."

### Q268. How do you tag and version a release in Git?

> "I use **semantic versioning**, `MAJOR.MINOR.PATCH`: major for incompatible changes, minor for new features, patch for fixes. When a release is ready, I create an **annotated tag** on the release commit, and push it, which triggers the release pipeline. The build reads the version from the tag and embeds it, with the commit hash, in the firmware."

```bash
git tag -a v2.3.1 -m "Release 2.3.1: fix I2C timeout on sensor init"
git push origin v2.3.1          # the pushed tag triggers the release pipeline

git describe --tags --dirty     # e.g. v2.3.1-4-g1a2b3c4: 4 commits after v2.3.1, at commit 1a2b3c4
```

### Q269. How do you trigger a CI/CD pipeline?

> "The pipeline is triggered **automatically by Git events**:
>
> - **Every push and pull request**: build, static analysis and unit tests.
> - **Merge to the main branch**: also the integration tests, and maybe hardware-in-the-loop tests.
> - **A release tag**: the full release build, signing and packaging.
> - Plus a **nightly** run for long tests.
>
> It's configured as code in the repository, in a `Jenkinsfile`, `.gitlab-ci.yml` or a GitHub Actions workflow. A manual trigger is also possible for special builds."

### Q270. What artifacts does the pipeline generate?

> "- The firmware **binaries**: `.elf` (with debug symbols, kept for crash analysis), `.bin`, `.hex`, and the **signed** image for OTA.
> - The **map file**, and a memory-usage report (flash and RAM).
> - **Checksums** (SHA-256) of every binary.
> - **Test reports**: unit tests, coverage, hardware tests.
> - **Static analysis** and MISRA reports.
> - **Release notes** and a version or manifest file with the Git hash.
> - Sometimes the production programming package for the factory."

### Q271. How do you maintain traceability between source code and production firmware?

> "- Every binary has the **version and the Git commit hash** embedded, readable from the running device.
> - Release builds come only from **tagged commits** in CI, in a fixed environment, so I can rebuild the exact same binary.
> - The **ELF and map file** of every release are archived, so a crash address from the field can be decoded years later.
> - Commits and pull requests reference **ticket IDs**, and tickets reference requirements, so I can go from a requirement to the code and to the release that contains it.
> - The factory and the device database record which version each device was shipped with."

### Q272. Have you used SonarQube or another static-analysis tool?

*(Adapt this to the tools you've used.)*

> "Yes. I've used **SonarQube** in CI, which reports bugs, code smells, duplication and coverage, with a quality gate that fails the build if new issues appear. For C, I've also used **Cppcheck**, the compilers' own warnings with `-Wall -Wextra -Werror`, and a MISRA checker (**PC-lint Plus** / **Polyspace**). The most useful habit is to keep the warnings at zero on new code, so real issues don't get lost in the noise."

### Q273. How do you share production binaries with the manufacturing team?

> "Through a **controlled release package**, never by email or chat:
>
> - The release pipeline publishes the package to an **artifact repository** or a controlled release folder, with access control.
> - The package contains: the production image (often bootloader plus application combined in one `.hex`), the **SHA-256 checksums**, the version, the programming instructions and option-byte settings, and the release notes.
> - The release is **approved** in the release process (a change request or ECO), and manufacturing only uses approved versions."

### Q274. How do you ensure the factory programs the correct firmware version?

> "- The factory programs only the **approved, checksummed package** for that product revision.
> - The programming tool **verifies the checksum** of the file before programming, and **reads back and verifies** the flash after programming.
> - The **end-of-line test** reads the firmware version from the device (over UART or USB) and compares it with the expected version. A mismatch fails the unit.
> - Each device's **serial number and firmware version** are logged in the production database."

### Q275. What reports, checksums and release documentation do you maintain?

> "For each release:
>
> - **Release notes**: version, date, new features, fixed bugs with ticket IDs, known issues, compatibility notes.
> - **Checksums**: SHA-256 of every binary.
> - **Test reports**: unit, integration and system tests, with coverage.
> - **Static analysis / MISRA report**, including justified deviations.
> - **Build information**: Git tag and hash, compiler version, build environment.
> - The archived **ELF and map files**.
> - For regulated products: traceability matrices and a change-impact analysis."

---

## 11. Linux, system architecture and board bring-up

### Q276. What is your experience with Embedded Linux?

*(Adapt this to your own experience.)*

> "I've worked on Embedded Linux on **ARM SoC boards**: building images with **Yocto** or Buildroot, configuring **U-Boot**, writing and changing **device tree** nodes for new peripherals, writing and debugging **kernel drivers** for I2C and SPI devices, and writing user-space applications in C/C++ that use those drivers through sysfs, `/dev`, and `ioctl`. I've also debugged boot problems from the serial console and used tools like `dmesg`, `i2cdetect`, `strace` and GDB."

### Q277. What is your current Linux platform-porting task?

*(Fill in your real task; example:)*

> "I'm porting our application from an older ARM edge device to a newer SoC board. That involves updating the **BSP**: the U-Boot configuration, the kernel version and the **device tree** for the new board's pins and peripherals; making sure the **drivers** for our sensors and communication interfaces work on the new kernel; and adapting the **application** where hardware paths changed, like the GPIO numbering, the UART device names and the network interface names. Then validating that everything behaves the same as on the old device."

### Q278. How would you migrate functionality from one Linux edge device to another?

> "1. **Inventory** what the old device does: applications, services, configuration files, kernel modules, drivers, device tree changes, startup scripts, and every hardware interface it uses.
> 2. **Compare the hardware** of the two devices (see Q279), and list what's different.
> 3. **Bring up the new board's BSP**: bootloader, kernel, device tree, and check each interface works with basic tools.
> 4. **Rebuild the applications** for the new target, ideally with the same Yocto layer, so the dependencies are the same.
> 5. **Abstract the differences**: put hardware paths and names in configuration, not hard-coded.
> 6. **Validate**: run the same tests on both devices and compare the results, including performance and power.
> 7. Plan the **field migration**: data and configuration migration, and the update path."

### Q279. What hardware dependencies would you check during platform migration?

> "- **CPU architecture**: ARMv7 vs ARMv8 (32 or 64-bit), endianness, FPU and NEON, so the binaries and libraries need rebuilding.
> - **Peripherals**: which UARTs, I2C, SPI, CAN and GPIOs exist, their names and numbers, and the pin muxing.
> - **Storage**: eMMC, SD or NAND, the partition layout, and the boot media.
> - **Memory**: RAM size and the performance of the applications.
> - **Networking**: Ethernet PHY, Wi-Fi/BLE module and its driver and firmware.
> - **Power**: PMIC, voltage levels (3.3 V vs 1.8 V I/O), sleep modes.
> - **Kernel driver support** for every chip on the new board.
> - **Security hardware**: secure boot, TPM or secure element."

### Q280. How does an application communicate with a Linux device driver?

> "Through **files**, because in Linux 'everything is a file':
>
> - **Character devices** in `/dev`: the application calls `open()`, `read()`, `write()` and `ioctl()`, and the kernel calls the driver's `file_operations` functions.
> - **sysfs** in `/sys`: simple attributes, like `/sys/class/gpio/...` or an IIO sensor's `in_temp_raw`, read and written as text.
> - Standard subsystems with their own interfaces: **input events**, **IIO**, **network sockets** for network drivers, **ALSA** for audio.
> - For high-speed data, `mmap()` of a shared buffer.
>
> The application never calls driver functions directly; the system call goes through the kernel's VFS, which calls the driver."

```c
int fd = open("/dev/mysensor", O_RDWR);          /* kernel calls the driver's open()  */
int32_t value;
read(fd, &value, sizeof(value));                 /* kernel calls the driver's read()  */
ioctl(fd, MYSENSOR_SET_RATE, 100);               /* kernel calls the driver's ioctl() */
close(fd);
```

### Q281. What is a Device Tree (DTS)?

> "A device tree is a **data structure that describes the hardware** of a board, for hardware that can't be discovered automatically: which SoC, how much memory, which peripherals are enabled, which pins they use, and which external chips are connected to which bus, with their addresses and interrupts.
>
> The `.dts` source is compiled into a binary `.dtb`, which the bootloader passes to the kernel at boot. The kernel then creates the devices and matches them to drivers using the `compatible` string. This means **one kernel binary can support many boards**; only the device tree changes."

### Q282. How do you write a Device Tree for a device?

> "I start from the SoC's `.dtsi` file and the closest existing board's `.dts`, and then:
>
> 1. **Enable** the controllers my board uses, with `status = "okay"`.
> 2. Set the **pin muxing** with `pinctrl` for each interface.
> 3. Add each **external device** as a child of its bus, with `compatible` (which selects the driver), `reg` (the I2C address or SPI chip select), interrupts, GPIOs and any properties the driver's binding document requires.
>
> I always check the driver's **binding documentation** in `Documentation/devicetree/bindings/`, compile with `make dtbs`, and check the result on the target in `/proc/device-tree/` and `dmesg`."

```dts
&i2c1 {
    pinctrl-names = "default";
    pinctrl-0 = <&i2c1_pins>;              /* SDA/SCL pin muxing                   */
    clock-frequency = <400000>;            /* 400 kHz                              */
    status = "okay";                       /* enable this controller               */

    temp_sensor: tmp117@48 {               /* @48 = I2C address                    */
        compatible = "ti,tmp117";          /* matches the tmp117 driver            */
        reg = <0x48>;
        interrupt-parent = <&gpio1>;
        interrupts = <14 IRQ_TYPE_EDGE_FALLING>;   /* ALERT pin on GPIO1_14      */
    };
};
```

### Q283. What is the difference between MCU firmware and an Embedded Linux system?

| | MCU firmware | Embedded Linux |
| --- | --- | --- |
| Hardware | Microcontroller, KB-MB of flash/RAM, no MMU | Application processor with MMU, hundreds of MB of RAM |
| Software | Bare metal or RTOS, one program | Full OS: kernel, drivers, file system, many processes |
| Boot time | Milliseconds | Seconds |
| Real-time | Hard real-time, deterministic | Soft real-time (better with PREEMPT_RT) |
| Power | Very low, µA sleep modes | Higher |
| Development | Direct register access, vendor HAL | Kernel drivers + user space, standard libraries and tools |
| Strengths | Cost, power, determinism, simplicity | Networking, file systems, UI, many existing libraries |

### Q284. How would you choose between bare metal, FreeRTOS and Embedded Linux?

> "I look at the requirements:
>
> - **Bare metal**: a simple device with a few jobs, tight cost, very low power, or a very small MCU. Example: a sensor node that wakes up, measures, sends and sleeps.
> - **FreeRTOS**: several independent activities with **real-time deadlines**, like communication, control loops and a UI at the same time, on an MCU. Example: a motor controller with BLE.
> - **Embedded Linux**: complex software needs: networking stacks, a file system, a rich display UI, cameras, AI, many third-party libraries, and enough budget for the processor, memory and power. Example: a gateway or an HMI panel.
>
> Often the answer is **both**: Linux on an application processor for the high-level work, plus an MCU with an RTOS for the hard real-time control."

### Q285. How do you validate a new hardware schematic against the datasheet?

> "I review it block by block, with each part's datasheet open:
>
> - **Power**: every supply pin connected, the right voltage, the **decoupling capacitors** as recommended, VCAP/VDDA/VBAT handled, enough current from the regulators.
> - **Pins**: each signal uses a pin that really supports that **function** (I check the pin-mux table, often with CubeMX), with no conflicts between peripherals.
> - **Boot and reset**: BOOT pins with the right pull-ups or pull-downs, a reset circuit, a debug connector (SWD) accessible.
> - **Clocks**: crystal frequency and **load capacitors** calculated.
> - **Interfaces**: I2C pull-ups, I2C addresses not conflicting, SPI chip selects, UART TX/RX not swapped, USB data lines and resistors, level shifting between voltage domains.
> - **Protection**: ESD on external connectors, reverse-polarity and over-voltage protection.
> - **Unused pins** handled as the datasheet recommends."

### Q286. What steps do you follow for board bring-up?

> "I go from the most basic to the most complex, and verify each step before the next:
>
> 1. **Visual inspection** and **power without the MCU running**: check the rails for shorts, then measure every voltage.
> 2. **Clock and reset**: the crystal oscillates, NRST is high, BOOT pins are right.
> 3. **Debugger connects** over SWD/JTAG; read the chip ID.
> 4. **First code**: blink an LED. Then a **UART console** to get prints.
> 5. **Clock tree**: switch to the external crystal and PLL, and check the frequency on the MCO pin.
> 6. **Each peripheral** one by one: GPIO, UART, I2C (scan for devices, read their ID registers), SPI, ADC, PWM, USB, Ethernet.
> 7. **Memory** tests for external RAM or flash.
> 8. **Power modes** and current consumption.
> 9. Then the real application and system tests."

### Q287. What do you check if the MCU cannot be programmed?

> "- **Power**: are all supply pins at the right voltage, including VDDA? Is the board drawing a sensible current?
> - **Debug connection**: SWDIO, SWCLK, GND and the **target voltage** reference connected to the probe, short wires, the right pinout on the connector.
> - **Reset**: is NRST held low by something? Try **'connect under reset'**.
> - **BOOT0**: in the right state.
> - **The chip**: is it the right part, and is it soldered correctly? Check for bridges under a microscope.
> - **Firmware locking**: the previous firmware may have disabled the SWD pins, or entered low-power mode, so connect under reset. **RDP read protection** may be on, needing a mass erase.
> - **The tools**: the probe's firmware, the right device selected, and a lower SWD clock speed."

### Q288. How do you verify power rails, clocks, reset and boot pins?

> "- **Power rails**: first, with the board unpowered, measure the resistance from each rail to ground, to catch a short. Then power it, ideally from a **current-limited supply**, and measure each rail with a multimeter. Then check **ripple and start-up** with an oscilloscope.
> - **Clocks**: check the crystal with a scope, using a 10x probe, because the probe's capacitance can stop the oscillator. Better, route the clock to the **MCO pin** and measure its frequency there.
> - **Reset**: measure NRST: it should be high after power-up, and the power-on reset timing should match the datasheet.
> - **Boot pins**: measure BOOT0 and other strap pins at reset, and compare with the boot-mode table in the reference manual."

### Q289. What is OpenOCD?

> "OpenOCD, the **Open On-Chip Debugger**, is an open-source tool that connects a **debug probe** (ST-LINK, J-Link, CMSIS-DAP, FTDI) to the target chip over **JTAG or SWD**. It can program flash, read and write memory and registers, halt and step the CPU, and it acts as a **GDB server**, so GDB or an IDE can debug the target. It supports many chips through configuration scripts."

### Q290. How does OpenOCD work with JTAG/SWD and GDB?

> "It sits in the middle:
>
> 1. **GDB** (or the IDE) talks to OpenOCD over TCP, port **3333**, using the GDB remote protocol: 'read memory', 'set breakpoint', 'continue'.
> 2. **OpenOCD** translates those requests into debug operations for that CPU architecture: Arm's debug interface, using the CoreSight registers.
> 3. It drives the **debug probe** over USB, and the probe generates the actual **SWD or JTAG signals** to the chip.
>
> There's also a telnet console on port **4444** for direct commands."

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg      # start the GDB server

arm-none-eabi-gdb firmware.elf
(gdb) target extended-remote :3333        # connect to OpenOCD
(gdb) monitor reset halt                   # OpenOCD command: reset and stop the CPU
(gdb) load                                 # program the flash
(gdb) break main
(gdb) continue
```

### Q291. Can OpenOCD read or write MCU memory and registers?

> "Yes. Through the telnet console or GDB's `monitor` command, I can read and write memory with **`mdw`** (memory display word) and **`mww`** (memory write word), which also covers peripheral registers, since they're memory-mapped. I can read the CPU registers with **`reg`**, and program flash with **`flash write_image`** or `program`."

```text
> halt
> mdw 0x40020014          # read GPIOA_ODR
0x40020014: 00000020
> mww 0x40020014 0x0      # write it: turn the LED off
> reg pc                  # read the program counter
pc (/32): 0x08000a3c
> program firmware.elf verify reset
```

### Q292. How do you use JTAG/SWD for firmware debugging?

> "With a debugger connected over SWD, I can:
>
> - **Set breakpoints** and step through code, and watch variables and registers.
> - Use **watchpoints** to stop when a variable is written, to find who corrupts it.
> - **Halt** a stuck system and read the **PC** to see where it is, and the **call stack**.
> - After a **HardFault**, read the fault registers and the stacked PC to find the crash location.
> - Look at **peripheral registers** in the IDE's register view, to check the configuration.
> - Use **SWO / ITM** for printf-style tracing without a UART, or **RTT** with J-Link.
> - Program the flash."

### Q293. What tools have you used for hardware-level debugging?

> "- **Multimeter**: voltages, continuity, shorts.
> - **Oscilloscope**: signal quality, rise times, power ripple, start-up sequencing, timing measurements with GPIO toggles.
> - **Logic analyzer** (Saleae): decoding UART, I2C, SPI and CAN traffic.
> - **Debug probes**: ST-LINK, J-Link, with STM32CubeIDE, OpenOCD and GDB.
> - **Protocol analyzers**: CAN analyzer (PCAN), USB-PD sniffer, BLE sniffer (nRF Sniffer + Wireshark).
> - **Current measurement**: a power analyzer or Nordic PPK for low-power profiling.
> - **Programmable power supply** with current limiting."

### Q294. How do you validate UART, SPI, I2C, ADC, PWM and GPIO during bring-up?

> "One by one, with a measurement instrument to confirm each:
>
> - **GPIO**: toggle each output and measure it; read inputs with a known level.
> - **UART**: loopback (TX to RX) first, then a terminal on the PC; check the baud rate on the scope.
> - **I2C**: scan all addresses to find the devices, then read each device's **ID register**; check the signal edges and pull-ups on the scope.
> - **SPI**: read a known register, like the flash's JEDEC ID or a sensor's WHO_AM_I; check the mode and clock on a logic analyzer.
> - **ADC**: apply known voltages, like 0 V, a reference and Vref, and compare the readings with the expected counts; check the noise.
> - **PWM**: measure the frequency and duty cycle on the scope at several settings.
>
> I keep these as small test functions, or a test command shell, so they can be reused in production testing."

---

## 12. Electronics, displays and hardware interfaces

### Q295. Have you interfaced alphanumeric displays or screens?

*(Adapt this to your own experience.)*

> "Yes. I've interfaced a **16×2 character LCD** (HD44780 controller) using a 4-bit parallel interface and also through an I2C backpack (PCF8574), a small **128×64 OLED** with the SSD1306 controller over I2C, and a **colour TFT** (ILI9341) over SPI with DMA. For each one, I wrote the low-level driver (reset, init command sequence, commands versus data) and a small layer on top for text and simple graphics, or used a library like u8g2 or LVGL."

### Q296. Would you choose I2C or SPI for a display that only shows text and alerts?

> "**I2C**, if it's on the same board. A text display only needs a few bytes per update, so I2C's speed is plenty, and it uses just two pins, which I can share with other I2C devices. I'd switch to SPI only if the display updates graphics often, or if I2C is already busy with time-critical sensors. More detail in [Q125](#q125-when-would-you-choose-i2c-for-a-display)."

### Q297. What changes if the display is on a separate PCB?

> "The **cable** becomes the main concern: its capacitance slows the edges, it picks up noise, and there's a ground connection between two boards. Same reasoning as [Q126](#q126-would-you-still-use-i2c-if-the-display-is-on-a-separate-pcb):
>
> - For a **short** cable, I2C still works at 100 kHz, with stronger pull-ups, a solid ground and maybe ESD protection on the connector.
> - For a **longer** cable or a noisy environment, I'd use a **differential** I2C buffer, or a **UART/RS-485 or CAN** link to a small MCU on the display board, which then drives the display locally.
> - I'd also think about **power** to the display board, and about **connector reliability**: what happens if the display is unplugged while running?"

### Q298. How do distance and electrical noise affect the choice of communication protocol?

> "- **Short distance, on-board, quiet**: I2C and SPI are fine. They're single-ended and designed for centimetres.
> - **Longer distance**: single-ended signals lose quality because of cable capacitance and ground differences between boards. A **differential** signal (RS-485, CAN, Ethernet, LVDS) carries the signal on two wires as a difference, so noise that hits both wires cancels out. That works over tens to hundreds of meters.
> - **Very noisy** (motors, relays, automotive): differential signalling, plus **error detection** (CRC) and retransmission, which CAN has built in.
> - **Electrical isolation** between systems, for safety or to stop ground loops: isolated transceivers or optocouplers.
>
> So the further and the noisier, the more I move toward differential, error-checked protocols."

### Q299. When would you choose CAN or RS-485 for board-to-board communication?

> "As in [Q127](#q127-when-would-you-choose-can-or-rs-485-instead-of-i2cspi-for-board-to-board-communication): when the boards are far apart, the environment is noisy, or several boards share one bus.
>
> - **CAN** when I want the protocol to do the hard work: multi-master arbitration with priorities, CRC, automatic retransmission and error handling. Best for vehicles, drones, robots.
> - **RS-485** when I want a simple, long-distance, multi-drop serial link with a protocol of my choice (often Modbus RTU), and a higher bit rate at short distances. Common in industrial and building automation."

### Q300. How do you select a peripheral interface based on bandwidth, latency, pin count and reliability?

> "I list the requirements, then compare the options:
>
> - **Bandwidth**: calculate the real data rate plus 30-50 % margin. A few bytes per second: anything works. MB/s: SPI, USB or Ethernet.
> - **Latency**: must data arrive within microseconds (SPI, a direct interrupt) or is 10 ms fine (I2C, UART, BLE)?
> - **Pin count**: I2C uses 2 pins for many devices, SPI needs more and one CS each, parallel interfaces need many.
> - **Reliability**: does the protocol confirm delivery (I2C ACK, CAN ACK + CRC, TCP)? Is it robust to noise?
> - **Distance and topology**: on-board, between boards, or long cables; point-to-point or bus.
> - **What the other chip supports**, and what my MCU has free.
>
> For example, an IMU at 1 kHz with tight timing: SPI. A slow temperature sensor: I2C. Two boards 5 m apart in a machine: CAN."

### Q301. What is your experience with schematic design and review?

*(Adapt this to your own experience.)*

> "I'm not a full-time hardware designer, but I **review schematics** for every board my firmware runs on, and I've designed small MCU sections. In reviews, I check the MCU's pin assignments against what the firmware needs, the pin-mux conflicts, power and decoupling, boot and reset circuits, the debug connector, crystals and load capacitors, I2C pull-ups and addresses, and level shifting. I use the datasheet and CubeMX side by side, and catching a wrong pin in a review is much cheaper than a board re-spin."

### Q302. How do you verify that MCU pins and peripheral connections match the schematic?

> "- I make a **pin map** from the schematic: every MCU pin, its net name, and the function it needs.
> - I load it into **STM32CubeMX** (or the vendor's pin tool), which shows immediately whether each pin really supports that alternate function, and whether two peripherals clash.
> - I check the **direction and naming** of signals: TX to RX, MOSI to MOSI (or SDI), active-low chip selects and resets.
> - On the real board, I verify each pin with a **continuity test**, and in bring-up by toggling it in firmware and measuring it at the connector or the target chip."

### Q303. What would you check if firmware fails to execute on a newly manufactured PCB?

> "I'd follow the bring-up order:
>
> 1. **Power**: every rail at the right voltage, VDDA and VCAP, current consumption normal (no short).
> 2. **Reset and boot**: NRST high, BOOT0 low, so it boots from flash.
> 3. **Debugger**: can I connect? If yes, halt and read the **PC**: is it in a HardFault, an Error_Handler, or stuck waiting for the clock?
> 4. **Clock**: does the external crystal start? A missing or wrong crystal or load capacitors is the most common cause on new boards. Test by switching the firmware to the internal oscillator.
> 5. **Firmware vs hardware variant**: is it the right firmware for this board revision and this exact MCU part (flash and RAM size in the linker script)?
> 6. **Assembly**: compare with a known-good board: missing or wrong components, solder bridges, a rotated part.
>
> If a known-good board works with the same firmware, the problem is in that board's manufacturing."

---

## 13. C++ and object-oriented programming

### Q304. Are you experienced in C or C++?

*(Adapt this to your own experience.)*

> "My strongest language is **C**, which I've used for most of my firmware: drivers, RTOS applications and bootloaders. I also use **C++** for embedded work, in an embedded-friendly style: classes for drivers and interfaces, RAII for locks and resources, templates where they help, but no exceptions and no dynamic allocation after start-up. I'm comfortable moving between the two."

### Q305. What C++ work have you done?

*(Adapt this to your own experience.)*

> "I've written **device drivers as C++ classes** behind abstract interfaces, so the application works with any sensor or communication module. I've used **RAII** wrappers for mutexes and critical sections, templates for fixed-size containers and ring buffers, and `constexpr` for compile-time configuration. I've also worked on Linux user-space applications in modern C++ (C++14/17) using the STL, threads and smart pointers."

### Q306. How would you migrate C++ functionality to C, or vice versa?

> "**C++ to C**: each class becomes a **struct for the data** plus **functions that take a pointer to that struct** as their first parameter, like `sensor_read(sensor_t *self)`. Virtual functions become a **struct of function pointers** (a manual vtable). Constructors and destructors become explicit `init()` and `deinit()` functions, templates become separate functions or macros, and exceptions become return codes.
>
> **C to C++**: the opposite. Group related data and functions into a class, make the internal data private, turn `init`/`deinit` into constructor and destructor, replace function-pointer tables with virtual functions or templates.
>
> In both directions I do it **incrementally**, with tests at each step, and keep the external interface stable, maybe with an `extern "C"` wrapper, so the rest of the system doesn't break."

```c
/* C version of a C++ interface: a struct of function pointers ("manual vtable") */
typedef struct sensor sensor_t;

typedef struct
{
    bool (*init)(sensor_t *self);
    bool (*read_celsius)(sensor_t *self, float *out);
} sensor_ops_t;

struct sensor
{
    const sensor_ops_t *ops;      /* like the C++ vtable pointer          */
    uint8_t             address;  /* like the C++ private member variables */
};

/* "virtual call": whichever driver this sensor uses */
static inline bool sensor_read(sensor_t *s, float *out) { return s->ops->read_celsius(s, out); }
```

### Q307. Why is C++ important in drone development?

> "Drone software is **large and complex**: flight control, sensor fusion, navigation, communication, and support for many hardware variants. C++ helps manage that:
>
> - **Abstraction**: interfaces for sensors, motors and radios, so the same flight code runs on different hardware.
> - **Type safety and templates**: math for vectors, matrices and quaternions, with no run-time cost.
> - **Ecosystem**: the main open-source flight stacks, **PX4** and **ArduPilot**, are written in C++, and so are ROS/ROS 2 for companion computers.
> - It's still **efficient and deterministic** enough for real-time control, if written in an embedded style.
>
> So being productive in C++ means being able to work directly with those codebases."

### Q308. What are the main object-oriented programming concepts?

> "The four main ones:
>
> - **Encapsulation**: keep data and the functions that work on it together, and hide the internal details.
> - **Abstraction**: expose only what the user needs, through a clear interface.
> - **Inheritance**: a new class reuses and extends an existing one ('is-a').
> - **Polymorphism**: code written for a base interface works with any derived class, and the right implementation is chosen at run time.
>
> All four appear in the sensor example in [Q320](#q320-how-would-you-design-a-common-sensor-interface-using-c-classes)."

### Q309. What is a class and an object?

> "A **class** is a **blueprint**: it defines what data (member variables) and what behaviour (member functions) a type has. An **object** is an **instance** of that class, with its own copy of the data, in memory.
>
> For example, `Tmp117` is a class. `Tmp117 boardSensor(0x48);` and `Tmp117 batterySensor(0x49);` are two objects of that class, each with its own I2C address."

### Q310. What is encapsulation?

> "Encapsulation means **bundling the data with the functions that operate on it**, and **hiding** the internal details behind `private`. Other code can only use the public functions. For example, a UART driver class keeps its buffer and registers private, and only exposes `send()` and `receive()`. That way the internal design can change without breaking the users, and nobody can put the object into an invalid state by writing its fields directly."

### Q311. What is inheritance?

> "Inheritance lets a **derived class** take over the members of a **base class**, and add or change behaviour. It models an **'is-a'** relationship: a `Tmp117` **is a** temperature sensor. In embedded code I mostly use it to implement **interfaces**: the base class defines the functions, and each driver class implements them. I avoid deep inheritance chains; composition is usually cleaner."

### Q312. What is polymorphism?

> "Polymorphism means **one interface, many implementations**: code that calls a function through a base-class pointer or reference gets the **derived class's version**. In C++ that's done with **virtual functions**, and the decision is made at run time.
>
> In the [Q320](#q320-how-would-you-design-a-common-sensor-interface-using-c-classes) example, `averageTemperature()` calls `readCelsius()` on each sensor without knowing its type, and the TMP117 and the NTC each run their own code. There's also **compile-time polymorphism** with templates and function overloading."

### Q313. What is a constructor?

> "A constructor is a special member function that **runs automatically when an object is created**, to initialize it. It has the same name as the class and no return type. It can take parameters, and it should leave the object in a valid state. Initializing members in the **initializer list** is best."

```cpp
class Uart {
public:
    explicit Uart(uint32_t baud) : baud_(baud), rxCount_(0U) {   /* initializer list */
        /* configure the peripheral here, or in a separate init() if it can fail */
    }
private:
    uint32_t baud_;
    uint32_t rxCount_;
};

Uart debugPort(115200U);    /* constructor runs here */
```

### Q314. What is a copy constructor?

> "A copy constructor **creates a new object as a copy of an existing one**: `T(const T &other)`. It's called for `T b = a;`, and when an object is passed or returned by value. If a class owns a resource, like a pointer to a buffer, I write it to make a **deep copy**, or I **delete** it (`= delete`) if copying makes no sense, like for a hardware driver or a lock. The full explanation and example are in Q108 of the [first question file](mix_interview_questions.md)."

### Q315. What is a destructor?

> "A destructor, `~ClassName()`, **runs automatically when an object is destroyed**: when it goes out of scope, or is deleted. It releases what the object owns: memory, a mutex, a file, a peripheral. In a base class used through pointers, the destructor must be **virtual**, otherwise deleting through a base pointer skips the derived destructor."

### Q316. What is a virtual function?

> "A virtual function is a member function that a **derived class can override**, and calls through a base pointer or reference go to the **derived version** at run time. Internally, each object of a class with virtual functions has a hidden pointer to a **vtable**, a table of function addresses, and a virtual call looks up the function in that table. The cost is one extra pointer per object and one indirect call, which is small, but I avoid virtual calls in very tight loops."

### Q317. What is an abstract class?

> "An abstract class has at least one **pure virtual function**, declared with `= 0`, so it **can't be instantiated** itself. It defines an **interface**: a contract that every derived class must implement. In the [Q320](#q320-how-would-you-design-a-common-sensor-interface-using-c-classes) example, `ITemperatureSensor` is abstract: you can't create an `ITemperatureSensor`, only a `Tmp117` or an `Ntc`."

### Q318. What are RAII and resource ownership?

> "**RAII**, 'Resource Acquisition Is Initialization', means: an object **acquires a resource in its constructor**, and **releases it in its destructor**. Since C++ guarantees the destructor runs when the object goes out of scope, on **every** exit path, including early returns, the resource can never leak.
>
> **Ownership** means being clear about **which object is responsible** for releasing a resource. `std::unique_ptr` has one owner; `std::shared_ptr` shares ownership with a reference count.
>
> In embedded, I use RAII for **mutex locks** and **critical sections**: the `IrqLock` in the Q320 example turns interrupts off in its constructor and back on in its destructor, so I can't forget to re-enable them."

### Q319. What are templates and STL?

> "**Templates** let me write code **once for any type**, and the compiler generates a specific version for each type used, at compile time, with full type checking and no run-time cost. For example `clamp<T>()`, or a ring buffer `RingBuffer<uint8_t, 64>` with the size as a template parameter.
>
> The **STL** (Standard Template Library) is the set of standard templates: containers (`std::array`, `std::vector`, `std::map`), algorithms (`std::sort`, `std::find`) and utilities (`std::unique_ptr`). On an MCU I use the ones that don't allocate, like `std::array` and the algorithms, and avoid `std::vector` and `std::string` unless I give them a fixed allocator."

### Q320. How would you design a common sensor interface using C++ classes?

> "I'd define an **abstract interface class** with the operations every sensor of that kind must support, like `init()` and `readCelsius()`, all pure virtual, plus a virtual destructor. Each **driver** is a class that inherits from it and implements those functions for its own hardware. The **application** only holds pointers to the interface, so adding a new sensor model means writing one new class, and nothing else changes. The objects are created statically, so there's no heap use."

```cpp
#include <cstdint>
#include <cstdio>
#include <array>

/* ---------- Abstract interface: what every temperature sensor must provide ---------- */
class ITemperatureSensor {
public:
    virtual ~ITemperatureSensor() = default;          /* virtual destructor: safe delete via base pointer */
    virtual bool init() = 0;                          /* pure virtual: makes the class abstract */
    virtual bool readCelsius(float &out) = 0;
    virtual const char *name() const = 0;
};

/* ---------- Hardware-specific implementations (drivers) ---------- */
class Tmp117 : public ITemperatureSensor {           /* inheritance: a Tmp117 IS-A temperature sensor */
public:
    explicit Tmp117(uint8_t i2cAddress) : address_(i2cAddress) {}

    bool init() override {                            /* override: replaces the base behaviour */
        std::printf("  TMP117 init at I2C 0x%02X\n", static_cast<unsigned>(address_));
        return true;                                  /* real code: read the device ID register */
    }
    bool readCelsius(float &out) override {
        const int16_t raw = 3200;                     /* real code: I2C read of the temp register */
        out = static_cast<float>(raw) * 0.0078125f;   /* TMP117: 7.8125 m°C per LSB */
        return true;
    }
    const char *name() const override { return "TMP117"; }

private:                                              /* encapsulation: callers can't touch this */
    uint8_t address_;
};

class Ntc : public ITemperatureSensor {
public:
    explicit Ntc(uint8_t adcChannel) : channel_(adcChannel) {}

    bool init() override {
        std::printf("  NTC on ADC channel %u\n", static_cast<unsigned>(channel_));
        return true;
    }
    bool readCelsius(float &out) override {
        const uint16_t adcCount = 1948U;              /* real code: ADC conversion */
        out = 25.0f + (2048.0f - static_cast<float>(adcCount)) * 0.05f;   /* simplified curve */
        return true;
    }
    const char *name() const override { return "NTC"; }

private:
    uint8_t channel_;
};

/* ---------- RAII: the constructor takes the resource, the destructor always releases it ---------- */
class IrqLock {
public:
    IrqLock()  { std::printf("  [irq off]\n"); }     /* real code: __disable_irq() */
    ~IrqLock() { std::printf("  [irq on]\n");  }     /* runs on every exit path, even early returns */
    IrqLock(const IrqLock &) = delete;                /* a lock must not be copied */
    IrqLock &operator=(const IrqLock &) = delete;
};

/* ---------- Template: one function for any numeric type, checked at compile time ---------- */
template <typename T>
T clamp(T value, T low, T high) {
    return (value < low) ? low : ((value > high) ? high : value);
}

/* ---------- Application: knows only the interface, not the hardware ---------- */
static float averageTemperature(ITemperatureSensor *const *sensors, std::size_t count) {
    float sum = 0.0f;
    std::size_t valid = 0U;

    for (std::size_t i = 0U; i < count; i++) {
        float t = 0.0f;
        if (sensors[i]->readCelsius(t)) {            /* polymorphism: the right driver is called */
            std::printf("  %-6s = %.2f C\n", sensors[i]->name(), static_cast<double>(t));
            sum += t;
            valid++;
        }
    }
    return (valid > 0U) ? (sum / static_cast<float>(valid)) : 0.0f;
}

int main() {
    Tmp117 boardSensor(0x48U);                        /* objects of each class (static, no heap) */
    Ntc    batterySensor(3U);
    std::array<ITemperatureSensor *, 2> sensors = { &boardSensor, &batterySensor };

    std::printf("init:\n");
    for (ITemperatureSensor *s : sensors) {
        (void)s->init();
    }

    std::printf("read:\n");
    const float avg = averageTemperature(sensors.data(), sensors.size());
    std::printf("average = %.2f C\n", static_cast<double>(avg));

    std::printf("clamp(120, 0, 100) = %d, clamp(-3.5f, 0.0f, 50.0f) = %.1f\n",
                clamp(120, 0, 100), static_cast<double>(clamp(-3.5f, 0.0f, 50.0f)));

    std::printf("critical section:\n");
    {
        IrqLock lock;                                 /* interrupts off here */
        std::printf("  updating shared data\n");
    }                                                 /* lock destroyed: interrupts back on */

    return 0;
}
```

**Output:**

```text
init:
  TMP117 init at I2C 0x48
  NTC on ADC channel 3
read:
  TMP117 = 25.00 C
  NTC    = 30.00 C
average = 27.50 C
clamp(120, 0, 100) = 100, clamp(-3.5f, 0.0f, 50.0f) = 0.0
critical section:
  [irq off]
  updating shared data
  [irq on]
```

### Q321. How would you separate hardware-specific implementations from application logic?

> "With **layers and interfaces**:
>
> - The **application** contains the logic: control, state machines, protocols. It depends only on **interfaces**: `ITemperatureSensor`, `IComm`, `IStorage`.
> - The **drivers** implement those interfaces for specific chips.
> - Below them, a **HAL/BSP** wraps the MCU registers and the board's pin assignments.
> - At start-up, one small **composition** function creates the concrete drivers for this board and hands them to the application, so it's the only place that knows the exact hardware.
>
> That makes the application **portable** to new hardware, and **testable on a PC** with mock drivers."

```text
Application logic   (control, protocols)        -> uses interfaces only
   |  ITemperatureSensor, IComm, IStorage
Drivers             (Tmp117, Ntc, Esp32Wifi)     -> implement the interfaces
   |
HAL / BSP           (I2C, SPI, GPIO, pins)       -> chip and board specific
```

---

## 14. Firmware architecture and technical leadership

### Q322. How do you approach a new project after receiving the requirements?

> "1. **Understand the requirements**: read them fully, and write down questions, gaps and contradictions. Clarify them with the customer or product owner, especially the non-functional ones: timing, power, safety, cost, lifetime.
> 2. **Identify the risks**: new hardware, a new protocol, tight timing. Then do quick prototypes or spikes on those first.
> 3. **Architecture**: choose the MCU/OS, define the layers, modules, tasks and interfaces, and the data flows. Review it with the team.
> 4. **Plan**: break it into tasks with estimates and milestones, decide the test strategy, and set up the repository and CI from day one.
> 5. **Build incrementally**: get a thin end-to-end version working early, then add features, with tests and reviews along the way."

### Q323. What tools and toolchains do you use during development?

> "- **Compilers / IDEs**: GCC arm-none-eabi, STM32CubeIDE, Keil or IAR; VS Code with CMake.
> - **Code generation / config**: STM32CubeMX.
> - **Debug**: ST-LINK and J-Link probes, OpenOCD, GDB, SEGGER SystemView and RTT.
> - **Hardware tools**: oscilloscope, logic analyzer, multimeter, protocol analyzers (CAN, BLE, USB-PD).
> - **Version control and CI**: Git (GitHub/GitLab/Bitbucket), Jenkins or GitLab CI, Docker for build environments.
> - **Quality**: Unity / CppUTest for unit tests, Cppcheck, SonarQube, PC-lint or Polyspace for MISRA.
> - **Linux**: Yocto or Buildroot, the cross toolchain, and the serial console.
> - **Project tools**: Jira, Confluence."

### Q324. How do you move from requirements to architecture, implementation and release?

> "- **Requirements**: clarified, numbered, and testable. Each has an acceptance criterion.
> - **Architecture**: a block diagram, the layers, modules and interfaces, the task design and data flow, and the key decisions documented with their reasons. Reviewed with the team.
> - **Design and implementation**: per module, small steps, each with unit tests and a code review, merged through CI.
> - **Integration and verification**: integration tests on the hardware, then system tests against each requirement, with a traceability matrix linking requirements to tests.
> - **Release**: a tagged CI build, signed binaries, release notes, test reports, and handover to manufacturing or OTA.
> - **Maintenance**: field feedback, bug fixes and updates through the same process."

### Q325. How would you design modular firmware for a long-lifecycle product?

> "- **Clear layers** (HAL/BSP, drivers, middleware, application) with dependencies only going downwards.
> - **Modules with small, stable interfaces**: each module hides its internals and exposes a documented API, so I can replace it without touching the others.
> - **Hardware abstraction**, so a component that goes end-of-life can be replaced by changing one driver.
> - **Configuration in data**, not in code branches.
> - **Versioned formats** for protocols and stored data, with migration.
> - **Automated tests and CI**, so changes years later are still safe.
> - **A reliable update mechanism** (secure OTA with rollback), since the product will need updates for years.
> - **Documentation and a reproducible build environment** (Docker, pinned toolchain), so the code can still be built in 10 years."

### Q326. How would you make firmware reusable across different hardware platforms?

> "- Put all hardware access behind a **HAL interface** that I own: functions like `hal_gpio_write()`, `hal_i2c_transfer()`, `hal_timer_now()`. Each platform implements it once.
> - Put **board details** (pins, which bus each sensor is on) in a per-board **BSP** or configuration file, not inside the drivers.
> - Write device drivers against my HAL, not the vendor's, so the same sensor driver works on STM32, NXP or nRF.
> - Use an **OS abstraction** if the RTOS may change.
> - Build per platform from the **same codebase** with CMake targets, and run the same tests on each."

### Q327. How would you decide which functionality belongs in drivers, middleware or the application layer?

> "I ask: **what does this code know about?**
>
> - **Driver**: it knows about a **specific piece of hardware**: registers, a chip's commands and timing. Example: the BMI270 driver, the UART driver.
> - **Middleware**: it's **generic infrastructure**, not specific to this product: protocol stacks, file systems, a TCP/IP stack, logging, a CRC library, the RTOS.
> - **Application**: it implements **this product's features and rules**: 'if the tank is empty, stop the pump and send an alarm'.
>
> A good test: if I changed the hardware, only drivers should change. If I built a different product on the same hardware, only the application should change."

### Q328. How would you separate hardware-dependent and hardware-independent code?

> "- Keep **hardware-dependent code** in clearly marked folders, like `hal/`, `bsp/`, `drivers/`, and nowhere else.
> - The **hardware-independent** code (application logic, algorithms, protocols) **never includes** vendor headers or touches registers; it only calls my interfaces.
> - I enforce that in the build: the independent code is compiled and **unit-tested on the PC**, which is impossible if it accidentally depends on hardware.
> - Where the dependency is through function pointers or interfaces, I can swap in mocks for testing."

```text
src/
  app/          hardware-independent: logic, state machines  (builds and tests on the PC)
  middleware/   hardware-independent: protocols, CRC, logging
  drivers/      chip-specific drivers, using the HAL API
  hal/stm32f4/  MCU-specific HAL implementation
  bsp/board_v2/ pin assignments, which device is on which bus
```

### Q329. How would you support different customer configurations?

> "One firmware, with configuration as data (see [Q221](#q221-how-would-you-support-customer-specific-product-configurations-without-maintaining-separate-firmware-branches)):
>
> - A **configuration record** in flash, written in production or provisioned from the cloud, with a version and a CRC, that enables features and sets parameters.
> - **Feature flags** checked at run time, and a variant ID read at boot.
> - If needed, **build-time options** from the same branch, built and tested by CI for each variant.
> - The configuration is **validated** at boot, and the device falls back to safe defaults if it's invalid."

### Q330. How would you design a system that scales from a single device to a large installation with many connected devices?

> "- **Unique identity per device**: a serial number and its own credentials, provisioned in production. Nothing hard-coded per installation.
> - **Hierarchical organisation**: devices grouped by site or zone, reflected in topic names or addresses, so adding a site is just provisioning.
> - **Local gateways or edge controllers** for each installation, so local control works without the cloud, and the cloud traffic stays manageable.
> - **Asynchronous messaging** (MQTT), so devices don't depend on each other directly.
> - **Device management**: remote configuration, monitoring and staged OTA updates for thousands of devices.
> - Test with **simulated devices** at the target scale before deployment."

### Q331. How would you ensure security, maintainability and backward compatibility?

> "- **Security**: secure boot and signed updates, encrypted and authenticated communication (TLS with device certificates), locked debug ports in production, least-privilege access, input validation, and a process to respond to vulnerabilities.
> - **Maintainability**: a clear modular architecture, coding standards, code reviews, automated tests and CI, and good documentation.
> - **Backward compatibility**: versioned protocols and data formats, only adding fields, migration of stored data, and regression tests against older versions of the app and server (see [Q222](#q222-how-would-you-maintain-backward-compatibility-across-a-product-lifetime-of-five-to-ten-years))."

### Q332. How would you collaborate with Embedded Linux, HMI, AI/ML, MATLAB and validation teams?

> "- **Agree on interfaces early**: a written **interface control document** for every boundary: the messages between the MCU and the Linux board, the data the HMI shows, the model's input format, and the parameters from the MATLAB models. With versions.
> - **Shared tools**: simulators or mock devices, so each team can work before the hardware is ready. For example, a PC tool that emulates my firmware's protocol for the HMI team.
> - **MATLAB**: turn their algorithm into firmware, either by generated code or by hand, and verify it with the **same test vectors** they use, comparing outputs.
> - **Validation**: involve them from the requirements stage, so every requirement is testable, and give them debug and logging tools.
> - **Regular syncs** and a shared issue tracker, so problems at the boundaries surface early."

### Q333. How would you clarify requirements directly with a customer?

> "- Prepare first: read everything, and list **specific questions**, not 'tell me more'.
> - Ask about **the use case** and the **why**, not just the feature: what problem are they solving, in what environment?
> - Turn vague words into **numbers**: 'fast' becomes 'response within 100 ms', 'long battery life' becomes '2 years with 10 measurements per hour'.
> - Talk about **edge cases and failures**: what should happen if the network is down, or the sensor fails?
> - **Summarise in writing** after the meeting, with the agreed requirements and the open points, and get confirmation.
> - Show **early prototypes or demos** to check we understood correctly."

### Q334. How would you manage a feature from requirements through production delivery?

> "1. **Requirements**: clarified with the stakeholders, written with acceptance criteria.
> 2. **Design**: a short design note, reviewed, covering the interfaces, risks and test plan.
> 3. **Plan**: split into tasks, estimated, in the sprint or project plan.
> 4. **Implement**: in a feature branch, with unit tests and code reviews, merged through CI.
> 5. **Verify**: integration and system tests on real hardware, plus regression tests.
> 6. **Release**: included in a tagged release, with release notes and documentation updated.
> 7. **Deliver**: to manufacturing or by OTA, with a staged rollout.
> 8. **Follow up**: monitor field data and feedback, and fix issues.
>
> Throughout, I keep the status visible and raise risks early."

### Q335. How would you divide work between yourself and a junior engineer?

> "I'd take the **riskiest and most architectural** parts myself: the overall design, tricky concurrency, the bootloader or security, or a new protocol. I'd give the junior **well-defined, self-contained** tasks with clear interfaces and acceptance criteria, like a specific sensor driver, a test tool, or a feature in an existing module, and something slightly beyond their current level, so they grow.
>
> I'd make sure they understand the **why** and the context, agree on check-in points, review their design before they code, and stay available for questions. Over time I'd give them bigger pieces."

### Q336. How would you review, test and validate a junior engineer's implementation?

> "- **Before coding**, review their **design approach** briefly, so they don't spend a week in the wrong direction.
> - **Code review**: check correctness, error handling, concurrency and readability, and explain the reasons in my comments, so it's a learning opportunity, not just corrections.
> - Ask them to **show their tests**, and test the edge cases together.
> - **Pair** on difficult bugs, and let them drive.
> - Validate on the **real hardware** together, with the instruments, before it's merged.
> - Give **positive feedback** too, and gradually reduce how closely I review as they gain experience."

### Q337. How would you balance hands-on coding with technical leadership?

> "I'd stay hands-on, but on the **right things**: the critical, architectural or risky parts, prototypes, and code reviews, rather than taking every feature myself. Leadership work, like unblocking people, design reviews, planning and talking to stakeholders, comes first, because if I block the team by coding, the whole project slows down.
>
> In practice, I'd reserve focused blocks of time for coding, avoid putting myself on the critical path for long tasks, and delegate with clear ownership. Staying technical keeps my reviews and decisions credible."

### Q338. How would you resolve disagreements between firmware, hardware and validation teams?

> "- **Focus on the data, not opinions**: reproduce the problem, measure it, and look at the evidence together. A scope capture or a log usually settles 'is it hardware or firmware?'.
> - **Go back to the requirement**: what does the product actually need? That often turns a disagreement into a shared problem.
> - **Listen** to each side's constraints. A hardware fix might be impossible for this batch, while a firmware workaround is quick, or the other way around.
> - **Decide** by the impact on the product and the customer, and **write down** the decision and the reason.
> - If it can't be resolved, **escalate** with the options and trade-offs clearly laid out, without blaming anyone."

### Q339. How would you handle an urgent customer issue?

> "1. **Respond quickly**: acknowledge the issue and set expectations for the next update.
> 2. **Understand the impact**: what fails, how many units, is it a safety issue, is there a workaround?
> 3. **Mitigate first** if possible: a workaround, a configuration change, holding back an update.
> 4. **Get the data**: logs, versions, a failed unit, and reproduce it.
> 5. **Fix** with the right urgency, but still with review and tests, because a rushed fix that breaks something else is worse.
> 6. **Communicate** regularly with the customer and internally.
> 7. After it's solved, do a **root-cause analysis** and prevent it from happening again."

### Q340. Why should we hire you for a technical lead role when you have limited direct drone experience?

*(Adapt this to your own background.)*

> "Because the core of a drone is exactly the work I do every day: **real-time embedded systems** on MCUs with an RTOS, **sensors** over I2C and SPI, **communication** (CAN, UART, BLE, Ethernet), **power and battery management**, **bootloaders and OTA**, and bringing up and debugging new hardware. Those skills transfer directly.
>
> What's drone-specific, like flight control concepts, PX4/ArduPilot, and the regulations, I can learn quickly, and I've already started. And for a lead role, what matters most is designing a solid architecture, making good technical decisions, raising quality with reviews and testing, and growing the team, which I've done in my current role. I'd bring a strong embedded foundation and learn the domain fast."

### Q341. What is your strongest technical skill?

*(Adapt this to yourself.)*

> "I'd say **embedded system design and debugging at the hardware-software boundary**. I'm comfortable going from a requirement down to the registers: designing the firmware architecture, writing drivers and RTOS applications, and, when something goes wrong, finding the root cause with a debugger, a scope and a logic analyzer, whether it's in the firmware, the hardware or the timing between them."

### Q342. What is your biggest professional achievement?

*(Use a real example, with the situation, what you did, and the measurable result.)*

> "In my last project, our devices in the field had a failure where some units stopped responding after a few days. It was hard to reproduce. I added crash logging with fault registers, collected the data from field units, and traced it to a race condition between an ISR and a task updating a shared buffer index. I fixed it, added a regression test, and improved our review checklist for shared data. After the update, the field failures dropped to zero, and the logging I added became standard in all our products."

### Q343. Are you comfortable owning the complete electronics and firmware segment?

> "Yes. I'm comfortable taking **end-to-end ownership**: the firmware architecture and implementation, working closely with the hardware design (reviewing schematics, bring-up, debugging), the test strategy, and the release process. Where I'm not the deepest expert, like detailed analog or RF design, I'll make sure the right people are involved, but I'd own the outcome: that the electronics and firmware work together and meet the requirements."

### Q344. What questions would you ask the interviewer about the team, product architecture and responsibilities?

> "For example:
>
> - How big is the team, and how is it split between firmware, hardware, software and validation? Who would I lead directly?
> - What does the current architecture look like: which MCUs and processors, RTOS or Linux, which flight stack?
> - What's the biggest technical challenge or risk in the product right now?
> - What does success look like for this role in the first 6 to 12 months?
> - What's the development process: code reviews, CI, testing, hardware-in-the-loop?
> - How much of the role is hands-on coding versus leadership and coordination?
> - How do you handle certification and safety requirements?"

---

## 15. Additional interview questions and scenarios

### Q345. A task is producing data and another task is consuming it. Which synchronization mechanism would you use?

> "A **queue**. It carries the data and does the synchronization in one object: the consumer sleeps in `xQueueReceive()` until data arrives, the producer blocks or gets an error if the queue is full, and the data is copied, so nothing is shared. For large items, I queue pointers into a static buffer pool. The code is in [Q95](#q95-how-do-you-transfer-data-between-producer-and-consumer-tasks).
>
> If the consumer only needs to know that 'something happened', a task notification or a semaphore is enough. For a byte stream, a stream buffer."

### Q346. A UART receives data continuously from a Wi-Fi module. How would you avoid losing characters?

> "Byte-by-byte interrupts work at low speed, but at 115200 baud or more, with other interrupts and tasks running, it's easy to miss a byte. So I'd use:
>
> - **DMA in circular mode** into a ring buffer: the hardware stores every byte, even if the CPU is busy.
> - The UART's **IDLE-line interrupt** (plus the DMA half- and full-transfer interrupts) to know when a burst has ended, so I can process data without waiting for a fixed length.
> - A **task** that reads from the DMA buffer, using the DMA's remaining-count register to know how far it has written, and parses the AT responses or packets.
> - A buffer **big enough** for the longest burst plus the worst-case processing delay.
> - **Hardware flow control (RTS/CTS)** if the module supports it, so the module pauses when we're not ready.
> - **Overrun error** detection, counted and logged, so a loss is never silent."

```c
#define RX_BUF_SIZE  (1024U)
static uint8_t  s_rx_buf[RX_BUF_SIZE];          /* DMA writes here in circular mode */
static uint32_t s_read_pos = 0U;                 /* how far the task has processed  */

void wifi_uart_start(void)
{
    HAL_UART_Receive_DMA(&huart2, s_rx_buf, RX_BUF_SIZE);   /* circular DMA, never stops */
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);            /* interrupt when the line goes quiet */
}

/* Called from the task when woken by the IDLE / half / complete interrupt */
void wifi_uart_process(void)
{
    /* DMA write position = buffer size minus what the DMA still has to transfer */
    uint32_t write_pos = RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart2.hdmarx);

    while (s_read_pos != write_pos)
    {
        parser_feed(s_rx_buf[s_read_pos]);                  /* hand each new byte to the parser */
        s_read_pos = (s_read_pos + 1U) % RX_BUF_SIZE;       /* wrap around like the DMA does    */
    }
}
```

### Q347. How would you design an interrupt-safe, RTOS-safe circular buffer?

> "I start from the ring buffer in [Q48](#q48-implement-a-circular-buffer-with-put-and-get-apis), and then decide based on **who uses it**:
>
> - **One ISR producer, one task consumer**: lock-free. Only the ISR writes `head`, only the task writes `tail`, the indexes are `volatile` and 32-bit (atomic), data is written before the index is updated, and one slot stays empty. Add a `__DMB()` barrier on multicore systems ([Q52](#q52-how-would-you-make-a-circular-buffer-safe-for-an-isr-producer-and-task-consumer)).
> - **Several tasks** on the same side: a **mutex** around `Put()` or `Get()` ([Q53](#q53-how-would-you-protect-a-circular-buffer-if-multiple-tasks-call-get-concurrently)).
> - **An ISR and several tasks** on the same side: a short **critical section**, because an ISR can't take a mutex.
> - **Waking the consumer**: after `Put()` in the ISR, a task notification with `vTaskNotifyGiveFromISR()`, so the consumer sleeps instead of polling.
> - **Overflow**: `Put()` returns an error and counts it ([Q56](#q56-how-would-you-handle-buffer-overflow-without-silently-losing-unread-data)).
>
> In FreeRTOS, a **stream buffer** gives exactly this for one writer and one reader, so I often just use that."

### Q348. Multiple tasks call the same Get() API. What race conditions can occur?

> "Without protection:
>
> - **The same item is returned twice**: both tasks read the same `tail`, both get the same byte, both increment.
> - **An item is skipped**: both read `tail = 5`, both write `tail = 6`, so one increment is lost, or, depending on timing, `tail` jumps by two and an item is never read.
> - **Reading an empty buffer**: both check 'not empty' when there's one item, then both take it, and the second reads stale data and moves `tail` past `head`, so the buffer state becomes corrupted.
>
> The fix is to make check, read and advance **one atomic step**: a mutex, a critical section, or an RTOS queue."

```text
Task A: reads tail = 5          Task B (preempts A): reads tail = 5, gets data[5], writes tail = 6
Task A: gets data[5] (again!), writes tail = 6        -> data[5] returned twice, both thought they took a new item
```

### Q349. One task is interrupted while updating the circular-buffer index. What can happen?

> "It depends on what the update looks like:
>
> - If the index update is a **read-modify-write** (`count++`, or computing a new index from the old one) and another context changes it in between, **one update is lost**: the buffer then thinks it has more or fewer items than it really has. Data gets overwritten or read twice.
> - If the index is **wider than the CPU's word**, for example a 32-bit index on an 8-bit or 16-bit MCU, the interrupt can see a **half-written value**: a completely wrong index.
> - If the index is updated **before** the data is written, the other side can read a slot that doesn't contain the new data yet.
>
> That's why only one side writes each index, the index is a native atomic size, the data is written before the index, and anything shared by both sides is protected with a critical section."

### Q350. How would you decide whether a critical section, mutex, semaphore or queue is appropriate?

| Situation | Use | Why |
| --- | --- | --- |
| A few lines shared with an **ISR** | Critical section | ISRs can't use a mutex; very short |
| A resource used by **several tasks** for a longer time (I2C bus, flash) | Mutex | Only waiting tasks block; priority inheritance |
| **Signal** an event (ISR → task, task → task) | Binary semaphore or task notification | No data, just 'it happened' |
| **Count** events or free resources | Counting semaphore | Remembers how many |
| **Send data** between tasks or from an ISR | Queue (or stream buffer) | Data and synchronization in one |
| Wait for **several conditions** | Event group | Wait for any or all bits |

> "My questions are: is an ISR involved? Do I need to pass data, or only a signal? How long is the protected code? And is it about protecting a resource, or signaling?"

### Q351. A production device crashes after release. What is your immediate response?

> "First **contain** it: find out how many devices are affected and whether it's a safety issue, and **stop the rollout** of that firmware version if it's going out by OTA. Then collect the crash data (fault registers, PC/LR, logs) and the conditions, inform the stakeholders, and start reproducing it. If there's a quick mitigation, like rolling back to the previous version, I do that while working on the real fix. The full process is in [Q257](#q257-what-is-your-process-when-production-firmware-crashes)."

### Q352. A USB-PD device produces multiple interrupts during attachment. How would you handle them?

> "That's contact bounce on plug-in. I keep the ISR minimal (just notify the PD task), read the **current status** in the task instead of acting on every interrupt, **debounce** the attach state for the specified tCCDebounce time, and make the state machine **ignore repeated or stale events**. The details and the code are in [Q162](#q162-how-do-you-handle-multiple-attachdetach-interrupts) and [Q163](#q163-how-do-you-prevent-repeated-state-transitions-caused-by-multiple-interrupts)."

### Q353. Some chargers negotiate successfully while others fail. How would you diagnose the issue?

> "1. **Collect the facts**: which chargers fail, which work, and what they have in common: PD version (2.0 or 3.0), the PDOs they offer, PPS support.
> 2. **Capture the CC traffic** with a **USB-PD analyzer** for one working and one failing charger, and compare them message by message. Where does it diverge: no Source_Capabilities, a Reject, a missing PS_RDY, a timeout, a hard reset?
> 3. Check my side: is my **Request valid** for that charger's PDOs (the current not above the PDO's maximum)? Do I respond **within the required time**? Do I handle messages I don't expect, like Get_Sink_Cap, or PD 3.0 extended messages?
> 4. Check the **hardware**: the CC lines, VBUS sensing and the inrush current when the voltage rises.
> 5. Fix, then build a **test matrix** of many chargers into the regression tests.
>
> More in [Q161](#q161-how-do-you-handle-negotiation-failures-with-different-chargers)."

### Q354. A new firmware image is downloaded, but the device loses power before activation. What should happen?

> "Nothing bad. The new image is complete in the **inactive slot**, but the metadata still points to the **old slot**, because activation hadn't happened yet. So after power returns, the device **boots the old firmware** normally.
>
> Then, either the device **re-verifies** the downloaded image (its CRC and signature) and continues the activation, or, if the metadata write was interrupted, the bootloader finds one valid metadata copy (that's why there are two) and uses it. Either way, the device always has a working image. See [Q235](#q235-what-happens-if-power-fails-during-a-firmware-update)."

### Q355. An MCU does not have a supported FreeRTOS port or a dedicated system timer. How would you proceed?

> "First I check whether a port exists for the **CPU core and compiler**, because ports are per core, not per chip. If there's none, I write one based on the closest existing port: stack initialization, starting the first task, the context switch, the critical-section and yield macros ([Q100](#q100-how-would-you-port-freertos-to-an-mcu-that-has-no-existing-freertos-port), [Q101](#q101-what-low-level-components-must-be-implemented-in-a-new-rtos-port)).
>
> For the tick, I use **any general-purpose timer** in periodic mode, at the lowest interrupt priority, and call `xTaskIncrementTick()` from its ISR ([Q103](#q103-how-would-you-generate-the-rtos-tick-using-another-hardware-timer)). Then I validate it step by step ([Q104](#q104-how-would-you-validate-a-newly-ported-rtos))."

### Q356. A new board cannot be programmed. What is your board-bring-up checklist?

> "1. **Power**: all rails correct, no short, normal current, VDDA connected.
> 2. **Debug connection**: SWDIO, SWCLK, GND and VTref wired correctly, short cable, the right connector pinout.
> 3. **Reset**: NRST not held low; try 'connect under reset'.
> 4. **Boot pins**: BOOT0 in the right state.
> 5. **Part and assembly**: the right MCU, soldered correctly, no bridges.
> 6. **Locked chip**: RDP protection, or old firmware disabling SWD, so use connect under reset, or a mass erase.
> 7. **Tools**: probe firmware, the right target selected, lower SWD clock.
>
> Then the full bring-up sequence in [Q286](#q286-what-steps-do-you-follow-for-board-bring-up), with details in [Q287](#q287-what-do-you-check-if-the-mcu-cannot-be-programmed)."

### Q357. The ADC needs to capture high-frequency samples continuously. How would you select and configure DMA?

> "- **Trigger the ADC from a timer**, not from software, so the sample rate is exact and doesn't depend on the CPU.
> - **Choose a DMA stream/channel** that's connected to that ADC (it's fixed in the reference manual's DMA request table), and give it **high priority**, so other DMA traffic doesn't delay it.
> - Configure: peripheral-to-memory, **circular mode**, half-word data size for a 12-bit ADC, memory increment on, peripheral increment off.
> - Use the **half-transfer and transfer-complete interrupts** for double buffering, and size the buffer so each half covers enough processing time.
> - On a cache-enabled core, put the buffer in **non-cacheable** memory, or invalidate it before reading.
> - Check the **bandwidth**: the sample rate times the sample size, against the bus capacity and other DMA users.
>
> The implementation is in [Q122](#q122-how-would-you-implement-continuous-adc-acquisition-using-dma)."

### Q358. You must transmit a large volume of sensor data to an SBC. How would you manage buffering and communication?

> "- **Choose the link by bandwidth** (with margin): SPI with DMA, USB (CDC or vendor bulk), or Ethernet ([Q144](#q144-how-would-you-transfer-high-speed-sensor-or-camera-data-to-an-sbc)).
> - **Double or multi-buffering** on the MCU: the sensors fill one buffer with DMA while the previous one is being sent.
> - **Packetize** the data: a header with a sequence number, a timestamp and a length, plus a CRC, so the SBC can detect loss, reorder and validate.
> - **Flow control**: the SBC acknowledges or signals 'ready', and if it falls behind, the MCU buffers, and drops by a defined policy only when it must, counting the drops.
> - Make the SBC side efficient too: a dedicated receive thread, large reads, no processing in the receive path.
> - Measure the end-to-end throughput and the worst-case latency under full load."

### Q359. A display is located on a separate PCB. Which interface would you choose and why?

> "It depends on the display type and the cable length:
>
> - **A text or small OLED display, short cable** (under about 20 cm): **I2C at 100 kHz** or SPI, with good grounding.
> - **A graphics display needing high bandwidth**: **SPI** with a short, shielded cable and series resistors, or a dedicated display interface (MIPI DSI, LVDS) for large screens.
> - **A long cable or a noisy environment**: a small MCU on the display board, driving the display locally, connected to the main board over **RS-485 or CAN**, or differential I2C buffers.
>
> See [Q126](#q126-would-you-still-use-i2c-if-the-display-is-on-a-separate-pcb) and [Q297](#q297-what-changes-if-the-display-is-on-a-separate-pcb)."

### Q360. The existing radio module must be replaced with a different vendor's module. How would you minimize application changes?

> "By putting the radio behind an **interface** that the application uses, so only the driver changes:
>
> - Define a small, generic API: `radio_init()`, `radio_connect()`, `radio_send()`, `radio_receive()`, plus callbacks for events like 'connected' and 'data received'. No vendor types or AT commands appear in it.
> - Move all **vendor-specific code** (AT commands, the vendor SDK, timing quirks) into a driver behind that interface.
> - For the new module, write a **new driver** implementing the same interface, and select it at build time or by a hardware ID at boot.
> - Run the **same application tests** against both drivers.
>
> If the old code wasn't structured this way, the first step is to refactor it into this interface, using the old module, before adding the new one."

```c
/* radio.h: what the application sees (no vendor details) */
typedef struct
{
    int32_t (*init)(void);
    int32_t (*connect)(const char *ssid, const char *password);
    int32_t (*send)(const uint8_t *data, size_t len);
    void    (*set_rx_callback)(void (*cb)(const uint8_t *data, size_t len));
} radio_driver_t;

extern const radio_driver_t esp32_at_driver;     /* old module: AT commands over UART */
extern const radio_driver_t vendorx_sdk_driver;  /* new module: vendor SDK over SPI   */

/* The application only ever uses this pointer, chosen once at start-up */
static const radio_driver_t *s_radio = &vendorx_sdk_driver;
```

### Q361. You need to support several drone variants with different sensors. How would you structure the drivers and application?

> "- **Sensor interfaces** by type: `IImu`, `IBarometer`, `IMagnetometer`, `IGps`. The flight code only uses these interfaces.
> - **Drivers** for each specific part (BMI088, ICM-42688, BMP388 ...) implement those interfaces.
> - A **board/variant configuration** describes which sensors each variant has, on which bus, with which orientation and calibration. It's chosen at boot from a hardware ID or a stored parameter.
> - A **factory or registry** at start-up creates the right drivers for that variant, and probes them (reads their ID registers) to confirm they're present.
> - The **application** handles optional sensors gracefully: for example, if there's no GPS, position-hold modes are disabled.
>
> That's very close to how PX4 and ArduPilot handle different flight controllers."

### Q362. How would you validate the complete embedded system on real drone hardware?

> "Step by step, from safe to real:
>
> 1. **Bench tests** without propellers: every sensor reads correctly, the motors respond to commands, failsafes trigger (signal loss, low battery), logging works.
> 2. **Hardware-in-the-loop** with a flight simulator: the real flight controller runs against a simulated vehicle, to test control logic and failure cases safely.
> 3. **Tethered or constrained flights**, then short, low, controlled flights in a safe area.
> 4. **Progressive flight tests**: hover, then manoeuvres, wind, payload, long endurance, with **flight logs** recorded and analysed after each one.
> 5. **Environmental and stress tests**: temperature, vibration, EMI from the motors, radio range.
> 6. **Fault injection**: sensor failures, link loss, GPS loss, a low-battery return-to-home.
>
> Each test has pass/fail criteria tied to the requirements, and everything is logged for traceability."

### Q363. How would you diagnose timing, memory, concurrency and communication failures during integration?

> "- **Timing**: toggle GPIOs and measure with a logic analyzer; use the DWT cycle counter; use a trace tool like SEGGER SystemView or Tracealyzer to see every task switch and interrupt, and find who is blocking whom.
> - **Memory**: check stack high-water marks for every task, enable stack-overflow checking, put a guard region or canary below each stack, check the heap's minimum free size, and use the map file. Use watchpoints to catch memory corruption at the exact instruction.
> - **Concurrency**: look for shared data without protection, check lock order for deadlocks, use the trace to see the sequence of events, and stress the system to make races appear more often.
> - **Communication**: capture the bus with a logic analyzer or protocol analyzer (CAN, I2C, SPI, BLE sniffer, Wireshark for Ethernet), log every message with timestamps and error counters, and compare with the protocol specification.
>
> In all cases: reproduce, isolate by removing parts, and measure rather than guess."

---

## 16. General technical questions

### Q364. How long have you worked at Capgemini?

*(Fill in your real details; example structure:)*

> "I've been at Capgemini for **[X years]**, since **[month, year]**, working as an embedded software engineer on **[domain: for example, railway and industrial embedded systems]**. Over that time I've worked on **[main projects: for example, Ethernet-based data acquisition, USB-PD and battery management, BLE devices]**, and my responsibilities grew from implementing drivers to owning complete firmware modules and reviewing others' code."

### Q365. What is your experience with Wi-Fi and BLE?

*(Adapt this to your own experience.)*

> "**BLE**: I've built peripherals with custom GATT services for control and status, handled advertising, connections, MTU and notifications, and worked at the HCI level with a separate controller (see [Q179](#q179-what-is-your-experience-with-bluetooth-and-ble)).
>
> **Wi-Fi**: I've integrated Wi-Fi modules (like the ESP32 or similar) with a host MCU, over UART with AT commands or over SPI with the vendor SDK, including connecting to an access point, reconnection handling, TCP sockets, and MQTT over TLS to the cloud. I've also handled provisioning, where the user enters the Wi-Fi credentials through BLE from a phone app."

### Q366. How does TCP/IP communication work?

> "Data goes down the stack on the sender and back up on the receiver:
>
> 1. The **application** writes data to a **socket**.
> 2. **TCP** splits it into **segments**, adds the source and destination **ports** and a **sequence number**. Before any data, the two sides do a **three-way handshake**: SYN, SYN-ACK, ACK. The receiver **acknowledges** what it got, and the sender **retransmits** anything that isn't acknowledged in time. A sliding **window** controls how much can be in flight.
> 3. **IP** adds the source and destination **IP addresses** and routes the packet, through routers, to the destination network.
> 4. The **link layer**, like Ethernet or Wi-Fi, delivers it hop by hop, using MAC addresses found with ARP.
> 5. On the receiver, each layer removes its header, TCP puts the segments back **in order**, and the application reads a reliable byte stream.
>
> The connection is closed with FIN and ACK from both sides."

```text
Client                         Server
  | --- SYN (seq=x) ---------->  |
  | <-- SYN-ACK (seq=y, ack=x+1) |    3-way handshake
  | --- ACK (ack=y+1) -------->  |
  | --- data (seq=x+1) ------->  |
  | <-- ACK ------------------   |    lost data is retransmitted
```

### Q367. What is inter-process communication (IPC)?

> "IPC means the **mechanisms that let separate tasks or processes exchange data and synchronize** with each other, because they can't safely just share variables. Examples are queues, pipes, message queues, shared memory with semaphores, sockets and signals. In an RTOS, the same idea applies between tasks: queues, semaphores, mutexes, event groups and notifications ([Q96](#q96-which-ipc-mechanisms-have-you-used))."

### Q368. What is the difference between task-to-task IPC and process-to-process IPC?

> "The difference comes from **memory**:
>
> - **RTOS tasks** (like FreeRTOS on an MCU) all run in the **same address space**: any task can access any global variable. So IPC is lightweight: queues, semaphores, notifications, or even shared variables with protection. It's fast, but there's no protection if one task corrupts another's data.
> - **Linux processes** each have their **own virtual address space**, isolated by the MMU. One process can't see another's memory. So IPC has to go **through the kernel**: pipes, message queues, sockets, signals, or **shared memory** that's explicitly mapped into both. It's safer, but each exchange costs more.
>
> Linux **threads** inside one process share memory, like RTOS tasks."

### Q369. What are the four traditional C storage-class specifiers?

> "**`auto`**, **`register`**, **`static`** and **`extern`**. (`typedef` is grammatically a storage-class specifier too, and C11 added `_Thread_local`.) The table with where each lives, how long, and who can see it is in [Q9](#q9-what-are-the-storage-classes-in-c), and the differences in [Q10](#q10-what-is-the-difference-between-auto-register-static-and-extern)."

### Q370. Why do we use a static variable when a local variable could also hold a value?

> "Because a normal local variable **only lives while the function runs**: it's on the stack and is lost when the function returns, so it can't remember anything between calls. A **static** local keeps its value **between calls**, while still being visible only inside that function.
>
> I use it for things like a call counter, a 'first call' init flag, a state machine's state, or a filter's previous value. A global would also keep the value, but then every other function could change it. See [Q6](#q6-what-does-the-static-keyword-do-inside-a-function)."

```c
uint32_t moving_average(uint32_t sample)
{
    static uint32_t s_avg = 0U;              /* remembers the previous average between calls */
    s_avg = (s_avg * 7U + sample) / 8U;      /* a normal local would restart at 0 every call */
    return s_avg;
}
```

### Q371. What happens when an uninitialized local pointer is dereferenced?

> "It's **undefined behaviour**. The pointer contains whatever value was on the stack, a random address. Depending on that value:
>
> - It points into **valid RAM**, so a read returns garbage, and a **write silently corrupts** some other variable or the stack, and the crash happens much later, somewhere unrelated. This is the worst case.
> - It points to an **invalid or protected address**, so the CPU raises a **HardFault** (or a segmentation fault on Linux).
>
> The fix is to always initialize pointers, to `NULL` if there's nothing valid yet, and check them before use. See [Q28](#q28-what-are-the-risks-of-uninitialized-local-variables-and-pointers)."

### Q372. What happens when a signed integer is assigned to a uint32_t?

> "The value is converted modulo 2³². A non-negative value stays the same. A negative value becomes `2³² + value`: for example, −1 becomes `4294967295` (`0xFFFFFFFF`), and −5 becomes `4294967291`. In practice the two's-complement bit pattern is kept and just read as unsigned. See [Q14](#q14-what-happens-when-a-signed-integer-is-assigned-to-an-unsigned-integer)."

### Q373. How do you calculate the output count of an ADC?

> "**count = Vin / Vref × (2ᴺ − 1)**, where N is the ADC resolution in bits. The result is rounded to an integer, and limited to 0 to 2ᴺ − 1. For example, a 12-bit ADC with Vref = 3.3 V and Vin = 1.65 V gives 1.65 / 3.3 × 4095 ≈ **2048**. Some datasheets use 2ᴺ instead of 2ᴺ − 1. Going back: **Vin = count × Vref / (2ᴺ − 1)**. A worked example with code is in [Q61](#q61-what-is-the-digital-adc-count-for-a-13-bit-adc-with-a-33-v-reference-and-a-16-v-input)."

### Q374. What is the difference between a binary semaphore and a counting semaphore?

> "A binary semaphore is only 0 or 1, so several gives before a take collapse into one. A counting semaphore counts up to N, so it remembers every give, or tracks how many resources are free. See [Q89](#q89-what-is-the-difference-between-binary-and-counting-semaphores) and the scenarios in [Q90](#q90-give-suitable-scenarios-for-binary-and-counting-semaphores)."

### Q375. What is the difference between a mutex and a semaphore?

> "A **mutex** protects a shared resource: it has an **owner**, only the owner can release it, and it has **priority inheritance**. A **semaphore** is for **signaling or counting**: no owner, and it can be given from an ISR. See [Q91](#q91-what-is-the-difference-between-a-semaphore-and-a-mutex)."

### Q376. How does the FreeRTOS scheduler know which task should execute next?

> "It keeps a **ready list for each priority**, and always runs the task at the **highest priority that has a ready task**. On Cortex-M it finds that priority very quickly with a bitmap and the **CLZ** (count leading zeros) instruction. Tasks at the same priority take turns in round-robin at each tick, if time slicing is on. Blocked and suspended tasks aren't in the ready lists at all. The decision is made at every tick, and whenever a task blocks, unblocks or changes priority. See [Q77](#q77-how-does-the-cpu-know-when-task-a-should-be-replaced-by-task-b) and [Q78](#q78-what-is-the-role-of-the-scheduler-during-context-switching)."

### Q377. What happens internally when the CPU switches from one task to another?

> "On Cortex-M with FreeRTOS:
>
> 1. An event (the tick, an ISR, or a blocking call) makes the scheduler decide to switch, and it **pends PendSV**.
> 2. When PendSV runs, the hardware has already saved R0-R3, R12, LR, PC and xPSR of the current task on its stack.
> 3. PendSV saves **R4-R11** (and S16-S31 if the FPU was used) on the same stack, and stores the stack pointer (PSP) in the current task's **TCB**.
> 4. It calls the scheduler to pick the next task, which updates `pxCurrentTCB`.
> 5. It loads the new task's **PSP** from its TCB, and pops its R4-R11.
> 6. It returns from the exception, and the hardware pops the new task's R0-R3, R12, LR, PC and xPSR, so the new task **continues exactly where it stopped**.
>
> See [Q71](#q71-what-is-context-switching) to [Q75](#q75-which-additional-registers-does-freertos-save)."

### Q378. How does a function pointer differ from a normal pointer?

> "A **normal (data) pointer** holds the address of **data** in RAM or flash, and I dereference it to read or write that data: `*p = 5`. A **function pointer** holds the address of **code**, an instruction in flash, and I dereference it to **call** the function: `fp(3, 4)`.
>
> Some practical differences:
>
> - Pointer arithmetic (`fp + 1`) isn't allowed on function pointers.
> - You can't convert a function pointer to `void *` in standard C, because code and data addresses may be different sizes on some architectures.
> - On Cortex-M, a function address has **bit 0 set** (the Thumb bit), so it's odd, which a data address usually isn't.
> - A function pointer's type includes the **parameter and return types**, and calling through the wrong type is undefined behaviour."

```c
int32_t value = 10;
int32_t *dp = &value;          /* data pointer: address of a variable   */
*dp = 20;                      /* dereference: write the data           */

int32_t square(int32_t x) { return x * x; }
int32_t (*fp)(int32_t) = square;   /* function pointer: address of code */
int32_t r = fp(5);                 /* dereference: call the function -> 25 */
```

### Q379. Why does a C function-pointer declaration require parentheses around the pointer name?

> "Because function-call parentheses `()` have **higher precedence** than `*`. Without the extra parentheses, `int *fp(int);` declares a **function** returning `int *`. With them, `int (*fp)(int);` declares a **pointer to a function** returning `int`. See [Q22](#q22-why-do-we-put-parentheses-around-the-function-pointer-name-in-its-declaration)."

### Q380. How do you use a callback function in embedded C?

> "I define a function-pointer type, let the lower layer (a driver) store a pointer of that type through a register function, and the driver calls it when the event happens, after a NULL check. Typical uses are a UART 'frame received', a timer expiry, a button press, or a DMA-complete event. Since the callback often runs in **interrupt context**, it must be short and must not block.
>
> Examples with full code: a UART driver in [Q23](#q23-what-is-a-callback-function-can-you-write-an-example), and a complete button-driver program in [Q62](#q62-how-would-you-implement-a-callback-using-a-function-pointer)."
