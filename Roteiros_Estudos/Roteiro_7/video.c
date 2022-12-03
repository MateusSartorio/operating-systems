#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char** argv, char** envp) {
    int i;
    key_t shm_key;
    int shm_id;
    int* shrd_value;

    pid_t pid;
    int fork_count;
    unsigned sem_value;

    ftok("/dev/null", 65);
    shm_id = shmget(shm_key, sizeof(int), 0644 | IPC_CREAT);
    
    if(shm_id < 0) {
        perror("shmget");
        exit(shm_id);
    }

    shrd_value = shmat(shm_id, NULL, 0);

    return 0;
}
