#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "spellchecker.h"
#include "undo.h"
#include "editor.h"
#include "utils.h"

#define MAX_COMANDO 256

int main(void)
{
    Editor editor;
    Dicionario dicionario;
    PilhaUndo undo;
    char comando[MAX_COMANDO];

    inicializarEditor(&editor);
    inicializarDicionario(&dicionario);
    inicializarUndo(&undo);
    carregarDicionario(&dicionario, "portugues.txt");

    printf("ED-LIN iniciado.\n");

    while (1)
    {
        printf("> ");

        if (fgets(comando, MAX_COMANDO, stdin) == NULL)
        {
            break;
        }

        removerQuebraLinha(comando);

        char *entrada = comando;
        while (*entrada != '\0' && isspace((unsigned char)*entrada))
        {
            entrada++;
        }

        char *fim = entrada + strlen(entrada);
        while (fim > entrada && isspace((unsigned char)fim[-1]))
        {
            fim--;
        }
        *fim = '\0';

        if (*entrada == '\0')
        {
            continue;
        }

        char *args = strchr(entrada, ' ');
        if (args != NULL)
        {
            *args = '\0';
            args++;
            while (*args != '\0' && isspace((unsigned char)*args))
            {
                args++;
            }
        }

        if (strcmp(entrada, "exit") == 0)
        {
            break;
        }

        else if (strcmp(entrada, "InsertEnd") == 0)
        {
            /*
                Antes de alterar, guardar estado para undo.
                Depois chamar inserirNoFim().
                Antonio
            */
            if (args != NULL && *args != '\0')
            {
                guardarEstado(&undo, &editor);
                inserirNoFim(&editor, args);
            }
            else
            {
                printf("Comando inválido. Uso: InsertEnd <texto>\n");
            }
        }

        else if (strcmp(entrada, "InsertInCursor") == 0)
        {
            /*
                Guardar estado.
                Inserir texto na posição do cursor.
                Afonso
            */
            if (args != NULL && *args != '\0')
            {
                guardarEstado(&undo, &editor);
                inserirNoCursor(&editor, args);
            }
            else
            {
                printf("Comando inválido. Uso: InsertInCursor <texto>\n");
            }
        }

        else if (strcmp(entrada, "InsertInLine") == 0)
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

            if (args != NULL && sscanf(args, "%d %[^\n]", &n, texto) == 2)
            {
                guardarEstado(&undo, &editor);
                inserirNaLinha(&editor, n, texto);
            }
            else
            {
                printf("Comando inválido. Uso: InsertInLine <numero> <texto>\n");
            }
        }

        else if (strcmp(entrada, "DeleteLine") == 0)
        {
            /*
                Guardar estado.
                Remover linha do cursor.
                Antonio
            */
            guardarEstado(&undo, &editor);
            removerLinhaCursor(&editor);
        }

        else if (strcmp(entrada, "DeleteCursor") == 0)
        {
            /*
                Extrair número da linha.
                Guardar estado.
                Remover linha n.
                Afonso
            */
            int n;
            if (args != NULL && sscanf(args, "%d", &n) == 1)
            {
                guardarEstado(&undo, &editor);
                removerLinhaN(&editor, n);
            }
            else
            {
                printf("Comando inválido. Uso: DeleteCursor <numero>\n");
            }
        }

        else if (strcmp(entrada, "EditCursor") == 0)
        {
            /*
                Guardar estado.
                Editar linha do cursor.
                Rodrigo
            */
            if (args != NULL && *args != '\0')
            {
                guardarEstado(&undo, &editor);
                editarCursor(&editor, args);
            }
            else
            {
                printf("Comando inválido. Uso: EditCursor <texto>\n");
            }
        }

        else if (strcmp(entrada, "EditLine") == 0)
        {
            /*
                Extrair número da linha.
                Extrair texto.
                Guardar estado.
                Editar linha n.
                Antonio
            */
            int n;
            char texto[MAX_LINHA + 1];
            if (args != NULL && sscanf(args, "%d %[^\n]", &n, texto) == 2)
            {
                guardarEstado(&undo, &editor);
                editarLinhaN(&editor, n, texto);
            }
            else
            {
                printf("Comando inválido. Uso: EditLine <numero> <texto>\n");
            }

        }
        else if (strcmp(entrada, "GoUp") == 0)
        {
            subirCursor(&editor);
        }

        else if (strcmp(entrada, "GoDown") == 0)
        {
            descerCursor(&editor);
        }

        else if (strcmp(entrada, "Print") == 0)
        {
            imprimirDocumento(&editor);
        }

        else if (strcmp(entrada, "PrintCursor") == 0)
        {
            imprimirCursor(&editor);
        }

        else if (strcmp(entrada, "Search") == 0)
        {
            /*
                Extrair texto a pesquisar.
                Chamar pesquisarTexto().
                Afonso
            */
            if (args != NULL && *args != '\0')
            {
                pesquisarTexto(&editor, args);
            }
            else
            {
                printf("Comando inválido. Uso: Search <texto>\n");
            }
        }
        else if (strcmp(entrada, "spell") == 0)
        {
            /*
                Chamar verificarOrtografia().
            */
            verificarOrtografia(&editor, &dicionario);
        }
        else if (strcmp(entrada, "undo") == 0)
        {
            /*
                Chamar fazerUndo().
            */
            fazerUndo(&undo, &editor);
        }
        else
        {
            printf("Comando desconhecido.\n");
        }
    }

    libertarEditor(&editor);
    libertarDicionario(&dicionario);
    libertarUndo(&undo);
    return 0;
}
