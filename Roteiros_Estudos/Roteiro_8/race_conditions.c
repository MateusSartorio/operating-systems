#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

int mails = 0;
sem_t s;
sem_t* named_s = NULL;

void* routine(void* args) {
    for(int i = 0; i < 100000; i++) {
        sem_wait(named_s);
        mails++;
        sem_post(named_s);
    }

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t p1, p2;

    sem_init(&s, 0, 1);
    named_s = sem_open("/cool-semaphore3", O_CREAT | O_EXCL, 1);
    
    int error_code = 0;
    if((error_code = pthread_create(&p1, NULL, routine, NULL)))
        return error_code;
    if((error_code = pthread_create(&p2, NULL, routine, NULL)))
        return error_code;
    if((error_code = pthread_join(p1, NULL)))
        return error_code;
    if((error_code = pthread_join(p2, NULL)))
        return error_code;
    
    sem_unlink("/cool-semaphore3");
    sem_close(named_s);
    sem_destroy(&s);
    
    printf("mails: %d\n", mails);

    return 0;
}
