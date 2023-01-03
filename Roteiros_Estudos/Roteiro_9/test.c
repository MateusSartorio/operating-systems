#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int fd[2];
    pipe(fd);

    if(!fork()) {
        close(fd[0]);
        close(fd[1]);
        sleep(2);

        int x = 10;
    
        write(fd[1], (void*) &x, sizeof(int));

        close(fd[1]);

        return 0;
    }
    
    close(fd[1]);
    
    int x = 0;
    read(fd[0], (void*) &x, sizeof(int));
    printf("[BEFOR WAIT] Got %d\n", x);

    wait(NULL);
    
    close(fd[0]);

    return 0;
}
