# Advanced 03 Python Interview Questions

> 50-question deep-dive track. Use each Q&A as a flashcard: first answer aloud, then compare with the model answer.

## 1. Why is Python valuable to an embedded engineer?

It is useful for test automation, serial tools, log parsing, packet generation, CI utilities, manufacturing tools, and data analysis.

## 2. List versus tuple?

Lists are mutable; tuples are immutable. A tuple is useful for fixed records or values that should not be changed.

## 3. What is a set and why useful in testing?

A set stores unique hashable elements and supports fast average-case membership checks, useful for duplicate detection and expected-value comparisons.

## 4. What is a dict?

A hash-table-based mapping from keys to values, useful for decoded packets, register metadata, and test configurations.

## 5. What is a generator?

A lazy iterator that yields values as requested, useful for processing large logs or streams without loading everything into memory.

## 6. What is a context manager?

It controls setup and cleanup around a block, commonly used with with for files, serial resources, and locks.

## 7. How would you structure a UART test tool?

Separate transport, framing, command sequencing, validation, logging, and report generation so each can be tested independently.

## 8. How do you parse binary data safely?

Validate packet length first, then decode using struct or explicit byte operations with defined endianness and bounds checks.

## 9. Why is struct.pack useful?

It converts Python values to a defined binary layout, making packet generation reproducible and explicit about field format.

## 10. What is bytes versus bytearray?

bytes is immutable binary data; bytearray is mutable. Use bytearray when a buffer must be modified in place.

## 11. What is slicing?

It creates a sequence subset using start/stop/step. For large binary data, be aware that many slices create copies.

## 12. What is a shallow copy?

It copies the outer container while referenced nested objects remain shared.

## 13. What is a deep copy?

It recursively copies nested structures when supported, creating independent objects at the cost of more memory/work.

## 14. What is an exception hierarchy?

Exceptions form classes that can be caught at suitable abstraction levels. Embedded test code should distinguish expected test failures from infrastructure failures.

## 15. How do you avoid hiding test failures?

Catch only exceptions you can recover from, log context, and let unexpected errors fail the test instead of converting them to generic pass/fail results.

## 16. Threading or multiprocessing for test automation?

Threads are convenient for I/O concurrency; multiprocessing can bypass CPython interpreter limitations for CPU-heavy Python work. Choose based on workload and synchronization needs.

## 17. What is asyncio useful for?

It coordinates many I/O-bound operations using cooperative scheduling, which can suit network/device orchestration tools.

## 18. How would you implement a retry strategy?

Bound the number of retries, use a timeout, apply backoff for recoverable failures, and distinguish transient errors from deterministic configuration errors.

## 19. How do you parse logs robustly?

Use structured fields when possible, validate timestamps/IDs, tolerate unrelated lines, and retain the original log as an artifact.

## 20. What is a fixture in testing?

Controlled setup/state provided to a test, such as a simulated device, serial endpoint, or configuration.

## 21. How would Python control a modem?

Open the transport, send AT commands through a command/response engine, parse expected terminators and unsolicited messages, enforce timeouts, and record transcripts.

## 22. Why are timestamps important in HIL testing?

They allow correlation between commands, hardware events, and firmware logs, especially when failures are timing-sensitive.

## 23. What is property-based testing?

Testing generated input combinations against general invariants instead of only fixed examples. It is useful for packet parsers and state machines.

## 24. How would you fuzz a binary parser in Python?

Generate valid and invalid byte sequences, enforce input-size limits, and assert that the parser never crashes, hangs, or reads beyond the provided buffer.

## 25. What is a mock?

A test double that simulates a collaborator and often records calls or returns controlled results.

## 26. Stub versus mock?

A stub mainly supplies controlled answers; a mock is usually also used to verify interactions or call expectations.

## 27. What is dependency injection in Python test tooling?

Pass the serial/network/device interface into the test component so a fake implementation can replace real hardware.

## 28. How do you handle flaky hardware tests?

Separate transport failures from product failures, capture artifacts, add bounded retries only for known transient conditions, and track failure rate instead of hiding it.

## 29. Why should test timeouts be explicit?

An unbounded read can hang CI indefinitely. Explicit timeouts turn a hang into a diagnosable failure.

## 30. How would you compare firmware versions?

Parse version components semantically rather than comparing strings lexicographically when the scheme is numeric.

## 31. How do you store test configuration?

Use a typed schema or validated mapping and reject invalid values early. Keep environment-specific secrets outside the repository.

## 32. Why avoid hard-coded serial ports?

Ports differ across systems. Resolve by stable identifiers or configuration and verify the selected device before testing.

## 33. What is CRC testing?

Compare the device/parser implementation against known vectors and an independent implementation, including parameter settings such as polynomial and initialization.

## 34. How would you test endian conversion?

Use known byte patterns such as 0x12345678 and verify both encoding and decoding against the protocol specification.

## 35. What is a virtual environment?

An isolated Python environment for dependencies, helping make test tooling reproducible across machines.

## 36. Why pin dependencies in CI?

It reduces unexpected environment changes. Update deliberately and test newer versions rather than allowing uncontrolled upgrades.

## 37. What is a CLI entry point?

A stable command interface for scripts, useful for automated firmware flashing, packet generation, regression runs, and report creation.

## 38. How would you design a serial log recorder?

Use a streaming reader, add timestamps, write raw and parsed artifacts separately, and rotate files if long-duration tests are required.

## 39. How do you handle binary plus text logs?

Keep them in separate paths or explicit record formats. Do not assume arbitrary device bytes are valid UTF-8.

## 40. What is a coroutine?

A resumable computation used by cooperative async frameworks. It is not the same as an OS thread.

## 41. Why can Python memory usage matter even on a PC?

Large logs or captures can make tests slow or crash. Streaming and bounded buffering produce more predictable tooling.

## 42. How would you benchmark a parser?

Use representative packet sizes and worst-case malformed inputs, measure multiple runs, and separate parser time from I/O time.

## 43. How do you make a test deterministic?

Control timeouts, randomness seeds where possible, device state, network dependencies, and test ordering. Preserve artifacts for failures.

## 44. What is serialization?

Converting structured data into a transport/storage representation. Define versioning, field widths, endianness, and validation rules.

## 45. Why validate every externally supplied length?

A length field is untrusted input. Checking it before indexing or allocation prevents out-of-bounds access and denial-of-service style parser failures.

## 46. How would you build a firmware register checker?

Describe registers in metadata, read values through a transport layer, mask reserved bits, compare expected fields, and report differences with addresses/field names.

## 47. How can Python help with manufacturing?

It can automate flashing, calibration, serial-number provisioning, functional checks, result capture, and traceability records.

## 48. What is the main Python interview message for an embedded role?

Show that you can use Python to make firmware development repeatable: automate hardware tests, decode data, reproduce failures, and generate evidence.

## 49. How would you make a Python hardware test safe to rerun?

Reset device state at setup, clean up resources in teardown, use unique output artifacts, and make provisioning/calibration steps idempotent where possible.

## 50. How do you test timing-sensitive firmware with Python?

Use monotonic timestamps, explicit timeout budgets, synchronized triggers when available, and capture raw traces so software test timing can be correlated with device behavior.
