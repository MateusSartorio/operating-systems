#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>
#include <fcntl.h>

#define DELAY 2

int main(int argc, char** argv, char** envp) {
    printf("[CONSUMER] Started.\n");

    int fd = open("sum", O_RDONLY);
     
    int sum = 0;
    int x = 0;
    while(read(fd, (void*) &x, sizeof(int))) {
        sleep(DELAY);
        printf("[CONSUMER] Got: %d\n", x);
        sum += x;
    }

    close(fd);

    fd = open("sum", O_WRONLY);
    
    write(fd, (void*) &sum, sizeof(int));

    close(fd);

    printf("[CONSUMER] Finished.\n");

    return 0;
}
