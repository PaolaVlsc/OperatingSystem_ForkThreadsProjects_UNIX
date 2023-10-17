# Multi-Threaded Sum of Squares Calculator

This C program demonstrates multi-threading using the Pthreads library in a Unix-like environment. It calculates the sum of squares of numbers in an array using multiple threads. This example showcases the power of parallel computing in a simple application.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Logic](#logic)
  - [Built-in Functions](#built-in-functions)
  - [Flow](#flow)
- [Author](#author)
- [Run](#run)

## Introduction

This C program creates a hierarchy of threads to calculate the sum of squares of numbers in an array. It uses the Pthreads library for multi-threading and showcases how to efficiently distribute computation among threads.

## Features

- Multi-threaded computation of the sum of squares.
- Use of Pthreads library for parallel processing.
- Synchronization of threads using mutex for shared variable updates.

## Logic

# Built-in Functions

This program utilizes the following built-in functions:

- `pthread_create()`: for creating a new thread.
- `pthread_join()`: for process synchronization.
- `pthread_mutex_lock()`: for process synchronization and mutual exclusion for critical sections.

# Flow

The program's flow is defined as follows:

1. The main thread/process, which is the `main()` function, prompts the user to input:
   - The size of the array.
   - The number of threads.
   - Input data for array A.
2. Calculation is done to distribute the appropriate elements to each thread.
3. Then, a data structure of type `data` is created, and its members are initialized with values to be passed to the threads.
4. Subsequently, threads are created while the main program is blocked until all threads complete the tasks assigned to them.
5. Threads execute the `calculateSquareSum()` function, which involves appropriate calculations and storing results in their local variable `local_sum`.
6. Before each thread finishes, they update a global shared variable `total_sum`.
7. Finally, after all threads have completed, the flow returns to the main program, where the `total_sum` variable is printed.

During the implementation of the exercise, it was observed that the use of mutex was necessary because there were variables that represented critical sections:

- `str->thread_number`
- `total_sum`

These variables are shared among threads, so any modification without synchronization can lead to incorrect results.

## Author

This code was written by Velasco Paola

Notes:
We observe that the same results are obtained for a different number of threads and the same vector size. Additionally, we can see that each thread has taken specific elements of the array.

## Run

```bash
gcc -o cs161020_askisi03 cs161020_askisi03.c -lpthread
./cs161020_askisi03
```

## Results for n = 8 και p = 2

```shell
paolavlsc98@linux:~/Desktop/ls2/Final_codes_cs161020$ gcc -o cs161020_askisi03 cs161020_askisi03.c -lpthread
paolavlsc98@linux:~/Desktop/ls2/Final_codes_cs161020$ ./cs161020_askisi03
Give length of array A: 8
paolavlsc98@linux:~/Desktop/ls2/Final_codes_cs161020$ ./cs161020_askisi03
Give length of array A: 8
Give number of threads: 2
Give numbers for mainArrayA
arrayA[0]: 1
arrayA[1]: 2
arrayA[2]: 3
arrayA[3]: 4
arrayA[4]: 5
arrayA[5]: 6
arrayA[6]: 7
arrayA[7]: 8
Contents of array A
mainArrayA[0] = 1
mainArrayA[1] = 2
mainArrayA[2] = 3
mainArrayA[3] = 4
mainArrayA[4] = 5
mainArrayA[5] = 6
mainArrayA[6] = 7
mainArrayA[7] = 8
Hello, I am thread 1 (not a real thread ID)
Contents of "local" A assigned to me
mainArrayA[0] = 1
mainArrayA[1] = 2
mainArrayA[2] = 3
mainArrayA[3] = 4
Thread 1 - Local_sum = 30
Hello, I am thread 2 (not a real thread ID)
Contents of "local" A assigned to me
mainArrayA[4] = 5
mainArrayA[5] = 6
mainArrayA[6] = 7
mainArrayA[7] = 8
Thread 2 - Local_sum = 174
Total_sum = 204
In main: Finish and Exit
paolavlsc98@linux:~/Desktop/ls2/Final_codes_cs161020$
```
