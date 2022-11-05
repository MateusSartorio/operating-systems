#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if(pid < 0) {
        printf("Erro no fork().\n");
        exit(1);
    }
    else if(pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        
        printf("[PARENT] Filho terminou com status %d.\n", status);
    }
    else {
        if(argc < 2)
            printf("Lista de argumentos invalida.\n");
        else
            execvp(*(argv + 1), argv + 1);
        
    }

    return 0;
}
