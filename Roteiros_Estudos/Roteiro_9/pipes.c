#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int fd[2];
    
    if(pipe(fd)) {
        perror("Error creating pipe");
        exit(-1);
    }

    pid_t pid = fork();
   
    if(!pid) {
        close(fd[0]);
        int x = 0;
        printf("Input a number: ");
        scanf("%d", &x);
        write(fd[1], (void*) &x, sizeof(int));
        close(fd[1]);
    }
    else {
        close(fd[1]);
        int x = 0;
        wait(NULL);
        read(fd[0], (void*) &x, sizeof(int));
        printf("The number read from the pipe is: %d\n", x);
    }
    
    return 0;
}
