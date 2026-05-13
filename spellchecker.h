#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H
#include "editor.h"

#define TAM_HASH 1009
#define MAX_PALAVRA 100

typedef struct Palavra {
    char palavra[MAX_PALAVRA];
    struct Palavra *seguinte;
} Palavra;

typedef struct {
    Palavra *tabela[TAM_HASH];
} Dicionario;

/* Inicialização */
void inicializarDicionario(Dicionario *dic);
void libertarDicionario(Dicionario *dic);

/* Hash */
unsigned int hashPalavra(const char *palavra);

/* Dicionário */
void carregarDicionario(Dicionario *dic, const char *nomeFicheiro);
void inserirPalavra(Dicionario *dic, const char *palavra);
int existePalavra(Dicionario *dic, const char *palavra);

/* Spellcheck */
void verificarOrtografia(Editor *ed, Dicionario *dic);
/* Auxiliares */
void limparPalavra(char *palavra);

#endif