#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void trata_signal(int num) {
    signal(SIGINT, trata_signal);
    
    printf("Operacao negada.\n");
    fflush(stdout);
}

int main() {
    if(signal(SIGINT, trata_signal) == SIG_ERR)
        printf("Erro no signal\n");

    for(;;)
        sleep(10);

    return 0;
}


