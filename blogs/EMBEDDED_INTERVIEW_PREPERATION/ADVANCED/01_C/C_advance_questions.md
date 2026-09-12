# Advanced 01 C Interview Questions

> Clean, numbered interview Q&A for embedded C fundamentals.

## 1. What exactly does `volatile` guarantee?

`volatile` tells the compiler that the value may change outside normal program flow. This prevents optimization that would incorrectly remove or reorder reads/writes for memory-mapped registers and shared hardware state.

## 2. Why is `volatile` not a mutex?

It does not provide atomicity or synchronization. It only prevents the compiler from assuming the value never changes.

## 3. When would you use `volatile const`?

For read-only hardware registers or externally controlled memory that firmware must read but never write through the C expression.

## 4. What is undefined behavior in C?

Undefined behavior is code that the C standard does not define. It may work on one platform and fail on another, especially when optimization is enabled.

## 5. What is strict aliasing?

Strict aliasing restricts which pointer types may access the same object. Violating it can cause incorrect code generation and subtle bugs.

## 6. What is alignment and why does it matter?

Alignment is the address requirement for an object type. Misaligned accesses can fault or be slower on some CPUs.

## 7. What is a dangling pointer?

A dangling pointer points to memory whose lifetime has ended. Dereferencing it is undefined behavior.

## 8. What is a memory leak?

A memory leak happens when allocated memory is no longer reachable but is never freed. In embedded systems it can exhaust RAM over time.

## 9. What is reentrancy?

A function is reentrant if it can be safely called while another invocation is active without corrupting shared data.

## 10. What is a callback function?

A callback is a function pointer passed to another module so that module can invoke it later for events, state transitions, or notifications.

## 11. Why use `uint32_t` instead of `unsigned long`?

`uint32_t` guarantees a fixed 32-bit type. This improves portability and clarity for protocol and register definitions.

## 12. What is endianness?

Endianness defines the byte order of multi-byte values in memory. It matters for protocols, registers, and binary payloads.

## 13. What is a memory barrier?

A memory barrier constrains memory access ordering. It is not the same as `volatile` and is often required in synchronization or hardware code.

## 14. What is integer promotion?

Smaller integer types are promoted in expressions, which can affect comparisons, arithmetic, and shifts.

## 15. What is a circular buffer?

A circular buffer is a fixed-size queue that wraps around. It is commonly used for UART and sensor data streams.

## 16. Why is stack overflow dangerous?

A stack overflow can overwrite nearby memory and corrupt code or data. It is especially dangerous in deeply nested or recursive firmware.

## 17. What is a memory pool?

A memory pool preallocates fixed-size blocks for deterministic allocation and release. It avoids unpredictable heap behavior in embedded code.

## 18. Why is `memset` on integers a common bug?

`memset` works byte-by-byte. Filling an integer with `memset` does not reliably produce the correct integer value in the way a proper assignment does.

## 19. What is the difference between `const int *p` and `int *const p`?

`const int *p` means the pointed-to value is constant. `int *const p` means the pointer itself cannot change after initialization.

## 20. Why are linker scripts important in embedded systems?

They define where code and data are placed in memory: flash, RAM, stack, and heap regions.

---

# Final review checklist

- Prefer fixed-width integer types for hardware and protocol code.
- Use `volatile` only for hardware-visible or externally modified state.
- Keep pointer ownership and lifetime explicit.
- Validate alignment and aliasing assumptions during review.

# Structure and Union Interview Questions & Answers — Advanced

## 1. How is structure size calculated?
Start with the first member, place subsequent members according to their alignment requirements, insert padding where necessary, and round the total size to satisfy the structure's alignment requirement.

Example:

```c
struct A {
    char c;
    int i;
};
```

A common implementation may place `i` at offset 4, making the size 8, but the exact result is implementation-dependent.

## 2. What is structure padding?
Padding is compiler-inserted storage used to satisfy alignment constraints.

```c
struct A {
    char c;
    int i;
};
```

Typical layout:

```text
offset 0 : char
offset 1-3 : padding
offset 4-7 : int
```

## 3. What is tail padding?
Padding added at the end of a structure so that consecutive elements of an array remain correctly aligned.

## 4. Why does structure member order matter?
Reordering members can reduce padding and therefore reduce memory consumption.

Example:

```c
struct Bad {
    char a;
    int b;
    char c;
};

struct Better {
    int b;
    char a;
    char c;
};
```

The exact sizes depend on the target ABI/compiler.

## 5. What is `offsetof()`?
`offsetof()` gives the byte offset of a structure member from the beginning of the structure.

```c
#include <stddef.h>

size_t offset = offsetof(struct Sensor, value);
```

## 6. Why is `offsetof()` useful in embedded systems?
It helps verify memory layouts for communication packets, shared-memory structures, drivers, and ABI interfaces.

## 7. What is a packed structure?
A packed structure requests reduced/eliminated padding between members, depending on compiler support.

For GCC:

```c
struct __attribute__((packed)) Packet {
    uint8_t id;
    uint32_t value;
};
```

## 8. What is the danger of packed structures?
Unaligned members may cause slower accesses or faults on architectures that do not support certain unaligned accesses. Packed structures should therefore be used carefully.

## 9. Is `sizeof(struct)` always equal to the sum of member sizes?
No. Padding and alignment can make the structure larger.

## 10. Is union size always equal to its largest member?
It is large enough to contain its largest member and satisfy the union's alignment requirements. In common implementations it equals the largest member size, but the standard does not require that simplistic formula in every case.

## 11. What happens when a union member is written?
The stored bytes are interpreted according to the member used to access them. Only one member's value should generally be treated as active at a time; reading another member for type-punning has portability considerations.

## 12. Structure vs union memory allocation?

```text
struct:
member A -> separate storage
member B -> separate storage
member C -> separate storage

union:
member A
member B  -> same storage
member C
```

## 13. What is an anonymous structure?
Some compilers/language modes support anonymous structures as an extension or through standard mechanisms in newer C standards. Portability should be considered.

## 14. What is an anonymous union?
An anonymous union allows its members to be accessed directly from the containing scope in implementations/language modes that support it.

Example:

```c
union {
    uint32_t word;
    uint8_t bytes[4];
};
```

## 15. What is a nested union inside a structure?

```c
struct Message {
    uint8_t type;

    union {
        uint32_t value;
        float temperature;
    } data;
};
```

This is useful when a message has a common header but different payload representations.

## 16. What is a tagged union?
A tagged union stores a discriminator indicating which union member is currently valid.

```c
enum Type {
    TYPE_INT,
    TYPE_FLOAT
};

struct Value {
    enum Type type;

    union {
        int i;
        float f;
    } data;
};
```

This is safer than using a union without knowing which member is active.

## 17. Why are tagged unions useful in embedded systems?
They are useful for command packets, event messages, state-machine data, and protocol payloads where different message types have different data.

## 18. What is bit-field memory layout?
Bit-fields can share storage units, but allocation order and layout are implementation-defined. Do not assume a portable bit ordering for wire protocols.

## 19. Can bit-fields be used for hardware registers?
They can be used on some platforms, but portable register definitions often prefer explicit masks and shifts because bit-field layout can be compiler/ABI dependent.

## 20. What is a safer alternative to bit-fields for registers?

```c
#define ENABLE_MASK  (1u << 0)
#define MODE_MASK    (3u << 1)

reg |= ENABLE_MASK;
reg = (reg & ~MODE_MASK) | (mode << 1);
```

## 21. What is structure aliasing?
A pointer to one structure object can be used to access that object according to the rules of C's effective type and aliasing requirements. Arbitrary casting between unrelated structure types can violate those rules.

## 22. Can you compare structures using `==`?
In standard C, structures cannot generally be compared directly with `==`.

Use member-by-member comparison.

## 23. Can you use `memcmp()` to compare structures?
Not reliably for logical equality because padding bytes may contain unspecified values.

```c
memcmp(&a, &b, sizeof(a));
```

can report inequality even when all logical members are equal.

## 24. Can you use `memcpy()` with structures?
Yes, copying an object representation with `memcpy()` is valid, provided the destination is appropriately sized/aligned.

## 25. Why can `memcpy()` of a structure be problematic for pointers?
It copies pointer values, not the objects they point to. This can create shallow copies.

## 26. What is shallow copy of a structure?
A structure copy copies member values directly. If the structure contains pointers, both structures may point to the same underlying object.

## 27. What is deep copy?
A deep copy duplicates dynamically referenced data so the copied structure owns separate storage.

## 28. Structure alignment and DMA
DMA buffers may require specific alignment and memory-region constraints. Structure layout alone does not guarantee that a buffer satisfies a peripheral's DMA requirements.

## 29. Structure and endianness
A structure's in-memory byte representation is affected by target endianness. Sending a structure directly over UART/TCP/CAN/Modbus is therefore not automatically portable.

## 30. Why should you avoid sending a structure directly over a communication interface?
Because of:

- Padding
- Alignment
- Endianness
- Compiler/ABI differences
- Bit-field layout
- Data type sizes

Prefer explicit serialization/deserialization.

## 31. How do you serialize a structure safely?
Convert each field explicitly into the required byte order and format.

```c
buffer[0] = value & 0xFF;
buffer[1] = (value >> 8) & 0xFF;
```

## 32. What is memory-mapped register structure?
A structure can describe registers at fixed addresses.

```c
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t STATUS;
    volatile uint32_t DATA;
} UART_Regs;

#define UART0 ((UART_Regs *)0x40000000u)
```

Actual addresses and definitions must come from the MCU reference manual.

## 33. Why is `volatile` used for register structures?
Hardware registers can change independently of normal program flow. `volatile` tells the compiler that accesses must not be optimized away as ordinary memory accesses.

## 34. Structure access pattern: direct object

```c
struct Sensor s;
s.value = 10;
```

Access is through a concrete object.

## 35. Structure access pattern: pointer

```c
struct Sensor *p = &s;
p->value = 10;
```

Useful for functions and dynamically selected objects.

## 36. Structure access pattern: array

```c
struct Sensor sensors[10];

sensors[3].value = 100;
```

The address of an array element is calculated using the structure's `sizeof`.

## 37. Why does structure layout matter for cache performance?
Poor member arrangement or large structures can increase memory traffic and cache usage on cache-enabled MCUs/processors.

## 38. Array of structures vs structure of arrays?

Array of structures:

```c
struct Sensor {
    float temperature;
    float pressure;
};

struct Sensor sensors[100];
```

Structure of arrays:

```c
struct Sensors {
    float temperature[100];
    float pressure[100];
};
```

AoS is often convenient when processing complete objects. SoA can improve locality when processing one field across many objects, depending on workload and architecture.

## 39. What is false sharing?
On multicore systems, independent variables located on the same cache line can cause unnecessary cache-coherence traffic when different cores modify them.

## 40. How can structure design reduce memory usage?
Consider:

- Member ordering
- Appropriate integer widths
- Avoiding unnecessary padding
- Splitting hot and cold data
- Avoiding unnecessary pointers
- Using compact representations where safe

## 41. What is ABI compatibility with structures?
The ABI defines conventions such as structure layout, alignment, calling conventions, and return rules. Changing structure layout can break binary compatibility.

## 42. What is a flexible array member?

```c
struct Packet {
    uint16_t length;
    uint8_t data[];
};
```

The flexible array member does not contribute storage for elements to `sizeof(struct Packet)`, and extra storage can be allocated for the payload.

## 43. Why are flexible array members useful in embedded systems?
They can represent variable-length packet buffers efficiently, but allocation and bounds checking must be handled carefully.

## 44. What happens if a structure contains a zero-width bit-field?
A zero-width bit-field can force the next bit-field to start at the next allocation unit boundary, subject to C implementation rules.

## 45. Advanced interview question: Why can two compilers produce different structure sizes?
Because ABI, alignment rules, packing options, target architecture, and compiler-specific extensions can differ.
