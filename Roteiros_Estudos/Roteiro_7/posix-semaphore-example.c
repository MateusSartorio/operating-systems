#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define SEM_MUTEX_NAME "/sem-mutex"
#define SEM_BUFFER_COUNT_NAME "/sem-buffer-count"
#define SEM_SPOOL_SIGNAL_NAME "/sem-spool-signal"

//Buffer data structures
#define MAX_BUFFERS 10
char buf[MAX_BUFFERS][100];
int buffer_index;
int buffer_print_index;

sem_t* mutex_sem;
sem_t* buffer_count_sem;
sem_t* spool_signal_sem;

void* producer(void* arg);
void* spooler(void* arg);

int main(int argc, char** argv) {
    

    return 0;
}