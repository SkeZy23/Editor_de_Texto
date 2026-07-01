#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "editor.h"
#include "spellchecker.h"

void inicializarDicionario(Dicionario *dic) {
    /*
        Poe todas as posiçoes da tabela hash a NULL.
        É basicamente so inicializar o dicionario vazio.
        Rodrigo
    */
    for (int i = 0; i < TAM_HASH; i++) {
        dic->tabela[i] = NULL;
    }
}

void libertarDicionario(Dicionario *dic)
{
    /*
        Percorre cada posiçao da tabela.
        Vai libertando todas as listas ligadas uma a uma.
        Afonso
    */
    for (int i = 0; i < TAM_HASH; i++)
    {
        Palavra *atual = dic->tabela[i];
        while (atual != NULL)
        {
            Palavra *proxima = atual->seguinte;
            free(atual);
            atual = proxima;
        }
        dic->tabela[i] = NULL;
    }
}


unsigned int hashPalavra(const char *palavra) {
    /*
        Cria uma funçao hash simples.
        Ideia:
        hash = hash * 31 + caractere
        no fim devolve hash % TAM_HASH
        Antonio
    */

    unsigned int hash = 0;
    for (int i = 0; palavra[i] != '\0'; i++) {
        hash = hash * 31 + palavra[i];
    }
    return hash % TAM_HASH;
}

void carregarDicionario(Dicionario *dic, const char *nomeFicheiro) {
    /*
        Abre o ficheiro com as palavras todas.
        Le linha a linha, limpa cada palavra e insere no dicionario.
        Se o ficheiro nao abrir da erro e sai.
        Rodrigo
    */
    FILE *f = fopen(nomeFicheiro, "r");
    if (f == NULL) {
        printf("Erro: não foi possível abrir '%s'.\n", nomeFicheiro);
        return;
    }
    char linha[MAX_PALAVRA];
    while (fgets(linha, MAX_PALAVRA, f) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        limparPalavra(linha);
        if (strlen(linha) > 0)
            inserirPalavra(dic, linha);
    }
    fclose(f);
}

void inserirPalavra(Dicionario *dic, const char *palavra)
{
    /*
        Calcula a posiçao hash.
        Cria um no novo do tipo Palavra.
        Insere no inicio da lista dessa posiçao (mais facil e rapido).
        Afonso
    */
    unsigned int pos = hashPalavra(palavra);
    Palavra *nova = malloc(sizeof(Palavra));
    if (nova == NULL)
    {
        return;
    }
    strncpy(nova->palavra, palavra, MAX_PALAVRA - 1);
    nova->palavra[MAX_PALAVRA - 1] = '\0';
    nova->seguinte = dic->tabela[pos];
    dic->tabela[pos] = nova;
}


int existePalavra(Dicionario *dic, const char *palavra) {
    /*
        Calcula o hash da palavra.
        Percorre a lista dessa posiçao a ver se encontra.
        Compara com strcmp().
        Devolve 1 se existir, 0 se nao existir.
        Antonio
    */
    unsigned int pos = hashPalavra(palavra);
    Palavra *atual = dic->tabela[pos];
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return 1;
        }
        atual = atual->seguinte;
    }
    return 0;
}

void verificarOrtografia(Editor *ed, Dicionario *dic) {
    /*
        Percorre todas as linhas do documento uma a uma.
        Separa cada linha em palavras (tokens).
        Limpa cada palavra e vai ver se ela existe no dicionario.
        Se nao existir avisa o utilizador com o numero da linha.
        Rodrigo
    */
    Linha *atual = ed->inicio;
    int numeroLinha = 1;
    while (atual != NULL) {
        char copia[MAX_LINHA + 1];
        strncpy(copia, atual->texto, MAX_LINHA);
        copia[MAX_LINHA] = '\0';

        char *token = strtok(copia, " \t");
        while (token != NULL) {
            char palavra[MAX_PALAVRA];
            strncpy(palavra, token, MAX_PALAVRA - 1);
            palavra[MAX_PALAVRA - 1] = '\0';
            limparPalavra(palavra);

            if (strlen(palavra) > 0 && !existePalavra(dic, palavra)) {
                printf("Linha %d: '%s' não encontrada no dicionário.\n", numeroLinha, token);
            }
            token = strtok(NULL, " \t");
        }
        atual = atual->seguinte;
        numeroLinha++;
    }
}

void limparPalavra(char *palavra)
{
    /*
        Remove a pontuaçao toda.
        Converte pra minusculas.
        Afonso
    */
    int i = 0, j = 0;
    while (palavra[i] != '\0')
    {
        if (isalpha((unsigned char)palavra[i]))
        {
            palavra[j++] = tolower((unsigned char)palavra[i]);
        }
        i++;
    }
    palavra[j] = '\0';
}