#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "editor.h"


#define MAX_COMANDO 256

int main(void) {
    Editor editor;
    char comando[MAX_COMANDO];

    inicializarEditor(&editor);


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
                Antonio
            */
           char *texto = comando + 10;
           inserirNoFim(&editor, texto);
        }

        else if (strncmp(comando, "InsertInCursor ", 15) == 0) {
            /*
                Guardar estado.
                Inserir texto na posição do cursor.
                Afonso
            */
            char *texto = comando + 15;
            inserirNoCursor(&editor, texto);
        }

       else if (strncmp(comando, "InsertInLine ", 13) == 0)
{
    /*
        Extrair o número da linha.
        Extrair o texto.
        Guardar estado.
        Chamar inserirNaLinha().
        Rodrigo
    */
    int n;
    char texto[MAX_LINHA + 1];

    if (sscanf(comando + 13, "%d %[^\n]", &n, texto) == 2)
    {

        inserirNaLinha(&editor, n, texto);
    }
    else
    {
        printf("Comando inválido. Uso: InsertInLine <numero> <texto>\n");
    }
}

        else if (strcmp(comando, "DeleteLine") == 0) {
            /*
                Guardar estado.
                Remover linha do cursor.
                Antonio
            */
            removerLinhaCursor(&editor);
        }

        else if (strncmp(comando, "DeleteCursor ", 13) == 0) {
            /*
                Extrair número da linha.
                Guardar estado.
                Remover linha n.
                Afonso
            */
            int n = atoi(comando + 13);
            removerLinhaN(&editor, n);
        }

        else if (strncmp(comando, "EditCursor ", 11) == 0)
{
    /*
        Guardar estado.
        Editar linha do cursor.
        Rodrigo
    */
    char *texto = comando + 11;

    editarCursor(&editor, texto);
}

        else if (strncmp(comando, "EditLine ", 9) == 0) {
            /*
                Extrair número da linha.
                Extrair texto.
                Guardar estado.
                Editar linha n.
                Antonio
            */
            int n;
            char texto[MAX_LINHA + 1];
            if (sscanf(comando + 9, "%d %[^\n]", &n, texto) == 2) {
                editarLinhaN(&editor, n, texto);
            } else {
                printf("Comando inválido. Uso: EditLine <numero> <texto>\n");
            }
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
                Afonso
            */
            char *padrao = comando + 7;
            pesquisarTexto(&editor, padrao);
        }

        else {
            printf("Comando desconhecido.\n");
        }
    }

    libertarEditor(&editor);
    

    return 0;
}