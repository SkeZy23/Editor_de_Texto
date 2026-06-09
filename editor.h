#ifndef EDITOR_H
#define EDITOR_H

#define MAX_LINHA 40
typedef struct Linha{
    char texto[MAX_LINHA +1];
    struct Linha *anterior;
    struct Linha *seguinte;
}Linha;

typedef struct{
    Linha *inicio;
    Linha *fim;
    Linha *cursor;
    int totalLinhas;
}Editor;

//Inicialização
void inicializarEditor(Editor *ed);
void libertarEditor(Editor *ed);

/*Criação de Linhas*/
Linha *criarLinha(const char *texto);

/*Inserção*/
void inserirNoCursor(Editor *ed, const char *texto);
void inserirNaLinha(Editor *ed, int n, const char *texto);
void inserirNoFim(Editor *ed, const char *texto);

/*Remoção*/
void removerLinhaCursor(Editor *ed);
void removerLinhaN(Editor *ed, int n);

/*Edição*/
void editarCursor(Editor *ed, const char *texto);
void editarLinhaN(Editor *ed, int n, const char *texto);

/*Navegação*/
void subirCursor(Editor *ed);
void descerCursor(Editor *ed);

/*Visualização*/
void imprimirDocumento(Editor *ed);
void imprimirCursor(Editor *ed);

/*Pesquisa*/
void pesquisarTexto(Editor *ed, const char *padrao);

/*Funções Auxiliares*/
Linha* obterLinha(Editor *ed, int n);
void inserirTextoComQuebra(Editor *ed, const char *texto);

#endif