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

