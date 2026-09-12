# Advanced Embedded Linux and Driver Questions

## 1. User-space vs kernel-space?

User-space applications run with restricted privileges and use OS APIs. Kernel-space code runs with high privilege and controls core OS/hardware mechanisms. Device drivers commonly execute in kernel space, while many hardware interactions should remain in user space when a kernel interface already exists.

## 2. What is a device tree?

On many embedded Linux systems, a device tree describes hardware configuration separately from the kernel image. The exact binding syntax and boot flow depend on the platform.

## 3. Character vs block device?

Character devices expose stream-like I/O semantics. Block devices support block-oriented storage and random access models. Linux driver interfaces and buffering semantics differ accordingly.

## 4. Interrupt handler design in Linux?

Do the minimum work in the hard interrupt context and defer longer processing when appropriate, using mechanisms such as threaded interrupts or workqueues depending on the driver.

## 5. Why use DMA in Linux drivers?

For high-bandwidth devices, DMA reduces CPU copying and can improve throughput. A correct driver must follow the kernel's DMA mapping and synchronization APIs rather than assuming physical addresses are directly usable.

## 6. How would you debug a Linux device driver?

Start with kernel logs/tracing, verify device tree/bus enumeration, inspect sysfs/debugfs interfaces where appropriate, check interrupt activity and register state, and reproduce the smallest failing operation.

## 7. Embedded Linux interview focus

Expect questions on boot flow, U-Boot concepts, device tree, kernel/user boundaries, driver binding, sysfs, interrupts, DMA, memory mapping, and networking.

