#include <stdarg.h>
#include <stdio.h>

int min(int argc_count, ...) {
    va_list list;
    va_start(list, argc_count);
   
    int min = va_arg(list, int);
    for(int i = 0; i < argc_count - 1; i++) {
        int v = va_arg(list, int); 
        min = v < min ? v : min; 
    }

    return min;
}

int main(int argc, char** argv, char** envp) {
    printf("The minimum value is: %d\n", min(10, 1, 2, -1, 3, 4, 5, -10, 9, -7, -20));

    return 0;
}
