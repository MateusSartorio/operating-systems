#include "./headers/recebe_prompt.h"
#include "./headers/executa_prompt.h"
#include "./headers/processa_prompt.h"
#include <signal.h>
#include <stdio.h>

char prompt[TAMANHO_PROMPT];
char vetor_comandos[QTD_COMANDOS_MAXIMA+1][TAMANHO_MAXIMO_COMANDO];
pid_t buffer_secoes[TAMANHO_BUFFER_SECOES];
int posicao_buffer_secoes = 0;

void handler(int signo) {
    printf("\nNao adianta me enviar o sinal por Ctrl-... . Estou vacinado!!\n");
}

int main(int argc, char** argv, char** envp) { 
    struct sigaction sa;
    sa.sa_handler = handler;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    
    while(1) {
        int prompt_return_value = recebe_prompt(prompt);
        
        if(prompt_return_value == 0) {
            int processa_prompt_return_value = processa_prompt(prompt, vetor_comandos);
             
            if(processa_prompt_return_value == 0)
                executa_prompt(vetor_comandos, buffer_secoes, &posicao_buffer_secoes);
        }
         
        
    }
    
    return 0;
}
