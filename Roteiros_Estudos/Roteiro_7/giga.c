#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>

int main(int argc, char** argv, char** envp) {
    char* name = "my_semaphore";
    int VALUE = 2;

    sem_t* sema;
    sema = sem_open(name, O_CREAT, 0666, VALUE);

    sem_wait(sema);
    printf("Decrease semaphore by 1\n");
    
    sem_post(sema);
    printf("Add semaphore by 1\n");
    
    sem_close(sema);
    sem_unlink(name);

    return 0;
}
