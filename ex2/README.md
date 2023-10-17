# Process Hierarchy and Inter-Process Communication

A simple C program that demonstrates process creation using `fork()` and inter-process communication through pipes in a Unix-like environment.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Logic](#logic)
    - [Built-in Functions](#built-in-functions)
    - [Flow](#flow)
  - [Prerequisites](#prerequisites)
  - [Run](#run)
- [Author](#author)
- [Results](#results)

## Introduction

This C program creates a hierarchy of processes and demonstrates how they communicate with each other using pipes. It's a useful example for understanding process management and inter-process communication in a Unix-like operating system.

## Features

- Creation of a hierarchy of processes using `fork()`.
- Inter-process communication through pipes.
- Parent and child processes print their process information.
- Waiting for child processes to complete using `wait()` and `waitpid()`.
- Execution of external commands using `execlp()`.

## Getting Started

These instructions will help you run the code on your local machine.

## Logic

### Built-in Functions

In the program, the following functions have been used:

- `fork()`: for creating a new process.
- `wait()`: for process synchronization.
- `pipe()`: for data communication between parent and child processes.

### Flow

The program flow is defined as follows:

1. First, the main part of the P1 process is executed.
2. Then, the message received from P1 is printed by P0.
3. Next, the child process P2 is created by P0, and it waits until the main part of the P2 process completes.
4. The subsequent processes that execute their main parts are P3, followed by P4, and finally, P5.

The main idea for this exercise is to execute the code of the "children" processes first, while the "parents" wait until their children complete their main parts.

### Prerequisites

- A Unix-like operating system (Linux, macOS, etc.)
- A C compiler (e.g., GCC) installed on your system.

### Run

```shell
gcc -o cs161020_askisi02 cs161020_askisi02.c
 ./cs161020_askisi02
```

## Author

This code was written by Velasco Paola

Notes: 
From the PID and PPID, we can see that P1 and P2 are the children of P0, while P3, P4, and P5 are the children of P2. Additionally, we observe that the execution order of the main part of each process is correct.

## Results 
![image](https://github.com/PaolaVlsc/OperatingSystem_ForkThreadsProjects_LINUX/assets/87998374/f060ad35-ae61-4932-9ee2-cf64869669ab)
![image](https://github.com/PaolaVlsc/OperatingSystem_ForkThreadsProjects_LINUX/assets/87998374/4cfe95e1-4342-4fda-a877-71410bd0399e)
![image](https://github.com/PaolaVlsc/OperatingSystem_ForkThreadsProjects_LINUX/assets/87998374/ea799c61-f95b-4b7a-b78f-c9d528b0594a)
![image](https://github.com/PaolaVlsc/OperatingSystem_ForkThreadsProjects_LINUX/assets/87998374/2fd689a2-26bb-457d-b0f9-741bc58891a9)

