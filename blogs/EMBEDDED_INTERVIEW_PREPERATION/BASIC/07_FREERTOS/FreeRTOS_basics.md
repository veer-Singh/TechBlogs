# FreeRTOS Interview Questions

## 1. What is a task?

A task is an independently schedulable execution context with its own stack and task state. Tasks can block, run, or be ready depending on scheduler events and synchronization.

## 2. Why use an RTOS?

An RTOS helps structure concurrent activities such as communication, sensor sampling, logging, and control. The main value is predictable coordination and blocking semantics, not automatically "faster" code.

## 3. Mutex vs binary semaphore?

A mutex represents ownership of a resource and is designed for mutual exclusion; many RTOS implementations provide priority inheritance for mutexes. A binary semaphore is primarily a synchronization/event primitive and normally does not express ownership.

## 4. Why use a queue instead of a semaphore for data?

A semaphore tells another context that an event/resource is available. A queue transfers discrete data items. If the receiver needs the actual bytes/value, a queue (or another data-buffering primitive) is usually the right abstraction.

## 5. What is priority inversion?

A high-priority task is blocked by a lower-priority task holding a resource while a medium-priority task consumes CPU, indirectly delaying the high-priority task. Priority inheritance is one common mitigation for mutex-protected resources.

## 6. What is deadlock?

Deadlock occurs when tasks wait forever for resources/events in a cyclic dependency. Prevention includes consistent lock ordering, minimizing lock scope, timeouts where appropriate, and simpler ownership models.

## 7. What should an ISR do?

Do the minimum time-critical work and use ISR-safe RTOS APIs where required. Defer substantial processing to a task. Never call an API from an ISR merely because a similarly named task API exists.

## 8. Tick, SysTick, and software timer?

The RTOS tick is a periodic scheduler time base. On Cortex-M, SysTick is one possible hardware timer source for that time base. A software timer is an RTOS-managed callback mechanism that runs in the context defined by that RTOS implementation.

## 9. What is stack overflow in a task?

Each task has its own stack. Excessive local variables, deep call chains, recursion, or library code can exhaust it. Use stack-high-water-mark mechanisms, overflow checks, and fault logs during validation.

## 10. How do you measure CPU load?

A common method is to run an idle hook/counter or trace facility and measure idle time over a fixed interval. CPU load is then inferred from the fraction of time not spent idle. Make sure measurement overhead and interrupt activity are accounted for.

## 11. When would you use task notification?

Task notifications are lightweight per-task signaling mechanisms and can be faster/smaller than some general-purpose primitives. They are useful for event bits, counts, or direct task signaling when the problem fits the notification model.

## 12. How should a 1 ms periodic task be implemented?

Use an RTOS delay-until style periodic mechanism where available, rather than repeatedly adding a relative delay. This reduces accumulated drift. The task must also finish before its period if the design requires one execution every 1 ms.

## References

- https://www.freertos.org/Documentation/
- https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/02-Queues-mutexes-and-semaphores/04-Mutexes
