# MyContainer & Custom Iterators (C++ Assignment 4)

## 👨‍💻 Author
Noa Shalom (Patito)
Email: noapatito123@gmail.com

---

## 📘 Overview

This project implements a generic container class `MyContainer<T>` for any **comparable type**, along with six different **custom iterator orders**:

- **AscendingOrder** – Elements in increasing order.
- **DescendingOrder** – Elements in decreasing order.
- **SideCrossOrder** – Zigzag from smallest to largest and inward.
- **ReverseOrder** – Reverse insertion order.
- **RegularOrder** – Original insertion order.
- **MiddleOutOrder** – Starts from the middle, then alternates left and right.

Each iterator is implemented as a class inheriting from a shared base class `AbstractIterator<T>`, which enforces safety (modification detection) and consistency.

---
## ✨ Features

### 🔧 Core Functionality

- `add(value)` – Inserts a new value into the container. Duplicate entries are supported.
- `remove(value)` – Deletes one instance of the given value.  
  Throws a `std::runtime_error` if the value does not exist.

- **Safe iteration** – Every iterator tracks the container’s version to detect changes during traversal.

- **Robust error handling:**
  - Throws `std::runtime_error` if the container is modified during iteration.
  - Throws `std::out_of_range` when attempting to increment past the end of the iterator.

### 🧪 Iterator Reliability

All custom iterators are validated against:
- Empty containers
- Containers with a single element
- Structural modification during iteration
- Out-of-bounds access

They are fully compatible with **range-based for loops** and **C++ iterator semantics**.

---

## ➕ Operators

### `MyContainer` Operators
- `operator<<` – Allows printing the container directly via `std::cout`, in the format:  
  `[val1, val2, val3]`.

### Iterator Operators
Each iterator supports the following:

- `operator*` – Dereferences the current element and returns a constant reference.
- `operator++` – Moves to the next element. Throws if incremented past the end.
- `operator==` / `operator!=` – Compares the position and type of two iterators from the same container.
- **Safety:** `operator*` and `operator++` will throw if the container has been changed after the iterator was created.

---

## 📁 File Structure

```
cpp_ex4/
├── include/
│   ├── MyContainer.hpp
│   ├── doctest.h
│   └── iterators/
│       ├── AbstractIterator.hpp
│       ├── AscendingOrder.hpp
│       ├── DescendingOrder.hpp
│       ├── MiddleOutOrder.hpp
│       ├── RegularOrder.hpp
│       ├── ReverseOrder.hpp
│       └── SideCrossOrder.hpp
│── Demo.cpp
├── tests/
│   └── tests.cpp
├── Makefile
└── README.md
```

---

## ⚙️ Build & Run

### 🔸 Compile & Run Demo
```bash
make Main
```

### 🔸 Run Tests
```bash
make test
```

### 🔸 Memory Leak Check (Valgrind) on tests only
```bash
make valgrind
```

### 🔸 Code Coverage
```bash
make coverage
```

---

## 🧪 Test Coverage

This project uses [`gcov`](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) to measure **test coverage** — how much of the code is executed by the unit tests.

### ✅ What is covered?
- **Only the test target (`tests/tests.cpp`) is compiled and run.**
- All logic inside `MyContainer` and iterator classes (`AscendingOrder`, `DescendingOrder`, etc.) is covered **only through test execution**.
- The demo file (`Demo.cpp`) is **not included**, ensuring coverage reflects actual test quality.

✅ **100% line coverage (for tests only)**
✅ **No memory leaks** (Valgrind clean)

---

## 🛠️ Example Output

```cpp
MyContainer<int> c;
c.add(3); c.add(1); c.add(4);

for (auto x : c.Ascending())   std::cout << x << " "; // 1 3 4
for (auto x : c.Descending())  std::cout << x << " "; // 4 3 1
for (auto x : c.Regular())     std::cout << x << " "; // 3 1 4
```

---

## 🧠 Notes

- Uses C++17, `unordered_multiset` for fast `remove` operations.
- Iterators throw exceptions if the container is modified mid-iteration.
- Generic and extensible for future iterator types.

