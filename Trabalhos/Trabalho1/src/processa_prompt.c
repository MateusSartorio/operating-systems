#include "../headers/processa_prompt.h"
#include <string.h>

// Remove espaços em branco no comeco da string e espacoes em branco ou quebra de linha do final
// Aloca uma string nova na heap e a retorna
// Não altera a string original
char* trim(const char* str) {
    if(!str || strlen(str) == 0) {
        perror("string nula ou vazia recebida - trim()");
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

void processa_prompt(char* prompt) {
    char* token = strtok(prompt, "<3");
    char* trimmed_token = NULL;

    while(token) {
        trimmed_token = trim(token);
        
        printf("token: -%s-\n", token);
        printf("trimmed_token: -%s-\n", trimmed_token);

        int cmp = strcmp(trimmed_token, "exit");

        if(cmp == 0)
            fecha_tudo_e_sai();

        token = strtok(NULL, "<3");
        free(trimmed_token);
    }
}
