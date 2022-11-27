#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void it_horloge(int sig) {
    printf("recepcao do sinal %d: SIGALARM\n", sig);
    printf("atencao, o principal reassume o comando\n");
}

void it_quit(int sig) {
    printf("recepcao do sinal %d: SIGINT\n", sig);
    printf("Por que eu?\n");
    exit(1);
}

int main() {
    unsigned sec;
    
    signal(SIGINT, it_quit);
    signal(SIGALRM, it_horloge);

    printf("Armando o alarme para 10 segundos\n");
    sec = alarm(10);

    printf("valor retornado pelo alarm: %d\n", sec);
    printf("Paciencia.. Vamos esperar 3 segundos com sleep\n");
    sleep(3);
    printf("Rearmando alarme com 5 segundos antes de chegar o sinal precedente\n");
    sec = alarm(5);
    printf("Novo valor retornado por alarm: %d\n", sec);

    printf("Principal em loop infinito (CTRL C para acabar)\n");

    for(;;);
}
