# Python Interview Questions for Embedded Engineers

How to use this file: read the **Short answer**, try the commented example, then check the details. Each question ends with a **Remember** line.

## 1. Why is Python useful to embedded engineers?

**Short answer:** It is the glue for testing, tooling, and data work around the firmware, rather than code that runs on the MCU.

Common uses:

- Test automation and hardware-in-the-loop tests
- Serial tools and log processing
- Firmware validation and manufacturing scripts
- Packet generation and data analysis
- CI utilities

**Remember:** Python usually sits beside the firmware, not inside it.

## 2. List vs tuple

**Short answer:** A list can change after creation; a tuple cannot.

```python
regs = [0x00, 0x01]        # list: mutable
regs.append(0x02)          # OK

point = (10, 20)           # tuple: immutable
# point[0] = 5             # TypeError: cannot modify
```

Use a tuple for a fixed record, and to signal "do not modify this".

**Remember:** tuple means fixed, list means changeable.

## 3. What is a set?

**Short answer:** An unordered collection of unique, hashable items. Fast membership checks and duplicate removal.

```python
seen = {1, 2, 3}          # a set of unique values
if 2 in seen:             # membership test is fast (average O(1))
    print("present")

unique_ids = set([1, 1, 2, 2, 3])   # removes duplicates -> {1, 2, 3}
```

**Remember:** use a set to answer "have I seen this already?".

## 4. Dictionary use in test automation

**Short answer:** A dictionary maps keys to values. It suits configuration, register descriptions, decoded packets, and test results.

```python
# Register map: name -> address
REGS = {"CTRL": 0x00, "STATUS": 0x04, "DATA": 0x08}

# A decoded packet
packet = {"id": 0x12, "length": 4, "payload": b"\x01\x02\x03\x04"}

# A test result
result = {"test": "uart_loopback", "passed": True, "duration_ms": 120}
```

**Remember:** use dictionaries for named data, so the code reads `REGS["STATUS"]` instead of a magic number.

## 5. What is a generator?

**Short answer:** A function that produces values one at a time, so it does not hold everything in memory.

```python
def lines(stream):
    for line in stream:
        yield line.strip()       # hands back one line, then pauses until asked for the next

# Processing a huge log without loading it all
with open("big.log") as f:
    for line in lines(f):
        if "ERROR" in line:
            print(line)
```

**Remember:** `yield` gives lazy, low-memory processing of large logs or streams.

## 6. What is a context manager?

**Short answer:** It guarantees setup and cleanup around a block, using `with`.

```python
import serial

# The port is always closed when the block ends, even if an exception happens.
with serial.Serial("COM3", 115200, timeout=1) as port:
    port.write(b"ping\n")
    reply = port.readline()
```

Also used for files, locks, and temporary resources.

**Remember:** `with` means cleanup is not forgotten.

## 7. How would you automate a UART test?

**Short answer:** Configure the port, send a known request, check the response and timing, record the result, and always close the port.

```python
import serial, time

def uart_test(port_name):
    # 1. open and configure the port (baud, data bits, parity, timeout)
    with serial.Serial(port_name, 115200, bytesize=8, parity="N", timeout=1) as port:
        for attempt in range(3):                       # 2. bounded retries, never infinite
            port.reset_input_buffer()
            start = time.time()
            port.write(b"VER?\n")                      # 3. send a known request
            reply = port.readline()                    # 4. read the response
            elapsed = time.time() - start
            if reply.startswith(b"VER=") and elapsed < 0.5:   # 5. check content AND timing
                return {"passed": True, "reply": reply, "time_s": elapsed}
        return {"passed": False, "reason": "no valid reply after 3 attempts"}   # 6. clear diagnostics
```

**Remember:** bounded retries, clear failure messages, always release the port.

## 8. Threading vs multiprocessing

**Short answer:** Threads share memory; in CPython the Global Interpreter Lock (GIL) limits parallel Python bytecode, so CPU-heavy work uses multiprocessing.

| | Threads | Multiprocessing |
| --- | --- | --- |
| Memory | Shared | Separate per process |
| CPU-heavy Python work | Limited by the GIL | Runs in parallel |
| I/O-heavy work (serial, sockets) | Works well | Works, with more overhead |

**Remember:** waiting on a serial port releases the GIL, so threads are fine for I/O-heavy test automation.

## 9. How do you parse a binary packet?

**Short answer:** Check the length first, then decode fields explicitly with `struct`.

```python
import struct

# Packet layout: [ID: 1 byte][LENGTH: 2 bytes, little-endian][PAYLOAD...]
def parse(packet: bytes):
    if len(packet) < 3:                           # validate BEFORE indexing
        raise ValueError("packet too short")
    pkt_id, length = struct.unpack_from("<BH", packet, 0)   # '<' little-endian, B = 1 byte, H = 2 bytes
    payload = packet[3:3 + length]
    if len(payload) != length:
        raise ValueError("truncated payload")
    return pkt_id, payload
```

**Remember:** validate length first, and state the byte order (`<` or `>`) in the format string.

## 10. How would Python help debug firmware?

**Short answer:** Build a repeatable tool, so a failure can be reproduced instead of chased by hand.

A useful tool:

- Timestamps serial logs
- Sends test commands
- Captures traces
- Decodes protocol frames
- Stores artifacts (logs, captures) for each run

**Remember:** automation should make failures reproducible, not just make manual work faster.
