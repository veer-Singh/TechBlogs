# Advanced Embedded Systems Questions

How to use this file: read the **Short answer**, explain it aloud, then check the details. Each question ends with a **Remember** line.

## 1. How do you reason about determinism?

**Short answer:** Decide what must be bounded, find what causes variation, and measure the worst case (not the average).

Things that may need a bound:

- Interrupt latency
- Task response time
- Message transport time
- Memory allocation time
- Device transaction time
- Recovery time

**Method:** for each, name the source of variance (for example, `malloc` search time, flash wait states, another interrupt), then measure the worst-case path.

**Remember:** averages hide the failures. Design and test for the worst case.

## 2. What is jitter?

**Short answer:** Jitter is how much an event's timing varies from its planned schedule.

```text
Planned:  |----|----|----|----|
Actual:   |----|-----|---|----|     <- some events arrive early or late
```

Common sources:

- Interrupt interference (a higher-priority interrupt delays yours)
- Cache effects on larger CPUs
- DMA contention on the bus
- Scheduler behaviour
- Variable-length operations
- Timing of external devices

**Remember:** use a hardware timer for the timing-critical edge, not a software delay.

## 3. Hard vs soft real-time

**Short answer:** Missing a hard deadline is a failure. Missing a soft deadline only degrades quality.

| Type | Missing the deadline means | Example |
| --- | --- | --- |
| Hard | System failure | Airbag deployment, motor over-current trip |
| Soft | Lower quality, still works | Video frame drop, UI lag |

**Remember:** "real-time" means predictable, not fast.

## 4. What is WCET?

**Short answer:** Worst-Case Execution Time is an upper bound on how long a code path can take in a defined environment.

- **Measured** time is what you observed; it is not automatically the upper bound.
- **Proven** WCET needs analysis of all paths, cache states, and interrupts, which is hard on complex CPUs.
- Simple MCUs without caches make WCET much easier to bound.

**Remember:** a measurement can only show what you saw. It does not prove nothing worse can happen.

## 5. How would you review an embedded architecture?

**Short answer:** Trace requirements through the design, then look for hidden coupling.

Checklist:

1. Requirements traced to tasks, interrupts, and drivers
2. Who owns each piece of data
3. Timing budget per path
4. Memory budget (RAM, flash, stack)
5. Fault behaviour, startup, and shutdown
6. Diagnostics and interfaces

Then challenge: "what happens if this piece fails?" and "what else does it quietly depend on?"

**Remember:** find where one failure can spread.

## 6. How do you prevent one bad subsystem from freezing the product?

**Short answer:** Never let one part wait forever on another.

- Timeouts on every wait
- Watchdog supervision of each critical task
- Bounded queues (a full queue does not grow without limit)
- Isolation between subsystems
- Explicit state machines
- Degraded modes (keep the essential function running)
- Recovery paths

**Remember:** avoid global blocking dependencies.

## 7. Why is a "single source of truth" useful for configuration?

**Short answer:** If the same setting is written in two places, they will eventually disagree.

Duplicated configuration causes mismatches between firmware, tests, manufacturing tools, and documentation.

**Fix:** keep one owner for each value and generate the other artifacts (headers, docs, test data) from it when practical.

**Remember:** one place to edit, everything else generated.

## 8. How do you handle partial failure?

**Short answer:** List the failures in advance and define the safe behaviour for each.

| Failure | Question to answer |
| --- | --- |
| Network unavailable | Queue, drop, or retry? For how long? |
| Sensor disconnected | Report "unavailable" rather than a stale value? |
| Flash write interrupted | How does the next boot detect and recover? |
| Queue overflow | Drop oldest or newest, and is it counted? |
| Battery brown-out | What is saved before power is lost? |
| Invalid configuration | Fall back to safe defaults? |
| Peripheral timeout | Reset the peripheral and retry? |

**Remember:** define a state transition and a safe behaviour for each failure, before it happens.
