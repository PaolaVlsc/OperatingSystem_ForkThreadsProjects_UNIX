/*  ;; ----------------------------------------------------------------
    ;;                   ΒΕΛΑΣΚΟ ΠΑΟΛΑ      cs161020
    ;; ----------------------------------------------------------------
    ;;           Τμήμα Μηχανικών Πληροφορικής και Υπολογιστών
    ;;               Εργαστήριο ΛΣΙΙ 2020/21 - Εργασία 1.2: 
    ;;                  Διεργασίες, Pipes & Νήματα
    ;; ----------------------------------------------------------------
    ;;  Υπεύθυνος μαθήματος: ΜΑΜΑΛΗΣ ΒΑΣΙΛΕΙΟΣ 
    ;;  Καθηγητές: ΙΟΡΔΑΝΑΚΗΣ ΜΙΧΑΛΗΣ
    ;; ----------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

char *phrase = "Hello from your first child";

void errorFork(); // Συνάρτηση για το διαχειρισμό αποτυχίας της κλήσης fork()
void errorWait(); // Συνάρτηση για το διαχειρισμό αποτυχίας της κλήσης wait()
 
int main()
{
    int pid0, pid1, pid2, pid3, pid4, pid5;
    int status;

    int file_descriptor[2], bytesread;
    char message[100];

    pid0 = getpid();

    pipe(file_descriptor);

    // έλεγχος για την pipe()
    if (file_descriptor < 0)
    {
        printf("Error. Exiting programme.");
        exit(-1);
    }

    pid1 = fork(); // ο P0 δημιουργεί το παιδί P1
    if (pid1 > 0)  // εκτέλεση κώδικα για P0
    {
        close(file_descriptor[1]);
        bytesread = read(file_descriptor[0], message, 100);                                                                    // Ο πατέρας P0 περιμένει εδώ μέχρι να λάβει το μήνυμα από το παιδί P1
        printf("I'm process P0: Read %d bytes from my child = %d (P1) the following message: %s\n", bytesread, pid1, message); // εκτύπωση μηνύματος που έλαβε από το παιδί
        close(file_descriptor[0]);

        // Δημιουργία παιδί P2
        pid2 = fork();

        if (pid2 > 0) // εκτέλεση κώδικα για P0
        {
            waitpid(pid2, &status, 0);
            // Κύριο μέρος της εργασίας της διεργασίας P0
            printf("Hi, I'm process P0: PID=%d, PPID=%d.\n", getpid(), getppid());
            execlp("ps", "ps", (char *)NULL);
        }
        else if (pid2 == 0) // Δημιουργία παιδιών της P2
        {
            pid3 = fork(); // Δημιουργία διεργασίας P3
            if (pid3 > 0)  // εκτέλεση κώδικα για P2
            {
                // έλεγχος για την wait()
                if (wait(&status) == -1) // περιμένει να εκτελέσει ο P3 πρώτα
                    errorWait();

                pid4 = fork(); // Δημιουργία διεργασίας P4
                if (pid4 > 0)  // εκτέλεση κώδικα για P2
                {
                    // έλεγχος για την wait()
                    if (wait(&status) == -1) // περιμένει να εκτελέσει ο P4 πρώτα
                        errorWait();

                    pid5 = fork(); // Δημιουργία διεργασίας P5
                    if (pid5 > 0)  // εκτέλεση κώδικα για P2
                    {
                        // έλεγχος για την wait()
                        if (wait(&status) == -1) // περιμένει να εκτελέσει ο P5 πρώτα
                            errorWait();
                        
                        // Κύριο μέρος της εργασίας της διεργασίας P2
                        printf("Hi, I'm process P2: PID=%d, PPID=%d.\n", getpid(), getppid());
                    }
                    else if (pid5 == 0) // εκτέλεση κώδικα για P5
                    {
                        printf("Hi, I'm process P5: PID=%d, PPID=%d.\n", getpid(), getppid());
                    }
                    else /* fork returns -1 on failure */
                    {
                        errorFork();
                    }
                }
                else if (pid4 == 0) // εκτέλεση κώδικα για P4
                {
                    printf("Hi, I'm process P4: PID=%d, PPID=%d.\n", getpid(), getppid());
                }
                else /* fork returns -1 on failure */
                    errorFork();
            }
            else if (pid3 == 0) // εκτέλεση κώδικα για P3
            {
                printf("Hi, I'm process P3: PID=%d, PPID=%d.\n", getpid(), getppid());
            }
            else /* fork returns -1 on failure */
                errorFork();
        }
        else /* fork returns -1 on failure */
            errorFork();
    }
    else if (pid1 == 0) // εκτέλεση κώδικα για P1
    {
        // Κύριο μέρος της εργασίας της διεργασίας P1
        printf("Hi, I'm process P1: PID=%d, PPID=%d.\n", getpid(), getppid());
        close(file_descriptor[0]);
        write(file_descriptor[1], phrase, strlen(phrase) + 1);
        close(file_descriptor[1]);
    }
    else /* fork returns -1 on failure */
        errorFork();

    return 0;
}

// Υλοποίηση συνάρτησης για το διαχειρισμό αποτυχίας της κλήσης fork()
void errorFork()
{
    perror("fork error"); /* display error message */
    exit(-3);
}

// Υλοποίηση συνάρτησης για το διαχειρισμό αποτυχίας της κλήσης wait()
void errorWait()
{
    perror("wait() error");
    exit(-2);
}
