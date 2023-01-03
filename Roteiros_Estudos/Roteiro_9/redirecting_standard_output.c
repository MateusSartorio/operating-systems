#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <time.h>

#define DELAY 2
#define ITERATIONS 5
#define RANGE 10
#define ARRAY_SIZE 100

int main() {
    
    int fd[2];
    pipe(fd);
    
    pid_t pid = fork();
    
    if(!pid) {
        srand(time(NULL));
        close(fd[0]);
        
        for(int i = 0; i < ITERATIONS; i++) {
            int num = (rand() % RANGE) + 1;
            printf("[CHILD] Sending %d.\n", num);
            write(fd[1], (void*) &num, sizeof(int));
            sleep(DELAY);
        }
        
        close(fd[1]);
    }
    else {
        close(fd[1]);

        int array[ARRAY_SIZE] = { 0 };
        unsigned array_position = 0;
        int num = 0;

        while(read(fd[0], (void*) &num, sizeof(int))) {
            printf("[PARENTE] Got %d, the array now is: [ ", num);
            
            array[array_position] = num;
            array_position++;

            for(int j = 0; j < array_position; j++)
                if(j != array_position - 1)
                    printf("%d, ", array[j]);
                else
                    printf("%d", array[j]);
            printf(" ]\n");

            sleep(2*DELAY);
        }
        
        wait(NULL);
        close(fd[0]);
    }

    return 0;
}
