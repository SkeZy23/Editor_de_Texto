#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

void inicializarEditor(Editor *ed)
{
    ed->inicio = NULL;
    ed->fim = NULL;
    ed->cursor = NULL;
    ed->totalLinhas = 0;
}

void libertarEditor(Editor *ed)
{
    /*
        Percorrer a lista toda
        Libertar cada nó
        Colocar inicio, fim e cursor a NULL
        Antonio
    */
    Linha *atual = ed->inicio;
    while (atual != NULL)
    {
        Linha *proxima = atual->seguinte;
        free(atual);
        atual = proxima;
    }
    ed->inicio = NULL;
    ed->fim = NULL;
    ed->cursor = NULL;
    ed->totalLinhas = 0;
}

Linha *criarLinha(const char *texto)
{
    /*
        Alocar memória para uma nova linha
        Copiar no máximo MAX_LINHA caracteres
        Inicializar anterior e seguinte como NULL
        Devolver ponteiro para a nova linha
        Afonso
    */
    Linha *nova = malloc(sizeof(Linha));
    if (nova == NULL)
        return NULL;
    strncpy(nova->texto, texto, MAX_LINHA);
    nova->texto[MAX_LINHA] = '\0';
    nova->anterior = NULL;
    nova->seguinte = NULL;
    return nova;
}

void inserirNoCursor(Editor *ed, const char *texto)
{
    /*Rodrigo*/
    Linha *novaLinha = criarLinha(texto);
    if (novaLinha == NULL)
    {
        printf("Erro ao criar linha.\n");
        return;
    }

    if (ed->cursor == NULL)
    {
        ed->inicio = novaLinha;
        ed->fim = novaLinha;
        ed->cursor = novaLinha;
        ed->totalLinhas++;
        return;
    }

    novaLinha->seguinte = ed->cursor;
    novaLinha->anterior = ed->cursor->anterior;

    if (ed->cursor->anterior != NULL)
    {
        ed->cursor->anterior->seguinte = novaLinha;
    }
    else
    {
        ed->inicio = novaLinha;
    }

    ed->cursor->anterior = novaLinha;
    ed->cursor = novaLinha;
    ed->totalLinhas++;
}

void inserirNaLinha(Editor *ed, int n, const char *texto)
{
    /*
        Inserir texto antes da linha número n.
        Primeiro encontrar a linha n.
        Depois inserir antes dela.
        Antonio
    */
    if (n < 1 || n > ed->totalLinhas + 1)
    {
        printf("Número de linha inválido.\n");
        return;
    }
    if (n == ed->totalLinhas + 1)
    {
        inserirNoFim(ed, texto);
        return;
    }
    Linha *linhaAtual = obterLinha(ed, n);
    if (linhaAtual == NULL)
    {
        printf("Linha não encontrada.\n");
        return;
    }
    Linha *novaLinha = criarLinha(texto);

    if (novaLinha == NULL)
    {
        printf("Erro ao criar linha.\n");
        return;
    }
    novaLinha->seguinte = linhaAtual;
    novaLinha->anterior = linhaAtual->anterior;

    if (linhaAtual->anterior != NULL)
    {
        linhaAtual->anterior->seguinte = novaLinha;
    }
    else
    {
        ed->inicio = novaLinha;
    }
    linhaAtual->anterior = novaLinha;

    ed->cursor = novaLinha;
    ed->totalLinhas++;
}

void inserirNoFim(Editor *ed, const char *texto)
{
    /*
        Criar uma nova linha.
        Se o documento estiver vazio, ela é inicio, fim e cursor.
        Caso contrário, ligar depois do fim atual.
        Afonso
    */

    Linha *novaLinha = criarLinha(texto);
    if (ed->fim == NULL)
    {
        ed->inicio = novaLinha;
        ed->fim = novaLinha;
        ed->cursor = novaLinha;
    }
    else
    {
        novaLinha->anterior = ed->fim;
        ed->fim->seguinte = novaLinha;
        ed->fim = novaLinha;
    }
    ed->totalLinhas++;
}

void removerLinhaCursor(Editor *ed)
{
    /*Rodrigo*/
    if (ed->cursor == NULL)
        return;
    Linha *aRemover = ed->cursor;
    if (aRemover->seguinte != NULL)
    {
        ed->cursor = aRemover->seguinte;
    }
    else if (aRemover->anterior != NULL)
    {
        ed->cursor = aRemover->anterior;
    }
    else
    {
        ed->cursor = NULL;
    }
    if (aRemover->anterior != NULL)
    {
        aRemover->anterior->seguinte = aRemover->seguinte;
    }
    else
    {
        ed->inicio = aRemover->seguinte;
    }
    if (aRemover->seguinte != NULL)
    {
        aRemover->seguinte->anterior = aRemover->anterior;
    }
    else
    {
        ed->fim = aRemover->anterior;
    }
    free(aRemover);
    ed->totalLinhas--;
}

void removerLinhaN(Editor *ed, int n)
{
    /*
        Obter a linha n.
        Atualizar o cursor para essa linha.
        Reutilizar removerLinhaCursor().
        Antonio
    */
    Linha *linhaN = obterLinha(ed, n);

    if (linhaN == NULL)
    {
        printf("Linha não encontrada.\n");
        return;
    }
    ed->cursor = linhaN;
    removerLinhaCursor(ed);
}

void editarCursor(Editor *ed, const char *texto)
{
    /*
        Substituir o texto da linha do cursor.
        Atenção ao limite de 40 caracteres.
        Afonso
    */

    if (ed->cursor == NULL)
        return;
    strncpy(ed->cursor->texto, texto, MAX_LINHA);
    ed->cursor->texto[MAX_LINHA] = '\0';
}

void editarLinhaN(Editor *ed, int n, const char *texto)
{
    /*rodrigo*/
    Linha *linha = obterLinha(ed, n);
    if (linha == NULL)
    {
        printf("Linha não encontrada.\n");
        return;
    }
    strncpy(linha->texto, texto, MAX_LINHA);
    linha->texto[MAX_LINHA] = '\0';
}

void subirCursor(Editor *ed)
{
    /*
        Se o cursor não for NULL
        e se existir linha anterior,
        mover cursor para cursor->anterior.
        Antonio
    */
    if (ed->cursor != NULL && ed->cursor->anterior != NULL)
    {
        ed->cursor = ed->cursor->anterior;
    }
}

void descerCursor(Editor *ed)
{
    /*
        Se o cursor não for NULL
        e se existir linha seguinte,
        mover cursor para cursor->seguinte.
        Afonso
    */

    if (ed->cursor != NULL && ed->cursor->seguinte != NULL)
        ed->cursor = ed->cursor->seguinte;
}

void imprimirDocumento(Editor *ed)
{
    /*Rodrigo*/
    const Linha *atual = ed->inicio;
    int numeroLinha = 1;
    while (atual != NULL)
    {
        if (atual == ed->cursor)
        {
            printf("-> %d: %s\n", numeroLinha, atual->texto);
        }
        else
        {
            printf("   %d: %s\n", numeroLinha, atual->texto);
        }
        atual = atual->seguinte;
        numeroLinha++;
    }
}

void imprimirCursor(Editor *ed)
{
    /*
        Imprimir apenas a linha atual do cursor.
        Antonio
    */
    if (ed->cursor == NULL)
    {
        printf("Cursor vazio.\n");
        return;
    }

    int numeroLinha = 1;
    const Linha *atual = ed->inicio;
    while (atual != NULL && atual != ed->cursor)
    {
        atual = atual->seguinte;
        numeroLinha++;
    }
    if (atual == NULL) {
    printf("Cursor fora da lista.\n");
    return;
    }
    printf("-> %d: %s\n", numeroLinha, ed->cursor->texto);
}

void pesquisarTexto(Editor *ed, const char *padrao)
{
    /*
        Percorrer todas as linhas.
        Usar strstr() para verificar se o padrão existe.
        Se encontrar, imprimir número da linha e conteúdo.
        Se não encontrar nenhuma, imprimir "not found".
        Afonso
    */

    Linha *atual = ed->inicio;
    int numeroLinha = 1;
    int encontrou = 0;
    while (atual != NULL)
    {
        if (strstr(atual->texto, padrao) != NULL)
        {
            printf("%d: %s\n", numeroLinha, atual->texto);
            encontrou = 1;
        }
        atual = atual->seguinte;
        numeroLinha++;
    }
    if (!encontrou)
        printf("not found\n");
}

Linha *obterLinha(Editor *ed, int n)
{
    /*rodrigo*/
    if (n < 1 || n > ed->totalLinhas)
        return NULL;
    Linha *atual = ed->inicio;
    int i = 1;
    while (atual != NULL)
    {
        if (i == n)
            return atual;
        atual = atual->seguinte;
        i++;
    }
    return NULL;
}

void inserirTextoComQuebra(Editor *ed, const char *texto)
{
    /*
        Dividir o texto em blocos de MAX_LINHA caracteres.
        Inserir cada bloco como uma linha.
        Antonio
    */
    int tamanho = strlen(texto);
    int i = 0;
    while (i < tamanho)
    {
        char bloco[MAX_LINHA + 1];

        strncpy(bloco, texto + i, MAX_LINHA);
        bloco[MAX_LINHA] = '\0';

        inserirNoFim(ed, bloco);

        i += MAX_LINHA;
    }
}