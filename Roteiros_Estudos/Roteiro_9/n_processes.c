#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <wait.h>

#define N 10

int main(int argc, char** argv, char** envp) {
    bool is_generator = true;

    int p[N+1][2];
    
    for(int i = 0; i < N+1; i++)
        pipe(p[i]);

    pid_t pid = 0;
    int count = 0;
    for(int i = 0; i < N; i++) {
        pid = fork();

        if(pid)
            break;
        else
            count++;
    }
    
    if(!count) {
        for(int i = 0; i < N+1; i++) {
            if(i != 0 && i != N) {
                close(p[i][0]);
                close(p[i][1]);
            }
            else if(i == 0)
                close(p[0][0]);
            else if(i == N)
                close(p[N][1]);
        }

        int x = 0;
        printf("[GENERATOR] Sent: %d\n", x);
        write(p[0][1], (void*) &x, sizeof(int));
        read(p[N][0], (void*) &x, sizeof(int));
        printf("[GENERATOR] Got: %d\n", x);
        
        close(p[0][1]);
        close(p[N][0]);
    }
    else {
        for(int i = 0; i < N+1; i++) {
            if(i != count && i != (count-1)) {
                close(p[i][0]);
                close(p[i][1]);
            }
            else if(i == count)
                close(p[count][0]);
            else if(i == (count-1))
                close(p[count-1][1]);
        }
        
        sleep(count);

        int x = 0; 
        read(p[count-1][0], (void*) &x, sizeof(int));
        printf("[CHILD %d] Got: %d\n", count, x);
        x++;
        printf("[CHILD %d] Sent: %d\n", count, x);
        write(p[count][1], (void*) &x, sizeof(int));
             
        close(p[count-1][0]);
        close(p[count][1]);
    }

    while(wait(NULL) != -1);

    return 0;
}
