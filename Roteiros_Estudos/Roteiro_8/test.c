#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 2;
    int* b = &a;

    free(b);

    return 0;
}
