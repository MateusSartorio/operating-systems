#include "../headers/recebe_prompt.h"
#include <stdio.h>
#include <string.h>

int recebe_prompt(char* prompt) {
    printf("acsh> ");
    
    memset(prompt, 0, TAMANHO_PROMPT);
    fgets(prompt, TAMANHO_PROMPT, stdin);
    if(strcmp(prompt, "\n") == 0)
        return -1;

    return 0;
}