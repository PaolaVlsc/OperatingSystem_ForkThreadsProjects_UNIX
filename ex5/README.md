# Multi-Threaded Max Value Finder

This C program showcases multi-threading using pthreads and demonstrates how to find the maximum value within a matrix. It synchronizes threads, calculates local maximum values, and then determines the global maximum. This code was created by ΒΕΛΑΣΚΟ ΠΑΟΛΑ (cs161020) as part of a task for the 2020/21 Laboratory of Computer and Informatics Engineering at the School of Engineering, University of Patras, under the guidance of Professor ΜΑΜΑΛΗΣ ΒΑΣΙΛΕΙΟΣ and Professor ΙΟΡΔΑΝΑΚΗΣ ΜΙΧΑΛΗΣ.

## Table of Contents

- [Introduction](#introduction)
- [Implementation Details](#implementation-details)
  - [Built-in Functions](#built-in-functions)
  - [Logic](#logic)
  - [Flow](#flow)
- [Usage](#usage)
- [Author](#author)

## Introduction

In this C program, multiple threads work in parallel to find the maximum value within a matrix. The program allows you to specify the matrix size and the number of threads. It synchronizes threads using semaphores and determines both local and global maximum values. This code serves as a simple demonstration of thread synchronization in a multi-threaded application.

## Implementation Details

- The program uses the `pthread` library for multi-threading and the `semaphore` library for synchronization.
- It initializes a mutex for thread synchronization.
- A barrier is used to ensure all threads have reached a synchronization point.
- The code defines a struct to pass data to each thread, including the portion of the matrix it needs to process.
- Threads are created to search for the local maximum values, which are then compared to determine the global maximum.

### Built-in Functions

The program utilizes the following built-in functions:

- `pthread_create()`: for creating new threads.
- `pthread_join()`: for process synchronization.
- `sem_init()`: for semaphore initialization.
- `sem_wait()`: for locking a semaphore.
- `sem_post()`: for unlocking a semaphore.
- `pthread_mutex_lock()`: for locking a mutex.
- `pthread_mutex_unlock()`: for unlocking a mutex.
- `pthread_barrier_init()`: for barrier initialization.
- `pthread_barrier_wait()`: for synchronizing threads at a barrier.

### Logic

The program's flow is defined as follows:

1. The main thread/process initializes the matrix, mutex, and barrier.
2. The number of threads is determined based on user input.
3. Threads are created, each responsible for calculating the local maximum of a portion of the matrix.
4. Mutex and barriers are used for thread synchronization.
5. The global maximum value is determined by comparing the local maximums of all threads.

### Flow

The program's flow is defined as follows:

- The main thread/process, which is the `main()`, requests the following input from the user:

  1. The size of the matrix.
  2. The number of threads.
  3. Data entry for matrix/vector A.

- Calculation for the distribution of the appropriate elements to each thread is performed.

- Next, a structure of type "data" is created and initialized with values that are meant to be passed to the threads.

- Threads are then created, while the main program is blocked until all threads have completed their tasks.

- Threads execute the `findMax()` function, which calculates the appropriate value for finding the maximum in the elements assigned to them.

- The global maximum value is updated, and locking/unlocking is used for synchronization.

- Subsequently, once all threads have completed their contributions to finding the maximum value, the calculation and initialization of array D are performed.

- Finally, after all threads have terminated, the flow returns to the main program, where the `maxElement` variable and array D are printed.

During the implementation of the exercise, it was observed that the use of mutexes was necessary because there were variables that represented critical sections:

- `str->thread_number`
- `maxElement`

These variables are shared among the threads, so any modification without synchronization could lead to incorrect results.

## Usage

To compile and run the program, follow these steps:

1. Compile the program using the following command:

   ```bash
   gcc -o max_value_finder max_value_finder.c -lpthread
   ```

2. Run
   ```bash
   ./max_value_finder
   ```
   The program will execute and display the maximum value found within the matrix.

## Author

This code was written byVelasco Paola
For a more detailed explanation of the code and its functionality, please refer to the comments within the source code.

Enjoy experimenting with thread synchronization in this simple multi-threaded example!

## Results

Below are snapshots from the terminal during different code executions. In the first execution, all calculations were printed for debugging purposes. In the second execution, these were removed to make the results more understandable.
