#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    signal(SIGCLD, SIG_IGN);

    if(fork() != 0)
        while(1);
    exit(0);
}
