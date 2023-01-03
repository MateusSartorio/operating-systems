#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int fd[2];
    if(pipe(fd))
        exit(-1);

    pid_t pid1 = fork();
    if(pid1 == -1)
        exit(-1);
    else if(!pid1) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ping", "ping", "google.com", "-c", "5", NULL);
    }
    
    waitpid(pid1, NULL, 0);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    execlp("grep", "grep", "rtt", NULL);

    return 0;
}
