#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

void handler(int sigtype) {
    printf("Programa terminando...\n");
    exit(0);
}

int main(int argc, char** argv) {
    struct sigaction action;
    
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    sigaction(SIGINT, &action, NULL);

    while(true) {
        printf("Digite CTRL-C para sair do loop\n");
        sleep(1);
    }

    return 0;
}
