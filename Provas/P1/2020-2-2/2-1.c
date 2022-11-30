#include <bits/types/sigset_t.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

volatile sig_atomic_t count = 0;
volatile sig_atomic_t cinco = 0;

void handle_sigint(int signo) {
    count++;

    if(count == 5) {
        cinco = 1;
        count = 0;
    }
}

void handle_sigststp(int signo) {
    printf("count: %d\n", count);
    fflush(stdout);
}

int main(int argc, char** argv, char** envp) {
    void (*old_sigint)(int) = signal(SIGINT, handle_sigint);
    void (*old_sigstop)(int) = signal(SIGTSTP, handle_sigststp);
    
    sigset_t new_set;
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);
    sigaddset(&new_set, SIGTSTP);

    sigset_t old_set;

    
    while(1) {
        if(cinco) {
            sigprocmask(SIG_BLOCK, &new_set, &old_set);

            printf("Tem certeza que deseja sair? [y/n]: ");
            fflush(stdout);
            
            char c = 0; 
            scanf("%c", &c);
            
            if(c == 'y')
                exit(1);
            else
                cinco = 0;

            sigprocmask(SIG_UNBLOCK, &new_set, NULL);
        }
    }


    return 0;
}
