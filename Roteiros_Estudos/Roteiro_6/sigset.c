#include <bits/types/sigset_t.h>
#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGQUIT);

    if(sigprocmask(SIG_BLOCK, &sigset, NULL))
        perror("sigprocmask");

    return 0;
}
