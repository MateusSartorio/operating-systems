#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUM 8

pthread_mutex_t fuel_mutex;
int fuel = 50;

void* routine(void* arg) {
    pthread_mutex_lock(&fuel_mutex);

    pthread_mutex_unlock(&fuel_mutex);
    return NULL;
}

int main(int argc, char** argv, char** envp) {
    pthread_mutex_init(&fuel_mutex, NULL);
    
    pthread_t th[THREAD_NUM];
    for(int i = 0; i < THREAD_NUM; i++)
        if(pthread_create(&th[i], NULL, routine, NULL) == -1)
            printf("There was a problem creating the thread.\n");

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_join(th[i], NULL);

    pthread_mutex_destroy(&fuel_mutex);

    return 0;
}
