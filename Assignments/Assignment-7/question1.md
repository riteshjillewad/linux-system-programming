# 🔗 Shared Library Dependency

This question demonstrates how **one shared library depends on another shared library** in Linux using C.

It shows:

- Creating multiple `.so` files
- Linking one shared library against another
- Loading only the top-level library in the client
- Automatic dependency resolution by the runtime linker

---

## 📌 Objective

Create:

- `libhelper.so` → Contains helper function `sumOfDivisors()`
- `libperfect.so` → Contains `isPerfect()` and internally calls `sumOfDivisors()` from `libhelper.so`
- `client` → Dynamically loads **only** `libperfect.so` using `dlopen()`

The client does **not** directly load `libhelper.so`.

---

## 📁 Folder Structure
```
├── helper.c                            // contains the logic for find the sum of it's perfect divisors
├── perfect.c                           // contains the logic for checking if number is perfect
├── client.c                            // main function that will load the library functions
├── libhelper.so
├── libperfect.so
└── README.md
```

---

## ⚙️ How It Works

### 🔹 Step 1 — Helper Library (`libhelper.so`)

Contains:
```c
int sumOfDivisors(int n);
```
Responsible for calculating sum of proper divisors.

### 🔹 Step 2 — Perfect Library (libperfect.so)

Contains:
```c
bool isPerfect(int n);
```
Internally calls:
```
extern int sumOfDivisors(int);
```
**This creates a library-to-library dependency.**

### 🔹 Step 3 — Client Program
* Uses `dlopen()` to load libperfect.so
* Uses `dlsym()` to get isPerfect
* Calls the function
* Closes library using `dlclose()`

## 🛠 Build Instructions

### 1️⃣ Build Helper Library
```c
gcc -fPIC -shared helper.c -o libhelper.so
```

### 2️⃣ Build Perfect Library (Linked to Helper)
```c
gcc -fPIC -shared perfect.c -o libperfect.so -L. -lhelper
```
where,
* `L`. → Look in current directory
* `lhelper` → Link against libhelper.so

### 3️⃣ Build Client
```c
gcc client.c -o client -ldl
```

### ▶️ Run
```c
./client
```

**NOTE: Symbol Lookup Error**
Symbol Lookup Error might occur due to missing dependency library. As the linker searches in trusted folders only, where our `.so` file might not be present.
**Temporary Sol:**
```c
export LD_LIBRARY_PATH=.
```

### 🧪 Sample Output
```c
Enter number: 28
28 is a Perfect Number
```































