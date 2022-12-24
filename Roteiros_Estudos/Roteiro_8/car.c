#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define THREAD_NUM 4

struct car {
    int year;
    char* name;
};

struct car* make_car(int year, char* name) {
    struct car* c = (struct car*) malloc(sizeof(struct car));
    c->year = year;
    c->name = strdup(name);
}

void destroi_car(struct car* c) {
    free(c->name);
    free(c);
}

int car_get_year(struct car* c) {
    return c->year;
}

char* car_get_name(struct car* c) {
    return c->name;
}

sem_t semaphore;

void* routine(void* args) {
    struct car* c = make_car(*((int*) args), "cool bro");

    return c;
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
        struct car* return_value = NULL;
        pthread_join(th[i], (void**) &return_value);
        printf("the car name is: %s, and its year is %d\n", car_get_name(return_value), car_get_year(return_value));
    }


    return 0;
}