#include "../headers/executa.h"

void fecha_tudo_e_sai() {
    puts("fechando...");
    exit(0);
}

void troca_diretorio(char* caminho) {
    chdir(caminho); 
}
