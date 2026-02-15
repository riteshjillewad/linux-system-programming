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


