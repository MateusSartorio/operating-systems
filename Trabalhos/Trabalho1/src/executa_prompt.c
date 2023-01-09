#include "../headers/executa_prompt.h"
#include <stdio.h>
#include <unistd.h>

#define QTD_MAX_ARGUMENTOS 5

static void fecha_tudo_e_sai() {
    exit(0);
}

static void troca_diretorio(char* caminho) {
    chdir(caminho); 
}

static void processo_em_foreground(char* comando) {
    puts("processo em foreground");
}

static void executa_comando(char* comando) {
    // Quantidade maxima de argumentos + o proprio nome do programa + NULL para sinalizar fim do vetor
    char* argv[QTD_MAX_ARGUMENTOS + 2];
    
    int i = 0;
    char* token = strtok(comando, " ");
    while(token) {
    //    printf("%s, ", token);
        argv[i] = token;
        i++;

        if(i > 4) {
            printf("Muitos argumentos passados para programa, maximo eh 3.\n");
            exit(1);
        }

        token = strtok(NULL, " ");
    }
    argv[i] = NULL;
        
    execvp(argv[0], argv);
}

static void cria_nova_secao(char** vetor_comandos) {
    pid_t pid = fork();
    
    if(pid == -1) {
        // Caso ocorra erro no fork
        printf("Erro ao realizar o fork - cria_nova_secao().\n");
        exit(1);
    }
    else if(pid == 0) {
        // Filho executa
        
        int setsid_return = setsid();
        if(setsid_return == -1) {
            printf("Erro ao criar nova secao - cria_nova_secao().\n");
            exit(1);
        }

        //fprintf(stdout, "[FILHO LIDER DA SECAO] pid: %d, pgid: %d, sid: %d\n", getpid(), getpgrp(), getsid(getpid()));
        int i = 0;
        char* comando = NULL;
        pid_t pid_comando_individual = 0;
        while((comando = vetor_comandos[i])) {
            pid_comando_individual = fork();
            
            if(pid_comando_individual == 0)
                executa_comando(comando);
            
            i++;
        }
    }
    else {
        // Pai executa
        //fprintf(stdout, "[PROCESSO PRINCIPAL] pid: %d, pgid: %d, sid: %d\n", getpid(), getpgrp(), getsid(getpid()));
        waitpid(pid, NULL, 0);
    }
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
        if(!regexec(&foreground_regex, comando, 0, NULL, 0))
            tem_foreground = true;
        if(!regexec(&exit_regex, comando, 0, NULL, 0))
            tem_exit = true;

        i++;
    }

    if(i > 1 && (tem_exit || tem_foreground))
        printf("Por favor, a operacao de exit ou comandos com o operador de foreground (%%) devem ser comandos unicos.\n");
    else if(tem_exit && tem_foreground)
        printf("A operacao de exit nao pode ser usada junto com o operador de foreground (%%).\n");
    else if(tem_exit)
        fecha_tudo_e_sai();
    else if(tem_foreground)
        processo_em_foreground(vetor_comandos[0]);
    else {
         cria_nova_secao(vetor_comandos);
    }
    
    regfree(&foreground_regex);
    regfree(&exit_regex);
}
