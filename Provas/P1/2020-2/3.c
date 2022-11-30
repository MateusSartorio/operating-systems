#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int a;

int main() {
    a = 0;

    if(fork() == 0) {
        a++;
        printf("%d", a);
        exit(0);
    }
    else {
        pid_t pid = 0;
        int estado = 0;

        pid = wait(&estado);
    }

    printf("%d", a);
    
    return 0;
}
