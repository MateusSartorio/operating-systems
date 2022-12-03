#include <stdbool.h>

bool p1_wants_to_enter = false, p2_wants_to_enter = false;

void process_1() {
    while(1) {
        p1_wants_to_enter = true;
        while(p2_wants_to_enter);
        // critical section
        p1_wants_to_enter = false;
    }
}

void process_2() {
    while(1) {
        p2_wants_to_enter = true;
        while(p1_wants_to_enter);
        // critical section
        p2_wants_to_enter = false;
    }
}
