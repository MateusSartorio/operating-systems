#include "../headers/recebe_prompt.h"
#include <stdio.h>

char* recebe_prompt() {
    printf("acsh> ");

    size_t size = 0;
    char* buffer = NULL;
    getline(&buffer, &size, stdin);
    
    if(strcmp(buffer, "\n") == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}
