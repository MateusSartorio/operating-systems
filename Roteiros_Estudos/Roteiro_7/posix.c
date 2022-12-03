#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <assert.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char** argv, char** envp) {
    sem_t* sem = sem_open("/sema", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    assert(sem != SEM_FAILED);
    
    pid_t child_pid = fork();
    assert(child_pid != -1);

    if(child_pid == 0) {
        sem_wait(sem);
        printf("second\n");
        sem_close(sem);
        return 0;
    }

    printf("first\n");
    sem_post(sem);
    wait(NULL);

    printf("third\n");
    sem_close(sem);
    sem_unlink("/sema");

    return 0;
}
