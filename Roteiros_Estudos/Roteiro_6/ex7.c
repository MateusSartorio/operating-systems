#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

pid_t pid;

void handle_int(int signo) {
    printf("Yep seems to be working bro\n");

    kill(pid, SIGKILL);
}

int main(int argc, char** argv) {
    pid = fork();

    if(pid == -1) {
        return 1;
    }
    else if(pid == 0) {
        while(1) {
            printf("Some text\n");
            usleep(50000);
        }
    }
    else {
        struct sigaction sa;
        sa.sa_handler = handle_int;
        sigaction(SIGINT, &sa, NULL);
        //signal(SIGINT, handle_int);
        wait(NULL);
    }

    return 0;
}
