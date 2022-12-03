#include <stdbool.h>
#define N 10

typedef int Mutex;

int count = 0;
Mutex mutex, empty, full;

void producer() {
    while(true) {
        int item = produce_item();
        if(count == N)
            sleep(empty);
        
        lock(mutex);
        insert_item(item);
        unlock(mutex);

        if(count == 1)
            wakeup(full);
    }
}

void consumer() {
    while(true) {
        if(count == 0)
            sleep(full);

        lock(mutex);
        int item = remove_item();
        count--;
        unlock(mutex);

        if(count == N - 1)
            wakeup(empty);

        consume_item(item);
    }
}
