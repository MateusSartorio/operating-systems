#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 4

pthread_mutex_t mutex;

void* routine(void* arg) {
    while(1) {
        if(!pthread_mutex_trylock(&mutex)) {
            printf("We got the lock.\n");
            sleep(1);
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        else {
            printf("Didn't get the lock.\n");
            sleep(1);
        }
    }
    
    return NULL;
}

int main(int argc, char** argv, char** envp) {
    pthread_mutex_init(&mutex, NULL);

    pthread_t th[THREAD_COUNT];

    for(int i = 0; i < THREAD_COUNT; i++)
        pthread_create(&th[i], NULL, routine, NULL);


    for(int i = 0; i < THREAD_COUNT; i++)
        pthread_join(th[i], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
