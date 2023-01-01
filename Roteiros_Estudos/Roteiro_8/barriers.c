#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_AMMOUNT 3

pthread_barrier_t b;

void* routine(void* arg) {
    pthread_barrier_wait(&b);
    printf("Cool bro.\n");
    
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t th[THREAD_AMMOUNT];

    pthread_barrier_init(&b, NULL, 3);

    for(int i = 0; i < THREAD_AMMOUNT; i++) {
        if(i == 0) {
            sleep(2);
            pthread_create(&th[i], NULL, routine, NULL);
        }
        else
            pthread_create(&th[i], NULL, routine, NULL);
    }

    for(int i = 0; i < THREAD_AMMOUNT; i++)
        pthread_join(th[i], NULL);

    pthread_barrier_destroy(&b);

    return 0;
}
