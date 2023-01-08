#include "../headers/prompt.h"

void exibe_prompt() {
    while(1) {
        printf("acsh> ");

        size_t size = 0;
        char* buffer = NULL;
        getline(&buffer, &size, stdin);

        processa_prompt(buffer);

        free(buffer);
    }
}
