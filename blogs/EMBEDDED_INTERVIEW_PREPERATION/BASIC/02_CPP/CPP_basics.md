# C++ Interview Questions for Embedded

## 1. Why use C++ in embedded systems?

C++ can provide stronger abstraction, RAII, templates, namespaces, type safety, and object-oriented design while still allowing low-level control. Whether to use a feature depends on compiler support, code-size/runtime constraints, safety rules, and team standards.

## 2. What is a constructor?

A constructor initializes an object when its lifetime begins. Prefer member-initializer lists because members are initialized directly rather than default-constructed and reassigned.

```cpp
class Uart {
public:
    explicit Uart(uint32_t baud) : baud_(baud) {}
private:
    uint32_t baud_;
};
```

## 3. What is RAII?

Resource Acquisition Is Initialization ties resource ownership to object lifetime. In embedded code it can be used for locks, peripheral ownership, critical sections, and other resources, provided the generated code meets timing and exception constraints.

## 4. What is a virtual function?

A virtual function enables runtime polymorphism through a base-class interface. The implementation usually requires a virtual dispatch mechanism, such as a vtable, which can add memory and runtime overhead.

## 5. What is a pure virtual function?

A pure virtual function uses `= 0` and makes the class abstract when the class has at least one such member.

```cpp
class Driver {
public:
    virtual bool init() = 0;
    virtual ~Driver() = default;
};
```

## 6. What are templates useful for in embedded systems?

Templates enable compile-time generic code and can avoid runtime polymorphism. A fixed-size ring buffer is a common example because the capacity can be known at compile time.

## 7. Why can exceptions and RTTI be disabled?

Some embedded products disable exceptions or RTTI to reduce binary size, avoid dynamic runtime machinery, simplify failure behavior, or comply with coding standards. The exact decision is project-specific.

## 8. What is the Rule of 0/3/5?

Rule of 0: let standard/member types manage resources. Rule of 3: if a class needs a custom destructor/copy constructor/copy assignment, it likely needs all three. Rule of 5 extends this to move constructor and move assignment in modern C++.

## 9. `nullptr` vs `NULL`?

`nullptr` is a dedicated null pointer literal with type safety. `NULL` is traditionally a macro and may be defined as an integer constant.

## 10. STL in embedded systems?

Containers such as `std::array` can be excellent. Dynamic containers such as `std::vector` may also be valid, but their allocation behavior must be understood. Evaluate worst-case memory, determinism, exceptions, and fragmentation rather than banning STL categorically.

## 11. `const` correctness — what does `const` mean in different positions?

`const int* p` (or `int const* p`) means the pointed-to data can't be modified through `p`, but `p` itself can be reassigned to point elsewhere. `int* const p` means `p` itself is fixed (can't repoint), but the pointed-to data can be modified. `const int* const p` locks both. A `const` member function (`void foo() const`) promises not to modify the object's non-`mutable` members, and is required to call the function on a `const` object/reference — a very common embedded interview probe since it directly maps to "can this driver method be called on a `const Sensor&`?"

```cpp
class Sensor {
public:
    int read() const { return cached_value_; }   // may be called on a const Sensor
    void update(int v) { cached_value_ = v; }     // cannot be called on a const Sensor
private:
    int cached_value_;
};
```

## 12. What is the difference between `static` at file scope, `static` on a class member, and `static` inside a function?

At file/namespace scope, `static` gives a variable/function internal linkage — it's only visible within that translation unit, useful to avoid symbol clashes across `.cpp` files without a header declaration. A `static` class member is shared across all instances (one copy total, not per-object) and must usually be defined once outside the class (pre-C++17) or can be `inline static` (C++17+). A `static` local variable inside a function is initialized once and persists across calls, retaining its value between invocations — but in embedded/multithreaded contexts its initialization is only thread-safe if the compiler implements C++11's magic-statics guarantee, which isn't always true on smaller embedded toolchains, so a lazily-initialized `static local` can be a genuine race-condition hazard on constrained platforms.

## 13. What is the difference between `#define`, `const`, and `constexpr`?

`#define` is a textual macro substitution performed by the preprocessor before compilation — no type checking, no scoping, and it can produce subtle bugs (e.g., `#define SQUARE(x) x*x` breaks on `SQUARE(a+b)`). `const` creates a typed, scoped variable whose value can't be changed after initialization, but its value may still only be known at runtime (e.g., `const int n = read_sensor();`). `constexpr` requires the value be computable at compile time, letting the compiler fold it into the binary, use it for array sizes/template arguments, and often place it in flash/ROM rather than RAM on an embedded target — most modern embedded C++ guidance prefers `constexpr` over `#define` for named constants for exactly this reason.

## 14. What is name mangling, and why does `extern "C"` matter for embedded C++ code that links against a C driver?

C++ compilers mangle function names to encode parameter types and namespace/class info (enabling overloading), so a C++ compiler and a C compiler produce differently-named symbols for what looks like the same function signature. `extern "C"` tells the C++ compiler to use C-style (unmangled) linkage for a declaration, which is essential when a C++ application links against a vendor-supplied HAL or driver library compiled as C — without it, the linker fails to resolve the C library's symbols because the C++ side is looking for a mangled name that doesn't exist in the C object file.

```cpp
extern "C" {
    #include "vendor_hal.h"   // C header, unmangled symbols
}
```

## 15. What is operator overloading, and where is it risky in embedded code?

Operator overloading lets a class define custom behavior for operators like `+`, `==`, `[]`, or `()`, which can make code expressing domain concepts (fixed-point math, register bitfields, vectors) read naturally. The risk in embedded code is that an overloaded operator can hide non-trivial cost (a heap allocation, a loop, a syscall) behind innocent-looking syntax like `a + b`, making worst-case timing and code size much harder to eyeball from the call site — a legitimate reason some embedded coding standards restrict or ban certain overloads (especially ones that allocate) even though the language allows them freely.

## 16. What is undefined behavior (UB), and give an embedded-relevant example

UB is behavior the C++ standard places no requirements on — the compiler is free to assume it never happens, which means an optimizer can produce surprising results (not just a crash) once UB occurs, rather than a predictable "wrong answer." A classic embedded example is signed integer overflow (`INT_MAX + 1`) — unlike unsigned overflow (which is well-defined wraparound), signed overflow is UB, so a compiler is technically allowed to optimize away a bounds check that "can't" be reached if it depends on wraparound behavior. Another common one is reading an uninitialized variable, or violating strict aliasing by reinterpreting a pointer's type (common when parsing raw byte buffers) without using `memcpy` or a `union`/`std::bit_cast`.

## 17. What is placement new, and why is it used in embedded systems?

Placement `new` constructs an object at a specific, already-allocated memory address instead of allocating new storage: `new (address) MyClass(args);`. It's used in embedded systems to construct C++ objects in statically-allocated buffers, memory-mapped peripheral regions, or a custom memory pool — avoiding the heap and its non-determinism entirely while still getting constructor/RAII semantics. The object placed this way must be manually destructed by calling its destructor explicitly (`obj->~MyClass();`), since `delete` cannot be used on memory it didn't allocate.

## 18. What is the difference between stack, heap (free store), and static/global allocation, and why do many embedded coding standards forbid heap allocation after initialization?

Stack allocation (automatic storage) is fast, deterministic, and automatically reclaimed on scope exit, but limited in size and unsuitable for data that must outlive the function. Static/global allocation has a fixed address for the program's whole lifetime, with size known at compile/link time. Heap (`new`/`malloc`) allocation is flexible at runtime but has non-deterministic timing (allocator search/fragmentation-dependent) and can fail unpredictably after long uptime due to fragmentation — unacceptable for hard-real-time or long-running unattended embedded systems, which is why many embedded/safety coding standards (like MISRA C++ or a project's internal guidelines) forbid or tightly restrict dynamic allocation after system initialization, favoring static pools or placement new instead.

## 19. What happens if a destructor is not declared `virtual` in a base class used polymorphically?

If a base class is deleted through a base-class pointer (`Base* p = new Derived(); delete p;`) and the base's destructor is not `virtual`, only the base class's destructor runs — the derived class's destructor is skipped, so any resources it owns (memory, handles, peripheral locks) leak or are left in an inconsistent state, and this is undefined behavior per the standard. The rule of thumb: any class intended to be used polymorphically (has at least one virtual function, or is inherited from with the expectation of base-pointer deletion) needs a `virtual` (or explicitly `protected` non-virtual, if base-pointer deletion is intentionally disallowed) destructor.

## 20. What is a lambda, and what's the embedded-relevant cost of capturing by reference vs by value?

A lambda is an anonymous function object; `[x](){ ... }` captures `x` by value (copies it into the lambda's closure), while `[&x](){ ... }` captures it by reference (stores a reference, no copy, but the referenced variable must outlive the lambda's use). In embedded code, capturing by reference into a lambda that's stored and called later (e.g., as an ISR callback or a task callback registered with an RTOS) is a common dangling-reference bug if the captured local variable goes out of scope before the callback fires — capturing by value avoids that lifetime hazard at the cost of a copy, which matters for larger captured objects on a stack-constrained target.

## 21. What is the difference between `std::array` and a raw C array in embedded code, and why is `std::array` usually preferred in modern embedded C++?

Both have the same underlying storage (contiguous, fixed-size, no heap allocation, size known at compile time — so no runtime cost difference), but `std::array` doesn't decay to a pointer when passed to a function (avoiding the classic bug where `sizeof(arr)` inside a function that received a decayed raw array silently returns the pointer size instead of the array size), provides `.size()`, bounds-checked `.at()`, and works with STL algorithms and range-based `for` directly. Because it compiles down to identical machine code as a raw array, it's considered a "zero-cost" safety improvement — one of the more universally-accepted "use this in embedded C++" recommendations.

## 22. What is a memory-mapped register access pattern in C++, and why is `volatile` still required even with strong typing?

A common pattern wraps a hardware register address in a `volatile` pointer or a struct of `volatile` members overlaid on the peripheral's base address via `reinterpret_cast`, so reads/writes go directly to the memory address without being optimized away or reordered by the compiler:

```cpp
struct GpioRegs {
    volatile uint32_t data;
    volatile uint32_t dir;
};
auto* const gpio = reinterpret_cast<GpioRegs*>(0x4002'0000u);
gpio->dir = 0x1u;
```

`volatile` is still required regardless of C++'s type system because the compiler's optimizer has no notion that this particular memory address can change due to hardware side effects (an incoming interrupt, an external device) — without `volatile`, the compiler is free to cache the value in a register or eliminate what it thinks is a redundant read/write, exactly as in C.

## 23. Templates vs virtual functions for embedded polymorphism — what's the trade-off?

Templates resolve at compile time (static/parametric polymorphism) — no vtable, no indirect call overhead, and the compiler can often fully inline and optimize the generated code, but each instantiation with a different type generates separate code (potentially increasing flash usage — "code bloat"), and the interface can't be selected at runtime. Virtual functions resolve at runtime (dynamic polymorphism) via a vtable — one shared implementation and runtime flexibility (e.g., swapping a driver implementation based on detected hardware), at the cost of an indirect call (a few cycles, and it can hinder inlining/branch prediction) and per-object vtable pointer overhead. Interview answer worth giving: choose templates when the type is known at compile time and performance/code size is critical (e.g., a fixed peripheral driver); choose virtual dispatch when the concrete type genuinely varies at runtime (e.g., a plugin-style sensor abstraction).

## 24. What does `noexcept` mean, and why does it matter even in embedded code that has exceptions disabled entirely?

`noexcept` is a function specifier promising the function will not throw; if it does throw anyway, `std::terminate()` is called immediately rather than unwinding the stack. It matters even with exceptions fully disabled (`-fno-exceptions`) because move constructors/assignment marked `noexcept` let STL containers like `std::vector` choose to move elements during reallocation instead of copying them (for exception-safety reasons, a container will only move-optimize if the move can't throw) — so `noexcept` correctness can have a real, measurable performance impact on container-heavy code independent of whether the project ever throws an exception at all.

## 25. What is the difference between a `struct` and a `class` in C++, and does it matter for embedded register-overlay structs?

The only functional difference is default access/inheritance: `struct` members and base classes default to `public`, `class` defaults to `private`. Everything else (methods, constructors, inheritance, virtual functions) is identical. For embedded register-overlay structs — plain data used to mirror a hardware register map — `struct` is used purely by convention to signal "this is a plain data layout," and such structs typically avoid any virtual functions or added data members entirely (which would break the fixed memory layout binary-compatible with the hardware map), often paired with `static_assert(sizeof(RegsType) == expected_size)` to catch accidental padding/layout mismatches at compile time.

## Advanced OOP Concepts — Answered the Way You'd Say It in an Interview

## 26. Can you explain the four pillars of OOP, and tie each one to something you'd actually do in embedded code?

"Sure. The four pillars are encapsulation, abstraction, inheritance, and polymorphism.

Encapsulation is bundling data with the functions that operate on it, and controlling access — so in a driver class I'd keep the register pointer and internal state `private`, and only expose `init()`, `read()`, `write()` as the `public` interface. That way the caller can't poke the hardware state directly and break an invariant I'm relying on.

Abstraction is about hiding *how* something works behind a simpler interface — so my `TemperatureSensor` class exposes `readCelsius()`, and the caller doesn't need to know it's doing an I2C transaction, converting a raw ADC count, and applying a calibration offset internally.

Inheritance lets me express an 'is-a' relationship and share a common interface — for example, a `Sensor` base class with `Accelerometer` and `Gyroscope` derived from it, so code that just needs 'any sensor' can work against the base type.

And polymorphism is what makes that useful — calling `sensor->read()` through a `Sensor*` and having it invoke the correct derived implementation at runtime, via virtual dispatch. In embedded work I always follow that up by mentioning the cost — a vtable pointer per object and an indirect call — because interviewers want to see that I understand these aren't free."

## 27. What's the difference between compile-time and runtime polymorphism, and when would you pick one over the other?

"Compile-time polymorphism is function overloading and templates — the compiler figures out which version to call, or generates the specific code, at build time. Runtime polymorphism is virtual functions — the actual function called is resolved through a vtable lookup at runtime, based on the object's real type.

On an embedded target I lean toward compile-time polymorphism, templates specifically, when the concrete type is known at build time and I care about performance or code size — say, a fixed SPI flash driver that's only ever going to be one specific chip. I get zero-overhead abstraction because the compiler can inline everything.

I reach for runtime polymorphism, virtual functions, when the concrete type genuinely isn't known until runtime — like a sensor abstraction where the actual chip on the board is selected by reading an ID register at startup, or a plugin-style driver registry. There I accept the vtable indirection because I actually need that flexibility."

## 28. Why would you make a destructor virtual, and what breaks if you forget?

"I make a destructor virtual any time a class is meant to be used polymorphically — meaning someone might hold a `Base*` that's actually pointing at a `Derived` object, and might delete it through that base pointer.

If the base destructor isn't virtual and you do `Base* p = new Derived(); delete p;`, only `~Base()` runs. `~Derived()` never gets called. So if `Derived` owns a heap buffer, a mutex, or a peripheral handle, that resource just leaks or is left in a bad state — and the standard actually calls this undefined behavior, not just 'a leak.'

My rule of thumb: if a class has even one virtual function, or it's designed to be a base class at all, its destructor should be virtual — or, if I specifically want to *prevent* base-pointer deletion, I'll make it `protected` and non-virtual instead, so it's a compile error to even try."

## 29. What's the diamond problem, and how does C++ let you solve it?

"The diamond problem happens with multiple inheritance — say class `D` inherits from both `B` and `C`, and both `B` and `C` inherit from a common base `A`. Without any special handling, `D` ends up with two separate copies of `A`'s data, and calling something that lives in `A` becomes ambiguous — the compiler doesn't know which `A` you mean.

C++ solves it with virtual inheritance — if `B` and `C` both inherit from `A` *virtually* (`class B : public virtual A`), then `D` gets exactly one shared instance of `A`, and the ambiguity goes away.

Honestly, in embedded code I try to avoid deep multiple-inheritance hierarchies altogether — they add vtable complexity and object layout overhead that's hard to reason about on a constrained target. If I need to compose behavior from multiple sources, I'll often prefer composition — holding a member object — over inheriting from multiple bases."

## 30. What's the difference between function overloading and function overriding?

"Overloading is having multiple functions with the same name but different parameter lists in the same scope — it's resolved at compile time based on the arguments you pass. For example, `write(uint8_t)` and `write(const uint8_t*, size_t)` in the same class.

Overriding is different — it's when a derived class provides its own implementation of a `virtual` function that's already declared in the base class, with the *same* signature. That's resolved at runtime through the vtable, based on the actual object type.

A mistake I watch for in code review is someone thinking they're overriding a virtual function but they've actually changed the signature slightly, so they've accidentally overloaded and hidden the base version instead. That's exactly why C++11 gave us the `override` keyword — I always mark overrides with `override` so the compiler catches that mistake for me at compile time instead of it silently compiling into a bug."

## 31. Composition versus inheritance — how do you decide, especially for embedded driver design?

"The classic guidance is 'favor composition over inheritance,' and I mostly agree with it for driver design specifically.

Inheritance models an 'is-a' relationship and is appropriate when the derived type really is a more specific version of the base — an `Accelerometer` is-a `Sensor`. But it's tightly coupled: the derived class inherits the base's entire interface and implementation details, and changes to the base can ripple down in surprising ways.

Composition models a 'has-a' relationship — I'll have my `ImuManager` class *hold* an `Accelerometer` and a `Gyroscope` as members, rather than inheriting from them. That's more flexible: I can swap out the accelerometer implementation without touching `ImuManager`'s class hierarchy, and I avoid the vtable and multiple-inheritance overhead that comes with trying to model 'this class does accelerometer things and gyroscope things' through inheritance.

So my rule: use inheritance for genuine is-a relationships where I actually need polymorphic dispatch through a common interface; use composition for everything else, which in practice ends up being most of the time."

## 32. What is object slicing, and how have you seen it cause a real bug?

"Object slicing happens when you assign or pass a derived-class object *by value* to something expecting the base class — the derived-specific parts get 'sliced off,' and you're left with just the base subobject.

```cpp
void log(Sensor s) { /* takes Sensor by value */ }

Accelerometer accel;
log(accel);   // Accelerometer part is sliced away; log() only sees a Sensor
```

I've seen this bite a teammate when a container was declared as `std::vector<Sensor>` instead of `std::vector<Sensor*>` or a vector of a variant/pointer type — every element pushed into it got sliced down to the base class, and calls that should've dispatched to the derived `read()` implementation silently called the base version instead. No compiler error, no crash — just wrong behavior, which is the worst kind of bug to track down.

The fix is to never store or pass polymorphic types by value when you need the derived behavior — use references, pointers, or smart pointers instead, so the object is never copied into a smaller version of itself."

## 33. How would you implement the Singleton pattern for something like a UART driver, and what are the risks in an embedded context?

"A Singleton restricts a class to exactly one instance, with a global access point — for something like a UART peripheral, that maps naturally, since the hardware itself is a single physical resource.

```cpp
class Uart {
public:
    static Uart& instance() {
        static Uart uart;   // constructed once, on first use
        return uart;
    }
    void send(uint8_t byte);
private:
    Uart() = default;
    Uart(const Uart&) = delete;
    Uart& operator=(const Uart&) = delete;
};
```

That's the 'Meyers' Singleton' — using a function-local static — and it's thread-safe under C++11's magic statics guarantee, on toolchains that actually implement it.

But I'd flag the risks too, because interviewers like to see that: first, on some smaller embedded compilers, that thread-safe initialization guarantee isn't reliably implemented, so if this is called from multiple contexts before I'm sure of single-threaded startup, it can be a real hazard. Second, Singletons make unit testing harder — you can't easily substitute a mock for a global. And third, if a product later needs two UART peripherals, the whole class needs restructuring, so I usually only reach for a true Singleton when the hardware itself is inherently singular, and otherwise I'll just pass a driver instance explicitly."

## 34. What's the difference between an abstract class and an interface in C++, since C++ doesn't have an `interface` keyword?

"C++ doesn't have a dedicated `interface` keyword like Java or C#, so we express the same idea using an abstract class — a class with at least one pure virtual function, which makes it impossible to instantiate directly.

The convention I follow is: if I want something that behaves like a pure interface — no data members, no implemented methods, purely a contract — I make every method pure virtual and give it a virtual destructor, nothing else.

```cpp
class ITransport {
public:
    virtual bool send(const uint8_t* data, size_t len) = 0;
    virtual ~ITransport() = default;
};
```

An abstract class in the more general C++ sense can mix pure virtual functions *and* provide some default implementation or shared data — so it's a superset. I'll use that when derived classes genuinely share common logic, and reserve the pure-interface style specifically when I want to decouple a component, like my application logic, from a concrete implementation, like whether the transport underneath is UART or a TCP socket."

## 35. Why does C++ not support multiple *virtual* inheritance well in performance-critical code, and how does the vtable layout change with multiple inheritance?

"With single inheritance, each object typically has one vtable pointer at a fixed offset, so a virtual call is one indirect jump. With multiple inheritance, if a class inherits from more than one base that each has virtual functions, the derived object actually needs multiple vtable pointers — one per base subobject — and the compiler has to insert 'thunks' to adjust the `this` pointer when calling through different base pointers, since each base subobject sits at a different offset within the derived object.

That adds both a small amount of extra memory per object and a small amount of extra runtime overhead compared to single inheritance, and it makes the object's memory layout harder to reason about — which matters a lot in embedded work if you're ever tempted to reinterpret an object's raw memory (which you generally shouldn't do with polymorphic types anyway).

So practically, in embedded C++, I use multiple inheritance sparingly — mainly for the 'multiple pure-interface' pattern, like inheriting from both `ITransport` and `ILoggable`, where each base is a thin interface — and I avoid combining it with virtual (diamond-solving) inheritance unless there's a genuine shared-base requirement, because the layout and dispatch cost compounds."

## Interview Tip

For embedded C++, interviewers often care less about syntax and more about whether you understand the cost of abstraction: memory, timing, startup behavior, allocation, and generated code.

