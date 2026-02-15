# 📚 UNIX Libraries
**A library is a set of pre-written, compiled functions that can be reused by multiple programs.** Instead of writing the same logic again and again, we keep it in a library and link it with the application.
ex:
* Standard C Library: `printf()`, `malloc()`, `open()`.
* POSIX Thread Library: `pthread_create()`

Imagine we are writing a program, and we keep needing the same function again and again, i.e may be a mathematical calculations, string manuplation of file operations. Instead of copying and pasting the same code again and again, programmers create libraries. It is like reference book, instead of memorizing everything, we can look up what we need when we need it.

1. Without Libraries: Every time we wanted to use our own `printf()`, we would have to write the 5000 lines of code that talks to the videodriver and kernel to display the pixels on screen.
2. With Libraries: We can just include `<stdio.h>` and link it against the standard c library (`-libc`).

## ⚙️ The Compilation Process
To understand the concepts of libraries, we need to understand how a c program becomes an executable. According to the `x86` toolchain architecture,

<img width="1000" height="400" alt="image" src="https://github.com/user-attachments/assets/9bd4571d-6e97-485e-938b-17f849813b40" />

**1. Preprocessor:**
   The preprocessor handles all the directives such as `#include` and `#define`, expanding macros and including the header files.
**2. Compiler:**
   The compiler translates our c source code (`.c`files) into the assembly language.
**3. Assembler:**
   Assembler converts our assembly code into the machine code, creating `.obj` files. These object files contains machine code but are not yet executable(contains partial code).
**4. Linker:**
   Linker is responsible to the link the "`.obj` files created by the assembler and it's dependent other `.obj` files". Linker creates an file with extension `.exe`, that contains the final executable code in
   binary format.

## 📦 Object Files
An object file (`.o`) is a compiled code that isn't yet ready to run. It contains:
* Machine code for the functions we wrote.
* References(symbols) to the external functions we called, but didn't define.
* Information about functions it provides that others can use.
ex:
If our code calls `printf()`, the object files knows that we called it, but it does not contain the actual code for `printf()`, it comes from the library.

## 🧠 Symbol Resolution and Linking
when we write a code like,

```
#include<stdio.h>
#include<math.h>

int main()
{
   printf("Square root: %f\n", sqrt(25.0));
   return 0;
}
```
Above code references two functions that we didn't implement, i.e `printf()` and `sqrt()`. These are external symbols or undefined references in our object files. The linkers main job is to perform **"symbol resolution"**. Finding where these functions actually live(in libraries) and connecting our code to them. This is where difference between static and dynamic linking becomes crucial.

If we compile,
```
gcc -c main.c        // This will create main.o (partial code)
```
So if we have multiple `.c` files,
```
main.c      ====>      main.o
helper.c    ====>      helper.o
```
The above is combined during linking.

**Note: Libraries v/s Header files**
* Header file(`.h`): Contains the declerations, they tell the compiler "this function exists, and here what it looks like", but don't contain the actual implementation.
* Libraries(`.a`, `.so`): Contains the actual implementation and compiled code that are declared in header files.

## 🔍 Library Search Path
The linker needs to know where to find the libraries. On UNIX systems, it searches the standard locations like:
* `\lib`
* `\usr\lib`
* `\usr\local\lib`
* directories specified with `-l` flag

## 🏷️ Types of Libraries
In linux, there are mainly two types of libraries:
* Static Libraries
* Dynamic Libraries
<img width="1180" height="720" alt="image" src="https://github.com/user-attachments/assets/23951491-f717-4b8e-9051-a5d22707491b" />


## 1. Static Libraries
Static libraries are archive of pre-compiled object files bundled together into a single file. On UNIX systems, static libraries have the `.a` extension (archieve) and are named with the `lib` prefix.
ex: `libmath.a`, `libutils.a`.
Think it as photocopier. When we link against a static library, we are making a copy of the library code and pasting it directly inside our executable. 

**When we build an application using static library:**
* During the linking time, the linker copies the required functions from the `.a` file into our executable.
* After linking our executable becomes self-contained.
* At runtime, the program does not need `.a` file.

### Structure of Static Library
A static library is:
```
Archieve file (.a)
|_ file1.o
|_ file2.o
|_ file3.o
```
It is simply **"collection of `.o` files together".** It is compiled using the command:
```
ar rcs libcalc.a add.o sub.o
```
where,
* `ar` : archive utility.
* `r` : replace (insert into archive).
* `c` : create (archive if it does not exists).
* `s` : create index (symbol table).
* `libcalc.a` : name of the library (static).

### The Creation Process
Creating a static library is a two-step process.
1. Compile our source code (`.c`) into object code (`.o`).
2. Archive those object files into a single library file (`.a`).

ex: we have two files: `add.c` and `sub.c`

<table>
  <tr>
    <th>Addition</th>
    <th>Subtraction</th>
  </tr>
  <tr>
    <td>
      <pre><code>int add(int a, int b)
{
    return a + b;
}</code></pre>
    </td>
    <td>
      <pre><code>int sub(int a, int b)
{
    return a - b;
}</code></pre>
    </td>
  </tr>
</table>

* Step 1) We compile them into our machine code (object files), but stops before linking.
```
gcc -c add.c sub.c         (-c tells compile to machine code, but don't make an executable)
```
so we get: `add.o` and `sub.o`.

* Step 2) Now we need to bundle them together using the `ar`(archive) command.
```
ar rcs libmymath.a add.o sub.o
```
Now we have the file named as `libmymath.o`, that contains machine code for `add()`, `sub()`.

### The Linking Process
consider we have a `main.c` function that uses this library:
```
#include<stdio.h>

int add(int, int);

int main()
{
   printf("5 + 3: %d\n", add(5,3));
   return 0;
}
```
To compile this code, we tell our GCC to look at the static library.
```
gcc main.c -L. -lmymath -o myapp
```
where,
* `-L.`: looks for libraries in the current directory(.). By default the GCC only looks in `(\usr\bin)`.
* `-lmymath`: Link agains the library named `libmymath.a`.
**Note:** We can drop the `lib` prefix and `.a` extension. GCC adds them back automatically.

#### Internally
* The linker sees `main.o` and calls `add()`.
* It looks inside `libmymath.a`.
* It finds `add.o` inside archive.
* It extracts the code for `add()` and copies it into `myapp` executable.
* Since `main.c` never called `sub()`, the linker is smart enough and not copy the `sub()` code. This minimizes the filesize.

### The Order Trap
```
gcc main.c -lmymath -o myapp                           // IT WORKS

gcc -lmymath main.c -o myapp                           // DOES NOT WORK (error undefined reference to add)
```
UNIX linker is a single pass. It reads the files from left to right. 
* If it sees `-lmymath` first, it thinks "I don't need anything from this library yet, because nobody has asked for anything". It discards library:
  * Then it sees `main.c` that asks for `add()`.
  * But library is already gone (passed).
  
**So, always put our libraries at the end of command line.**

### ❌ Problem with Static Libraries
Every program that runs the library, gets it's own copy. If we have 10 programs using the same library, we have 10 copies of code on disk.
```
program1   --->   500KB   (includes 100KB in library)
program2   --->   450KB   (includes 100KB in library)
program3   --->   480KB   (includes 100KB in library)
total      --->   1430KB  (300 KB is duplicate library code)
```
If multiple process runs simultaneously, each process has it's own copy of library in RAM
```
RAM:
program1   --->   Library code copy 1
program2   --->   Library code copy 2
program3   --->   Library code copy 3
```
If a bug is found in the library, we must:
* Recompile the library.
* Recompile every program that uses it.
* Redistribute all the executables.





