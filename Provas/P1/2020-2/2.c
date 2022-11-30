#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include<unistd.h>
#include <wait.h>

int main() {
    pid_t pid, pid_filho;
    int status;

    printf("\nAntes do fork pid = %d\n", getpid());
    fflush(stdout);

    pid = fork();

    char* args[] = {"./build", NULL};

    if(pid == 0) {
        printf("pai = %d e filho %d\n", getppid(), getpid());
        fflush(stdout);
        execv("./build", args);
    }
    else if(pid != -1) {
        pid_filho = wait(&status);
        printf("Depois do wait feito pelo pid = %d obtendo pid_filho = %d\n", getpid(), pid_filho);
        fflush(stdout);
        exit(0);
    }
    else {
        printf("Erro no fork\n");
        exit(-1);
    }

    return 0;
}
