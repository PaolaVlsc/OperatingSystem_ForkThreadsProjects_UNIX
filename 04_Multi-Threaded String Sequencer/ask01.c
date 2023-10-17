/*  ;; ----------------------------------------------------------------
    ;;                   ΒΕΛΑΣΚΟ ΠΑΟΛΑ      cs161020
    ;; ----------------------------------------------------------------
    ;;           Τμήμα Μηχανικών Πληροφορικής και Υπολογιστών
    ;;               Εργαστήριο ΛΣΙΙ 2020/21 - Εργασία 2.1: 
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

void *printThread01();
void *printThread02();
void *printThread03();

#define NUM_THREADS 3
pthread_t tid[NUM_THREADS]; /* array of thread IDs */
sem_t semA, semB, semC;     // declare 3 semaphores

#define LOOP 15

int main(int argc, char *argv[])
{
    int i, ret;

    // initialize semaphores
    sem_init(&semA, 0, 1); // Has value 1 so it can start from here
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);

    // δημιουργία 3 νημάτων
    pthread_create(&tid[0], NULL, printThread01, NULL);
    pthread_create(&tid[1], NULL, printThread02, NULL);
    pthread_create(&tid[2], NULL, printThread03, NULL);

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(tid[i], NULL);

    printf("\n\n End of main: reporting that all %d threads have terminated\n", i);

    return 0;
} /* main */


// Συνάρτηση που θα εκτελέσει το νήμα 1
void *printThread01()
{
    int i;

    for (i = 0; i < LOOP; i++)
    {
        sem_wait(&semA);
        printf("<one>");
        sem_post(&semB);
    }
}

// Συνάρτηση που θα εκτελέσει το νήμα 2
void *printThread02()
{
    int i;

    for (i = 0; i < LOOP; i++)
    {
        sem_wait(&semB);
        printf("<two>");
        sem_post(&semC);
    }
}

// Συνάρτηση που θα εκτελέσει το νήμα 3
void *printThread03()
{
    int i;

    for (i = 0; i < LOOP; i++)
    {
        sem_wait(&semC);
        printf("<three>");
        sem_post(&semA);
    }
}