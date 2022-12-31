#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;

void* routine1(void* args) {
    printf("[Thread 1] Process id: %d\n", getpid());
    
    x++;

    sleep(2);
    
    printf("[Thread 1] Value of x is: %d\n", x);

    return NULL;
}

void* routine2(void* args) {
    printf("[Thread 2] Process id: %d\n", getpid());

    sleep(1);

    x++;

    sleep(1);

    printf("[Thread 2] Value of x is: %d\n", x);

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t t1, t2;
    
    int error_code = 0;
    if((error_code = pthread_create(&t1, NULL, routine1, NULL)))
        exit(error_code);

    if((error_code = pthread_create(&t2, NULL, routine2, NULL)))
        exit(error_code);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
