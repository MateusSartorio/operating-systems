#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t counter = 2;

void my_handler(int signal_number) {
    counter++;
    printf("%d ", counter);
    fflush(stdout);
    exit(0);
}

int main() {
    pid_t pid;

    struct sigaction sa;
    sa.sa_handler = my_handler;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    printf("%d ", counter);
    fflush(stdout);
    
    if((pid = fork()) == 0)
        while(1);

    kill(pid, SIGUSR1);
    waitpid(pid, NULL, 0);
    counter--;
    printf("%d ", counter);
    fflush(stdout);

    return 0;
}
