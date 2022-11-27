#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void nullfcn() {}

void sleep2(int secs) {
    if(signal(SIGALRM, nullfcn)) {
        perror("error: reception signal");
        exit(-1);
    }
    alarm(secs);
    pause();
}

int main() {
    if(fork() == 0) {
        sleep(3);
        printf("hello, sleep\n");
    }
    else {
        sleep2(3);
        printf("hello, sleep2\n");
    }

    exit(0);
}
