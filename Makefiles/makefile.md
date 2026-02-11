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
Makefiles support variables to avoid repetition and make maintenance eaiser. <br>
ex:
```
  CC = gcc
  app:
    $(CC) main.c -o app
```
Makefiles have cryptic symbols that save typing.
* `$@`: Represents the target name
* `$^`: Represents all dependencies
* `$<`: Represents the first dependency
ex:
```
  CC = gcc
  app:
    $(CC) main.c -o $@
```
## 🐛 Missing Dependency Bug in Makefiles
Consider the following scenario to understand the _"missing dependency bug"_ in Linux.
<br>
#### **Initial Setup**

<table>
<tr>
<th width="33%">main.c</th>
<th width="33%">Makefile</th>
<th width="34%">Terminal</th>
</tr>
<tr>
<td valign="top">
  
```c
#include<stdio.h>

int main()
{
    printf("Jay Ganesh...\n");
    return 0;
}
```
</td>

<td valign="top">
  
```c
CC = gcc
app:
  $(CC) main.c -o app
```
</td>

<td valign="top">
  
```c
make

// The output will be Jay Ganesh... 
```
</td>
</tr> 
</table>

#### **Modified Code**

<table>
<tr>
<th width="33%">main.c</th>
<th width="33%">Makefile</th>
<th width="34%">Terminal</th>
</tr>
<tr>
<td valign="top">
  
```c
#include<stdio.h>

int main()
{
    printf("Hello World!\n");
    return 0;
}
```
</td>

<td valign="top">
  
```c
CC = gcc
app:
  $(CC) main.c -o app
```
</td>

<td valign="top">
  
```c
make
// Expected Output: Hello World!
// Resultant Output: Jay Ganesh...
```
</td>
</tr> 
</table>

We can see the resultant output contradicts the expected output. The root cause for this is due to make, "make did not recompile `main.c`, because according to it's dependency rules, nothing appreared to be changed, so make does not recompile the main.o (obj file), or the executable.

### Scenario
**1. Run 1:**
* We type `make`.
* `make` checks "does file app exists?"
* Answer is no.
* Action, it runs the recipie command to create the target file.
* Now, we get new executable, when we run it, we say the output as "Jay Ganesh...".

**2. Edit `main.c`:**
* We modify the `main.c`.
* Now, the timestamp of `main.c` is newer than the timestamp of `app`.

**3. Run 2:**
* We type `make`.
* It checks does `app` exists?.
* Yes, it exists. It then checks the dependencies, does `app` depend on anything?.
* Since we left the field empty, so it assumes "it relies on nothing", and must be perfect.
* `make` says "`app` is upto date", and does nothing.
* So the compiler is never called, and the old executable remains and we see the old output only.


### Solution
There are mainly two solutions for this problem.

#### **1. Remove the Old Executable (Brute Force)**
* If we delete `app` (target file/executable) using `rm` or manually, `make` looks for the target `app`, sees it's missing and concludes that _"I have no choice but to run the command to create it"_.
* It works becuase we force a rebuild by eliminating the "up to date" check entirely.

**Note:** This is manual labour. The whole point of makefiles is to automate the decisions. If we have to manually delete the files, every time we change the file code, we might as well type the command manually. So this is why the **"makefiles include a `make - clean` utility to automate the reset process."**
```
  CC = gcc

  app:
    $(CC) main.c -o app

  clean:
    rm -f app
```
* `make`: Create the executable
* `make clean`: Remove the old executable

#### **2. Adding Dependencies (Correct Method)**
* By adding `main.c` (filename) after the `app`, we tell the `make` the truth. **"This is executable made from the source file."**
* It works because `make` can now compare the timestamps. It sees `main.c` is newer than `app` and realizes that the executable is outdated (stale), so it recompiles it automatically.
* This is the power of `make`. We can edit 50 different files, and type `make` once, it will only recompile the specific ones that changed.
```
  CC = gcc

  app:main.c
    $(CC) main.c -o app                // if main.c changes then app must be rebuilt
```

## 📔.PHONY
* By default make assumes that every target in your makefile is the name of file we want to create.
* If we have a target named `myapp`, `make` expects a file named `app` to appear after the command finishes.
* If we have target named `clean`, `make` expects a file named `clean` to appear.

But wait, The `clean` command is usually just a script to delete the files, so it never creates a file named `clean`. So imagine that we have a makefile 
```
  clean:
    rm *.o app                          // Delete all the .o files
```
Now imagine, that one day by accident, we create a file named `clean` in our folder, and now we try to use the cleanup command.
```
  make clean
```
**IT FAILS!**
* `make` sees the target `clean`
* It checks the folder, does the file named `clean` exists?
* Yes (since we just created it accidentally).
* It checks the dependencies: does that target `clean` rely on other files?.
* Answer is no.

"The file is clean, it's exists and no dependencies that are outdated", so `make` "clean is upto date" and does nothing, and our object files are not deleted.

### Solution: `.PHONY`
* We need to explicitly tell `make`, **"don't look at the filesystem for this specific name", just run the command every time i ask."** We do this by declaring the target as dependency of `.PHONY`.
* `.PHONY` tells `make` that target is not a real file, **i.e a PHONY target is name for an action, not for a file that get's created.**

ex:
```
  .PHONY:clean
```
This line tells `make`: `clean` is not a file, always execute it's commands when requested.

#### Why name .PHONY?
Word "PHONY", means "Fake" or "Counterfiet".
* A normal target represents a "real file" (present on the disk).
* A PHONY target represents a "fake file", the target `clean` is a fake file, that never is created.

In real world projects, 
`.PHONY`: `all` `clean` `install` `uninstall` `test` `debug`
* `all`: Build everything.
* `clean`: Remove build artifacts.
* `install`: Copy binaries to system path.
* `test`: Run test suite.
ex:
```
.PHONY: all clean install test

all:myapp

clean:
  rm *.o myapp

install:
  cp myapp /usr/local/bin

test:
  ./myapp --run --test
```

## 🔧 Hiding the `make` Commands
By default, `make` echoes every command before executing it, so when we run:
```
make
```
we see
```
gcc main.c -o myexe
```
This is not the output from the gcc, it's `make` showing is what it's about to run.

### Solution 1 (@ symbol)
By default `@` command hides the echo commands.
ex:
```
app:main.c
  @gcc main.c -o app
```
now we run `make`, so no gcc command is shown here. `@` tells make: **"Run this command silently, do not echo it"**, so it's a per-command control.
ex:
```
myexe:main.c
  @echo "Compiling..."
  @gcc main.c -o myexe
  @echo "DONE, build complete"
```

### Solution 2 (Custom Messages)
Most developers don't want complete silence, they want cleaner output. The standard patern is to use `@` to hid the ugly compiler commands, and use `@echo` to print the friendly status message.
ex:
```
myapp:main.c
  @echo "Compiling..."
  @gcc main.c -o myexe
  @echo "DONE, build complete"
```

### Solution 3 (Hiding Commands Globally)
We can use the `make -s`(silent) to hide the commands.
```
make -s
```
use `.SILENT`
```
.SILENT
```
use `.SILENT` for specific groups.
```
.SILENT:Myexe clean
```

  













