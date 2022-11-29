#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MESSAGE "you can't stop me!\n"
#define MSGLEN 19

static volatile sig_atomic_t keep_running = 1;

static void sig_handler(int this_signal) {
    if(this_signal == SIGINT) {
        write(STDOUT_FILENO, MESSAGE, MSGLEN);
        keep_running = 0;
    }
}

int main() {
    unsigned counter = 0;
    int sleep_result;

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    
    while(keep_running) {
        printf("Look I can count to %u\n", counter++);
        sleep_result = usleep(250000);


        if(sleep_result != 0) {
            perror("");
        }
    }

    return EXIT_SUCCESS;
}
