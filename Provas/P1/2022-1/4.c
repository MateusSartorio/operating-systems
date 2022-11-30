#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Eu sou o processo %d\n", getpid());

    int pid = fork();
    if(pid == -1) {
        perror("Erro no fork!!");
        exit(-1);
    }
    else if(pid == 0) {
        printf("Eu sou o processo %d\n", getpid());
        sleep(30);
        printf("Eu vou terminar na boa\n");
        exit(0);
    }
    else
        for(;;);

    return 0;
}
