#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/wait.h>

int delay;
void childhandler(int signo);

int main(int argc, char** argv) {
    pid_t pid;

    signal(SIGCHLD, childhandler);

    pid = fork();
    if(pid == 0)
        execvp(argv[2], &argv[2]);
    else {
        sscanf(argv[1], "%d", &delay);
        sleep(delay);
        printf("Programa %s exceeded limit of %d seconds!\n", argv[2], delay);
        kill(pid, SIGKILL);
    }
    
    return 0;
}

void childhandler(int signo) {
    int status;
    pid_t pid;

    pid = wait(&status);
    printf("Child %d terminated within %d seconds.\n", pid, delay);
}
