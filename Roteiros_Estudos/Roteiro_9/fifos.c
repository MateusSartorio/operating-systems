#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char** argv, char** envp) {
    if(mkfifo("myfifo", 0777) == -1) {
        if (errno != EEXIST) {
            perror("Could not create or find fifo: ");
            return 1;
        }
    }
    
    int fd = open("myfifo", O_WRONLY);
    
    int x = 97;
    write(fd, (void*) &x, sizeof(int));
    
    close(fd);

    return 0;
}
