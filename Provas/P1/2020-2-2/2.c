#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

volatile sig_atomic_t count = 0;

void handle_sigint(int signo) {
    count++;
}

int main(int argc, char** argv, char** envp) {
    


    return 0;
}