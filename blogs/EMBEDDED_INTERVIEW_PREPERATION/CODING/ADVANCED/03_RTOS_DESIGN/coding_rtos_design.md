# Advanced Coding — 03 Rtos Design

These are design-oriented interview exercises. A strong solution should state assumptions, interfaces, memory ownership, timing constraints, concurrency model, failure behavior, and test strategy.

## 1. Design ISR-to-task UART reception

ISR records bytes/positions and signals a parser task; parser performs framing and application dispatch.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 2. Design a producer-consumer pipeline

Use bounded queues/ring buffers and define a policy for full buffers.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 3. Design a periodic 1 ms control task

Use absolute-period scheduling, bounded work, and a measurable execution-time budget.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 4. Design a high-throughput logger

Use a lock-safe bounded buffer and a dedicated DMA-backed logger task.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 5. Design a priority scheme

Rank tasks from timing/criticality, then analyze blocking and higher-priority interference.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 6. Design a deadlock-resistant locking strategy

Define global lock order and avoid holding locks across blocking I/O.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 7. Design CPU-load telemetry

Measure idle/execution time with bounded instrumentation and avoid perturbing critical paths.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 8. Design task health monitoring

Each critical task provides a progress indicator; a supervisor evaluates freshness and dependencies.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 9. Design a memory-pool message system

Use fixed-size blocks, ownership transfer, and pool exhaustion statistics.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 10. Design a graceful shutdown path

Stop producers, drain or discard queues by policy, close peripherals, persist required state, then power down.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy
