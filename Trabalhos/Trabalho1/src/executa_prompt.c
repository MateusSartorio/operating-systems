#include "../headers/executa_prompt.h"
#include <regex.h>

static void fecha_tudo_e_sai() {
    puts("fechando...");
    exit(0);
}

static void troca_diretorio(char* caminho) {
    chdir(caminho); 
}

static void processo_em_foreground(char* comando) {
    puts("processo em foreground");
}

static void cria_nova_secao(char** vetor_comandos) {
    int i = 0;
    char* comando = NULL;
}

static void libera_vetor_comandos(char** vetor_comandos) {
    for(int i = 0; vetor_comandos[i] != NULL; i++)
        free(vetor_comandos[i]);

    free(vetor_comandos);
}

void executa_prompt(char** vetor_comandos) {
    // Expressao regular responsavel por identificar se um processo deve ser executado em background
    regex_t foreground_regex;
    int foreground_regex_value = regcomp(&foreground_regex, ".\%$", 0);
    if(foreground_regex_value) {
        printf("Problema ao compilar foreground_regex.\n");
        exit(foreground_regex_value);
    }

    // Expressao regular responsavel por identificar se o comando de exit foi passado
    regex_t exit_regex;
    int exit_regex_value = regcomp(&exit_regex, "^exit[ ]*", 0);
    if(exit_regex_value) {
        printf("Problema ao compilar exit_regex.\n");
        exit(exit_regex_value);
    }

    bool tem_exit = false, tem_foreground = false;
    int i = 0;
    char* comando = NULL;
    while((comando = vetor_comandos[i])) {
        
        if(!regexec(&foreground_regex, vetor_comandos[i], 0, NULL, 0))
            tem_exit = true;
        else if(!regexec(&exit_regex, vetor_comandos[i], 0, NULL, 0))
            tem_foreground = true;

        i++;
    }

    if(i > 1 && (tem_exit || tem_foreground))
        printf("Por favor, a operacao de exit ou background (%%) devem ser comandos unicos.\n");
    else if(tem_exit)
        fecha_tudo_e_sai();
    else if(tem_foreground)
        processo_em_foreground(vetor_comandos[0]);
    else {
         cria_nova_secao(vetor_comandos);
    }
    
    libera_vetor_comandos(vetor_comandos);
    regfree(&foreground_regex);
    regfree(&exit_regex);
}
