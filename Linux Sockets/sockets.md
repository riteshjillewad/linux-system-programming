# 📡 Linux Socket Programming

Sockets are one of the most versatile and powerful IPC mechanism that allows data to be exchanged between applications, either on the same host(computer) or on different hosts connected by network.

## 🖥️ What are Sockets?
A socket is a communication endpoint between two process.
* One process writed data into a socket.
* Another process reads the data from socket.
* The O.S (kernel) handles everything in between

The term socket comes from the analogy of plugging into a wall socket: we create a socket endpoint and "plug it" to communicate with another socket endpoint.

## ☕ Historical Context
* Sockets were developed at UC Berkley in 1980's as part of BSD UNIX. They were created to provide clean, consistent interface for the TCP/IP networking protocols that were emerging at that time.
* Before sockets, network programming involved dealing with the various low-level protocols details differently for each protocol. The socket abstraction unifies this, providing a single unified API that could work with different protocol families.
* This became standard network programming interface across the UNIX systems, and beyond (windows sockets / winsockets are based on this).

Sockets are part of OS kernel, exposed to user programs via the system calls.
```
User program
    |
Socket API
    |
  Kernel
    |
 Network
```
**In a typical client-server scenario, applications communicate using the sockets as follows:**
* Each application creates a socket. A socket is a "apparatus" that allows communication, and both applications require one.
* The server bind's it's socket to a well-known address(name) so that the client can locate it.

**"Sockets are treated like files", so we can create the sockets using the `socket()` system call, that returns a FD, that can be used to refer socket in subsequent system calls.**
ex:
```
fd = socket(domain, type, protocol);
```

## 🌐 Socket Communication Domains
Sockets operate within different domains or address families. So when we create a socket, we must choose it's family, that decides where it can talk. Sockets exists in a communication domain that determines:
* The method of identifying a socket.
* Range of communication (i.e either between applications on the same host or between applications on different hosts connected via the network).
* Mordern OS supports atleast the following domains.

#### 1. **UNIX Domain Sockets (`AF_UNIX`/`AF_LOCAL`)**
   * **These are used for IPC on same machine**. They use the filesystem path as address.
   * It creates a special file in our disk (`/tmp/mysql.sock`).
   * It is extremly fast and bypass the entire network stack (no TCP/IP overhead).

#### 2. **Internet Domain Sockets (`AF_UNIX`/`AF_LOCAL`)**
   * **These support network communication across machines.**
   * It uses IP address, port numbers.
     * IP address: To find the computer.
     * Port number: To find specific process.
   * It can communicate across networks and the internet.
   * It supports both: TCP and UDP protocols.

   ex:
  ```
    AF_INET    ->  IPV4 Internet Protocols
    AF_INET 6  ->  IPV6 Internet Protocols
  ```

| Domain     | Communication Performed | Communication Between | Address Format | Address Structure |
|------------|------------------------|-----------------------|---------------|------------------|
| AF_UNIX    | Within kernel on same host | Applications on same system | Pathname | `sockaddr_un` |
| AF_INET    | Via IPv4 network | Applications on different hosts | 32-bit IPv4 address + 16-bit port number | `sockaddr_in` |
| AF_INET6   | Via IPv6 network | Applications on different hosts | 128-bit IPv6 address + 16-bit port number | `sockaddr_in6` |

## 🔌 Socket Types
Every socket implementation provides atleast two types of sockets. "Streams" and "Datagrams". They are supported in UNIX and Internet Domains.

#### 1. **Stream Sockets (`SOCK_STREAM`): TCP**
Stream sockets provide reliable, bi-directional, byte-stream communication channel.
* **Connection Oriented:** Must establish connection before data transfer.
* **Reliable:** Data delivery is guranteed in order, no loss.
* **Byte stream:** No message boundaries preserved.
* **Flow control:** Prevents sender from overwhelming reciever.
* **Error detection:** Error detection and recovery.

_Protocol: TCP for internet domain_

ex: File-transfers, HTTP, database connections.

#### 2. **Datagram Sockets (`SOCK_DGRAM`): UCP**
Datagram sockets allows data to be exchanged in the form of messages called "datagrams". With datagrams sockets, message boundaries are preserved, but the data transmission is not reliable. Messages may arrive out of order, be duplicated or not arrive at all.
It does need to be connected

_Protocol: TCP for internet domain_

ex: File-transfers, HTTP, database connections.



| Property                          | Stream Socket (`SOCK_STREAM`) | Datagram Socket (`SOCK_DGRAM`) |
|----------------------------------|-------------------------------|---------------------------------|
| Reliable Delivery?               | Yes                           | No                              |
| Message Boundaries Preserved?    | No                            | Yes                             |
| Connection-Oriented?             | Yes                           | No                              |





  



















