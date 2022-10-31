#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if(pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0)
        printf("[CHILD]: PID: %d - PPID: %d\n", getpid(), getppid());
    else
        printf("[PARENT]: PID: %d - PPID: %d\n", getpid(), getppid());

	return 0;
}
