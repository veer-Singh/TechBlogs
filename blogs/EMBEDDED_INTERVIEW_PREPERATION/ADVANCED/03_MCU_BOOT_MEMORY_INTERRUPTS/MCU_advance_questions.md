# Advanced MCU, Boot, Memory and Interrupt Questions

These questions focus on what happens between reset and `main()`, how the linker and memory map shape a running firmware, and how exceptions/interrupts actually enter, nest, and return. For every question, answer in the order: **Definition -> Why -> How -> Example -> Failure mode / trade-off**.

> Note: exact addresses, register names, alignment rules, and boot-memory aliases differ per Cortex-M profile and per silicon vendor. Treat the numbers here as representative; confirm against the target reference manual.

## 1. Explain a Cortex-M reset path.

On power-on, external `nRESET`, or a system reset, the core does very little by itself. It reads two words from the boot memory that is currently aliased at address `0x00000000`:

- Word at `0x00000000` -> initial **MSP** (Main Stack Pointer).
- Word at `0x00000004` -> **Reset** vector (address of the reset handler).

The core loads MSP, fetches the reset handler, and begins executing in Thread mode / handler-style startup before `main()`. The reset handler (toolchain `startup_*.s` / `Reset_Handler`) then runs the C runtime setup: `SystemInit()` for clocks and flash wait states, copy `.data` from flash to RAM, zero `.bss`, optionally run C++ constructors, then call `main()`.

Which physical memory is aliased at `0x00000000` depends on the boot configuration (main flash, system memory, or SRAM). That is why a blank or mis-linked image, or a wrong boot-pin state, produces a lockup before any user code runs.

## 2. What is in the vector table and how is it laid out?

The vector table is an array of 32-bit words starting at the active vector-table base:

- Word 0: initial MSP.
- Word 1: Reset.
- Then the system exceptions: NMI, HardFault, MemManage, BusFault, UsageFault, SVC, DebugMon, PendSV, SysTick (availability varies by profile).
- Then the device IRQs (IRQ0, IRQ1, ...).

Each handler entry is the **address** of the handler; the low bit is the Thumb bit and is normally set to 1 for a valid handler in Thumb state. Entries are usually supplied as weak symbols so application code can override a default infinite-loop handler by defining the same name.

Failure mode: an entry of `0` or a non-Thumb address causes a fault or an unexpected branch the moment that exception is taken.

## 3. What is VTOR, and when do you relocate the vector table?

**VTOR** (Vector Table Offset Register, Cortex-M3 and later) holds the base address of the *active* vector table. Cortex-M0/M0+ has no VTOR, so the table is fixed at its hardware base.

You relocate the table when:

- A bootloader hands control to an application that sits at a different flash address and has its own table.
- You want handler addresses in RAM so you can patch/register ISRs dynamically.
- An RTOS or firmware framework registers per-driver ISRs at runtime.

Requirements: the base must satisfy the alignment the device documents (commonly the table size, and often at least 32 words / 128 bytes), and VTOR must be updated **before** any interrupt that will use the new table is enabled. After writing VTOR, issue a `__DSB()` followed by `__ISB()` so the change is visible and the pipeline refetches.

## 4. What does the startup code do before `main()`?

The startup file bridges hardware reset and C code. Typical steps, in order:

1. MSP is already loaded by hardware from vector[0].
2. `SystemInit()`: configure the clock tree (PLL, prescalers), flash wait states, and optionally disable the watchdog.
3. Set `VTOR` to the correct table.
4. Copy `.data` from its load address in flash to its run address in RAM.
5. Zero the `.bss` region.
6. Initialize the C library (`__libc_init_array` runs C++ static constructors; `_sbrk` heap setup vary by toolchain).
7. Call `main()`.

Ordering matters: clocks must be correct before code that depends on timing, and `.data`/`.bss` must be ready before any C code that uses initialized/zeroed globals executes.

## 5. What is the difference between LMA and VMA?

- **VMA (Virtual Memory Address)**: where a section lives when the program runs.
- **LMA (Load Memory Address)**: where that section's initial image is stored in nonvolatile memory.

For `.text` and `.rodata`, LMA and VMA are usually identical (both in flash). For `.data`, the VMA is in RAM but the LMA is in flash, because the value must be writable at runtime yet survive power loss. The linker emits the copy source addresses, and startup code performs the copy.

Linker-provided symbols such as `_sidata`, `_sdata`, `_edata`, `_sbss`, `_ebss` mark these boundaries and are consumed by the startup copy/zero loops.

## 6. What happens if the vector table or reset vector is wrong?

The core has no recovery path of its own at reset:

- Bad initial MSP -> first push or interrupt faults immediately; often a lockup or HardFault before `main()`.
- Bad reset vector (not a Thumb address, erased 0xFFFFFFFF, or pointing to garbage) -> the core branches into invalid code.

Common causes: wrong link/load base address, wrong VTOR after a bootloader jump, a partially programmed or erased flash region, wrong boot-pin selection, or an incorrectly aligned vector table. Because no user code has run yet, the only diagnostics are the fault registers and a debugger attached at reset.

## 7. How does a typical bootloader-to-application handoff work?

A robust handoff does more than jump:

1. Validate the application image (header, length, hash, signature).
2. Shut down bootloader activity: disable its interrupts, clear pending IRQs, stop timers/DMA it owns, and de-initialize or reset peripherals the app will own.
3. Ensure a clean state: mask interrupts, set VTOR to the application's table (or let the app do it first), and load MSP from the application vector[0].
4. Jump to the application reset vector.

Failure modes: leaving bootloader interrupts enabled so an ISR vectors into the old table after the jump; not clearing the bootloader's peripheral state; or relying on the app to re-enable clocks it never set up. The app must fully reinitialize the clock tree and its own vector table.

## 8. How does the application know firmware is valid?

By combining integrity and authenticity:

- **Integrity**: a CRC or cryptographic hash (SHA-256) over the image detects corruption. A hash alone is only as trustworthy as the expected value, which must come from a trusted source.
- **Authenticity**: a digital signature over the image hash, verified with a public key whose trust anchor (public key hash / root cert) is stored in immutable memory such as OTP or protected ROM.

A typical image header holds magic, version, image length, hash, and signature. If the trust anchor can be replaced or the verifier skipped, the whole scheme collapses, so protecting the anchor and the verification code is the real security boundary.

## 9. What is secure boot conceptually, and what is A/B with rollback?

**Secure boot** establishes a chain of trust: each stage verifies the next stage before transferring control. The first stage's trust is rooted in immutable hardware (ROM boot + OTP key hash); it verifies stage 2, stage 2 verifies the application, and so on.

**A/B (dual-slot) update** keeps two application slots. The running slot is marked good; new firmware is written to the inactive slot, verified, and then selected by boot metadata that is updated atomically. Rollback protection uses a monotonic version counter so an attacker cannot re-flash a known-vulnerable older image.

Trade-off: authentication proves the image came from the trusted signer, but it does **not** hide its contents. Confidentiality is a separate goal requiring encryption of the image.

## 10. What is the role of the boot pins (BOOT0/BOOT1)?

At reset the core samples boot pins and uses them to select which physical memory is aliased at `0x00000000`:

- Main flash -> normal application boot.
- System memory -> vendor bootloader ROM (UART/USB/CAN DFU) for factory programming and recovery.
- SRAM -> debug/development boot.

The pins are sampled only at reset, so their state during normal running is irrelevant to the current boot. A design bug here is common: a floating or wrongly strapped BOOT pin makes a device occasionally enter the ROM bootloader instead of the application.

## 11. Why is clock configuration in `SystemInit` important before `main()`?

Almost every peripheral derives its clock from the system clock tree, and the CPU-to-flash timing depends on it:

- After reset the core usually runs from a fast-but-imprecise internal RC oscillator.
- Firmware raises the clock via the PLL, requiring **flash wait states** proportional to the target frequency.
- Peripherals (UART, timers, ADC, SysTick/HAL tick) are configured from their bus clock, so their divisors are meaningless until the tree is set.

Failure modes: not increasing flash wait states when raising the clock (unreliable fetches), or switching the clock source after configuring a peripheral that then runs at the wrong rate. Keep the sequence: set source and wait states, switch, then update `SystemCoreClock` and the tick source.

## 12. How do `.text`, `.data`, `.bss`, `.rodata`, `.heap`, and `.stack` differ?

- **`.text`**: executable code.
- **`.rodata`**: read-only data such as string literals and `const` objects; normally placed in flash, but may be copied to RAM if declared with a RAM attribute.
- **`.data`**: initialized read/write globals; VMA in RAM, LMA in flash; copied at startup.
- **`.bss`**: uninitialized or zero-initialized globals; RAM only; zeroed at startup.
- **heap**: dynamic-allocation region; grows/shrinks at runtime; region and limits are toolchain-specific.
- **stack**: automatic storage and exception frames; usually the region is grown downward from its top.

Placement followed one rule: a `const` definition lands in `.rodata`, an initialized non-`const` in `.data`, and an uninitialized or explicitly zeroed object in `.bss`. Understanding this is how you predict what actually consumes RAM versus flash.

## 13. How does a linker script describe memory regions?

A linker script (`.ld`/scatter file) has two conceptually separate halves:

- **`MEMORY`**: names physical regions with origin and length, e.g. `FLASH`, `RAM`, sometimes `CCMRAM` and multiple RAM banks. This tells the linker where bytes *may* go.
- **`SECTIONS`**: maps input sections from compiled objects into output sections and assigns them to regions, setting addresses and optionally `AT> region` load addresses.

A minimal mapping: `.text`/`.rodata` -> FLASH; `.data` -> RAM with `AT> FLASH`; `.bss` -> RAM; `.stack`/`.heap` -> RAM near the end. Linker-provided symbols (`_estack`, `_sidata`) are how startup code learns the boundaries.

Trade-off: how much flash and RAM to reserve for the stack/heap, and whether to place latency-critical code in RAM, are design decisions expressed here, not in C.

## 14. Why keep the stack 8-byte aligned, and how do link errors appear?

The AAPCS (Arm procedure call standard) requires **8-byte** stack alignment at a public interface. When an exception occurs, the core hardware-aligns the stack and pushes a 32-byte frame (8 words) on the aligned stack; if the SP was not already aligned, it inserts padding and records it in `xPSR` bit 9 (STKALIGN/SPREALIGN). Correct C compiled by a correct compiler maintains this automatically.

The classic link error `undefined reference to _sbrk` / the startup symbol occurs when startup is responsible for setting the stack but it is missing or mismatched, or when `malloc` is used but the heap is not defined. In a **scatter/`.ld`** flow the stack is a reserved region; in a **`-nostartfiles`** flow it must be an explicit symbol. Let the toolchain's startup/linker defaults apply unless you have a reason to override them.

## 15. How does interrupt-driven I/O differ from polling?

- **Polling**: the CPU repeatedly reads a status bit in a tight loop. Simple and predictable, but wastes cycles and delays other work.
- **Interrupt-driven**: a peripheral raises an IRQ; the CPU saves context, runs the ISR, and returns. Efficient and responsive, but adds context-switch overhead and concurrency hazards.

Rules that keep interrupt-driven I/O safe: keep ISRs short, defer heavy work to the main loop or a task, mark shared variables `volatile` (or use explicit memory ordering), guard multi-word state, and never call non-reentrant/blocking APIs from an ISR.

Success depends on which peripheral and which HAL: polling may be acceptable for a low-rate status check, while UART RX, DMA completion, and timing-critical events belong in interrupts.

## 16. What are NVIC priority, preemption, and subpriority?

The NVIC encodes each IRQ's priority in a register (on STM32: an 8-bit field in `NVIC_IPR`, of which only the implemented high bits matter). A fixed bit split divides each priority value into:

- **Preemption priority**: a higher-preemption (numerically lower) IRQ can interrupt a lower-preemption ISR.
- **Subpriority**: only breaks ties between equal preemption priorities when several are pending; it does not preempt.

Two rules define nesting: an ISR can preempt another only if its preemption priority is strictly higher, and equal-priority IRQs do not preempt each other. On a FreeRTOS system, every IRQ that calls a `...FromISR` API must have a preemption priority numerically **greater than or equal to** `configMAX_SYSCALL_INTERRUPT_PRIORITY`.

## 17. What are the Cortex-M exception entry and exit steps?

On taking an exception the hardware automatically:

1. Pushes a frame: `xPSR`, `PC`, `LR`, `R12`, `R3`, `R2`, `R1`, `R0` (32 bytes).
2. Loads the handler address from the vector table.
3. Loads `LR` with the EXC_RETURN magic value encoding which stack to return to and which mode.
4. Enters Handler mode, optionally stacking an FP frame if the FPU was active.

On exit it restores the frame and branches using `EXC_RETURN`.

This is why an ISR looks like a normal function yet returns to the interrupted code. For long or persistent work, the hardware frame plus Tail-chaining keeps overhead low; for a context switch, firmware triggers **PendSV** and does the switch in software.

## 18. What are tail-chaining, late arrival, and the lazy FPU state?

- **Tail-chaining**: if an exception is pending when an ISR is ready to return, the core skips unstacking/restacking and immediately vectors to the next handler, so back-to-back IRQs cost much less than two independent entries.
- **Late arrival**: if a higher-priority exception arrives while the core is already stacking for a lower-priority one, the core vectors straight to the higher-priority handler; the lower one runs afterward.
- **Lazy FPU stacking**: FPU registers are not stacked on exception entry unless the context actually used floating point, which is recorded in `CONTROL.FPCA`; the FP frame is added only when needed.

Together these features make Cortex-M interrupt latency short and its throughput high, but they also mean measured latency depends on pending state, not only on priority.

## 19. What is a memory barrier, and how does it differ from `volatile`?

A memory barrier constrains the **ordering** of memory accesses. `volatile` constrains the **optimizer** from removing or merging accesses to that specific object; it is not a barrier. They solve different problems.

Firmware uses:

- Compiler barriers (`__asm volatile("" ::: "memory")`, `asm volatile` clobbers) to prevent reordering around a critical region.
- Instruction barriers: `__DSB()` (complete before continuing), `__DMB()` (order data accesses), `__ISB()` (flush pipeline and refetch instruction stream).
- Architecture atomics/acquire-release (or `LDREX/STREX`) for inter-core sharing.

Needed when: releasing a lock, publishing a buffer pointer to DMA/another core, changing `VTOR` or MPU registers, or after cache maintenance.

## 20. What is cache coherency, and how do you handle DMA with caches?

On a cacheless MCU, CPU and DMA see the same memory, so a DMA buffer placed in RAM is naturally coherent. On a cached core (Cortex-M7 with D-cache, or an application core in an application processor), the CPU may read a stale cache line or fail to write back a dirty one, so DMA and CPU disagree.

Handling rules:

- **Global rules** where possible: mark DMA (and shared) buffers **non-cacheable** via MPU attributes, invalidate before a DMA-in transfer, clean before a DMA-out transfer, and align naturally to the cache-line size.
- Use a cache-maintenance API (`SCB_InvalidateDCache_by_Addr`, `SCB_CleanDCache_by_Addr`) after the transfer, not before and after blindly.
- Never place CPU-held data and DMA data in the same not-yet-maintained cache line.

## 21. What causes a HardFault, and how do you diagnose one?

A HardFault is the catch-all escalation (or direct cause) of a fault that the fault-status unit records. Typical causes: a bus error (bad address, unclocked peripheral, unaligned word access), a usage error (divide by zero if enabled, undefined instruction, unaligned access), a stack overflow, or an exception return with a bad frame.

Diagnose methodically:

1. Catch it in the handler and save the stacked frame words (`R0-R3, R12, LR, PC, xPSR`).
2. Read the fault status registers (`CFSR`/`HFSR`, plus `BFAR`/`MMFAR`) to classify the fault.
3. Map the saved `PC` to source/a disassembly listing to find the instruction.
4. Check `LR`/`SP` if the stack may be corrupted.

The saved `PC` is usually the single most useful value: it points at or just after the faulting instruction. Note that `MMFAR`/`BFAR` are only valid when the corresponding `VALID` bit in `CFSR` is set.

## 22. Why does the CPU lock up after enabling an interrupt that has no handler?

The default handler in most startup files is an infinite loop `b .`, or an exception. When the IRQ fires, the core vectors to that handler and stays there, so the CPU appears dead to the main loop. In Handler mode at the same priority, the main loop never runs again.

This is why the symbol shown in the debugger as the current PC when "the program hangs" is often a default handler name, and why the very first debugging step is to read the current PC and match it to a handler. Always implement every enabled IRQ's handler, or ensure the startup default is a conscious choice.

## 23. What is the difference between level- and edge-triggered interrupts?

- **Level-triggered**: while the interrupt source is asserted, the IRQ stays pending. If the ISR does not clear the source, it fires again immediately. Common for shared/peripheral request lines.
- **Edge-triggered**: the IRQ is latched on the transition only; no retrigger until the next edge, even if the source stays asserted.

Practical consequences: level-triggered IRQs require the ISR to clear or mask the condition before return, or the CPU livelocks in the handler; edge-triggered IRQs can lose events if the source pulses faster than the software can clear pending, and require debouncing for mechanical inputs. Many MCU external-interrupt blocks (e.g. EXTI) let you choose edge or level, and the choice interacts with how the pending bit is cleared.

## 24. How do you prioritize an interrupt that must be very fast?

Classify by latency requirement and isolate the critical section:

- Put the highest-frequency, shortest-latency work on the highest preemption priority, and keep that ISR tiny (a flag, a counter, a register read, a single handoff).
- Move everything else to lower-priority deferred work (main loop, RTOS task, or a software-triggered lower-priority IRQ).
- Protect shared data with the lightest mechanism that works, and account for the RTOS priority ceiling if one exists.
- Watch out for priority inversions: calling a kernel/blocking API from too high a priority leads to faults, while making unrelated ISRs equal-priority blocks preemption.

The inverse trade-off also matters: a very high priority for a noisy source can starve the rest of the system.

## 25. How do you debug an interrupt that never fires?

Walk the chain in order:

- Is the peripheral's interrupt enable bit set inside the peripheral itself?
- Is the function of the pin/peripheral configured (alternate function, input mode)?
- Is the specific IRQ enabled in NVIC (or is the block clock/IRQ masked)?
- Is there a pending flag left set from before enable that must be cleared, and does enabling occur while the source is already asserted?
- Is the priority valid (not below `configMAX_SYSCALL_INTERRUPT_PRIORITY` on an RTOS), and is global interrupt masking (`PRIMASK`/`FAULTMASK`) left set?
- Are the vector entry and handler name correct, and is `VTOR` pointing at the table that contains it?

Debug by toggling a GPIO in the handler and watching a scope, and by polling the pending/enable registers from the main loop to see which stage stops.

## 26. How do you handle interrupt latency deterministically?

Latency is the sum of several terms, and to bound it you must bound each:

- **Hardware entry**: stacking/handling, worst case when a late high-priority IRQ arrives and FPU state must be stacked.
- **Masking**: time spent with `PRIMASK` set (critical sections), which delays *all* IRQs; keep these short.
- **Nesting**: preemption by higher-priority ISRs, bounded by the priority scheme.
- **Software**: the ISR work itself.

Techniques: assign priorities so latency-critical IRQs are near the top, keep critical sections to a few instructions, avoid blocking calls and long floating-point in ISRs, use DMA to decouple burst work from the CPU, and measure with a GPIO toggled at entry/exit rather than reasoning about it.

## 27. What are PendSV and SysTick, and why use PendSV for context switching?

- **SysTick**: a core 24-bit down counter used as a periodic tick for an RTOS (or time base) generated by the core itself.
- **PendSV**: a software-triggered exception, typically lowest priority, used to perform the actual context switch.

The pattern: SysTick (or an event) sets PendSV pending; when all higher-priority handlers have finished, PendSV runs and saves/restores task context. Because PendSV is lowest priority and software-controlled, it **never interrupts another ISR**, so a context switch can wait until the current interrupt work is complete. Doing the switch in PendSV instead of inside SysTick avoids preempting interrupts and keeps a deterministic, single place where the switch happens.

## 28. What is `EXC_RETURN`, and what does it encode?

When an exception is taken, the hardware loads `LR` with a special value whose bit pattern identifies how to return: which stack pointer to use (MSP or PSP), whether to return to Thread or Handler mode, and whether a floating-point frame is present.

The handler must not corrupt this `LR` if it intends to return normally; this is why a plain `bx lr` at the end of an ISR restores the interrupted context. A context switch instead *changes* the saved `LR` (or the stacked context) so the return lands in the chosen task.

## 29. What does the stack overflow look like at the hardware level?

The stack grows downward in the region you reserved. When it underflows its region it physically writes below it, into adjacent RAM: another variable's area, a task stack, or the heap.

Symptoms and detection:

- A write to a variable that changes unexpectedly, or a HardFault whose faulting `SP` is outside the expected region.
- A HardFault on entry when the MSP hits a boundary or an unaligned/invalid address.
- Detection: enable an MPU guard region below the stack, place a known canary pattern below it and scan it periodically, use the RTOS high-water-mark check, or keep the lowest addresses reserved.

Root causes are usually deep recursion, a large automatic array in a task with a small stack, or an ISR that preempts deep in the call tree.

## 30. How do device faults progress from a configurable unit up to HardFault?

The core evaluates each fault against its **enable** bits:

- If the specific fault is enabled in `SHCSR`, the core vectors to the corresponding handler (MemManage, BusFault, UsageFault).
- If it is disabled, or if the fault occurs while already in a fault handler at the same or lower priority, it **escalates** to HardFault.

Because a fault taken inside a fault handler escalates, a bug in a fault handler's own access tends to become a second HardFault. This is why diagnostics should be gathered as early and as simply as possible in a minimal-entry HardFault handler.

## 31. How do you split RAM between stack and heap deliberately?

Give the design a budget rather than leaving it to chance:

- Reserve the **stack** region explicitly, size it for the actual worst-case path, and reserve margin. Static allocation avoids fragmentation.
- Reserve a **heap** region only ifyou actually use `malloc`/`new`; many safety-critical designs forbid dynamic allocation entirely.
- On an RTOS, allocate per-task stacks and avoid heap-based queues/timers where bounded behavior is required.

Linker scripts and toolchain defaults differ; the design decision is which sections are placed where, plus the guard/canary and overflow checks around them. A useful rule: prefer static allocation on MCUs, and treat any heap as a fixed budget you measure with a high-water mark.

## 32. What is `volatile` actually required for?

`volatile` tells the compiler the object may change **outside the current flow of control**, so it must not cache it in a register, reorder it away, or remove apparently redundant reads/writes. It is required for:

- Memory-mapped peripheral registers.
- Variables shared between an ISR and main/task context.
- Variables changed by DMA or another core.

It is **not** a substitute for atomicity or memory barriers. A 32-bit aligned read/write is atomic on Cortex-M, but a read-modify-write (`counter++`), a bitfield, or a 64-bit value is not. Use `volatile` for observability plus a critical section/atomic for the modification.

## 33. How does a peripheral interrupt make it from the pin to the CPU?

Peripheral interrupt latency is a chain of enable and routing stages, not a single step. A typical path, using an external line as an example:

1. The **pin/alternate function** is configured, and the edge detector (e.g. EXTI) records the event and sets its **pending** flag.
2. The peripheral's event is routed to the **NVIC** by a mux; NVIC sets the corresponding pending IRQ.
3. If the IRQ is **enabled** in NVIC and its priority passes the current mask, the core takes the exception.
4. Hardware saves the frame and vectors to the handler from the vector table (`VTOR`-based).

Where it breaks: a programming error at any stage — an unconfigured pin, a debounce that never triggers, the wrong peripheral-to-line mapping, a pending flag left set, the wrong IRQ enabled, or a handler name that does not match the symbol.

## 34. What are the main sources of interrupt latency and jitter?

Split into fixed and variable:

- **Fixed/hardware**: exception entry costs a stacking + vector fetch, deterministic for a given state.
- **Variable**: tail-chaining/late-arrival scheduling, waiting for a long critical section (`PRIMASK`) to end, and preemption by higher-priority IRQs.

Examples of the same IRQ firing with different measured latency: a pending higher-priority IRQ is mid-service in one run and absent in another; or the main line is inside a long critical section in one run. Because of this, always quote a worst-case bound and the conditions under which it holds, not an average.

## 35. How do you implement a C function to be an ISR safely?

- Use the **exact handler name** the vector table defines (or the toolchain's attribute/irq-handler convention) so the vector resolves to your function.
- Declare shared data `volatile` and protect it where atomicity is required.
- Keep it short; do not block, allocate, print with an unbounded formatter, or call non-reentrant library code.
- Do the minimum in the ISR: read the source data, clear the interrupt flag, then hand off (set a flag or send a queue message) for heavier processing.
- For an RTOS, use the `...FromISR` variants and the correct yield on exit.

In C, a function used as a handler by name is resolved by the linker, not by source ordering; a typo silently keeps the weak default handler.

## 36. What is the difference between an interrupt and an exception?

- **Exception**: the architectural term (Cortex-M), covering anything that interrupts normal flow: reset, NMI, HardFault, SVC, PendSV, SysTick, and external interrupts.
- **Interrupt (IRQ)**: an external or peripheral event routed to the NVIC that requests service.

Practical rule: the mechanism is the same (save frame, vector, return), so the same care applies; the difference is the source. Reset is a half-exception (it does not return the normal way), which is why the startup path is special-cased.

## 37. How do you debug a corrupted vector table or bad handler?

Compile a one-line check first: dump the words at the active `VTOR` base and compare with the linked image and the map file.

Then:

- Confirm `VTOR` matches the running image base (a stale `VTOR` after a bootloader jump is a classic cause).
- Confirm handler symbol names match the vector declarations; a name mismatch means the default loop survives.
- Confirm the image is loaded at the address the linker assumed.
- Suspect flash corruption if a word that should be a valid handler is `0xFFFFFFFF` or garbage.

A wrong table usually produces a lockup the first time an affected IRQ fires, so correlate with the debugger's current PC and the fault registers.

## 38. What is an unaligned access and how do you prevent a fault?

An aligned word access has its address a multiple of the access size. Cortex-M generally allows some unaligned halfword/word accesses, but not all: unaligned access to a device/peripheral region or with unaligned access trapping enabled raises a UsageFault (or becomes HardFault if UsageFault is disabled).

Prevention: align buffers and structures (compiler alignment attributes), avoid casting packed/`char` buffers to wider types, use `memcpy` for unaligned copies, and check that the fault's saved `PC` points at the offending load/store. Reading naturally-aligned rings and DMA descriptors avoids the whole class.

## 39. What does a stack backtrace look like when the CPU is in an ISR?

A normal call returns by `LR`/stack frames, but an ISR entered by hardware has a hardware-pushed exception frame, not a `BL` return address. Debugger unwinders recognize this and use the stacked `PC`/`LR` plus `EXC_RETURN` to reconstruct the interrupted call chain.

Consequences: a naive frame-pointer walk may stop or misreport at an ISR boundary; the reliable anchors are the stacked `PC` (where the interrupt happened) and the interrupts-already-active state. Preserve the exception frame early in the handler if you want a trustworthy postmortem.

## 40. What is the role of memory attributes (MPU / cacheability)?

For Cortex-M with an MPU, each region carries attributes: read/write/execute permissions, and memory type/behavior such as Normal cached, Normal non-cacheable, and Device/Strongly-ordered. These determine both access permission and how the interconnect treats the region.

They matter for:

- **DMA/shared buffers**: mark as non-cacheable or manage cache explicitly (see #20).
- **Protection**: make code/variables read-only to catch stray writes; use a guard region to catch stack overflow.
- **Peripherals**: keeping device regions strongly ordered and non-cacheable avoids stale reads and reordering.

Trade-off: attribute conflicts and multiple regions overlapping require the priority rules of the MPU; and marking shared RAM non-cacheable trades performance for simplicity. On hard real-time audio, the same reasoning appears in audio/DSP systems where buffer access must not stall on cache lines.

## Bonus: Quick reference for the numbers

| Item | Representative value / rule |
| --- | --- |
| Initial MSP and reset vector | words 0 and 1 of the active vector table |
| CPU exception frame size | 32 bytes (8 words); +FP frame if FPU active |
| Thumb handler address | low bit set to 1 |
| Default stack alignment | 8 bytes (AAPCS) at public interfaces |
| Typical Cortex-M D-cache line | 32 bytes (Cortex-M7, part dependent) |
| Fault status registers | `CFSR`/`HFSR`, `MMFAR`, `BFAR` |
| FreeRTOS ISR priority rule | preemption priority numerically >= `configMAX_SYSCALL_INTERRUPT_PRIORITY` |

> Always confirm the exact values against the target reference manual and the toolchain's linker/startup files before relying on any of the above in production code.
