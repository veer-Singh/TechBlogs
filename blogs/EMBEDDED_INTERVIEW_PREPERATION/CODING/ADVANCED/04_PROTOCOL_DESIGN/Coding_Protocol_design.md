# Advanced Coding — 04 Protocol Design

These are design-oriented interview exercises. A strong solution should state assumptions, interfaces, memory ownership, timing constraints, concurrency model, failure behavior, and test strategy.

## 1. Design a framed binary protocol

Define sync, length, type, payload, CRC, maximum frame size, and parser recovery.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 2. Design a reliable command protocol over UART

Add sequence IDs, acknowledgements, timeouts, retries, and duplicate handling.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 3. Design a protocol over TCP

Add application framing because TCP is a byte stream; define reconnect/session semantics.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 4. Design an MQTT message lifecycle

Define publish queueing, QoS choice, reconnect behavior, deduplication, and offline policy.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 5. Design a Modbus master

Implement request sequencing, response validation, timeout/retry, exception responses, and device addressing.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 6. Design a CAN transport layer

Split larger messages into frames, maintain sequence state, timeouts, and reassembly limits.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 7. Design CRC test vectors

Document exact polynomial, width, init, reflection, xorout, and known input/output vectors.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 8. Design protocol versioning

Define backward-compatible fields, version negotiation, and behavior for unknown fields.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 9. Design a command-line protocol

Separate lexical parsing, validation, dispatch, response formatting, and error reporting.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy

## 10. Design an encrypted application protocol

Separate transport security from application authentication, key management, replay protection, and framing.

### What the interviewer should hear
- Clear state/data ownership
- Bounded memory and timing
- Error/recovery path
- Test strategy
