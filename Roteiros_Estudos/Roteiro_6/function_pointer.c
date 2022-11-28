#include <stdio.h>

int add_one(int input) {
    return input + 1;
}

int main() {
    int (*fp_arg)(int) = add_one;
    printf("10 + 1 = %d\n", fp_arg(10));

    return 0;
}
