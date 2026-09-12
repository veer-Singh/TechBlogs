# Advanced 02 Cpp Interview Questions

> 50-question deep-dive track. Use each Q&A as a flashcard: first answer aloud, then compare with the model answer.

## 1. Why use C++ for firmware instead of C?

C++ can add stronger type safety, RAII, generic programming, namespaces, and abstraction while still allowing low-level control. The cost model must be understood.

## 2. What is RAII?

Resource Acquisition Is Initialization ties resource ownership to object lifetime, enabling deterministic cleanup for resources such as locks or peripheral ownership.

## 3. Why prefer constructor initializer lists?

Members are initialized directly, avoiding unnecessary default construction and reassignment. It is also required for some members such as references and const members.

## 4. What is a virtual function?

A virtual function enables dynamic dispatch through a base-class interface. It typically introduces a runtime dispatch structure and may have memory/runtime cost.

## 5. What is a pure virtual function?

A member declared with =0 that contributes to making the class abstract. Derived classes can provide the implementation.

## 6. Why should a polymorphic base class often have a virtual destructor?

Deleting a derived object through a base pointer should invoke the derived destructor. Without a virtual destructor, that usage is unsafe.

## 7. What is object slicing?

Copying a derived object into a base object by value discards the derived part. Use references/pointers when polymorphic behavior is intended.

## 8. What is the Rule of Five?

If a class manages a resource and defines one of destructor, copy constructor, copy assignment, move constructor, or move assignment, it may need an appropriate set of all five.

## 9. What is the Rule of Zero?

Prefer member types that manage resources so the class itself needs no custom special member functions.

## 10. What is move semantics?

Move operations transfer ownership/resources from a temporary or expiring object rather than copying the underlying resource.

## 11. Why can dynamic allocation be risky in embedded C++?

Heap fragmentation and non-deterministic allocation behavior can violate timing or memory constraints. Policies may restrict or isolate allocations.

## 12. What is noexcept useful for?

It documents and enforces that a function does not propagate exceptions. It can also affect optimization and move/certain library behavior.

## 13. Why disable exceptions in some firmware projects?

Projects may want bounded control flow, smaller runtime support, or compliance with coding standards. The decision is architectural, not a universal C++ rule.

## 14. What is RTTI?

Run-time type information supports features such as dynamic_cast and typeid. It can add binary/data overhead and may be disabled in constrained systems.

## 15. What is constexpr?

It enables compile-time evaluation when inputs and the expression permit it. It is useful for fixed configuration values and generated lookup tables.

## 16. What is consteval?

It requires a function invocation to be evaluated at compile time. It is stronger than constexpr and requires compiler support for the C++ version used.

## 17. Why use enum class?

It provides scoped, strongly typed enumerators and avoids unintended implicit conversion to int in many contexts.

## 18. What is template metaprogramming useful for in embedded?

It can move decisions to compile time, create zero-overhead abstractions, and encode fixed capacities without runtime polymorphism.

## 19. What is std::array useful for?

It provides a fixed-size array with STL semantics and no dynamic allocation, making it a good embedded-friendly container.

## 20. What is a span-like view?

A non-owning view over contiguous storage. It can pass buffer and length together without copying data.

## 21. What is ownership?

Ownership defines which object/component is responsible for a resource lifetime. Explicit ownership prevents leaks, double frees, and unclear concurrency.

## 22. Unique_ptr in embedded?

std::unique_ptr expresses exclusive ownership. It can be useful when dynamic lifetime is justified, but allocation and deleter behavior must fit system constraints.

## 23. Shared_ptr in embedded?

shared_ptr expresses shared ownership but adds reference counting and often allocation/control-block overhead. It is usually unnecessary for deterministic low-level drivers.

## 24. What is dependency injection in embedded?

Provide collaborators such as transports or register interfaces through constructors or interfaces so logic can be tested without real hardware.

## 25. Why prefer composition over deep inheritance?

Composition often keeps dependencies explicit and reduces hidden runtime behavior and fragile hierarchies.

## 26. How would you design a hardware interface in C++?

Separate a stable semantic interface from MCU-specific implementation, keep ownership explicit, and avoid exposing register details to higher layers.

## 27. What is a constexpr configuration object?

A compile-time initialized structure holding fixed parameters such as pin mappings or buffer capacities. It can avoid runtime initialization.

## 28. Why can templates increase flash usage?

Different template instantiations may generate separate code for different types/configurations unless the compiler can merge or optimize them.

## 29. What is an inline namespace?

A namespace mechanism mainly for versioning APIs. It is more relevant to large libraries than typical MCU code, but can help maintain interfaces.

## 30. What is copy elision?

A compiler optimization, also permitted/required in certain C++ language cases, that avoids unnecessary object copies/moves.

## 31. Why avoid global constructors in constrained systems?

They add startup work and hidden initialization ordering. Some projects restrict dynamic/global object initialization to keep startup deterministic.

## 32. What is static initialization order risk?

Objects with static storage in different translation units can have unspecified initialization order dependencies. Prefer function-local statics or explicit initialization where appropriate.

## 33. How does C++ interact with C drivers?

Use extern "C" when C linkage is required so C++ name mangling does not change symbols expected by C code or linker scripts.

## 34. What is ABI compatibility?

It covers binary-level conventions such as name mangling, calling conventions, object layout, and exception/RTTI mechanisms. Compiler/toolchain changes can break ABI assumptions.

## 35. What is placement new?

It constructs an object in already-provided storage. It is useful for static memory arenas but requires careful object lifetime management.

## 36. Why can exceptions affect stack analysis?

Exception handling mechanisms may add metadata and alternate control-flow paths, making bounded execution and memory analysis more complex.

## 37. What is a virtual call cost?

Typically an indirect function call through a dispatch mechanism plus any associated table/storage. Exact cost depends on compiler and target.

## 38. How do you avoid runtime polymorphism?

Use templates, tagged unions/variants, function tables, or compile-time configuration when dynamic dispatch is not required.

## 39. What is std::variant useful for?

It represents one of several typed alternatives and can model explicit states without inheritance. It may add code/data overhead depending on use.

## 40. Why is std::function sometimes avoided in low-level firmware?

It can have type-erasure machinery, storage overhead, and potential allocation depending on the callable. A raw function pointer or lightweight delegate may be cheaper.

## 41. What is a lambda in embedded C++?

A lambda creates a callable object. Non-capturing lambdas can often convert to function pointers; capturing lambdas carry state and have object-size implications.

## 42. How would you write a zero-allocation message queue wrapper?

Use a fixed-size array/ring buffer with compile-time capacity and explicit ownership rules rather than allocating messages dynamically.

## 43. What makes an embedded C++ API reviewable?

Small interfaces, explicit ownership, clear lifetime, bounded memory, deterministic error paths, minimal hidden work, and a clear hardware abstraction boundary.

## 44. What is the benefit of strong types for units?

Distinct types for volts, milliseconds, bytes, or hertz can prevent accidental mixing of quantities that share the same underlying integer type.

## 45. How would you make a driver mockable?

Depend on an interface or injected function table representing register/transport operations, then provide a fake implementation for tests.

## 46. Why can default arguments be undesirable in library interfaces?

They are compile-time substitutions at call sites, so changing a default may require clients to be rebuilt. Explicit configuration can be clearer in long-lived firmware.

## 47. How do templates support fixed-capacity buffers?

The capacity becomes a template parameter, allowing compile-time storage sizing and bounds checks without dynamic allocation.

## 48. What is the embedded C++ trade-off question interviewers want?

Can you explain the generated/runtime cost of the abstraction you chose and why it is acceptable for the timing, flash, RAM, and reliability requirements?

## 49. How would you replace a virtual interface in a hard real-time path?

Consider a function table, templates, tagged dispatch, or compile-time policy when runtime polymorphism is not required. Compare code size, flexibility, testability, and timing.

## 50. How do you keep C++ drivers deterministic?

Prefer bounded containers, explicit lifetimes, controlled allocation, predictable error handling, and clear ISR/task boundaries; inspect generated code where performance is critical.

## 51. What is the difference between `std::vector` and `std::array` in firmware?

`std::array` stores a fixed number of elements inline and does not allocate. `std::vector` owns a resizable allocation and may reallocate as it grows.

**Example:**

```cpp
std::array<uint8_t, 32> packet{};
std::vector<uint8_t> dynamic_packet;
```

**Interview follow-up:** Which is easier to bound for a hard real-time path? `std::array`.

## 52. How can you prevent accidental heap allocation in a driver?

Use fixed-capacity containers, static storage, deleted allocation operators where appropriate, and code-review or linker checks for allocation symbols.

**Example:**

```cpp
template <std::size_t Capacity>
class PacketBuffer {
	std::array<std::byte, Capacity> storage_{};
};
```

**Interview follow-up:** Is banning `new` enough? No; library calls and hidden allocations must also be checked.

## 53. What is `std::optional` useful for in embedded C++?

It represents a value that may be absent without using a sentinel value that could be confused with valid data.

**Example:**

```cpp
std::optional<uint16_t> read_temperature();

auto temperature = read_temperature();
if (temperature.has_value()) {
	use_temperature(*temperature);
}
```

**Interview follow-up:** What cost should be checked? Object size, code generation, and whether the contained type is cheap to move.

## 54. When would you use `std::expected` or an equivalent result type?

Use it when an operation needs to return either a value or a structured error without exceptions.

**Example:**

```cpp
using ReadResult = expected<uint8_t, DriverError>;

ReadResult read_register(uint8_t address);
```

**Interview follow-up:** Why is it preferable to a global error variable? The error travels with the result and is safer for concurrency.

## 55. What is the difference between `volatile` and `std::atomic`?

`volatile` controls compiler treatment of accesses but does not provide atomicity or synchronization. `std::atomic` provides language-level atomic operations and memory-ordering semantics.

**Example:**

```cpp
std::atomic<bool> conversion_done{false};

conversion_done.store(true, std::memory_order_release);
```

**Interview follow-up:** Is `volatile` appropriate for a memory-mapped register? Often yes, but it does not replace synchronization between tasks.

## 56. What is a memory order in an atomic operation?

It defines how operations are ordered and observed between execution contexts. Choose the weakest order that satisfies the synchronization contract.

**Example:**

```cpp
data_ready.store(true, std::memory_order_release);
if (data_ready.load(std::memory_order_acquire)) {
	consume_data();
}
```

**Interview follow-up:** What does release/acquire establish? Writes before the release become visible after a matching acquire.

## 57. How do you make a C++ class safe for ISR and task use?

Define the execution-context contract, keep ISR methods short and non-blocking, and use ISR-safe synchronization at the boundary.

**Example:**

```cpp
void UartDriver::on_rx_irq() {
	rx_events_.give_from_isr();
}
```

**Interview follow-up:** Should an ISR call a method that can allocate? No, unless allocation is proven bounded and explicitly permitted.

## 58. What is a `constexpr` lookup table useful for?

It moves fixed transformations and validation data to compile time, avoiding runtime initialization and computation.

**Example:**

```cpp
constexpr auto crc_table = make_crc_table();

constexpr uint8_t nibble_value(uint8_t value) {
	return crc_table[value & 0x0f];
}
```

**Interview follow-up:** Where should the table live? Choose flash or RAM deliberately based on access speed and platform attributes.

## 59. What is the cost of virtual inheritance or multiple inheritance?

It can add pointer adjustments, extra object metadata, more complex layout, and larger generated code. Use it only when the design benefit is clear.

**Example:**

```cpp
struct Device : virtual Bus, virtual Clock {
	void start();
};
```

**Interview follow-up:** What should you inspect? Object size, construction order, generated calls, and ABI requirements.

## 60. Why should embedded classes avoid owning raw pointers?

Raw pointers do not express ownership and make lifetime, cleanup, and copying rules ambiguous.

**Example:**

```cpp
class Driver {
public:
	explicit Driver(RegisterBlock& registers) : registers_(registers) {}

private:
	RegisterBlock& registers_;
};
```

**Interview follow-up:** When is a raw pointer acceptable? For a non-owning nullable handle with a documented lifetime contract.

## 61. How do you implement a fixed-capacity ring buffer?

Use bounded storage, head and tail indices, and an explicit full/empty invariant. Avoid allocation and make overflow behavior deliberate.

**Example:**

```cpp
template <typename T, std::size_t Capacity>
class RingBuffer {
	std::array<T, Capacity> values_{};
	std::size_t head_{0};
	std::size_t tail_{0};
};
```

**Interview follow-up:** How do you distinguish full from empty? Use a count or reserve one slot.

## 62. What is false sharing and can it matter on an MCU?

False sharing occurs when independent variables share a cache line and updates cause unnecessary coherence traffic. It is mainly relevant on cached multicore systems.

**Example:**

```cpp
struct alignas(32) Counter {
	std::atomic<uint32_t> value{0};
};
```

**Interview follow-up:** Is it usually the first concern on a small Cortex-M? No; ownership and interrupt latency usually matter first.

## 63. How do you avoid static initialization order problems?

Prefer constant initialization, function-local statics with known behavior, or explicit system initialization in a controlled order.

**Example:**

```cpp
Logger& logger() {
	static Logger instance{debug_uart};
	return instance;
}
```

**Interview follow-up:** What risk remains? First-use initialization can still add hidden startup or locking behavior.

## 64. What is placement `new` useful for?

It constructs an object in caller-provided storage, which can support static arenas and deterministic allocation.

**Example:**

```cpp
std::array<std::byte, sizeof(Sensor)> storage{};
auto* sensor = new (storage.data()) Sensor{config};
sensor->~Sensor();
```

**Interview follow-up:** What must be handled manually? Alignment, lifetime, destruction, and reuse of the storage.

## 65. How do you enforce alignment for DMA buffers?

Declare the required alignment and place the buffer in a memory region compatible with the DMA controller and cache policy.

**Example:**

```cpp
alignas(32) std::array<std::byte, 256> dma_buffer{};
```

**Interview follow-up:** Is alignment sufficient on a cached MCU? No; cache maintenance or non-cacheable memory may also be required.

## 66. What is a strong exception guarantee?

It means an operation either completes successfully or leaves the observable state unchanged. It is useful for transactional updates but may require extra storage or work.

**Example:**

```cpp
auto candidate = settings;
candidate.apply(new_value);
settings = candidate;
```

**Interview follow-up:** Is this always appropriate in firmware? Only when the copy cost and failure model are acceptable.

## 67. How do you design error handling when exceptions are disabled?

Return explicit status types, use `expected`-style results, document recoverable failures, and keep error paths bounded.

**Example:**

```cpp
enum class Status { ok, timeout, invalid_state };

Status start_conversion();
```

**Interview follow-up:** What should not happen? Silent failure or error handling through undocumented global state.

## 68. What is a `noexcept` move constructor useful for?

A non-throwing move allows standard containers and generic code to move objects safely instead of falling back to copying.

**Example:**

```cpp
Buffer(Buffer&& other) noexcept
	: data_(other.data_), size_(other.size_) {
	other.data_ = nullptr;
	other.size_ = 0;
}
```

**Interview follow-up:** What must the moved-from object guarantee? It must remain valid for destruction and reassignment.

## 69. How can you make a class non-copyable?

Delete copying when duplicating the underlying hardware resource would be unsafe or meaningless.

**Example:**

```cpp
class Uart {
public:
	Uart(const Uart&) = delete;
	Uart& operator=(const Uart&) = delete;
};
```

**Interview follow-up:** Can it still be movable? Yes, if ownership transfer is valid and implemented safely.

## 70. What is the pImpl pattern and is it useful on MCUs?

pImpl hides implementation details behind a pointer, reducing header dependencies and rebuilds, but it may add indirection and allocation.

**Example:**

```cpp
class Driver {
public:
	void start();

private:
	struct Impl;
	Impl* impl_;
};
```

**Interview follow-up:** When should it be avoided? In tight real-time paths or when dynamic allocation is prohibited.

## 71. How do you expose a register block safely?

Wrap volatile registers in a small type that exposes meaningful operations and prevents unrelated code from manipulating fields directly.

**Example:**

```cpp
struct Registers {
	volatile uint32_t control;
	volatile uint32_t status;
};

void enable(Registers& registers) {
	registers.control |= 1u;
}
```

**Interview follow-up:** What does `volatile` not solve? Atomic read-modify-write races and hardware access ordering.

## 72. How do you test a C++ driver without hardware?

Inject register, transport, clock, and interrupt collaborators, then use fakes to control responses and verify calls.

**Example:**

```cpp
FakeSpi spi;
Sensor sensor{spi};
sensor.read_id();
assert(spi.last_command() == ReadId);
```

**Interview follow-up:** What should tests avoid? Depending on timing or real peripheral side effects.

## 73. What is the cost of `std::function` in embedded code?

It provides type erasure but may increase object size, code size, and allocation risk. A function pointer or fixed delegate can be cheaper.

**Example:**

```cpp
using Callback = void (*)(uint32_t event);
void register_callback(Callback callback);
```

**Interview follow-up:** When is `std::function` acceptable? When its storage and allocation behavior are proven acceptable.

## 74. How do you use a function table instead of virtual functions?

Store operation pointers in a fixed table and pass an explicit context pointer. This gives runtime dispatch without a C++ vtable.

**Example:**

```cpp
struct Operations {
	bool (*read)(void* context, uint8_t* value);
	void* context;
};
```

**Interview follow-up:** What trade-off exists? More manual safety and context management in exchange for explicit layout and dispatch.

## 75. How do you review C++ for zero-cost abstractions?

Check generated code, object size, allocations, startup work, exception/RTTI settings, and worst-case timing. Keep abstractions when their cost is understood and acceptable.

**Example:** A templated fixed-capacity queue can compile to the same loop as a hand-written C ring buffer.

**Interview follow-up:** What is the final engineering question? Does the abstraction improve correctness without violating flash, RAM, timing, or safety requirements?

