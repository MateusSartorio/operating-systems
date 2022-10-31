#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char** argv) {
	pid_t spawn_pid = -5;
    int child_exit_status = -5;

    spawn_pid = fork();
    switch(spawn_pid) {
        case -1:
            perror("Hull Breach!\n");
            exit(1);
            break;
        case 0:
            printf("CHILD(%d): sleeping for 1 second\n", getpid());
            sleep(1);
            printf("CHILD(%d): converting into \'ls -a\'\n", getpid());
            execlp("ls", "ls", "-a", NULL);
            perror("CHILD exec failure\n");
            exit(2);
            break;
        default:
            printf("PARENT(%d): sleeping for 2 seconds\n", getpid());
            sleep(2);
            printf("PARENT(%d): waiting for child(%d) to terminate\n", getpid(), spawn_pid);
            pid_t actual_pid = waitpid(spawn_pid, &child_exit_status, 0);
            printf("PARENT(%d): child(%d) terminated, exiting!\n", getpid(), actual_pid);
            exit(0);
            break;
    }

	return 0;
}
