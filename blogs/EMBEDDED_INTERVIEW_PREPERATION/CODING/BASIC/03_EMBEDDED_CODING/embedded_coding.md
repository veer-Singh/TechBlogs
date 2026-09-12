# Basic Embedded Coding Questions

## 1. Set/clear/toggle/test a bit

```c
#define BIT(n) (1UL << (n))

reg |= BIT(5);        /* set */
reg &= ~BIT(5);       /* clear */
reg ^= BIT(5);        /* toggle */
if ((reg & BIT(5)) != 0U) { /* test */ }
```

## 2. Safe register field update

```c
reg = (reg & ~FIELD_MASK) | ((value << FIELD_SHIFT) & FIELD_MASK);
```

Explain why clearing the old field before inserting the new value matters.

## 3. Power-of-two check

```c
int is_power_of_two(uint32_t x)
{
    return x != 0U && (x & (x - 1U)) == 0U;
}
```

## 4. Find the missing number from `0..n`

Use the XOR property `a ^ a = 0` and `a ^ 0 = a`, or an arithmetic formulation with overflow considerations. XOR avoids sum overflow from the values themselves.

## 5. `memset` vs `memcpy`

`memset` writes the same byte value across a byte range. `memcpy` copies bytes from one region to another. Neither operation understands C++ object lifetimes or protocol field semantics; overlap requires `memmove` rather than `memcpy`.

## 6. Poll a hardware bit with timeout

```c
bool wait_ready(volatile uint32_t *reg, uint32_t mask, uint32_t limit)
{
    while (limit-- != 0U) {
        if ((*reg & mask) != 0U) {
            return true;
        }
    }
    return false;
}
```

For production code, use a real time base when the timeout requirement is temporal rather than iteration-based.

## 7. Debounce a button

A robust solution can combine sampling with a state machine: RAW_LOW/RAW_HIGH -> candidate state -> stable state after a configured dwell time. Avoid blocking delays in the main control path.

## References

- https://en.cppreference.com/w/c
- https://developer.arm.com/documentation
