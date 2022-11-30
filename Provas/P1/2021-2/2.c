#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int i = (fork() && fork() && fork());

    if(!i) {
        printf("I am a child\n");
        sleep(30);
    }
    else {
        int status = 0;
        pid_t pid = 0;

        while((pid = wait(&status)) != -1) {
            if(WIFEXITED(status))
                printf("Child exited normally with code %d.\n", WEXITSTATUS(status));
            else if(WIFSIGNALED(status))
                printf("Child exited because of signal %d\n", WSTOPSIG(status));
        }
    }

    return 0;
}
