// Haleah Mauck
// 2/24/2026
// CS-314-006
// Lab4 monitorasaurus
// hmauck@pdx.edu
// this is the implementation file for the monitorasaurus program
 
//valgrind --leak-check=full --show-leak-kinds=all
 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>
#include "monitorasaurus.h"


 
#ifdef NOISY_DEBUG 
# define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__)
#else // NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif // NOISY_DEBUG

static int v = 0;
volatile sig_atomic_t run =  1;


// Desc: Signal handler function, sets the global run variable to false
// Inputs: int, the signal 
// Returns: void 
void handleSignal(int signal);

// Desc: Runs a loop of refreshing the screen, at the user specifed interval
// Inputs: ints, the amount of times the screen has refreshed, and the interval at which to refresh
// a unsigned int, the width to display on screen, a semphore to use as a counter
// Returns: Int, 1 if successful, 0 if popen fails 
int refresh(int refreshCount, int refreshInterval, size_t width, sem_t * bobSemaphore);
 

int main(int argc, char * argv[]) {

    int refreshInterval = DEFAULT_INTERVAL;
    int refreshCount = 0;
    size_t width = DEFAULT_COLS;
    struct sigaction bobSignal;
    //initalize semphore, value init to 0, use sem_init(), second param also 0
    sem_t bobSemaphore;
    sem_init(&bobSemaphore, 0, 0);

    {

        int opt = -1;
        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
                case 'i':
                    refreshInterval = atoi(optarg);
                     break;
                case 'c':
                    refreshCount = atoi(optarg);
                    break;
                case 'w':
                    width = atoi(optarg);
                    break;
                case 'v':
                    v = 1;
                    break;
                case 'h':
                    printf("Usage: monitorasaurus -[i:c:w:vh]\n");
                    printf("        -i #    set the refresh interval, in seconds. Default is 2.\n");
                    printf("        -c #    set the count of how many times the output will refresh before exiting.\n");
                    printf("                Default is 0 (don't stop).\n");
                    printf("        -w #    set the width of text to display. Default is 100.");
                    printf("        -v      minimal verbose output\n");
                    printf("        -h      show this amazing help and exit\n");
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }

    //connect signal handler to signalHandle function 
    memset(&bobSignal, 0, sizeof(bobSignal));
    bobSignal.sa_handler = handleSignal;
    if (sigaction(SIGINT, &bobSignal, NULL)== -1) {
        fprintf(stderr, "Sigaction failed\n");
        exit(EXIT_FAILURE);
    }

    //call refresh loop function
    if (refresh(refreshCount, refreshInterval, width, &bobSemaphore) == 0) {
        fprintf(stderr, "Semaphore never reached timeout\n");
        exit(EXIT_FAILURE);
    }

    //destroy semaphore
    sem_destroy(&bobSemaphore); 
 
    exit(EXIT_SUCCESS);

}


// Desc: Signal handler function, sets the global run variable to false
// Inputs: int, the signal 
// Returns: void 
void handleSignal(int signal) {
    run = 0;
}


// Desc: Runs a loop of refreshing the screen, at the user specifed interval
// Inputs: ints, the amount of times the screen has refreshed, and the interval at which to refresh
// a unsigned int, the width to display on screen, a semphore to use as a counter
// Returns: Int, 1 if successful, 0 if popen fails 
int refresh(int refreshCount, int refreshInterval, size_t width, sem_t * bobSemaphore) {
    int count = 0;
    struct timespec ts;
    FILE * bob = NULL;
    char line[MAX_LINE_LEN];
    int success = 1;
        
    //while (run (run is set to false when user presses control c) && count < refreshCount)
    while(run && (refreshCount == INFINITE_COUNT || count < refreshCount)) {

        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += refreshInterval;
        //pass timespec as second param to sem_timedwait()
        //what is the first parameter?
        if (sem_timedwait(bobSemaphore, &ts) == -1) {

            //wait for timeout, the return value with be -1
            //the value for magic gloably variable errno is set
            if(errno == EINTR) {
                //control c was pressed, break out of while loop 
                break;
            }
            else if (errno == ETIMEDOUT) {
                //semphore timeout occured
                //update display 
                //clear the screen,  
                printf(CLEAR_SCREEN);

                //process command output in popen loop
                bob = popen(CMD, "r");
                if (bob == NULL) {
                    fprintf(stderr, "popen failed\n");
                    success = 0;
                    break;
                }
                while (fgets(line, sizeof(line), bob)) {
                    if (strlen(line) > width) {
                        line[width] = '\n';
                        line[width + 1] = '\0';
                    }
                    fputs(line, stdout);
                }
                pclose(bob);
                ++count;
            }
     
        }
    }
    
    return success;
}

  