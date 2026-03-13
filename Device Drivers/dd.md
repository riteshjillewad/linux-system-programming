# 🔧 Device Drivers

## 📖 Introduction

Device drivers are specialized piece of softwares that acts as **translators between the operating system and hardware device**. Since the Operating system can't possibly know the inner workings of every piece of hardware ever made, drivers fill that gap.

**Device drivers are kernel-level software components that allows the operating system to communicate with the hardware devices.** It acts as translators between:
- **User-space applications**
- **The operating system kernel**
- **Physical hardware devices**

**Note: Without device drivers, the operating system cannot interact with the hardware.**

## 🧠 Driver Architecture

<img width="870" height="523" alt="image" src="https://github.com/user-attachments/assets/22ecc5ab-956a-4d3c-ab88-6bed1f0d62b4" />

Hardware devices like the printers, GPU's, keyboards or network cards, all speak their own language (specific commands, registers, protocols). The operating system speaks a general, abstract language, so the device drivers bridge this mismatch. 

As the golden rule of UNIX states, **"Everything is a file."**

When we plug in a mouse, keyboard, or hard drive, Linux represents that physical hardware as **special device files** inside the `/dev` (device) directory. Since these devices are treated as files, user-space programs do not need to know how the hardware works internally. Instead, they interact with devices using standard system calls such as:
```
open()    ------------->    Open the device
read()    ------------->    Read from the device (ex: get mouse coordinates)
write()   ------------->    Write to the device (ex: send audio signals to the speaker)
close()   ------------->    Close the device
```
In simple terms, device drivers enitre job is to sit in the middle, catch all these `read()`, `write()`, requests and translate them into the electrical signals the hardware expects.


## ⚙️ Kernel Interaction
Drivers typicall operates in the **"kernel space"** (or very close to it), which gives them priveleged access to the hardware. This is also why a buggy driver can crash out entire operating system, that is running with the elevated privileges right alongside the kernel itself.

<img width="1466" height="647" alt="image" src="https://github.com/user-attachments/assets/ff61b2bb-4ae0-4b8d-b6cb-8215812d77ae" />

We must ensure that the code we write for the kernel modules & device drivers must be **error free**, otherwise it might **crash the operating system.**. Due to this, some mordern operating systems designs, push the drivers into the user space for safety.

When we use the command `ls -l /dev`. It displays the types of files in the device folder. These are the device files (device nodes). A device is a `.ko` code that runs inside the kernel space and controls the hardware. Files in `/dev` are interfaces to drivers, not the drivers themselves. They are special files created by the kernel so the user program can talk to the drivers.

```text

User Programs  ---------->  /dev Device File  ---------->  Device Driver  ---------->  Hardware

```
`/dev` device files are the files that communicate with the disk driver, which then communicates with the hardware.

When we use the command: `ls -l /dev`, we get the following output:
```text
crw-r--r---  1  root  root  10,235
.            .   .     .      .
.            .   .     .      .
.            .   .     .      .
.            .   .     .      .
drwxr-xr-x   2  root  root  10,234
lrwxr-xr-x   1  root  root  38,400    cdrom -> sro
```
Abbrevations:
* `l`: Symbolic link (shortcut pointing to another `/dev` file)
* `d`: Directory (group of device files)
* `c`: Character device (character device interface)
* `d`: Block device (block device interface)

## 💾 Types of Device Drivers
There are mainly three types of device drivers

### 1️⃣ Character Device Drivers
Character device drivers handle devices that transfer data **one character (byte) at a time**. These devices do not support random access and process data sequentially (reading a file from start to end).
Examples of character devices include:

- Keyboards
- Mice
- Serial ports
- Terminals

Character devices typically appear in `/dev` with a **`c` identifier**.

Example
```bash
ls -l /dev/tty
crw-rw-rw- 1 root root 5, 0 /dev/tty
```
When a user program calls the `read(fd, buffer, size)`, the kernel internally calls the driver's `driver_read()` function.

### 2️⃣ Block Device Drivers
Block device drivers manage devices that **store data in fixed-size blocks (512 bytes or 4KB) and support random access to data**. These devices are typically used for storage.

Examples of block devices include:

- Hard disks
- SSDs
- USB drives
- CD/DVD drives

Block devices appear in `/dev` with a **`b` identifier**.

Example
```bash
ls -l /dev/sda
brw-rw---- 1 root disk 8, 0 /dev/sda
```
Internally block devices use: request queues, I/O scheduler, buffer cache, page cache. So data flow direction is:
```
Application  ---------->  Filesystem  ---------->  Block layer  ---------->  Storage hardware
```
Block devices implements functions like `read_block()`, `write_block()` internally.


### 3️⃣ Network Device Drivers
Network device drivers manage network interface hardware and allow the system to communicate over networks. These handle the packet-based communication over a network.

Unlike character and block devices, network devices do not appear as device files in /dev. Instead, they are accessed through the network stack of the kernel.

Examples include:

* Ethernet cards
* Wi-Fi adapters
* Virtual network interfaces

Example network interfaces:
```text
eth0
wlan0
lo
```
These can be viewed using commands like:
```
ip a 
```

## ✅ Devices and Drivers
In Linux system programming, one of the most important types of **special files** are **device files**. These files provide an interface for user-space programs to interact with hardware devices through the kernel.

Unlike regular files, device files do not store data on disk. Instead, operations performed on them are handled by the **corresponding device driver inside the kernel**.

### 📦 What is Device ?
A **device** is any physical or virtual hardware component that the operating system can interact with.

Examples include:

- Keyboard
- GPU
- Printer
- Hard drives / SSDs
- Network interfaces
- Pseudo devices such as `/dev/null`, `/dev/zero`, and `/dev/random`

These devices are represented in Linux as **special files inside the `/dev` directory**, allowing applications to communicate with hardware using standard system calls like `open()`, `read()`, `write()`, and `close()`.

**Devices fall under 3 categories:**
```text
1) Block devices        ------->   Transfers the data in fixed-sized chunks (disks, SSD's)
2) Character devices    ------->   Transfers the data as stream, byte-by-byte (keyboards)
3) Network devices      ------->   Send or recieve packets (ethernet card, WIFI adapter)
```

A Device:
* Does not understand system calls.
* Does not understand our c code or does not directly talk to the user programs.
* It only speaks the hardware-level signals (electrical/protocol-based).
* It understands only bits, interrupts, registers.


### 🧰 What is Driver ?
A **driver** is any software module that knows how to talk to a specific device. It enables the **operating system to communicate with a hardware device**.

Since every hardware device (such as keyboards, disks, GPUs, or printers) has its own communication protocols and control mechanisms, the operating system cannot directly interact with them. A driver acts as an **intermediary layer** that translates generic OS requests into **device-specific commands**.

Ex: Kernel says "I need 512 bytes of data. The device driver translates it into: send 5 volt pulse over pin 3 of PCLE bus, wait 2ms and read the buffer".

When we buy a new piece of hardware, it won't work on linux until a developer writes a device driver (`.ko`) file for it and loads it into kernel space.

#### **Role of a Device Driver**
A driver is responsible for:

- Controlling and managing a hardware device
- Translating OS system calls (`read()`, `write()`, etc.) into hardware instructions
- Handling device-specific operations such as interrupts and I/O requests
- Providing a standardized interface for user-space applications

#### **Relation between Device and Driver (Communication flow)**
Relation is straightforward:

* **Device**: Is the hardware 
* **Driver**: It's voice inside the O.S

```
      User application
            |
       System calls  (`open()`, `read()`, `write()`) 
            |
          Kernel     (acts as standard interface that allows users to acces the device services)
            |
       Device driver (software that knows the device's language)
            |
          Device     (hardware)
```

> A device driver is kernel-level software that acts as an intermediary between the operating system and hardware devices, enabling the OS to control and communicate with hardware.

## 📂 Device Files
Since **"everything is considered as file"** is the core philosophy of UNIX systems, even hardware devices are no exceptions to this rule. **A device file is a special type of file that acts as an interface between the user space and device driver.** Even if it looks like a regular file, it lives in `/dev` folder, but instead of storing data on disk, it allows reading/writing to the hardware.

**Device files (also called device nodes) are special files in Linux that provide a file-based interface to hardware devices. They are usually located in the `/dev` directory.**

Instead of storing data like regular files, device files act as communication endpoints that allow user-space programs to interact with device drivers using standard system calls such as:

* `open()`
* `read()`
* `write()`
* `close()`

**When a program performs an operation on a device file, the request is forwarded to the corresponding device driver inside the kernel, which then interacts with the hardware.**

Standard commands like the `cat`, `cp`, or `echo` can interact with the hardware without any special knowledge.
```bash
cat /dev/sda                                    (read raw data from the disk)
echo "hello" > /dev/tty50                       (sending data to serial port)
```

Device files **do not contain data in it**. Instead it holds **two important identifiers (metadata)** that the kernel uses to route the operations. It is typically of `4 bytes` and **contains two numbers**.

1. **Major number** (solves which driver?)
2. **Minor number** (solves which device?)
3. **Permissions** (who can access the device?)

These numbers help the Linux kernel identify **which driver should handle a device request and which specific device instance is being accessed**.

Device files are special types of inodes(index nodes) that acts as portal into the kernel. When we call `open()` on device file, kernel looks at the major number to find the registered driver, and from that point, our `read()`/`write()` calls go straight through that driver to the hardware.

Command used to create a device file is `mknod`


| Component | Definition | Role |
|-----------|------------|------|
| **Device** | A physical or virtual hardware component | Performs the actual hardware operation |
| **Device Driver** | Kernel-level software that controls the device | Translates OS requests into hardware-specific commands |
| **Device File** | A special file in `/dev` representing the device | Interface used by programs to communicate with the driver |

## 🔢 Major and Minor Numbers

### 🧠 Major Number
The **major number** identifies the **device driver** responsible for handling operations on the device.

When a program performs an operation such as `read()` or `write()` on a device file, the kernel uses the **major number** to determine **which driver should handle the request**.

Example:

```bash
ls -l /dev/null

crw-rw-rw- 1 root root 1, 3 /dev/null
```
- **c**: Character device
- **1**: Major number (identifies the device driver)
- **3**: Minor number (identifies the device instance)


### 🔹 Minor Number
The minor number is used by the device driver to **distinguish between multiple devices it manages**.

For example, a single disk driver may manage multiple disks:

| Device File | Major | Minor | Meaning |
|-------------|-------|-------|--------|
| `/dev/sda` | 8 | 0 | First disk |
| `/dev/sdb` | 8 | 16 | Second disk |

**Both devices use the same driver (major number) but represent different hardware devices (minor numbers).**

```text
User Program
     │
     ▼
Device File (/dev)
     │
     ▼
Kernel reads Major Number
     │
     ▼
Selects Correct Driver
     │
     ▼
Driver uses Minor Number to identify the specific device
```

**Major number identifies the driver, and the minor number identifies the specific device managed by that driver.**

Ex: Imagine there are **5 cars**, and a **driver named X** who is responsible for driving them.

- **Major number** → Identifies the **driver** (who is responsible for operating the cars).
- **Minor number** → Identifies **which specific car** the driver will operate.

So even though the **same driver (major number)** is responsible for all cars, the **minor number specifies which particular car is being used**.

### Flow
Ex:
```c
int fd = open("/dev/sda", O_RDONLY);
read(fd, buffer, 512);
```
Following flow is executed
```
Application calls read()
           |
System calls enter kernel (sys_read)
           |
Virtual Filesystem Layer
- Looks up file, see's it's a device file
- Reads the major number
           |
Kernel finds the registered drive for that major number
           |
Call's drivers .read() function, passing minor number
           |
Driver talks to the actual hardware
           |
Data comes back to our application
```

Virtual filesystem layer is the key. It's an abstraction inside the kernel that makes device files, regular files and network sockets look all the same to applications. We can see that when we call `read()`, it does not directly call hardware it access it through the driver's `read()`.

### 🔄 Flow of Major and Minor Numbers in Device Communication

<img width="1767" height="635" alt="image" src="https://github.com/user-attachments/assets/3d219ec3-78d4-42dc-85db-f3bec95237c9" />

The following steps explain how Linux uses **major and minor numbers** to connect an application with the correct hardware device.

1️⃣ **End User Interaction**  
The process starts when the **end user runs an application program** that needs to interact with a hardware device.

Example:
- Reading data from a disk
- Getting mouse input
- Writing audio to a speaker


2️⃣ **Application Program Request**

The application program makes a **system call** such as:
```c
open()
read()
write()
```
to access a device file inside the `/dev` directory.
```c
open("/dev/mydevice");
```

3️⃣ **Kernel Receives the Request (HAL Layer)**

The request enters the **Linux Kernel**, which acts as a mediator between user-space and hardware.

The kernel reads the **device file metadata**, which contains:

- **Major Number (55)** → identifies the device driver  
- **Minor Number (11)** → identifies the specific device handled by that driver


4️⃣ **Driver Selection using Major Number**

The kernel uses the **major number** to determine **which device driver should handle the request**. Ex: In the diagram
```
Major number = 55 → Driver responsible for that device
```
So the kernel routes the request to the **driver registered with major number 55**.


5️⃣ **Device Identification using Minor Number**

Once the driver receives the request, it uses the **minor number** to identify **which specific device instance should be accessed**. Ex: In the diagram
```
Minor number = 11 → Specific hardware device
```


6️⃣ **Driver Communicates with Hardware**

The device driver then:

- Translates the request into **device-specific commands**
- Sends the appropriate **signals or instructions to the hardware**

Finally, the hardware performs the requested operation and returns the result.


## 🧰 Creating Device Files
Device files (device nodes) can be created manually using the `mknod` command.

The `mknod` command is used to create **special files that represent devices** in the filesystem. These device files act as an interface between **user-space programs and device drivers in the kernel**.

Creating device files requires **superuser (root) privileges**.

The `mknod` command takes **three arguments in addition to the file name being created**:

1. **Device type**
2. **Major number**
3. **Minor number**

Consider the below syntax:

```bash
mknod <device_name> <type> <major_number> <minor_number>
```
```bash
mknod /dev/LSP c 101 0
```













