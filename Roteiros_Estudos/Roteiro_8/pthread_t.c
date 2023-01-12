#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <syscall.h>

#define THREAD_NUM 8
#define DELAY 2

void* routine(void* arg) {
    int index = *(int*) arg;

    //printf("I am thread %zd\n", pthread_self());
    
    printf("I am a thread with thread_id %d\n", (int) syscall(SYS_gettid));

    return arg;
}

int main() {
    pthread_t th[THREAD_NUM];
    
    printf("I am the main function, my thread id is: %zd\n", pthread_self());

    for(int i = 0; i < THREAD_NUM; i++) {
        int* a = (int*) malloc(sizeof(int));
        *a = i;
        pthread_create(&th[i], NULL, routine, (void*) a);
        printf("Created thread with id of: %zd\n", th[i]);
    }
    
    for(int i = 0; i < THREAD_NUM; i++) {
        void* a = NULL;
        pthread_join(th[i], &a);
        free(a);
    }

    return 0;
}

