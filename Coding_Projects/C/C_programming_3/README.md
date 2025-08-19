## C Programming Class 3

This repository contains my most advanced work in systems programming and operating system simulation from my C Programming III course. The two major projects included here are:

**USLOSS** – A simulator for experimenting with low-level OS and hardware concepts.

**THREADS** – A software-based framework for exploring OS kernel design and process management.

Both projects were written in C and represent the culmination of my work in the course. They demonstrate my ability to work with low-level system concepts, such as interrupts, device drivers, process scheduling, and context switching.


## 📂 Repository Structure
C_Programming_3/
│── USLOSS/      # Operating system simulation framework
│── THREADS/     # Threading and kernel-level programming framework
└── README.md    # Project documentation

🚀 Projects
🔹 USLOSS

USLOSS (Unix Software Library for Operating System Simulation) simulates the basic hardware features of a hypothetical computer system. It provides students the ability to experiment with low-level systems programming concepts in a safe environment.

**Key Features:**

Simulated single CPU environment with kernel/user modes.

Support for interrupt handling, including:

periodic clock interrupts

system calls

terminal I/O

disk storage devices

Context switching support for process scheduling.

Provides realistic abstractions for device drivers and memory management.

This project strengthened my knowledge of system calls, interrupt handling, process control, and kernel design.

📖 For detailed usage instructions, see the USLOSS User’s Manual provided in the project folder.


## 🔹 THREADS

THREADS is a software-only simulation platform that allows building and testing of OS kernel features such as process management, scheduling, and interrupt handling without needing specialized hardware.

Key Features:

Context switching and process lifecycle management.

Processor Status Register (PSR) simulation, including kernel/user modes.

Interrupt handling system with customizable handlers.

Simplified I/O operations for simulating OS-peripheral communication.

Intuitive API for system calls, debugging, and kernel interaction.

THREADS helped me gain hands-on experience with designing and implementing an operating system kernel while reinforcing my understanding of cybersecurity concepts related to CPU protection modes, interrupt handling, and resource isolation.


## 🛠️ Skills Demonstrated

Through these projects, I developed and showcased expertise in:

C programming at the systems level

OS concepts: process scheduling, context switching, interrupt handling

Low-level debugging with gdb

Building and linking static libraries

Kernel/user mode transitions and CPU state management


## 📌 Notes

Both projects were developed in a Linux environment using GCC and Makefiles.

These projects are educational in nature and simulate real-world operating system behaviors in a controlled, software-only environment.


## 🌟 Why This Matters

USLOSS and THREADS represent the most impressive and complex work I have completed in C programming so far. They demonstrate my ability to design and implement low-level systems software, a strong foundation for future work in operating systems, embedded systems, and cybersecurity engineering.


## Academic Integrity Notice
If you are a student who found this repo while searching for help on coursework:
- **Do not copy** this work into your assignments. 
- Use these examples only as references to learn concepts.
- The best way to grow as a programmer is to solve problems yourself.
- If you need help, feel free to reach out - I'd be glad to offer guidance.