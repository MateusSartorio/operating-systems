#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_AMMOUNT 16
#define THREAD_ROUTINE_LOOP_SIZE 1000000

unsigned mails = 0;

pthread_mutex_t mutex;

void* routine(void* args) {
    printf("Thread %d has started\n", *(int*) args);
    for(int i = 0; i < THREAD_ROUTINE_LOOP_SIZE; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }

    return args;
}

int main(int argc, char** argv, char** envp) {
    pthread_t p[THREAD_AMMOUNT];

    pthread_mutex_init(&mutex, NULL);
    
    int error_code = 0;
    for(int i = 0; i < THREAD_AMMOUNT; i++) {
        int* j = (int*) malloc(sizeof(int));
        *j = i;
        if((error_code = pthread_create(&p[i], NULL, routine, (void*) j)))
            exit(error_code);
    }

    for(int i = 0; i < THREAD_AMMOUNT; i++) {
        int* j;
        if((error_code = pthread_join(p[i], (void**) &j)))
            exit(error_code);
        else {
            printf("Thread %d has finished\n", *(int*) j);
        }
    }

    printf("The ammount of mails is: %d\n", mails);

    pthread_mutex_destroy(&mutex);

    return 0;
}
