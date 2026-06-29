#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "editor.h"
#include "spellchecker.h"

void inicializarDicionario(Dicionario *dic) {
    /*
        Colocar todas as posições da tabela a NULL.
        Rodrigo 
    */
}

void libertarDicionario(Dicionario *dic)
{
    /*
        Percorrre cada posição da tabela.
        Libertar todas as listas ligadas.
        Afonso
    */
    for (int i = 0;i < TAM_HASH; i++)
    {
        Palavra *atual = dic->tabela[i];
        while (atual != NULL){
            Palavra *proxima = atual->seguinte;
            free(atual);
            atual = proxima;
        }
        dic->tabela[i] = NULL;
    }
}

unsigned int hashPalavra(const char *palavra) {
    /*
        Criar uma função hash simples.
        Exemplo:
        hash = hash * 31 + caractere
        devolver hash % TAM_HASH
        Antonio
    */

    return 0;
}

void carregarDicionario(Dicionario *dic, const char *nomeFicheiro) {
    /*
        Abrir ficheiro do dicionário.
        Ler palavra a palavra.
        Limpar cada palavra.
        Inserir na tabela de hash.
       Rodrigo
    */
}

void inserirPalavra(Dicionario *dic, const char *palavra)
{
    /*
        Calcular posição hash.
        Criar novo nó Palavra.
        Inserir no início da lista dessa posição.
        Afonso
    */
    unsigned int pos = hashPalavra(palavra);
    Palavra *nova = malloc(sizeof(Palavra));
    if (nova == NULL)
        return;
    strncpy(nova->palavra, palavra, MAX_PALAVRA - 1);
    nova->palavra[MAX_PALAVRA - 1] = '\0';
    nova->seguinte = dic->tabela[pos];
    dic->tabela[pos] = nova;
}

int existePalavra(Dicionario *dic, const char *palavra) {
    /*
        Calcular hash.
        Percorrer a lista dessa posição.
        Comparar com strcmp().
        Devolver 1 se existir, 0 se não existir.
        Antonio
    */

    return 0;
}

void verificarOrtografia(Editor *ed, Dicionario *dic) {
    /*
        Percorrer todas as linhas do editor.
        Separar cada linha em palavras.
        Limpar pontuação.
        Converter para minúsculas.
        Verificar se a palavra existe no dicionário.
        Se não existir, imprimir a palavra.
        Rodrigo
    */
}

void limparPalavra(char *palavra)
{
    /*
        Remover pontuação.
        Converter tudo para minúsculas.
        Afonso
    */
    int i = 0, j = 0;
    while (palavra[i] != '\0')
    {
        if (isalpha((unsigned char)palavra[i]))
            palavra[j++] = tolower((unsigned char)palavra[i]);
        i++;
    }
    palavra[j] = '\0';
}