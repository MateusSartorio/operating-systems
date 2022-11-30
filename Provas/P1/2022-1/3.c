#include <stdio.h>
#include <unistd.h>

int main() {
    if(fork() && (fork())) {
        if(fork() || fork()) {
            fork();
        }
    }
    
    printf("Hello bro\n");

    return 0;
}
