#include "./headers/recebe_prompt.h"
#include "headers/executa_prompt.h"
#include "headers/processa_prompt.h"

int main(int argc, char** argv, char** envp) { 
    while(1) {
        char* prompt = recebe_prompt();
        
        if(prompt) {
            char** vetor_comandos = processa_prompt(prompt);
            
            if(vetor_comandos) {
                executa_prompt(vetor_comandos);

                libera_vetor_comandos(vetor_comandos);
            }

            free(prompt);
        }
    }
    
    return 0;
}
