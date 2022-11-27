#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void it_fils() {
    printf("- Sim, sim. E darei um jeito nisso eu mesmo... ARGHH...\n");
    kill(getpid(), SIGINT);
}

void fils() {
    signal(SIGUSR1, it_fils);
    printf("- Papai conte maus uma vez, como foi que voce me fez?\n");
    while(1);
}

int main() {
    int pid;

    if((pid = fork()) == 0)
        fils();
    else {
        sleep(2);
        printf("- Filhinho, quer ir passear no reino dos mortos?\n");
        kill(pid, SIGUSR1);
        sleep(1);
    }

    exit(0);
}
