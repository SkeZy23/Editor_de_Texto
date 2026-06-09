#include <stdio.h>
#include <string.h>
#include "utils.h"

void removerQuebraLinha(char *str) {
    /*
        Remover '\n' do final da string, se existir.
    */
    str [strcspn(str, "\n")] = '\0';
}

void limparBuffer(void) {
    /*
        Limpar caracteres restantes do stdin, se necessário.
    */
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int compararComando(const char *entrada, const char *comando) {
    /*
        Verificar se a entrada começa com determinado comando.
        Pode ser feito com strncmp().
    */
    return strncmp(entrada, comando, strlen(comando)) == 0;  
    return 0;
}