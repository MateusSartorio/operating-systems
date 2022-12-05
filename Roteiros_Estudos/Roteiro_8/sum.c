#include <stdio.h>
#include <pthread.h>

unsigned long sum[4];

void* thread_fn(void* arg) {
    long id = (long) arg;
    int start = id * 2500000;
    
    for(int i = 0; i < 2500000; i++)
        sum[id] += (i + start);

    return NULL;
}

int main(int argc, char** argv, char** envp) {
    pthread_t p1, p2, p3, p4;

    pthread_create(&p1, NULL, thread_fn, (void*) 0);
    pthread_create(&p2, NULL, thread_fn, (void*) 1);
    pthread_create(&p3, NULL, thread_fn, (void*) 2);
    pthread_create(&p4, NULL, thread_fn, (void*) 3);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    printf("%lu\n", sum[0] + sum[1] + sum[2] + sum[3]);

    return 0;
}
