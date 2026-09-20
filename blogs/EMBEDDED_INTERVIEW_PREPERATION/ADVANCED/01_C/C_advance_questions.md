# Advanced C Interview Questions

How to use this file: read the **Short answer** first, then the details and the commented example. Each part has its own numbering.

## Contents

| Part | Topic | Questions |
| --- | --- | --- |
| A | Embedded C fundamentals (quick round) | 1-20 |
| B | Advanced C deep dive | 1-50 |
| C | Structures and unions | 1-45 |

The Part B questions were moved here from the end of the FreeRTOS file, where they had been pasted by mistake.

---

## Part A: Embedded C fundamentals (quick round)

## A1. What exactly does `volatile` guarantee?

**Short answer:** The compiler must perform every access to that object and cannot remove or reorder it.

It is for memory-mapped registers and hardware-visible state. It does not give atomicity.

## A2. Why is `volatile` not a mutex?

**Short answer:** It stops compiler assumptions, but does not stop two contexts from changing the object at the same time.

## A3. When would you use `volatile const`?

**Short answer:** For a value firmware may read but never write, such as a read-only hardware status register.

```c
volatile const uint32_t *const STATUS = (volatile const uint32_t *)0x40000004u;
```

## A4. What is undefined behavior in C?

**Short answer:** Code the standard gives no meaning to. It may work on one platform and fail on another, especially with optimization.

## A5. What is strict aliasing?

**Short answer:** A rule about which pointer types may access the same object. Breaking it can produce wrong code.

## A6. What is alignment and why does it matter?

**Short answer:** The address requirement for a type. Misaligned access can fault or be slow.

## A7. What is a dangling pointer?

**Short answer:** A pointer to storage whose lifetime has ended. Dereferencing it is undefined behaviour.

```c
int *bad(void) { int x = 5; return &x; }   /* x is gone when the function returns */
```

## A8. What is a memory leak?

**Short answer:** Allocated memory that is no longer reachable but never freed. In firmware it can exhaust RAM over time.

## A9. What is reentrancy?

**Short answer:** A function is reentrant if it can be called again while an earlier call is active, without corrupting shared data.

## A10. What is a callback function?

**Short answer:** A function pointer passed to another module so it can be called later.

## A11. Why use `uint32_t` instead of `unsigned long`?

**Short answer:** `uint32_t` is exactly 32 bits everywhere. `unsigned long` may be 32 or 64.

## A12. What is endianness?

**Short answer:** The byte order of multi-byte values in memory. It matters for protocols, registers, and binary payloads.

## A13. What is a memory barrier?

**Short answer:** A constraint on the order of memory accesses. It is not the same as `volatile`.

## A14. What is integer promotion?

**Short answer:** Small integer types are converted to `int` in expressions, which can change comparisons, arithmetic, and shifts.

## A15. What is a circular buffer?

**Short answer:** A fixed-size queue that wraps around. Common for UART and sensor streams.

## A16. Why is stack overflow dangerous?

**Short answer:** It silently overwrites nearby memory, corrupting code or data.

## A17. What is a memory pool?

**Short answer:** Pre-allocated fixed-size blocks with predictable allocation and release.

## A18. Why is `memset` on integers a common bug?

**Short answer:** `memset` fills bytes, not integers.

```c
int a[4];
memset(a, 1, sizeof a);     /* each int becomes 0x01010101, NOT 1 */
for (int i = 0; i < 4; i++) a[i] = 1;   /* correct */
```

## A19. `const int *p` versus `int *const p`

**Short answer:** Read right to left.

| Declaration | Meaning |
| --- | --- |
| `const int *p` | The value pointed to is constant |
| `int *const p` | The pointer itself cannot change |

## A20. Why are linker scripts important in embedded systems?

**Short answer:** They decide where code and data go: flash, RAM, stack, and heap.

## Final review checklist

- Prefer fixed-width integer types for hardware and protocol code.
- Use `volatile` only for hardware-visible or externally modified state.
- Keep pointer ownership and lifetime explicit.
- Validate alignment and aliasing assumptions during review.

---

## Part B: Advanced C deep dive

## B1. What exactly does `volatile` guarantee?

**Short answer:** The compiler cannot freely remove or reorder accesses to that object.

It does not give atomicity, inter-thread synchronization, or cache coherency.

## B2. Why is `volatile` not a mutex?

**Short answer:** It only affects compiler optimization. It does not stop two execution contexts from modifying an object at the same time.

Use a proper synchronization primitive or an atomic operation.

## B3. When would you use `volatile const`?

**Short answer:** For a value that software reads from an external source but must not modify, such as a read-only status register.

## B4. What is a sequence point (sequencing) in modern C?

**Short answer:** Rules for the order in which evaluations happen.

Modifying and reading the same scalar in a way the rules do not order is undefined behaviour.

```c
int i = 0;
int x = i++ + i++;     /* undefined: i is modified twice with no ordering between them */
```

## B5. What is undefined behavior, and why is it dangerous in firmware?

**Short answer:** The standard gives no required result, so optimization can expose failures hidden at lower optimization levels.

## B6. What is implementation-defined behavior?

**Short answer:** The implementation chooses the behaviour and must document it.

Example: the result of right-shifting a negative signed number.

## B7. What is unspecified behavior?

**Short answer:** The implementation may pick any of several allowed behaviours and need not document which.

Example: the order in which function arguments are evaluated.

## B8. Why use `uint32_t` instead of `unsigned long`?

**Short answer:** `uint32_t` states an exact 32-bit width. That matters for register fields, packet formats, and binary layouts.

## B9. What is strict aliasing?

**Short answer:** Rules for which lvalue types may access an object. Violating them can cause undefined behaviour and surprising compiler output.

```c
float f = 1.0f;
uint32_t bits = *(uint32_t *)&f;      /* violates strict aliasing */

uint32_t bits2;
memcpy(&bits2, &f, sizeof bits2);     /* correct way to reinterpret the bytes */
```

## B10. How can you legally inspect the bytes of an object?

**Short answer:** Through a character type such as `unsigned char`.

```c
const unsigned char *p = (const unsigned char *)&value;   /* always allowed */
for (size_t i = 0; i < sizeof value; i++) { printf("%02X ", p[i]); }
```

## B11. What is alignment?

**Short answer:** The address rule for an object type. Misaligned accesses may be slow, fault, or be unsupported.

## B12. Why can packed structs be risky?

**Short answer:** Packing creates misaligned members and depends on the compiler and ABI.

Use explicit byte serialization when a wire format must be exact.

## B13. Pointer to const versus const pointer

**Short answer:** Pointer-to-const stops changes through that pointer. A const pointer cannot be repointed. Both can be combined.

## B14. What is a callback table?

**Short answer:** An array or struct of function pointers, used to dispatch by event, command, or device type.

```c
typedef void (*cmd_fn)(const uint8_t *args);
static const cmd_fn handlers[] = { cmd_start, cmd_stop, cmd_reset };   /* index = command id */

if (id < sizeof handlers / sizeof handlers[0]) { handlers[id](args); }   /* bounds check first */
```

## B15. How would you make a callback API safe for ISR use?

**Short answer:** Define whether registration and invocation can overlap, keep callbacks short, use ISR-safe synchronization, and never block.

## B16. What does `static` mean for a file-scope symbol?

**Short answer:** Internal linkage: the symbol is visible only in that file.

## B17. What does `static` mean for a local variable?

**Short answer:** It has static storage duration and keeps its value between calls.

## B18. What is `extern` used for?

**Short answer:** It declares a symbol defined elsewhere, so files can share one definition.

## B19. What is a translation unit?

**Short answer:** A source file after preprocessing (headers and macros expanded), compiled as one unit.

## B20. Why use header include guards?

**Short answer:** To stop multiple inclusion in one translation unit, which would cause duplicate definitions.

## B21. What does `inline` actually mean?

**Short answer:** Mainly a linkage rule (it allows multiple definitions). It does not force the compiler to inline the code.

## B22. Macro versus inline function for register helpers

**Short answer:** Prefer typed inline functions. Use macros for token pasting, conditional compilation, and constant patterns.

## B23. Why parenthesize macro arguments?

**Short answer:** Operator precedence can otherwise change the result.

```c
#define SQUARE_BAD(x)  x * x
#define SQUARE_OK(x)   ((x) * (x))

SQUARE_BAD(a + 1);    /* expands to a + 1 * a + 1, which is wrong */
SQUARE_OK(a + 1);     /* expands to ((a + 1) * (a + 1)), which is right */
```

## B24. What is a dangling pointer?

**Short answer:** A pointer to storage whose lifetime ended. Dereferencing it is undefined behaviour.

## B25. What is a memory leak?

**Short answer:** Allocated storage becomes unreachable without being freed. Long-running firmware eventually fails.

## B26. Why is dynamic allocation often constrained in embedded systems?

**Short answer:** Fragmentation, unbounded allocation time, and failure behaviour that is hard to prove.

Some systems still use it under strict rules.

## B27. What is a memory pool?

**Short answer:** Fixed same-size blocks for deterministic allocation and release, avoiding general heap fragmentation.

## B28. What is reentrancy?

**Short answer:** A function is reentrant when interrupted or concurrent calls cannot corrupt shared state.

Hidden global mutable state usually breaks reentrancy.

## B29. Why should ISR code avoid non-reentrant library functions?

**Short answer:** An interrupt can arrive while another context is inside the library, corrupting its internal state.

## B30. What is the recursion risk in embedded firmware?

**Short answer:** Each call uses stack, which makes worst-case stack use hard to prove.

## B31. What is a circular buffer?

**Short answer:** A fixed-size queue with wrapping indices. It is deterministic and common for UART streams, logging, and producer-consumer data.

## B32. How do you distinguish full from empty in a ring buffer?

**Short answer:** Keep a count, or keep one slot unused. State the invariant explicitly.

```c
bool empty = (head == tail);
bool full  = ((head + 1u) % SIZE) == tail;     /* one-slot-unused convention */
```

## B33. What is an atomic operation?

**Short answer:** An operation that cannot be split, relative to the concurrency model in use.

Whether a C operation is atomic depends on the target and type. Do not assume every read or write is atomic.

## B34. When would you use C11 atomics in embedded?

**Short answer:** When the toolchain and target support them and you need lock-free or synchronized shared state with defined memory ordering.

```c
#include <stdatomic.h>
static atomic_uint counter;
atomic_fetch_add(&counter, 1u);      /* a safe increment even with an ISR */
```

## B35. What is a memory barrier?

**Short answer:** It controls the order of memory operations as seen by other agents. It is different from `volatile`.

## B36. What is endianness?

**Short answer:** The byte order of multi-byte objects. Protocol code must follow the specified wire order, not the CPU's native layout.

## B37. How do you serialize a 32-bit integer portably?

**Short answer:** Write each byte explicitly in the protocol's byte order.

```c
buf[0] = (uint8_t)(value >> 24);    /* big-endian: most significant byte first */
buf[1] = (uint8_t)(value >> 16);
buf[2] = (uint8_t)(value >> 8);
buf[3] = (uint8_t)(value);
```

## B38. What is integer promotion?

**Short answer:** `char` and `short` are generally promoted to `int` in expressions, which can affect signedness, shifts, and comparisons.

## B39. Why can signed shifts be dangerous?

**Short answer:** Rules differ for signed and unsigned values, especially right shifts of negatives. Prefer unsigned types for bit work.

## B40. What is integer overflow in unsigned C?

**Short answer:** It wraps modulo 2^N. Signed overflow is undefined behaviour.

```c
uint8_t u = 255; u++;     /* well defined: becomes 0 */
int8_t  s = 127; s++;     /* undefined behaviour in C (signed overflow) */
```

## B41. Why cast before shifting a narrow value?

**Short answer:** Promotion and signedness change the shift. Use an explicitly sized unsigned type.

```c
uint8_t v = 0x80u;
uint32_t r = (uint32_t)v << 24;     /* cast first: the shift happens in 32 bits, unsigned */
```

## B42. What is a linker error versus a compiler error?

**Short answer:** Compiler errors happen while translating one file. Linker errors happen when combining files and resolving symbols or sections.

## B43. Why is a linker script important in embedded firmware?

**Short answer:** It controls memory placement and section layout: flash, RAM, boot regions, and special windows.

## B44. What is the difference between stack and heap lifetime?

**Short answer:** Automatic objects live for their scope or call. Dynamically allocated objects live until released.

## B45. What causes stack overflow?

**Short answer:** Deep call chains, large local arrays, recursion, interrupt nesting, or library calls.

Measure high-water marks and test worst-case paths.

## B46. Why use `assert` in embedded code?

**Short answer:** It catches violated invariants early in development.

Define production behaviour carefully, because a failing assert can affect availability.

## B47. What is defensive parsing?

**Short answer:** Validate lengths, ranges, types, and state before acting on external data.

## B48. What is a translation-unit private helper?

**Short answer:** A file-scope `static` function. It avoids exporting symbols other modules should not use.

## B49. How do you review embedded C for portability?

**Short answer:** Check integer widths, alignment, endianness, compiler extensions, ABI assumptions, `volatile` use, undefined behaviour, and hardware dependencies.

## B50. What is a common mistake with `memset` on integers?

**Short answer:** `memset` works byte by byte, so setting an integer to 1 with it does not give the value 1. Use assignment.

---

## Part C: Structures and unions

## C1. How is structure size calculated?

**Short answer:** Place each member at its alignment, add padding where needed, then round the total up to the structure's alignment.

```c
struct A {
    char c;      /* offset 0 */
    int  i;      /* offset 4 (3 bytes of padding before it) */
};               /* size 8 on a common 32-bit ABI */
```

The exact result depends on the implementation.

## C2. What is structure padding?

**Short answer:** Compiler-inserted bytes that satisfy alignment rules.

```text
offset 0   : char c
offset 1-3 : padding
offset 4-7 : int i
```

## C3. What is tail padding?

**Short answer:** Padding at the end of a structure so that array elements stay correctly aligned.

## C4. Why does member order matter?

**Short answer:** Reordering can reduce padding and save memory.

```c
struct Bad    { char a; int b; char c; };   /* typically 12 bytes: 1 + 3 pad + 4 + 1 + 3 pad */
struct Better { int b; char a; char c; };   /* typically 8 bytes: 4 + 1 + 1 + 2 pad */
```

Sizes depend on the ABI and compiler.

## C5. What is `offsetof()`?

**Short answer:** The byte offset of a member from the start of its structure.

```c
#include <stddef.h>
size_t offset = offsetof(struct Sensor, value);
```

## C6. Why is `offsetof()` useful in embedded systems?

**Short answer:** It verifies memory layouts for packets, shared-memory structures, drivers, and ABI interfaces.

```c
_Static_assert(offsetof(Regs, STATUS) == 0x04, "STATUS register offset changed");
```

## C7. What is a packed structure?

**Short answer:** A structure with reduced or no padding, if the compiler supports it.

```c
struct __attribute__((packed)) Packet {     /* GCC syntax */
    uint8_t  id;
    uint32_t value;      /* now at offset 1, so misaligned */
};
```

## C8. What is the danger of packed structures?

**Short answer:** Unaligned members can be slower or fault on architectures without unaligned support. Use carefully.

## C9. Is `sizeof(struct)` always the sum of the member sizes?

**Short answer:** No. Padding and alignment can make it larger.

## C10. Is a union's size always its largest member?

**Short answer:** It must hold the largest member and satisfy the union's alignment. Commonly that equals the largest member, but the standard does not promise the simple formula in every case.

## C11. What happens when a union member is written?

**Short answer:** The stored bytes are interpreted according to whichever member you read.

Treat one member as active at a time. Reading another member for type punning has portability considerations.

## C12. Structure versus union memory

**Short answer:** A struct gives every member its own storage; a union makes all members share it.

```text
struct:  [ A ][ B ][ C ]      separate storage
union:   [ A / B / C ]        one shared storage
```

## C13. What is an anonymous structure?

**Short answer:** A structure without a name, supported as an extension or in newer C standards. Consider portability.

## C14. What is an anonymous union?

**Short answer:** A union whose members are accessed directly from the containing scope.

```c
union {
    uint32_t word;
    uint8_t  bytes[4];
};      /* use as: x.word or x.bytes[0] */
```

## C15. What is a nested union inside a structure?

**Short answer:** A common header with different payload views.

```c
struct Message {
    uint8_t type;             /* common header */
    union {
        uint32_t value;       /* payload as an integer... */
        float temperature;    /* ...or as a float */
    } data;
};
```

## C16. What is a tagged union?

**Short answer:** A union plus a tag that says which member is valid.

```c
enum Type { TYPE_INT, TYPE_FLOAT };

struct Value {
    enum Type type;           /* the tag: tells you which member to read */
    union {
        int   i;
        float f;
    } data;
};
```

It is safer than a union without knowing which member is active.

## C17. Why are tagged unions useful in embedded systems?

**Short answer:** For command packets, event messages, state-machine data, and protocol payloads with different types.

## C18. What is the bit-field memory layout?

**Short answer:** Bit-fields can share storage units, but order and layout are implementation-defined. Do not assume a portable bit order for wire protocols.

## C19. Can bit-fields be used for hardware registers?

**Short answer:** Sometimes, but portable definitions prefer explicit masks and shifts because layout is compiler and ABI dependent.

## C20. What is a safer alternative to bit-fields for registers?

**Short answer:** Masks and shifts.

```c
#define ENABLE_MASK  (1u << 0)
#define MODE_MASK    (3u << 1)

reg |= ENABLE_MASK;                          /* set the enable bit */
reg = (reg & ~MODE_MASK) | (mode << 1);      /* clear the mode field, then insert the new value */
```

## C21. What is structure aliasing?

**Short answer:** Accessing an object through a pointer of another type. Casting between unrelated structure types can break C's effective-type and aliasing rules.

## C22. Can you compare structures with `==`?

**Short answer:** No. Compare member by member.

## C23. Can you use `memcmp()` to compare structures?

**Short answer:** Not reliably for logical equality, because padding bytes can hold unspecified values.

```c
memcmp(&a, &b, sizeof a);     /* may say "different" even if every member is equal */
```

## C24. Can you use `memcpy()` with structures?

**Short answer:** Yes, if the destination is properly sized and aligned.

## C25. Why can `memcpy()` of a structure be a problem with pointers?

**Short answer:** It copies the pointer values, not the objects they point to. That is a shallow copy.

## C26. What is a shallow copy of a structure?

**Short answer:** Members are copied directly. If the structure contains pointers, both copies point to the same underlying object.

## C27. What is a deep copy?

**Short answer:** A copy that also duplicates the referenced data, so the new structure owns separate storage.

## C28. Structure alignment and DMA

**Short answer:** DMA may need specific alignment and memory regions. A structure's layout alone does not guarantee that.

## C29. Structure and endianness

**Short answer:** In-memory bytes depend on the target's endianness, so sending a structure directly over UART, TCP, CAN, or Modbus is not automatically portable.

## C30. Why avoid sending a structure directly over a communication interface?

**Short answer:** Because of padding, alignment, endianness, compiler and ABI differences, bit-field layout, and data type sizes.

Prefer explicit serialization and deserialization.

## C31. How do you serialize a structure safely?

**Short answer:** Convert each field to the required byte order and format.

```c
buffer[0] = (uint8_t)(value & 0xFFu);          /* low byte first: little-endian */
buffer[1] = (uint8_t)((value >> 8) & 0xFFu);
```

## C32. What is a memory-mapped register structure?

**Short answer:** A structure that describes registers at fixed addresses.

```c
typedef struct {
    volatile uint32_t CTRL;      /* offset 0x00 */
    volatile uint32_t STATUS;    /* offset 0x04 */
    volatile uint32_t DATA;      /* offset 0x08 */
} UART_Regs;

#define UART0 ((UART_Regs *)0x40000000u)     /* the address comes from the reference manual */
```

## C33. Why is `volatile` used for register structures?

**Short answer:** Registers can change independently of program flow, so accesses must not be optimized away.

## C34. Structure access: direct object

```c
struct Sensor s;
s.value = 10;         /* access through a concrete object with the dot operator */
```

## C35. Structure access: pointer

```c
struct Sensor *p = &s;
p->value = 10;        /* the arrow operator: same as (*p).value */
```

Useful for functions and dynamically chosen objects.

## C36. Structure access: array

```c
struct Sensor sensors[10];
sensors[3].value = 100;      /* address = base + 3 * sizeof(struct Sensor) */
```

## C37. Why does structure layout matter for cache performance?

**Short answer:** Poor member arrangement or large structures increase memory traffic and cache use on cached MCUs and processors.

## C38. Array of structures versus structure of arrays

```c
/* Array of structures (AoS): convenient when handling a whole object */
struct Sensor { float temperature; float pressure; };
struct Sensor sensors[100];

/* Structure of arrays (SoA): better locality when processing one field across many objects */
struct Sensors { float temperature[100]; float pressure[100]; };
```

The best choice depends on the workload and architecture.

## C39. What is false sharing?

**Short answer:** On multicore systems, independent variables on the same cache line cause needless coherence traffic when different cores modify them.

## C40. How can structure design reduce memory usage?

**Short answer:** Order members well, use appropriate integer widths, avoid padding and needless pointers, split hot and cold data, and use compact representations where safe.

## C41. What is ABI compatibility with structures?

**Short answer:** The ABI defines layout, alignment, calling conventions, and return rules. Changing a structure's layout can break binary compatibility.

## C42. What is a flexible array member?

**Short answer:** A last member with no size, used for variable-length data.

```c
struct Packet {
    uint16_t length;
    uint8_t  data[];        /* adds nothing to sizeof(struct Packet) */
};

/* Allocate header plus payload together */
struct Packet *p = malloc(sizeof *p + payload_len);
```

## C43. Why are flexible array members useful in embedded systems?

**Short answer:** They represent variable-length packet buffers efficiently. Handle allocation and bounds checking carefully.

## C44. What happens with a zero-width bit-field?

**Short answer:** It forces the next bit-field to start at the next allocation unit boundary, subject to the implementation's rules.

## C45. Why can two compilers produce different structure sizes?

**Short answer:** ABI, alignment rules, packing options, target architecture, and compiler extensions can all differ.
