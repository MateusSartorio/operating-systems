#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    char* ls_args[3] = {"ls", "-l", NULL};
    pid_t c_pid, pid;
    int status;

    c_pid = fork();

    if(c_pid == 0) {
        /* CHILD */
        printf("Child: exercuting ls\n");

        //execute ls
        execvp(ls_args[0], ls_args);

        //only get here if exec failed
        perror("execvp failed\n");
    }
    else if(c_pid > 0) {
        /* PARENT */
        if(wait(&status) < 0) {
            perror("wait\n");
            exit(1);
        }

        printf("Parent: finished\n");
    }
    else {
        perror("fork failed\n");
        exit(1);
    }

    return 0;
}
