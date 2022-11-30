#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int a;

void fn() {
    a++;
    printf("X %d\n", a);
    exit(0);
}

int main() {
    int val;
    a = 0;

    printf("Y %d\n", a);

    if(fork() == 0)
        fn();

    wait(&val);

    printf("Z %d\n", a);

    return 0;
}
