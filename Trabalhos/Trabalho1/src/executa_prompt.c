#include "../headers/executa_prompt.h"
#include <fcntl.h>
#include <regex.h>
#include <stdio.h>
#include <unistd.h>

#define QTD_MAX_ARGUMENTOS 5

static void fecha_tudo_e_sai() {


    exit(0);
}

static void troca_diretorio(char* caminho) {
    char* token = strtok(caminho, " ");
    token = strtok(NULL, " ");
    chdir(token); 
}

static void processo_em_foreground(char* comando) {
    pid_t pid = fork();
    
    if(pid == 0) {
        // Quantidade maxima de argumentos + o proprio nome do programa + NULL para sinalizar fim do vetor
        char* argv[QTD_MAX_ARGUMENTOS + 2];
        
        int i = 0;
        char* token = strtok(comando, " ");
        while(token) {
        //    printf("%s, ", token);
            if(strcmp(token, "%") == 0)
                break;

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
    else {
        waitpid(pid, NULL, 0);
    }
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
    
    int dev_null = open("/dev/null", O_CREAT | O_WRONLY);
    dup2(dev_null, STDOUT_FILENO);
    dup2(dev_null, STDERR_FILENO);
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

        //printf("[FILHO LIDER DA SECAO] pid: %d, pgid: %d, sid: %d\n", getpid(), getpgrp(), getsid(getpid()));
        int i = 0;
        char* comando = NULL;
        pid_t pid_comando_individual = 0;
        while((comando = vetor_comandos[i])) {
            pid_comando_individual = fork();
            
            if(pid_comando_individual == 0) {
                executa_comando(comando);
                break;
            }
            
            i++;
        }
        exit(0);
    }
    else {
        // Pai executa
        //waitpid(pid, NULL, 0);
        //printf("[PROCESSO PRINCIPAL] pid: %d, pgid: %d, sid: %d\n", getpid(), getpgrp(), getsid(getpid()));
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

    regex_t cd_regex;
    int cd_regex_value = regcomp(&cd_regex, "^cd", 0);
    if(cd_regex_value) {
        printf("Problema ao compilar cd_regex.\n");
        exit(cd_regex_value);
    }

    bool tem_exit = false, tem_foreground = false, tem_cd = false;
    int i = 0;
    char* comando = NULL;
    while((comando = vetor_comandos[i])) {
        if(!regexec(&foreground_regex, comando, 0, NULL, 0))
            tem_foreground = true;
        if(!regexec(&exit_regex, comando, 0, NULL, 0))
            tem_exit = true;
        if(!regexec(&cd_regex, comando, 0, NULL, 0))
            tem_cd = true;

        i++;
    }

    if(i > 1 && (tem_exit || tem_foreground || tem_cd))
        printf("Por favor, a operacao de exit, cd ou comandos com o operador de foreground (%%) devem ser comandos unicos.\n");
    else if(tem_exit && tem_foreground)
        printf("A operacao de exit nao pode ser usada junto com o operador de foreground (%%).\n");
    else if(tem_cd && tem_foreground)
        printf("A operacao de cd nao pode ser usada junto com o operador de foreground (%%).\n");
    else if(tem_exit)
        fecha_tudo_e_sai();
    else if(tem_foreground)
        processo_em_foreground(vetor_comandos[0]);
    else if(tem_cd)
        troca_diretorio(vetor_comandos[0]);
    else
         cria_nova_secao(vetor_comandos);
    
    regfree(&foreground_regex);
    regfree(&exit_regex);
    regfree(&cd_regex);
}
