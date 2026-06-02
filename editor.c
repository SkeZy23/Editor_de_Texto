#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

void inicializarEditor(Editor *ed) {
    ed->inicio = NULL;
    ed->fim = NULL;
    ed->cursor = NULL;
    ed->totalLinhas = 0;
}

void libertarEditor(Editor *ed) {
    /*
        Percorrer a lista toda
        Libertar cada nó
        Colocar inicio, fim e cursor a NULL
        Antonio
    */
   Linha *atual = ed->inicio;
   while (atual != NULL) {
        Linha *proxima = atual->seguinte;
        free(atual);
        atual = proxima;
   }
    ed -> inicio = NULL;
    ed -> fim = NULL;
    ed -> cursor = NULL;
    ed -> totalLinhas = 0;
}

Linha *criarLinha(const char *texto) {
    /*
        Alocar memória para uma nova linha
        Copiar no máximo MAX_LINHA caracteres
        Inicializar anterior e seguinte como NULL
        Devolver ponteiro para a nova linha
        Afonso
    */

    return NULL;
}

void inserirNoCursor(Editor *ed, const char *texto) {
    /*
        Inserir uma nova linha na posição atual do cursor.
        
        Casos a tratar:
        - Documento vazio
        - Cursor no início
        - Cursor no meio
        - Cursor no fim
        Rodrigo
    */
}

void inserirNaLinha(Editor *ed, int n, const char *texto) {
    /*
        Inserir texto antes da linha número n.
        Primeiro encontrar a linha n.
        Depois inserir antes dela.
        Antonio
    */
   if(n < 1 || n > ed->totalLinhas + 1) {
        printf("Número de linha inválido.\n");
        return;
   }
   if (n == ed->totalLinhas + 1){
        inserirNoFim(ed, texto);
        return;
   }
    Linha *linhaAtual = obterLinha(ed, n);
    if (linhaAtual == NULL){
        printf("Linha não encontrada.\n");
        return;
    }
    Linha *novaLinha = criarLinha(texto);

    if (novaLinha == NULL){
        printf("Erro ao criar linha.\n");
        return;
    }
    novaLinha->seguinte = linhaAtual;
    novaLinha->anterior = linhaAtual->anterior;

    if(linhaAtual->anterior != NULL){
        linhaAtual->anterior->seguinte = novaLinha;
    } else {
        ed->inicio = novaLinha;
    }
    linhaAtual->anterior = novaLinha;

    ed->cursor = novaLinha;
    ed->totalLinhas++;
}

void inserirNoFim(Editor *ed, const char *texto) {
    /*
        Criar uma nova linha.
        Se o documento estiver vazio, ela é inicio, fim e cursor.
        Caso contrário, ligar depois do fim atual.
        Afonso
    */
}

void removerLinhaCursor(Editor *ed) {
    /*
        Remover a linha onde está o cursor.
        
        Depois de remover:
        - Se existir linha seguinte, cursor passa para ela.
        - Caso contrário, se existir anterior, cursor passa para ela.
        - Se não existir nenhuma, cursor fica NULL.
        Rodrigo
    */
}

void removerLinhaN(Editor *ed, int n) {
    /*
        Obter a linha n.
        Atualizar o cursor para essa linha.
        Reutilizar removerLinhaCursor().
        Antonio
    */
   Linha *linhaN = obterLinha(ed, n);

   if(linhaN == NULL){
        printf("Linha não encontrada.\n");
        return;
    }
    ed->cursor = linhaN;
    removerLinhaCursor(ed);
}

void editarCursor(Editor *ed, const char *texto) {
    /*
        Substituir o texto da linha do cursor.
        Atenção ao limite de 40 caracteres.
        Afonso
    */
}

void editarLinhaN(Editor *ed, int n, const char *texto) {
    /*
        Encontrar a linha n.
        Substituir o conteúdo dessa linha pelo texto recebido.
        Rodrigo
    */
}

void subirCursor(Editor *ed) {
    /*
        Se o cursor não for NULL
        e se existir linha anterior,
        mover cursor para cursor->anterior.
        Antonio
    */
   if(ed->cursor != NULL && ed->cursor->anterior != NULL){
        ed->cursor = ed->cursor->anterior;
   }
}

void descerCursor(Editor *ed) {
    /*
        Se o cursor não for NULL
        e se existir linha seguinte,
        mover cursor para cursor->seguinte.
        Afonso
    */
}

void imprimirDocumento(Editor *ed) {
    /*
        Percorrer desde o início até ao fim.
        Imprimir número da linha e conteúdo.
        A linha do cursor deve estar assinalada.
        Rodrigo
    */
}

void imprimirCursor(Editor *ed) {
    /*
        Imprimir apenas a linha atual do cursor.
        Antonio
    */
   if(ed->cursor != NULL){
        printf("Cursor Vazio. \n");
        return;
   }
   Linha *linhaAtual = ed->cursor;
   int numeroLinha = 1;
   while(linhaAtual != NULL){
        linhaAtual = linhaAtual->seguinte;
        numeroLinha++;
   }
   printf("-> %d: %s\n", numeroLinha, ed->cursor->texto);
}

void pesquisarTexto(Editor *ed, const char *padrao) {
    /*
        Percorrer todas as linhas.
        Usar strstr() para verificar se o padrão existe.
        Se encontrar, imprimir número da linha e conteúdo.
        Se não encontrar nenhuma, imprimir "not found".
        Afonso
    */
}

Linha *obterLinha(Editor *ed, int n) {
    /*
        Validar se n está entre 1 e totalLinhas.
        Percorrer a lista até chegar à linha n.
        Devolver ponteiro para essa linha.
        Rodrigo
    */

    return NULL;
}

void inserirTextoComQuebra(Editor *ed, const char *texto) {
    /*
        Dividir o texto em blocos de MAX_LINHA caracteres.
        Inserir cada bloco como uma linha.
        Antonio
    */
   int tamanho = strlen(texto);
   int i = 0;
   while(i < tamanho){
    char bloco[MAX_LINHA + 1];

    strncpy(bloco, texto + i, MAX_LINHA);
    bloco[MAX_LINHA] = '\0';

    inserirNoFim(ed, bloco);

    i += MAX_LINHA;
   }
}