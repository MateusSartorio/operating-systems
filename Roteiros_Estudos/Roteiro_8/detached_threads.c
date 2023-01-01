#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 2

void* routine(void* arg) {
    printf("Hello bro.\n");
    return NULL;
}

int main(int argc, char** argv, char** envp) {
    pthread_t th[THREAD_NUM];
    
    /*
    for(int i = 0; i < THREAD_NUM; i++) {
        pthread_create(&th[i], NULL, routine, NULL);
        pthread_detach(th[i]);
    }
    */
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for(int i = 0; i < THREAD_NUM; i++)
        pthread_create(&th[i], &attr, routine, NULL);

    pthread_attr_destroy(&attr);

    pthread_exit(0);
}
