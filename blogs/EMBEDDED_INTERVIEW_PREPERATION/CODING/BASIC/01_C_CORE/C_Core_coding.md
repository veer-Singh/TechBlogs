# Basic Embedded Coding Questions: C Core

How to use this file: read the **Idea** first, try to write the code yourself, then compare with the commented solution. Every code block explains what each step does and why.

## Contents

| Part | Topic | Questions |
| --- | --- | --- |
| A | Strings, bits, arrays, pointers, callbacks | A1-A15 |
| B | Structures, unions, bit-fields, serialization, registers | B1-B35 |

---

## Part A: Strings, bits, arrays, pointers, and callbacks

## A1. Reverse a string

**Idea:** Swap the first and last characters, then move both ends inward until they meet.

```c
#include <stdio.h>
#include <string.h>

void reverse_string(char *str)
{
    size_t len = strlen(str);                  /* number of characters, not counting '\0' */

    for (size_t i = 0; i < len / 2; i++) {     /* only go halfway, or we would swap back */
        char tmp = str[i];                     /* keep the left character */
        str[i] = str[len - 1 - i];             /* copy the mirrored right character to the left */
        str[len - 1 - i] = tmp;                /* put the saved character on the right */
    }
}

int main(void)
{
    char s[] = "rajbir is my name";            /* must be a writable array, not a string literal pointer */
    reverse_string(s);
    printf("%s\n", s);                         /* eman ym si ribjar */
    return 0;
}
```

**Follow-up:** Time is O(n). Extra space is O(1), because only one temporary character is used.

**Remember:** loop to `len / 2`, and use a writable `char[]`.

## A2. Reverse words in a sentence

**Idea:** "Reverse words" has two common meanings. Ask which one is meant before coding.

| Meaning | Input | Output |
| --- | --- | --- |
| A. Reverse the letters of each word | `rajbir is my name` | `ribjar si ym eman` |
| B. Reverse the order of the words | `rajbir is my name` | `name my is rajbir` |

### A2.1 Reverse the letters of each word (word order unchanged)

```c
#include <stdio.h>
#include <string.h>

/* Reverses the letters inside every word, in place. Word order stays the same. */
void reverse_each_word(char *str)
{
    int len = (int)strlen(str);
    int start = 0;                             /* index where the current word begins */

    /* i == len reads the terminating '\0', which flushes the last word too. */
    for (int i = 0; i <= len; i++) {
        if (str[i] == ' ' || str[i] == '\0') { /* end of a word */
            int end = i - 1;                   /* last letter of the word */

            while (start < end) {              /* reverse str[start..end] */
                char temp = str[start];
                str[start] = str[end];
                str[end] = temp;
                start++;
                end--;
            }

            start = i + 1;                     /* the next word starts after the space */
        }
    }
}

int main(void)
{
    char s[] = "rajbir is my name";
    reverse_each_word(s);
    printf("%s\n", s);                         /* ribjar si ym eman */
    return 0;
}
```

### A2.2 Reverse the order of the words

**Idea:** Reverse the whole string first, then reverse each word back to reading order.

```c
static void reverse_range(char *s, int left, int right)
{
    while (left < right) {                     /* swap the ends and move inward */
        char t = s[left];
        s[left++] = s[right];
        s[right--] = t;
    }
}

void reverse_word_order(char *str)
{
    int len = (int)strlen(str);

    reverse_range(str, 0, len - 1);            /* step 1: "eman ym si ribjar" */

    int start = 0;
    for (int i = 0; i <= len; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            reverse_range(str, start, i - 1);  /* step 2: fix each word: "name my is rajbir" */
            start = i + 1;
        }
    }
}
```

**Follow-up:** Both versions are O(n) time and O(1) extra space. Each character is swapped a constant number of times. Repeated or leading spaces keep their positions in A2.1; if exactly one space between words is required, compact the string in a separate pass. The input must be a writable `char[]`, not a `const char *`.

**Remember:** whole-string reverse plus per-word reverse gives word order reversal.

## A3. Count set bits

**Idea:** `x & (x - 1)` clears the lowest set bit. Count how many times you can do that.

```c
unsigned count_set_bits(unsigned x)
{
    unsigned count = 0U;
    while (x != 0U) {
        x &= (x - 1U);       /* remove the lowest set bit */
        ++count;             /* one more bit was set */
    }
    return count;            /* runs once per set bit */
}
```

Example: `x = 0b1011` needs 3 iterations, so the answer is 3.

## A4. Reverse the bits of a 32-bit value

**Idea:** Take the lowest bit of the input and push it into the result from the other side, 32 times.

```c
#include <stdint.h>

uint32_t reverse_bits32(uint32_t num)
{
    uint32_t rev = 0U;

    for (unsigned i = 0U; i < 32U; ++i) {
        rev <<= 1;               /* make room at the bottom of the result */
        rev |= (num & 1U);       /* copy the lowest input bit into it */
        num >>= 1;               /* move to the next input bit */
    }
    return rev;                  /* bit 0 of the input is now bit 31 of the result */
}
```

Example: `0x00000001` becomes `0x80000000`.

## A5. Rotate an array right by `k`

**Idea:** Reverse the whole array, then reverse the first `k` elements, then reverse the rest.

```c
static void reverse_part(int *a, int left, int right)
{
    while (left < right) {
        int t = a[left];
        a[left++] = a[right];
        a[right--] = t;
    }
}

void rotate_right(int *a, int n, int k)
{
    if (n <= 1) { return; }
    k %= n;                          /* rotating by n or more is the same as k % n */
    if (k == 0) { return; }

    reverse_part(a, 0, n - 1);       /* {1,2,3,4,5}, k=2 -> {5,4,3,2,1} */
    reverse_part(a, 0, k - 1);       /* first k elements       -> {4,5,3,2,1} */
    reverse_part(a, k, n - 1);       /* remaining elements     -> {4,5,1,2,3} */
}
```

**Follow-up:** O(n) time, O(1) space.

## A6. Implement a callback across two C files

**Idea:** One module stores a function pointer; another module supplies the function.

```c
/* callback.h : the public interface */
typedef void (*callback_t)(void);            /* a pointer to a function with no arguments and no return */
void register_callback(callback_t cb);       /* the caller hands in its function */
void fire_callback(void);                    /* calls it when the event happens */
```

```c
/* callback.c : the implementation */
#include "callback.h"

static callback_t g_callback;                /* private to this file; NULL until registered */

void register_callback(callback_t cb)
{
    g_callback = cb;                         /* remember which function to call later */
}

void fire_callback(void)
{
    if (g_callback != NULL) {                /* never call a NULL function pointer */
        g_callback();
    }
}
```

**Remember:** always check the pointer for `NULL` before calling.

## A7. Macro vs inline function

**Idea:** Prefer an inline function. It is type-checked and evaluates its arguments once.

```c
#define SQUARE_MACRO(x)  ((x) * (x))          /* no type check; SQUARE_MACRO(i++) increments twice */
static inline int square_inline(int x) { return x * x; }   /* typed, evaluated once */
```

Macros are still useful for token pasting, conditional compilation, and constants.

---

## Pointer and array questions

## A8. Swap two numbers using pointers

**Idea:** Pass addresses, so the function can change the caller's variables.

```c
void swap(int *a, int *b)
{
    int temp = *a;      /* save the value a points to */
    *a = *b;            /* overwrite it with the value b points to */
    *b = temp;          /* put the saved value where b points */
}
/* Call as: swap(&x, &y); */
```

## A9. Print an array using pointer arithmetic

**Idea:** `*(ptr + i)` means the same as `arr[i]`.

```c
#include <stdio.h>

int main(void)
{
    int arr[3] = {1, 2, 3};
    int *ptr = arr;                       /* the array name decays to a pointer to its first element */

    for (int i = 0; i < 3; ++i) {
        printf("%d ", *(ptr + i));        /* ptr + i advances by i ints, not i bytes */
    }
    return 0;
}
```

## A10. Reverse an array using pointers

**Idea:** Two pointers, one at each end, swap and move inward.

```c
void reverse(int *arr, int size)
{
    int *start = arr;                     /* first element */
    int *end = arr + size - 1;            /* last element */

    while (start < end) {                 /* stop when they meet or cross */
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
```

## A11. What is the output?

```c
int x = 10;
int *p = &x;
printf("%d %d\n", x, *p);
```

Output:

```text
10 10
```

**Why:** `p` holds the address of `x`, so `*p` reads the same value.

## A12. Find the maximum value using pointers

```c
int find_max(const int *arr, int size)     /* const: the function only reads the array */
{
    int max = arr[0];                      /* assume the first element is the largest */

    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];                  /* found a bigger one */
        }
    }
    return max;
}
```

**Watch out:** the array must not be empty, or `arr[0]` is out of bounds.

## A13. Calculate the length of an array using `sizeof`

```c
int arr[] = {10, 20, 30, 40, 50};
size_t size = sizeof(arr) / sizeof(arr[0]);    /* total bytes / bytes per element = 5 */
```

**Watch out:** this only works where `arr` is a real array. Inside a function that received it as a parameter, `sizeof` gives the pointer size.

## A14. Copy an array using pointer arithmetic

```c
void copy_array(const int *src, int *dst, int size)
{
    for (int i = 0; i < size; ++i) {
        *(dst + i) = *(src + i);          /* same as dst[i] = src[i] */
    }
}
```

## A15. What is a double pointer?

**Idea:** A pointer to a pointer. Use it when a function must change the caller's pointer itself.

```c
void set_pointer(int **pp, int *new_addr)
{
    *pp = new_addr;            /* change what the caller's pointer points to */
}

/* int a = 1; int *p = NULL; set_pointer(&p, &a);   ->   p now points to a */
```

---

## Part B: Structures, unions, bit-fields, serialization, and registers

## B1. Find the size of a structure

**Idea:** Each member is aligned, and the total is rounded up to the structure's alignment.

```c
struct Test {
    char c;      /* offset 0 */
    int  i;      /* offset 4 (3 bytes of padding before it) */
    char d;      /* offset 8 */
};               /* total 12: 3 bytes of tail padding so arrays stay aligned */
```

**Answer:** Commonly 12 bytes on a 32-bit MCU. The exact size is implementation-dependent. Verify with `sizeof`.

## B2. Reduce structure padding

**Idea:** Put larger members first.

```c
struct A { char a; int b; char c; };    /* typically 12 bytes */
struct B { int b; char a; char c; };    /* typically 8 bytes: 4 + 1 + 1 + 2 tail padding */
```

**Answer:** `struct B` is usually smaller because the small members share one padded region.

## B3. Print member offsets

```c
#include <stdio.h>
#include <stddef.h>

struct Sensor {
    char  id;
    int   value;
    float temperature;
};

int main(void)
{
    printf("id = %zu\n",          offsetof(struct Sensor, id));           /* 0 */
    printf("value = %zu\n",       offsetof(struct Sensor, value));        /* 4 (after padding) */
    printf("temperature = %zu\n", offsetof(struct Sensor, temperature));  /* 8 */
    return 0;
}
```

**Concept tested:** structure layout and padding.

## B4. Swap two structures

```c
struct Data { int a; int b; };

void swap(struct Data *x, struct Data *y)
{
    struct Data temp = *x;     /* structures can be assigned as whole objects */
    *x = *y;
    *y = temp;
}
```

## B5. Pass a structure to a function

```c
struct Sensor { int id; float value; };

void print_sensor(const struct Sensor *s)
{
    printf("%d %.2f\n", s->id, s->value);      /* '->' reads a member through a pointer */
}
```

**Why a pointer?** It avoids copying the whole structure, and `const` protects it from changes.

## B6. Find the largest member of a union

```c
union Data { char c; int i; double d; };
```

**Answer:** `double` is the largest declared member, but use `sizeof(union Data)` for the real storage size.

## B7. Demonstrate shared union memory

```c
#include <stdio.h>

union Data { int i; float f; };

int main(void)
{
    union Data d;
    printf("%p\n", (void *)&d.i);      /* same address... */
    printf("%p\n", (void *)&d.f);      /* ...as this one: all members share storage */
    return 0;
}
```

## B8. Union type-punning

```c
union Data { uint32_t u32; float f; };
```

**Question:** Can you write `u32` and read `f`?

**Answer:** The result depends on the representation, so it is not a portable way to reinterpret bytes. Use `memcpy()` (B9).

## B9. Portable representation conversion

```c
#include <stdint.h>
#include <string.h>

float uint32_to_float(uint32_t value)
{
    float result;
    memcpy(&result, &value, sizeof result);    /* copy the raw bytes: always well defined */
    return result;
}
```

## B10. Implement a tagged union

**Idea:** A union plus a tag that says which member is valid.

```c
#include <stdint.h>

typedef enum { TYPE_INT, TYPE_FLOAT } DataType;

typedef struct {
    DataType type;                 /* the tag */
    union {
        int32_t i;
        float   f;
    } value;
} Data;

/* Usage */
Data d;
d.type = TYPE_INT;                 /* set the tag together with the value */
d.value.i = 100;
```

## B11. Set and clear structure flags (bit-fields)

```c
struct Status {
    unsigned int ready : 1;        /* 1 bit */
    unsigned int error : 1;        /* 1 bit */
};

void set_ready(struct Status *s)   { s->ready = 1; }
void clear_ready(struct Status *s) { s->ready = 0; }
```

**Watch out:** bit-field layout is compiler-dependent. Prefer masks for hardware (B12).

## B12. Implement flags without bit-fields

```c
#include <stdint.h>

#define FLAG_READY  (1u << 0)
#define FLAG_ERROR  (1u << 1)

uint32_t status;

status |= FLAG_READY;       /* set */
status &= ~FLAG_READY;      /* clear */
status ^= FLAG_ERROR;       /* toggle */
```

**Why?** Explicit masks and shifts are predictable and avoid bit-field layout dependencies.

## B13. Extract a bit-field using masks

```c
uint32_t reg = 0x0000001Au;               /* binary 1 1010 */

uint32_t mode = (reg >> 1) & 0x7u;        /* shift bit 1 down to bit 0, then keep 3 bits */
```

**Answer:** Bits 1 to 3 are extracted. Here `mode = 0b101 = 5`.

## B14. Modify selected bits without affecting others

```c
#define MODE_MASK  (0x7u << 1)                                   /* bits 1..3 */

reg = (reg & ~MODE_MASK)                 /* 1. clear the old field */
    | ((mode & 0x7u) << 1);              /* 2. insert the new value, masked so it cannot spill */
```

## B15. Serialize a 16-bit value in little-endian format

```c
#include <stdint.h>

void write_u16_le(uint8_t *buf, uint16_t value)
{
    buf[0] = (uint8_t)(value & 0xFFu);          /* low byte first */
    buf[1] = (uint8_t)((value >> 8) & 0xFFu);   /* then the high byte */
}
```

## B16. Deserialize a 16-bit little-endian value

```c
uint16_t read_u16_le(const uint8_t *buf)
{
    return (uint16_t)buf[0] |                   /* low byte */
           ((uint16_t)buf[1] << 8);             /* high byte shifted into place */
}
```

**Concept tested:** structure-independent serialization and endianness.

## B17. Why should you not directly send this structure?

```c
struct Packet { uint8_t id; uint32_t value; };

send((uint8_t *)&packet, sizeof(packet));      /* bad idea */
```

**Answer:** Padding, alignment, endianness, and ABI differences make the bytes unsuitable for a portable protocol.

## B18. Create an explicit packet serializer

```c
typedef struct { uint8_t id; uint16_t value; } Packet;

void serialize_packet(const Packet *p, uint8_t *buf)
{
    buf[0] = p->id;                                  /* wire byte 0 */
    buf[1] = (uint8_t)(p->value & 0xFFu);            /* wire byte 1: value low byte */
    buf[2] = (uint8_t)((p->value >> 8) & 0xFFu);     /* wire byte 2: value high byte */
}
```

The wire format is exactly 3 bytes, no matter what `sizeof(Packet)` is.

## B19. Array of structures access

```c
struct Sensor { int id; float value; };
struct Sensor sensors[5];

sensors[2].value = 25.5f;
```

**Question:** How is the address of `sensors[2]` found?

**Answer:** Base address plus `2 * sizeof(struct Sensor)`.

## B20. Structure pointer access

```c
struct Sensor s;
struct Sensor *ptr = &s;

ptr->id = 10;             /* same as (*ptr).id = 10 */
ptr->value = 25.5f;
```

## B21. Nested structure access

```c
struct Date { int day; int month; };
struct Employee { int id; struct Date date; };

struct Employee e;
e.date.day = 10;          /* chain the dots: outer.inner.member */
e.date.month = 9;
```

## B22. Structure containing a union

```c
struct Message {
    uint8_t type;                    /* which payload is in use */
    union {
        uint32_t value;
        float    temperature;
    } payload;
};

struct Message msg;
msg.type = 1;
msg.payload.value = 100;
```

## B23. Implement a circular buffer using a structure

```c
#define BUFFER_SIZE 16

struct RingBuffer {
    uint8_t  data[BUFFER_SIZE];
    uint16_t head;                 /* next write position */
    uint16_t tail;                 /* next read position */
};

int push(struct RingBuffer *rb, uint8_t value)
{
    uint16_t next = (uint16_t)((rb->head + 1u) % BUFFER_SIZE);   /* wrap around */

    if (next == rb->tail) {        /* buffer full (one slot is left unused) */
        return 0;
    }

    rb->data[rb->head] = value;    /* store first... */
    rb->head = next;               /* ...then publish the new head */
    return 1;
}
```

## B24. Structure for memory-mapped peripheral registers

```c
typedef struct {
    volatile uint32_t CTRL;        /* offset 0x00 */
    volatile uint32_t STATUS;      /* offset 0x04 */
    volatile uint32_t DATA;        /* offset 0x08 */
} UART_Regs;

#define UART0 ((UART_Regs *)0x40000000u)     /* the base address comes from the reference manual */
```

**Important:** addresses and offsets must match the MCU reference manual.

## B25. Set a register bit using a structure

```c
#define UART_ENABLE (1u << 0)

UART0->CTRL |= UART_ENABLE;
```

## B26. Clear a register bit

```c
UART0->CTRL &= ~UART_ENABLE;
```

## B27. Read a status bit

```c
#define UART_RX_READY (1u << 1)

if (UART0->STATUS & UART_RX_READY) {
    /* data is available */
}
```

## B28. Compare two structures

```c
struct Data { int a; int b; };

int equal(const struct Data *x, const struct Data *y)
{
    return (x->a == y->a) && (x->b == y->b);     /* compare member by member */
}
```

**Why not `memcmp()`?** Padding bytes can differ even when all logical fields are equal.

## B29. Reverse an array of structures

```c
struct Data { int value; };

void reverse(struct Data arr[], int n)
{
    for (int i = 0; i < n / 2; i++) {
        struct Data temp = arr[i];          /* whole-structure assignment */
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}
```

## B30. Array of structures vs structure of arrays

```c
/* Array of structures (AoS) */
struct Sensor { float temperature; float pressure; };
struct Sensor sensors[100];

/* Structure of arrays (SoA) */
struct Sensors { float temperature[100]; float pressure[100]; };
```

**Interview answer:** AoS suits processing whole objects. SoA can be faster when processing one field across many objects, because memory access is more contiguous.

## B31. Find the largest value in an array of structures

```c
struct Sensor { int id; float value; };

int max_sensor_index(const struct Sensor arr[], int n)
{
    int index = 0;                             /* index of the best so far */

    for (int i = 1; i < n; i++) {
        if (arr[i].value > arr[index].value) {
            index = i;
        }
    }
    return index;
}
```

## B32. Use `const` with a structure pointer

```c
void print_sensor(const struct Sensor *s)
{
    printf("%d %.2f\n", s->id, s->value);
}
```

**Answer:** `const` prevents the function from modifying the structure through that pointer.

## B33. Use `volatile` with a hardware structure

```c
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t STATUS;
} Peripheral;
```

**Question:** Why `volatile`?

**Answer:** Hardware can change register values independently of program flow, so the compiler must perform every access as written.

## B34. Identify the padding issue

```c
struct Example { char a; int b; short c; };
```

**Answer:** Padding is likely after `a` (before `b`) and at the end (to align the whole structure). Confirm with `sizeof()` and `offsetof()` on the target compiler.

## B35. Design a protocol structure

**Question:** A packet has a 1-byte command, a 2-byte length, and a 4-byte sequence number.

**Answer:** Keep logical fields in a structure, but serialize explicitly:

```c
struct Packet { uint8_t command; uint16_t length; uint32_t sequence; };

/* Wire size is 1 + 2 + 4 = 7 bytes. sizeof(struct Packet) is probably 8 or 12, so never assume they match. */
```

---

## Quick revision

| Topic | Key concept |
| --- | --- |
| Structure | Separate storage for members |
| Union | Shared storage |
| Padding | Compiler-inserted alignment bytes |
| Alignment | Address requirements of types |
| `offsetof()` | Member offset |
| Bit-field | Compact bit-level members, layout is compiler-dependent |
| Tagged union | Tag plus union |
| `.` | Access through an object |
| `->` | Access through a pointer |
| `memcpy()` | Copy object representation |
| `memcmp()` | Not reliable for structure equality |
| Serialization | Explicit byte conversion |
| AoS / SoA | Array of objects / separate array per field |
| `volatile` | Needed for hardware register accesses |
