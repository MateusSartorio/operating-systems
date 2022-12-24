#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define THREAD_NUM 16

sem_t semaphore;

void* routine(void* args) {
    printf("(%d) Waiting in the login queue\n", *(int*)args);
    sem_wait(&semaphore);
    printf("(%d) Loggin in\n", *(int*)args);
    sleep(rand() % 5 + 1);
    printf("(%d) Logged out\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
}

int main(int argc, char** argv) {
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 4);

    for(int i = 0; i < THREAD_NUM; i++) {
        int* a = (int*) malloc(sizeof(int));
        *a = i;
        pthread_create(&th[i], NULL, routine, a);
    }

    for(int i = 0; i < THREAD_NUM; i++) {
        pthread_join(th[i], NULL);
    }


    return 0;
}