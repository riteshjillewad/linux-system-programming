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













