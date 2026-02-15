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
**Static libraries are archive of pre-compiled object files bundled together into a single file. **On UNIX systems, static libraries have the `.a` extension (archieve) and are named with the `lib` prefix.
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

### **Problem with Static Libraries**
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

### Flow of Commands
Consider the following flow of commands in case of static library
```
START
  |
  |
[STEP 1] Write library source code
file: mymath.c
file: mymath.h
  |
  |
[STEP 2] Compile to object file
command: gcc -c mymath.c
output:  mymath.o
  |
  |
[STEP 3] Create static library (archive)
command: ar rcs libmymath.a mymath.o
output: libmymath.a
  |
  |
[STEP 4] Compile main and link it with static library
command: gcc main.c -L. -lmymath -o app
output:  app (executable with library code inside)
 |
 |
[STEP 5] Run the program
command: ./app
output:  program output (library not required at runtime)
 |
 |
END
```
Final executable => `main.o` + Library code (copied). <br>
**No dependency on `libmymath.a` at runtime, even if we delete the `.a` file, app will run**

## 2. Dynamic Libraries
**A dynamic library (also called as shared library) is compiled code that remains seperate from our executable and is loaded into memory at the runtime.** On UNIX,
* Linux: `.so`    (shared object).
* MacOS: `.dylib` (dynamic library).

Dynamic libraries are like rental service. Instead of everyone owining a copy, programs "rent" access to a single shared copy when they need it. It is not copied into the executable at the compile time, instead it is linked at runtime.
ex: GNU C Library
```
executable = our code + reference to library
library = seperate shared file(.so)
```

let's now understand the working of the dynamic libraries.

### **Step 1) Position Independent Code**
* Dynamic linking requires special compilation, because they can be loaded at any memory address.
* In case of dynamic linking, shared objects are:
  * Loaded at runtime.
  * Loaded at different memory address in different process.
* So if our code used a fixed address(absolute), it would fail when loaded at different locations.
ex:
```
libssl.so is a file that provides the implementation of secure network communication protocols. Since multiple programs might use libssl.so at the same time, O.S loads it into memory once:
- Program A might see it at address 0x1000.
- Program B might see it at address 0x9000.
Because the code can live anywhere, so we use relative address instead of absolute address.

gcc -c -fPIC add.c sub.c
```
so, this flag changes the assembly code. Instead of hardcoding jump address, it uses global offset table(GOT) to calculate address dynamically at runtime.

### **Step 2) Creating the Shared Library**
We don't use `ar rcs` here, instead we use,
```
gcc -shared -o libmymath.so add.o sub.o
```
where,
* `shared`: flag tells the compiler to create a shared library instead of executable.

### **Step 3) Linking the Program**
Compiling our `main.c` program looks exactly the same as static libraries.
* `-L.`: Look in the current folder.
* `-lmymath`: Link against `libmymath`.

But if we try to run the `./app`, we will get an runtime error.
* At compile time, we told GCC where the library was (-L.), so it built it.
* At runtime the OS loader (`ld-linux.so`) tries to run the program, it looks for `libmymath.so` in trusted folders like `lib` or `\usr\lib`, and not look in current folder. (OS loader comes before `main()`).

So for temporary solution we can use the _Environment Variables_. We can tell the loader to look in your current folder (.) for this session.
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
./myapp
```
**This type of linking is called as load-time dynamic linking.**

### Types of Dynamic Linking
In case of dynamic linking (`.so`), there are two options:
* Load-Time Dynamic Linking  (Implicit Linking)
* Run-Time Dynamic Loading (Explicit Linking)

### `-ldl` (Link against dynamic loader library)
It is a special type of library, that allows our program to **"manually load other libraries at runtime".** Usually the O.S loads all the necessary libraries before our `main()`, but sometimes it wants to add library in middle of our program, so we need to use the functions provided by the `-ldl`.

**Core functions of run-time dynamic loading:**

#### 1. `dlopen()`:
`dlopen()` is used to load a shared memory (`.so`) file at runtime manually. Instead of linking it with
```
gcc main.c -lmylib
```
We can load the library inside our program using `dlopen()`. It is part of the `<dlfcn.h>`.

**Syntax:**
```
void *dlopen(const char *filename, int flags);
```
where, <br>
**1. `filename`:**
This is the string containing name of dynamic library we want to load (ex: `libm.so`, `mylib\libm.so`).
**How does OS search for the path:**
* If it contains slash (/), OS assumes it's a specific path and looks there.
* If it contains no slash, OS searchs in standard library path.

**2.`flags`:**
This integer tells dynamic linker when and how to resolve the symbols inside library.
* `RTLD_LAZY` (lazy binding): Resolve symbols as they're used (lazy binding, faster startup).
* `RTLD_NOW` (Immediate binding): Resolve all symbols immediately (catches errors early).

**Return value:**
* On success, it returns a `void *` handle. It is an opaque pointer, we don't know what it points to.
* If we call `dlopen()` twice, the OS is smart, it doesn't load the library twice, it just increments the counter.
* On failure, it returns NULL.

#### 2. `dlsym()`:
It is used to get the address of function or variable from a shared library loaded using the `dlopen()`. It is like: **"Find me function named `add` inside the library"**.

**Syntax:**
```
void *dlsym(void *handle, const char *symbol);
```
where,<br>
**1. `handle`:**
The opaque pointer we got from the `dlopen()`.

**2. `symbol`:**
Name of the function or global variable as string.

**Return value:**
* On success, it returns address/pointer to symbol.
* On failure, it returns NULL.

#### 3. `dlclose()`:
It is used to decrease the reference count of a dynamically loaded shared library and unload it when it is no longer needed.

**Syntax:**
```
int dlclose(void *handle)
```
where,<br>
**1. `handle`:**
Handle returned by `dlopen()`.

**Note:** OS does not always unloads the library:
* It keeps the reference count for every loaded library.
  `dlopen()` increments the count.
  `dlclose()` decrements the count.
* When the count is zero, only then the OS removes the code from memory and frees the resources.

**Return value:**
* On success it returns 0.
* On error, it returns a non-zero value.

When we call `dlclose()`, the library is unloaded, any function pointers we fetched using `dlsym()`, it wont work, as it might give segmentation fault (memory freed).

#### 4. `dlerror()`:
It is used to "retrive a human-readable error message from the dynamic loader". It reports errors that occured in `dlopen()`, `dlsym()`, `dlclose()`.

**Syntax:**
```
char *dlerror(void);
```
Note: calling `dlerror` cleans the error. The next call returns NULL, even if an error occurs previously.
* It returns a string: If an error occurred since the last call, it returns a pointer to static string describing it.
* It returns NULL: If no error occured since the last call.
* The "clear effect", when we call `dlerror()`, it resets error state to NULL.
```
We cannot call dlerror() twice on the same error. The first call retrives the message, the second call returns NULL(because we just created it).
```

**Return value:**
* If an error occured, it returns the pointer to error message string.
* If no error, it returns NULL.

**Error handling patterns**:
1. `dlopen()`:
```
void *handle = dlopen("hello.so", RTLD_LAZY);

if(!handle)
{
   printf("ERROR: %s\n", dlerror());
   return -1;
}
```
In this case:
* If `dlopen()` fails, it always sets an error.
* If succeeds, no error is leaved.

2. `dlsym()`:
```
dlerror();

void *sym = dlsym(handle, "add");
char *error = dlerror();
if(error != NULL)
{
   printf("ERROR: %s\n", error);
   return -1;
}
```
In this case:
* `dlsym()` return value is `void *`.
* `dlsym()` returns NULL if error, but a valid symbol address could also be NULL. So how do we know if null means error or actual symbol value, so we must check:
```
dlerror()                  ---> Clears old message
sym = dlsym()
error = dlerror()          ---> Checks if new error occured
```

### Flow of Commands
Consider the following flow of commands in case of dynamic library
```
START
  |
  |
[STEP 1] Write library source code
file: mymath.c
file: mymath.h
  |
  |
[STEP 2] Compile an position independent code
command: gcc -fPIC -c mymath.c
output: mymath.o
  |
  |
[STEP 3] Create shared library
command: gcc -shared mymath.o -o libmymath.so
output: libmymath.so
  |
  |
[STEP 4] Compile and link with shared library
command: gcc main.c -L. -lmymath -o app
output: app (executable with library reference only)
  |
  |
[STEP 5] Set library path (mostly needed)
command: export LD_LIBRARY_PATH = ./app
output: environment generated
            OR
We can use the dynamic runtime loading functions:
  |
  |
[STEP 6] Run the program
command: ./app
output: program output.
```
Final executable = `main.o` + `reference` + `libmymath.o`.
**If we delete the `.so` file, and run it, it will give error.**








