# 🔎 Dynamic Library Inspection Tool (C / Linux)

A lightweight system-level utility written in C that dynamically inspects and validates shared libraries (`.so` files) at runtime.

This tool:

- Checks whether a shared object file exists
- Attempts to load it using `dlopen()`
- Inspects required exported symbols using `dlsym()`
- Reports detailed loader errors via `dlerror()`
- Safely unloads the library using `dlclose()`

It is designed for learning and demonstrating **runtime dynamic linking in Linux**.

---

## 🎯 Purpose

In many systems (plugins, drivers, modules), libraries are not linked at compile time.  
They are loaded only if present.

This tool simulates that real-world scenario by:

- Verifying that required shared objects are present in the working directory
- Ensuring mandatory functions are exported
- Gracefully handling missing libraries or symbols

---

## 🛠 Technologies Used

- C Programming
- POSIX Dynamic Linking API
- `libdl`
- Linux ELF shared objects

---

## ⚙️ How It Works

### Step 1 – Library Presence Check
The program attempts to load the shared object:

```c
handle = dlopen("./libmath.so", RTLD_LAZY);
```
If the `.so` file is missing
```
dlopen failed: cannot open shared object file
```

### Step 2 – Symbol Inspection
After loading, the tool verifies required functions.
**Each symbol is validated using:**
```
dlsym(handle, "function_name");
```
**If a symbol is missing:**
```
dlsym error: undefined symbol
```

### Step 3 – Safe Cleanup
After inspection:
```
dlclose(handle);
```
The library is safely unloaded.

## ▶️ Usage
Place the `.so` file in the same directory.

### Run
```
./inspector
```

## 🧪 Example Scenarios

### ✅ Case 1 – Library Present
```
Library loaded successfully...
All required symbols found.
```

### ❌ Case 2 – Library Missing
```
dlopen failed: ./libmath.so: cannot open shared object file
```

### ❌ Case 3 – Missing Function in Library
```
dlsym error: undefined symbol: checkPrime
```

## 🔍 Runtime Flow
```
Check .so file
        ↓
dlopen()
        ↓
dlsym() for required symbols
        ↓
dlerror() validation
        ↓
dlclose()
```

## 👤 Author
**Ritesh Jillewad** 








































