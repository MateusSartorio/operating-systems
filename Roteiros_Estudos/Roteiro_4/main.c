#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>
#include <errno.h>

/*
void faz_pai() {
    printf("%d: sou o pai\n", getpid());
    int ret;
    pid_t p = wait(&ret);
    printf("Filho %d terminou com status %d, tambem vou terminar\n", p, WEXITSTATUS(ret));
    //sleep(10);
    exit(0);
}

void faz_filho() {
    printf("%d: Sou o filho e meu pai eh %d\n", getpid(), getppid());
    sleep(2);
    printf("%d: Sou o filho e meu pai eh %d\n", getpid(), getppid());
    exit(3);
}
*/
/*
int main(int argc, char** argv) {
    //char* arr[] = {"ls", ".", NULL};

    //execvp("ls", arr); 
    //printf("program finished executing\n");
    
    pid_t p = fork();
    
    if(p > 0)
        faz_pai();
    else
        faz_filho();
    
    int pid = fork();
        
    if(pid == 0)
        execlp("ping", "ping", "-c", "3", "google.com", NULL);

    printf

        return 0;
}
*/
