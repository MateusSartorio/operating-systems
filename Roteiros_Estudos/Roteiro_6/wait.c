#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <wait.h>
#include <spawn.h>

int main() {
    int child_status;

    char* arg_list[] = {
        "ls",
        "-l",
        "/",
        NULL
    };

    spawn("ls", arg_list);

    wait(&child_status);
    
    if(WIFEXITED(child_status))
        printf("the child process exit normally, with exit code %d\n", WIFEXITED(child_status));

    return 0;
}
