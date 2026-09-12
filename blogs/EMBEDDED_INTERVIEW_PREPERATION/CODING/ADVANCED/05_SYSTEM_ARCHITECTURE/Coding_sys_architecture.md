# Advanced Coding — 05 System Architecture

These are design-oriented interview exercises. A strong solution should state assumptions, interfaces, memory ownership, timing constraints, concurrency model, failure behavior, and test strategy.

## 1. Design a battery-powered IoT node

Partition sensing, processing, storage, connectivity, power, watchdog, diagnostics, and update logic.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 2. Design a modem controller

Create a transport/parser/command engine with explicit ownership and recovery.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 3. Design a firmware update architecture

Define image metadata, validation, storage, activation, rollback, and power-loss recovery.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 4. Design a fault manager

Classify faults, preserve context, coordinate recovery, and escalate safely.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 5. Design a logging architecture

Use asynchronous bounded transport and define drop/backpressure policy.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 6. Design a sensor aggregation service

Normalize timestamps/units, handle missing sensors, and expose a stable consumer API.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 7. Design a hardware abstraction layer

Keep MCU/board details below stable driver interfaces and isolate conditional compilation.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 8. Design a bootloader/application contract

Define memory map, vector handoff, versioning, metadata, trust, and reset behavior.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 9. Design system observability

Include software version, reset reason, state, counters, event IDs, and compact fault context.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 10. Design for field recovery

Plan watchdog reset, rollback, safe defaults, persistent diagnostics, and recoverable update state.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy
