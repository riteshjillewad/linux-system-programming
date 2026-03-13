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














