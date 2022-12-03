#include <stdbool.h>

bool p1_wants_to_enter = false, p2_wants_to_enter = true;
unsigned favored = 1;

void process_1() {
    p1_wants_to_enter = true;
    favored = 2;
    
    while(p2_wants_to_enter && favored == 2);
    // critical section
    p1_wants_to_enter = false;
}

void process_2() {
    p2_wants_to_enter = true;
    favored = 1;

    while(p1_wants_to_enter && favored == 1);
    //critical section
    p2_wants_to_enter = false;
}
