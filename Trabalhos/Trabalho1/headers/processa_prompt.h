#ifndef PROCESSA_PROMPT
#define PROCESSA_PROMPT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "constantes.h"

int processa_prompt(char* prompt, char vetor_comandos[][TAMANHO_MAXIMO_COMANDO]);

#endif
