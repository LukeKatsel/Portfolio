## x86 Assembly Programming II

This repository contains coursework from my second x86 Assembly programming class. The projects expand on low-level programming concepts with a stronger focus on networking, system calls, and structured Visual Studio assembly projects.

## 📂 Structure

**Lab 1 – Lab 7**
Step-by-step exercises covering assembly fundamentals, system calls, and control flow.

**Final**
A comprehensive capstone project that applies skills from the entire course.

**Files**
Miscellaneous .asm files made throughout the semester for testing, experimentation, or practice.


## 🏆 Final Project – Telnet Client

The final project was the breakdown of a  provided fully functional Telnet client written entirely in x86 assembly. The program implements network communication through system calls and demonstrates socket programming at the assembly level.

**Features**

Accepts IP address and port as command-line arguments.

Parses and validates IP addresses (with error handling for malformed inputs).

Opens and manages a socket connection with connect().

Sets up file descriptors for stdin and socket I/O.

Implements a read/write loop with select() to handle asynchronous I/O.

Reads user input and writes to the socket, while also reading socket data and writing to stdout.

Includes graceful error handling and socket closure routines.


## Skills Demonstrated

Network programming in x86 assembly (socket, connect, select, read, write, close).

Parsing and validating input at a low level (custom cStrtoul and cStrIP_to_Octets).

Bitwise operations to manage file descriptors.

Modular assembly program design with reusable subroutines.

Debugging and documenting complex assembly logic.


## Academic Integrity Notice
If you are a student who found this repo while searching for help on coursework:
- **Do not copy** this work into your assignments. 
- Use these examples only as references to learn concepts.
- The best way to grow as a programmer is to solve problems yourself.
- If you need help, feel free to reach out - I'd be glad to offer guidance.