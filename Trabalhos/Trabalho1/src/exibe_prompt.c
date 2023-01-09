#include "../headers/exibe_prompt.h"

void exibe_prompt() {
    while(1) {
        printf("acsh> ");

        size_t size = 0;
        char* buffer = NULL;
        getline(&buffer, &size, stdin);
        
        char** vetor_comandos = NULL;
        if(strcmp(buffer, "\n")) {
            vetor_comandos = processa_prompt(buffer);

            if(vetor_comandos)
                executa_prompt(vetor_comandos);
        }
         
        if(buffer)
            free(buffer);
    }
}
