# Advanced 05 Stm32 Interview Questions

> 50-question deep-dive track. Use each Q&A as a flashcard: first answer aloud, then compare with the model answer.

## 1. What is RCC and why does every STM32 project care about it?

RCC controls clocks and resets for many MCU domains/peripherals. A peripheral can be configured incorrectly or not operate at all if its clock source is missing or wrong.

## 2. How do you derive a timer period?

Starting from timer clock, apply the prescaler and auto-reload relationships defined for that STM32 timer. Always account for the actual timer input clock, not just the CPU clock.

## 3. Why can STM32 timer clock be different from APB clock?

On many STM32 families, timer kernels can receive a multiplied clock when an APB prescaler is not 1. The exact rule is family-specific, so check the clock tree/reference manual.

## 4. How do you calculate PWM duty?

Compare value relative to the timer period determines duty in common PWM modes; exact edge behavior depends on mode and polarity.

## 5. What is center-aligned PWM?

The timer counts up and down around the period, which can change spectral characteristics and timing compared with edge-aligned PWM.

## 6. What is input capture?

A timer captures its counter value on a selected input edge, allowing pulse width/period measurement without tight polling.

## 7. What is output compare?

A timer triggers an event when its counter matches a configured compare value.

## 8. What is one-pulse mode?

A timer can generate a single programmed pulse or event sequence and then stop, depending on timer capabilities/configuration.

## 9. What is EXTI?

External interrupt/event routing that connects GPIO-related events to interrupt lines. Exact multiplexing is family-specific.

## 10. How do GPIO pull-ups differ from external pull-ups?

Internal pulls are integrated into the MCU and have device-specific value/tolerance; external resistors can offer stronger/more predictable electrical behavior.

## 11. What is alternate-function remapping/pin mux?

It selects which peripheral signal is routed to a pin. Multiple peripherals may compete for pins, so board design and mux configuration must agree.

## 12. How would you debug UART garbage data?

Verify clock tree, peripheral clock, baud calculation, oversampling, GPIO mux, line levels, parity/stop bits, and external signal wiring. Capture the line with a logic analyzer.

## 13. How does DMA improve UART throughput?

It moves data between UART and memory with fewer CPU interrupts. Firmware still must handle buffer ownership, transfer completion, and errors.

## 14. What is ADC sample time?

The duration allowed for the ADC sampling capacitor to acquire the input. Source impedance and required accuracy can require longer sampling times.

## 15. Resolution versus accuracy in an ADC?

Resolution is the number of digital codes; accuracy includes offset, gain, linearity, reference, noise, and other error sources.

## 16. What is oversampling?

Collecting/combining multiple samples to reduce noise or increase effective resolution under suitable conditions. The achievable improvement depends on noise characteristics and implementation.

## 17. What is DAC?

A digital-to-analog converter generates an analog output corresponding to a digital input code, subject to reference, settling, linearity, and output-stage limits.

## 18. What is watchdog IWDG versus WWDG conceptually?

Both are watchdog mechanisms with different timing/clock/reset characteristics; the exact configuration differs by STM32 family. Windowed watchdogs impose an allowed refresh window.

## 19. What is NVIC?

The Nested Vectored Interrupt Controller on Cortex-M handles interrupt enabling, priority, pending state, and exception dispatch according to architecture/device features.

## 20. How do you avoid interrupt priority bugs?

Define a priority scheme based on latency/criticality, verify API restrictions, understand preemption rules, and test nested interrupt behavior.

## 21. What is SysTick typically used for?

It can provide a regular system tick used by RTOSes or timekeeping layers, though another timer can sometimes be selected.

## 22. Why configure clocks before peripherals?

Peripheral baud rates, timer periods, ADC timing, and bus frequencies depend on clock configuration. Wrong clocks create symptoms that look like peripheral bugs.

## 23. What is clock source failover?

Some STM32 families provide clock monitoring or backup sources. Robust systems can detect loss of an oscillator and switch or enter a safe state when supported.

## 24. What is HSE versus HSI?

They are typical categories of external and internal high-speed clock sources. Exact names/frequencies vary by family.

## 25. What is PLL used for?

A phase-locked loop can multiply/divide a source clock to generate required core/peripheral frequencies, subject to device limits.

## 26. How do you debug a timer that runs twice as fast as expected?

Recompute the actual timer kernel clock including APB prescaler rules, then verify PSC/ARR and whether the measured edge is one or two transitions per period.

## 27. What is the difference between polling and DMA for ADC?

Polling makes CPU explicitly wait/read conversions. DMA can capture streams into memory, enabling efficient sample pipelines.

## 28. How would you implement periodic sampling?

Use a timer as the sample trigger when timing matters, optionally with ADC + DMA, instead of relying on software delays.

## 29. What is SPI CPOL/CPHA?

They define clock idle polarity and which clock edge samples/shifts data. Both master and slave must agree with the peripheral datasheet.

## 30. Why can I2C get stuck low?

A device may hold SDA/SCL low after reset or a communication fault. Recovery can require clocking/reinitialization or bus recovery sequences supported by the hardware/design.

## 31. What does open-drain mean electrically?

The output actively pulls low and otherwise releases the line so a pull-up creates the high level, enabling wired sharing.

## 32. How do you debug CAN no-ACK?

Check transceiver power/mode, bus termination, bitrate/sample point, wiring, filters, and whether another active node is present to acknowledge frames.

## 33. What is CAN bus-off?

A CAN controller can enter a bus-off state after excessive transmit errors. Recovery behavior depends on the controller/configuration and should be part of the driver design.

## 34. What is STM32CubeMX good for?

It generates initial peripheral/clock/pin configuration and project scaffolding. Generated code should still be reviewed against the reference manual and application requirements.

## 35. HAL callback pitfalls?

Weak callbacks or global callback assumptions can hide ownership and concurrency issues. Keep callbacks short and define whether they execute in ISR or task context.

## 36. How do you choose HAL vs LL vs registers?

Use the highest layer that still meets timing/control requirements, while keeping performance-critical or device-specific paths at a lower layer when justified.

## 37. What is a linker scatter/load issue?

Code/data may be placed in an invalid memory region or startup copy/clear settings may not match section placement. The map file and linker script are primary debugging tools.

## 38. How do you debug HardFault on STM32?

Capture the stacked PC/LR/xPSR and fault status registers, map the PC to source/disassembly, then inspect stack/memory corruption and fault cause.

## 39. What common causes lead to HardFault?

Invalid memory access, execution of invalid state/instruction, corrupted stack/return state, bad function pointers, or escalated configurable faults.

## 40. Why check the exact STM32 part number?

Peripheral capabilities, register definitions, memory sizes, pin multiplexing, clocks, and errata differ across families and even related subparts.

## 41. What is TrustZone on applicable STM32 MCUs?

A hardware isolation/security feature available on certain Cortex-M architectures/devices, separating secure and non-secure execution and resources.

## 42. How do you validate a 20 kHz PWM?

Measure the output with an oscilloscope, verify period/duty, then correlate with the timer clock, prescaler, and ARR configuration. Do not rely on source-code arithmetic alone.

## 43. What should a production STM32 peripheral driver expose?

Initialization/configuration, start/stop, data path APIs, status/errors, and recovery semantics. Keep register details inside the driver boundary.

## 44. How do you handle peripheral reset during recovery?

Return the block to a known state, clear stale flags/FIFOs, reapply configuration, and synchronize with callers so no transaction uses the peripheral mid-reset.

## 45. What is an STM32 errata workaround?

A firmware sequence designed to avoid a documented silicon bug. It must be applied only to affected parts/revisions and validated during bring-up.

## 46. What is the best STM32 interview debugging sequence?

Start with clock -> pin mux -> reset state -> peripheral configuration -> interrupt/DMA path -> status flags -> physical waveform -> software state.

## 47. How do you verify an STM32 clock-tree assumption?

Read the configured clock registers, calculate the actual kernel clock from the family-specific tree, and compare with a measured timer/UART output.

## 48. How do you handle DMA transfer completion races?

Define ownership transfer at a precise point, synchronize producer/consumer access, and ensure callbacks cannot observe buffers while hardware still owns them.

## 49. How do you design STM32 low-power wakeup logic?

List wake sources, retained state, clock reinitialization requirements, peripheral reconfiguration, and the maximum wake-to-service latency.

## 50. Why should STM32 register code check errata?

The silicon can have documented deviations from the architectural/reference-manual behavior; affected revisions may require firmware workarounds.

