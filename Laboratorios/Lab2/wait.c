#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, char** argv) {
    pid_t pid = fork();

    if(pid < 0)

	return 0;
}
