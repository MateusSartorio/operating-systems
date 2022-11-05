#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if(pid < 0) {
        fprintf(stderr, "Error forking\n");
        return 1;
    }
    else if(pid == 0) {
        printf("[Child] about to load command.\n");
        execlp("/usr/bin/ls", "ls", "-la", NULL);
        printf("[CHILD] Great! It worked\n");
    }
    else {
        printf("[PARENT] Wating on child.\n");
        wait(NULL);
        printf("[PARENT] Child finished.\n");
    }


    return 0;
}
