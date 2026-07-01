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
        Percorre a pilha toda do inicio ao fim.
        Para cada estado liberta o editor guardado e depois liberta o proprio no.
        No fim a pilha fica vazia (topo a NULL).
        Rodrigo
    */
    Estado *atual = pilha->topo;
    while (atual != NULL) {
        Estado *seguinte = atual->seguinte;
        libertarEditor(&atual->documento);
        free(atual);
        atual = seguinte;
    }
    pilha->topo = NULL;
}

void guardarEstado(PilhaUndo *pilha, Editor *ed)
{
    /*
        Cria um Estado novo.
        Faz uma copia completa do editor atual (pra nao perder nada).
        Poe esse estado no topo da pilha.
        Afonso
    */
    Estado *novo = malloc(sizeof(Estado));
    if (novo == NULL)
    {
        return;
    }
    copiarEditor(&novo->documento, ed);
    novo->seguinte = pilha->topo;
    pilha->topo = novo;
}

int fazerUndo(PilhaUndo *pilha, Editor *ed) {
    /*
        Se a pilha tiver vazia nao ha undo possivel, sai logo.
        Se nao:
        - Liberta o editor atual.
        - Restaura o editor que estava guardado no topo.
        - Tira esse estado da pilha.
        Antonio
    */
    if (pilha == NULL || pilha->topo == NULL) {
        return 0;
    }else{
        Estado *estado = pilha->topo;
        pilha->topo = estado->seguinte;
        libertarEditor(ed);
        copiarEditor(ed, &estado->documento);
        libertarEditor(&estado->documento);
        free(estado);
        return 1;
    }
}

void copiarEditor(Editor *destino, Editor *origem) {
    /*
        Inicializa o destino primeiro.
        Percorre todas as linhas do editor de origem.
        Vai copiando cada linha pro destino.
        Garante que o cursor fica na mesma posiçao relativa la no fim.
        Antonio
    */
    inicializarEditor(destino);
    for (Linha *atual = origem->inicio; atual != NULL; atual = atual->seguinte) {
        inserirNoFim(destino, atual->texto);
        if (atual == origem->cursor) {
            destino->cursor = destino->fim;
        }
    }
}