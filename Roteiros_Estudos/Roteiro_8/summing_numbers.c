#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct boundary {
    unsigned lo;
    unsigned hi;
};

unsigned sum = 0;
int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

pthread_mutex_t mutex;

/*
void* routine(void* args) {
    struct boundary* b = (struct boundary*) args;
    
    unsigned* local_sum = (unsigned*) malloc(sizeof(unsigned));
    *local_sum = 0;
    for(int i = b->lo; i <= b->hi; i++)
        *local_sum += primes[i];

    return (void*) local_sum;
}
*/

/*
int main() {
    pthread_t th[2];
    
    struct boundary b[] = { { 0, 4 }, { 5, 9 } };

    for(int i = 0; i < 2; i++)
        pthread_create(&th[i], NULL, routine, (void*) &b[i]);
    
    unsigned* results[2];
    for(int i = 0; i < 2; i++)
        pthread_join(th[i], (void**) &results[i]);
    
    for(int i = 0; i < 2; i++) {
        sum += *results[i];
        free(results[i]);
    }
   
    printf("The sum is: %u\n", sum);

    return 0;
}
*/

void* routine(void* args) {
    struct boundary* b = (struct boundary*) args;

    for(int i = b->lo; i <= b->hi; i++) {
        pthread_mutex_lock(&mutex);
        sum += primes[i];
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t th[2];

    struct boundary b[] = { {0, 4}, {5, 9} };

    for(int i = 0; i < 2; i++)
        pthread_create(&th[i], NULL, routine, (void*) &b[i]);

    for(int i = 0; i < 2; i++)
        pthread_join(th[i], NULL);

    printf("The sum is: %u\n", sum);

    pthread_mutex_destroy(&mutex);
}
