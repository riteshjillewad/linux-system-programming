# File Subsystem
This section of the repository covers the fundamental concepts and practical implementation of the File Subsystem in Linux. 
It focuses on how user-space programs interact with the kernel to perform file and directory operations using low-level system calls.

## 📌 Core Concepts
- **File I/O:** Performing basic operations like opening, reading, writing, and closing files using system calls rather than standard library functions.
- **File Metadata:** Accessing and interpreting file information such as inode numbers, sizes, permissions, and types (regular, directory, symbolic link, etc.).
- **Directory Management:** Navigating the file system, listing directory contents, and creating or removing directories.
- **Offset Control:** Managing the file offset (cursor) to perform non-sequential reads and writes.
- **Data Integrity:** Ensuring data is physically written to the disk using synchronization system calls.

## 🛠️ System Calls and Functions
The following table summarizes the key file subsystem system calls utilized in this project:

| Function | Type | Description |
|---------|------|-------------|
| `open` | System Call | Opens or creates a file, returning a file descriptor (fd) for subsequent operations. |
| `read` | System Call | Reads a specified number of bytes from an open file descriptor into a buffer. |
| `write` | System Call | Writes data from a buffer to an open file descriptor. |
| `close` | System Call | Closes an open file descriptor, releasing the resource back to the system. |
| `creat` | System Call | Creates a new file or overwrites an existing one; equivalent to `open` with `O_CREAT | O_WRONLY | O_TRUNC`. |
| `stat` / `lstat` | System Call | Retrieves file metadata (inode, size, type, permissions) without opening the file. |
| `access` | System Call | Checks a process's permissions for a file (existence, read, write, or execute). |
| `lseek` | System Call | Changes the current file offset to a specific position for random access. |
| `pread` / `pwrite` | System Call | Performs atomic I/O at a specific offset without changing the global file offset. |
| `dup` / `dup2` | System Call | Duplicates an existing file descriptor, often used for I/O redirection. |
| `mkdir` / `rmdir` | System Call | Creates a new directory or removes an empty one. |
| `opendir` / `readdir` | Library | Opens a directory stream and reads entries (files/subdirectories) sequentially. |
| `closedir` | Library | Closes an open directory stream. |
| `link` / `symlink` | System Call | Creates a hard link or a symbolic (soft) link to an existing file. |
| `unlink` / `remove` | System Call / Library | Deletes a name from the filesystem; if it's the last link, the file is deleted. |
| `rename` | System Call | Renames or moves a file or directory. |
| `truncate` | System Call | Shrinks or extends the size of a file to a specified length. |
| `sync` / `fsync` | System Call | Flushes kernel buffers to disk to ensure data persistence. |

### 📂 1️⃣ File I/O System Calls

| Function | Description |
|---------|-------------|
| `open` | Opens or creates a file and returns a file descriptor. |
| `read` | Reads bytes from a file descriptor into a buffer. |
| `write` | Writes bytes from a buffer to a file descriptor. |
| `close` | Closes an open file descriptor. |
| `lseek` | Moves the file offset for random access. |
| `pread` / `pwrite` | Performs offset-based I/O without changing file offset. |
| `dup` / `dup2` | Duplicates a file descriptor. |

### 📁 2️⃣ Directory Management

| Function | Type | Description |
|---------|------|-------------|
| `mkdir` | System Call | Creates a new directory. |
| `rmdir` | System Call | Removes an empty directory. |
| `opendir` | Library | Opens a directory stream. |
| `readdir` | Library | Reads directory entries. |
| `closedir` | Library | Closes a directory stream. |

### 📄 3️⃣ File Metadata & Permissions

| Function | Description |
|---------|-------------|
| `stat` / `lstat` | Retrieves file metadata (inode, size, permissions). |
| `access` | Checks file permissions for a process. |

### 🔗 4️⃣ Links & File Management

| Function | Description |
|---------|-------------|
| `link` | Creates a hard link to a file. |
| `symlink` | Creates a symbolic (soft) link. |
| `unlink` | Removes a file name (deletes file if last link). |
| `rename` | Renames or moves a file/directory. |
| `truncate` | Changes the size of a file. |

### 💾 5️⃣ Data Synchronization

| Function | Description |
|---------|-------------|
| `sync` | Flushes all filesystem buffers to disk. |
| `fsync` | Flushes buffers of a specific file descriptor. |




