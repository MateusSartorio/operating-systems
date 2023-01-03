#include <alloca.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#define ARRAY_SIZE 5
#define DELAY 1

int main(int argc, char** argv, char** envp) {
    printf("[PRODUCER] Started.\n");

    int* arr = (int*) alloca(ARRAY_SIZE*sizeof(int));
    
    srand(time(NULL));
    for(int i = 0; i < ARRAY_SIZE; i++)
        *(arr + i) = rand() % 10;

    int fd = open("sum", O_WRONLY);

    for(int i = 0; i < ARRAY_SIZE; i++) {
        sleep(DELAY);
        printf("[PRODUCER] Produced: %d\n", *(arr + i));
        write(fd, (void*) (arr + i), sizeof(int));
    }

    close(fd);

    fd = open("sum", O_RDONLY); 
        
    int sum = 0;
    read(fd, (void*) &sum, sizeof(int));

    printf("[PRODUCER] The sum is: %d\n", sum);

    close(fd);

    printf("[PRODUCER] Finished.\n");

    return 0;
}
