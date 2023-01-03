#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char** argv, char** envp) {
    pid_t pid1, pid2;
    
    int fd12[2];
    int fd23[2];
    int fd31[2];

    pipe(fd12);
    pipe(fd23);
    pipe(fd31);

    if( !(pid1 = fork()) ) {
        // Process 2
        close(fd12[1]);
        close(fd23[0]);
        close(fd31[0]);
        close(fd31[1]);

        sleep(1);
        int x = 0;
        read(fd12[0], (void*) &x, sizeof(int));
        printf("[PROCESS 2] I got: %d\n", x);
        x += 5;
        printf("[PROCESS 2] I passed: %d\n", x);        
        write(fd23[1], (void*) &x, sizeof(int));

        close(fd12[0]);
        close(fd23[1]);
    }
    else {
        if( !(pid2 = fork()) ) {
            // Process 3
            close(fd12[0]);
            close(fd12[1]);
            close(fd23[1]);
            close(fd31[0]);
            
            sleep(2);
            int x = 0;
            read(fd23[0], (void*) &x, sizeof(int));
            printf("[PROCESS 3] I got: %d\n", x);
            x += 5;
            printf("[PROCESS 3] I passed: %d\n", x);
            write(fd31[1], (void*) &x, sizeof(int));
            
            close(fd23[0]);
            close(fd31[1]);

        }
        else {
            // Process 1
            close(fd12[0]);
            close(fd23[0]);
            close(fd23[1]);
            close(fd31[1]);
            
            int x = 5;
            printf("[PROCESS 1] I passed: %d\n", x);
            write(fd12[1], (void*) &x, sizeof(int));
            sleep(3);
            read(fd31[0], (void*) &x, sizeof(int));
            printf("[PROCESS 1] I got: %d\n", x);

            close(fd12[1]);
            close(fd31[0]);

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    return 0;
}
