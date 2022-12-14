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
   
    SIGINT_action.sa_handler = catch_sigint;
    sigfillset(&SIGINT_action.sa_mask);
    SIGINT_action.sa_flags = 0;

    SIGUSR2_action.sa_handler = catch_sigusr2;
    sigfillset(&SIGUSR2_action.sa_mask);
    SIGUSR2_action.sa_flags = 0;

    ignore_action.sa_handler = SIG_IGN;

    sigaction(SIGINT, &SIGINT_action, NULL);
    sigaction(SIGUSR2, &SIGUSR2_action, NULL);
    sigaction(SIGTERM, &ignore_action, NULL);
    sigaction(SIGHUP, &ignore_action, NULL);
    sigaction(SIGQUIT, &ignore_action, NULL);

    printf("SIGTERM, SIGHUP and SIGQUIT are disabled.\n");
    printf("Send a SIGUSR2 signal to kill this program.\n");
    printf("Send a SIGINT signal to sleep 5 seconds, then kill this program.\n");
    
    printf("My id is: %d\n", getpid());

    while(1)
        pause();

    return 0;
}
