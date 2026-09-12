# Python Interview Questions for Embedded Engineers

## 1. Why is Python useful to embedded engineers?

Python is commonly used for test automation, serial tools, log processing, firmware validation, manufacturing scripts, packet generation, data analysis, and CI utilities. It often sits beside the firmware rather than running on the microcontroller.

## 2. List vs tuple?

A list is mutable; a tuple is immutable after creation. Tuples are useful for fixed records and can communicate intent that a sequence should not be modified.

## 3. What is a set?

A set is an unordered collection of unique hashable elements. It is useful for membership checks and removing duplicates.

```python
seen = {1, 2, 3}
if 2 in seen:
    print("present")
```

## 4. Dictionary use in test automation?

Dictionaries map keys to values and are useful for configuration, register descriptions, decoded packets, and test results.

## 5. What is a generator?

A generator yields values lazily, which can reduce memory usage when processing a large log or stream.

```python
def lines(stream):
    for line in stream:
        yield line.strip()
```

## 6. What is a context manager?

A context manager controls setup/cleanup, commonly via `with`. This is useful for serial ports, files, locks, and temporary resources.

## 7. How would you automate a UART test?

Open the port, configure baud/data bits/parity/timeout, send a known request, parse the response, validate timing/content, record the result, and always close the resource. For hardware-in-the-loop, include retry limits and clear failure diagnostics.

## 8. Threading vs multiprocessing?

Threads share a process memory space. In CPython, the Global Interpreter Lock affects execution of Python bytecode in typical builds, so CPU-heavy workloads often use multiprocessing or native extensions. I/O-heavy test automation can still benefit from threads.

## 9. How do you parse a binary packet?

Prefer explicit byte handling and validate length before indexing. `struct` is useful for converting byte sequences to numeric fields.

```python
import struct
value, = struct.unpack_from('<H', packet, 0)
```

## 10. How would Python help debug firmware?

Build a repeatable tool that timestamps serial logs, sends test commands, captures traces, decodes protocol frames, and stores artifacts. Automation should make a failure reproducible instead of just making a manual process faster.
