#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 2


void* routine(void* arg) { 
    int value = rand() % 6;
    int* result = (int*) malloc(sizeof(int));
    *result = value;
    printf("The result is: %d\n", *result);
    pthread_exit((void*) result);
}

int main(int argc, char** argv, char** envp) {
    pthread_t th[THREAD_NUM];

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_create(&th[i], NULL, routine, NULL);

    pthread_exit(0);

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_join(th[i], NULL);

    return 0;
}
