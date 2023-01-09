#ifndef PROCESSA_PROMPT
#define PROCESSA_PROMPT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "executa_prompt.h"

char** processa_prompt(char* prompt);
void libera_vetor_comandos(char** vetor_comandos);

#endif
