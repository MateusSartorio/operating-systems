#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <alloca.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int compara(const void* p1, const void* p2) {
    return strcmp(*((char**) p1), *((char**) p2));
}

int main(int argc, char** argv, char** envp) {
    qsort(argv + 1, argc - 1, sizeof(char*), compara);

    pid_t pid = fork();
    if(pid == -1) {
        perror("Erro no fork");
        exit(-1);
    }
    else if(pid == 0) {
        int N = argc + 1;
        char** argumentos = alloca(sizeof(char*)*N);
        
        for(int i = 0; i < argc; i++)
            argumentos[i] = argv[i];
        argumentos[N - 1] = NULL;

        execve("./busca_binaria", argumentos, envp);
    }
    else {
        int status = 0;
        pid_t cpid = wait(&status);
        printf("Child with pid %d exited with status %d\n", cpid, status);
    }

    return 0;
}