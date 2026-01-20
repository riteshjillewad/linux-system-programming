# System V IPC Model

## Background
System V (pronounced "System Five") was a version of Unix released by AT&T in 1983. It introduced a unified IPC framework that became a standard across Unix systems. Before System V, IPC mechanisms were fragmented and inconsistent across different Unix implementations. System V IPC brought three major mechanisms under one coherent model: message queues, semaphores, and shared memory.
This model has been so successful that it remains available in modern Unix-like systems (Linux, BSD, macOS) decades later, even as newer IPC mechanisms have been introduced.

## The Core Philosophy of System V IPC
**System V IPC treats communication mechanisms as persistent kernel objects that exist independently of the processes that create them**. This is fundamentally different from mechanisms like pipes, which disappear when the processes using them terminate.
Think of System V IPC objects as resources managed by the kernel, similar to files. They have identities, permissions, owners, and lifetimes that can outlast the processes that create them. <br>

## IPC Objects
An IPC object is a kernel data structure that represents a **communication resource**.
**- Persistence:** Unlike a Pipe (which vanishes when the process dies), a System V IPC Object is persistent. It lives in the kernel memory until it is explicitly deleted by a user or the system reboots.
**- Scope:** Because they live in the kernel, they are visible to any process on the system, provided the process knows the object's name and has the right keys.

How do process find specific IPC objects? The model makes use of two-step identification system involving *keys* and *identifiers*.

## Keys(`key_t`)
- A key is a 32-bit integer that serves as external name for an IPC object. Just as files have filenames, IPC objects have keys.
- Just as two process can open the same file by knowing it's path, "**two unrelated process can access the same IPC object by knowing it's key**".<br>
#### Keys can be
- **Explicit integers:** You might hardcode a key like 1234 in your programs
- **Generated using ftok():** This function converts a filesystem path and a project ID into a key, providing a semi-unique way to generate keys based on existing files
- **IPC_PRIVATE (value 0):** Creates a private IPC object with a key that cannot be used by other processes to find it

**Note:** The ftok() function is particularly clever. It takes a pathname (like "/tmp/myapp") and a single-byte project identifier and generates a key. Multiple processes can call ftok() with the same parameters to arrive at the same key, allowing them to rendezvous at the same IPC object. We need to keep in mind that the key should be same for the server and the client, so the client and server both should have the same filename. *A clever approach is to use .(root directory)*

## Identifiers(`int`)
- When an IPC object is created or accessed, the kernel returns an identifier (often called an IPC ID or handle). This is an integer that the process uses in subsequent operations on that object. It's similar to a file descriptor.
- The identifier is what you actually use in your program to perform operations. The key is just used during creation or initial access to find or create the object.
- ex: `shmid`, `semid`, `msgid`

### Consider the below workflow
1. Process A creates a message queue with key 5678, and the kernel returns identifier 3
2. Process A uses identifier 3 to send messages
3. Process B wants to access the same queue, so it requests access to the queue with key 5678
4. The kernel returns identifier 7 to Process B (different from Process A's identifier, but referring to the same underlying object)
5. Process B uses identifier 7 to receive messages from the same queue

## Permission and Authentication System
System V IPC implements a permission model very similar to Unix file permissions, which makes it familiar to Unix programmers.

### The `ipc_perm` Structure:
Every IPC object has an associated `ipc_perm` structure containing information used to determine permissions granted on IPC objects

```
struct ipc_perm
{
    key_t              key;                  // Key
    uid_t              uid;                  // Owner's user ID
    gid_t              gid;                  // Owner's group ID
    uid_t              cuid;                 // Creator's user ID
    gid_t              cgid;                 // Creator's group ID
    unsigned short     mode;                 // Permissions (read, write)
    unsigned short     seq;                  // Sequence number
};
```
- The sequence number is internally used by kernel to generate unique identifiers.
- There are no execute bits—execution doesn't apply to IPC objects. "Read" generally means receiving/reading data, while "write" means sending/writing data or modifying the object's state.

> Superuser (root, UID 0) typically bypasses these checks and can access any IPC object.

## Associated IPC data structures
The kernel maintains an associated data structure for each instance of a System V IPC Object. The form of this data structure varies according to IPC mechanism (pipes, message queue, semaphores or shared memory) and is defined in their corrosponding header files for IPC mechanisms. The associated data sructure for an IPC object is initialized when an object is created via appropriate system call

* Message queue    -> msg table      -> sys/msg.h
* Shared memory    -> shm table      -> sys/shm.h
* Semaphores       -> sem table      -> sys/sem.h

#### Problems with System V IPC Objects
- System V IPC objects exist in kernel memory and persist until explicitly removed or the system reboots. They are not automatically cleaned up when processes terminate.
- If a process creates a message queue and crashes without cleaning up, that queue remains in the system, consuming kernel resources. This can lead to resource exhaustion over time if not carefully managed.
- Administrators must sometimes manually remove orphaned IPC objects using commands like `ipcrm`. The ipcs command lists all System V IPC objects on the system, showing their keys, IDs, owners, and permissions.
