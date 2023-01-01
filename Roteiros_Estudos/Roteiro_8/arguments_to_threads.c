#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PRIMES_SIZE 10

int primes[PRIMES_SIZE] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* args) {
    printf("%d ", *(int*) args);

    return NULL;
}

int main(int argc, char** argv, char** envp) {
    pthread_t th[PRIMES_SIZE];

    for(int i = 0; i < PRIMES_SIZE; i++) {
        /* 
        int* j = (int*) malloc(sizeof(int));
        *j = i;
        */
        pthread_create(&th[i], NULL, routine, (void*) &primes[i]);
    }

    for(int i = 0; i < PRIMES_SIZE; i++)
        pthread_join(th[i], NULL);


    return 0;
}
