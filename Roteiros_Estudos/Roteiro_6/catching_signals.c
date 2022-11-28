#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void catch_sigint(int signo) {
    char* message = "Caught SIGINT, sleeping for 5 seconds\n";
    write(STDOUT_FILENO, message, 38);
    raise(SIGUSR2);
    sleep(5);
}

void catch_sigusr2(int signo) {
    char* message = "Caught SIGUSR2, exiting\n";
    write(STDOUT_FILENO, message, 25);
    exit(0);
}

int main() {
    struct sigaction SIGINT_action = {0};
    struct sigaction SIGUSR2_action = {0};
    struct sigaction ignore_action = {0};
    


    return 0;
}
