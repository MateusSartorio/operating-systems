#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if(pid == -1) {
        perror("Error forking\n");
        exit(1);
    }
    else if(pid == 0) {
        while(1) {
            printf("Some output\n");
            fflush(stdout);
            sleep(1);
        }      
    }
    else {
        sleep(3);
        kill(pid, SIGSTOP);
        sleep(3);
        kill(pid, SIGCONT);
        sleep(3);
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}
