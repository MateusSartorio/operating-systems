#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine(void* args) {
    for(int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char** argv, char** envp) {
    pthread_t p1, p2;
    
    pthread_mutex_init(&mutex, NULL);



    pthread_mutex_destroy(&mutex);

    return 0;
}
