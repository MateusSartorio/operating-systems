#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    int x = 2;

    pid_t pid = fork();

    if(pid == -1)
        exit(pid);

    if(!pid)
        x++;

    sleep(2);
    
    printf("Process id: %d, the value of x is: %d\n", getpid(), x);

    if(pid != 0)
        wait(NULL);

    return 0;
}
