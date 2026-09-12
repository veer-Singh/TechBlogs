# Basic Embedded Coding Questions — C Core

## 1. Reverse a string

```c
#include <stdio.h>
#include <string.h>

void reverse_string(char *str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

int main(void)
{
    char s[] = "rajbir is my name";
    reverse_string(s);
    printf("%s\n", s);
    return 0;
}
```

**Follow-up:** Explain the time complexity and why the extra space remains constant.

## 2. Reverse words in a sentence

"Reverse words" has two common readings. State which one you mean before you code.

### 2.1 Reverse the letters of each word (word order unchanged)

```c
#include <stdio.h>
#include <string.h>

/* Reverses the letters inside every word in place; word order is unchanged. */
void reverse_words(char *str)
{
    int len = (int)strlen(str);
    int start = 0;

    /* i == len reads the terminating '\0', so the last word is flushed too. */
    for (int i = 0; i <= len; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            int end = i - 1;

            while (start < end) {
                char temp = str[start];
                str[start] = str[end];
                str[end] = temp;
                start++;
                end--;
            }

            start = i + 1;
        }
    }

    printf("Reverse string = %s\n", str);
}

int main(void)
{
    char s[] = "rajbir is my name";
    reverse_words(s);
    return 0;
}
```

Output:

```text
name my is rajbir
```

**Follow-up:** Time complexity is `O(n)` (one full pass plus one pass over the word characters, both linear), and extra space is `O(1)` because the two pointers and the swap temporaries are reused for every element. Note that pass 1 relocates separators as well, so leading, trailing, or repeated spaces are preserved in count but may move position. If the caller needs exactly one space between words, compact the string in a separate pass. Also note that string literals are read-only, so the input must be a writable `char[]`, not a `const char *`.

## 3. Count set bits

```c
unsigned count_set_bits(unsigned x)
{
    unsigned count = 0U;
    while (x != 0U) {
        x &= (x - 1U);
        ++count;
    }
    return count;
}
```

## 4. Reverse bits of a 32-bit value

```c
#include <stdint.h>

uint32_t reverse_bits32(uint32_t num)
{
    uint32_t rev = 0U;
    for (unsigned i = 0U; i < 32U; ++i) 
    {
        rev = (rev << 1);
        rev |= (num & 1U);
        num >>= 1;
    }
    return rev;
}
```

## 5. Rotate an array right by `k`

Use the reversal technique: reverse the full array, reverse the first `k` elements, and reverse the remaining elements.

## 6. Implement a callback across two C files

```c
/* callback.h */
typedef void (*callback_t)(void);
void register_callback(callback_t cb);
```

```c
/* callback.c */
static callback_t g_callback;

void register_callback(callback_t cb)
{
    g_callback = cb;
}
```

## 7. Macro vs. inline function

Prefer an inline function for type-safe behavior when possible. Macros are useful for token substitution and compile-time logic, but they can have side effects and no type checking.

---

# Pointer and array coding questions

## 8. Swap two numbers using pointers

```c
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

## 9. Print an array using pointer arithmetic

```c
#include <stdio.h>

int main(void)
{
    int arr[3] = {1, 2, 3};
    int *ptr = arr;

    for (int i = 0; i < 3; ++i) {
        printf("%d ", *(ptr + i));
    }
    return 0;
}
```

## 10. Reverse an array using pointers

```c
void reverse(int *arr, int size)
{
    int *start = arr;
    int *end = arr + size - 1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
```

## 11. What is the output?

```c
int x = 10;
int *p = &x;
printf("%d %d\n", x, *p);
```

Output:

```text
10 10
```

## 12. Find the maximum value using pointers

```c
int find_max(const int *arr, int size)
{
    int max = arr[0];

    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
```

## 13. Calculate the length of an array using `sizeof`

```c
int arr[] = {10, 20, 30, 40, 50};
size_t size = sizeof(arr) / sizeof(arr[0]);
```

## 14. Copy an array using pointer arithmetic

```c
void copy_array(const int *src, int *dst, int size)
{
    for (int i = 0; i < size; ++i) {
        *(dst + i) = *(src + i);
    }
}
```

## 15. What is a double pointer?

A double pointer is a pointer to a pointer. It is used when a function must modify the caller's pointer value itself.

```c
void set_pointer(int **pp, int *new_addr)
{
    *pp = new_addr;
}
```

---
# Structure and Union Coding Interview Questions — Embedded C

## 1. Find the size of a structure

**Question:** What is the likely size of this structure on a typical 32-bit MCU?

```c
struct Test {
    char c;
    int i;
    char d;
};
```

**Answer:** It is commonly 12 bytes because of alignment and tail padding, but the exact size is implementation-dependent.

---

## 2. Reduce structure padding

**Question:** Which structure is generally more memory-efficient?

```c
struct A {
    char a;
    int b;
    char c;
};

struct B {
    int b;
    char a;
    char c;
};
```

**Answer:** `struct B` is generally more compact because related alignment requirements can reduce padding.

---

## 3. Print member offsets

```c
#include <stdio.h>
#include <stddef.h>

struct Sensor {
    char id;
    int value;
    float temperature;
};

int main(void)
{
    printf("id = %zu\n", offsetof(struct Sensor, id));
    printf("value = %zu\n", offsetof(struct Sensor, value));
    printf("temperature = %zu\n", offsetof(struct Sensor, temperature));

    return 0;
}
```

**Concept tested:** Structure memory layout and padding.

---

## 4. Swap two structures

```c
struct Data {
    int a;
    int b;
};

void swap(struct Data *x, struct Data *y)
{
    struct Data temp = *x;
    *x = *y;
    *y = temp;
}
```

**Concept tested:** Structure assignment and pointers.

---

## 5. Pass structure to a function

```c
struct Sensor {
    int id;
    float value;
};

void print_sensor(const struct Sensor *s)
{
    printf("%d %.2f\n", s->id, s->value);
}
```

**Why use a pointer?** Avoids copying the entire structure and allows `const` protection when modification is not required.

---

## 6. Find the largest member of a union

```c
union Data {
    char c;
    int i;
    double d;
};
```

**Answer:** `double` is the largest declared member, but `sizeof(union Data)` should be used to determine actual storage size.

---

## 7. Demonstrate shared union memory

```c
#include <stdio.h>

union Data {
    int i;
    float f;
};

int main(void)
{
    union Data d;

    printf("%p\n", (void *)&d.i);
    printf("%p\n", (void *)&d.f);

    return 0;
}
```

**Expected concept:** Both members have the same starting address.

---

## 8. Union type-punning question

```c
union Data {
    uint32_t u32;
    float f;
};
```

**Question:** Can you write `u32` and read `f`?

**Answer:** The representation is implementation-dependent; do not use this as a portable way to reinterpret object representations. For portable byte-level conversion, use `memcpy()`.

---

## 9. Portable representation conversion

```c
#include <stdint.h>
#include <string.h>

float uint32_to_float(uint32_t value)
{
    float result;
    memcpy(&result, &value, sizeof(result));
    return result;
}
```

**Concept tested:** Object representation and safe copying.

---

## 10. Implement a tagged union

```c
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT
} DataType;

typedef struct {
    DataType type;

    union {
        int32_t i;
        float f;
    } value;
} Data;
```

Usage:

```c
Data d;

d.type = TYPE_INT;
d.value.i = 100;
```

**Concept tested:** Safe union usage with a discriminator.

---

## 11. Set and clear structure flags

```c
struct Status {
    unsigned int ready : 1;
    unsigned int error : 1;
};

void set_ready(struct Status *s)
{
    s->ready = 1;
}

void clear_ready(struct Status *s)
{
    s->ready = 0;
}
```

**Concept tested:** Bit-fields.

---

## 12. Implement flags without bit-fields

```c
#include <stdint.h>

#define FLAG_READY  (1u << 0)
#define FLAG_ERROR  (1u << 1)

uint32_t status;

status |= FLAG_READY;       // Set
status &= ~FLAG_READY;      // Clear
status ^= FLAG_ERROR;       // Toggle
```

**Why prefer this in many embedded cases?** Explicit masks and shifts provide predictable bit operations and avoid bit-field layout dependencies.

---

## 13. Extract a bit-field using masks

```c
uint32_t reg = 0x0000001Au;

uint32_t mode = (reg >> 1) & 0x7u;
```

**Answer:** Bits 1 through 3 are extracted into `mode`.

---

## 14. Modify selected bits without affecting others

```c
#define MODE_MASK  (0x7u << 1)

reg = (reg & ~MODE_MASK) | ((mode & 0x7u) << 1);
```

**Concept tested:** Read-modify-write and bit masking.

---

## 15. Serialize a 16-bit value in little-endian format

```c
#include <stdint.h>

void write_u16_le(uint8_t *buf, uint16_t value)
{
    buf[0] = (uint8_t)(value & 0xFFu);
    buf[1] = (uint8_t)((value >> 8) & 0xFFu);
}
```

---

## 16. Deserialize a 16-bit little-endian value

```c
uint16_t read_u16_le(const uint8_t *buf)
{
    return (uint16_t)buf[0] |
           ((uint16_t)buf[1] << 8);
}
```

**Concept tested:** Structure-independent serialization and endianness.

---

## 17. Why should you not directly send this structure?

```c
struct Packet {
    uint8_t id;
    uint32_t value;
};
```

Bad approach:

```c
send((uint8_t *)&packet, sizeof(packet));
```

**Answer:** Padding, alignment, endianness, and ABI differences can make the byte representation unsuitable for a portable protocol.

---

## 18. Create an explicit packet serializer

```c
typedef struct {
    uint8_t id;
    uint16_t value;
} Packet;

void serialize_packet(const Packet *p, uint8_t *buf)
{
    buf[0] = p->id;
    buf[1] = (uint8_t)(p->value & 0xFFu);
    buf[2] = (uint8_t)((p->value >> 8) & 0xFFu);
}
```

---

## 19. Array of structures access

```c
struct Sensor {
    int id;
    float value;
};

struct Sensor sensors[5];

sensors[2].value = 25.5f;
```

**Question:** How is the address of `sensors[2]` determined?

**Answer:** Conceptually, it is the base address plus `2 * sizeof(struct Sensor)`.

---

## 20. Structure pointer access

```c
struct Sensor s;
struct Sensor *ptr = &s;

ptr->id = 10;
ptr->value = 25.5f;
```

---

## 21. Nested structure access

```c
struct Date {
    int day;
    int month;
};

struct Employee {
    int id;
    struct Date date;
};

struct Employee e;

e.date.day = 10;
e.date.month = 9;
```

---

## 22. Structure containing a union

```c
struct Message {
    uint8_t type;

    union {
        uint32_t value;
        float temperature;
    } payload;
};
```

Usage:

```c
struct Message msg;

msg.type = 1;
msg.payload.value = 100;
```

---

## 23. Implement a circular buffer using a structure

```c
#define BUFFER_SIZE 16

struct RingBuffer {
    uint8_t data[BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
};

int push(struct RingBuffer *rb, uint8_t value)
{
    uint16_t next = (uint16_t)((rb->head + 1u) % BUFFER_SIZE);

    if (next == rb->tail)
        return 0;

    rb->data[rb->head] = value;
    rb->head = next;

    return 1;
}
```

**Concept tested:** Structure-based state management and memory access patterns.

---

## 24. Structure for memory-mapped peripheral registers

```c
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t STATUS;
    volatile uint32_t DATA;
} UART_Regs;
```

A vendor-specific base address may then be mapped:

```c
#define UART0 ((UART_Regs *)0x40000000u)
```

**Important:** The address and register offsets must match the MCU reference manual.

---

## 25. Set a register bit using a structure

```c
#define UART_ENABLE (1u << 0)

UART0->CTRL |= UART_ENABLE;
```

---

## 26. Clear a register bit

```c
UART0->CTRL &= ~UART_ENABLE;
```

---

## 27. Read a status bit

```c
#define UART_RX_READY (1u << 1)

if (UART0->STATUS & UART_RX_READY) {
    /* Data available */
}
```

---

## 28. Find the difference between two structures

```c
struct Data {
    int a;
    int b;
};

int equal(const struct Data *x, const struct Data *y)
{
    return (x->a == y->a) && (x->b == y->b);
}
```

**Why not `memcmp()`?** Padding bytes can differ even when all logical fields are equal.

---

## 29. Reverse an array of structures

```c
struct Data {
    int value;
};

void reverse(struct Data arr[], int n)
{
    for (int i = 0; i < n / 2; i++) {
        struct Data temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}
```

---

## 30. Array of structures vs structure of arrays

### Array of structures

```c
struct Sensor {
    float temperature;
    float pressure;
};

struct Sensor sensors[100];
```

### Structure of arrays

```c
struct Sensors {
    float temperature[100];
    float pressure[100];
};
```

**Interview answer:** Use AoS when processing complete sensor objects; SoA can be better when processing one field across many objects because memory access can be more contiguous.

---

## 31. Find the largest value in an array of structures

```c
struct Sensor {
    int id;
    float value;
};

int max_sensor_index(const struct Sensor arr[], int n)
{
    int index = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i].value > arr[index].value)
            index = i;
    }

    return index;
}
```

---

## 32. Use `const` with a structure pointer

```c
void print_sensor(const struct Sensor *s)
{
    printf("%d %.2f\n", s->id, s->value);
}
```

**Answer:** `const` prevents the function from modifying the structure through that pointer.

---

## 33. Use `volatile` with a hardware structure

```c
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t STATUS;
} Peripheral;
```

**Question:** Why `volatile`?

**Answer:** Hardware can change register values independently of normal program execution, so the compiler must perform the accesses as specified.

---

## 34. Coding question: Identify the padding issue

```c
struct Example {
    char a;
    int b;
    short c;
};
```

**Answer:** Padding may be inserted after `a` before `b`, and possibly at the end to satisfy alignment. Use `sizeof()` and `offsetof()` on the target compiler to verify the actual layout.

---

## 35. Coding question: Design a protocol structure

**Question:** You have a packet containing:

- 1 byte command
- 2 byte length
- 4 byte sequence number

**Answer:** Define logical fields in a structure, but serialize them explicitly:

```c
struct Packet {
    uint8_t command;
    uint16_t length;
    uint32_t sequence;
};
```

Do not assume `sizeof(struct Packet)` equals the protocol's wire size.

---

# Quick Coding Revision

| Topic | Key Concept |
|---|---|
| Structure | Separate storage for members |
| Union | Shared storage |
| Padding | Compiler-inserted alignment bytes |
| Alignment | Address requirements of types |
| `offsetof()` | Member offset |
| Bit-field | Compact bit-level members |
| Tagged union | Discriminator + union |
| `.` | Structure/union object access |
| `->` | Pointer to structure/union access |
| `memcpy()` | Copy object representation |
| `memcmp()` | Not reliable for structure logical equality |
| Serialization | Explicit byte conversion |
| AoS | Array of complete objects |
| SoA | Separate arrays for each field |
| `volatile` | Important for hardware register accesses |
