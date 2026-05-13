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
    */
}

Linha *criarLinha(const char *texto) {
    /*
        Alocar memória para uma nova linha
        Copiar no máximo MAX_LINHA caracteres
        Inicializar anterior e seguinte como NULL
        Devolver ponteiro para a nova linha
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
    */
}

void inserirNaLinha(Editor *ed, int n, const char *texto) {
    /*
        Inserir texto antes da linha número n.
        Primeiro encontrar a linha n.
        Depois inserir antes dela.
    */
}

void inserirNoFim(Editor *ed, const char *texto) {
    /*
        Criar uma nova linha.
        Se o documento estiver vazio, ela é inicio, fim e cursor.
        Caso contrário, ligar depois do fim atual.
    */
}

void removerLinhaCursor(Editor *ed) {
    /*
        Remover a linha onde está o cursor.
        
        Depois de remover:
        - Se existir linha seguinte, cursor passa para ela.
        - Caso contrário, se existir anterior, cursor passa para ela.
        - Se não existir nenhuma, cursor fica NULL.
    */
}

void removerLinhaN(Editor *ed, int n) {
    /*
        Obter a linha n.
        Atualizar o cursor para essa linha.
        Reutilizar removerLinhaCursor().
    */
}

void editarCursor(Editor *ed, const char *texto) {
    /*
        Substituir o texto da linha do cursor.
        Atenção ao limite de 40 caracteres.
    */
}

void editarLinhaN(Editor *ed, int n, const char *texto) {
    /*
        Encontrar a linha n.
        Substituir o conteúdo dessa linha pelo texto recebido.
    */
}

void subirCursor(Editor *ed) {
    /*
        Se o cursor não for NULL
        e se existir linha anterior,
        mover cursor para cursor->anterior.
    */
}

void descerCursor(Editor *ed) {
    /*
        Se o cursor não for NULL
        e se existir linha seguinte,
        mover cursor para cursor->seguinte.
    */
}

void imprimirDocumento(Editor *ed) {
    /*
        Percorrer desde o início até ao fim.
        Imprimir número da linha e conteúdo.
        A linha do cursor deve estar assinalada.
    */
}

void imprimirCursor(Editor *ed) {
    /*
        Imprimir apenas a linha atual do cursor.
    */
}

void pesquisarTexto(Editor *ed, const char *padrao) {
    /*
        Percorrer todas as linhas.
        Usar strstr() para verificar se o padrão existe.
        Se encontrar, imprimir número da linha e conteúdo.
        Se não encontrar nenhuma, imprimir "not found".
    */
}

Linha *obterLinha(Editor *ed, int n) {
    /*
        Validar se n está entre 1 e totalLinhas.
        Percorrer a lista até chegar à linha n.
        Devolver ponteiro para essa linha.
    */

    return NULL;
}

void inserirTextoComQuebra(Editor *ed, const char *texto) {
    /*
        Dividir o texto em blocos de MAX_LINHA caracteres.
        Inserir cada bloco como uma linha.
    */
}