#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int pid;

    printf("Eu sou o processo pai, PID = %d, e eu vou criar um filho.\n", getpid());
    pid = fork();

    if(pid == -1) {
        perror("Eh impossivel criar um filho");
        _exit(-1);
    }
    else if(pid == 0) {
        printf("Eu sou o filho, PID = %d. Estou vivo mas vou dormir um pouco. Use of comando ps -l para conferir o meu estado e o do meu pai. Daqui a pouco eu acordo.\n", getpid());
        sleep(60);
        printf("Sou eu de novo, o filho. Acordei mas vou terminar agora. Use ps -l novamente.\n");
        exit(0);
    }
    else {
        printf("Bem, agora eu vou esperar pelo termino da execucao do meu filho. Tchau!\n");
        wait(NULL);
    }



	return 0;
}
