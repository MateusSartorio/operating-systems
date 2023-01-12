#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define CHEFS_COUNT 10
#define STOVE_COUNT 4

#define min(a, b) { a < b ? a : b }

int stove_fuel[STOVE_COUNT] = { 100, 100, 100, 100 };
pthread_mutex_t stove_mutex[STOVE_COUNT];

void* routine(void* arg) {
    srand(time(NULL));
    
    for(int i = 0; i < STOVE_COUNT; i++) {
        if(!pthread_mutex_trylock(&stove_mutex[i])) {
            int fuel_needed = rand() % 30;
            
            if(stove_fuel[i] - fuel_needed < 0) {
                printf("No more fuel, going home.\n");
            }

            stove_fuel[i] -= fuel_needed;
            sleep(1);
            printf("Fuel left: %d\n", stove_fuel[i]);

            pthread_mutex_unlock(&stove_mutex[i]);
            break;
        }
        else {
            if(i == 3) {
                i = 0;
                printf("Busy...\n");
                sleep(1);
            }
        }

    }
        return NULL;
}

int main(int argc, char** argv, char** envp) {
    for(int i = 0; i < STOVE_COUNT; i++)
        pthread_mutex_init(&stove_mutex[i], NULL);
    
    pthread_t th[CHEFS_COUNT];
    for(int i = 0; i < CHEFS_COUNT; i++)
        pthread_create(&th[i], NULL, routine, NULL);

    for(int i = 0; i < CHEFS_COUNT; i++)
        pthread_join(th[i], NULL);
    
    for(int i = 0; i < STOVE_COUNT; i++)
        pthread_mutex_destroy(&stove_mutex[i]);

    return 0;
}
