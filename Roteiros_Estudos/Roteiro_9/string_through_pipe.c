#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define BUFFER_SIZE 200

int main() {
    int fd[2];
   
    if(pipe(fd) == -1) {
        perror("Error creating pipe: \n");
        exit(-1);
    }

    pid_t pid = fork();
    
    if(pid == -1) {
        perror("Error forking: ");
        exit(-1);
    }
    if(!pid) {
        close(fd[0]);
        
        char str[BUFFER_SIZE] = {0};
        printf("Input string: ");
        fgets(str, BUFFER_SIZE, stdin);
        str[strlen(str) - 1] = '\0';
        
        write(fd[1], (void*) &str, BUFFER_SIZE*sizeof(char));

        close(fd[1]);
    }
    else {
        close(fd[1]);
        wait(NULL);
        
        char str[BUFFER_SIZE] = { 0 };
        read(fd[0], (void*) &str, BUFFER_SIZE*sizeof(char));

        printf("The string read is: %s\n", str);

        close(fd[0]);
    }

    return 0;
}
