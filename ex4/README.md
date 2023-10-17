# Multi-Threaded String Sequencer

This C program illustrates the use of threads and semaphores to control the concurrent printing of strings from three different threads. It coordinates the output of `<one>`, `<two>`, and `<three>` strings to demonstrate how semaphores can synchronize thread execution in a Unix-like environment.

## Table of Contents

- [Introduction](#introduction)
- [Implementation Details](#implementation-details)
- [Logic](#logic)
  - [Built-in Functions](#built-in-functions)
  - [Flow](#flow)
- [Usage](#usage)
- [Author](#author)
- [Results](#results)

## Introduction

In this C program, three threads (`printThread01`, `printThread02`, and `printThread03`) work together to print specific strings in a coordinated manner. Each thread prints its corresponding string (`<one>`, `<two>`, or `<three>`) in a synchronized sequence. This example serves as a simple demonstration of how semaphores can be used to control the execution flow of threads in a multi-threaded application.

## Implementation Details

- The program uses the `pthread` library for multi-threading and the `semaphore` library for synchronization.
- Three semaphores (`semA`, `semB`, `semC`) are utilized to coordinate the thread execution.
- The code defines three separate threads, each responsible for printing a specific string.
- Threads use semaphores to ensure that they print their respective strings in the correct order.
- The `main` function initializes the semaphores, creates the threads, and waits for them to complete their tasks.
- After all threads have terminated, the program prints a message to indicate their successful completion.

## Logic

### Built-in Functions

The program utilizes the following built-in functions:

- `pthread_create()`: for creating a new thread.
- `pthread_join()`: for process synchronization.
- `sem_init()`: for semaphore initialization.
- `sem_wait()`: for locking a semaphore.
- `sem_post()`: for unlocking a semaphore.

### Flow

The program's flow is defined as follows:

1. The main thread/process, `main()`, initializes the semaphores.
2. It creates three threads, each responsible for executing its corresponding code as specified by the exercise.

The program makes use of `sem_wait()` and `sem_post()` for thread execution synchronization.

## Usage

To compile and run the program, follow these steps:

1. Compile the program using the following command:

   ```bash
   gcc -o a ask01.c -lpthread
   ```

2. Run the compiled program:

   ```bash
   ./a
   ```

The program will execute and produce synchronized output of `<one>`, `<two>`, and `<three>` strings.

## Author

This code was written by Paola Velasco.

For a more detailed explanation of the code and its functionality, please refer to the comments within the source code.

Enjoy experimenting with threads and semaphores in this simple multi-threading example!

Notes:
We observe that they are indeed executed in the order analyzed above, and there are no random executions or sequences. We can see that <one><two><three> were printed in sequence 15 times.


## Results

![image](https://github.com/PaolaVlsc/OperatingSystem_ForkThreadsProjects_LINUX/assets/87998374/6611ba8a-456d-49c1-8069-4bd4cec6ef33)

