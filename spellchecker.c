#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "editor.h"
#include "spellchecker.h"

void inicializarDicionario(Dicionario *dic) {
    /*Rodrigo*/
    for (int i = 0; i < TAM_HASH; i++) {
        dic->tabela[i] = NULL;
    }
}

void libertarDicionario(Dicionario *dic)
{
    /*
        Percorrer cada posição da tabela.
        Libertar todas as listas ligadas.
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
        Criar uma função hash simples.
        Exemplo:
        hash = hash * 31 + caractere
        devolver hash % TAM_HASH
        Antonio
    */

    return 0;
}

void carregarDicionario(Dicionario *dic, const char *nomeFicheiro) {
    /*Rodrigo*/
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
        Calcular posição hash.
        Criar novo nó Palavra.
        Inserir no início da lista dessa posição.
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
        Calcular hash.
        Percorrer a lista dessa posição.
        Comparar com strcmp().
        Devolver 1 se existir, 0 se não existir.
        Antonio
    */

    return 0;
}

void verificarOrtografia(Editor *ed, Dicionario *dic) {
    /*Rodrigo*/
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
        Remover pontuação.
        Converter tudo para minúsculas.
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
