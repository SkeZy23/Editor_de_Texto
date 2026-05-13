#ifndef UNDO_H
#define UNDO_H

#include "editor.h"

typedef struct Estado {
    Editor documento;
    struct Estado *seguinte;
} Estado;

typedef struct {
    Estado *topo;
} PilhaUndo;

/* Inicialização */
void inicializarUndo(PilhaUndo *pilha);
void libertarUndo(PilhaUndo *pilha);

/* Operações */
void guardarEstado(PilhaUndo *pilha, Editor *ed);
int fazerUndo(PilhaUndo *pilha, Editor *ed);

/* Cópias */
void copiarEditor(Editor *destino, Editor *origem);

#endif