#include <stdbool.h>

bool flag[2] = { false, false };
int turn = 0;

void p1() {
    flag[0] = true;
    while(flag[1]) {
        if(turn != 0) {
            flag[0] = false;
            while(turn != 0) {
                // busy wait
            }
            flag[0] = true;
        }
    }

    // critical section
    
    turn = 1;
    flag[0] = false;
}

void p2() {
    flag[1] = true;
    while(flag[0]) {
        flag[1] = false;
        while(turn != 1) {
            // busy wait
        }
        flag[1] = true;
    }
    
    // critical section

    turn = 0;
    flag[1] = false;
}
