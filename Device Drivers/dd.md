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
Ex:
```bash
mknod /dev/LSP c 101 0
```
This creates a character device, whose major number is 101 and minor number is 0. (minor numbers must be in range of 0 to 255).

To view the newly created device node we can use `ls -l /dev`.

Once the device node is created using `mknod`, the special device files remains unless it is explicitly deleted. Device files can be removed using the `rm` command, just like regular files.
```bash
rm <device_file>
```
Ex:
```bash
sudo rm /dev/LSP
```


## 🔄 Complete Lifecycle of a Character Device Driver
Let us understand the **complete lifecycle of a character device driver**, from loading the driver to interacting with the device and finally unloading it.

### 1. Loading the Driver
A character device driver is loaded into the kernel using:
```
insmod mydriver.ko
```
This inserts the kernel module `(.ko file)` into the running kernel.

### 2. Internal Steps Performed by the Kernel
Once the module is loaded, the following steps occur internally:

#### 1. Module Initialization
The kernel calls the driver's initialization function (`module_init`)

#### 2. Device Number Allocation
The driver allocates a major and minor number using functions such as:
* `alloc_chrdev_region()`
* `register_chrdev_region()`

#### 3. Character Device Structure Initialization
The driver initializes the `cdev` structure using:
```
cdev_init()
```

#### 4. Registering the Device with the Kernel
The driver registers the character device with the kernel using:
```
cdev_add()
```

#### 5. Device File Creation
A device node is created in `/dev` either:
* Manually using `mknod`, or
* Automatically using `udev`


### 3. User Interaction with the Device
Once the device file exists, user-space programs can interact with the device using standard system calls:
```
open()
read()
write()
close()
```
These system calls are routed to the corresponding driver functions defined in `file_operations`.


### 4. Removing the Driver
When the driver is no longer needed, it can be removed using:
```
rmmod mydriver
```
The kernel then calls the cleanup function (`module_exit`), which performs:

* `cdev_del()` → removes the device from the kernel
* `unregister_chrdev_region()` → releases device numbers
* Frees allocated resources


```
insmod mydriver.ko
      │
      ▼
module_init()
      │
      ▼
Allocate Major/Minor Numbers
      │
      ▼
cdev_init()
      │
      ▼
cdev_add()
      │
      ▼
Create Device File (/dev)
      │
      ▼
User → open/read/write
      │
      ▼
rmmod mydriver
      │
      ▼
module_exit() → cleanup
```

## 📦 Detailed Explanation of Steps

### **Step 1) Module Initialization**
* When we run teh `insmod mydriver.ko`, the kernel calls our driver's `init` function. This is the entry point of our driver.
* It acts as the `main()` function for the kernel modules.
Ex:
```c
#include <linux/init.h>                                                      // __init, __exit
#include <linux/module.h>                                                    // modules, macros
#include <linux/kernel.h>                                                    // printk, KERN_INFO, KERN_ALERT
#include <linux/uaccess.h>                                                   // copy_to_user(), copy_from_user()             
#include <linux/fs.h>                                                        // register_chrdev, file_operations, inodes

static int __init mydriver_init(void)
{
    printk(KERN_INFO "mydriver: Module loaded successfully\n");
    return 0;
}

static void __exit mydriver_exit(void)
{
    printk(KERN_INFO "mydriver: Module removed successfully\n");
}

module_init(mydriver_init);                                                  // tells the kernel to call this function on load
module_exit(mydriver_exit);                                                  // tells the kernel to call this function on unload
```

The macros `module_init()`, and `module_exit()`, simply registers our functions with the kernel. The kernel does not know anything about our driver, until this runs

### **Step 2) Device Number Allocation**
Before our drivers can do anything, it needs a device number (major-minor pair). The major number is how the kernel routes requests to our driver.
```c
majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
```
we made use of:
```c
register_chrdev(unsigned int major, const char *name, const struct file_operations *fops);
```
where,
* `major`: The desired major number. If 0 is passed, the kernel dynamically allocates an available major number
* `name`: Name for device that will appear in the `/proc/device` list.
* `fops`: Pointer to the driver's `struct file_operations`, that defines the driver functions for operations like `read`, `write`, `open`, and `release`.

Internally the kernel maintains a table (`chrdevs[]`) indexed by the major number. This call inserts out `fops` into that table. When any process opens the file with our major number, the kernel finds our `fops` through this table.

### **Step 3) `cdev` Registration**
* `dev_t` is just a number. The kernel still doesn't know what to do when that device is accessed. So we must create a `cdev`(character device) object and tell "here are my file operations", done through the `file_operations` struct (contains `read`/`write` functions).
```c
static struct file_operations fops = {
      .owner = THIS_MODULE,
      .open = dev_open,
      .read = dev_read,
      .write = dev_write,
      .release = dev_release,
};
```
now,
```c
cdev_init(&my_cdev, &fops);                        // binds fops to cdev
my_cdev.owner = THIS_MODULE;                      

cdev_add(&my_cdev, dev_num, 1);                    // register with kernel (device name, device number, number of devices)
```
now the kernel knows:
```
Major number      ---------->      my_cdev      ---------->      fops
```
so, when someone access this device number, we call the functions in the `fops`. But `/dev/mydevice` still does not exists. A user still cannot see it or access it.

### **Step 4) Device File Creation**
* Historically, we had to create device file using the `mknod /dev/my_device c 240 0` in the terminal to create portal. We can do it automatically by creating a class and device, and `udev` (userspace `/dev`. dynamic manager for linux, responsible to manage device nodes in `/dev` by creating or removing them when hardware is added or removed).
* The above command creates an entry in `/sys/class/CLASS_NAME/.`
ex:
```c
static struct class *charClass = NULL;
charClass = class_create(CLASS_NAME);

static struct device *charDevice = NULL;
charDevice = device_create(charClass, NULL, MKDEV(majorNo, 0), NULL, DEVICE_NAME);
```
where, `MKDEV(major, minor)` -> Combines major and minor number into single `dev_t` value. 

**Note:** After this, `udev` sees the event and automatically creates `/dev/mydevice`, **now we can see the device in `ls -l /dev/mydevice`**

#### `udev`
`udev` is a device manager for the Linux kernel that automatically creates and manages device files in the /dev directory. When hardware devices are connected, removed, or detected, `udev` dynamically creates or removes the corresponding device nodes.

### **Step 5) File Operations**
This is where the real work happens, when a user process calls `open()`, `read()`, `write()` on `dev/mydevice`, the kernel calls our corrosponding function from the `fops`. `struct file_operations` is a data structure in the Linux kernel that **defines how a device driver handles file-related operations such as opening, reading, writing, and closing a device.** Since Linux follows the principle “everything is a file”, devices are accessed through device files in `/dev`. When a user program performs operations like `open()`, `read()`, or `write()` on a device file, the kernel calls the corresponding functions defined in the `file_operations` structure of the device driver.

The structure is defined in the `#include <linux/fs.h>`.

Ex:
```c
struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .read = my_read,
    .write = my_write,
    .release = my_close,
};
```
Here each field points to a **function implemented inside the driver**. Common functions implemented inside the `file_operations` structure is:
```text
open                Called when the device file is opened.
read                Called when data is read from the device.  
write               Called when data is written to the device.
realease            Called when device file is closed.
unlocked_ioctl      Handles device-specific control operations
```

#### A) `open()`:
The `open()` function in a device driver is called whenever a user-space program opens the device file using the `open()` system call.
```c
int fd = open("/dev/myDevice", O_RDWR);
```
When this happens, the Linux kernel invokes the **driver’s `open()` function defined in the `file_operations` structure.**

**Function Prototype:**
```c
int open(struct inode *inode, struct file *file);
```
* `struct inode *inode`: Represents the inode structure of the device file in the filesystem. In Linux, every file (including device files in `/dev`) has an inode, which stores metadata about that file. The driver can use the `inode` structure to **identify the device being accessed.** For example, the driver can extract the `major` and `minor` numbers, if the driver controls multiple devices, the `minor` number helps determine which device instance is being opened.
* `struct file *file`: Represents the file structure associated with the opened file descriptor. **It represents the specific instance of the opened file.** The driver uses this structure to maintain information specific to that open instance. Multiple processes may open the same device file, and each will have its own struct file instance.

**Flow**:
```
User Program
      │
      ▼
open("/dev/mydevice")
      │
      ▼
Kernel
      │
      ▼
Driver open(struct inode *, struct file *)
```

**Typical `open()` implementation**
```c
static int dev_open(struct inode *inodep, struct file *filep)
{
      noOpens++;
      printk(KERN_INFO "Device opened %d times!\n", noOpens);
      return 0;
}
```

#### B) `release()`:
The `release()` function in a Linux device driver is called when a process **closes the device file**. It is the **counterpart of the `open()` function** and is executed when the user program calls:
```c
close(fd)
```
When this happens, the Linux kernel **invokes the driver's `release()` function** defined in the `file_operations` structure.

**Function Prototype:**
```c
int release(struct inode *inode, struct file *file);
```
* `struct inode *inode`: Represents the inode of the device file. It can be used to identify the device (major/minor number).
* `struct file *file`: Represents the opened file instance. Used to access driver-specific data stored during `open()`. 

**Flow**:
```
User Program
      │
      ▼
close(fd)
      │
      ▼
Kernel
      │
      ▼
Driver release(struct inode *, struct file *)
```

**Typical `release()` implementation**
```c
static int dev_release(struct inode *inodep, struct file *filep)
{
      printk(KERN_INFO "Device closed successfully!\n")
      return 0;
}
```


#### C) `read()`:
The `read()` function in a Linux device driver is called when a user-space program attempts to **read data from the device file**. This happens when the program executes the `read()` system call.
```c
read(fd, buffer, size);
```
When this system call is executed, the Linux kernel invokes the driver's `read()` function defined in the `file_operations` structure.

**Function Prototype:**
```c
ssize_t read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
```
* `struct file *file`: Represents the open file instance. Allows driver to access device-specific data.
* `char __user *buf`: Pointer to user-space buffer. Data will be copied from the kernel to this buffer.
* `size_t count`: Number of bytes requested from the user. Maximum number of bytes the driver should send
* `loff_t *ppos`: File offset pointer. Tracks the current read position.

**How data transfer happens?**
Since kernel space cannot directly access the user-space memory (security reasons), the driver must use special helper functions such as:
```c
copy_to_user(void __user *to, const void *from, unsigned long n);
```
**It copies data from kernel space to user space**. Since the memory is divided into user and kernel space for security and memory protection. If a user could directly access the kernel memory, it could crash the system, modify critical kernel data, so it does not allow direct pointer access between the user and kernel memory.

**Typical `read()` implementation**
```c
static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, off_t *offset)
{
      char data[] = "Hello from kernel\n";
      int len = strlen(data);

      copy_to_user(buf, data, len);                  // buf -> user buffer(dest)  data -> kernel buffer(src)

      printk(KERN_INFO "Data read from device\n");

      return len;                                    // returns the bytes read
}
```
The `read()` function **allows user-space programs to retrieve data from a device by copying data from kernel space to user space.**

**Execution flow:**
```text
User Program
      │
      ▼
read(fd, buffer, size)
      │
      ▼
Kernel
      │
      ▼
file_operations.read
      │
      ▼
Driver read() function
      │
      ▼
Data copied from kernel buffer to user
```

#### D) `write()`:
The `write()` function in a Linux device driver is called when a user-space program attempts to **send data to the device**. This happens when the program executes the `write()` system call.
```c
write(fd, buffer, size);
```
When this system call is executed, the Linux kernel invokes the driver's `write()` function defined in the `file_operations` structure.

**Function Prototype:**
```c
ssize_t write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
```
* `struct file *file`: Represents the open file instance. Allows the driver to access device-specific data.
* `const char __user`: Pointer to user-space buffer. Data will be copied from user-space to kernel-space.
* `size_t count`: Number of bytes send by the user. Maximum number of bytes the driver should receive.
* `loff_t *ppos`: File offset pointer. Tracks the current write position


**How Data Transfer Happens**
The kernel cannot directly access user-space memory. Therefore, drivers must use helper functions such as:
```c
copy_from_user(const void *to, const void __user *from, int n);
```
This function safely copies data from user space to kernel space. User space programs are untrusted, as users may pass invalid pointers, pass NULL, pass malicious memory, so kernel must validate everything before copying. `__user` is special annotation that tells kernel, this pointer belongs to user.


**Typical `write()` implementation:**
```c
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    char kernel_buffer[100];

    copy_from_user(kernel_buffer, buf, count);

    printk(KERN_INFO "Data received from user: %s\n", kernel_buffer);

    return count;
}
```

**Execution Flow:**
```text
User Program
      │
      ▼
write(fd, buffer, size)
      │
      ▼
Kernel
      │
      ▼
file_operations.write
      │
      ▼
Driver write() function
      │
      ▼
Data copied from user buffer to kernel
```

### **Step 6) Module exit cleanup**
When we run the command `mydriver`, the kernel calls out the `exit` function. We must undo everything we did inside `init` in reverse order. Failing to do so may cause memory leaks and the kernel may panic.
```c
static void __exit char_exit(void)
{
      // Removing the device file (udev will delete /dev/myDevice)
      device_destroy(charClass, MKDEV(majorNumber, 0));

      // Destroy the class
      class_destroy(charClass);

      // Unregister the cdev
      unregister_chrdev(majorNumber, DEVICE_NAME);

      // Release the device number
      printk(KERN_INFO "Driver unloaded successfully!\n");
}
```
If any of the above step is skipped, the next `insmod` may fail or we may corrupt the kernel data structure.


### 💡 Concept Overview

| Concept | What it is | What it does |
|--------|------------|--------------|
| **dev_t** | A data type used by the Linux kernel to store device numbers | Holds the **major and minor numbers** that uniquely identify a device |
| **alloc_chrdev_region()** | Kernel function used to dynamically allocate device numbers | Assigns a **major number and a range of minor numbers** for a character device driver |
| **cdev** | Kernel structure representing a **character device** | Connects the device number with the **driver’s file operations** so the kernel knows how to handle device requests |
| **file_operations** | A structure containing function pointers for device operations | Defines how the driver handles system calls like **open(), read(), write(), and release()** |
| **class_create() + device_create()** | Kernel functions used for device registration | Creates a **device class and device node**, allowing `udev` to automatically generate the device file in `/dev` |
| **copy_to_user() / copy_from_user()** | Kernel helper functions for memory transfer | Safely copies data between **kernel space and user space** |
| **exit cleanup** | Cleanup operations performed when a driver is removed | Frees allocated resources using functions like **cdev_del(), unregister_chrdev_region(), and device_destroy()** |


### 🧠 Complete Flow
```text
insmod mydriver.ko
|
|__ mydriver_init()
|      |
|      |__ alloc_chrdev_region()            (reserves (major, minor) /proc/devices shows entry)
|      |
|      |__ cdev_init() + cdev_add()         (connects fops to device number, kernel can now route calls)
|      |
|      |__ class_create()                   (creates /sys/class/mydriver_class)
|      |      
|      |__ device_create()                  (udev creates /dev/mydevice)
|
|
|      (driver is now live and usable)
|
|
|
|______ user calls open("/dev/mydevice");   (mydriver_open())
|______ user calls read(fd, buf, n);        (mydriver_read())
|______ user calls write(fd, buf, n);       (mydriver_write())
|______ user calls close(fd);               (mydriver_release())
|
|
|
|
rmmod mydriver.ko
|
|______ mydriver_exit()
            |
            |__ device_destroy()            (udev removes /dev/mydevice)
            |__ class_destroy()             (removes /sys/class entry)
            |__ cdev_del()                  (unlinks fops from device number)
            |__ unregister_chrdev_region()  (releases major/minor number)
```





