#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char** argv) {
    pid_t pid = fork();
    
    if(pid < 0)
        fprintf(stderr, "Fork failed!\n");
    else if(pid == 0) {
        sleep(20); 
        printf("[CHILD]: I'm finished.\n");
        return 42;
    }
    else {
        printf("[PARENT]: Waiting on child.\n");
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus))
            printf("[PARENT]: Child returned with code %d.\n", WEXITSTATUS(wstatus));
        else if(WIFSIGNALED(wstatus))
            printf("[PARENT]: Child was killed by a signal and ended with code %d.\n", WTERMSIG(wstatus));
    }

	return 0;
}
