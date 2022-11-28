#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int x;
    printf("Input number: ");
    scanf("%d", &x);
    printf("Result %d * 5 = %d\n", x, x * 5);

    return 0;
}
