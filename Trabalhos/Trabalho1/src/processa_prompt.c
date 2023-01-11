#include "../headers/processa_prompt.h"

#define QTD_MAX_COMANDOS 5

// Remove espaços em branco no comeco da string e espacoes em branco ou quebra de linha do final
// Aloca uma string nova na heap e a retorna
// Não altera a string original
static void trim(char* origem, char* destino) {
    if(!origem || strlen(origem) == 0) {
        perror("String nula ou vazia recebida - trim().\n");
        exit(1);
    }

    unsigned i = 0;
    while(origem[i] == ' ' || origem[i] == '\n')
        i++;

    unsigned j = strlen(origem) - 1;
    while(origem[j] == ' ' || origem[j] == '\n')
        j--;
    
    int k = 0;
    for(int l = i; l <= j; l++)
        destino[k++] = origem[l];
    destino[k] = '\0';
}

int processa_prompt(char* prompt, char vetor_comandos[][TAMANHO_MAXIMO_COMANDO]) {
    // Separa os comandos individuais em tokens e os coloca do vetor de comandos
    // O vetor de comandos eh terminado por NULL
    char* token = strtok(prompt, "<3");
    int i = 0;
    while(token) {
        trim(token, vetor_comandos[i]);
        i++;
        
        // Verifica se mais de 5 comandos foram passados
        if(i > 5) {
            printf("Por favor, digite no maximo 5 comandos por vez.\n");
            return -1;
        }

        token = strtok(NULL, "<3");
    }
    
    strcpy(vetor_comandos[i], "NULL");

    return 0;
}
