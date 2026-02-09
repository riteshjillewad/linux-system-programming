# 🔨 Makefiles
A Makefile is a special configuration file used by the `make` utility to automate the build process of software projects. Think of it as a recipe book that tells your computer how to compile and link your code, specifying what needs to be built, in what order, and under what conditions.

So, a makefile is a text file that tells the `make` tool:
* How to build a program (compile + link)
* What depends on what (dependencies)
* What to rebuild when a file changes
* How to clean the generated files

## 📌 Need for Makefiles ?
When we are working on a small program with just one or two source files, compiling it is simple as we can type the compiler commands directly. But imagine a project with dozens or hundreds of source files, recompiling everything from the scratch each time we change one file would be a complete waste. <br>
ex,
```
gcc -c main.c
gcc -c helper.c
gcc -c math-utils.c

gcc -o myapp main.o helper.o math-utils.o
```
Here we have 3 files that will have their own `.o(obj)` files, as we want to compile multiple files together, so next we use final command that combines these individuals pieces into one final product. New problem is that typing this everything we change one line of code is exhausting. If we change `main.c`, why recompile `helper.c` and `math-utils.c` as compiling large projects would take hours. <br>

**Solution: Makefiles solve these problem by**:
* Tracking dependencies between files.
* Only rebuilding what's changed (and what depends on it).
* Automating complex build sequences.
* Providing consistent build process across different environments.

**Note:** _It looks at the timestamps of our file, if `main.c` is newer than `main.o`, then `main.c` is changed. It must recompile it, if `helper.c` is old than the `helper.o`, skip it._

## 🔧 Make Utility
`make` is a unix build tool, that reads instructions from a file named `Makefile`. It checks:
* Which file is changed.
* Which parts need recompilation.
* Executes only the minimum required commands.

## 🔪 Anatomy of Makefiles
Makefiles are simply **"List of rules"**. Every rule follows a strict structure.
```
target : dependencies
[TAB]recipe
```
**1. Target:**
* It is the file we want to create.
* Ex, main.o (object) or myapp (executable)

**2. Dependencies (pre-requisites):**
* These are the files that the target depends on.
* If any of these files are changed, the target is considered as outdated.

**3. Recipe:**
* The shell commands to execute to create the target_(it must be intended with a TAB character, not space)_

Consider an ex,
```
                                                                              Makefile
            Operating System    ----------->    make    ----------->    target : dependencies
                                      (tool that opens makefile)               recipe


            Tea : Milk, Sugar
            [TAB] procedure to make tea
```
                                                  
### Simple Makefile Example

#### `main.c`
```
#include<stdio.h>

int main()
{
    printf("Jay Ganesh...\n");

    return 0;
}
```

#### `makefile`
```
myapp:
  gcc main.c -o myapp

```

#### `Terminal`
```
make
```

In the above example, we have taken a simple approach to make a makefile. We only have one `.c` file, that can be runned using the `gcc main.c -o myapp` command, so this is the command line script that we write under the procedure section of the makefile.

1. Makefile:
* `myapp`: Name of the target (can be anything).
* Since it is a single file, so there are no dependenices.
* `gcc main.c -o myapp` is the recipe to run that target.

2. Terminal:
* On the terminal we write the `make` command, that will create the objects and the executable named as the target name.
* We can run the newly created executable directly or write the make command for it also in the makefile.

**Note: By default, the `make` tool runs the first available target in our makefile.**

## 📗 Variables in Makefiles
Makefiles 

