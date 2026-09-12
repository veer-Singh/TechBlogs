# Advanced FreeRTOS Debugging Questions

> Each card includes an answer, a practical example, an interview follow-up, and a debugging flow.

## 1. A high-priority task never runs. How do you debug it?

Check task creation, priority, state, stack health, scheduler startup, interrupts, and the object blocking the task.

**Example:** Inspect `xTaskCreate()`'s return value and `eTaskGetState()`.

**Interview follow-up:** What if the task is ready but never scheduled? Check for an always-running higher-priority task.

**Flow:**
```text
create -> ready state -> priority -> scheduler -> blocking object
```

## 2. How do you prove priority inversion?

Capture a timeline showing a high-priority task blocked by a low-priority owner while medium-priority work runs.

**Example:** Trace mutex take, task switch, and mutex give timestamps.

**Interview follow-up:** What primitive normally mitigates it? A mutex with priority inheritance.

**Flow:**
```text
high blocks -> low owns mutex -> medium runs -> low delayed -> inversion
```

## 3. Sporadic deadlock: what is your method?

Trace lock acquisition and release with task identity and timestamps, then reconstruct the wait-for graph.

**Example:** Log every mutex take and give with the current task name.

**Interview follow-up:** Why are random delays not a fix? They only change the timing.

**Flow:**
```text
trace locks -> find cycle -> enforce order -> retest under stress
```

## 4. Queue full: bug or expected behavior?

It may be valid backpressure or a permanent producer-consumer rate mismatch. Define a documented policy.

**Example:** Drop the oldest telemetry sample when freshness matters more than completeness.

**Interview follow-up:** What policies are possible? Block, drop, overwrite, or escalate an error.

**Flow:**
```text
send -> queue full -> policy -> block/drop/overwrite/fault
```

## 5. How do you detect stack overflow early?

Enable RTOS checks, inspect `uxTaskGetStackHighWaterMark()`, use guard patterns, and test worst-case call paths.

**Example:** Logging and floating-point formatting reduce a task's remaining watermark.

**Interview follow-up:** Is the hook a complete solution? No, it detects a problem; sizing and testing still matter.

**Flow:**
```text
allocate -> execute worst path -> measure watermark -> resize -> repeat
```

## 6. CPU load suddenly rises after a new feature. Why?

Check busy loops, logging, timer frequency, queue retries, interrupt storms, retransmissions, and tasks that stopped blocking.

**Example:** A zero-timeout queue receive inside `while (1)` creates a polling loop.

**Interview follow-up:** What measurement is useful? Per-task runtime statistics and event-rate counters.

**Flow:**
```text
load rises -> identify task/ISR -> inspect loop -> restore blocking -> measure
```

## 7. Why can logging itself cause bugs?

Formatting can be expensive, writes can block, buffers can overflow, and logging changes timing.

**Example:** `printf()` in a high-priority task delays a control task.

**Interview follow-up:** What is safer? Bounded asynchronous logging through RTT, DMA, or a logger task.

**Flow:**
```text
log request -> format -> buffer -> output -> possible blocking/timing change
```

## 8. How do you debug a race condition?

List all readers and writers, identify execution contexts, capture ordering, and fix ownership or synchronization.

**Example:** Two tasks update a shared state variable without a mutex.

**Interview follow-up:** Why not add a delay? It hides the ordering defect.

**Flow:**
```text
shared state -> readers/writers -> interleaving -> owner -> synchronize
```

## 9. What should a Cortex-M fault dump contain?

Preserve fault registers and the stacked CPU context, including PC, LR, SP, and xPSR.

**Example:** Store `SCB->CFSR`, `SCB->HFSR`, and the stacked PC in RAM before reset.

**Interview follow-up:** Why is PC important? It identifies the failing instruction.

**Flow:**
```text
fault -> capture frame/registers -> preserve RAM -> map PC -> root cause
```

## 10. What is a good watchdog architecture?

A supervisor refreshes the watchdog only after critical tasks report valid progress.

**Example:** Each task updates a heartbeat; the health task checks all heartbeats before feeding the watchdog.

**Interview follow-up:** Why not feed it from any idle loop? That can hide a stalled subsystem.

**Flow:**
```text
task health -> supervisor -> all healthy? -> feed/reset
```

## 11. A task crashes only after long uptime. Where do you look?

Check leaks, heap fragmentation, growing queues, tick wraparound, timestamp rollover, and saturating counters.

**Example:** An object is allocated once per connection and never released.

**Interview follow-up:** What should be trended? Free heap, queue depth, object count, and uptime.

**Flow:**
```text
long runtime -> trend resources -> find growth/wrap -> reproduce -> fix ownership
```

## 12. How do you debug a mutex that is never released?

Find the owner, inspect its PC and stack, and look for early returns, task deletion, or faults before the give.

**Example:** An error branch returns before `xSemaphoreGive()`.

**Interview follow-up:** What design helps? Use one cleanup path or a bounded timeout with fault reporting.

**Flow:**
```text
blocked waiter -> owner -> owner PC -> missing give/error path -> repair
```

## 13. An interrupt fires but the task never wakes. Why?

Verify the ISR-safe API, wake flag, `portYIELD_FROM_ISR()`, and permitted interrupt priority.

**Example:** `xSemaphoreGiveFromISR()` succeeds but no yield is requested.

**Interview follow-up:** Can an ISR use a normal queue API? No, use its `FromISR` variant.

**Flow:**
```text
ISR -> FromISR API -> wake flag -> yield request -> task runs
```

## 14. What is the difference between deadlock and livelock?

Deadlocked tasks wait forever. Livelocked tasks run and change state but never make useful progress.

**Example:** Two tasks repeatedly release and retry the same resource without blocking.

**Interview follow-up:** What metric separates them? Deadlock usually has blocked tasks; livelock consumes CPU.

**Flow:**
```text
tasks wait -> deadlock
 tasks retry -> livelock
```

## 15. How do you distinguish starvation from a scheduling bug?

Measure ready-to-run latency and per-task CPU time. A ready task receiving no CPU while higher-priority work dominates is starvation.

**Example:** A priority-5 polling task prevents a priority-3 task from running.

**Interview follow-up:** What should you inspect? Ready lists, priorities, and whether the dominant task blocks.

**Flow:**
```text
ready task -> scheduler trace -> CPU share -> priority analysis
```

## 16. A queue works in testing but drops messages in the field. What changed?

Field bursts may fill the queue. Check producer rate, consumer rate, queue depth, priorities, and unchecked return values.

**Example:** A network burst fills a queue whose send result is ignored.

**Interview follow-up:** Is a larger queue always the fix? No, sustained rate mismatch remains.

**Flow:**
```text
burst -> queue fills -> send fails/blocks -> policy -> rate correction
```

## 17. How do you debug priority inversion when no mutex is involved?

Trace indirect resource ownership through queues, notifications, shared hardware, and driver tasks.

**Example:** A high-priority task waits for a low-priority SPI owner through a queue.

**Interview follow-up:** What must the trace include? The whole resource-owner chain, not only locks.

**Flow:**
```text
high waits -> indirect owner -> low task -> medium interference -> delay
```

## 18. Why does adding a delay sometimes fix a bug?

A delay changes timing and hides a race or missing memory-ordering rule.

**Example:** A producer happens to finish before a consumer reads a buffer.

**Interview follow-up:** What is the correct response? Find and encode the required synchronization.

**Flow:**
```text
delay changes schedule -> failure disappears -> ordering still missing -> synchronize
```

## 19. How do you diagnose a hard fault with no usable stack?

Determine whether MSP or PSP was active, save fault registers immediately, and keep the handler independent of the damaged stack.

**Example:** A corrupted task stack prevents a normal debugger backtrace.

**Interview follow-up:** What else helps? A fault handler that copies the exception frame to a reserved RAM buffer.

**Flow:**
```text
fault -> identify MSP/PSP -> copy frame -> inspect registers -> map PC
```

## 20. How do you find which task corrupted memory?

Use MPU protection, guard words, canaries, ownership records, and write tracing.

**Example:** A canary after a DMA buffer changes before the task reports failure.

**Interview follow-up:** Why locate the writer? The damaged object is often only the victim.

**Flow:**
```text
corruption -> guard detects -> address/owner -> locate writer -> repair bounds
```

## 21. What causes a task to report ready but never execute?

An always-runnable higher-priority task may monopolize the CPU. Confirm scheduler state and ready lists.

**Example:** A task loops without `vTaskDelay()`, queue receive, or notification wait.

**Interview follow-up:** What is the simplest remedy? Make the task block or yield according to requirements.

**Flow:**
```text
ready -> higher task runs -> no block -> starvation -> redesign loop
```

## 22. How do you debug spurious semaphore wakeups?

Check duplicate ISR gives, binary-semaphore event collapse, and whether a counting semaphore is required.

**Example:** Two interrupts occur before one task take; a binary semaphore records only availability.

**Interview follow-up:** What should be logged? Give/take source, timestamp, and semaphore count where available.

**Flow:**
```text
event -> give -> count/availability -> take -> verify event semantics
```

## 23. A periodic task drifts over time. What is wrong?

Relative delays include execution time. Use `vTaskDelayUntil()` with an absolute reference period.

**Example:** A 1000-tick delay follows a 100-tick operation, producing a 1100-tick cycle.

**Interview follow-up:** What remains? Tick rounding and higher-priority interference still affect jitter.

**Flow:**
```text
release -> execute -> absolute deadline -> delay-until -> next release
```

## 24. How do you trace timing without a full debugger?

Use GPIO timing, DWT cycle counters, trace hooks, runtime statistics, or a logic analyzer.

**Example:** Toggle a GPIO at task entry and exit and measure pulse width.

**Interview follow-up:** What risk exists? Instrumentation can perturb timing, so keep it bounded.

**Flow:**
```text
instrument -> capture -> measure latency/execution -> compare deadline
```

## 25. What is the most common root cause of RTOS timing bugs?

Unsynchronized shared state and code that holds the CPU longer than expected, such as logging and long critical sections.

**Example:** A driver disables interrupts while performing a large copy.

**Interview follow-up:** What is the design rule? Bound critical sections and define ownership.

**Flow:**
```text
shared resource -> contention/blocking -> timing variance -> measure -> bound
```

## 26. A task is created successfully but never runs

Check `xTaskCreate()`'s return value, scheduler startup, priority, task state, immediate blocking, stack validity, and deletion.

**Example:** A task starts with `xQueueReceive(..., portMAX_DELAY)` and correctly remains blocked.

**Interview follow-up:** What proves creation? The API return value plus a task-state snapshot.

**Flow:**
```text
create -> scheduler start -> state -> wait object -> execution
```

## 27. A task runs once and then stops

Add checkpoints around work, delay, and blocking calls. Check faults, stack overflow, blocked resources, disabled interrupts, and scheduler failure.

**Example:** Logging prints once, then `read_sensor()` blocks forever.

**Interview follow-up:** What does the last checkpoint tell you? The last completed region narrows the fault.

**Flow:**
```text
start -> work -> checkpoint -> block/fault -> inspect last checkpoint
```

## 28. One high-priority task prevents all other tasks from running

An always-runnable task can starve lower-priority tasks. Make it block, yield, or wait for an event.

**Example:**
```c
while (1) {
    do_work();
    vTaskDelay(1);
}
```

**Interview follow-up:** Does time slicing solve different priorities? No, time slicing mainly affects equal-priority tasks.

**Flow:**
```text
high task ready -> scheduler selects it -> no block -> lower tasks starve
```

## 29. CPU usage is 100%

Use `uxTaskGetSystemState()` or runtime statistics to identify the consumer. Replace polling loops with blocking APIs.

**Example:** Replace an empty loop with `ulTaskNotifyTake(pdTRUE, portMAX_DELAY)`.

**Interview follow-up:** What else can consume CPU? Interrupt storms and retry loops.

**Flow:**
```text
100% load -> runtime stats -> identify source -> block/limit -> remeasure
```

## 30. A task is stuck in the Blocked state

Blocked is often correct. Identify the queue, semaphore, mutex, notification, delay, or event group being awaited.

**Example:** `xQueueReceive(queue, &data, portMAX_DELAY)` intentionally blocks until data arrives.

**Interview follow-up:** When is it suspicious? When the awaited producer or timeout can never occur.

**Flow:**
```text
blocked -> wait object -> producer/event -> wake or timeout
```

## 31. A task is permanently blocked on a mutex

Find the mutex owner and check every successful take has a matching give, including error paths.

**Example:**
```c
if (xSemaphoreTake(mutex, timeout) == pdTRUE) {
    critical_operation();
    xSemaphoreGive(mutex);
}
```

**Interview follow-up:** What can recover it? A bounded timeout and fault report, not an arbitrary delay.

**Flow:**
```text
waiter -> mutex owner -> owner PC -> missing give -> repair cleanup path
```

## 32. Deadlock occurs between two tasks

If Task A takes Mutex A then B while Task B takes B then A, both can wait forever. Use one global lock order.

**Example:**
```text
Task A -> Mutex A -> Mutex B
Task B -> Mutex B -> Mutex A
```

**Interview follow-up:** What is the prevention rule? Always acquire multiple locks in the same order.

**Flow:**
```text
lock A -> lock B -> work -> unlock B -> unlock A
```

## 33. What is priority inversion?

A low-priority task holds a mutex needed by a high-priority task while medium-priority work runs. A mutex can temporarily raise the owner's priority.

**Example:** High waits for Low, while Medium preempts Low.

**Interview follow-up:** Why not a binary semaphore? It does not express ownership or priority inheritance.

**Flow:**
```text
low owns -> high waits -> inheritance -> low releases -> priority restored
```

## 34. A mutex is released but the high-priority task does not run

Check preemption, interrupt context, scheduler suspension, critical sections, interrupt priority, and context-switch requests.

**Example:**
```c
BaseType_t woken = pdFALSE;
xSemaphoreGiveFromISR(mutex, &woken);
portYIELD_FROM_ISR(woken);
```

**Interview follow-up:** What is the ISR rule? Use the ISR-safe API and request a switch when indicated.

**Flow:**
```text
give -> waiter ready -> yield requested -> scheduler -> high task
```

## 35. Queue data is never received

Verify the queue handle, item size, creation result, producer and consumer execution, return values, capacity, and ISR API usage.

**Example:**
```c
BaseType_t result = xQueueSend(queue, &data, 100);
if (result != pdPASS) {
    /* Queue full or timeout. */
}
```

**Interview follow-up:** What should never be ignored? Queue send and receive return values.

**Flow:**
```text
producer -> send result -> queue state -> consumer -> receive result
```

## 36. Queue values are corrupted

The queue item size must match the object sent. A queue configured for `sizeof(uint32_t)` must not copy from a one-byte object.

**Example:** `xQueueCreate(10, sizeof(uint32_t))` requires a 32-bit item at send time.

**Interview follow-up:** What other issue matters? Pointer queues require lifetime and ownership rules.

**Flow:**
```text
create item size -> send object -> copy bytes -> receive matching type
```

## 37. An ISR occasionally crashes the system

Normal task APIs must not be called from an ISR. Use `xQueueSendFromISR()`, `xSemaphoreGiveFromISR()`, or the matching ISR-safe API.

**Example:**
```c
void USART_IRQHandler(void) {
    xQueueSendFromISR(queue, &data, &woken);
}
```

**Interview follow-up:** What else must be checked? Interrupt priority and bounded ISR work.

**Flow:**
```text
interrupt -> capture minimal data -> FromISR API -> optional yield -> task
```

## 38. ISR priority causes a FreeRTOS assertion

An ISR calling FreeRTOS must use a priority allowed by the port. Check `configMAX_SYSCALL_INTERRUPT_PRIORITY`.

**Example:** An above-threshold interrupt calls `xQueueSendFromISR()` and triggers `configASSERT()`.

**Interview follow-up:** Which ISRs may avoid the restriction? ISRs that never call FreeRTOS APIs.

**Flow:**
```text
ISR priority -> API permission -> assert or valid call -> task wake
```

## 39. The system randomly HardFaults after hours

Check stack overflow, heap failure, memory corruption, ISR misuse, buffer bounds, DMA ownership, and fault registers.

**Example:** Inspect `SCB->CFSR`, `SCB->HFSR`, `SCB->BFAR`, and `SCB->MMFAR`.

**Interview follow-up:** What trend helps? Heap low-water marks and task stack watermarks over uptime.

**Flow:**
```text
fault -> capture registers -> classify cause -> reproduce -> fix ownership/bounds
```

## 40. How do you debug a HardFault in FreeRTOS?

Determine thread or handler mode, inspect the stacked registers, and map the stacked PC to the ELF or map file.

**Example:**
```text
R0 R1 R2 R3 R12 LR PC xPSR
```

**Interview follow-up:** Which register is usually the first target? PC, followed by CFSR and HFSR.

**Flow:**
```text
fault -> exception frame -> PC -> symbol map -> failing instruction
```

## 41. A feature triggers task stack overflow

Logging, floating-point formatting, `sprintf()`, and large local arrays can consume significant stack.

**Example:** Check `uxTaskGetStackHighWaterMark()` before and during logging.

**Interview follow-up:** What is a safer alternative? Bounded formatting and a dedicated logger task.

**Flow:**
```text
feature -> call depth/locals -> watermark -> resize or redesign
```

## 42. Why does `printf()` cause an RTOS timing problem?

It can be slow, use locks and stack, block on UART, or change interrupt timing.

**Example:** `printf("Temperature = %f\n", temperature);` in a high-priority task delays control work.

**Interview follow-up:** Which alternatives help? ITM, RTT, UART DMA, or asynchronous logging.

**Flow:**
```text
format -> lock/output -> block -> priority interference -> timing fault
```

## 43. The tick interrupt stops working

Check SysTick, interrupt enable and priority, the tick handler, global interrupt state, tickless idle, clock configuration, and the RTOS port.

**Example:** Toggle a GPIO from the tick handler and measure its frequency.

**Interview follow-up:** What symptoms result? Delays, timeouts, and software timers stop progressing.

**Flow:**
```text
clock -> tick interrupt -> kernel tick -> timers/delays -> task wake
```

## 44. `vTaskDelay(100)` gives inaccurate timing

It delays approximately 100 ticks, not necessarily 100 milliseconds. With a 1000 Hz tick, one tick is approximately 1 ms, plus scheduling latency.

**Example:** A higher-priority task adds latency after the delay expires.

**Interview follow-up:** What improves periodic accuracy? `vTaskDelayUntil()`.

**Flow:**
```text
delay ticks -> tick expires -> scheduler latency -> task resumes
```

## 45. A periodic task slowly drifts over time

Use `vTaskDelayUntil()` instead of repeatedly adding a relative delay.

**Example:**
```c
TickType_t last_wake_time = xTaskGetTickCount();
while (1) {
    operation();
    vTaskDelayUntil(&last_wake_time, pdMS_TO_TICKS(1000));
}
```

**Interview follow-up:** What remains? Tick rounding and higher-priority interference still cause jitter.

**Flow:**
```text
absolute release -> operation -> delay-until -> next absolute release
```

## 46. A task misses its deadline even though CPU usage is low

Measure release-to-completion time and include interrupt latency, blocking, mutex contention, critical sections, DMA delays, and higher-priority bursts.

**Example:** Low average CPU use hides a short high-priority burst at every deadline.

**Interview follow-up:** What should be measured? Worst-case response time, not only average load.

**Flow:**
```text
release -> interference/blocking -> execute -> complete -> compare deadline
```

## 47. `vTaskDelay()` does not work inside a critical section

A task must not normally block while inside a critical section. Protect shared data, exit the critical section, and then delay.

**Example:**
```c
taskENTER_CRITICAL();
update_state();
taskEXIT_CRITICAL();
vTaskDelay(pdMS_TO_TICKS(100));
```

**Interview follow-up:** Why? Blocking while interrupts or scheduling are constrained can break system progress.

**Flow:**
```text
enter critical -> protect -> exit -> block/delay
```

## 48. Why does disabling interrupts cause RTOS instability?

Long interrupt-disabled regions delay SysTick, UART, and DMA interrupts, causing inaccurate timeouts and late task wakeups.

**Example:** Keep `__disable_irq()` around only a few atomic instructions, never a long transfer.

**Interview follow-up:** What is the design rule? Bound interrupt latency.

**Flow:**
```text
disable IRQ -> tick/ISR delayed -> latency grows -> re-enable -> recovery
```

## 49. `taskENTER_CRITICAL()` versus a mutex

A mutex allows blocking and can provide priority inheritance. Critical sections are for very short atomic operations and affect interrupt latency.

**Example:** Use a mutex for a shared peripheral; use a critical section for a short index update.

**Interview follow-up:** Can a critical section replace every mutex? No, especially not for long or blocking work.

**Flow:**
```text
shared resource -> choose mutex/critical section -> bound duration -> verify latency
```

## 50. A queue works for 10 minutes and then stops

Check queue occupancy, producer and consumer rates, blocked tasks, memory corruption, stack overflow, ISR overload, and priority starvation.

**Example:**
```c
UBaseType_t waiting = uxQueueMessagesWaiting(queue);
UBaseType_t available = uxQueueSpacesAvailable(queue);
```

**Interview follow-up:** What does a permanently full queue indicate? The producer outpaces the consumer or the consumer is stalled.

**Flow:**
```text
queue works -> occupancy grows -> full -> send policy -> rate/consumer fix
```

## 51. Binary semaphore versus mutex debugging scenario

Use a mutex for shared resource ownership and priority inheritance. Use a binary semaphore primarily for synchronization or signaling.

**Example:** Protect a shared UART with a mutex; signal UART completion with a binary semaphore.

**Interview follow-up:** Why are they not interchangeable? Ownership and priority-inheritance semantics differ.

**Flow:**
```text
resource ownership -> mutex
completion event -> binary semaphore
```

## 52. A semaphore is always available even though nobody gives it

Check the handle, initialization, startup gives, object corruption, unexpected ISR gives, and every give/take call.

**Example:** Log `xSemaphoreGive()` and `xSemaphoreTake()` with task names and timestamps.

**Interview follow-up:** What can a binary semaphore hide? Multiple events can collapse into one available state.

**Flow:**
```text
give/take trace -> identify source -> verify initialization -> repair ownership
```

## 53. Event group bits appear to be randomly cleared

With `xEventGroupWaitBits()`, `pdTRUE` for `xClearOnExit` clears matched bits after a successful wait.

**Example:** Verify `xClearOnExit` and `xWaitForAllBits` before blaming memory corruption.

**Interview follow-up:** How do multiple consumers affect interpretation? One consumer may clear bits before another observes them.

**Flow:**
```text
set bits -> wait condition -> clear-on-exit? -> consumer observes state
```

## 54. Why is a task notification faster than a queue?

Notifications are stored in the task control block and avoid general queue storage for simple signaling.

**Example:** DMA ISR calls `vTaskNotifyGiveFromISR()` and the task calls `ulTaskNotifyTake()`.

**Interview follow-up:** When is a queue better? When payload buffering or multiple destinations are required.

**Flow:**
```text
ISR -> task notification -> task wakes -> consume event
```

## 55. A DMA task receives corrupted data

Check buffer lifetime, cache coherency, and ownership. Synchronize DMA completion, ISR notification, and task processing.

**Example:** Do not process a buffer while DMA still writes it; invalidate cache where required.

**Interview follow-up:** What is the ownership rule? Exactly one context writes a buffer at a time.

**Flow:**
```text
DMA owns -> transfer complete -> ISR -> task owns -> process -> release
```

## 56. A task crashes when it is deleted

Before `vTaskDelete()`, check held mutexes, owned memory, active DMA, peripheral state, callbacks, and dependent tasks.

**Example:** Stop DMA and release the peripheral before deleting its worker task.

**Interview follow-up:** Is deletion cleanup? No, resources need explicit ownership and release.

**Flow:**
```text
stop work -> release resources -> notify dependents -> delete task
```

## 57. The FreeRTOS heap becomes fragmented

Repeated allocation and release can fragment the heap. Identify the selected heap implementation and prefer bounded allocation.

**Example:** Allocate fixed-size message blocks from a pool instead of varying heap sizes.

**Interview follow-up:** What should be monitored? Minimum free heap, allocation failures, and allocation lifetime.

**Flow:**
```text
allocate/free cycles -> fragmentation -> allocation failure -> pool/static storage
```

## 58. `malloc()` versus `pvPortMalloc()`

Do not mix C-library allocation with FreeRTOS allocation unless the platform explicitly supports it.

**Example:** Use one allocator for task objects and define who releases every allocation.

**Interview follow-up:** Why does mixing fail? The allocators may use different heaps and free-list metadata.

**Flow:**
```text
choose allocator -> allocate -> own -> release with same allocator
```

## 59. The idle task never runs

Possible causes include CPU overload, an always-runnable high-priority task, an interrupt storm, or scheduler configuration. The idle task also cleans up deleted tasks.

**Example:** A polling task with no block prevents idle processing.

**Interview follow-up:** What measurement helps? Idle time or idle-hook counters.

**Flow:**
```text
no idle -> find ready task/ISR -> restore blocking -> verify idle time
```

## 60. A timer callback blocks the system

Timer callbacks run in the timer service task and must remain short. Send an event to a worker task for long operations.

**Example:**
```c
void TimerCallback(TimerHandle_t timer) {
    xTaskNotifyGive(worker_task);
}
```

**Interview follow-up:** Why not call `vTaskDelay()` there? It blocks other timer callbacks.

**Flow:**
```text
timer callback -> notify worker -> worker blocks/works -> timer service remains free
```

## 61. A software timer does not execute on time

Check timer service task priority, queue length, callback duration, scheduler load, interrupt latency, tick frequency, and timer-command congestion.

**Example:** A long callback delays every callback behind it in the timer service task.

**Interview follow-up:** Which configuration matters? `configTIMER_TASK_PRIORITY`, queue length, and stack depth.

**Flow:**
```text
timer command -> timer queue -> service task -> callback -> next timer
```

## 62. `xQueueSend()` from an ISR sometimes fails

The queue is often full. Track `uxQueueSpacesAvailable()` from a task and maintain an overflow counter rather than doing expensive ISR diagnostics.

**Example:** Increment `queue_overflow_count` when the ISR send returns failure.

**Interview follow-up:** What policy is needed? Drop, overwrite, defer, or signal overload.

**Flow:**
```text
ISR event -> send -> queue full? -> count/drop/defer -> consumer
```

## 63. A race condition disappears when the debugger is attached

The debugger changes timing. Investigate synchronization, initialization, stack corruption, DMA ownership, and timing-sensitive ISRs.

**Example:** A breakpoint gives a producer time to finish before a consumer reads.

**Interview follow-up:** What is the correct conclusion? The bug is hidden, not fixed.

**Flow:**
```text
debugger changes timing -> race hidden -> trace ordering -> synchronize
```

## 64. A variable changes in an ISR but the task does not see it

`volatile` may prevent compiler caching, but it does not provide synchronization. Prefer a task notification, semaphore, queue, or event group.

**Example:** Replace a polling flag with `vTaskNotifyGiveFromISR()`.

**Interview follow-up:** What can volatile not guarantee? Atomicity, mutual exclusion, and memory ordering across all agents.

**Flow:**
```text
ISR event -> ISR-safe signal -> task wakes -> task reads shared state
```

## 65. Why does `volatile` not solve a race condition?

An increment is a read-modify-write sequence. Two tasks can read the same value and overwrite each other's updates.

**Example:** Protect `counter++` with a mutex or use a suitable atomic operation.

**Interview follow-up:** What does volatile provide? Visibility of accesses to the compiler, not synchronization.

**Flow:**
```text
read -> modify -> write -> interleave -> lost update
```

## 66. A context switch happens unexpectedly

Common causes are a tick, a higher-priority task becoming ready, an ISR unblocking a task, a semaphore release, a queue event, or a notification.

**Example:** Inspect PendSV and the ready list when execution moves from Task A to Task B.

**Interview follow-up:** Is every unexpected switch a bug? No, it may be normal scheduler behavior.

**Flow:**
```text
event -> task ready -> PendSV/tick -> scheduler -> new task
```

## 67. Why does PendSV have very low priority?

PendSV performs context switching after higher-priority interrupts finish, keeping interrupt latency predictable.

**Example:** An ISR sets an event; PendSV switches tasks after the ISR exits.

**Interview follow-up:** What should not run in the ISR? Long application work.

**Flow:**
```text
high-priority ISR -> event -> PendSV pending -> ISR exits -> switch
```

## 68. The system crashes only when optimization is enabled

Investigate undefined behavior, uninitialized variables, invalid pointers, races, buffer overflows, stack corruption, and strict-aliasing violations.

**Example:** Compare `-O0`, `-O1`, and `-O2` while checking warnings and fault registers.

**Interview follow-up:** Should optimization be disabled permanently? No, find the underlying defect.

**Flow:**
```text
optimization change -> behavior changes -> identify UB/race -> fix defect
```

## 69. Task stack usage keeps increasing

`uxTaskGetStackHighWaterMark()` reports the minimum remaining stack, not current usage. A small value indicates danger.

**Example:** A logger's watermark falls after formatted floating-point output.

**Interview follow-up:** What should be tested? Worst-case call depth, locals, interrupts, and library paths.

**Flow:**
```text
feature path -> stack watermark -> margin -> resize/redesign
```

## 70. How do you debug a complete FreeRTOS deadlock?

Identify stalled tasks, capture states and wait objects, find resource owners, check lock ordering and priority inversion, inspect scheduler and interrupt state, and check memory corruption.

**Example:** Build `Task A -> Mutex 1 -> Task B -> Queue -> Task C` as a wait-for graph.

**Interview follow-up:** What evidence is strongest? Task states, owners, timestamps, and the dependency cycle.

**Flow:**
```text
stalled tasks -> wait objects -> owners -> dependency graph -> break cycle
```

## 71. How do you debug a production FreeRTOS system without stopping it?

Use runtime statistics, stack-watermark data, counters, trace hooks, GPIO timing, and watchdog reset-reason logging. Keep instrumentation non-intrusive.

**Example:** Record `hardfault_count`, queue overflows, malloc failures, and heartbeat age.

**Interview follow-up:** What must instrumentation avoid? Unbounded blocking and significant timing perturbation.

**Flow:**
```text
instrument -> observe live system -> correlate counters -> diagnose -> recover
```

## 72. A watchdog resets the system every few seconds

Find which task feeds it and why progress stops: blocking, deadlock, starvation, interrupt storms, long critical sections, HardFault, or stack overflow.

**Example:** A health-monitor task feeds the watchdog only after all heartbeats advance.

**Interview follow-up:** Why not increase the timeout first? It can hide the failure and delay recovery.

**Flow:**
```text
reset -> read reason -> inspect health -> find stalled subsystem -> repair/recover
```

## 73. A task is starved but never blocked

A ready task can be starved by an always-runnable higher-priority task. Make the higher-priority task block or yield according to requirements.

**Example:** Task A at priority 5 polls continuously while Task B at priority 4 remains ready.

**Interview follow-up:** What state does B show? Ready, but not Running.

**Flow:**
```text
ready task -> higher task always ready -> no CPU share -> starvation
```

## 74. Priority inheritance is not working

Confirm `xSemaphoreCreateMutex()`, not `xSemaphoreCreateBinary()`, and verify `configUSE_MUTEXES`. Confirm the owner inherits priority while the waiter is blocked.

**Example:** Trace low-owner priority before, during, and after high-priority mutex contention.

**Interview follow-up:** When does inheritance restore? After the owner releases the mutex, subject to remaining mutex ownership rules.

**Flow:**
```text
mutex owner -> high waiter -> inherit -> release -> restore priority
```

## 75. The ultimate FreeRTOS debugging scenario

For a system combining STM32, FreeRTOS, UART, SPI, DMA, tasks, interrupts, mutexes, and queues, investigate methodically rather than randomly changing priorities.

**Example:** Collect watchdog reason, last task and ISR, task states, stack watermarks, heap statistics, queue occupancy, mutex ownership, interrupt frequency, fault registers, DMA state, and deadline violations.

**Interview follow-up:** What is the first split? Separate CPU usage, task state, and fault/reset evidence.

**Flow:**
```text
system failure
├── CPU usage -> runtime statistics -> identify task
├── task state -> ready/blocked -> wait object
└── fault/reset -> HardFault -> CFSR/HFSR
```
