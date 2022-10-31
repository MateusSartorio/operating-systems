#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>

int main(int argc, char** argv) {
    pid_t cpid;

    cpid = fork();

    if(cpid == 0) {
        //child

        while(1);
    }
    else if(cpid > 0) {
        //parent

        while(1);
    }
    else {
        perror("fork");
        _exit(1);
    }

	return 0;
}
