#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PRODUCERS_AMMOUNT 2
#define CONSUMERS_AMMOUNT 2

#define PRODUCER_COOLDOWN 2
#define CONSUMER_COOLDOWN 1

#define PRODUCER_CAPACITY 15
#define CONSUMER_CAPACITY 15

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
unsigned buffer_head = 0;

pthread_mutex_t mutex;
pthread_cond_t buffer_full, buffer_empty;

void* producer(void* arg) {
    unsigned identifier = *(int*) arg;
    
    srand(identifier*time(NULL));

    printf("[PRODUCER %d] Has started.\n", identifier);
    sleep(PRODUCER_COOLDOWN);

    for(int i = 0; i < PRODUCER_CAPACITY; i++) {
        pthread_mutex_lock(&mutex);
        
        while(buffer_head >= BUFFER_SIZE) {
            printf("[PRODUCER %d] The buffer is full. Waiting...\n", identifier);
            pthread_cond_wait(&buffer_full, &mutex);
        }
        
        buffer[buffer_head] = (rand() % 100) + 1;
        buffer_head++;
        
        printf("[PRODUCER %d] Pushed the value %d, the buffer now is: [ ", identifier, buffer[buffer_head - 1]);

        for(int j = 0; j < buffer_head; j++)
            if(j != buffer_head - 1)
                printf("%d, ", buffer[j]);
            else
                printf("%d", buffer[j]);
        printf(" ]\n");

        pthread_cond_broadcast(&buffer_empty);

        pthread_mutex_unlock(&mutex);
        sleep(PRODUCER_COOLDOWN);
    }

    printf("[PRODUCER %d] Has finished.\n", identifier);

    return arg;
}

void* consumer(void* arg) {
    unsigned identifier = *(int*) arg;
    
    printf("[CONSUMER %d] Has started.\n", identifier);
    
    sleep(CONSUMER_COOLDOWN);

    for(int i = 0; i < CONSUMER_CAPACITY; i++) {
        pthread_mutex_lock(&mutex);
        while(buffer_head <= 0) {
            printf("[CONSUMER %d] Buffer empty. Waiting...\n", identifier);
            pthread_cond_wait(&buffer_empty, &mutex);
        }
        
        buffer_head--;
        printf("[CONSUMER %d] Got the value %d, the buffer now is: [ ", identifier, buffer[buffer_head + 1]);
        for(int j = 0; j < buffer_head; j++)
            if(j != buffer_head - 1)
                printf("%d, ", buffer[j]);
            else
                printf("%d", buffer[j]);
        printf(" ]\n");

        pthread_cond_broadcast(&buffer_empty);
        pthread_mutex_unlock(&mutex);
        sleep(CONSUMER_COOLDOWN);
    }

    printf("[CONSUMER %d] Has finished.\n", identifier);

    return arg;
}

int main(int argc, char** argv, char** envp) {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&buffer_full, NULL);
    pthread_cond_init(&buffer_empty, NULL);
    
    pthread_t producers[PRODUCERS_AMMOUNT];
    for(int i = 0; i < PRODUCERS_AMMOUNT; i++) {
        int* j = (int*) malloc(sizeof(int));
        *j = i;
        pthread_create(&producers[i], NULL, producer, (void*) j);
    }

    pthread_t consumers[CONSUMERS_AMMOUNT];
    for(int i = 0; i < CONSUMERS_AMMOUNT; i++) {
        int* j = (int*) malloc(sizeof(int));
        *j = i;
        pthread_create(&consumers[i], NULL, consumer, (void*) j);
    }

    for(int i = 0; i < PRODUCERS_AMMOUNT; i++) {
        void* j = NULL;
        pthread_join(producers[i], &j);
        free(j);
    }
    
    for(int i = 0; i < CONSUMERS_AMMOUNT; i++) {
        void* j = NULL;
        pthread_join(consumers[i], &j);
        free(j);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&buffer_full);
    pthread_cond_destroy(&buffer_empty);

    return 0;
}
