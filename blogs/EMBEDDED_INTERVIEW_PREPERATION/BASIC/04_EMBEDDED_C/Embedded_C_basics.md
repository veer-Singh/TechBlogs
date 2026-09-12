# Embedded C Interview Questions

## 1. What is memory-mapped I/O?

Peripherals can be exposed at fixed memory addresses so CPU load/store operations access hardware registers. The device header normally provides typed definitions and bit masks rather than application code hard-coding addresses.

## 2. Why must peripheral registers often be `volatile`?

A register value can change because of hardware activity, not because of a C statement. `volatile` prevents the compiler from assuming repeated reads have the same value.

## 3. What is a critical section?

A critical section is code executed with a synchronization mechanism that prevents an unsafe concurrent access pattern. On a small MCU this might be a short interrupt-masked region; in RTOS code it could be a mutex or scheduler-aware primitive. The correct mechanism depends on who shares the resource.

## 4. Why should an ISR be short?

Long ISRs increase interrupt latency and can delay higher-priority work. An ISR should normally capture the minimum required state, clear the interrupt source, and defer processing to a task/thread or main loop.

## 5. What is a watchdog?

A watchdog resets or otherwise recovers a system when software fails to service it as expected. Robust designs do not simply "kick the watchdog everywhere"; they make the watchdog reflect meaningful system health.

## 6. Polling vs interrupt?

Polling repeatedly checks a condition and is simple but can waste CPU time or introduce variable response time. Interrupts let hardware signal an event, improving efficiency for sparse asynchronous events, but they increase concurrency complexity.

## 7. What is DMA?

Direct Memory Access allows a DMA controller to move data between a peripheral and memory, or between memory regions, with less CPU involvement. Correct use requires understanding buffer ownership, alignment, cache coherency on cached CPUs, and completion/error handling.

## 8. Why use bit masks?

Bit masks let code modify only the intended fields of a register.

```c
reg |=  (1U << 3);      /* set */
reg &= ~(1U << 3);      /* clear */
reg ^=  (1U << 3);      /* toggle */
```

## 9. What is a linker script used for?

It controls how sections are placed in memory and how symbols are resolved. Embedded linker scripts commonly place vector tables, code, initialized data, zero-initialized data, stack, and sometimes special memory regions.

## 10. What happens after reset?

A typical MCU boot flow loads an initial stack value and reset handler from the vector table, executes startup code, initializes memory required by the C runtime, performs low-level hardware setup, and enters `main()`. Exact behavior is architecture and toolchain dependent.

## 11. What is the difference between a pointer and an array?

An array owns a fixed-size contiguous collection, while a pointer stores an address and can refer to different objects. An array name often converts to a pointer to its first element, but the types are not interchangeable.

```c
uint8_t buffer[16];
uint8_t* cursor = buffer;

cursor[0] = 0x55;
```

## 12. Why should pointer bounds be checked?

An invalid pointer or index can overwrite unrelated memory, registers, or control data. Embedded systems should validate lengths before every copy and access.

```c
bool read_byte(const uint8_t* data, size_t length, size_t index, uint8_t* value)
{
	if (data == NULL || value == NULL || index >= length) {
		return false;
	}

	*value = data[index];
	return true;
}
```

## 13. What is the difference between `memcpy` and `memmove`?

`memcpy` requires non-overlapping regions. `memmove` safely handles overlap by choosing a copy direction or equivalent strategy.

```c
char text[16] = "abcdef";
memmove(&text[1], &text[0], 5); /* Safe when regions overlap. */
```

## 14. Why is `sizeof` safer than hard-coded buffer sizes?

`sizeof` derives the size from the actual object, reducing maintenance errors when the declaration changes.

```c
uint8_t packet[32];
memset(packet, 0, sizeof(packet));
```

## 15. What is the difference between stack and static storage?

Automatic local objects usually use the stack and exist for a function call. Static objects have program lifetime and can consume RAM for the entire application.

```c
void sample_task(void)
{
	uint8_t local_buffer[64];       /* Stack storage. */
	static uint32_t call_count;     /* Static storage. */
	call_count++;
	(void)local_buffer;
}
```

## 16. Why should recursion usually be avoided in small firmware?

Each recursive call consumes additional stack, making worst-case memory use difficult to prove. Iterative state machines are usually easier to bound.

```c
uint32_t factorial_iterative(uint32_t value)
{
	uint32_t result = 1u;
	while (value > 1u) {
		result *= value--;
	}
	return result;
}
```

## 17. What are structures useful for in embedded C?

Structures group related fields such as configuration, messages, and register views. Their padding and alignment must be considered for hardware or wire formats.

```c
typedef struct {
	uint16_t sample;
	uint8_t channel;
	uint8_t valid;
} sensor_result_t;
```

## 18. Why can packed structures be dangerous?

Packing can create misaligned members, causing slower access or faults on some targets. Explicit byte serialization is safer for portable protocols.

```c
uint32_t decode_le32(const uint8_t bytes[4])
{
	return ((uint32_t)bytes[0]) |
		   ((uint32_t)bytes[1] << 8) |
		   ((uint32_t)bytes[2] << 16) |
		   ((uint32_t)bytes[3] << 24);
}
```

## 19. What is an enumeration useful for?

An enumeration gives meaningful names to related states or modes and makes state-machine code easier to review.

```c
typedef enum {
	DRIVER_IDLE,
	DRIVER_BUSY,
	DRIVER_ERROR
} driver_state_t;
```

## 20. What is the purpose of `static` at file scope?

It gives a function or object internal linkage, preventing other translation units from depending on an implementation detail.

```c
static uint32_t error_count;

static void record_error(void)
{
	error_count++;
}
```

## 21. What is `extern` used for?

`extern` declares an object or function defined in another translation unit. The definition must exist exactly once in the final link.

```c
/* public_status.h */
extern volatile uint32_t system_status;
```

## 22. Why use include guards?

Include guards prevent a header from being processed more than once in the same translation unit.

```c
#ifndef SENSOR_DRIVER_H
#define SENSOR_DRIVER_H

void sensor_init(void);

#endif
```

## 23. What is a function pointer used for in firmware?

Function pointers support callbacks, interrupt dispatch tables, and hardware abstraction without large conditional chains.

```c
typedef void (*event_handler_t)(uint32_t event);

static event_handler_t handler;

void register_handler(event_handler_t callback)
{
	handler = callback;
}
```

## 24. What is the difference between `const` pointer forms?

`const uint8_t*` prevents modification through the pointer. `uint8_t* const` prevents changing the pointer itself after initialization.

```c
void inspect(const uint8_t* data, size_t length)
{
	for (size_t index = 0; index < length; ++index) {
		process(data[index]);
	}
}
```

## 25. Why are integer widths important in embedded C?

Types such as `uint8_t` and `uint32_t` make register fields, packet layouts, and arithmetic assumptions explicit across toolchains.

```c
uint32_t control = 0u;
control |= UINT32_C(1) << 31;
```

## 26. What is integer promotion?

Small integer types are often promoted to `int` during expressions. This can affect signedness, comparisons, shifts, and register operations.

```c
uint8_t value = 0x80u;
uint32_t shifted = (uint32_t)value << 8;
```

## 27. Why prefer unsigned types for bit manipulation?

Unsigned shifts and overflow have defined modulo behavior, while signed shifts and signed overflow can be implementation-defined or undefined.

```c
uint32_t mask = UINT32_C(1) << bit_index;
uint32_t field = (register_value & mask) != 0u;
```

## 28. What is a linker error versus a compiler error?

A compiler error occurs while translating a source file. A linker error occurs while combining objects and resolving symbols or sections.

```c
/* Declaration without a matching definition can produce a linker error. */
extern int missing_symbol;
int read_symbol(void) { return missing_symbol; }
```

## 29. Why use assertions in Embedded C?

Assertions catch violated assumptions during development. Production behavior must be defined because stopping in an assertion handler may affect availability.

```c
assert(buffer != NULL);
assert(length <= BUFFER_CAPACITY);
```

## 30. How should Embedded C handle external input safely?

Validate lengths, ranges, command types, state, and checksums before using external data. Reject malformed input without corrupting parser state.

```c
bool accept_frame(const uint8_t* frame, size_t length)
{
	if (frame == NULL || length < 3u || length > 64u) {
		return false;
	}

	return crc8(frame, length - 1u) == frame[length - 1u];
}
```

