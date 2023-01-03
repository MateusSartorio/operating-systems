#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char** argv, char** envp) {
    int fd1[2];
    int fd2[2];

    pipe(fd1);
    pipe(fd2);

    pid_t pid = fork();

    if(!pid) {
        close(fd1[1]);
        close(fd2[0]);
        
        int x = 0;
        read(fd1[0], (void*) &x, sizeof(int));
        printf("[CHILD] Got: %d\n", x);
        x *= 4;
        printf("[CHILD] Sent: %d\n", x);
        write(fd2[1], (void*) &x, sizeof(int));

        close(fd1[0]);
        close(fd2[1]);

        return 0;
    }
    
    close(fd1[0]);
    close(fd2[1]);

    int x = 5;
    printf("[PARENT] Sent %d\n", 5);
    write(fd1[1], (void*) &x, sizeof(int));
    read(fd2[0], (void*) &x, sizeof(int));
    printf("[PARENT] Got: %d\n", x);

    close(fd1[1]);
    close(fd2[0]);

    return 0;
}
