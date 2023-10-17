# Multi-Threaded Max Value Finder

This C program showcases multi-threading using pthreads and demonstrates how to find the maximum value within a matrix. It synchronizes threads, calculates local maximum values, and then determines the global maximum.

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
   gcc -o a ask02.c -lpthread
   ```

2. Run
   ```bash
   ./a
   ```
   The program will execute and display the maximum value found within the matrix.

## Author

This code was written byVelasco Paola
For a more detailed explanation of the code and its functionality, please refer to the comments within the source code.

Enjoy experimenting with thread synchronization in this simple multi-threaded example!

## Results

Below are snapshots from the terminal during different code executions. In the first execution, all calculations were printed for debugging purposes. In the second execution, these were removed to make the results more understandable.

Run no.1

```shell
velasco@DESKTOP-A3QHN88:/mnt/d/Velasco/UniWA/UniWA_3rd_year/UniWa_6th_semester/Λειτουργικά
Συστήματα ΙΙ/Ergasia2$ gcc -o a ask02.c -lpthread
velasco@DESKTOP-A3QHN88:/mnt/d/Velasco/UniWA/UniWA_3rd_year/UniWa_6th_semester/Λειτουργικά
Συστήματα ΙΙ/Ergasia2$ ./a
Give length of array A: 4
Give number of threads: 2
Give numbers for mainArrayA
mainArrayA[0][0]: 1
mainArrayA[0][1]: 2
mainArrayA[0][2]: 3
mainArrayA[0][3]: 4
mainArrayA[1][0]: 5
mainArrayA[1][1]: 6
mainArrayA[1][2]: 7
mainArrayA[1][3]: 8
mainArrayA[2][0]: 9
mainArrayA[2][1]: 10
mainArrayA[2][2]: 11
mainArrayA[2][3]: 12
mainArrayA[3][0]: 13
mainArrayA[3][1]: 14
mainArrayA[3][2]: 15
mainArrayA[3][3]: 16
Contents of array A
mainArrayA[0][0] = 1
mainArrayA[0][1] = 2
mainArrayA[0][2] = 3
mainArrayA[0][3] = 4
mainArrayA[1][0] = 5
mainArrayA[1][1] = 6
mainArrayA[1][2] = 7
mainArrayA[1][3] = 8
mainArrayA[2][0] = 9
mainArrayA[2][1] = 10
mainArrayA[2][2] = 11
mainArrayA[2][3] = 12
mainArrayA[3][0] = 13
mainArrayA[3][1] = 14
mainArrayA[3][2] = 15
mainArrayA[3][3] = 16
Hello, I am thread 1 (not a real thread ID)
Value of lines assigned to me = 2
My job to look for the max number will start at A[0][0]
mainArrayA[0][0] = 1
mainArrayA[0][1] = 2
mainArrayA[0][2] = 3
mainArrayA[0][3] = 4
mainArrayA[1][0] = 5
mainArrayA[1][1] = 6
mainArrayA[1][2] = 7
mainArrayA[1][3] = 8
Local max = 8
Hello, I am thread 2 (not a real thread ID)
Value of lines assigned to me = 2
My job to look for the max number will start at A[2][0]
mainArrayA[2][0] = 9
mainArrayA[2][1] = 10
mainArrayA[2][2] = 11
mainArrayA[2][3] = 12
mainArrayA[3][0] = 13
mainArrayA[3][1] = 14
mainArrayA[3][2] = 15
mainArrayA[3][3] = 16
Local max = 16
Back to the main thread
Maximum value in the array = 16
Contents of array D
arrayD[0][0] = 15
arrayD[0][1] = 14
arrayD[0][2] = 13
arrayD[0][3] = 12
arrayD[1][0] = 11
arrayD[1][1] = 10
arrayD[1][2] = 9
arrayD[1][3] = 8
arrayD[2][0] = 7
arrayD[2][1] = 6
arrayD[2][2] = 5
arrayD[2][3] = 4
arrayD[3][0] = 3
arrayD[3][1] = 2
arrayD[3][2] = 1
arrayD[3][3] = 0
In the main: Finish and Exit
```

Run no.2

```shell
velasco@DESKTOPA3QHN88:/mnt/d/Velasco/UniWA/UniWA_3rd_year/UniWa_6th_semester/Λειτουργικά
Συστήματα ΙΙ/Ergasia2$ ./a
Give length of array A: 4
Give number of threads: 2
Give numbers for mainArrayA
mainArrayA[0][0]: 34
mainArrayA[0][1]: 56
mainArrayA[0][2]: 324
mainArrayA[0][3]: 234
mainArrayA[1][0]: 234
mainArrayA[1][1]: 656453
mainArrayA[1][2]: 43
mainArrayA[1][3]: 243
mainArrayA[2][0]: 234
mainArrayA[2][1]: 523
mainArrayA[2][2]: 465
mainArrayA[2][3]: 42
mainArrayA[3][0]: 341
mainArrayA[3][1]: 2345
mainArrayA[3][2]: 246
mainArrayA[3][3]: 426
Hello I am thread 1 (not real thread id)
Local max = 656453
Hello I am thread 2 (not real thread id)
Local max = 2345
Back to main thread
Maximum value in array = 656453
Contents of array D
arrayD[0][0] = 656419
arrayD[0][1] = 656397
arrayD[0][2] = 656129
arrayD[0][3] = 656219
arrayD[1][0] = 656219
arrayD[1][1] = 0
arrayD[1][2] = 656410
arrayD[1][3] = 656210
arrayD[2][0] = 656219
arrayD[2][1] = 655930
arrayD[2][2] = 655988
arrayD[2][3] = 656411
arrayD[3][0] = 656112
arrayD[3][1] = 654108
arrayD[3][2] = 656207
arrayD[3][3] = 656027
In main: Finish and Exit

```
