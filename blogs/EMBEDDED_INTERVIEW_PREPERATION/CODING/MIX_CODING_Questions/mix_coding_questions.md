# Mixed C Coding Questions

How to use this file: read the question, try it yourself, then compare with the commented solution. Each solution has a **Key concept** line and, where it matters, a **Watch out** line for edge cases.

## Contents

| Part | Topic | Questions |
| --- | --- | --- |
| A | Embedded C core challenges (bits, memory, strings, math) | Q01-Q30 |
| B | Practice programs (numbers, strings, bits, arrays, linked lists) | B1-B11 |

Common rules used throughout: use unsigned types for bit work, never shift by the type width or more, and check pointers and lengths before use.

---

## Part A: Embedded C core challenges

### Q01: Swap the endianness of a 32-bit unsigned integer

```c
#include <stdint.h>
#include <stdio.h>

uint32_t swap_endian32(uint32_t val) {
    return ((val & 0x000000FFU) << 24) |   /* byte 0 moves to byte 3 */
           ((val & 0x0000FF00U) << 8)  |   /* byte 1 moves to byte 2 */
           ((val & 0x00FF0000U) >> 8)  |   /* byte 2 moves to byte 1 */
           ((val & 0xFF000000U) >> 24);    /* byte 3 moves to byte 0 */
}

int main(void) {
    uint32_t val = 0x12345678;
    printf("Swapped: 0x%08X\n", swap_endian32(val));   /* 0x78563412 */
    return 0;
}
```

**Key concept:** isolate each byte with a mask and shift it to the reverse position.

### Q02: Count set bits with Brian Kernighan's algorithm (O(K))

```c
#include <stdint.h>
#include <stdio.h>

uint32_t count_set_bits(uint32_t n) {
    uint32_t count = 0;
    while (n > 0) {
        n = n & (n - 1);        /* clears the lowest set bit */
        count++;             /* so the loop runs once per set bit (K times) */
    }
    return count;
}

// or

uint32_t count_set_bits(uint32_t n) {
    uint32_t count = 0;
    while (n > 0) 
    {
        if(n & 1)
        {
            count++;
        }        /* clears the lowest set bit */
        n = n >> 1;           /* so the loop runs once per set bit (K times) */
    }
    return count;
}

int main(void) {
    printf("Set bits: %u\n", count_set_bits(0x80F00101));   /* 1 + 4 + 1 + 1 = 7 */
    return 0;
}
```

**Key concept:** `n & (n - 1)` removes exactly one set bit each iteration.

### Q03: Memory move that handles overlapping regions

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void* custom_memmove(void* dest, const void* src, size_t n) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    if (d == s || n == 0) return dest;         /* nothing to do */
    if (d < s) {
        for (size_t i = 0; i < n; i++) d[i] = s[i];       /* copy forward: safe when dest is below src */
    } else {
        for (size_t i = n; i > 0; i--) d[i - 1] = s[i - 1];   /* copy backward: safe when dest is above src */
    }
    return dest;
}

int main(void) {
    char buf[20] = "Hello World";
    custom_memmove(buf + 2, buf, 5);           /* overlapping move */
    printf("Result: %s\n", buf);               /* HeHelloorld */
    return 0;
}
```

**Key concept:** copy backward when the destination is after the source, so unread source bytes are not overwritten.

### Q04: Integer-to-ASCII conversion (base 10 and base 16)

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static void reverse(char* str, int len) {
    int i = 0, j = len - 1;
    while (i < j) {
        char tmp = str[i]; str[i++] = str[j]; str[j--] = tmp;
    }
}

char* custom_itoa(int32_t num, char* str, int base) {
    int i = 0;
    bool neg = false;
    uint32_t u;                                   /* work in unsigned to avoid INT32_MIN overflow */

    if (num == 0) { str[i++] = '0'; str[i] = '\0'; return str; }

    if (num < 0 && base == 10) {
        neg = true;
        u = (uint32_t)0 - (uint32_t)num;          /* safe magnitude, even for INT32_MIN */
    } else {
        u = (uint32_t)num;                        /* negative hex prints as two's complement */
    }

    while (u != 0) {
        uint32_t rem = u % (uint32_t)base;        /* least significant digit first */
        str[i++] = (rem > 9) ? (char)((rem - 10) + 'A') : (char)(rem + '0');
        u /= (uint32_t)base;
    }
    if (neg) str[i++] = '-';
    str[i] = '\0';
    reverse(str, i);                              /* digits were produced in reverse order */
    return str;
}

int main(void) {
    char buf[33];
    printf("%s\n", custom_itoa(-255, buf, 10));   /* -255 */
    printf("%s\n", custom_itoa(255, buf, 16));    /* FF */
    return 0;
}
```

**Key concept:** extract digits with modulo (lowest first), then reverse the string.

**Watch out:** the buffer must be large enough (33 bytes covers base 2 for 32 bits). Working in `uint32_t` avoids overflow when negating `INT32_MIN`.

### Q05: String-to-integer conversion with overflow detection

```c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool custom_atoi(const char* str, int32_t* res) {
    if (!str || !res) return false;                /* reject NULL pointers */
    while (*str == ' ') str++;                     /* skip leading spaces */

    int sign = 1;
    if (*str == '-' || *str == '+') {
        if (*str == '-') sign = -1;
        str++;
    }

    int64_t acc = 0;                               /* 64-bit accumulator detects 32-bit overflow */
    while (*str >= '0' && *str <= '9') {
        acc = acc * 10 + (*str - '0');
        if (sign == 1 && acc > INT32_MAX) return false;     /* too large */
        if (sign == -1 && -acc < INT32_MIN) return false;   /* too small */
        str++;
    }
    *res = (int32_t)(acc * sign);
    return true;
}

int main(void) {
    int32_t val;
    if (custom_atoi(" -1234", &val)) printf("Value: %d\n", val);   /* -1234 */
    return 0;
}
```

**Key concept:** accumulate in 64 bits so overflow of the 32-bit range can be detected before it happens.

**Watch out:** this version accepts an input with no digits as 0. A production version should also reject that case.

### Q06: Reverse the bits of an 8-bit value

```c
#include <stdint.h>
#include <stdio.h>

uint8_t reverse_bits8(uint8_t val) {
    val = ((val & 0xF0) >> 4) | ((val & 0x0F) << 4);   /* swap nibbles */
    val = ((val & 0xCC) >> 2) | ((val & 0x33) << 2);   /* swap 2-bit pairs */
    val = ((val & 0xAA) >> 1) | ((val & 0x55) << 1);   /* swap neighbouring bits */
    return val;
}

int main(void) {
    printf("0x%02X -> 0x%02X\n", 0xF0, reverse_bits8(0xF0));   /* 0x0F */
    return 0;
}
```

**Key concept:** divide and conquer with masks, O(1) time.

### Q07: Position of the most significant bit

```c
#include <stdint.h>
#include <stdio.h>

int find_msb(uint32_t val) {
    if (val == 0) return -1;                      /* no bit set */
    int pos = 0;
    if (val >= 1U << 16) { val >>= 16; pos += 16; }   /* is the top half non-zero? */
    if (val >= 1U << 8)  { val >>= 8;  pos += 8;  }
    if (val >= 1U << 4)  { val >>= 4;  pos += 4;  }
    if (val >= 1U << 2)  { val >>= 2;  pos += 2;  }
    if (val >= 1U << 1)  { pos += 1; }
    return pos;
}

int main(void) {
    printf("MSB of 0x8000: %d\n", find_msb(0x8000));   /* 15 */
    return 0;
}
```

**Key concept:** a binary search over the bit positions takes 5 steps instead of 32. On Cortex-M, `__builtin_clz` maps to the `CLZ` instruction.

### Q08: Is a number a power of two?

```c
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_power_of_two(uint32_t n) {
    return (n > 0) && ((n & (n - 1)) == 0);       /* one set bit only */
}

int main(void) {
    printf("16 is Power of 2: %s\n", is_power_of_two(16) ? "Yes" : "No");
    return 0;
}
```

**Key concept:** a power of two has exactly one set bit, so clearing it gives zero.

### Q09: Toggle `n` bits starting at bit `p`

```c
#include <stdint.h>
#include <stdio.h>

uint32_t toggle_bit_range(uint32_t val, uint8_t p, uint8_t n) {
    uint32_t mask = ((1U << n) - 1) << p;         /* n ones, moved up to position p */
    return val ^ mask;                            /* XOR flips exactly those bits */
}

int main(void) {
    printf("Toggled: 0x%08X\n", toggle_bit_range(0xFF00, 8, 4));   /* 0x0000F000: bits 8-11 were 1111, now 0000 */
    return 0;
}
```

**Key concept:** build a contiguous mask, then XOR.

**Watch out:** `n` must be less than 32, since `1U << 32` is undefined.

### Q10: Align an address up to a power-of-two boundary

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

uintptr_t align_up(uintptr_t addr, size_t align) {
    /* Add (align - 1), then clear the low bits. align must be a power of two. */
    return (addr + (align - 1)) & ~(uintptr_t)(align - 1);
}

int main(void) {
    printf("Aligned: 0x%zX\n", (size_t)align_up(0x1003, 4));    /* 0x1004 */
    return 0;
}
```

**Key concept:** add the alignment minus one, then mask off the low bits.

### Q11: Word-at-a-time memory copy

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void* aligned_memcpy(void* dest, const void* src, size_t n) {
    uint8_t* d8 = (uint8_t*)dest;
    const uint8_t* s8 = (const uint8_t*)src;

    /* Use 32-bit copies only when BOTH pointers are 4-byte aligned. */
    if ((((uintptr_t)d8 | (uintptr_t)s8) & 3U) == 0U) {
        uint32_t* d32 = (uint32_t*)d8;
        const uint32_t* s32 = (const uint32_t*)s8;
        for (size_t words = n / 4; words > 0; words--) *d32++ = *s32++;
        d8 = (uint8_t*)d32;
        s8 = (const uint8_t*)s32;
        n %= 4;                                   /* the leftover 0-3 bytes */
    }
    while (n--) *d8++ = *s8++;                    /* byte copy for the tail (or the unaligned case) */
    return dest;
}

int main(void) {
    uint32_t src[2] = {0x11223344, 0x55667788}, dst[2];
    aligned_memcpy(dst, src, sizeof(src));
    printf("Copied word: 0x%08X\n", dst[0]);
    return 0;
}
```

**Key concept:** moving 4 bytes per access reduces bus cycles.

**Watch out:** casting unaligned pointers to `uint32_t *` can fault on some cores, so check alignment first. Regions must not overlap (use `memmove` for that).

### Q12: Word-at-a-time memset

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void* custom_memset(void* s, int c, size_t n) {
    uint8_t* p = (uint8_t*)s;
    uint8_t byte = (uint8_t)c;

    while (n > 0 && ((uintptr_t)p & 3U) != 0U) {   /* fill single bytes until 4-byte aligned */
        *p++ = byte;
        n--;
    }

    uint32_t pattern = byte;                       /* replicate the byte into all 4 lanes */
    pattern |= (pattern << 8) | (pattern << 16) | (pattern << 24);
    while (n >= 4) {
        *(uint32_t*)p = pattern;                   /* one 32-bit store writes 4 bytes */
        p += 4;
        n -= 4;
    }
    while (n--) *p++ = byte;                       /* leftover tail bytes */
    return s;
}

int main(void) {
    uint8_t buf[8];
    custom_memset(buf, 0xAA, sizeof(buf));
    printf("Byte 0: 0x%02X\n", buf[0]);
    return 0;
}
```

**Key concept:** replicate the byte across a 32-bit word for faster fills.

### Q13: `strlen` without the C library

```c
#include <stddef.h>
#include <stdio.h>

size_t custom_strlen(const char* s) {
    const char* p = s;
    while (*p) p++;                  /* advance to the terminating '\0' */
    return (size_t)(p - s);          /* pointer subtraction gives the count */
}

int main(void) {
    printf("Length: %zu\n", custom_strlen("Embedded"));   /* 8 */
    return 0;
}
```

**Key concept:** pointer subtraction avoids a separate counter.

### Q14: `strcmp` and `strncmp`

```c
#include <stddef.h>
#include <stdio.h>

int custom_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) { s1++; s2++; }                /* stop at a difference or the end */
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;   /* compare as unsigned chars */
}

int custom_strncmp(const char* s1, const char* s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) { s1++; s2++; n--; }
    if (n == 0) return 0;                                       /* first n characters matched */
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int main(void) {
    printf("strncmp: %d\n", custom_strncmp("Test", "Team", 2));   /* 0: "Te" == "Te" */
    printf("strcmp:  %d\n", custom_strcmp("Test", "Team"));       /* positive: 's' > 'a' */
    return 0;
}
```

**Key concept:** compare as `unsigned char` until a mismatch, the end, or the length limit.

### Q15: `strncpy` that always null-terminates

```c
#include <stddef.h>
#include <stdio.h>

char* safe_strncpy(char* dest, const char* src, size_t n) {
    if (n == 0) return dest;
    size_t i;
    for (i = 0; i < n - 1 && src[i] != '\0'; i++) {    /* leave room for the terminator */
        dest[i] = src[i];
    }
    dest[i] = '\0';                                    /* always terminate */
    return dest;
}

int main(void) {
    char buf[5];
    safe_strncpy(buf, "EmbeddedC", sizeof(buf));
    printf("Safe String: %s\n", buf);                  /* Embe */
    return 0;
}
```

**Key concept:** always reserve the last byte for `'\0'` to prevent buffer overruns.

### Q16: Swap two integers without a temporary

```c
#include <stdio.h>

void xor_swap(int* a, int* b) {
    if (a != b) {                 /* required: XOR-swapping a variable with itself zeroes it */
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

int main(void) {
    int x = 10, y = 20;
    xor_swap(&x, &y);
    printf("x=%d, y=%d\n", x, y);         /* x=20, y=10 */
    return 0;
}
```

**Key concept:** `(A ^ B) ^ A = B`, so XOR can exchange two values.

**Watch out:** a normal temporary variable is usually clearer and just as fast.

### Q17: Find the missing number in `1..N`

```c
#include <stdio.h>

int find_missing(const int* arr, int n) {   /* arr holds n numbers taken from 1..n+1 */
    int xor_all = 0;
    for (int i = 1; i <= n + 1; i++) xor_all ^= i;    /* XOR of the full range 1..n+1 */
    for (int i = 0; i < n; i++) xor_all ^= arr[i];    /* XOR out every number that is present */
    return xor_all;                                   /* only the missing number remains */
}

int main(void) {
    int data[] = {1, 2, 4, 5};
    printf("Missing: %d\n", find_missing(data, 4));   /* 3 */
    return 0;
}
```

**Key concept:** duplicates cancel under XOR, leaving the missing value.

### Q18: Find a duplicate using bit flags

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int find_duplicate(const uint8_t* arr, size_t len) {
    uint32_t flag = 0;                            /* one bit per value seen: supports values 0..31 */
    for (size_t i = 0; i < len; i++) {
        if (flag & (1U << arr[i])) return arr[i];   /* bit already set: seen before */
        flag |= (1U << arr[i]);                     /* remember this value */
    }
    return -1;                                    /* no duplicate */
}

int main(void) {
    uint8_t data[] = {3, 1, 4, 1, 5};
    printf("Duplicate: %d\n", find_duplicate(data, 5));   /* 1 */
    return 0;
}
```

**Key concept:** a bitmask tracks seen values with almost no memory.

**Watch out:** values must be below 32 for a 32-bit flag word.

### Q19: Q16.16 fixed-point multiply

```c
#include <stdint.h>
#include <stdio.h>

typedef int32_t q16_t;                                   /* 16 integer bits, 16 fraction bits */
#define Q16_SHIFT 16
#define TO_Q16(f)   ((q16_t)((f) * (1 << Q16_SHIFT)))    /* float to fixed */
#define TO_FLOAT(q) ((float)(q) / (1 << Q16_SHIFT))      /* fixed to float */

q16_t q16_mul(q16_t a, q16_t b) {
    return (q16_t)(((int64_t)a * b) >> Q16_SHIFT);       /* widen first: the raw product needs 64 bits */
}

int main(void) {
    q16_t r = q16_mul(TO_Q16(2.5f), TO_Q16(4.0f));
    printf("Result: %.2f\n", TO_FLOAT(r));               /* 10.00 */
    return 0;
}
```

**Key concept:** cast to 64 bits before shifting, or the product overflows.

### Q20: Absolute value without branching

```c
#include <stdint.h>
#include <stdio.h>

int32_t branchless_abs(int32_t v) {
    int32_t const mask = v >> 31;        /* 0 for v >= 0, -1 (all ones) for v < 0 */
    return (v + mask) ^ mask;            /* for negatives: subtract 1, then flip the bits */
}

int main(void) {
    printf("Abs: %d\n", branchless_abs(-42));      /* 42 */
    return 0;
}
```

**Key concept:** the sign mask conditionally applies two's-complement negation.

**Watch out:** `v >> 31` on a negative value is implementation-defined, and `INT32_MIN` has no positive counterpart. A plain `(v < 0) ? -v : v` is usually just as fast and clearer.

### Q21: Rotate left and rotate right (32-bit)

```c
#include <stdint.h>
#include <stdio.h>

uint32_t rol32(uint32_t val, uint8_t shift) {
    shift &= 31U;                                        /* keep the count in 0..31 */
    return (val << shift) | (val >> ((32U - shift) & 31U));   /* & 31 avoids a shift by 32 (undefined) */
}

uint32_t ror32(uint32_t val, uint8_t shift) {
    shift &= 31U;
    return (val >> shift) | (val << ((32U - shift) & 31U));
}

int main(void) {
    printf("ROL: 0x%08X\n", rol32(0x80000001, 1));       /* 0x00000003 */
    printf("ROR: 0x%08X\n", ror32(0x80000001, 1));       /* 0xC0000000 */
    return 0;
}
```

**Key concept:** combine two shifts so the bits that fall off one end re-enter at the other. Compilers turn this pattern into a single rotate instruction.

### Q22: Extract a bit-field from a register

```c
#include <stdint.h>
#include <stdio.h>

uint32_t extract_field(uint32_t reg, uint32_t mask, uint8_t shift) {
    return (reg & mask) >> shift;      /* isolate the field, then move it down to bit 0 */
}

int main(void) {
    printf("Field: 0x%X\n", extract_field(0x0000F000, 0x0000F000, 12));   /* 0xF */
    return 0;
}
```

### Q23: Write a field without disturbing other bits

```c
#include <stdint.h>
#include <stdio.h>

uint32_t set_field(uint32_t reg, uint32_t val, uint32_t mask, uint8_t shift) {
    return (reg & ~mask)                 /* 1. clear the old field */
         | ((val << shift) & mask);      /* 2. insert the new value, masked so it cannot spill */
}

int main(void) {
    printf("Reg: 0x%08X\n", set_field(0xFFFFFFFF, 0x5, 0x000000F0, 4));   /* 0xFFFFFF5F */
    return 0;
}
```

**Key concept:** clear with the inverted mask, then OR in the shifted value.

### Q24: Detect endianness at run time

```c
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

bool is_little_endian(void) {
    uint16_t val = 0x0001;
    uint8_t* ptr = (uint8_t*)&val;        /* look at the first byte in memory */
    return ptr[0] == 0x01;                /* little-endian stores the low byte first */
}

int main(void) {
    printf("System is: %s\n", is_little_endian() ? "Little-Endian" : "Big-Endian");
    return 0;
}
```

### Q25: Integer square root without floating point

```c
#include <stdint.h>
#include <stdio.h>

uint32_t isqrt(uint32_t n) {
    uint32_t res = 0, bit = 1U << 30;     /* start with the highest power of four <= 2^30 */
    while (bit > n) bit >>= 2;            /* reduce to the highest power of four <= n */
    while (bit != 0) {
        if (n >= res + bit) {
            n -= res + bit;               /* this bit belongs in the result */
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;                        /* move to the next digit */
    }
    return res;
}

int main(void) {
    printf("sqrt(25): %u\n", isqrt(25));  /* 5 */
    return 0;
}
```

**Key concept:** digit-by-digit square root with shifts and no math library.

### Q26: Even parity of a byte

```c
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

bool get_parity8(uint8_t val) {
    val ^= val >> 4;          /* fold the byte in half... */
    val ^= val >> 2;          /* ...then in half again... */
    val ^= val >> 1;          /* ...until bit 0 holds the parity */
    return val & 1;           /* 1 = odd number of set bits */
}

int main(void) {
    printf("Parity of 0x03: %d\n", get_parity8(0x03));   /* 0: two set bits, so even */
    return 0;
}
```

### Q27: Reverse a string in place

```c
#include <stdio.h>
#include <string.h>

void reverse_string(char* str) {
    if (!str) return;
    int i = 0, j = (int)strlen(str) - 1;
    while (i < j) {
        char tmp = str[i]; str[i++] = str[j]; str[j--] = tmp;   /* swap the ends, move inward */
    }
}

int main(void) {
    char msg[] = "MCU";
    reverse_string(msg);
    printf("Reversed: %s\n", msg);        /* UCM */
    return 0;
}
```

### Q28: Do two integers have opposite signs?

```c
#include <stdbool.h>
#include <stdio.h>

bool has_opposite_signs(int x, int y) {
    return (x ^ y) < 0;       /* the sign bit of x ^ y is 1 only if the sign bits differ */
}

int main(void) {
    printf("Opposite: %s\n", has_opposite_signs(10, -5) ? "Yes" : "No");
    return 0;
}
```

### Q29: `strchr`

```c
#include <stdio.h>

char* custom_strchr(const char* s, int c) {
    while (*s != (char)c) {
        if (*s == '\0') return NULL;      /* reached the end without finding it */
        s++;
    }
    return (char*)s;                      /* also finds the terminator when c == '\0' */
}

int main(void) {
    const char* str = "MCU Driver";
    printf("Found at: %s\n", custom_strchr(str, 'D'));    /* Driver */
    return 0;
}
```

### Q30: Read an unaligned 16-bit value safely

```c
#include <stdint.h>
#include <stdio.h>

uint16_t read_u16_unaligned(const uint8_t* buf) {
    return (uint16_t)buf[0] | ((uint16_t)buf[1] << 8);   /* build it byte by byte: little-endian */
}

int main(void) {
    uint8_t stream[] = {0x00, 0xCD, 0xAB};
    printf("Unaligned Val: 0x%04X\n", read_u16_unaligned(&stream[1]));   /* 0xABCD */
    return 0;
}
```

**Key concept:** assemble multi-byte values from single-byte reads, so alignment never matters.

---

## Part B: Practice programs

## B1. Armstrong number

**Idea:** A number equals the sum of its digits, each raised to the power of the number of digits (153 = 1^3 + 5^3 + 3^3).

```c
#include <stdio.h>

int main(void) {
    int num, originalNum, remainder, result = 0, count = 0;

    printf("Enter a non-negative integer: ");
    scanf("%d", &num);

    originalNum = num;

    /* Step 1: count the digits */
    while (originalNum != 0) {
        originalNum /= 10;
        count++;
    }

    originalNum = num;

    /* Step 2: add each digit raised to the power 'count' */
    while (originalNum != 0) {
        remainder = originalNum % 10;         /* the last digit */

        int power = 1;
        for (int i = 0; i < count; i++) {     /* digit^count by repeated multiplication */
            power *= remainder;
        }

        result += power;
        originalNum /= 10;                    /* drop the last digit */
    }

    /* Step 3: compare with the original */
    if (result == num)
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);

    return 0;
}
```

## B2. Prime number

**Idea:** A prime has no divisor between 2 and its square root.

```c
#include <stdio.h>

int main(void) {
    int num, isPrime = 1;

    printf("Enter a positive integer: ");
    scanf("%d", &num);

    if (num <= 1) {
        isPrime = 0;                          /* 0 and 1 are not prime */
    } else {
        for (int i = 2; (long)i * i <= num; i++) {   /* i * i <= num is enough: no need to go to num / 2 */
            if (num % i == 0) {
                isPrime = 0;                  /* found a factor */
                break;
            }
        }
    }

    printf(isPrime ? "%d is a prime number.\n" : "%d is not a prime number.\n", num);
    return 0;
}
```

**Follow-up:** checking up to `sqrt(num)` gives O(sqrt n) instead of O(n / 2).

## B3. Reverse a string and reverse a sentence's words

**Idea:** To reverse the order of words, reverse the whole string, then reverse each word back.

```c
#include <stdio.h>
#include <string.h>

static void reverse_range(char *s, int left, int right) {
    while (left < right) {
        char t = s[left];
        s[left++] = s[right];
        s[right--] = t;
    }
}

void revstr(char *str) {
    reverse_range(str, 0, (int)strlen(str) - 1);
}

void rev_sen(char *str) {
    int l = (int)strlen(str);

    revstr(str);                                   /* step 1: "Hello World" -> "dlroW olleH" */

    int start = 0;
    for (int i = 0; i <= l; i++) {
        if (str[i] == ' ' || str[i] == '\0') {     /* end of a word */
            reverse_range(str, start, i - 1);      /* step 2: fix that word */
            start = i + 1;
        }
    }
    printf("rev sen: %s\n", str);                  /* World Hello */
}

int main(void) {
    char s[] = "Hello World";
    rev_sen(s);
    return 0;
}
```

## B4. Find repeated letters in a string

**Idea:** Count how many times each character occurs, then print those seen more than once.

```c
#include <stdio.h>
#include <stdint.h>

void find_repeated_letters(const char *str) {
    uint8_t count[256] = {0};                      /* one counter per possible byte value */

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            count[(uint8_t)str[i]]++;              /* cast to uint8_t so negative chars are safe indexes */
        }
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] > 1) {
            printf("%c ", i);                      /* seen more than once */
        }
    }
    printf("\n");
}
```

**Watch out:** a `uint8_t` counter wraps after 255 occurrences. Use a wider type for long inputs.

## B5. Reverse hexadecimal digits

**Idea:** Take the lowest nibble each time and push it into the result from the other side.

```c
#include <stdint.h>

uint32_t reverse_hex(uint32_t num) {
    uint32_t rev = 0;

    while (num) {
        rev = (rev << 4) | (num & 0xF);    /* append the lowest nibble to the result */
        num >>= 4;                         /* move to the next nibble */
    }

    return rev;    /* 0x1234 -> 0x4321. Leading zero nibbles of the input are not preserved. */
}
```

## B6. Bit reversal (8, 16, 32 bit, and generic)

**Idea:** Swap halves, then quarters, and so on, down to single bits.

```c
#include <stdint.h>

/* 8-bit */
uint8_t reverseBits(uint8_t b) {
    b = (uint8_t)(((b & 0xF0) >> 4) | ((b & 0x0F) << 4));    /* nibbles */
    b = (uint8_t)(((b & 0xCC) >> 2) | ((b & 0x33) << 2));    /* pairs */
    b = (uint8_t)(((b & 0xAA) >> 1) | ((b & 0x55) << 1));    /* bits */
    return b;
}

/* 16-bit */
uint16_t reverseBits16(uint16_t x) {
    x = (uint16_t)(((x & 0xFF00) >> 8) | ((x & 0x00FF) << 8));   /* swap bytes */
    x = (uint16_t)(((x & 0xF0F0) >> 4) | ((x & 0x0F0F) << 4));   /* swap nibbles */
    x = (uint16_t)(((x & 0xCCCC) >> 2) | ((x & 0x3333) << 2));   /* swap pairs */
    x = (uint16_t)(((x & 0xAAAA) >> 1) | ((x & 0x5555) << 1));   /* swap bits */
    return x;
}

/* 32-bit */
uint32_t reverseBits32(uint32_t x) {
    x = ((x & 0xFFFF0000U) >> 16) | ((x & 0x0000FFFFU) << 16);
    x = ((x & 0xFF00FF00U) >> 8)  | ((x & 0x00FF00FFU) << 8);
    x = ((x & 0xF0F0F0F0U) >> 4)  | ((x & 0x0F0F0F0FU) << 4);
    x = ((x & 0xCCCCCCCCU) >> 2)  | ((x & 0x33333333U) << 2);
    x = ((x & 0xAAAAAAAAU) >> 1)  | ((x & 0x55555555U) << 1);
    return x;
}

/* Generic N-bit: reverse only the lowest num_bits bits */
uint64_t reverseBitsGeneric(uint64_t num, uint8_t num_bits) {
    uint64_t rev = 0;
    for (uint8_t i = 0; i < num_bits; i++) {
        rev = (rev << 1) | (num & 1);      /* take the lowest bit of num, push it in from the other end */
        num >>= 1;
    }
    return rev;
}
```

## B7. Byte splitting, combining, nibble swap, byte swap

```c
#include <stdio.h>
#include <stdint.h>

/* Split a 16-bit value into two bytes, and combine two bytes into one value */
#define GET_HIGH_8(num)        ((uint8_t)(((uint16_t)(num) >> 8) & 0xFF))
#define GET_LOW_8(num)         ((uint8_t)((uint16_t)(num) & 0xFF))
#define TO_16_BITS(high, low)  ((uint16_t)(((uint16_t)(uint8_t)(high) << 8) | (uint8_t)(low)))

void to_8_bits(uint16_t num) {
    uint8_t high = (num >> 8) & 0xFF;
    uint8_t low  = num & 0xFF;
    printf("high: %u, low = %u\n", high, low);
}

void to_16_bits(uint8_t high, uint8_t low) {
    uint16_t n = (uint16_t)(((uint16_t)high << 8) | low);
    printf("num: %u\n", n);
}

/* Nibble swaps: swap the two halves of every byte */
uint8_t  swap_nibbles_8(uint8_t val)   { return (uint8_t)(((val & 0x0F) << 4) | ((val & 0xF0) >> 4)); }
uint16_t swap_nibbles_16(uint16_t val) { return (uint16_t)(((val & 0x0F0F) << 4) | ((val & 0xF0F0) >> 4)); }
uint32_t swap_nibbles_32(uint32_t val) { return ((val & 0x0F0F0F0FU) << 4) | ((val & 0xF0F0F0F0U) >> 4); }

/* Endianness (byte order) swaps */
uint16_t swap_num_16(uint16_t val) {
    return (uint16_t)(((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8));
}

uint32_t swap_num_32(uint32_t val) {
    return ((val & 0x000000FFU) << 24) |
           ((val & 0x0000FF00U) << 8)  |
           ((val & 0x00FF0000U) >> 8)  |
           ((val & 0xFF000000U) >> 24);
}
```

## B8. Array rotation, insertion, and deletion

**Idea:** Shifting elements one step at a time is simple. For large rotations, use the three-reversal method.

```c
#include <stdio.h>
#include <stdint.h>

#define LEFT  1
#define RIGHT 0

void print_arr(const uint8_t a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/* Rotate left by one: the first element moves to the end */
void rotate_left(uint8_t a[], int n) {
    uint8_t temp = a[0];                       /* save the element that will wrap around */
    for (int i = 0; i < n - 1; i++) {
        a[i] = a[i + 1];                       /* shift everything one place left */
    }
    a[n - 1] = temp;
    print_arr(a, n);
}

/* Rotate right by one: the last element moves to the front */
void rotate_right(uint8_t a[], int n) {
    uint8_t temp = a[n - 1];
    for (int i = n - 1; i > 0; i--) {
        a[i] = a[i - 1];                       /* shift everything one place right */
    }
    a[0] = temp;
    print_arr(a, n);
}

/* Rotate by shift_cnt positions in a chosen direction */
void rotate_pos(uint8_t a[], uint8_t n, uint8_t dir, uint8_t shift_cnt) {
    if (n <= 1 || shift_cnt == 0) {
        return;
    }

    shift_cnt = shift_cnt % n;                 /* rotating by n is the same as not rotating */
    while (shift_cnt > 0) {
        if (dir == LEFT) {
            uint8_t temp = a[0];
            for (int i = 0; i < n - 1; i++) a[i] = a[i + 1];
            a[n - 1] = temp;
        } else {
            uint8_t temp = a[n - 1];
            for (int i = n - 1; i > 0; i--) a[i] = a[i - 1];
            a[0] = temp;
        }
        shift_cnt--;
    }
    print_arr(a, n);
}

/* Insert 'num' at index 'pos'. The array must have room for one more element. */
uint8_t insert_at_pos(uint8_t a[], uint8_t n, uint8_t num, uint8_t pos) {
    if (pos > n) {
        printf("Invalid position!\n");
        return n;
    }
    for (int i = n; i > pos; i--) {
        a[i] = a[i - 1];                       /* open a gap by shifting right */
    }
    a[pos] = num;
    return (uint8_t)(n + 1);
}

/* Remove the element at index 'pos' */
uint8_t remove_at_pos(uint8_t a[], uint8_t n, uint8_t pos) {
    if (pos >= n) {
        printf("Invalid position!\n");
        return n;
    }
    for (int i = pos; i < n - 1; i++) {
        a[i] = a[i + 1];                       /* close the gap by shifting left */
    }
    return (uint8_t)(n - 1);
}

int main(void) {
    uint8_t a[10] = {1, 2, 3, 4, 5};           /* capacity 10, 5 in use */
    uint8_t n = 5;

    rotate_left(a, n);                         /* 2 3 4 5 1 */
    rotate_right(a, n);                        /* 1 2 3 4 5 */
    rotate_pos(a, n, LEFT, 3);                 /* 4 5 1 2 3 */

    n = insert_at_pos(a, n, 99, 2);
    print_arr(a, n);                           /* 4 5 99 1 2 3 */

    n = remove_at_pos(a, n, 1);
    print_arr(a, n);                           /* 4 99 1 2 3 */
    return 0;
}
```

## B9. Sorting, searching, and removing duplicates

```c
#include <stdio.h>
#include <stdint.h>

static void print_arr(const uint8_t a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

/* Bubble sort: repeatedly swap neighbours that are out of order. O(n^2). */
void bubble_sort(uint8_t a[], uint8_t n) {
    for (int i = 0; i < n; i++) {
        int swapped = 0;
        for (int k = 0; k < n - 1 - i; k++) {          /* the last i elements are already in place */
            if (a[k] > a[k + 1]) {
                uint8_t temp = a[k];
                a[k] = a[k + 1];
                a[k + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;                           /* already sorted: stop early */
    }
    print_arr(a, n);
}

/* Linear search: check every element. O(n). Works on unsorted data. */
int linear_search(const uint8_t a[], uint8_t n, uint8_t target) {
    for (int i = 0; i < n; i++) {
        if (a[i] == target) return i;
    }
    return -1;                                         /* not found */
}

/* Binary search: halve the range each step. O(log n). The array must be sorted. */
int binary_search(const uint8_t a[], uint8_t n, uint8_t target) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;              /* avoids overflow of (low + high) */

        if (a[mid] == target) return mid;
        if (a[mid] < target)  low = mid + 1;           /* target is in the upper half */
        else                  high = mid - 1;          /* target is in the lower half */
    }
    return -1;
}

/* Remove duplicates in place, keeping the first occurrence. Returns the new size. O(n^2). */
int remove_duplicates(int arr[], int size) {
    int count = 0;                                     /* number of unique elements so far */

    for (int i = 0; i < size; i++) {
        int k;
        for (k = 0; k < count; k++) {
            if (arr[i] == arr[k]) break;               /* already kept */
        }
        if (k == count) {                              /* not found among the kept ones */
            arr[count++] = arr[i];
        }
    }
    return count;
}

int main(void) {
    uint8_t a[] = {5, 2, 9, 1, 7};
    bubble_sort(a, 5);                                 /* 1 2 5 7 9 */
    printf("index of 7: %d\n", binary_search(a, 5, 7));   /* 3 */
    printf("index of 4: %d\n", linear_search(a, 5, 4));   /* -1 */

    int d[] = {1, 2, 2, 3, 1};
    int n = remove_duplicates(d, 5);                   /* 1 2 3 */
    for (int i = 0; i < n; i++) printf("%d ", d[i]);
    printf("\n");
    return 0;
}
```

## B10. Singly linked list: insert, delete, and traversal

**Idea:** Two API styles. A **return-based** function returns the new head. A **double-pointer** function changes the caller's head directly.

```c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;                 /* the value stored in the node */
    struct node *next;        /* the next node, or NULL at the end */
};

/* Create a node. Returns NULL if the allocation fails. */
static struct node *make_node(int data, struct node *next) {
    struct node *n = (struct node *)malloc(sizeof *n);
    if (n == NULL) return NULL;
    n->data = data;
    n->next = next;
    return n;
}

/* ---- Return-based API: caller writes head = insert_start(head, x); ---- */

struct node *insert_start(struct node *head, int data) {
    struct node *n = make_node(data, head);       /* new node points at the old head */
    return n ? n : head;                          /* on failure, keep the list unchanged */
}

struct node *insert_end(struct node *head, int data) {
    struct node *n = make_node(data, NULL);
    if (n == NULL) return head;
    if (head == NULL) return n;                   /* empty list: the new node is the head */

    struct node *t = head;
    while (t->next != NULL) t = t->next;          /* walk to the last node */
    t->next = n;
    return head;
}

struct node *delete_start(struct node *head) {
    if (head == NULL) return NULL;
    struct node *next = head->next;               /* remember the new head before freeing */
    free(head);
    return next;
}

/* Insert so the new node becomes position 'pos' (1-based). */
struct node *insert_pos(struct node *head, int data, int pos) {
    if (pos == 1) return insert_start(head, data);

    struct node *t = head;
    for (int i = 1; i < pos - 1 && t != NULL; i++) t = t->next;   /* stop at node pos-1 */
    if (t == NULL) { printf("Position out of bounds\n"); return head; }

    struct node *n = make_node(data, t->next);    /* link the new node into the gap */
    if (n) t->next = n;
    return head;
}

/* Delete the node at position 'pos' (1-based). */
struct node *del_pos(struct node *head, int pos) {
    if (head == NULL) return NULL;
    if (pos == 1) return delete_start(head);

    struct node *t = head;
    for (int i = 1; i < pos - 1 && t != NULL; i++) t = t->next;
    if (t == NULL || t->next == NULL) { printf("Position out of bounds\n"); return head; }

    struct node *victim = t->next;
    t->next = victim->next;                       /* unlink first... */
    free(victim);                                 /* ...then free */
    return head;
}

/* ---- Double-pointer API: call as insert_at_start(&head, x); ---- */

void insert_at_start(struct node **head, int data) {
    struct node *n = make_node(data, *head);
    if (n) *head = n;                             /* change the caller's head pointer */
}

void insert_at_end(struct node **head, int data) {
    struct node *n = make_node(data, NULL);
    if (n == NULL) return;

    struct node **pp = head;                      /* pointer to the link that must be filled */
    while (*pp != NULL) pp = &(*pp)->next;        /* walk until we reach the NULL link */
    *pp = n;                                      /* works for an empty list too */
}

void delete_at_start(struct node **head) {
    if (head == NULL || *head == NULL) return;
    struct node *t = *head;
    *head = t->next;
    free(t);
}

/* ---- Printing ---- */

void print_list(const struct node *head) {
    for (const struct node *t = head; t != NULL; t = t->next) printf("%d -> ", t->data);
    printf("NULL\n");
}

void print_list_recursive(const struct node *head) {
    if (head == NULL) { printf("NULL\n"); return; }   /* base case */
    printf("%d -> ", head->data);
    print_list_recursive(head->next);                 /* recursion uses stack: avoid on long lists */
}

int main(void) {
    struct node *list = NULL;

    list = insert_start(list, 5);
    list = insert_start(list, 15);
    list = insert_start(list, 25);
    print_list(list);                    /* 25 -> 15 -> 5 -> NULL */

    insert_at_start(&list, 30);
    print_list(list);                    /* 30 -> 25 -> 15 -> 5 -> NULL */

    list = delete_start(list);
    list = delete_start(list);
    print_list(list);                    /* 15 -> 5 -> NULL */

    delete_at_start(&list);
    print_list(list);                    /* 5 -> NULL */

    list = insert_end(list, 31);
    insert_at_end(&list, 32);
    print_list(list);                    /* 5 -> 31 -> 32 -> NULL */

    while (list) delete_at_start(&list); /* free everything before exit */
    return 0;
}
```

**Remember:** when a function must change the head, pass `struct node **` or return the new head.

## B11. In-place linked list reversal

**Idea:** Walk the list once, turning each `next` pointer to point backward.

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *reverseList(struct Node *head) {
    struct Node *prev_node = NULL;                 /* the reversed part built so far */
    struct Node *curr_node = head;

    while (curr_node != NULL) {
        struct Node *next_node = curr_node->next;  /* 1. remember the rest of the list */
        curr_node->next = prev_node;               /* 2. point this node backward */
        prev_node = curr_node;                     /* 3. advance both pointers */
        curr_node = next_node;
    }

    return prev_node;                              /* prev_node is the new head */
}

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void printList(const struct Node *head) {
    for (const struct Node *c = head; c != NULL; c = c->next) printf("%d -> ", c->data);
    printf("NULL\n");
}

void freeList(struct Node *head) {
    while (head != NULL) {
        struct Node *next_node = head->next;       /* save before freeing */
        free(head);
        head = next_node;
    }
}

int main(void) {
    struct Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Original List:\n");
    printList(head);                               /* 1 -> 2 -> 3 -> 4 -> 5 -> NULL */

    head = reverseList(head);

    printf("\nReversed List:\n");
    printList(head);                               /* 5 -> 4 -> 3 -> 2 -> 1 -> NULL */

    freeList(head);
    return 0;
}
```

**Follow-up:** O(n) time and O(1) extra space.
