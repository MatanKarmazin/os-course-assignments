# 🖥️ Operating Systems – Assignments Repository

This repository includes three assignments submitted for the *Operating Systems* course. Each task demonstrates hands-on work with system-level programming in C, including shell simulation, process synchronization using semaphores, and inter-process communication through shared memory.

---

## 📁 Folder Structure

```

os-assignments/
├── assignment1_shell/
│   └── shell_simulation.c
├── assignment2_semaphores/
│   └── parallel_print.c
├── assignment3_shared_memory/
│   └── shared_memory_sum.c
└── README.md

````

---

## 📝 Assignment Descriptions

### 🔹 Assignment 1 – Shell Simulation (`assignment1_shell/`)

**Goal**: Simulate a basic shell terminal that:
- Reads and parses user input
- Validates executable commands based on the system `PATH`
- Uses `fork()`, `execv()`, and `waitpid()` to launch and manage child processes
- Recognizes a custom `"leave"` command to exit the shell

> 🔧 Key System Calls: `fork()`, `execv()`, `waitpid()`, `getenv()`, `access()`

---

### 🔹 Assignment 2 – Semaphores (`assignment2_semaphores/`)

**Goal**: Create N (5) processes that print numbers from 1 to 100 in a controlled and synchronized manner using semaphores. Each process prints a different sequence of numbers, but synchronization ensures orderly execution without overlap.

> 🔧 Key System Concepts: `semget()`, `semop()`, `semctl()`, process synchronization

---

### 🔹 Assignment 3 – Shared Memory and Semaphores (`assignment3_shared_memory/`)

**Goal**: Create 100 processes, each adding its index to a shared memory sum. Synchronization is managed using semaphores to ensure data consistency and avoid race conditions.

- Uses `shmget()` and `shmat()` to allocate shared memory
- Semaphores protect access to the shared integer
- Prints sum before and after each addition
- Frees shared resources at the end

> 🔧 Key System Calls: `shmget()`, `shmat()`, `shmdt()`, `shmctl()`, `semget()`, `semctl()`

---

## ⚠️ Disclaimer

> 🧪 **Some code may be experimental or modified during testing.**  
While all files are functional and reflect the assignment goals, parts of the code may have been edited for testing or experimentation and may require minor changes to compile/run depending on the system.

---

## 🧪 Compilation & Execution

Typical compilation examples:

```bash
# Assignment 1
gcc shell_simulation.c -o shell
./shell

# Assignment 2
gcc parallel_print.c -o print -lrt
./print

# Assignment 3
gcc shared_memory_sum.c -o sum
./sum
````

> Add `-lpthread` or `-lrt` if necessary, depending on your system.

---

## 📚 Course Topics Demonstrated

* Process creation and termination
* System-level I/O and execution
* POSIX semaphores
* Shared memory management
* Synchronization and concurrency control
* Safe inter-process communication (IPC)
