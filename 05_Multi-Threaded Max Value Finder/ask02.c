/*  ;; ----------------------------------------------------------------
    ;;                   ΒΕΛΑΣΚΟ ΠΑΟΛΑ      cs161020
    ;; ----------------------------------------------------------------
    ;;           Τμήμα Μηχανικών Πληροφορικής και Υπολογιστών
    ;;               Εργαστήριο ΛΣΙΙ 2020/21 - Εργασία 2.2: 
    ;;                  THREADS, SEMAPHORES, SOCKETS
    ;; ----------------------------------------------------------------
    ;;  Υπεύθυνος μαθήματος: ΜΑΜΑΛΗΣ ΒΑΣΙΛΕΙΟΣ 
    ;;  Καθηγητές: ΙΟΡΔΑΝΑΚΗΣ ΜΙΧΑΛΗΣ
    ;; ----------------------------------------------------------------
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Δήλωση mutex για συγχρονισμό
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Δήλωση barrier για συγχρονισμό
pthread_barrier_t our_barrier;

int maxElement; // μέγιστη τιμή

// struct για τα δεδομένα που θα σταλθούν/λάβει
struct dataToFunction
{
    int lines;
    int arraySize;
    int **arrayOriginal;
    int **arrayOriginalD;
    int thread_number;
};

// αρχικοποίηση πίνακα[][]
void initArrayA(int **mainArrayA, int arrayA_size);

// συνάρτηση που θα εκτελέσει κάθε νήμα
void *findMax(void *arg);

int main()
{
    int **mainArrayA;   // Αρχικός πίνακας A
    int **arrayD;       // Αρχικός πίνακας D
    int arrayA_size;    // Μέγεθος πίνακα Α: n
    int number_threads; // Αριθμός νημάτων: p
    int i, j;

    // Ζητάει το μέγεθος του πίνακα: n
    printf("Give length of array A: ");
    scanf("%d", &arrayA_size);

    // allocate memory for mainArrayA
    mainArrayA = (int **)malloc(arrayA_size * sizeof(int *));
    for (i = 0; i < arrayA_size; i++)
        mainArrayA[i] = (int *)malloc(arrayA_size * sizeof(int));

    // Check if malloc was successfully completed
    if (mainArrayA == NULL)
    {
        printf("Error: Not available memory\n");
        exit(EXIT_FAILURE);
    }

    // allocate memory for arrayD
    arrayD = (int **)malloc(arrayA_size * sizeof(int *));
    for (i = 0; i < arrayA_size; i++)
        arrayD[i] = (int *)malloc(arrayA_size * sizeof(int));

    // Check if malloc was successfully completed
    if (arrayD == NULL)
    {
        printf("Error: Not available memory\n");
        exit(EXIT_FAILURE);
    }

    // Ζητάει τον αριθμό των νημάτων: p
    printf("Give number of threads: ");
    scanf("%d", &number_threads);
    pthread_barrier_init(&our_barrier, NULL, number_threads); // Αρχικοποίηση , το 3ο όρισμα ορίζει πόσα νήματα θα συμμετάσχουν

    // Αρχικοποίηση διανύσματος Α με τη χρήση συνάρτησης initArrayA
    initArrayA(mainArrayA, arrayA_size);

    // αρχικοποίηση μέγιστης τιμής με το πρώτο στοιχείο του πίνακα
    maxElement = mainArrayA[0][0];

    /* Εκτύπωση διανύσματος A 
    printf("\nContents of array A\n");

    for (i = 0; i < arrayA_size; i++)
    {
        for (j = 0; j < arrayA_size; j++)
            printf("mainArrayA[%d][%d] = %d\n", i, j, mainArrayA[i][j]);
    }*/

    // πόσες γραμμές θα λάβει κάθε νήμα
    int linesOfArray;
    linesOfArray = arrayA_size / number_threads;

    /****************** Δημιουργία νημάτων ******************/

    pthread_t *array_threads;

    // allocate memory for mainArrayA
    array_threads = (pthread_t *)malloc(sizeof(pthread_t) * number_threads);
    // Check if malloc was successfully completed
    if (array_threads == NULL)
    {
        printf("Error: Not available memory\n");
        exit(EXIT_FAILURE);
    }

    // Δεδομένα που θα σταλθούν στα νήματα - Αρχικοποίηση
    struct dataToFunction data_thread;
    data_thread.lines = linesOfArray;
    data_thread.arrayOriginal = mainArrayA;
    data_thread.arraySize = arrayA_size;
    data_thread.thread_number = 0;
    data_thread.arrayOriginalD = arrayD;

    for (i = 0; i < number_threads; i++)
    {
        // Έτοιμη συνάρτηση για τη δημιουργία νημάτων. θα εκτλέσουν τη συνάρτηση findMax και θα πάρουν δεδομένα τη δομή data_thread
        pthread_create(&array_threads[i], NULL, findMax, (void *)&data_thread);
    }

    // Εγγύηση ότι το αρχικό νήμα θα εκτυπώσει το αποτέλεσμα αφού ολοκληρωθούν όλες οι διεργασίες
    for (i = 0; i < number_threads; i++)
        pthread_join(array_threads[i], NULL);

    // Απελευθέρωση πόρων
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&our_barrier);

    /* Εκτύπωση διανύσματος μέγιστης τιμής */
    printf("\n\nBack to main thread\nMaximum value in array = %d\n", maxElement);

    /* Εκτύπωση διανύσματος D */
    printf("\nContents of array D\n");
    for (i = 0; i < arrayA_size; i++)
    {
        for (j = 0; j < arrayA_size; j++)
            printf("arrayD[%d][%d] = %d\n", i, j, arrayD[i][j]);
    }

    printf("In main: Finish and Exit\n");

    return 0;
}

// Συνάρτηση: αρχικοποίηση πίνακα Α
void initArrayA(int **mainArrayA, int arrayA_size)
{

    int i, j;
    printf("\nGive numbers for mainArrayA\n");
    for (i = 0; i < arrayA_size; i++)
    {
        for (j = 0; j < arrayA_size; j++)
        {
            printf("mainArrayA[%d][%d]: ", i, j);
            scanf("%d", &mainArrayA[i][j]);
        }
    }
}

//Υλοποίηση συνάρτησης που θα εκτελούν τα νήματα για τον υπολογισμό
void *findMax(void *arg)
{

    // Λήψη δεδομένων 
    struct dataToFunction *str = (struct dataToFunction *)arg;

    int i, j;
    int local_max = 0; 

    // Έλεγχος και δημιουργία συγχρονισμού με mutex
    if (pthread_mutex_lock(&mutex))
    {
        perror("mutex_lock");
        exit(3);
    }

    // print which thread it is
    str->thread_number = str->thread_number + 1;
    printf("\n\nHello I am thread %d (not real thread id) \n", str->thread_number);

    // Αρχικοποίηση από ποιο σημείο του πίνακα θα ξεκινήσουν τον υπολογισμό κάθε νήμα
    int linesLocal = (str->thread_number - 1) * str->lines;
    //printf("Value of lines assigned to me = %d\nMy job to look for the max number will start at A[%d][0]\n\n", str->lines, linesLocal);

    // Αρχικοποίηση για το τοπικό μέγιστο με το πρώτο στοιχείο
    local_max = str->arrayOriginal[linesLocal][0];
    // printf("Local max before = %d\n\n", local_max);

    // Εκτύπωση σημείων του πίνακα που θα ψάξει
    // Ψάχνοντας στον τοπικό πίνακα το μέγιστο αριθμό
    for (i = linesLocal; i < linesLocal + str->lines; i++)
    {
        for (j = 0; j < str->arraySize; j++)
        {
            // printf("mainArrayA[%d][%d] = %d\n", i, j, str->arrayOriginal[i][j]);
            if (str->arrayOriginal[i][j] > local_max)
            {
                local_max = str->arrayOriginal[i][j];
            }
        }
    }

    // Εκτύπωση μέγιστης τιμής ανάμεσα στα στοιχεία που έψαξε. 
    printf("Local max = %d\n\n", local_max);

    // Ενημέρωση καθολικής τιμής για μέγιστο αριθμό
    if (local_max > maxElement)
    {
        maxElement = local_max;
    }
    // Έλεγχος επιτυχούς τερματισμού συγχρονισμού των mutex
    if (pthread_mutex_unlock(&mutex))
    {
        perror("pthread_mutex_unlock() error");
        exit(4);
    }

    // reassure that every thread has found its maximum value
    // απαραίτητο για να είμαστε σίγουροι ότι θα γίνει ταυτόχρονα ο παρακάτω υπολογισμός μεταξύ των άλλων νημάτων  
    pthread_barrier_wait(&our_barrier);

    // Αρχικοποίηση πίνακα με την απόσταση κάθε στοιχείου από το μέγιστο αριθμό 
    for (i = linesLocal; i < linesLocal + str->lines; i++)
    {
        for (j = 0; j < str->arraySize; j++)
        {
            str->arrayOriginalD[i][j] = maxElement - str->arrayOriginal[i][j];
        }
    }

    pthread_exit(NULL);
}
