# Advanced Power and Performance Study Notes

> Answer each question first, then review the example and measurement point.

## 1. Why is average current more important than peak current for a battery product?

Battery life is strongly influenced by charge consumed over time. Peak current still matters because it can cause brownouts, regulator limitations, radio performance problems, and battery voltage droop.

## 2. How do you reduce MCU power?

Lower active time first: sleep instead of polling, reduce frequency when allowed, batch work, use peripheral/DMA offload, and disable unused clocks/blocks. Then measure current across the actual workload.

## 3. What is dynamic power conceptually?

Dynamic switching power is strongly related to capacitance, voltage, switching activity, and frequency. Lowering voltage or activity can therefore reduce energy, subject to device operating limits.

## 4. What is CPU load vs energy efficiency?

A lower CPU load does not automatically mean lower energy. A task could run briefly at high frequency and sleep, or run longer at low frequency. Optimize energy per useful operation and verify with measurements.

## 5. How do you optimize a 20 kHz PWM application?

First define resolution, timer clock, acceptable jitter, duty-cycle granularity, and power stage requirements. Use a timer peripheral rather than software toggling. Verify frequency and duty with a scope.

## 6. Why can compiler optimization change firmware behavior?

Correct C code should remain correct across optimization levels, but undefined behavior, missing synchronization, timing-dependent bugs, and incorrect register declarations can surface when optimization changes generated code.

## 7. What is a performance budget?

Define limits for CPU time, RAM, flash, ISR latency, communication throughput, boot time, and energy. Review them as design constraints rather than discovering violations late in integration.

## Examples for Questions 1-7

- **1 Example:** A radio draws 180 mA for 20 ms and 5 mA for the remaining sleep period. **Measure:** Integrate current over a complete workload cycle, not only the radio peak.
- **2 Example:** Replace a 1 ms polling loop with a timer interrupt and sleep until the next event. **Measure:** Compare active time and average current before and after.
- **3 Example:** Lowering a peripheral clock reduces switching activity, but the peripheral must still meet its timing requirement. **Measure:** Check energy per completed transaction.
- **4 Example:** A sensor task uses less CPU after optimization but keeps the MCU awake longer. **Measure:** Compare sleep time and joules per sample, not CPU percentage alone.
- **5 Example:** Configure a timer peripheral for 20 kHz PWM instead of toggling a GPIO in software. **Measure:** Verify frequency, duty cycle, jitter, and output transitions with a scope.
- **6 Example:** An uninitialized variable works at `-O0` but fails at `-O2`. **Measure:** Enable warnings and inspect the generated access sequence before blaming optimization.
- **7 Example:** Set a maximum ISR time of 10 us, a boot limit of 500 ms, and a battery-energy budget per sample. **Measure:** Track each limit in automated performance tests.

## 8. What is dynamic voltage and frequency scaling?

DVFS changes voltage and clock frequency to match the current workload. Lower settings save energy but reduce available performance.

**Example:** Run a sensor-processing task at a high clock only during computation, then return to a low-power clock before sleep.

**Measurement:** Record voltage, frequency, execution time, and energy per operation.

## 9. How do you choose between sleep modes?

Compare wake-up latency, retained state, available wake sources, RAM retention, peripheral support, and current consumption.

**Example:** Use light sleep for a 1 ms response requirement and deep sleep when the next event is several seconds away.

**Measurement:** Measure entry time, wake time, current, and missed-event behavior for each mode.

## 10. What is energy per operation?

Energy per operation is the total energy used to complete useful work. It is often more useful than instantaneous current for optimization.

**Example:** A DMA transfer may use more peak current but less total energy than a CPU byte-copy loop.

**Measurement:** Integrate voltage multiplied by current over the complete operation.

## 11. How do you measure embedded power accurately?

Use a suitable shunt, current monitor, power analyzer, or oscilloscope, and capture both active and sleep intervals with correct bandwidth.

**Example:** A slow multimeter can hide a 2 ms radio burst that causes a brownout.

**Measurement:** Validate instrument bandwidth, shunt impact, sample rate, trigger point, and calibration.

## 12. What is clock gating?

Clock gating disables clocks for unused peripherals or blocks. It reduces switching power but must not disable a block still needed by software or DMA.

**Example:** Disable the ADC clock after conversion and re-enable it before the next measurement.

**Measurement:** Confirm the block is inactive and compare current before and after gating.

## 13. How can DMA improve both performance and power?

DMA moves data without CPU involvement, allowing the CPU to sleep or perform other work. Setup overhead means it is not efficient for every small transfer.

**Example:** Use DMA for a 512-byte SPI transfer instead of handling 512 receive interrupts.

**Measurement:** Compare CPU cycles, transfer time, interrupt count, and energy per transfer.

## 14. What is cache impact on embedded performance?

Caches reduce memory latency when access patterns have locality, but misses, invalidation, and coherency work can add cost.

**Example:** A sequential buffer scan may benefit from cache, while random peripheral descriptors may not.

**Measurement:** Use hardware counters or trace data to compare hit rate and execution time.

## 15. How do you optimize memory bandwidth?

Reduce unnecessary copies, use DMA, align buffers when required, process data in cache-friendly blocks, and avoid reading the same data repeatedly.

**Example:** Parse a network packet in place instead of copying its payload into several temporary arrays.

**Measurement:** Track bus utilization, copy time, cache misses, and end-to-end latency.

## 16. What is interrupt latency?

Interrupt latency is the time from an event to the start of its handler. Disabled interrupts, higher-priority handlers, and long critical sections increase it.

**Example:** Toggle a GPIO at the first instruction of an ISR and compare it with the external event on a scope.

**Measurement:** Record minimum, average, and worst-case latency under maximum system load.

## 17. How do you optimize ISR performance safely?

Keep the handler bounded, clear the source correctly, capture minimal state, and defer processing to a task or main loop.

**Example:** Store a UART byte in a ring buffer and signal a parser instead of decoding a complete protocol frame in the ISR.

**Measurement:** Measure handler duration and check for missed or nested events.

## 18. What is thermal throttling?

Thermal throttling reduces frequency, workload, or output power when temperature approaches a limit. It protects reliability at the cost of performance.

**Example:** Reduce CPU frequency when the MCU temperature exceeds a warning threshold and restore it after cooling.

**Measurement:** Test temperature, workload, frequency transitions, and recovery hysteresis.

## 19. How do you prevent thermal oscillation?

Use separate enter and exit thresholds, minimum dwell times, and controlled transitions instead of switching modes at one exact temperature.

**Example:** Enter throttling at 90 C and exit only below 80 C after a stable cooling period.

**Measurement:** Plot temperature and operating mode over time under a repeatable load.

## 20. How do you profile firmware without changing timing too much?

Use hardware cycle counters, trace units, GPIO markers, sampling profilers, or low-overhead counters. Avoid heavy logging in the measured path.

**Example:** Read a cycle counter at function entry and exit, then store only an aggregate maximum.

**Measurement:** Compare timing with instrumentation enabled and disabled to estimate perturbation.

## 21. How do you find the source of a CPU hotspot?

Measure by task, function, interrupt, and event type. A high-level CPU percentage alone does not identify the cause.

**Example:** A low-priority task may appear expensive because it repeatedly retries a full queue.

**Measurement:** Use call sampling, runtime statistics, and event counters together.

## 22. How do you reduce boot time?

Measure each startup phase, defer noncritical initialization, reduce unnecessary memory clearing or probing, and parallelize independent setup where safe.

**Example:** Start the user interface after essential safety checks while a noncritical sensor calibrates in the background.

**Measurement:** Timestamp reset, clock setup, memory init, driver init, scheduler start, and application-ready events.

## 23. How do you balance flash size and performance?

Choose optimization settings and code structure using measured flash, RAM, execution time, and maintenance impact rather than size alone.

**Example:** An inline helper may improve speed but increase flash when instantiated for many types.

**Measurement:** Compare map-file size, hot-path cycles, and worst-case timing for each build option.

## 24. How do you optimize a memory-constrained system?

Measure static usage, stack high-water marks, heap behavior, buffer peaks, and fragmentation. Reduce duplication before reducing safety checks.

**Example:** Share a scratch buffer between non-overlapping processing stages with explicit ownership.

**Measurement:** Record minimum free RAM and maximum simultaneous buffer usage during stress tests.

## 25. What is performance regression testing?

It automatically compares timing, memory, throughput, power, and boot metrics against a known baseline.

**Example:** Fail CI if a driver increases worst-case ISR time by more than 10 percent.

**Measurement:** Store repeatable workload results with build and hardware identifiers.

## 26. How do you optimize communication throughput?

Use suitable frame sizes, DMA, batching, flow control, efficient parsing, and enough buffering without violating latency requirements.

**Example:** Batch sensor samples into one DMA transfer while keeping the maximum frame delay within the control budget.

**Measurement:** Check payload throughput, bus utilization, queue depth, retries, and latency percentiles.

## 27. How do you reduce power in a wireless product?

Reduce radio-on time, batch transmissions, use appropriate transmit power, sleep between events, and avoid unnecessary reconnects.

**Example:** Collect ten samples and publish one packet instead of waking the radio for every sample.

**Measurement:** Measure energy per packet, connection time, retry rate, and battery life under realistic signal conditions.

## 28. How do you detect a power regression?

Use a repeatable workload, fixed firmware configuration, calibrated measurement equipment, and automated comparison against a baseline.

**Example:** A new logging feature adds 4 mA during every idle interval even though CPU load appears unchanged.

**Measurement:** Compare current waveforms, sleep percentage, wake count, and energy per test cycle.

## 29. How do you handle performance versus safety trade-offs?

Keep safety limits, watchdogs, bounds checks, and fault handling intact unless the risk is explicitly reviewed. Optimize the implementation around them.

**Example:** Replace expensive diagnostic logging with a bounded counter rather than removing an over-temperature shutdown.

**Measurement:** Verify both performance targets and safety-response timing.

## 30. What is the strongest power and performance interview answer?

State the target, identify the bottleneck, propose a change, explain the trade-off, and describe how the result will be measured.

**Example:** “DMA reduces CPU time for the SPI transfer, but I will verify cache ownership, completion latency, and energy per transfer.”

**Measurement:** Always report the workload, hardware, baseline, metric, and worst-case result.

