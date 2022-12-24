#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t sem_fuel;
// pthread_mutex_t mutex_fuel;

int fuel = 50;

void* routine(void* args) {
    // pthread_mutex_lock(&mutex_fuel);
    sem_wait(&sem_fuel);

    fuel += 50;
    printf("Current value is %d\n", fuel);

    // pthread_mutex_unlocks(&mutex_fuel);
    sem_post(&sem_fuel);
}

int main(int argc, char** argv) {
    pthread_t th[THREAD_NUM];
    
    // pthread_mutex_init(&mutex_fuel, NULL);
    sem_init(&sem_fuel, 0, 1);

    for(int i = 0; i< THREAD_NUM; i++)
        if(pthread_create(&th[i], NULL, &routine, NULL))
            perror("Failed to create thread");
    
    for(int i = 0; i < THREAD_NUM; i++)
        if(pthread_join(th[i], NULL))
            perror("Failed to join thread");

    // pthread_mutex_destroy(&mutex_fuel);
    sem_destroy(&sem_fuel);

    return 0;
}