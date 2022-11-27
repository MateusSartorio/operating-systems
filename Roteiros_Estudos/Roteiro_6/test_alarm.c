#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void it_horloge(int sig) {
    printf("recepcao do sinal %d: SIGALARM\n", sig);
}

int main() {
    unsigned sec;

    signal(SIGALRM, it_horloge);
    printf("Fazendo alarm(5)\n");
    sec = alarm(5);

    printf("Valor retornado por alarm: %d\n", sec);
    printf("Principal em loop infinito (CTRL C para acabar)\n");

    for(;;);
}
