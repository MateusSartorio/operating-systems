
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char** argv, char** envp) {
    sem_t* sema = (sem_t*) malloc(sizeof(sem_t));
    int pshared = true;
    int value = 1;
    int status;

    status = sem_init(sema, pshared, value);
    if(status) {
        perror("sem_init() failed.\n");
        exit(status);
    }

    sem_wait(sema);
    printf("Decrease semaphore by 1\n");
    
    sem_post(sema);
    printf("Add semaphore by 1\n");
    
    sem_destroy(sema);

    return 0;
}
