#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main(int argc, char** argv, char** envp) {
    int fd;
    int VALUE = 1;

    sem_t* mutex;
    mutex = sem_open("mutex", O_CREAT, 0666, VALUE);

    printf("Mom comes home.\n");
    sem_wait(mutex);
    printf("Mom checks the fridge.\n");

    fd = open("fridge", O_CREAT | O_RDWR | O_APPEND, 0777);

    if(lseek(fd, 0, SEEK_END)) {
        printf("Mom goes to buy milk...\n");
        sleep(2);
        write(fd, "milk ", 5);
        printf("Mom puts milk in the fridge and leaves.\n");
        if(lseek(fd, 0, SEEK_END) > 5)
            printf("What a waste of food! The fridge can not hold so much milk!\n");
    }
    else
        printf("Mom closes the fridge and leaves.\n");

    close(fd);
    sem_close(mutex);
    sem_unlink("mutex");

    return 0;
}
