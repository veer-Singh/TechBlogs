# Advanced Coding — 02 Driver Design

These are design-oriented interview exercises. A strong solution should state assumptions, interfaces, memory ownership, timing constraints, concurrency model, failure behavior, and test strategy.

## 1. Design a UART driver

Define init, TX, RX, DMA/ISR, ring buffers, error handling, ownership, and thread safety.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 2. Design an SPI driver for multiple slaves

Define bus ownership, chip-select management, transaction serialization, and device-specific mode setup.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 3. Design an I2C recovery routine

Detect stuck lines, reset/reconfigure the controller, perform bus recovery where supported, and surface errors.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 4. Design an ADC streaming driver

Use timer triggering plus DMA, define buffer ownership, half/full callbacks, and overrun handling.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 5. Design a CAN driver

Define TX queues, RX filters, error states, bus-off recovery, timestamps, and bounded buffering.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 6. Design a GPIO abstraction

Separate pin identity, mode, electrical configuration, and board mapping while keeping the API simple.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 7. Design a watchdog service

Aggregate subsystem health and refresh hardware only when required components report progress.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 8. Design a flash storage driver

Handle erase/program granularity, alignment, wear, CRC/versioning, and power-loss recovery.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 9. Design a sensor driver without hardware

Inject transport/register operations so protocol and state logic can be unit-tested.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 10. Design a driver error model

Create stable status codes, classify retryable versus fatal errors, and document recovery semantics.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy
