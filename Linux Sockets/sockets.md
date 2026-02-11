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


## ⚡Socket Programming Model
Socket communication follows different modesl depending on the socket types.

<img width="708" height="797" alt="image" src="https://github.com/user-attachments/assets/9b9d7298-bbcc-4d50-acb4-1e198e293616" />

**Flow:**
* Server creates a socket and waits.
* Client creates a socket and connects.
* Data flows in both ways.
* Connection closes.


### 🔀 Client-Server Stream Socket Model

| Server Side | Client Side |
|-------------|-------------|
| 1. `socket()` — Creates a socket | 1. `socket()` — Creates a socket |
| 2. `bind()` — Binds to address (IP + Port / Filesystem path) | 2. `connect()` — Initiates connection to server |
| 3. `listen()` — Marks socket as passive (ready to accept connections) | 3. `send()/recv()` — Exchange data with server (`write()/read()`) |
| 4. `accept()` — Waits for client and accepts connection | 4. `close()` — Closes the connection |
| 5. `send()/recv()` — Exchange data with client (`read()/write()`) |  |
| 6. `close()` — Closes the connection |  |

## 🧵 Core Socket Functions

### Socket Creation
* First step deals with the creation of sockets, that is the basic component for sending or recieving signals between nodes. The `sys/socket.h` header has necessary functions to create sockets in C.

**Syntax:**
```
int socket(int domain, int type, int protocol);
```
where,
1. `domain`: Represents the domain family over which communication will be performed.
   * `AF_UNIX` or `AF_LOCAL`: UNIX domain sockets.
   * `AF_INET`: IPV4 internet sockets.
   * `AF_INET6`: IPV6 internet sockets.

2. `type`: Represents type of communication used in the socket.
   * `SOCK_STREAM`: Stream Socket (TCP-like)
   * `SOCK_DGRAM`: Datagram Socket (UDP-like)
   * `SOCK_RAW`: Raw Socket

3. `protocol`: Protocol to be used in the socket, represented by number.
   * `0`: Let the system choose appropriate protocol for domain/type.
   * `IP_PROTOCOL`, `IPRIO_UDP`: Specific protocols.
   
**Return Value:**
* Socket file descriptor on success, and -1 on error.
ex:
```
// Unix domain stream socket
int sock = socket(AF_UNIX, SOCK_STREAM, 0);

// IPv4 TCP socket
int sock = socket(AF_INET, SOCK_STREAM, 0);

// IPv4 UDP socket
int sock = socket(AF_INET, SOCK_DGRAM, 0);

// IPv6 TCP socket
int sock = socket(AF_INET6, SOCK_STREAM, 0);
```
**Note: The returned socket descriptor is just like the file descriptor. We can use `close()` to close it, or use `read()` and `write()` functions.**

### Binding Socket to an Address
* The `bind()` system call assigns a socket file descriptor with a specific local address and port number.
* Before `bind()`, socket exists, but it has no address, so nobody can reach it. After `bind()` socket is tied to a specific IP address and Port number, so the other process(client) know where to connect.

**Server Side:** <br>
On the server side it is mandatory to `bind()` the socket.

**Client Side:** <br>
It is optional, when a client connects, the OS automatically assigns it a random, unused port (called as the ephemeral port). Clients usually don't care what their own port number is, only care about the server's port.

**Syntax:**
```
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
where,
1. `sockfd`: Socket file descriptor returned from `socket()`.
2. `addr`: Pointer to structure containing the IP address and the port we want to assign to the socket.
3. `addrlen`: Size of the address structure (`sizeof(struct sockaddrr_in)`)

**Return Value:**
* Returns 0 on success, and -1 on error.

#### Struct Address (`sockaddr_in`)
The `bind()` function is generic. It works for UNIX sockets, IPV4, IPV6, so it accepts a generic pointer type(`struct sockaddr *`). However for the internet sockets (IPV4), we rarely use the generic struct directly. We use the IPV4 specific struct (`struct sockaddr_in`), it fills the data and then cast it to generic type.

**Layout:**
```
struct sockaddr_in
{
    short                sin_family;        // Address family
    unsigned short       sin_port;          // Port number
    struct in_addr       sin_addr;          // IP address
    char                 sin_zero[8];       // Padding (to match the generic strucutre)
};
```

**Key Concepts within Bind:**

**A. Byte Ordering (htons)**
Computers store numbers in different orders (Big Endian vs. Little Endian). The Internet, however, has a strict standard: Network Byte Order (Big Endian).
* If you just say `my_addr.sin_port = 8080;`, your computer might store it as 8080, but the network might read it as 36895 (the bytes flipped).
**Solution:** You MUST use `htons()` (Host to Network Short).
```
my_addr.sin_port = htons(8080);                            // Included in the <arpa/inet.h>
```

**B. Bind Address**
There are two options:
* Bind to specific IP: `server_addr.sinaddr = inet_addr("192.168.1.10");`
* Bind to all interface: `server_addr.sin_addr.s_addr = INADDR_ANY;`, It means **"accept connections from any IP address of this machine".**

**Note:** Since `bind()` accepts a generic, so all the address strucutres can be cast to `struct sockaddr *` for function calls. This is how it achieves the socket independence.
ex: since we are using IPV4 address, so in-built strucutre for it is:
```
struct sockaddr_in
{
    sa_family_t        sin_family;
    in_port_t          sin_port;
    struct in_addr     sin_addr;
};
```
so we create the object of this strucutre `struct sockaddr_in serverAddress;`
```
memset(&serverAddress, 0, sizeof(serverAddress));

serverAddress.sin_family = AF_INET;                                // Family
serverAddress.sin_port = htons(8000);                              // Port number
serverAddress.sin_addr.s_addr = INADDR_ANY;                        // Listen on any IP
```

The `serverAddress.sin_addr.s_addr = INADDR_ANY` is derived from the structure:
```
struct in_addr
{
    in_addr_t    s_addr;
};
```

Note:
* Port numbers < 1024 require root privileges (privileged ports)
* INADDR_ANY (0.0.0.0) means bind to all network interfaces
* Use htons() (host to network short) for port numbers to handle byte order
* For Unix sockets, remove the socket file before binding if it exists


### Marking the Socket as Passive
The `listen()` system call marks the socket as passive (i.e it ready to accept the incoming client connections). By default when we create a socket with `socket()`, the kernel assumes it is in active state (like a client that will initiate a call), but `listen()`, flips the switch in OS kernel, that says i am not waiting for anyone, others will call me.

#### **Syntax:**
```
int listen(int sockfd, int backlog);
```
where, 
1. `sockfd`: Socket file descriptor (already bound to an address/port).
2. `backlog`: Length of queue.

#### **Backlog Queue**
When clients try to connect, their connection requests queue up until you accept() them. The backlog parameter specifies how many pending connections can be queued. If the queue fills, new connection attempts are refused. Modern systems often have a maximum backlog limit (e.g., 128 or higher), and specifying larger values gets clamped to the maximum. <br>
**Typical Values:**
* Small servers: 5-10
* Busy servers: 128 or more
* Use SOMAXCONN for system maximum

In short,
    _"It tells the kernel, how many pending connections shoudl i keep on hold, before i start rejecting new callers"_

**How the Kernel handles it:**
* **Client Calls:** A client sends a SYN packet (Connect request).
* **Kernel Queues It:** The OS completes the TCP Handshake (SYN $\to$ SYN-ACK $\to$ ACK) automatically.
* **Ready State:** The connection is now "ESTABLISHED" at the TCP level, but your application hasn't touched it yet. The Kernel puts this completed connection into the Backlog Queue.
* **Accept:** When you finally call accept(), you are simply taking the first connection off this queue.

Note: After `listen()`, the socket is ready to accept connections, but does not accept any connections yet.

#### **Return Value**
* On success it returns 0, and -1 on error.
ex:
```
#include <sys/socket.h>
#include <stdio.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // (Assume we filled the struct and called bind() here...)
    // bind(server_fd, ...);

    // THE LISTEN STEP
    // We allow a "waiting room" of 10 people.
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Server is listening... The Ringer is ON.\n");
    printf("Waiting for connections...\n");
    
    // The program continues instantly to the next step (usually accept)
    return 0;
}
```








