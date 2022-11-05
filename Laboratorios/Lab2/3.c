#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if(pid < 0) {
        printf("Erro ao fazer o fork\n");
        exit(1);
    }
    else if(pid == 0) {
        printf("[FILHO]: meu pid eh %d\n", getegid());
        sleep(1000);
    }
    else {
        printf("[PAI]: meu pid eh %d\n", getegid());
        int testa = wait();
    }

    return 0;
}
