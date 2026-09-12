# Advanced Embedded Systems Questions

## 1. How do you reason about determinism?

Ask what must be bounded: interrupt latency, task response time, message transport, memory allocation, device transaction time, and recovery time. Then identify the source of variance and measure the worst-case path rather than relying on averages.

## 2. What is jitter?

Jitter is variation in event timing around the intended schedule. Sources include interrupt interference, cache effects on larger CPUs, DMA contention, scheduler behavior, variable-length operations, and external device timing.

## 3. Hard vs soft real-time?

A hard real-time deadline is one where missing it constitutes system failure for the requirement. In soft real-time systems, deadline misses degrade quality but are not necessarily catastrophic.

## 4. What is WCET?

Worst-Case Execution Time estimates an upper bound on execution time for a defined code path/environment. Proving tight WCET can be difficult on complex CPUs; measurement alone does not automatically prove a true upper bound.

## 5. How would you review an embedded architecture?

Trace requirements to tasks/interrupts/drivers, identify ownership of data, timing budgets, memory budgets, fault behavior, startup/shutdown, diagnostics, and interfaces. Then challenge hidden coupling and failure propagation.

## 6. How do you prevent one bad subsystem from freezing the product?

Use timeouts, watchdog supervision, bounded queues, isolation, explicit state machines, degraded modes, and recovery paths. Avoid global blocking dependencies where possible.

## 7. Why is "single source of truth" useful for configuration?

Duplicated configuration causes mismatches between firmware, tests, manufacturing tools, and documentation. Keep ownership clear and generate derivative artifacts when practical.

## 8. How do you handle partial failure?

Design for it explicitly: network unavailable, sensor disconnected, flash write interrupted, queue overflow, battery brownout, invalid configuration, or peripheral timeout. Define state transitions and safe behavior for each case.
