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
