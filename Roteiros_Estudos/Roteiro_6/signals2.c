#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    unsigned counter = 0;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    while(1) {
        printf("Look I can count to %u\n", counter++);
        usleep(250000);
    }

    return 0;
}
