# Basic C Core Coding Challenges

Comprehensive list of 30 embedded C core coding questions and reference solutions.

### Q01: Write a function to swap the endianness of a 32-bit unsigned integer without standard library functions.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t swap_endian32(uint32_t val) {
    return ((val & 0x000000FFU) << 24) |
           ((val & 0x0000FF00U) << 8)  |
           ((val & 0x00FF0000U) >> 8)  |
           ((val & 0xFF000000U) >> 24);
}

int main(void) {
    uint32_t val = 0x12345678;
    printf("Swapped: 0x%08X\n", swap_endian32(val));
    return 0;
}
```

**Key Concept:** Isolate each byte using bitwise masks and shift them into reverse positional order.

---

### Q02: Implement Brian Kernighan's algorithm to count set bits in an N-bit integer in O(K) time.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t count_set_bits(uint32_t n) {
    uint32_t count = 0;
    while (n > 0) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int main(void) {
    printf("Set bits: %u\n", count_set_bits(0x80F00101));
    return 0;
}
```

**Key Concept:** The operation `n & (n - 1)` clears the lowest set bit in each iteration.

---

### Q03: Implement a custom memory move function that safely handles overlapping memory regions.

**Implementation & Explanation:**

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void* custom_memmove(void* dest, const void* src, size_t n) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    if (d == s || n == 0) return dest;
    if (d < s) {
        for (size_t i = 0; i < n; i++) d[i] = s[i];
    } else {
        for (size_t i = n; i > 0; i--) d[i - 1] = s[i - 1];
    }
    return dest;
}

int main(void) {
    char buf[20] = "Hello World";
    custom_memmove(buf + 2, buf, 5);
    printf("Result: %s\n", buf);
    return 0;
}
```

**Key Concept:** Copy backwards when destination > source to prevent overwriting source data prior to reading.

---

### Q04: Implement an integer-to-ASCII conversion function supporting base 10 and base 16.

**Implementation & Explanation:**

```c
#include <stdio.h>
#include <stdint.h>

void reverse(char* str, int len) {
    int i = 0, j = len - 1;
    while (i < j) {
        char tmp = str[i]; str[i++] = str[j]; str[j--] = tmp;
    }
}

char* custom_itoa(int32_t num, char* str, int base) {
    int i = 0, neg = 0;
    if (num == 0) { str[i++] = '0'; str[i] = '\0'; return str; }
    if (num < 0 && base == 10) { neg = 1; num = -num; }
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
        num /= base;
    }
    if (neg) str[i++] = '-';
    str[i] = '\0';
    reverse(str, i);
    return str;
}

int main(void) {
    char buf[32];
    printf("%s\n", custom_itoa(-255, buf, 10));
    return 0;
}
```

**Key Concept:** Extract digits in reverse order using modulo operations, then reverse the final string array.

---

### Q05: Implement a string-to-integer conversion function with overflow detection.

**Implementation & Explanation:**

```c
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

bool custom_atoi(const char* str, int32_t* res) {
    if (!str || !res) return false;
    while (*str == ' ') str++;
    int sign = 1;
    if (*str == '-' || *str == '+') {
        if (*str == '-') sign = -1;
        str++;
    }
    int64_t acc = 0;
    while (*str >= '0' && *str <= '9') {
        acc = acc * 10 + (*str - '0');
        if (sign == 1 && acc > INT32_MAX) return false;
        if (sign == -1 && -acc < INT32_MIN) return false;
        str++;
    }
    *res = (int32_t)(acc * sign);
    return true;
}

int main(void) {
    int32_t val;
    if (custom_atoi(" -1234", &val)) printf("Value: %d\n", val);
    return 0;
}
```

**Key Concept:** Accumulate values into a 64-bit integer to detect standard 32-bit boundary overflow conditions.

---

### Q06: Write a function to reverse the bit order of an 8-bit unsigned integer.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint8_t reverse_bits8(uint8_t val) {
    val = ((val & 0xF0) >> 4) | ((val & 0x0F) << 4);
    val = ((val & 0xCC) >> 2) | ((val & 0x33) << 2);
    val = ((val & 0xAA) >> 1) | ((val & 0x55) << 1);
    return val;
}

int main(void) {
    printf("0x%02X -> 0x%02X\n", 0xF0, reverse_bits8(0xF0));
    return 0;
}
```

**Key Concept:** Use divide-and-conquer bit masks to swap nibbles, pairs, and individual bits in O(1) time.

---

### Q07: Find the Most Significant Bit (MSB) position of a 32-bit unsigned integer.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

int find_msb(uint32_t val) {
    if (val == 0) return -1;
    int pos = 0;
    if (val >= 1U << 16) { val >>= 16; pos += 16; }
    if (val >= 1U << 8)  { val >>= 8;  pos += 8;  }
    if (val >= 1U << 4)  { val >>= 4;  pos += 4;  }
    if (val >= 1U << 2)  { val >>= 2;  pos += 2;  }
    if (val >= 1U << 1)  { pos += 1; }
    return pos;
}

int main(void) {
    printf("MSB of 0x8000: %d\n", find_msb(0x8000));
    return 0;
}
```

**Key Concept:** Binary search bit testing reduces loop overhead when identifying highest set bit position.

---

### Q08: Determine if an integer is a power of 2 using bitwise operators.

**Implementation & Explanation:**

```c
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool is_power_of_two(uint32_t n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int main(void) {
    printf("16 is Power of 2: %s\n", is_power_of_two(16) ? "Yes" : "No");
    return 0;
}
```

**Key Concept:** Powers of two contain exactly one set bit; clearing it results in zero.

---

### Q09: Toggle bits in a 32-bit integer from start bit index `p` for `n` consecutive bits.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t toggle_bit_range(uint32_t val, uint8_t p, uint8_t n) {
    uint32_t mask = ((1U << n) - 1) << p;
    return val ^ mask;
}

int main(void) {
    printf("Toggled: 0x%08X\n", toggle_bit_range(0xFF00, 8, 4));
    return 0;
}
```

**Key Concept:** Construct a contiguous bit mask and apply XOR operation to toggle specified bits.

---

### Q10: Align a memory address to the next power-of-two boundary.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uintptr_t align_up(uintptr_t addr, size_t align) {
    return (addr + (align - 1)) & ~(align - 1);
}

int main(void) {
    printf("Aligned: 0x%ZX\n", align_up(0x1003, 4));
    return 0;
}
```

**Key Concept:** Add alignment offset and clear lower mask bits corresponding to power-of-two boundary.

---

### Q11: Implement an optimized memory copy routine utilizing 32-bit word transfers.

**Implementation & Explanation:**

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void* aligned_memcpy(void* dest, const void* src, size_t n) {
    uint32_t* d32 = (uint32_t*)dest;
    const uint32_t* s32 = (const uint32_t*)src;
    size_t words = n / 4;
    size_t bytes = n % 4;
    while (words--) *d32++ = *s32++;
    uint8_t* d8 = (uint8_t*)d32;
    const uint8_t* s8 = (const uint8_t*)s32;
    while (bytes--) *d8++ = *s8++;
    return dest;
}

int main(void) {
    uint32_t src[2] = {0x11223344, 0x55667788}, dst[2];
    aligned_memcpy(dst, src, sizeof(src));
    printf("Copied word: 0x%08X\n", dst[0]);
    return 0;
}
```

**Key Concept:** Process 4 bytes per machine word to minimize bus access cycles.

---

### Q12: Implement an optimized memset function.

**Implementation & Explanation:**

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void* custom_memset(void* s, int c, size_t n) {
    uint8_t* p = (uint8_t*)s;
    uint32_t pattern = (uint8_t)c;
    pattern |= (pattern << 8) | (pattern << 16) | (pattern << 24);
    while (n >= 4) {
        *(uint32_t*)p = pattern;
        p += 4;
        n -= 4;
    }
    while (n--) *p++ = (uint8_t)c;
    return s;
}

int main(void) {
    uint8_t buf[8];
    custom_memset(buf, 0xAA, sizeof(buf));
    printf("Byte 0: 0x%02X\n", buf[0]);
    return 0;
}
```

**Key Concept:** Replicate byte patterns across 32-bit words for faster memory fills.

---

### Q13: Implement strlen without standard C runtime functions.

**Implementation & Explanation:**

```c
#include <stddef.h>
#include <stdio.h>

size_t custom_strlen(const char* s) {
    const char* p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

int main(void) {
    printf("Length: %zu\n", custom_strlen("Embedded"));
    return 0;
}
```

**Key Concept:** Pointer subtraction provides string length calculation without explicit counter increment.

---

### Q14: Implement custom_strcmp and custom_strncmp functions.

**Implementation & Explanation:**

```c
#include <stdio.h>

int custom_strncmp(const char* s1, const char* s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        s1++; s2++; n--;
    }
    if (n == 0) return 0;
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int main(void) {
    printf("Match: %d\n", custom_strncmp("Test", "Team", 2));
    return 0;
}
```

**Key Concept:** Compare byte-wise unsigned char values until length limit or character mismatch is encountered.

---

### Q15: Implement custom_strncpy that ensures null-termination.

**Implementation & Explanation:**

```c
#include <stddef.h>
#include <stdio.h>

char* safe_strncpy(char* dest, const char* src, size_t n) {
    if (n == 0) return dest;
    size_t i;
    for (i = 0; i < n - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

int main(void) {
    char buf[5];
    safe_strncpy(buf, "EmbeddedC", sizeof(buf));
    printf("Safe String: %s\n", buf);
    return 0;
}
```

**Key Concept:** Always reserve the final index for explicit null-termination to prevent buffer overruns.

---

### Q16: Swap two integer variables in-place without using auxiliary memory.

**Implementation & Explanation:**

```c
#include <stdio.h>

void xor_swap(int* a, int* b) {
    if (a != b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

int main(void) {
    int x = 10, y = 20;
    xor_swap(&x, &y);
    printf("x=%d, y=%d\n", x, y);
    return 0;
}
```

**Key Concept:** XORing properties `(A ^ B) ^ A = B` allow value swapping without temporary variables.

---

### Q17: Find the missing number in an array containing numbers from 1 to N.

**Implementation & Explanation:**

```c
#include <stdio.h>

int find_missing(const int* arr, int n) {
    int xor_all = 0;
    for (int i = 1; i <= n + 1; i++) xor_all ^= i;
    for (int i = 0; i < n; i++) xor_all ^= arr[i];
    return xor_all;
}

int main(void) {
    int data[] = {1, 2, 4, 5};
    printf("Missing: %d\n", find_missing(data, 4));
    return 0;
}
```

**Key Concept:** XORing array items against full range `1..N+1` isolates the single missing element.

---

### Q18: Find a duplicate number in an array using bitwise flags.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

int find_duplicate(const uint8_t* arr, size_t len) {
    uint32_t flag = 0;
    for (size_t i = 0; i < len; i++) {
        if (flag & (1U << arr[i])) return arr[i];
        flag |= (1U << arr[i]);
    }
    return -1;
}

int main(void) {
    uint8_t data[] = {3, 1, 4, 1, 5};
    printf("Duplicate: %d\n", find_duplicate(data, 5));
    return 0;
}
```

**Key Concept:** Bit mask bit-field tracking tracks seen elements using minimal stack space.

---

### Q19: Convert floating point value to Q16.16 fixed-point format and perform multiplication.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

typedef int32_t q16_t;
#define Q16_SHIFT 16
#define TO_Q16(f) ((q16_t)((f) * (1 << Q16_SHIFT)))
#define TO_FLOAT(q) ((float)(q) / (1 << Q16_SHIFT))

q16_t q16_mul(q16_t a, q16_t b) {
    return (q16_t)(((int64_t)a * b) >> Q16_SHIFT);
}

int main(void) {
    q16_t r = q16_mul(TO_Q16(2.5f), TO_Q16(4.0f));
    printf("Result: %.2f\n", TO_FLOAT(r));
    return 0;
}
```

**Key Concept:** Cast operands to 64-bit prior to shifting to prevent fixed-point overflow.

---

### Q20: Compute absolute value of a 32-bit signed integer without branching.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

int32_t branchless_abs(int32_t v) {
    int32_t const mask = v >> 31;
    return (v + mask) ^ mask;
}

int main(void) {
    printf("Abs: %d\n", branchless_abs(-42));
    return 0;
}
```

**Key Concept:** Arithmetic right shift creates sign mask `0x0` or `0xFFFFFFFF` to apply two's complement conditionally.

---

### Q21: Implement 32-bit rotate left (ROL) and rotate right (ROR) operations.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t rol32(uint32_t val, uint8_t shift) {
    return (val << shift) | (val >> (32 - shift));
}

int main(void) {
    printf("ROL: 0x%08X\n", rol32(0x80000001, 1));
    return 0;
}
```

**Key Concept:** Combine left and right shifts to wrap discarded overflow bits into lower positions.

---

### Q22: Extract bitfield value from a 32-bit register given mask and offset.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t extract_field(uint32_t reg, uint32_t mask, uint8_t shift) {
    return (reg & mask) >> shift;
}

int main(void) {
    printf("Field: 0x%X\n", extract_field(0x0000F000, 0x0000F000, 12));
    return 0;
}
```

**Key Concept:** Apply mask to isolate target region then right shift to retrieve zero-indexed field value.

---

### Q23: Write new bitfield value into target field of a register without clearing other bits.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t set_field(uint32_t reg, uint32_t val, uint32_t mask, uint8_t shift) {
    return (reg & ~mask) | ((val << shift) & mask);
}

int main(void) {
    printf("Reg: 0x%08X\n", set_field(0xFFFFFFFF, 0x5, 0x000000F0, 4));
    return 0;
}
```

**Key Concept:** Clear existing bit region using inverted mask, then OR shifting target value.

---

### Q24: Write a C function to determine endianness of processor architecture at runtime.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

bool is_little_endian(void) {
    uint16_t val = 0x0001;
    uint8_t* ptr = (uint8_t*)&val;
    return ptr[0] == 0x01;
}

int main(void) {
    printf("System is: %s\n", is_little_endian() ? "Little-Endian" : "Big-Endian");
    return 0;
}
```

**Key Concept:** Cast integer pointer to byte pointer to inspect lowest physical memory address contents.

---

### Q25: Implement an integer square root algorithm without floating point operations.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t isqrt(uint32_t n) {
    uint32_t res = 0, bit = 1U << 30;
    while (bit > n) bit >>= 2;
    while (bit != 0) {
        if (n >= res + bit) {
            n -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }
    return res;
}

int main(void) {
    printf("sqrt(25): %u\n", isqrt(25));
    return 0;
}
```

**Key Concept:** Digit-by-digit square root computation using shift operations avoids library math calls.

---

### Q26: Compute parity bit (even parity) of an 8-bit unsigned byte.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

bool get_parity8(uint8_t val) {
    val ^= val >> 4;
    val ^= val >> 2;
    val ^= val >> 1;
    return val & 1;
}

int main(void) {
    printf("Parity of 0x03: %d\n", get_parity8(0x03));
    return 0;
}
```

**Key Concept:** Fold bit halves using XOR until parity state propagates to the least significant bit.

---

### Q27: Reverse a null-terminated string in-place without dynamic allocations.

**Implementation & Explanation:**

```c
#include <stdio.h>
#include <string.h>

void reverse_string(char* str) {
    if (!str) return;
    int i = 0, j = strlen(str) - 1;
    while (i < j) {
        char tmp = str[i]; str[i++] = str[j]; str[j--] = tmp;
    }
}

int main(void) {
    char msg[] = "MCU";
    reverse_string(msg);
    printf("Reversed: %s\n", msg);
    return 0;
}
```

**Key Concept:** Swap character pairs from array bounds inward until pointers cross.

---

### Q28: Determine if two signed integers have opposite signs without branching.

**Implementation & Explanation:**

```c
#include <stdbool.h>
#include <stdio.h>

bool has_opposite_signs(int x, int y) {
    return (x ^ y) < 0;
}

int main(void) {
    printf("Opposite: %s\n", has_opposite_signs(10, -5) ? "Yes" : "No");
    return 0;
}
```

**Key Concept:** XORing values with differing sign bits sets the MSB sign bit to 1 (negative value).

---

### Q29: Implement custom_strchr to locate character in string.

**Implementation & Explanation:**

```c
#include <stdio.h>

char* custom_strchr(const char* s, int c) {
    while (*s != (char)c) {
        if (*s == '\0') return NULL;
        s++;
    }
    return (char*)s;
}

int main(void) {
    const char* str = "MCU Driver";
    printf("Found at: %s\n", custom_strchr(str, 'D'));
    return 0;
}
```

**Key Concept:** Sequential scan returns memory address pointer upon finding matching byte value.

---

### Q30: Safely read an unaligned 16-bit integer from a byte array across word boundaries.

**Implementation & Explanation:**

```c
#include <stdint.h>
#include <stdio.h>

uint16_t read_u16_unaligned(const uint8_t* buf) {
    return (uint16_t)buf[0] | ((uint16_t)buf[1] << 8);
}

int main(void) {
    uint8_t stream[] = {0x00, 0xCD, 0xAB};
    printf("Unaligned Val: 0x%04X\n", read_u16_unaligned(&stream[1]));
    return 0;
}
```

**Key Concept:** Assemble multi-byte integers using explicit byte shifts to avoid target unaligned memory faults.

---

# C Programming Practice & Interview Questions

---

## 1. Mathematical Algorithms & Number Theory

### 1. Check Armstrong Number
Checks if an integer is equal to the sum of its own digits each raised to the power of the number of digits.

```c
#include <stdio.h>

int main() {
    int num, originalNum, remainder, result = 0, count = 0;

    printf("Enter an integer: ");
    scanf("%d", &num);

    originalNum = num;

    // Step 1: Find the total number of digits
    while (originalNum != 0) {
        originalNum /= 10;
        count++;
    }

    originalNum = num;

    // Step 2: Calculate sum of each digit raised to the power of 'count'
    while (originalNum != 0) {
        remainder = originalNum % 10;

        // Multiply the digit by itself 'count' times manually
        int power = 1;
        for (int i = 0; i < count; i++) {
            power *= remainder;
        }

        result += power;
        originalNum /= 10;
    }

    // Step 3: Check if sum equals the original number
    if (result == num)
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);

    return 0;
}
```
### 2. Check Prime Number
Determines whether a given positive integer is a prime number.

```c
#include <stdio.h>

int main() {
    int num, isPrime = 1;

    printf("Enter a positive integer: ");
    scanf("%d", &num);

    // 0 and 1 are not prime numbers
    if (num <= 1) {
        isPrime = 0;
    } else {
        // Check for factors from 2 up to num / 2
        for (int i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                isPrime = 0; // Found a factor, so it's not prime
                break;
            }
        }
    }

    if (isPrime)
        printf("%d is a prime number.\n", num);
    else
        printf("%d is not a prime number.\n", num);

    return 0;
}
```
## 3. String Manipulation & Character Processing

### 3. Reverse String and Reverse Sentence Words
Includes helper functions to reverse a string in-place and reverse individual words in a sentence.

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void revstr(char *str) {
    int l, temp;
    for (l = 0; str[l]; l++);

    for (int i = 0; i < l / 2; i++) {
        temp = str[i];
        str[i] = str[l - 1 - i];
        str[l - 1 - i] = temp;
    }
    printf("rev: %s\n", str);
}

void rev_sen(char *str) {
    int l;
    for (l = 0; str[l]; l++);

    revstr(str);

    int start = 0;
    for (int i = 0; i <= l; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            int end = i - 1;
            while (start < end) {
                int t = str[start];
                str[start] = str[end];
                str[end] = t;
                start++;
                end--;
            }
            start = i + 1;
        }
    }
    printf("rev sen: %s\n", str);
}

int main() {
    char s[] = "Hello World";
    rev_sen(s);
    return 0;
}
```

### 4. Find Repeated Letters in a String
Tracks occurrences of characters using a frequency table and prints duplicate characters.

```c
#include <stdio.h>
#include <stdint.h>

void find_repeated_letters(char *str) {
    uint8_t count[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            count[(uint8_t)str[i]]++;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] > 1) {
            printf("%c ", i);
        }
    }
    printf("\n");
}
```

## 4. Bit Manipulation & Byte-Level Operations

### 5. Reverse Hexadecimal Digits
Reverses hexadecimal nibbles for a 32-bit integer.

```c
#include <stdint.h>

uint32_t reverse_hex(uint32_t num) {
    uint32_t rev = 0;

    while (num) {
        rev = (rev << 4) | (num & 0xF);
        num >>= 4;
    }

    return rev;
}
```

### 6. Bit Reversal Operations (8-bit, 16-bit, 32-bit, and Generic)
Optimized bitwise techniques for reversing bits across various integer bit widths.

```c
#include <stdint.h>

// 8-bit Bit Reversal
uint8_t reverseBits(uint8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

// 16-bit Bit Reversal
uint16_t reverseBits16(uint16_t x) {
    x = (x & 0xFF00) >> 8 | (x & 0x00FF) << 8; // Swap bytes
    x = (x & 0xF0F0) >> 4 | (x & 0x0F0F) << 4; // Swap nibbles
    x = (x & 0xCCCC) >> 2 | (x & 0x3333) << 2; // Swap pairs
    x = (x & 0xAAAA) >> 1 | (x & 0x5555) << 1; // Swap bits
    return x;
}

// 32-bit Bit Reversal
uint32_t reverseBits32(uint32_t x) {
    x = (x & 0xFFFF0000) >> 16 | (x & 0x0000FFFF) << 16;
    x = (x & 0xFF00FF00) >> 8  | (x & 0x00FF00FF) << 8;
    x = (x & 0xF0F0F0F0) >> 4  | (x & 0x0F0F0F0F) << 4;
    x = (x & 0xCCCCCCCC) >> 2  | (x & 0x33333333) << 2;
    x = (x & 0xAAAAAAAA) >> 1  | (x & 0x55555555) << 1;
    return x;
}

// Generic N-bit Bit Reversal
uint64_t reverseBitsGeneric(uint64_t num, uint8_t num_bits) {
    uint64_t rev = 0;
    for (uint8_t i = 0; i < num_bits; i++) {
        rev = (rev << 1) | (num & 1);
        num >>= 1;
    }
    return rev;
}
```

### 7. Byte Splitting, Combining & Nibble Swapping
Macros and functions for manipulating bytes, nibbles, and endianness conversions.

```c
#include <stdio.h>
#include <stdint.h>

// Macros
#define GET_HIGH_8(num)        ((uint8_t)(((uint16_t)(num) >> 8) & 0xFF))
#define GET_LOW_8(num)         ((uint8_t)((uint16_t)(num) & 0xFF))
#define TO_16_BITS(high, low)  ((uint16_t)(((uint16_t)(uint8_t)(high) << 8) | (uint8_t)(low)))

void to_8_bits(uint16_t num) {
    uint8_t high = (num >> 8) & 0xFF;
    uint8_t low = num & 0xFF;
    printf("high: %u, low = %u\n", high, low);
}

void to_16_bits(uint8_t high, uint8_t low) {
    uint16_t n = (uint16_t)high << 8 | low;
    printf("num: %u\n", n);
}

// Nibble Swaps
uint8_t swap_nibbles_8(uint8_t val) {
    return (((val & 0x0F) << 4) | ((val & 0xF0) >> 4));
}

uint16_t swap_nibbles_16(uint16_t val) {
    return ((val & 0x0F0F) << 4) | ((val & 0xF0F0) >> 4);
}

uint32_t swap_nibbles_32(uint32_t val) {
    return ((val & 0x0F0F0F0F) << 4) | ((val & 0xF0F0F0F0) >> 4);
}

// Endianness / Byte Swaps
uint16_t swap_num_16(uint16_t val) {
    return ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
}

uint32_t swap_num_32(uint32_t val) {
    return ((val & 0x000000FF) << 24) |
           ((val & 0x0000FF00) << 8)  |
           ((val & 0x00FF0000) >> 8)  |
           ((val & 0xFF000000) >> 24);
}
```

## 5. Array Operations, Sorting & Searching

### 8. Array Rotations, Insertion, and Deletion
Functions to manipulate arrays including left/right shifts, directional position shifts, element insertion, and element deletion.

```c
#include <stdio.h>
#include <stdint.h>

#define LEFT  1
#define RIGHT 0

void print_arr(uint8_t a[], int n) {
    for (uint8_t i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void rotate_left(uint8_t a[], int n) {
    uint8_t temp = a[0];
    for (int i = 0; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    a[n - 1] = temp;
    print_arr(a, n);
}

void rotate_right(uint8_t a[], int n) {
    uint8_t temp = a[n - 1];
    for (uint8_t i = n - 1; i > 0; i--) {
        a[i] = a[i - 1];
    }
    a[0] = temp;
    print_arr(a, n);
}

void rotate_pos(uint8_t a[], uint8_t n, uint8_t dir, uint8_t shift_cnt) {
    if (n <= 1 || shift_cnt <= 0) {
        return;
    }

    shift_cnt = shift_cnt % n;
    while (shift_cnt > 0) {
        if (dir == LEFT) {
            uint8_t temp = a[0];
            for (uint8_t i = 0; i < n - 1; i++) {
                a[i] = a[i + 1];
            }
            a[n - 1] = temp;
        } else if (dir == RIGHT) {
            uint8_t temp = a[n - 1];
            for (uint8_t i = n - 1; i > 0; i--) {
                a[i] = a[i - 1];
            }
            a[0] = temp;
        }
        shift_cnt--;
    }
    print_arr(a, n);
}

uint8_t insert_at_pos(uint8_t a[], uint8_t n, uint8_t num, uint8_t pos) {
    if (pos > n) {
        printf("Invalid position!\n");
        return n;
    }
    for (uint8_t i = n; i > pos; i--) {
        a[i] = a[i - 1];
    }
    a[pos] = num;
    return n + 1;
}

uint8_t remove_at_pos(uint8_t a[], uint8_t n, uint8_t pos) {
    if (pos >= n) {
        printf("Invalid position!\n");
        return n;
    }
    for (uint8_t i = pos; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    return n - 1;
}

int main() {
    uint8_t a[10] = {1, 2, 3, 4, 5};
    uint8_t n = 5;

    rotate_left(a, n);
    rotate_left(a, n);
    rotate_right(a, n);
    rotate_right(a, n);

    rotate_pos(a, n, LEFT, 3);

    n = insert_at_pos(a, n, 99, 2);
    print_arr(a, n);

    n = remove_at_pos(a, n, 1);
    print_arr(a, n);

    return 0;
}
### 9. Sorting, Searching & Deduplication
```

```c
#include <stdio.h>
#include <stdint.h>

void print_arr(uint8_t a[], int n);

void bubble_sort(uint8_t a[], uint8_t n) {
    for (uint8_t i = 0; i < n; i++) {
        for (uint8_t k = 0; k < n - 1 - i; k++) {
            if (a[k] >= a[k + 1]) {
                uint8_t temp = a[k];
                a[k] = a[k + 1];
                a[k + 1] = temp;
            }
        }
    }
    print_arr(a, n);
}

int linear_search(uint8_t a[], uint8_t n, uint8_t target) {
    for (uint8_t i = 0; i < n; i++) {
        if (a[i] == target) return i;
    }
    return -1;
}

int binary_search(uint8_t a[], uint8_t n, uint8_t target) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (a[mid] == target) 
            return mid;
        if (a[mid] < target) 
            low = mid + 1;
        else 
            high = mid - 1;
    }
    return -1;
}

int remove_duplicates(int arr[], int size) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        int k;
        for (k = 0; k < count; k++) {
            if (arr[i] == arr[k]) {
                break;
            }
        }
        if (k == count) {
            arr[count] = arr[i];
            count++;
        }
    }
    return count;
}
## 6. Linked List Data Structures

### 10. Singly Linked List (Insertion, Deletion, Positional Operations & Traversals)
Demonstrates both Return-based (Pass by Value) and Double Pointer (Pass by Reference) APIs.

```c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int head;
    struct node *next;
};

// 1. Return-based Insert at Start
struct node *insert_start(struct node *current_head, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(*new_node));
    new_node->head = data;
    new_node->next = current_head;
    return new_node;
}

// 2. Return-based Insert at End
struct node *insert_end(struct node *curr_head, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(*new_node));
    new_node->head = data;
    new_node->next = NULL;
    if (curr_head == NULL) return new_node;

    struct node *temp_node = curr_head;
    while (temp_node->next != NULL) {
        temp_node = temp_node->next;
    }
    temp_node->next = new_node;
    return curr_head;
}

// 3. Double Pointer Insert at Start
void insert_at_start(struct node **curr_head, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(*new_node));
    new_node->head = data;
    new_node->next = *curr_head;
    *curr_head = new_node;
}

// 4. Double Pointer Insert at End
void insert_at_end(struct node **curr_head, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(*new_node));
    new_node->head = data;
    new_node->next = NULL;
    if (*curr_head == NULL) {
        *curr_head = new_node;
        return;
    }
    struct node *temp_node = *curr_head;
    while (temp_node->next != NULL) {
        temp_node = temp_node->next;
    }
    temp_node->next = new_node;
}

// 5. Return-based Delete Head
struct node *delete_start(struct node *current_head) {
    if (current_head == NULL) return NULL;
    struct node *temp = current_head;
    current_head = current_head->next;
    free(temp);
    return current_head;
}

// 6. Double Pointer Delete Head
void delete_at_start(struct node **curr_head) {
    if (curr_head == NULL || *curr_head == NULL) return;
    struct node *temp = *curr_head;
    *curr_head = (*curr_head)->next;
    free(temp);
}

// 7. Insert at Position (Return-based)
struct node *insert_pos(struct node *current_head, int data, int pos) {
    if (pos == 1) {
        struct node *new_node = (struct node*)malloc(sizeof(*new_node));
        new_node->head = data;
        new_node->next = current_head;
        return new_node;
    }

    struct node *temp = current_head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of bounds\n");
        return current_head;
    }

    struct node *new_node = (struct node*)malloc(sizeof(*new_node));
    new_node->head = data;
    new_node->next = temp->next;
    temp->next = new_node;

    return current_head;
}

// 8. Insert at Position (Double Pointer)
void insert_at_pos(struct node **curr_head, int data, int pos) {
    if (pos == 1) {
        struct node *new_node = (struct node*)malloc(sizeof(*new_node));
        new_node->head = data;
        new_node->next = *curr_head;
        *curr_head = new_node;
        return;
    }

    struct node *temp = *curr_head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    struct node *new_node = (struct node*)malloc(sizeof(*new_node));
    new_node->head = data;
    new_node->next = temp->next;
    temp->next = new_node;
}

// 9. Delete at Position (Return-based)
struct node *del_pos(struct node *current_head, int pos) {
    if (current_head == NULL) return NULL;

    if (pos == 1) {
        struct node *temp = current_head;
        current_head = current_head->next;
        free(temp);
        return current_head;
    }

    struct node *temp = current_head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return current_head;
    }

    struct node *node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    free(node_to_delete);

    return current_head;
}

// 10. Delete at Position (Double Pointer)
void del_at_pos(struct node **curr_head, int pos) {
    if (curr_head == NULL || *curr_head == NULL) return;

    if (pos == 1) {
        struct node *temp = *curr_head;
        *curr_head = (*curr_head)->next;
        free(temp);
        return;
    }

    struct node *temp = *curr_head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    struct node *node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    free(node_to_delete);
}

// Iterative Printing
void print_list(struct node *head) {
    struct node *new_node = head;
    while (new_node != NULL) {
        printf("%d -> ", new_node->head);
        new_node = new_node->next;
    }
    printf("NULL\n");
}

// Recursive Printing
void iterate_list_recursive(struct node *head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d -> ", head->head);
    iterate_list_recursive(head->next);
}

int main() {
    struct node *new_node = NULL;

    new_node = insert_start(new_node, 5);
    new_node = insert_start(new_node, 15);
    new_node = insert_start(new_node, 25);
    print_list(new_node);

    insert_at_start(&new_node, 30);
    print_list(new_node);

    new_node = delete_start(new_node);
    new_node = delete_start(new_node);
    print_list(new_node);

    delete_at_start(&new_node);
    print_list(new_node);

    new_node = insert_end(new_node, 31);
    print_list(new_node);

    insert_at_end(&new_node, 32);
    print_list(new_node);

    return 0;
}

```

### 11. In-Place Linked List Reversal
Reverses a singly linked list in-place using iterative three-pointer technique.

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *reverseList(struct Node *head) {
    struct Node *prev_node = NULL;
    struct Node *curr_node = head;

    while (curr_node != NULL) {
        struct Node *next_node = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next_node;
    }

    return prev_node;
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

void printList(struct Node *head) {
    struct Node *curr_node = head;
    while (curr_node != NULL) {
        printf("%d -> ", curr_node->data);
        curr_node = curr_node->next;
    }
    printf("NULL\n");
}

void freeList(struct Node *head) {
    struct Node *curr_node = head;
    while (curr_node != NULL) {
        struct Node *next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
    }
}

int main(void) {
    struct Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Original List:\n");
    printList(head);

    head = reverseList(head);

    printf("\nReversed List:\n");
    printList(head);

    freeList(head);

    return 0;
}
```