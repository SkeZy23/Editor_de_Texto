#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "editor.h"
#include "spellchecker.h"
#include "undo.h"
#include "utils.h"

#define MAX_COMANDO 256

int main(void) {
    Editor editor;
    Dicionario dicionario;
    PilhaUndo undo;
    char comando[MAX_COMANDO];

    inicializarEditor(&editor);
    inicializarDicionario(&dicionario);
    inicializarUndo(&undo);

    /*
        Opcional:
        carregarDicionario(&dicionario, "portuguese.txt");
    */

    printf("ED-LIN iniciado.\n");

    while (1) {
        printf("> ");

        if (fgets(comando, MAX_COMANDO, stdin) == NULL) {
            break;
        }

        removerQuebraLinha(comando);

        if (strcmp(comando, "exit") == 0) {
            break;
        }

        else if (strncmp(comando, "InsertEnd ", 10) == 0) {
            /*
                Antes de alterar, guardar estado para undo.
                Depois chamar inserirNoFim().
            */
        }

        else if (strncmp(comando, "InsertInCursor ", 15) == 0) {
            /*
                Guardar estado.
                Inserir texto na posição do cursor.
            */
        }

        else if (strncmp(comando, "InsertInLine ", 13) == 0) {
            /*
                Extrair o número da linha.
                Extrair o texto.
                Guardar estado.
                Chamar inserirNaLinha().
            */
           
        }

        else if (strcmp(comando, "DeleteLine") == 0) {
            /*
                Guardar estado.
                Remover linha do cursor.
            */
        }

        else if (strncmp(comando, "DeleteCursor ", 13) == 0) {
            /*
                Extrair número da linha.
                Guardar estado.
                Remover linha n.
            */
        }

        else if (strncmp(comando, "EditCursor ", 11) == 0) {
            /*
                Guardar estado.
                Editar linha do cursor.
            */
        }

        else if (strncmp(comando, "EditLine ", 9) == 0) {
            /*
                Extrair número da linha.
                Extrair texto.
                Guardar estado.
                Editar linha n.
            */
        }

        else if (strcmp(comando, "GoUp") == 0) {
            subirCursor(&editor);
        }

        else if (strcmp(comando, "GoDown") == 0) {
            descerCursor(&editor);
        }

        else if (strcmp(comando, "Print") == 0) {
            imprimirDocumento(&editor);
        }

        else if (strcmp(comando, "PrintCursor") == 0) {
            imprimirCursor(&editor);
        }

        else if (strncmp(comando, "Search ", 7) == 0) {
            /*
                Extrair texto a pesquisar.
                Chamar pesquisarTexto().
            */
        }

        else if (strcmp(comando, "spell") == 0) {
            /*
                Chamar verificarOrtografia().
            */
        }

        else if (strcmp(comando, "undo") == 0) {
            /*
                Chamar fazerUndo().
            */
        }

        else {
            printf("Comando desconhecido.\n");
        }
    }

    libertarEditor(&editor);
    libertarDicionario(&dicionario);
    libertarUndo(&undo);

    return 0;
}