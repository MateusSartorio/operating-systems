#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int x;

    for(x = 0; x < 59; x++) {
        printf("\t0:%3d\n", x);
        sleep(1);
    }

    return 0;
}
