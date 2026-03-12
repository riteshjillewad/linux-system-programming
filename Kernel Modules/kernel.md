# 📦 Kernel Modules

A kernel module (kernel object) is a resource that is created, managed, and controlled by the operating system kernel.

User programs running in user space cannot directly access hardware or core system resources. Instead, they request services from the kernel, which internally creates and manages these resources as Kernel Objects.


## 🐧 Introduction
Kernel objects are **fundamental data structures maintained by the operating system kernel to represent system resources**. They provide a structured way for the kernel to manage entities such as:

* Processes
* Threads
* Files
* Memory
* Synchronization primitives

A **kernel module** is a small piece of code that **runs inside the Linux kernel and dynamically extends its functionality**. Unlike normal programs, **kernel modules** operate in kernel space and can be **loaded or unloaded at runtime without rebooting the system.**


## 🧠 Kernel Objects in Memory

A kernel object is essentially a **block of memory (data structure)** allocated inside **kernel space**. This memory structure represents a specific system resource such as:

* File
* Network socket
* Process
* Thread

Since these **objects exist in kernel space, user programs cannot directly access them**. If a program attempts to read or write kernel memory directly, the operating system will terminate the program with a **Segmentation Fault.**


## 🔗 Interaction Between User Space and Kernel Space
Because user programs cannot directly interact with kernel memory, they use an indirect reference:

* **Handle** → Windows systems
* **File Descriptor (FD)** → Linux systems

These are simply **integers that reference kernel objects** maintained by the kernel.
```
User Space                                   Kernel Space
-----------                                  -----------------

Handle / File Descriptor  --------->          Kernel Object
                                              ├─ Reference Count
                                              ├─ Security Descriptor
                                              └─ Type-Specific Data
```

## 🔌 Common Types of Kernel Objects
Almost everything used in system programming is backed by kernel objects.

**1. Synchronization Objects**<br>
Used to coordinate execution between processes or threads.
Examples:
* `Mutex`
* `Semaphore`
* `Condition Variable`
* `Event`

**2. Process and Thread Objects**<br>
Used to manage execution units in the operating system.
Examples:
* `Process Control Block (PCB)`
* `Thread Control Block (TCB)`

**3. File Objects**<br>
Represents open file resources and I/O streams.
Examples:
* `File Objects`
* `Pipe Objects`
* `Socket Objects`


**4. Memory Objects**<br>
Used for managing memory mapping and shared memory.
Examples:
* `Memory Mapped Files`
* `Shared Memory`


**5. IPC Objects**<br>
Used for communication between processes.
Examples:
* `Message Queues`
* `Shared Memory Segments`


### 📊 Reference Counting
Every kernel object maintains a **reference count**.

* **Each handle or file descriptor** pointing to the object increments the count.
* When a reference is released, the count is decremented.
* The **kernel destroys the object only when the reference count reaches zero**.

This mechanism **ensures safe memory management and prevents premature deletion of active resources**.


### 🔒 Security Descriptor
Every kernel object also contains a **security descriptor** that defines **who is allowed to access the object and what operations they can perform**.

* It contains **access control information** for the kernel object.
* The operating system checks this descriptor whenever a process tries to access the object.
* If the process does not have the required permission, the kernel **denies access**.

Typical information inside a security descriptor may include:
* **Owner** → The user or process that created the object
* **Access Control List (ACL)** → List of permissions for users or processes
* **Permission Types** → Read, Write, Execute, or Full Control

This mechanism ensures that system resources are protected from unauthorized access and maintains system security and stability.


## 📟 Device Drivers
Modules are piece of codes that can be loaded and unloaded into the kernel upon demand. They extend the functionality of the kernel without the need to reboot the system. One type of modules is **`device_drivers`**, that allows **kernels to access hardware connected to the system**. Without the modules, we have to build a monolithic kernel and add the new functionality directly into the kernel image. Besides having larger kernels, this has a disadvantage of requiring us to rebuild and reboot the kernel every time we want to add new functionality.


## 🔄 Kernel Space v/s User Space
Linux operates in two execution domains: **User Mode and Kernel Mode**.

User Space provides a restricted and safe environment for applications. Programs rely heavily on standard libraries such as `<stdio.h>` and `<stdlib.h>` to perform operations like input/output and memory allocation.

In contrast, Kernel Space has direct access to hardware resources and core system components. It is self-contained and cannot rely on user-space libraries.

Therefore, standard functions like:
* `printf()`
* `malloc()`
* `free()`

cannot be used inside kernel modules. Instead, the kernel provides its own internal functions:

| User Space Function | Kernel Space Equivalent |
|---------------------|-------------------------|
| `printf()`          | `printk()`              |
| `malloc()`          | `kmalloc()`             |
| `free()`            | `kfree()`               |

**These kernel-specific functions are designed to work safely within the kernel environment.**

### ⚠️ Consequences of Errors
Because of the difference in privilege levels, programming mistakes behave very differently in user space and kernel space.

#### **User Space Errors**
If a user program tries to access invalid memory (for example, dereferencing a `NULL` pointer), the kernel's memory manager detects the violation and terminates the program by raising a Segmentation Fault.
This prevents the rest of the system from being affected.

#### **Kernel Space Errors**
If a kernel module dereferences a `NULL` pointer or corrupts memory, there is no higher authority to recover from the error, since the kernel itself is the highest privilege level.

As a result:

* The kernel may crash
* The system may freeze
* A kernel panic may occur
* The system usually requires a reboot


## 🧪 How Do Modules Get Into the Kernel?
The linux kernel follows a monolithic but modular design. The core of the kernel runs in one big block, but we can **load and unload the functionality dynamically at runtime without rebooting**. These are called **"Kernel Modules"**

```text
User Space                                                      Kernel Space
-----------------------                                         -----------------------

insmod / lsmod / rmmod                syscalls                  Core Kernel       Loaded Modules
(userspace tools)              --------------------->                            (live in kernel)
```

### `.ko` file
.ko (kernel object) is a compiled binary form of kernel module. It contains compiled kernel space code.

```text
Normal Execution                              Kernel Module Execution
----------------                              -----------------------

Hello.c                                       Hello.c
   |                                             |
Hello.i                                       Hello.i
   |                                             |
Hello.s                                       Hello.s
   |                                             |
Hello.o                                       Hello.o
                                                |
                                             Hello.ko
```

* When we compile a user-space program, we get an executable or an `.o` object file. But when we compile a kernel module, we get a `.ko` file.
* It is a specially designed formatted ELC (Executable and Linkable format file). It contains our compiled c code, but not a standalone executable. It locks the `main()` function.
* Like a dynamic library (`.so`), a `.ko` file contains unresolved symbols (like `printk()`). It relies on the kernel's internal linker to connect these dots at the exact moment the module is loaded into the memory.

**ELF sections in the `.ko` file:**
```
.text          --------->    Actual code
.data          --------->    Initialized variables
.bss           --------->    Uninitialized variables
.init.text     --------->    module_init() code
.exit.text     --------->    module_exit() code
.versions      --------->    Kernel version it was built for
.modinfo       --------->    Metadata  (author, license, params)
.symtable      --------->    Symbol table for linking
```


<img width="1308" height="679" alt="image" src="https://github.com/user-attachments/assets/78c608d8-a749-41e1-a8ff-b17082d88a29" />



Since we are loading these codes at runtime and they are not the part of official linux kernel, these are called as _loadable kernel modules_ that are different from the _base kernel_. Base kernels are located in the `/boot` directory and are always loaded when we boot our machine, wherease lkm's are loaded after the kernel get's loaded.

### 📄 Kernel Modules Structure

consider the following code snippet,
```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ritesh Jillewad");
MODULE_DESCRIPTION("First kernel module");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye");
}

module_init(hello_init);
module_exit(hello_exit);
```

**Note:** Kernel modules must have at least two functions defined:

* **Initialization Function** – `init_module()`  
  This function is executed when the module is **loaded into the kernel**. It is used to perform setup tasks such as initializing data structures or registering devices.

* **Cleanup Function** – `cleanup_module()`  
  This function is executed when the module is **removed from the kernel**. It is used to release allocated resources and perform necessary cleanup operations.


### Header Files

1. **`<linux/module.h>`**:
   * This is the core header for loadable kernel modules. It provides us macros and functions used by the modules. It provides definitions for `MODULE_LICENSE`, `MODULE_AUTHOR`, `MODULE_DESCRIPTION`.
   * It includes declerations related to the module initializations and cleanups, i.e `module_init()` and `module_exit()` helpers.
   * Without these headers, kernel won't understand our code as a module

2. **`<linux/kernel.h>`**:
   * This provides common kernel utilities and macros. It provides functions such as `printk()` decleration (kernel logging function), and log-level macros such as `KERN_INFO`, `KERN_ERR`, etc.

3. **`<linux/init.h>`**:
   * It provides macros used for initialization and cleanup sections. It provides: `_inti` and `_exit` annotations.
   * These annotations tell the kernel build system how to place the code in memory and how it can be discarded after the use.


### Modules

1. **`MODULE_LICENSE("GPL")`**:
   * This declares the module's license. If we don't specify a compatible licence (commonly GPL), the kernel may mark itself as **"tainted"** when we try to load the module.
   * Tainted kernel means "a non-standard/possibly propietary module is loaded", so kernel developers may refuse bug reports.
   * Common values:
     * GPL
     * Dual BSD/GPL
    
2. **`MODULE_AUTHOR("Ritesh Jillewad")`**:
   * Stores the author name in module info.

3. **`MODULE_DESCRIPTION(...)`**:
   * Stores short description shown in the modinfo.
   * This section stores "module's metadata macros". These are not normal c statements, they are the macros that stores metadata inside the `.ko` files

### Module Loading Functions

1. **`static int hello_init(void)`**:
   * Static indicates that the scope is only within this file. So this file cannot be accessed or called by another files.
   * `return type`: int (the kernel expects the init function to return either success or failure).
     * if 0: Module loads
     * if non-zero: Module loading failed


2. **`__init` annotation**:
   * __init is a macro that marks this function as initialization code. It means kernel can place this function in special memory section (init section). After the module is loaded successfully, kernel may free/discard this to save the RAM.
  

3. **`printk(KERN_INFO "....")`**:
   * `printk()` is kernel equivalent of `printf()`, but it prints into the kernel log buffer, not to our terminal directly. `printk()` will not print anything on console, but will log the message in `/var/log/kern.log`, so it is used to debug the kernel modules.
   * There are 8 possible log-level strings, defined in headers.
     
     ```text
     KERN_EMERG:  Used for emergency messages
     KERN_ALERT:  Situation requiring immediate action
     KERN_CRIT:   Critical conditions (hardware or software failures)
     KERN_ERR:    Used to report error conditions (used by device drivers)
     KERN_INFO:   Informational messages
     ```
     So we we use the the kernel logger function, it means write an INFO log line into the kernel logs when the module loads.


### Module Unloading Functions

1. **`static void hello_exit(void)`**:
   * This function runs when the module is removed. Return type is void, as unload does not fall in the noraml flow.
   * We must ensure that the cleanup is correct.

2. **`_exit annotation`**:
   * It marks this function as "exit code". For the built-in kernel code, this annotation is discarded (as built-in code isn't unloadable).

3. **Cleanup responsibility**:
   * In real modules, we must free everything we allocated inside the `init`. ex: free memory, unregister devices, stop the kernel threads, etc.
   * In this hello module, only logs are printed, so not special cleanup is required.
  

### Function Registration
If we have used user-defined names, i.e instead of `init_module` and `clean_module`, we need to register it.
  
  
















