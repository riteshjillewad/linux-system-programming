# Message Queues
Message queues provide a structured, ordered way for processes to exchange discrete messages. Unlike pipes (which are byte streams) or shared memory (which requires manual synchronization), message queues handle messages as distinct units with built-in synchronization.

<img width="1090" height="316" alt="image" src="https://github.com/user-attachments/assets/5c9ce861-552f-4a8c-ba31-a104840e17a2" />

## What is a Message Queue?
A message queue is a **kernel-maintained linked list of messages**. Processes can send messages to the queue and receive messages from it. Each message is a self-contained unit with a type and data payload.<br>
Think of it like a post office mailbox system. Processes drop messages into the queue (like putting letters in a mailbox), and other processes retrieve messages (like collecting mail). The kernel manages the queue, ensures messages aren't lost or corrupted, and handles synchronization automatically.
```
                                WRITER ---------> |     QUEUE      | ---------> READER
```
Queue is esentially a container holding line of messages. New messages are added to back, and messages are read from the front.

## Characteristics

#### Message Boundaries:
Unlike pipes where data is a continuous stream, message queues preserve message boundaries. If Process A sends two messages of 100 bytes each, Process B receives two distinct 100-byte messages, not one 200-byte chunk or arbitrary fragments.

#### Message Types:
Each message has a type (a positive long integer). Receivers can selectively retrieve messages based on type, enabling priority schemes or multiple communication channels within a single queue.

#### Asynchronous Communication:
The sender doesn't need to wait for the receiver. Messages are buffered in the queue. The sender deposits the message and continues; the receiver retrieves it whenever ready.

#### Automatic Synchronization:
The kernel handles all locking and coordination. Multiple processes can send to or receive from the same queue safely without explicit synchronization code.

#### Persistence:
Like other System V IPC mechanisms, message queues persist in the kernel until explicitly removed or the system reboots.

## Message Queue Mechanism
A data structure (message m) is copied from space of sender process into a message buffer in system space, and then copied again from buffer in system space to structure in space of recieving process.

<img width="999" height="280" alt="image" src="https://github.com/user-attachments/assets/8f7fea70-60f1-4d46-b717-fb20ab6a088f" />

In order to make messages work across process boundary, the message buffers have to be named, each process that creates a message buffer has to refer to same message buffer name (kernel will create a message object and return a handle). Handles returned by kernels are local for each process.

<img width="998" height="376" alt="image" src="https://github.com/user-attachments/assets/d99d9482-24d6-4e7e-a492-1735e5f4390d" />

The message buffers are normally synchronized, i.e recieving process is blocked if message buffers are empty, and sending process are blocked if message buffers are full. The messages can be of fixed or variable size.

## Message Structure
A message isn't just random data. It follows specific template defined by the system.<br>
Every message has two parts:
* Type: (`mtype`): A positive long integer that labels message.
* Data: (`mdata`): Actual content we want to send.

**Generic template:**
```
struct msgbuf
{
    long int mtype;                          // Message type > 0
    char mtext[100];
};
```
Kernel uses `mtype` to organize the queue.

#### Selective Reading
This is why developers choose Message Queues over Pipes. When you read from a pipe, you must read whatever is next. With Message Queues, you have choices based on the mtype.<br>
When calling the receive function (msgrcv), you pass a type argument:
- If type == 0: Retrieve the first message in the queue (Classic FIFO behavior).
- If type > 0: Retrieve the first message where mtype equals that specific number. (e.g., "Skip the regular logs, give me the Errors").
- If type < 0: Retrieve the message with the lowest type value that is less than or equal to the absolute value of type. (Used for Priority Queues—get the smallest number first).

## Types of Message Queues
Like shared memory, there are two main APIs:

### System V Message Queues
The original implementation following the System V IPC model:

- msgget() - create/access a queue
- msgsnd() - send a message
- msgrcv() - receive a message
- msgctl() - control operations

Uses the key/identifier system and permission model we've discussed.

### POSIX Message Queues
A newer, cleaner API:

- mq_open() - create/open a queue
- mq_send() - send a message
- mq_receive() - receive a message
- mq_close() - close the queue
- mq_unlink() - remove the queue

Uses filesystem-like names and integrates better with modern Unix features, including support for asynchronous notification.

## System V Message Queues

### Step 1: Creation (`msgget`)
- Action: You pass a Key and Flags.
- Result: The Kernel creates a new linked list structure and returns a Queue ID (msqid).

### Step 2: Sending (`msgsnd`)
- Action: The process packages data into a struct msgbuf and calls msgsnd.
- Kernel Action: The OS copies the data from User Space into a Kernel Buffer and links it to the end of the queue.
- Blocking: If the queue is full (system limit reached), the process blocks (sleeps) until space opens up (unless IPC_NOWAIT is used).

### Step 3: Receiving (`msgrcv`)
- Action: The process asks for a message (specifying the type).
- Kernel Action: The OS finds the matching message, unlinks it from the list, and copies the data back to User Space.
- Cleanup: The message is effectively removed from the queue after reading.

### Step 4: Control/Destruction (`msgctl`)
- Action: Used to view status (permissions, number of messages) or delete the queue (IPC_RMID).
- Note: If you don't delete it, the messages sit in the Kernel memory consuming RAM until the system reboots.
