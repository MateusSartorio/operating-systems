#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int n = atoi(argv[1]);

    printf("%d\n", n);
    
    int pid = 0;
    for(int i = 0; i < n; i++)
        if(!(pid = fork()))
            break;
    
    if(!pid)
        sleep(20);

    return 0;
}
