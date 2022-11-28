#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void handle_sigstp(int signo) {
    printf("cool bro\n");
}

void handle_sigcont(int signo) {
    printf("Input number: ");
    fflush(stdout);
}

int main(int argc, char** argv) {
    /*
    struct sigaction sa;

    sa.sa_handler = handle_sigstp;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa, NULL);
    */

    struct sigaction sa;
    sa.sa_handler = handle_sigcont;
    sigaction(SIGCONT, &sa, NULL);

    // signal(SIGTSTP, handle_sigstp);
    //signal(SIGCONT, handle_sigcont);

    int x;
    printf("Input number: ");
    scanf("%d", &x);
    printf("Result %d * 5 = %d\n", x, x * 5);
}
