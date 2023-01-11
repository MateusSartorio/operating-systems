#include "../headers/executa_prompt.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>

static void fecha_tudo_e_sai(pid_t* buffer_secoes, int* posicao_buffer_secoes) {
    for(int i = 0; i < *posicao_buffer_secoes; i++)
        killpg(buffer_secoes[i], SIGKILL);

    exit(0);
}

static void troca_diretorio(char* caminho) {
    char* token = strtok(caminho, " ");
    token = strtok(NULL, " ");
    
    if(strtok(NULL, "") != NULL)
        printf("Por favor passe apenas um argumento para cd.\n");
    else if(token == NULL)
        printf("Por favor passe pelo menos um argumento para cd.\n");
    else {    
        int chdir_return_value = chdir(token);

        if(chdir_return_value == -1)
            perror("Erro ao trocar de diretorio: ");
    }
}

static void processo_em_foreground(char* comando) {
    pid_t pid = fork();
    
    if(pid == 0) {
        struct sigaction sa;
        sa.sa_handler = SIG_DFL;
        sigfillset(&sa.sa_mask);
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
        sigaction(SIGTSTP, &sa, NULL);

        // Quantidade maxima de argumentos + o proprio nome do programa + NULL para sinalizar fim do vetor
        char* argv[QTD_MAXIMA_ARGUMENTOS + 2];
        
        int i = 0;
        char* token = strtok(comando, " ");
        while(token) {
            if(strcmp(token, "%") == 0)
                break;

            argv[i] = token;
            i++;

            if(i > 4)
                exit(1);

            token = strtok(NULL, " ");
        }
        argv[i] = NULL;

        execvp(argv[0], argv);

        exit(2);
    }
    else {
        int status = 0;
        while(wait(&status) != -1) {
            if(WIFEXITED(status)) {
                if(WEXITSTATUS(status) == 1)
                    printf("Muitos argumentos passados para programa, o maximo eh 3.\n");
                else if(WEXITSTATUS(status) == 2)
                    printf("Falha ao executar o comando: <%s>.\n", comando);
            }
        }
    }
}

static void executa_comando(char* comando) {
    // Quantidade maxima de argumentos + o proprio nome do programa + NULL para sinalizar fim do vetor
    char* argv[QTD_MAXIMA_ARGUMENTOS + 2];
    
    int i = 0;
    char* token = strtok(comando, " ");
    while(token) {
        argv[i] = token;
        i++;

        if(i > 4)
            exit(1);

        token = strtok(NULL, " ");
    }
    argv[i] = NULL;
    
    int dev_null = open("/dev/null", O_CREAT | O_WRONLY);
    dup2(dev_null, STDOUT_FILENO);
    dup2(dev_null, STDERR_FILENO);
    execvp(argv[0], argv);
    
    exit(2);
}

static void cria_nova_secao(char vetor_comandos[][TAMANHO_MAXIMO_COMANDO], pid_t* buffer_secoes, int* posicao_buffer_secoes) {
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
        
        int qtd_processos = 0;
        while(strcmp(vetor_comandos[qtd_processos], "NULL") != 0)
            qtd_processos++;

        if(qtd_processos == 1) {
            struct sigaction sa;
            sa.sa_handler = SIG_DFL;
            sigfillset(&sa.sa_mask);
            sigaction(SIGINT, &sa, NULL);
            sigaction(SIGQUIT, &sa, NULL);
            sigaction(SIGTSTP, &sa, NULL);
        }
        else {
            struct sigaction sa;
            sa.sa_handler = SIG_DFL;
            sigfillset(&sa.sa_mask);
            sigaction(SIGINT, &sa, NULL);
            sigaction(SIGQUIT, &sa, NULL);
            sigaction(SIGTSTP, &sa, NULL);
        }

        int i = 0;
        pid_t pid_comando_individual = 0;
        while(strcmp(vetor_comandos[i], "NULL") != 0) {
            pid_comando_individual = fork();
            
            if(pid_comando_individual == 0)
                executa_comando(vetor_comandos[i]);
            
            i++;
        }
        
        int status = 0;
        while(wait(&status) != -1) {
            killpg(0, SIGKILL);

            if(WIFEXITED(status))
                exit(WEXITSTATUS(status));
        }

        exit(0);
    }
    else {
        // Pai executa
        buffer_secoes[*posicao_buffer_secoes] = pid;
        *posicao_buffer_secoes += 1;
    }
}

void executa_prompt(char vetor_comandos[][TAMANHO_MAXIMO_COMANDO], pid_t* buffer_secoes, int* posicao_buffer_secoes) {
    // Expressao regular responsavel por identificar se um processo deve ser executado em background
    regex_t foreground_regex;
    int foreground_regex_value = regcomp(&foreground_regex, " \%$", 0);
    if(foreground_regex_value) {
        printf("Problema ao compilar foreground_regex.\n");
        exit(foreground_regex_value);
    }

    // Expressao regular responsavel por identificar se o comando de exit foi passado
    regex_t exit_regex;
    int exit_regex_value = regcomp(&exit_regex, "^exit$", 0);
    if(exit_regex_value) {
        printf("Problema ao compilar exit_regex.\n");
        exit(exit_regex_value);
    }

    regex_t cd_regex;
    int cd_regex_value = regcomp(&cd_regex, "^cd ", 0);
    if(cd_regex_value) {
        printf("Problema ao compilar cd_regex.\n");
        exit(cd_regex_value);
    }

    bool tem_exit = false, tem_foreground = false, tem_cd = false;
    int i = 0;
    while(strcmp(vetor_comandos[i], "NULL") != 0) {
        if(!regexec(&foreground_regex, vetor_comandos[i], 0, NULL, 0))
            tem_foreground = true;
        if(!regexec(&exit_regex, vetor_comandos[i], 0, NULL, 0))
            tem_exit = true;
        if(!regexec(&cd_regex, vetor_comandos[i], 0, NULL, 0))
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
        fecha_tudo_e_sai(buffer_secoes, posicao_buffer_secoes);
    else if(tem_foreground) {
        sigset_t new_set, old_set; 
        
        sigfillset(&new_set);
        sigprocmask(SIG_BLOCK, &new_set, &old_set);

        processo_em_foreground(vetor_comandos[0]);

        sigprocmask(SIG_SETMASK, &old_set, NULL);
    }
    else if(tem_cd)
        troca_diretorio(vetor_comandos[0]);
    else
        cria_nova_secao(vetor_comandos, buffer_secoes, posicao_buffer_secoes); 
    
    regfree(&foreground_regex);
    regfree(&exit_regex);
    regfree(&cd_regex);
}
