# Advanced C++ Interview Questions (for Embedded)

How to use this file: this is a 75-question flashcard track in numbered order. Answer each question aloud first, then compare with the **Short answer**, the commented example, and the **Follow-up**. Each question has a **Topic** tag.

Topic tags: Basics, OOP, Memory, Modern C++, Templates, Errors, Concurrency, Design, Testing, Cost.

## The one idea behind most answers

Interviewers want to hear that you know the **cost** of each C++ feature (flash, RAM, time, determinism) and can say why it is acceptable for your product.

| Feature | Typical cost | Cheaper alternative |
| --- | --- | --- |
| Virtual function | vtable pointer per object, indirect call | Template, function table |
| Exceptions | Extra tables and code, harder stack analysis | Status codes, `expected` |
| RTTI | Extra type data | Tagged types, enums |
| `std::function` | Type erasure, possible allocation | Function pointer |
| `std::vector` | Heap, reallocation | `std::array`, fixed capacity |
| Templates | Code per instantiation | Shared non-template core |

---

## 1. Why use C++ for firmware instead of C?

**Topic:** Basics

**Short answer:** Stronger type safety, RAII, generics, and namespaces, with the same low-level control. Understand the cost model.

## 2. What is RAII?

**Topic:** Basics

**Short answer:** Resource Acquisition Is Initialization: a resource is owned by an object and released when the object dies.

```cpp
class LockGuard {
public:
    explicit LockGuard(Mutex& m) : m_(m) { m_.lock(); }     // acquire in the constructor
    ~LockGuard() { m_.unlock(); }                           // release in the destructor, always
private:
    Mutex& m_;
};

void update() {
    LockGuard g(mutex);      // locked here
    shared_value++;
}                            // unlocked here, even on early return
```

## 3. Why prefer constructor initializer lists?

**Topic:** Basics

**Short answer:** Members are initialized directly, not default-constructed and then reassigned. Required for references and `const` members.

```cpp
class Uart {
public:
    Uart(uint32_t baud, Registers& regs) : baud_(baud), regs_(regs) {}   // initializer list
private:
    const uint32_t baud_;      // const member: MUST be in the initializer list
    Registers& regs_;          // reference member: MUST be in the initializer list
};
```

## 4. What is a virtual function?

**Topic:** OOP

**Short answer:** Dynamic dispatch through a base-class interface. It usually costs a vtable pointer per object and an indirect call.

## 5. What is a pure virtual function?

**Topic:** OOP

**Short answer:** A member declared `= 0`. It makes the class abstract, and derived classes implement it.

```cpp
class Transport {
public:
    virtual bool send(const uint8_t* data, size_t len) = 0;   // pure virtual: no body here
    virtual ~Transport() = default;
};
```

## 6. Why should a polymorphic base class often have a virtual destructor?

**Topic:** OOP

**Short answer:** Deleting a derived object through a base pointer must run the derived destructor. Without `virtual`, that is undefined behaviour.

## 7. What is object slicing?

**Topic:** OOP

**Short answer:** Copying a derived object into a base object by value throws away the derived part.

```cpp
void log(Sensor s);          // by value: slices
void log(const Sensor& s);   // by reference: keeps the derived type
```

## 8. What is the Rule of Five?

**Topic:** Memory

**Short answer:** If a class manages a resource and defines one of destructor, copy constructor, copy assignment, move constructor, or move assignment, it probably needs all five.

## 9. What is the Rule of Zero?

**Topic:** Memory

**Short answer:** Let member types manage resources, so the class needs no custom special member functions.

## 10. What is move semantics?

**Topic:** Memory

**Short answer:** Move operations transfer a resource from a temporary or expiring object instead of copying it.

```cpp
Buffer make();                // returns a big buffer
Buffer b = make();            // moved (or elided), not copied
```

## 11. Why can dynamic allocation be risky in embedded C++?

**Topic:** Memory

**Short answer:** Heap fragmentation and non-deterministic timing can break timing or memory limits. Policies may restrict or isolate allocation.

## 12. What is `noexcept` useful for?

**Topic:** Errors

**Short answer:** It states that a function will not throw. It can also affect optimization and container behaviour (see Q68).

## 13. Why disable exceptions in some firmware projects?

**Topic:** Errors

**Short answer:** Bounded control flow, smaller runtime support, or coding standards. It is an architectural decision, not a universal rule.

## 14. What is RTTI?

**Topic:** Basics

**Short answer:** Run-time type information, used by `dynamic_cast` and `typeid`. It adds binary and data overhead and is often disabled (`-fno-rtti`).

## 15. What is `constexpr`?

**Topic:** Modern C++

**Short answer:** It allows compile-time evaluation when the inputs and expression permit.

```cpp
constexpr uint32_t kBaud = 115200;
constexpr uint32_t bit_time_us(uint32_t baud) { return 1000000u / baud; }
constexpr uint32_t kBitTime = bit_time_us(kBaud);   // computed by the compiler, no runtime cost
```

## 16. What is `consteval`?

**Topic:** Modern C++

**Short answer:** A function that **must** be evaluated at compile time. Stronger than `constexpr`, and needs C++20.

## 17. Why use `enum class`?

**Topic:** Modern C++

**Short answer:** Scoped, strongly typed enumerators with no silent conversion to `int`.

```cpp
enum class State : uint8_t { Idle, Busy, Error };
State s = State::Idle;          // must be qualified
// int x = s;                   // error: no implicit conversion
```

## 18. What is template metaprogramming useful for in embedded?

**Topic:** Templates

**Short answer:** Moving decisions to compile time, zero-overhead abstractions, and fixed capacities without runtime polymorphism.

## 19. What is `std::array` useful for?

**Topic:** Modern C++

**Short answer:** A fixed-size array with STL features and no dynamic allocation. An embedded-friendly container.

## 20. What is a span-like view?

**Topic:** Modern C++

**Short answer:** A non-owning view of contiguous data. It passes pointer and length together without copying.

```cpp
void parse(std::span<const uint8_t> bytes);      // C++20
std::array<uint8_t, 16> buf{};
parse(buf);                                      // no copy, size travels with the pointer
```

## 21. What is ownership?

**Topic:** Design

**Short answer:** Which object or component is responsible for a resource's lifetime. Explicit ownership prevents leaks, double frees, and unclear concurrency.

## 22. `unique_ptr` in embedded?

**Topic:** Memory

**Short answer:** Exclusive ownership. Useful when dynamic lifetime is justified, but check allocation and deleter behaviour.

## 23. `shared_ptr` in embedded?

**Topic:** Memory

**Short answer:** Shared ownership adds reference counting and often a control-block allocation. Usually unnecessary for deterministic low-level drivers.

## 24. What is dependency injection in embedded?

**Topic:** Testing

**Short answer:** Pass collaborators (transport, register access) in through constructors or interfaces, so logic can be tested without hardware.

```cpp
class Sensor {
public:
    explicit Sensor(Transport& bus) : bus_(bus) {}     // the bus is injected
private:
    Transport& bus_;
};
// Production: Sensor s(real_i2c);    Test: Sensor s(fake_i2c);
```

## 25. Why prefer composition over deep inheritance?

**Topic:** Design

**Short answer:** Explicit dependencies, less hidden runtime behaviour, fewer fragile hierarchies.

## 26. How would you design a hardware interface in C++?

**Topic:** Design

**Short answer:** A stable semantic interface separated from the MCU-specific implementation, explicit ownership, and no register details exposed upward.

## 27. What is a `constexpr` configuration object?

**Topic:** Modern C++

**Short answer:** A compile-time initialized struct with fixed parameters such as pin maps or buffer sizes. No runtime initialization.

```cpp
struct UartConfig { uint32_t baud; uint8_t tx_pin; uint8_t rx_pin; };
constexpr UartConfig kDebugUart{115200, 9, 10};    // lives in flash, no startup code
```

## 28. Why can templates increase flash usage?

**Topic:** Templates

**Short answer:** Each instantiation for a different type or size can generate separate code, unless the compiler merges it.

## 29. What is an inline namespace?

**Topic:** Basics

**Short answer:** A namespace mainly for API versioning. More relevant to large libraries than to typical MCU code.

## 30. What is copy elision?

**Topic:** Modern C++

**Short answer:** The compiler avoids unnecessary copies or moves. Required in some cases in C++17.

## 31. Why avoid global constructors in constrained systems?

**Topic:** Design

**Short answer:** They add startup work and hidden initialization order. Some projects restrict them to keep startup deterministic.

## 32. What is the static initialization order risk?

**Topic:** Design

**Short answer:** Static objects in different files can be initialized in an unspecified order. Prefer function-local statics or explicit initialization.

## 33. How does C++ interact with C drivers?

**Topic:** Basics

**Short answer:** Use `extern "C"` so C++ name mangling does not change the symbol names C code expects.

```cpp
extern "C" {
    #include "vendor_hal.h"      // C header: symbols keep their C names
}
```

## 34. What is ABI compatibility?

**Topic:** Basics

**Short answer:** Binary-level conventions: name mangling, calling convention, object layout, and exception and RTTI mechanisms. A toolchain change can break them.

## 35. What is placement new?

**Topic:** Memory

**Short answer:** Constructing an object in storage you provide. Good for static arenas, but lifetime is manual.

## 36. Why can exceptions affect stack analysis?

**Topic:** Errors

**Short answer:** Exception handling adds metadata and alternate control-flow paths, which complicates bounded execution and memory analysis.

## 37. What is the cost of a virtual call?

**Topic:** Cost

**Short answer:** An indirect call through a dispatch table, plus the table and pointer storage. The exact cost depends on the compiler and target.

```text
Object:  [vptr | members...]      vptr -> vtable: [&method1, &method2, ...]
Call:    load vptr, load slot, indirect jump
```

## 38. How do you avoid runtime polymorphism?

**Topic:** Design

**Short answer:** Templates, tagged unions or variants, function tables, or compile-time configuration, when dynamic dispatch is not needed.

## 39. What is `std::variant` useful for?

**Topic:** Modern C++

**Short answer:** One of several typed alternatives, modelling explicit states without inheritance. It may add code and data overhead.

```cpp
std::variant<Idle, Running, Fault> state;
std::visit([](auto& s) { s.tick(); }, state);     // call tick() on whichever is active
```

## 40. Why is `std::function` sometimes avoided in low-level firmware?

**Topic:** Cost

**Short answer:** Type erasure, storage overhead, and possible allocation. A raw function pointer or small delegate is cheaper.

## 41. What is a lambda in embedded C++?

**Topic:** Modern C++

**Short answer:** A callable object. A non-capturing lambda converts to a function pointer; a capturing lambda carries state and has a size.

```cpp
void (*cb)(uint32_t) = [](uint32_t e) { handle(e); };   // OK: non-capturing
```

## 42. How would you write a zero-allocation message queue wrapper?

**Topic:** Design

**Short answer:** A fixed-size array or ring buffer with compile-time capacity and explicit ownership, instead of allocating messages.

## 43. What makes an embedded C++ API reviewable?

**Topic:** Design

**Short answer:** Small interfaces, explicit ownership, clear lifetime, bounded memory, deterministic error paths, minimal hidden work, and a clear hardware boundary.

## 44. What is the benefit of strong types for units?

**Topic:** Design

**Short answer:** Distinct types for volts, milliseconds, bytes, or hertz prevent mixing quantities that share the same integer type.

```cpp
struct Milliseconds { uint32_t value; };
struct Hertz        { uint32_t value; };
void set_period(Milliseconds ms);
// set_period(Hertz{50});    // compile error: wrong unit
```

## 45. How would you make a driver mockable?

**Topic:** Testing

**Short answer:** Depend on an interface or injected function table for register and transport operations, then provide a fake for tests.

## 46. Why can default arguments be undesirable in library interfaces?

**Topic:** Design

**Short answer:** Defaults are substituted at the call site, so changing one requires rebuilding clients. Explicit configuration is clearer in long-lived firmware.

## 47. How do templates support fixed-capacity buffers?

**Topic:** Templates

**Short answer:** Capacity becomes a template parameter, so storage size and bounds checks are known at compile time, with no heap.

## 48. What is the embedded C++ trade-off question interviewers want?

**Topic:** Cost

**Short answer:** Can you explain the runtime cost of your abstraction and why it is acceptable for the timing, flash, RAM, and reliability requirements?

## 49. How would you replace a virtual interface in a hard real-time path?

**Topic:** Cost

**Short answer:** A function table, templates, tagged dispatch, or a compile-time policy. Compare code size, flexibility, testability, and timing.

## 50. How do you keep C++ drivers deterministic?

**Topic:** Design

**Short answer:** Bounded containers, explicit lifetimes, controlled allocation, predictable error handling, and clear ISR and task boundaries. Inspect generated code where speed matters.

## 51. What is the difference between `std::vector` and `std::array` in firmware?

**Topic:** Memory

**Short answer:** `std::array` stores a fixed number of elements inline and never allocates. `std::vector` owns a resizable heap allocation.

```cpp
std::array<uint8_t, 32> packet{};      // 32 bytes inline, no heap
std::vector<uint8_t> dynamic_packet;   // heap, may reallocate as it grows
```

**Follow-up:** Which is easier to bound for a hard real-time path? `std::array`.

## 52. How can you prevent accidental heap allocation in a driver?

**Topic:** Memory

**Short answer:** Fixed-capacity containers, static storage, deleted allocation operators where appropriate, and review or linker checks for allocation symbols.

```cpp
template <std::size_t Capacity>
class PacketBuffer {
    std::array<std::byte, Capacity> storage_{};    // capacity known at compile time
};
```

**Follow-up:** Is banning `new` enough? No. Library calls and hidden allocations must be checked too.

## 53. What is `std::optional` useful for in embedded C++?

**Topic:** Modern C++

**Short answer:** A value that may be absent, without a sentinel that could be mistaken for valid data.

```cpp
std::optional<uint16_t> read_temperature();

auto temperature = read_temperature();
if (temperature.has_value()) {                 // check before using
    use_temperature(*temperature);
}
```

**Follow-up:** What cost should be checked? Object size, code generation, and whether the contained type is cheap to move.

## 54. When would you use `std::expected` or an equivalent result type?

**Topic:** Errors

**Short answer:** When an operation returns either a value or a structured error, without exceptions.

```cpp
using ReadResult = expected<uint8_t, DriverError>;
ReadResult read_register(uint8_t address);
```

**Follow-up:** Why is it better than a global error variable? The error travels with the result and is safer for concurrency.

## 55. What is the difference between `volatile` and `std::atomic`?

**Topic:** Concurrency

**Short answer:** `volatile` controls compiler treatment of accesses only. `std::atomic` gives atomic operations and memory-ordering semantics.

```cpp
std::atomic<bool> conversion_done{false};
conversion_done.store(true, std::memory_order_release);
```

**Follow-up:** Is `volatile` right for a memory-mapped register? Often yes, but it does not replace synchronization between tasks.

## 56. What is a memory order in an atomic operation?

**Topic:** Concurrency

**Short answer:** It defines how operations are ordered and seen between contexts. Use the weakest order that satisfies the contract.

```cpp
data_ready.store(true, std::memory_order_release);        // producer: publish
if (data_ready.load(std::memory_order_acquire)) {         // consumer: observe
    consume_data();                                       // sees everything written before the release
}
```

**Follow-up:** What do release and acquire establish? Writes before the release become visible after a matching acquire.

## 57. How do you make a C++ class safe for ISR and task use?

**Topic:** Concurrency

**Short answer:** Define the execution-context contract, keep ISR methods short and non-blocking, and use ISR-safe synchronization at the boundary.

```cpp
void UartDriver::on_rx_irq() {
    rx_events_.give_from_isr();       // signal only; no parsing, no allocation
}
```

**Follow-up:** Should an ISR call a method that can allocate? No, unless allocation is proven bounded and explicitly allowed.

## 58. What is a `constexpr` lookup table useful for?

**Topic:** Modern C++

**Short answer:** Fixed data computed at compile time, avoiding runtime initialization.

```cpp
constexpr auto crc_table = make_crc_table();        // built by the compiler

constexpr uint8_t nibble_value(uint8_t value) {
    return crc_table[value & 0x0f];
}
```

**Follow-up:** Where should the table live? Choose flash or RAM deliberately, based on access speed and platform attributes.

## 59. What is the cost of virtual or multiple inheritance?

**Topic:** Cost

**Short answer:** Pointer adjustments, extra object metadata, complex layout, and larger code. Use only when the benefit is clear.

```cpp
struct Device : virtual Bus, virtual Clock {
    void start();
};
```

**Follow-up:** What should you inspect? Object size, construction order, generated calls, and ABI requirements.

## 60. Why should embedded classes avoid owning raw pointers?

**Topic:** Memory

**Short answer:** A raw pointer does not say who owns the object, which makes lifetime, cleanup, and copying ambiguous.

```cpp
class Driver {
public:
    explicit Driver(RegisterBlock& registers) : registers_(registers) {}   // borrowed, not owned
private:
    RegisterBlock& registers_;
};
```

**Follow-up:** When is a raw pointer acceptable? As a non-owning, nullable handle with a documented lifetime.

## 61. How do you implement a fixed-capacity ring buffer?

**Topic:** Templates

**Short answer:** Bounded storage, head and tail indices, and an explicit full and empty rule. No allocation, deliberate overflow behaviour.

```cpp
template <typename T, std::size_t Capacity>
class RingBuffer {
    std::array<T, Capacity> values_{};     // storage sized at compile time
    std::size_t head_{0};                  // next write position
    std::size_t tail_{0};                  // next read position
};
```

**Follow-up:** How do you distinguish full from empty? Keep a count, or reserve one slot.

## 62. What is false sharing, and can it matter on an MCU?

**Topic:** Concurrency

**Short answer:** Independent variables sharing a cache line cause needless coherence traffic. Mainly relevant on cached multicore systems.

```cpp
struct alignas(32) Counter {              // one counter per cache line
    std::atomic<uint32_t> value{0};
};
```

**Follow-up:** Is it usually the first concern on a small Cortex-M? No. Ownership and interrupt latency come first.

## 63. How do you avoid static initialization order problems?

**Topic:** Design

**Short answer:** Constant initialization, function-local statics with known behaviour, or explicit initialization in a controlled order.

```cpp
Logger& logger() {
    static Logger instance{debug_uart};    // created on first use
    return instance;
}
```

**Follow-up:** What risk remains? First-use initialization can still add hidden startup or locking behaviour.

## 64. What is placement `new` useful for?

**Topic:** Memory

**Short answer:** Constructing an object in storage you provide, supporting static arenas and deterministic allocation.

```cpp
alignas(Sensor) std::array<std::byte, sizeof(Sensor)> storage{};   // correct size AND alignment
auto* sensor = new (storage.data()) Sensor{config};                // construct in place
sensor->~Sensor();                                                 // destroy by hand: no delete
```

**Follow-up:** What must be handled manually? Alignment, lifetime, destruction, and reuse of the storage.

## 65. How do you enforce alignment for DMA buffers?

**Topic:** Design

**Short answer:** Declare the alignment and place the buffer in a memory region the DMA controller and cache policy allow.

```cpp
alignas(32) std::array<std::byte, 256> dma_buffer{};
```

**Follow-up:** Is alignment enough on a cached MCU? No. Cache maintenance or non-cacheable memory may also be needed.

## 66. What is the strong exception guarantee?

**Topic:** Errors

**Short answer:** An operation either fully succeeds or leaves the observable state unchanged.

```cpp
auto candidate = settings;         // work on a copy
candidate.apply(new_value);        // if this fails, 'settings' is untouched
settings = candidate;              // commit only on success
```

**Follow-up:** Always appropriate in firmware? Only when the copy cost and failure model are acceptable.

## 67. How do you design error handling when exceptions are disabled?

**Topic:** Errors

**Short answer:** Explicit status types, `expected`-style results, documented recoverable failures, and bounded error paths.

```cpp
enum class Status { ok, timeout, invalid_state };
Status start_conversion();
```

**Follow-up:** What should not happen? Silent failure, or error handling through undocumented global state.

## 68. What is a `noexcept` move constructor useful for?

**Topic:** Errors

**Short answer:** A non-throwing move lets containers and generic code move objects instead of falling back to copying.

```cpp
Buffer(Buffer&& other) noexcept
    : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;      // leave the source valid but empty
    other.size_ = 0;
}
```

**Follow-up:** What must the moved-from object guarantee? It must stay valid for destruction and reassignment.

## 69. How can you make a class non-copyable?

**Topic:** Design

**Short answer:** Delete copying when duplicating the underlying hardware resource would be unsafe or meaningless.

```cpp
class Uart {
public:
    Uart(const Uart&) = delete;                // no copy construction
    Uart& operator=(const Uart&) = delete;     // no copy assignment
};
```

**Follow-up:** Can it still be movable? Yes, if ownership transfer is valid and implemented safely.

## 70. What is the pImpl pattern, and is it useful on MCUs?

**Topic:** Design

**Short answer:** It hides implementation behind a pointer, cutting header dependencies and rebuilds, but adds indirection and often allocation.

```cpp
class Driver {
public:
    void start();
private:
    struct Impl;          // defined only in the .cpp file
    Impl* impl_;
};
```

**Follow-up:** When avoid it? In tight real-time paths, or when dynamic allocation is prohibited.

## 71. How do you expose a register block safely?

**Topic:** Design

**Short answer:** Wrap volatile registers in a small type that exposes meaningful operations, so unrelated code cannot poke fields directly.

```cpp
struct Registers {
    volatile uint32_t control;
    volatile uint32_t status;
};

void enable(Registers& registers) {
    registers.control |= 1u;       // named operation instead of a raw write
}
```

**Follow-up:** What does `volatile` not solve? Atomic read-modify-write races and hardware access ordering.

## 72. How do you test a C++ driver without hardware?

**Topic:** Testing

**Short answer:** Inject register, transport, clock, and interrupt collaborators, then use fakes to control responses and verify calls.

```cpp
FakeSpi spi;
Sensor sensor{spi};
sensor.read_id();
assert(spi.last_command() == ReadId);     // verify what the driver sent
```

**Follow-up:** What should tests avoid? Depending on timing or real peripheral side effects.

## 73. What is the cost of `std::function` in embedded code?

**Topic:** Cost

**Short answer:** Type erasure can grow object and code size and risk allocation. A function pointer or fixed delegate is cheaper.

```cpp
using Callback = void (*)(uint32_t event);
void register_callback(Callback callback);
```

**Follow-up:** When is `std::function` acceptable? When its storage and allocation behaviour are proven acceptable.

## 74. How do you use a function table instead of virtual functions?

**Topic:** Design

**Short answer:** Keep operation pointers in a fixed table and pass an explicit context pointer. It gives runtime dispatch without a vtable.

```cpp
struct Operations {
    bool (*read)(void* context, uint8_t* value);
    void* context;                        // the "this" that a virtual call would supply
};
```

**Follow-up:** What is the trade-off? More manual safety and context management in exchange for explicit layout and dispatch.

## 75. How do you review C++ for zero-cost abstractions?

**Topic:** Cost

**Short answer:** Check generated code, object size, allocations, startup work, exception and RTTI settings, and worst-case timing.

**Example:** A templated fixed-capacity queue can compile to the same loop as a hand-written C ring buffer.

**Follow-up:** What is the final engineering question? Does the abstraction improve correctness without violating flash, RAM, timing, or safety requirements?
