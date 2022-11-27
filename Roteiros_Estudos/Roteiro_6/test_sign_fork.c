#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void fin() {
    printf("SIGINT para os processos %d\n", getpid());
    exit(0);
}

int main() {
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, fin);

    if(fork() > 0) {
        printf("processo pai: %d\n", getpid());
        while(1);
    }
    else {
        printf("processo filho: %d\n", getpid());
        while(1);
    }

    exit(0);
}
