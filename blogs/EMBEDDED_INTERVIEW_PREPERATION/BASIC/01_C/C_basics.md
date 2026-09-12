# C Interview Questions

## 1. Why is `volatile` used in embedded C?

`volatile` tells the compiler that a value may change outside the current code flow, so each access must be treated as an observable memory access. Typical examples are memory-mapped registers, variables modified by an ISR, and variables updated by hardware or DMA.

```c
volatile uint32_t *status = (volatile uint32_t *)STATUS_REG;
while ((*status & READY_BIT) == 0U) {
}
```

`volatile` does not make an operation atomic, does not provide mutual exclusion, and is not a replacement for a mutex or memory barrier.

## 2. `const` vs `volatile`?

`const` restricts modification through that expression; `volatile` controls how the compiler may optimize accesses.

A hardware status register is commonly both:

```c
volatile const uint32_t status_reg;
```

The exact declaration used for a real register depends on the device header and register access model.

## 3. Pointer vs array?

An array is an object containing a fixed number of elements; a pointer is an object that stores an address. In many expressions, an array decays to a pointer to its first element, but the two types are not interchangeable.

```c
int a[10];
int *p = a;
```

`sizeof(a)` gives the size of all 10 integers, while `sizeof(p)` gives the pointer size.

## 4. What is pointer arithmetic?

For a pointer `p` to an element type `T`, `p + 1` advances by `sizeof(T)` bytes. This is why array indexing works as `*(p + i)`.

## 5. What is a function pointer and why is it useful in embedded systems?

A function pointer stores the address of a function. It is widely used for callbacks, driver abstraction, interrupt dispatch, state handlers, and configurable operations.

```c
typedef void (*callback_t)(uint8_t event);

void register_callback(callback_t cb);
```

## 6. Macro vs `const` vs `enum`?

A macro is preprocessor substitution. `const` creates a typed read-only object. An `enum` defines named integer constants. Prefer typed language constructs where practical because they provide better type checking and debugging information.

## 7. What does `static` mean in C?

At file scope, `static` gives internal linkage, so the symbol is private to that translation unit. Inside a function, a `static` local retains its value between calls. For an embedded driver, file-scope `static` is useful for private state.

## 8. What is the difference between stack and heap?

The stack is normally used for automatic storage such as local variables and call frames. The heap is used for dynamic allocation. In embedded systems, uncontrolled dynamic allocation can cause fragmentation, nondeterministic timing, and failure after long runtimes, so static allocation or bounded memory pools are often preferred.

## 9. What is undefined behavior?

Undefined behavior means the C language specification imposes no requirements on the result. Examples include signed integer overflow, out-of-bounds access, use-after-free, and invalid shifts. Embedded compilers may optimize aggressively around UB, so code that "works on the board" can still be incorrect.

## 10. What is endianness?

Endianness describes byte order for multi-byte values in memory. Little-endian stores the least-significant byte at the lowest address; big-endian stores the most-significant byte first. Protocols define their own byte order, so never assume CPU endianness equals wire format.

## 11. Why use fixed-width integer types?

`uint8_t`, `uint16_t`, `uint32_t`, and `int32_t` express the intended width when the implementation provides them. This is especially useful for register fields, packet formats, and binary protocols.

## 12. What makes code reentrant?

A function is reentrant if it can safely be interrupted and called again, or invoked concurrently, without corrupting shared state. Avoid hidden mutable global state, protect shared resources appropriately, and be especially careful about functions called from ISRs.

### Quick Revision

- `volatile` = compiler-visible external changes; not synchronization.
- `static` = lifetime and linkage control.
- `const` = prevents modification through the declared access path.
- Function pointers = callback and dispatch mechanism.
- Undefined behavior = never rely on the observed output.

---

# C Pointers Interview Questions & Answers

## 1. What is a pointer in C?

A pointer is a variable that stores the memory address of another object.

```c
int a = 10;
int *ptr = &a;
```

- `ptr` stores the address of `a`.
- `*ptr` accesses the value stored at that address.
- `&` is the address-of operator.
- `*` is the dereference operator.

## 2. Why are pointers important in embedded systems?

Pointers are heavily used in embedded systems for:

- Direct hardware register access
- Efficient memory handling
- Peripheral communication
- Buffer manipulation
- Interrupt and callback handling
- Passing data efficiently to functions

Example:

```c
#define GPIO_REG (*(volatile unsigned int *)0x40021018)
```

This gives access to a memory-mapped hardware register.

## 3. Difference between `ptr` and `*ptr`?

```c
int x = 5;
int *ptr = &x;
```

| Expression | Meaning |
| --- | --- |
| `ptr` | Address stored in the pointer |
| `*ptr` | Value at that address |

## 4. What is pointer arithmetic?

Pointer arithmetic means performing operations such as incrementing, decrementing, or subtracting pointers.

```c
int arr[3] = {10, 20, 30};
int *ptr = arr;

ptr++;
```

Now `ptr` points to `arr[1]`.

The increment is scaled by the pointed-to type. If `int` is 4 bytes, `ptr + 1` advances by 4 bytes.

## 5. Can we add two pointers?

No. Adding two pointers is not defined by standard C.

Invalid:

```c
ptr1 + ptr2;
```

Commonly valid pointer operations include:

- Increment/decrement
- Adding or subtracting an integer
- Subtracting two pointers that point into the same array

## 6. What is pointer subtraction?

Pointer subtraction gives the number of elements between two pointers into the same array.

```c
int arr[5];
int *p1 = &arr[1];
int *p2 = &arr[4];

printf("%td", p2 - p1);
```

Output:

```text
3
```

## 7. What is a pointer to pointer?

A pointer to pointer stores the address of another pointer.

```c
int x = 10;
int *p = &x;
int **pp = &p;
```

- `p` → address of `x`
- `*p` → value of `x`
- `pp` → address of `p`
- `*pp` → value stored in `p`, which is the address of `x`
- `**pp` → value of `x`

## 8. Where are double pointers used?

Double pointers are commonly used for:

- Modifying a pointer inside a function
- Dynamic memory allocation
- 2D pointer-based data structures
- Linked data structures
- Arrays of pointers

Example:

```c
void allocate(int **ptr)
{
    *ptr = malloc(sizeof(int));
}
```

## 9. What is a function pointer?

A function pointer stores the address of a function.

Syntax:

```c
return_type (*ptr_name)(arguments);
```

Example:

```c
int add(int a, int b)
{
    return a + b;
}

int (*fp)(int, int);
fp = add;

printf("%d", fp(2, 3));
```

Output:

```text
5
```

## 10. Why are function pointers used in embedded systems?

Common uses include:

- Callback registration
- Interrupt and event handlers
- Driver abstraction
- State machines
- Event handling
- Table-driven logic

Example:

```c
void UART_Callback(void)
{
    printf("Data received");
}
```

A driver can store the callback address and invoke it when the event occurs.

## 11. What is a void pointer?

A `void *` is a generic object pointer that can hold the address of an object of any complete object type.

```c
int x = 10;
void *ptr = &x;
```

A `void *` must be converted to the appropriate type before dereferencing:

```c
printf("%d", *(int *)ptr);
```

## 12. Why is a void pointer called a generic pointer?

Because an object pointer can be converted to and from `void *`, allowing generic functions to work with different object types.

For example, a `void *` can point to:

- `int`
- `char`
- `float`
- `struct`

The programmer must still know the correct original type before dereferencing.

## 13. Can pointer arithmetic be done on a void pointer?

Standard C does not define arithmetic on `void *` because `void` has no size.

Some compilers support `void *` arithmetic as a compiler extension, but portable C code should not rely on it.

## 14. What is a dangling pointer?

A dangling pointer is a pointer whose referenced object no longer exists or whose allocated storage has been released.

Example:

```c
int *ptr = malloc(sizeof(int));
free(ptr);
```

After `free(ptr)`, `ptr` still contains the old address, but that storage is no longer owned by the allocation.

Dereferencing it is undefined behavior.

A common practice is:

```c
free(ptr);
ptr = NULL;
```

## 15. What is an uninitialized pointer?

An uninitialized pointer has an indeterminate value because it has not been initialized.

```c
int *ptr;
*ptr = 10;
```

Dereferencing such a pointer can cause undefined behavior.

## 16. What is a wild pointer?

A wild pointer is an informal term for a pointer that has not been initialized to a valid object address.

```c
int *ptr;
```

Using it without assigning a valid target is unsafe.

## 17. What is invalid dereference?

Invalid dereference means accessing memory through a pointer that does not point to a valid object for that access.

Example:

```c
int *ptr = NULL;
printf("%d", *ptr);
```

Dereferencing a null pointer is undefined behavior. On many systems it results in a fault, but the C language does not require a specific symptom.

## 18. Difference between a NULL pointer and a wild pointer?

| Type | Meaning |
| --- | --- |
| Null pointer | Explicitly represents a null pointer value |
| Wild pointer | Informal term for an uninitialized or invalid pointer |

A null pointer is not a valid pointer to an object.

## 19. What happens when dereferencing a NULL pointer?

Dereferencing a null pointer causes undefined behavior.

On many embedded systems it can trigger a HardFault, BusFault, MemManage fault, or another exception depending on the MCU and memory configuration.

## 20. What is a memory leak?

A memory leak occurs when dynamically allocated memory is no longer reachable and has not been released.

```c
int *ptr = malloc(sizeof(int));
```

If the allocation is lost without calling `free(ptr)`, the allocated memory remains unavailable for reuse.

In embedded systems, dynamic allocation is often restricted or carefully controlled because memory is limited and long-running systems must avoid fragmentation and leaks.

## 21. Difference between array and pointer?

| Array | Pointer |
| --- | --- |
| Reserves storage for its elements | Stores an address |
| Array name is not a modifiable pointer | Pointer can normally be reassigned |
| `sizeof(array)` gives the total array size | `sizeof(pointer)` gives the pointer size |
| Number of elements is fixed for a fixed-size array | Pointer itself does not define the size of the referenced object |

Example:

```c
int arr[5];
int *ptr = arr;
```

## 22. What is `NULL`?

`NULL` is a macro representing a null pointer constant.

Example:

```c
int *ptr = NULL;
```

It is commonly used to indicate that a pointer currently does not point to an object.

## 23. What is the size of a pointer?

Pointer size depends on the target architecture and ABI.

Typical examples:

| Architecture | Typical pointer size |
| --- | --- |
| 32-bit | 4 bytes |
| 64-bit | 8 bytes |

Do not assume these sizes universally; the target compiler and ABI determine the actual representation.

## 24. Explain pointer increment internally.

For a pointer `ptr` of type `T *`:

```c
ptr++;
```

This moves it to the next `T` object.

Conceptually, the address advances by:

```text
sizeof(T)
```

For example, if `int` is 4 bytes, incrementing an `int *` advances by 4 bytes.

## 25. What are the advantages of pointers?

Pointers provide:

- Efficient access to existing objects
- Array and buffer traversal
- Passing data to functions without copying the object
- Dynamic memory management
- Hardware register access
- Callback and function-pointer mechanisms
- Data structure implementation

### Quick Basic Revision

- `&x` → address of `x`
- `*p` → value or object accessed through `p`
- `p + 1` → next object of the pointed-to type
- `NULL` → null pointer value
- Wild pointer → uninitialized or invalid pointer
- Dangling pointer → pointer to an object or storage that is no longer valid
- `void *` → generic object pointer
- `T **` → pointer to a pointer

---

# Memory Layout Interview Questions & Answers

## 1. What is memory layout in C?

Memory layout refers to how a program is organized in memory during execution.

Main sections:

- Text segment
- Data segment
- BSS segment
- Heap
- Stack

## 2. Explain the basic memory layout of a C program.

Typical memory layout:

```text
-------------------
|   Stack         |
-------------------
|   Heap          |
-------------------
|   BSS           |
-------------------
|   Data          |
-------------------
|   Text/Code     |
-------------------
```

- Stack grows downward.
- Heap grows upward.

## 3. What is the text segment (code segment)?

Stores:

- Executable instructions
- Program code
- Read-only constants sometimes

Example:

```c
int add(int a, int b)
{
    return a + b;
}
```

Function code is stored in the text segment.

### Features:

- Read-only
- Fixed size
- Sometimes shared among processes

## 4. What is the data segment?

Stores initialized global and static variables.

Example:

```c
int global = 10;
static int s = 20;
```

Both are stored in the data segment.

## 5. What is the BSS segment?

BSS stands for Block Started by Symbol.

Stores:

- Uninitialized global variables
- Uninitialized static variables

Example:

```c
int global;
static int s;
```

Stored in BSS.

### Important:

The system initializes them to zero automatically.

## 6. Difference between the data segment and BSS?

| Data segment | BSS segment |
| --- | --- |
| Initialized globals and statics | Uninitialized globals and statics |
| Occupies space in the executable image | Does not occupy actual initialized data space |

Example:

```c
int x = 5;  // data segment
int y;      // BSS segment
```

## 7. What is stack memory?

Used for:

- Local variables
- Function calls
- Function parameters
- Return addresses

Example:

```c
void fun(void)
{
    int x = 10;
}
```

`x` is stored in the stack.

## 8. What is heap memory?

Used for dynamic memory allocation.

Functions:

- `malloc()`
- `calloc()`
- `realloc()`
- `free()`

Example:

```c
int *ptr = malloc(sizeof(int));
```

Memory allocated in the heap.

## 9. Difference between stack and heap?

| Stack | Heap |
| --- | --- |
| Automatic allocation | Manual allocation |
| Faster | Slower |
| Limited size | Larger size |
| Managed by compiler | Managed by programmer |
| Stores local variables | Stores dynamic memory |

## 10. Why is the stack faster than the heap?

The stack uses simple push and pop operations.

The heap requires:

- Memory searching
- Fragmentation handling
- Allocation algorithms

## 11. What is stack overflow?

Occurs when stack memory exceeds its limit.

Reasons:

- Deep recursion
- Large local arrays
- Infinite recursive calls

Example:

```c
void fun(void)
{
    fun();
}
```

This can cause stack overflow.

## 12. What is heap fragmentation?

Small unused memory blocks are scattered in the heap.

Results:

- Memory wastage
- Allocation failure

This is very important in embedded systems.

## 13. Why is dynamic memory allocation risky in embedded systems?

Because it can cause:

- Fragmentation
- Memory leaks
- Non-deterministic behavior
- Allocation failure

Hence many embedded systems avoid `malloc()` and `free()`.

## 14. What is a memory leak?

Allocated heap memory is not freed.

Example:

```c
int *ptr = malloc(sizeof(int));
```

If `free(ptr)` is not called, the memory remains unavailable for reuse.

## 15. What is memory lifetime?

It is the duration for which memory remains valid.

| Variable type   | Lifetime           |
| --------------- |--------------------|
| Local variable  | Function execution |
| Global variable | Entire program     |
| Static variable | Entire program     |
| Heap memory     | Until `free()`     |

## 16. What is a local variable?

A variable declared inside a function.

Example:

```c
void fun(void)
{
    int x = 5;
}
```

Stored in the stack.

## 17. What is a global variable?

Declared outside all functions.

Example:

```c
int g = 10;
```

Accessible throughout the program.

Stored in:

- Data segment or
- BSS segment

## 18. What is a static variable?

A static variable retains its value between function calls.

Example:

```c
void fun(void)
{
    static int count = 0;
    count++;
}
```

### Important:

- Initialized only once
- Stored in data or BSS
- Lifetime = entire program

## 19. Difference between static and global variable?

| Static variable | Global variable |
| --- | --- |
| Scope can be limited | Accessible globally |
| Lifetime = entire program | Lifetime = entire program |
| Internal linkage possible | External linkage |

## 20. What is the scope of a local variable?

Accessible only inside the function or block where it is declared.

## 21. What happens to local variables after a function returns?

They are destroyed automatically because the stack frame is removed.

## 22. Why is returning the address of a local variable dangerous?

Because the local variable is destroyed after the function exits.

Wrong:

```c
int *fun(void)
{
    int x = 10;
    return &x;
}
```

This creates a dangling pointer.

## 23. Where are string literals stored?

Usually in:

- Read-only memory
- Text/code segment

Example:

```c
char *str = "Hello";
```

## 24. Difference between `char str[]` and `char *str`?

```c
char str[] = "Hello";
```

This creates an array.

```c
char *str = "Hello";
```

This creates a pointer to a string literal.

## 25. Explain function call memory behavior.

When a function is called:

- A stack frame is created
- Parameters are pushed
- Local variables are allocated
- The return address is stored

After return:

- The stack frame is removed

## 26. What is a stack frame?

A memory block created for a function call.

Contains:

- Local variables
- Parameters
- Return address
- Saved registers

## 27. What is recursion memory behavior?

Each recursive call creates a new stack frame.

Example:

```c
void fun(void)
{
    fun();
}
```

Infinite recursion leads to stack overflow.

## 28. Why are static variables useful in embedded systems?

Used for:

- State retention
- Counters
- Persistent task variables
- ISR communication

Example:

```c
static uint8_t uart_state;
```

---

# Storage Classes Interview Questions & Answers

## 1. What is a storage class in C?

A storage class tells us where a variable is stored, what its lifetime is, and what its scope is. Common storage classes are `auto`, `static`, `register`, and `extern`.

## 2. What is `auto` storage class?

`auto` is the default storage class for local variables. Variables declared inside a function are usually `auto` by default.

```c
void fun(void)
{
    int x = 10; // auto by default
}
```

## 3. What is `static` storage class?

`static` variables retain their value between function calls and have static lifetime.

```c
void counter(void)
{
    static int count = 0;
    count++;
}
```

## 4. What is `register` storage class?

The `register` keyword suggests the compiler store the variable in a CPU register for faster access, but the compiler may ignore it.

```c
register int i = 0;
```

## 5. What is `extern` storage class?

`extern` declares a variable or function defined in another file or translation unit.

```c
extern int global_count;
```

## 6. Difference between `auto` and `static`?

| `auto` | `static` |
| --- | --- |
| Local variable | Retains value across calls |
| Usually stack allocated | Has static storage duration |
| Lifetime limited to function call | Lifetime = entire program |

## 7. What is the scope of a `static` variable?

At file scope, it has internal linkage. Inside a function, it is local to that function but retains its value across calls.

## 8. What is the difference between `extern` and `static`?

`extern` provides external linkage and allows access across files, while `static` restricts visibility to the current file.

## 9. Why are storage classes important in embedded systems?

They control memory allocation, lifetime, and behavior of variables used in low-level drivers, timers, state machines, and interrupt handlers.

## 10. Which storage class is most useful for ISR variables?

`static` or `volatile` combinations are commonly used for ISR-shared state. `static` preserves state, and `volatile` ensures the compiler does not optimize away expected hardware changes.

---

# Bit Manipulation Interview Questions & Answers

## 1. What is bit manipulation?

Bit manipulation means performing operations directly on individual bits using bitwise operators.

This is heavily used in:

- Embedded systems
- Device drivers
- Communication protocols
- Register programming

## 2. Why is bit manipulation important in embedded systems?

Because hardware registers are controlled bit by bit.

Benefits:

- Faster execution
- Less memory usage
- Direct hardware control
- Efficient communication protocols

## 3. What are the bitwise operators in C?

```c
&   AND
|   OR
^   XOR
~   NOT
<<  Left shift
>>  Right shift
```

## 4. What is bitwise AND (`&`)?

It sets a bit to `1` only if both bits are `1`.

Example:

```c
5 & 3
```

Binary:

```text
0101
0011
----
0001
```

Result: `1`

## 5. What is bitwise OR (`|`)?

It sets a bit to `1` if any bit is `1`.

Example:

```c
5 | 3
```

Binary:

```text
0101
0011
----
0111
```

Result: `7`

## 6. What is bitwise XOR (`^`)?

It sets a bit to `1` if the bits are different.

Example:

```c
5 ^ 3
```

Binary:

```text
0101
0011
----
0110
```

Result: `6`

## 7. What is bitwise NOT (`~`)?

It inverts all bits.

Example:

```c
~5
```

## 8. What is left shift (`<<`)?

It shifts bits toward the left.

Example:

```c
5 << 1
```

Binary:

```text
0101 -> 1010
```

Result: `10`

Important: left shift by 1 is approximately a multiply by 2.

## 9. What is right shift (`>>`)?

It shifts bits toward the right.

Example:

```c
8 >> 1
```

Binary:

```text
1000 -> 0100
```

Result: `4`

Important: right shift by 1 is approximately a divide by 2.

## 10. How do you set a bit?

Use the OR operator.

```c
num |= (1 << pos);
```

Example:

```c
num = 5;
num |= (1 << 1);
```

## 11. How do you clear a bit?

Use AND with a NOT mask.

```c
num &= ~(1 << pos);
```

## 12. How do you toggle a bit?

Use XOR.

```c
num ^= (1 << pos);
```

## 13. How do you check whether a bit is set?

```c
if (num & (1 << pos))
{
    // bit is set
}
```

## 14. What is masking?

Masking means using bit patterns to extract or modify specific bits.

Example:

```c
status = reg & 0x0F;
```

This extracts the lower 4 bits.

## 15. What is a mask?

A mask is a bit pattern used during bit operations.

Example:

```c
0x0F == 00001111
```

## 16. What is bitfield extraction?

Bitfield extraction means retrieving specific bits from a value.

Example:

```c
data = (value >> 4) & 0x0F;
```

This extracts bits 4 through 7.

## 17. What is bit packing?

Bit packing combines multiple small signals into one variable or frame.

Useful in:

- CAN
- LIN
- UART protocols

Example:

```c
uint8_t data = (signal1 << 4) | signal2;
```

## 18. Why is bit packing useful?

Benefits:

- Saves bandwidth
- Saves memory
- Makes communication efficient

---

# Compilation Pipeline Interview Questions & Answers (Embedded Systems Focus)

## 1. What is compilation pipeline?

Compilation pipeline is the process of converting C source code into executable machine code.

Stages:

1. Preprocessing
2. Compilation
3. Assembly
4. Linking

---

## 2. What are the stages of compilation?

```text
.c file
   ↓
Preprocessor
   ↓
Compiler
   ↓
Assembler
   ↓
Linker
   ↓
Executable (.elf/.bin)
```

---

## 3. What is preprocessing?

Preprocessor handles:

- Macros
- Header includes
- Conditional compilation

Before actual compilation starts.

---

## 4. Which symbol is used for preprocessing directives?

```c
#
```

Examples:

```c
#include
#define
#ifdef
#ifndef
```

---

## 5. What does `#include` do?

Copies header file contents into source file.

Example:

```c
#include <stdio.h>
```

---

## 6. What is macro in C?

Text substitution performed by preprocessor.

Example:

```c
#define PI 3.14
```

---

## 7. Advantages of macros?

- Faster execution
- Reusable code
- No function call overhead

---

## 8. What are disadvantages of macros?

- No type checking
- Difficult debugging
- Multiple evaluation issues

Example:

```c
#define SQUARE(x) x*x
```

Problem:

```c
SQUARE(1+2)
```

Becomes:

```c
1+2*1+2
```

Output:

```text
5
```

instead of 9.

Safer version:

```c
#define SQUARE(x) ((x) * (x))
```

---

## 9. What is conditional compilation?

Compile specific code conditionally.

Example:

```c
#ifdef DEBUG
printf("Debug mode");
#endif
```

---

## 10. What is compilation stage?

Compiler converts preprocessed C code into assembly code.

Also performs:

- Syntax checking
- Optimization
- Semantic analysis

---

## 11. What errors are detected during compilation?

Examples:

- Syntax errors
- Type mismatch
- Undeclared variables

---

## 12. What is assembly stage?

Assembler converts assembly code into object code.

Output file:

```text
.o
```

or

```text
.obj
```

---

## 13. What is object file?

Intermediate machine code file generated by assembler.

Contains:

- Machine instructions
- Symbol table
- Relocation info

---

## 14. What is linking?

Combines multiple object files and libraries into final executable.

---

## 15. What does linker do?

Responsibilities:

- Resolve symbols
- Combine object files
- Address relocation
- Create executable

---

## 16. What is symbol resolution?

Linker matches function/variable references with definitions.

Example:

```c
extern int count;
```

Linker finds actual definition.

---

## 17. What is relocation?

Adjusting memory addresses during linking/loading.

---

## 18. What happens if linker cannot resolve symbol?

Linker error occurs.

Example:

```text
undefined reference
```

---

## 19. Difference between compiler error and linker error?

| Compiler Error | Linker Error |
|---|---|
| Syntax/type issue | Missing definitions |
| Happens during compilation | Happens during linking |

---

## 20. What is executable file?

Final runnable machine code.

Examples:

```text
.exe
.out
.elf
.bin
.hex
```

---

## 21. What is ELF file in embedded systems?

ELF = Executable and Linkable Format

Contains:

- Code
- Data
- Symbol table
- Debug info

Used for debugging/programming MCU.

---

## 22. What is BIN file?

Raw binary machine code.

Contains only executable instructions.

Used for flashing microcontrollers.

---

## 23. Difference between ELF and BIN?

| ELF | BIN |
|---|---|
| Contains debug info | Raw binary only |
| Larger size | Smaller |
| Used for debugging | Used for flashing |

---

## 24. What is HEX file?

Intel HEX formatted file containing:

- Address
- Data
- Checksum

Used for MCU programming.

---

## 25. What happens when you write a function?

Compiler:

- Creates symbol table entry
- Generates assembly
- Creates stack frame logic

---

## 26. What is symbol table?

Stores information about:

- Variables
- Functions
- Addresses
- Scope

---

## 27. What is stack frame generation?

Compiler creates logic for:

- Local variable allocation
- Parameter handling
- Return address handling

---

## 28. What happens during function call internally?

Steps:

1. Parameters pushed to stack/registers
2. Return address stored
3. Stack frame created
4. Function executes
5. Stack restored after return

---

## 29. What is name mangling?

Primarily in C++.

Compiler modifies function names internally.

C does not usually use name mangling.

---

## 30. What is startup code in embedded systems?

Code executed before `main()`.

Responsibilities:

- Initialize stack pointer
- Copy `.data`
- Clear `.bss`
- Configure runtime

---

## 31. What is linker script?

Defines memory layout of embedded application.

Specifies:

- Flash regions
- RAM regions
- Stack location
- Heap location

---

## 32. Why linker script important in embedded systems?

Because embedded systems have fixed memory addresses.

Need proper placement of:

- Code
- ISR vectors
- Stack
- Heap

---

## 33. What is static linking?

Libraries copied into executable.

Advantages:

- Standalone executable

Disadvantages:

- Larger size

---

## 34. What is dynamic linking?

Libraries loaded at runtime.

Common in Linux systems.

Less common in bare-metal embedded systems.

---

## 35. What is relocation table?

Contains addresses needing adjustment during linking/loading.

---

## 36. What is cross compilation?

Compiling code on one machine for another architecture.

Example:

- Compile on PC
- Run on ARM Cortex MCU

---

## 37. What is cross compiler?

Compiler generating code for different CPU architecture.

Example:

```text
arm-none-eabi-gcc
```

---

## 38. What is optimization in compiler?

Improves:

- Speed
- Code size
- Efficiency

---

## 39. Common optimization levels in GCC?

| Level | Meaning |
|---|---|
| `-O0` | No optimization |
| `-O1` | Basic optimization |
| `-O2` | Moderate optimization |
| `-O3` | Aggressive optimization |
| `-Os` | Optimize for size |

---

## 40. Why debugging difficult with optimization?

Compiler may:

- Remove variables
- Inline functions
- Reorder instructions

---

## 41. What is inline function?

Compiler may replace function call with actual code.

Example:

```c
inline int add(int a,int b)
{
    return a+b;
}
```

---

## 42. Advantages of inline functions?

- Faster execution
- Reduces function call overhead

---

## 43. Difference between macro and inline function?

| Macro | Inline Function |
|---|---|
| No type checking | Type safe |
| Preprocessor handled | Compiler handled |
| Hard debugging | Easier debugging |

---

## 44. What is dead code elimination?

Compiler removes unused code during optimization.

---

## 45. What is dependency in compilation?

Header/source relationships.

Changing header may require recompilation.

---

## 46. What is incremental build?

Only modified files recompiled.

Reduces build time.

---

## 47. What is Makefile?

Automation file for build process.

Defines:

- Compiler
- Flags
- Dependencies
- Build steps

---

## 48. Example GCC compilation command

```bash
gcc main.c -o app
```

---

## 49. Embedded compilation flow example

```text
main.c
 ↓
arm-none-eabi-gcc
 ↓
main.o
 ↓
Linker
 ↓
firmware.elf
 ↓
objcopy
 ↓
firmware.bin
```

---

## 50. Interview-Level Summary

| Stage | Output |
|---|---|
| Preprocessing | Expanded source |
| Compilation | Assembly code |
| Assembly | Object file (.o) |
| Linking | Executable (.elf/.bin) |

# Structure and Union Interview Questions & Answers — Basic

## 1. What is a structure in C?
A structure is a user-defined data type that groups variables of different data types under one name.

```c
struct Employee {
    int id;
    char grade;
    float salary;
};
```

## 2. Why are structures used in embedded systems?
Structures group related hardware, configuration, sensor, protocol, and application data into one logical object.

## 3. How do you declare a structure variable?

```c
struct Employee e1;
```

## 4. How do you access structure members?
Use the dot (`.`) operator.

```c
e1.id = 10;
e1.salary = 50000.0f;
```

## 5. What is a union?
A union is a user-defined type in which all members share the same memory location.

```c
union Data {
    int i;
    float f;
    char c;
};
```

## 6. What is the main difference between structure and union?
A structure allocates separate storage for its members, while union members share the same storage.

## 7. What is the size of a structure?
Its size is affected by member sizes, alignment requirements, and padding. It is not necessarily the simple sum of member sizes.

## 8. What is the size of a union?
At minimum, it must be large enough for its largest member and may include additional alignment requirements.

## 9. Can a structure contain different data types?
Yes.

```c
struct Sensor {
    int id;
    float temperature;
    char status;
};
```

## 10. Can a structure contain another structure?
Yes.

```c
struct Date {
    int day;
    int month;
};

struct Employee {
    int id;
    struct Date joining_date;
};
```

## 11. Can a union contain different data types?
Yes, but all members occupy the same storage.

## 12. Can a structure contain a pointer?
Yes.

```c
struct Node {
    int data;
    struct Node *next;
};
```

## 13. What is a typedef with structure?

```c
typedef struct {
    int id;
    float value;
} Sensor;

Sensor s1;
```

## 14. What is structure initialization?

```c
struct Sensor s = {1, 25.5f};
```

Designated initialization:

```c
struct Sensor s = {
    .value = 25.5f,
    .id = 1
};
```

## 15. What is a structure pointer?
A pointer that stores the address of a structure.

```c
struct Sensor s;
struct Sensor *p = &s;
```

## 16. How do you access members through a structure pointer?
Use the arrow (`->`) operator.

```c
p->id = 10;
```

`p->id` is equivalent to `(*p).id`.

## 17. Can structures be passed to functions?
Yes, either by value or by pointer.

```c
void process(struct Sensor *s);
```

Passing a pointer is often preferred when copying the whole structure is unnecessary.

## 18. Can a structure be returned from a function?
Yes.

```c
struct Sensor get_sensor(void);
```

## 19. What is padding?
Padding is unused space inserted by the compiler between or after structure members to satisfy alignment requirements.

## 20. What is alignment?
Alignment is the requirement that an object starts at an address suitable for its type.

## 21. Why is padding important in embedded systems?
Padding can increase RAM/Flash usage and affect binary layouts used for communication, storage, and hardware registers.

## 22. What is a bit-field?
A bit-field allows a structure member to occupy a specified number of bits.

```c
struct Flags {
    unsigned int ready : 1;
    unsigned int error : 1;
};
```

## 23. Why are bit-fields useful?
They can represent compact flags or fields, especially when working with status information.

## 24. What is a bit-field limitation?
Layout, allocation order, and other details can be implementation-defined, so bit-fields should be used carefully for portable protocol or hardware-register layouts.

## 25. What is memory layout of a structure?
Members appear in declaration order, with possible padding inserted between members and at the end.

## 26. What is memory layout of a union?
All members start at the same address.

## 27. Which operator is used to access union members?
Use `.` for a union object and `->` for a pointer to a union.

## 28. When should you use a union?
Use a union when different representations share the same storage and only one representation is intended to be active at a time.

## 29. When should you use a structure?
Use a structure when multiple fields need to exist simultaneously.

## 30. Simple structure vs union example

```text
Structure:
+---------+---------+---------+
|   int   |  float  |  char   |
+---------+---------+---------+

Union:
+-----------------------------+
| shared memory for one member|
+-----------------------------+
```
