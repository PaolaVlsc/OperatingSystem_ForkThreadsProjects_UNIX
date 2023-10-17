/*  ;; ----------------------------------------------------------------
    ;;                   ΒΕΛΑΣΚΟ ΠΑΟΛΑ      cs161020
    ;; ----------------------------------------------------------------
    ;;           Τμήμα Μηχανικών Πληροφορικής και Υπολογιστών
    ;;               Εργαστήριο ΛΣΙΙ 2020/21 - Εργασία 1.3: 
    ;;                  Διεργασίες, Pipes & Νήματα
    ;; ----------------------------------------------------------------
    ;;  Υπεύθυνος μαθήματος: ΜΑΜΑΛΗΣ ΒΑΣΙΛΕΙΟΣ 
    ;;  Καθηγητές: ΙΟΡΔΑΝΑΚΗΣ ΜΙΧΑΛΗΣ
    ;; ----------------------------------------------------------------
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


// Δήλωση mutex για συγχρονισμό
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long total_sum = 0; // καθολική μεταβλητή


// Μια δομή infoCalculate, με την οποία θα στέλνουμε πολλά δεδομένα στα νήματα
struct infoCalculate
{
    int sizeArraylocal;
    int arraySize;
    int *arrayOriginal;
    int thread_number;
};

void *calculateSqaureSum(void *arg);			    // πρότυπο συνάρτησης που θα εκτελούν τα νήματα
void initArrayA(int mainArrayA[], int arrayA_size);	// πρότυπο συνάρτησης για την αρχικοποίηση του αρχικού πίνακα

int main()
{
    
    int *mainArrayA;	// Αρχικός πίνακας A
    int arrayA_size;	// Μέγεθος πίνακα Α: n
    int number_threads;	// Αριθμός νημάτων: p
    int i;
    double time_spent = 0.0;	// Χρόνος εκτέλεσης
 
    // Ζητάει το μέγεθος του πίνακα: n
    printf("Give length of array A: ");
    scanf("%d", &arrayA_size);

    // allocate memory for mainArrayA
    mainArrayA = (int *)malloc(sizeof(int) * arrayA_size);
    // Check if malloc was successfully completed
    if (mainArrayA == NULL)
    {
        printf("Error: Not available memory\n");
        exit(EXIT_FAILURE);
    }

    // Ζητάει τον αριθμό των νημάτων: p
    printf("Give number of threads:  ");
    scanf("%d", &number_threads);
	
    // Αρχικοποίηση διανύσματος Α με τη χρήση συνάρτησης initArrayA
    initArrayA(mainArrayA, arrayA_size);

    /* Εκτύπωση διανύσματος A */
    printf("\nContents of array A\n");
    for (i = 0; i < arrayA_size; i++)
    {
        printf("mainArrayA[%d] = %d\n", i, mainArrayA[i]);
    }

    /* Διαμοιρασμός πόσα στοιχεία θα λάβει το κάθε νήμα */
    int localSizeArray_Thread;
    localSizeArray_Thread = arrayA_size / number_threads;

    
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
    struct infoCalculate data_thread;
    data_thread.sizeArraylocal = localSizeArray_Thread;
    data_thread.arrayOriginal = mainArrayA;
    data_thread.arraySize = arrayA_size;
    data_thread.thread_number = 0;

    /* Έναρξη: χρόνος εκτέλεσης 
    clock_t begin = clock();
    */
    
    for (i = 0; i < number_threads; i++)
    {
        // Έτοιμη συνάρτηση για τη δημιουργία νημάτων. θα εκτλέσουν τη συνάρτηση calculateSquareSum και θα πάρουν δεδομένα τη δομή data_thread
        pthread_create(&array_threads[i], NULL, calculateSqaureSum, (void *)&data_thread);
    }

    // Εγγύηση ότι το αρχικό νήμα θα εκτυπώσει το αποτέλεσμα αφού θα υπολογιστούν τα αθροίσματα
    for (i = 0; i < number_threads; i++)
        pthread_join(array_threads[i], NULL);

    // Απελευθέρωση πόρου
    pthread_mutex_destroy(&mutex);

    
    /* Τέλος: χρόνος εκτέλεσης 
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);
    */
   
    printf("\n\nTotal_sum = %ld\n", total_sum);
    printf("In main: Finish and Exit\n");


    return 0;
}

// Συνάρτηση: αρχικοποίηση αρχικού πίνακα A
void initArrayA(int mainArrayA[], int arrayA_size)
{
    /// srand(time(NULL));

    int i;

    printf("\nGive numbers for mainArrayA\n");
    for (i = 0; i < arrayA_size; i++)
    {
        printf("arrayA[%d]: ", i);
        scanf("%d", &mainArrayA[i]);

        /* Αλλιώς: αρχικοποίηση με τυχαία νούμερα */ 
        // mainArrayA[i] = rand() % 10 + 1;
    }
}


//Υλοποίηση συνάρτησης που θα εκτελούν τα νήματα για τον υπολογισμό
void *calculateSqaureSum(void *arg)
{
    struct infoCalculate *str = (struct infoCalculate *)arg;

    int i;
    int local_sum = 0;

    // Έλεγχος και δημιουργία συγχρονισμού με mutex
    if (pthread_mutex_lock(&mutex))
    {
        perror("mutex_lock");
        exit(3);
    }

    str->thread_number = str->thread_number + 1;
    printf("\n\nHello I am thread %d (not real thread id) \n", str->thread_number);

    // Αρχικοποίηση από ποιο σημείο του πίνακα θα ξεκινήσουν τον υπολογισμό κάθε νήμα
    printf("Contents of \"local\" A assigned to me\n");
    int y = (str->thread_number - 1) * str->sizeArraylocal;

    // Υπολογισμός του local_sum ανά νήμα
    for (i = y; i < y + str->sizeArraylocal; i++)
    {
        printf("mainArrayA[%d] = %d\n", i, str->arrayOriginal[i]);
        local_sum += str->arrayOriginal[i] * str->arrayOriginal[i];
    }

    // Εκτύπωση του local_sum 
    printf("\nThread %d - Local_sum  = %d\n", str->thread_number, local_sum);

    // Ενημέρωση καθολικής μεταβλητής
    total_sum += local_sum;

    // Έλεγχος επιτυχούς τερματισμού συγχρονισμού των mutex
    if (pthread_mutex_unlock(&mutex))
    {
        perror("pthread_mutex_unlock() error");
        exit(4);
    }

    pthread_exit(NULL);
}
