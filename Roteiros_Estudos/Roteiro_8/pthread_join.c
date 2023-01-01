#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* roll_dice(void* args) {
    int* value = (int*) malloc(sizeof(int));
    
    srand(time(NULL));
    *value = (rand() % 6) + 1;

    return (void*) value;
}

int main(int argc, char** argv, char** envp) {
    pthread_t th;

    pthread_create(&th, NULL, roll_dice, NULL);
    
    int* value = NULL;
    pthread_join(th, (void**) &value);

    printf("Dice roll: %d\n", *value);

    free(value);

    return 0;
}
