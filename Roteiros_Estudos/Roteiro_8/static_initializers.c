#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

void* routine(void* arg) {

    return NULL;
}

int main(int argc, char** argv, char** envp) {
    pthread_t th[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_create(&th[i], NULL, routine, NULL);


    for(int i = 0; i < THREAD_NUM; i++)
        pthread_join(th[i], NULL);


    return 0;
}
