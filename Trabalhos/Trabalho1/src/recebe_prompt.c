#include "../headers/recebe_prompt.h"

int recebe_prompt(char* prompt) {
    printf("acsh> ");
    
    fgets(prompt, TAMANHO_PROMPT, stdin);
    if(strcmp(prompt, "\n") == 0)
        return -1;

    return 0;
}