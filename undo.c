#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"
#include "undo.h"

void inicializarUndo(PilhaUndo *pilha) {
    pilha->topo = NULL;
}

void libertarUndo(PilhaUndo *pilha) {
    /*
        Libertar todos os estados guardados.
        Cada estado contém uma cópia do editor.
    */
}

void guardarEstado(PilhaUndo *pilha, Editor *ed) {
    /*
        Criar novo Estado.
        Fazer uma cópia completa do editor atual.
        Colocar no topo da pilha.
    */
}

int fazerUndo(PilhaUndo *pilha, Editor *ed) {
    /*
        Se a pilha estiver vazia, não há undo possível.
        Caso contrário:
        - Libertar o editor atual.
        - Restaurar o editor guardado no topo.
        - Remover esse estado da pilha.
    */

    return 0;
}

void copiarEditor(Editor *destino, Editor *origem) {
    /*
        Inicializar destino.
        Percorrer todas as linhas de origem.
        Copiar cada linha para destino.
        Garantir que o cursor fica na mesma posição relativa.
    */
}