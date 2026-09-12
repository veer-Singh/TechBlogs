# Advanced Driver Engineering Questions

## 1. What makes a good peripheral driver?

A good driver has a clear API, owns the hardware configuration it is responsible for, has explicit initialization/state/error behavior, avoids hidden global coupling, and documents timing/concurrency assumptions.

## 2. Blocking vs non-blocking driver API?

Blocking APIs are simple but can stall a task for device-dependent time. Non-blocking APIs improve responsiveness but usually require interrupts/DMA and a completion mechanism. The API should match system timing requirements.

## 3. How would you design a UART driver for high throughput?

Use DMA or interrupt-driven RX, a ring buffer, explicit framing, bounded memory, and a non-blocking consumer path. Define what happens on overflow and framing errors.

## 4. How do you handle hardware timeout?

Every transaction that can wait on external hardware should have a bounded timeout unless the protocol explicitly guarantees completion. On timeout, return a distinct error, collect diagnostics, and put the peripheral into a known state before retrying.

## 5. How do you make a driver testable without hardware?

Separate hardware access from protocol/state logic. Inject register access or a transport interface, use fakes/mocks for responses, and unit-test state transitions and error paths independently from physical I/O.

## 6. What belongs in the BSP/HAL layer vs device driver?

The boundary should be stable. MCU-specific pin/clock/register operations usually belong in the lower hardware abstraction. Device-specific sequencing and protocol belong in the peripheral/device driver.

## 7. What is idempotent initialization?

Calling initialization repeatedly should either be safe or fail predictably without leaving corrupted state. This is valuable during recovery and controlled peripheral restart.

## 8. How do you review register-level code?

Check reset values, access types, reserved bits, required ordering, clock dependencies, write-one-to-clear behavior, volatile semantics, read-modify-write hazards, and errata. The reference manual alone may not include every silicon-specific issue; check the device errata.

