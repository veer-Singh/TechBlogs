# Advanced Coding — 01 State Machines

These are design-oriented interview exercises. A strong solution should state assumptions, interfaces, memory ownership, timing constraints, concurrency model, failure behavior, and test strategy.

## 1. Design a button debounce FSM

Define stable/reject states, sample timing, press/release events, and ensure no blocking delay.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 2. Design an AT modem command FSM

Separate SEND, WAIT, PARSE, RETRY, TIMEOUT, and ERROR; handle unsolicited responses independently.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 3. Design a firmware update FSM

Use DOWNLOAD, VERIFY, STAGE, ACTIVATE, BOOT_VALIDATE, CONFIRMED, and ROLLBACK states.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 4. Design a Wi-Fi reconnect FSM

Separate disconnected, connecting, network-ready, application-ready, backoff, and fatal states.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 5. Design a motor controller FSM

Include startup, ramp, run, stop, fault, and recovery with current/speed guards.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 6. Design a battery charger FSM

Model idle, precharge, constant-current, constant-voltage, termination, fault, and thermal limits.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 7. Design a packet parser FSM

Use sync/header/payload/CRC states with bounded length and guaranteed recovery after malformed input.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 8. Design a USB-like enumeration FSM

Represent reset, descriptor exchange, configuration, operational, and error states; define timeout handling.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 9. Design an elevator controller FSM

Identify motion, door, request, obstruction, timeout, and fault states before implementing outputs.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 10. Design a safe-state supervisor FSM

Every fault path must converge on a defined safe state and a bounded recovery/escalation policy.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy
