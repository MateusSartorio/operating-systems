#include <stdbool.h>
/*
void down(int* S) {
    while(*S <= 0);
    *S--;
}

void up(int* S) {
    *S++;
}

void producer() {
    while(true) {
        item = produce_item();
        down(empty);
        lock(mutex);
        insert_item(item);
        unlock(mutex);
        up(full);
    }
}

void consumer() {
    while(true) {
        down(full);
        lock(mutex);
        item = consume_item();
        unlock(mutex);
        up(empty);
        consume_item(item);
    }
}
*/
