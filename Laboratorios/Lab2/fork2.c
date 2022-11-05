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
        printf("[CHILD] My pid is: %d\n", getpid());
        sleep(60); 
        printf("[CHILD]: I'm finished.\n");
        return 42;
    }
    else {
        printf("[PARENT] My pid is %d\n", getpid());
        
        int wstatus;
        waitpid(pid, &wstatus, WUNTRACED);
        
        if(WIFEXITED(wstatus))
            printf("[PARENT]: Child returned with code %d.\n", WEXITSTATUS(wstatus));
        else if(WIFSIGNALED(wstatus)) {
            int status = WTERMSIG(wstatus);

            if(status == 9)
                printf("[PARENT]: Child was killed by a signal and ended with code %d.\n", WTERMSIG(wstatus));
            else if(status == 19)
                printf("[PARENT]: Child was suspended by a signal and ended with code %d.\n", WTERMSIG(wstatus));
            else
                printf("[PARENT]: Something else happened to the child. Code: %d.\n", WTERMSIG(wstatus));
        }
    }

	return 0;
}
