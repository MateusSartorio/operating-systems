#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define THREAD_NUM 8
#define DELAY 2

int dice_values[THREAD_NUM] = { 0 };
int status[THREAD_NUM] = { 0 };

pthread_barrier_t barrier_rolled_dice;
pthread_barrier_t barrier_calculated_status;

void* routine(void* arg) {
    int index = *(int*) arg;

    while(1) {
        dice_values[index] = (rand() % 6) + 1;

        pthread_barrier_wait(&barrier_rolled_dice);
        pthread_barrier_wait(&barrier_rolled_dice);

        if(status[index])
            printf("(%d rolled %d) I won.\n", index, dice_values[index]);
        else
            printf("(%d rolled %d) I lost.\n", index, dice_values[index]);
        }
    return arg;
}

int main() {
    srand(time(NULL));
    
    pthread_barrier_init(&barrier_rolled_dice, NULL, THREAD_NUM + 1);
    pthread_barrier_init(&barrier_rolled_dice, NULL, THREAD_NUM + 1);

    pthread_t th[THREAD_NUM];
    
    for(int i = 0; i < THREAD_NUM; i++) {
        int* a = (int*) malloc(sizeof(int));
        *a = i;
        pthread_create(&th[i], NULL, routine, (void*) a);
    }
    
    while(1) {
        pthread_barrier_wait(&barrier_rolled_dice);
        
        int max = 0;
        for(int i = 0; i < THREAD_NUM; i++)
            if(dice_values[i] > max)
                max = dice_values[i];

        for(int i = 0; i < THREAD_NUM; i++)
            if(dice_values[i] == max)
                status[i] = 1;
            else
                status[i] = 0;
        
        printf("===== NEW ROUND STARTED =====\n");

        pthread_barrier_wait(&barrier_rolled_dice);
        
        sleep(DELAY);
    }

    for(int i = 0; i < THREAD_NUM; i++) {
        void* a = NULL;
        pthread_join(th[i], &a);
        free(a);
    }

    pthread_barrier_destroy(&barrier_rolled_dice);
    pthread_barrier_destroy(&barrier_rolled_dice);

    return 0;
}
