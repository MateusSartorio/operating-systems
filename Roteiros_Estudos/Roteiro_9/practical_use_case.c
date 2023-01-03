#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

#define PROCESSES_COUNT 11

int calculate_sum(int* arr, int lo, int hi) {
    int local_sum = 0;

    for(int i = lo; i <= hi; i++)
        local_sum += arr[i];

    return local_sum;
}


int main(int argc, char** argv, char** envp) {
    int arr[] = { 1, 2, 3, 4, 1, 2, 7, 9, 1, 5 };
    int arr_size = sizeof(arr)/sizeof(int);
    int delta = arr_size/(PROCESSES_COUNT);
    
    int fd[2];
    pipe(fd);

    pid_t pid[PROCESSES_COUNT];
    
    for(int i = 0; i < PROCESSES_COUNT; i++) {
        pid[i] = fork();
        
        if(!pid[i]) {
            close(fd[0]);

            int local_sum = 0;
            if(i != PROCESSES_COUNT - 1)
                local_sum = calculate_sum(arr, delta*i, delta*(i + 1) - 1);
            else
                local_sum = calculate_sum(arr, delta*i, arr_size - 1);
            
            write(fd[1], (void*) &local_sum, sizeof(int));

            close(fd[1]);
            return 0;
        }
    }
    
    

    close(fd[1]);
    
    int final_sum = 0;
    int local_sum[PROCESSES_COUNT] = { 0 };
    for(int i = 0; i < PROCESSES_COUNT; i++) {
        read(fd[0], (void*) &local_sum[i], sizeof(int));
        final_sum += local_sum[i];
    }

    printf("The total sum is: %d\n", final_sum);

    close(fd[0]);

    return 0;
}
