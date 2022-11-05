#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if(pid < 0) {
        printf("Erro ao fazer o fork\n");
        exit(1);
    }
    else if(pid == 0) {
        printf("[FILHO]: meu pid eh %d\n", getpid());
        sleep(1000);
    }
    else {
        printf("[PAI]: meu pid eh %d\n", getpid());
        int status;
        int testa = wait(&status);
        
        if(testa == -1)
            printf("Testa eh -1\n");

        printf("[PAI] testa: %d, status: %d\n", testa, status);
    }

    return 0;
}
