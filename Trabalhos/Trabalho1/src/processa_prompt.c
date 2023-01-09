#include "../headers/processa_prompt.h"

#define QTD_MAX_COMANDOS 5

// Remove espaços em branco no comeco da string e espacoes em branco ou quebra de linha do final
// Aloca uma string nova na heap e a retorna
// Não altera a string original
static char* trim(const char* str) {
    if(!str || strlen(str) == 0) {
        perror("String nula ou vazia recebida - trim().\n");
        exit(1);
    }
    
    char* new_str = strdup(str);

    unsigned i = 0;
    while(new_str[i] == ' ' || new_str[i] == '\n')
        i++;

    unsigned j = strlen(new_str) - 1;
    while(new_str[j] == ' ' || new_str[j] == '\n')
        j--;
    
    char* trimmed_str = (char*) malloc((j-i+2)*sizeof(char));
    
    int k = 0;
    for(int l = i; l <= j; l++)
        trimmed_str[k++] = new_str[l];
    trimmed_str[k] = '\0';
    
    free(new_str);

    return trimmed_str;
}

char** processa_prompt(char* prompt) {
    char** vetor_comandos = (char**) malloc((QTD_MAX_COMANDOS+1)*sizeof(char*));

    // Separa os comandos individuais em tokens e os coloca do vetor de comandos
    // O vetor de comandos eh terminado por NULL
    char* token = strtok(prompt, "<3");
    char* trimmed_token = NULL;
    
    int i = 0;
    while(token) {
        trimmed_token = trim(token);

        vetor_comandos[i] = trimmed_token;
        i++;
        
        // Verifica se mais de 5 comandos foram passados
        if(i > 5) {
            printf("Por favor, digite no maximo 5 comandos por vez.\n");
            libera_vetor_comandos(vetor_comandos);
            return NULL;
        }

        token = strtok(NULL, "<3");
    }

    vetor_comandos[i] = NULL;

    return vetor_comandos;
}

void libera_vetor_comandos(char** vetor_comandos) {
    if(vetor_comandos == NULL) {
        printf("Vetor de comandos nulo recebido - libera_vetor_comandos().\n");
        exit(1);
    }

    for(int i = 0; vetor_comandos[i] != NULL; i++)
        free(vetor_comandos[i]);

    free(vetor_comandos);
}
