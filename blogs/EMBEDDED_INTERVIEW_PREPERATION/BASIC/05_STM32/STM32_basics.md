# STM32 Interview Questions

## 1. What is the role of the STM32 reference manual?

The datasheet describes electrical characteristics, package/pin details, and device-level limits. The reference manual provides detailed peripheral behavior, registers, bit fields, clocking, interrupts, and programming information. Both are needed for firmware work.

## 2. What is RCC in STM32?

The Reset and Clock Control block manages clocks and reset signals for many peripherals and core domains. Before using a peripheral, firmware normally must ensure its clock is enabled and the required clock source/configuration is valid.

## 3. What is a GPIO alternate function?

An alternate function routes a physical pin to a peripheral signal such as UART TX, SPI SCK, timer PWM, etc. One pin often has several possible alternate functions, selected through GPIO configuration registers.

## 4. How does PWM work?

A timer counts between configured limits and drives an output based on a compare value. Duty cycle is controlled by the compare value relative to the period. Frequency depends on timer input clock, prescaler, and auto-reload value.

## 5. What is EXTI?

External Interrupt/Event controller logic can route GPIO edge/level events to interrupt lines, depending on the STM32 family. Correct configuration includes the GPIO source, edge selection, interrupt enable, and NVIC setup.

## 6. UART interrupt receive design?

A common design is: enable RX interrupt -> ISR reads received byte -> push byte into a ring buffer -> notify/defer parsing to a task. Avoid running a complete text parser in the ISR.

## 7. ADC interview point: what does resolution mean?

An N-bit ADC represents the input using up to `2^N` digital codes. Resolution is not the same as absolute accuracy; reference quality, noise, offset, gain error, layout, and sampling behavior also matter.

## 8. Why are timers so important in STM32?

Timers support periodic interrupts, PWM, input capture, output compare, pulse measurement, encoder interfaces, one-pulse operation, and more. Interviewers often use timers to test whether you can reason from clock tree -> prescaler -> counter -> event rate.

## 9. HAL vs LL vs register-level?

STM32 HAL provides a higher-level abstraction and portability across many projects. LL exposes a lighter abstraction closer to registers. Direct register programming gives maximum control but increases maintenance and device-specific coupling. The right choice depends on project constraints and team standards.

## 10. How would you debug a peripheral that does not work?

Confirm clock enable, pin mux, mode, polarity, baud/timing, interrupt/DMA configuration, and peripheral status flags. Then compare register values against a working configuration and observe the external pin with a logic analyzer or oscilloscope when possible.

## References

- https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-m-mcus.html
- https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
