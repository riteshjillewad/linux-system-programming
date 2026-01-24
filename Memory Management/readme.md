# Memory Management

This section of the repository focuses on the fundamental concepts and practical implementation of memory management in Linux using system calls and standard library functions. It covers dynamic memory allocation, heap management, and memory-mapped files.

## 📌 Core Concepts
- **Heap Management:** Understanding how to grow and shrink the data segment of a process using brk and sbrk.
- **Dynamic Allocation:** Utilizing malloc, calloc, realloc, and free for efficient user-space memory management.
- **Memory Mapping:** Mapping files or devices into memory for high-performance I/O and shared memory communication using mmap.

## 🛠️ System Calls and Functions
The following table summarizes the key memory management functions used in this project:

| Function | Type        | Description |
|---------|-------------|-------------|
| `malloc` | Library     | Allocates a contiguous block of memory of a specified size (in bytes). The memory is uninitialized (contains garbage). |
| `calloc` | Library     | Allocates memory for an array of elements, initializing all bytes to zero. |
| `realloc` | Library    | Changes the size of a previously allocated memory block, moving it if necessary. |
| `free` | Library      | Deallocates a memory block previously allocated by `malloc`, `calloc`, or `realloc` to prevent memory leaks. |
| `brk` | System Call   | Sets the end of the data segment (program break) to a specific address, effectively growing or shrinking the heap. |
| `sbrk` | System Call  | Increments or decrements the program's data space by a specified number of bytes. |
| `mmap` | System Call  | Creates a new mapping in the virtual address space of the calling process, often used to map files directly into RAM. |
| `munmap` | System Call | Deletes the mappings for the specified address range, freeing the associated memory resources. |
| `msync` | System Call | Flushes changes made to an in-memory copy of a file that was mapped using `mmap` back to the disk. |

