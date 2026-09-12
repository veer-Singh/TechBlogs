# Advanced Embedded System Design Questions

## 1. Design a battery-powered IoT sensor node.

Start with requirements: measurement rate, radio duty cycle, battery life, latency, environmental constraints, updateability, security, and failure recovery. Then partition into sensor acquisition, local processing, storage, communication, power manager, watchdog, and OTA/update logic.

A strong architecture has explicit state machines and bounded interfaces rather than allowing every subsystem to call every other subsystem.

## 2. Design a modem controller.

Use a command engine with states such as IDLE, SEND_CMD, WAIT_RESPONSE, RETRY, TIMEOUT, and ERROR. Separate transport bytes from AT-command parsing. Add command deadlines, response tokenization, and recovery for unsolicited modem events.

## 3. Design a UART logging system.

Application code writes to a bounded lock-safe buffer/queue. A dedicated logger task drains it to UART/DMA. On overflow, the system uses a documented policy such as dropping low-priority logs or counting lost records.

## 4. Design a firmware update system.

Define image format, signature verification, version policy, storage layout, update state metadata, power-loss recovery, rollback, and diagnostic reporting before choosing the transport.

## 5. How do you choose RTOS task boundaries?

A task should represent a meaningful independent execution flow with a clear blocking/scheduling requirement. Do not create a task per function. Too many tasks increase stack RAM, scheduling overhead, and synchronization complexity.

## 6. How do you choose between queue, ring buffer, mutex, semaphore, event flag, and notification?

Choose based on semantics: data transfer -> queue/ring buffer; ownership -> mutex; event/resource availability -> semaphore; multiple conditions -> event flags; lightweight direct task signal -> notification. State ownership and data lifetime explicitly.

## 7. How do you design for observability?

Define event IDs, error codes, counters, timestamps, reset reasons, fault context, and version information. A system that cannot explain why it failed is expensive to maintain in the field.
