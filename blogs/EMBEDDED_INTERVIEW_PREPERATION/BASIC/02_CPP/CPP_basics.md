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

## Interview Tip

For embedded C++, interviewers often care less about syntax and more about whether you understand the cost of abstraction: memory, timing, startup behavior, allocation, and generated code.

