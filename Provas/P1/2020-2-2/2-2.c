#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

int main() {
    sigset_t new_set;
    sigfillset(&new_set);
    sigprocmask(SIG_BLOCK, &new_set, NULL);

    pid_t pid = fork();

    if(pid == -1) {
        perror("Erro no fork");
        exit(-1);
    }
    else if(pid == 0) {
        execlp("ls", "ls", "-l", NULL); 
    }
    else {
        int status = 0;
        pid_t cpid = 0;

        cpid = wait(&status);

        if(WIFEXITED(status))
            printf("Child exited normally with code %d\n", WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
            printf("Child was terminated by signal of number %d\n", WTERMSIG(status));
        else if(WIFSTOPPED(status))
            printf("Child was stopped by signal of number %d\n", WSTOPSIG(status));

        sigprocmask(SIG_UNBLOCK, &new_set, NULL);
    }

    return 0;
}
