#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char** argv, char** envp) {
    pid_t pid = fork();

    if(!pid) {
        int file = open("ping_result.txt", O_WRONLY | O_CREAT, 0777);
        int file2 = dup2(file, STDOUT_FILENO);
        close(file);
        
        execlp("ping", "ping", "-c", "1", "google.com", NULL);

        return 1;
    }
    else {
        int status;
        wait(&status);
        return 0;
        if(WIFEXITED(status))
            printf("Child returned with exit code: %d\n", WEXITSTATUS(status));
    } 
    
    return 0;
}
