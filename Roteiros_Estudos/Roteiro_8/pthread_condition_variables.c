#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define THREAD_AMMOUNT 6

unsigned fuel = 0;
pthread_mutex_t fuel_mutex;
pthread_cond_t cond_fuel;

void* fuel_filling(void* args) {
    for(int i = 0; i < 5; i++) {
        pthread_mutex_lock(&fuel_mutex);
        fuel += 60;
        printf("Filling fuel... %u\n", fuel);
        pthread_mutex_unlock(&fuel_mutex);
        pthread_cond_broadcast(&cond_fuel);
        sleep(1);
    }

    return NULL;
}

void* car(void* args) {
    pthread_mutex_lock(&fuel_mutex);
    
    while(fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&cond_fuel, &fuel_mutex);
    }
    fuel -= 40;
    printf("Got fuel now left: %u\n", fuel);
    pthread_mutex_unlock(&fuel_mutex);
    

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t th[THREAD_AMMOUNT];

    pthread_mutex_init(&fuel_mutex, NULL);
    pthread_cond_init(&cond_fuel, NULL);

    for(int i = 0; i < THREAD_AMMOUNT; i++)
        if(i < 2)
            pthread_create(&th[i], NULL, fuel_filling, NULL);
        else
            pthread_create(&th[i], NULL, car, NULL);
    
    for(int i = 0; i < THREAD_AMMOUNT; i++)
        pthread_join(th[i], NULL);

    pthread_mutex_destroy(&fuel_mutex);
    pthread_cond_destroy(&cond_fuel);

    return 0;
}
