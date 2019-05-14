#ifndef LIVRO_H
#define LIVRO_H

typedef struct livro {
    int isbn;
    char *titulo;
    char *autor;
    char *editora;
} Livro;

typedef  struct no_indice {
  int isbn;
  int referencia;
  no_indice *esq, *dir;
}no_indice;


typedef struct tabela_livro {
    FILE * dados;
    FILE * indice;
    no_indice *raiz;
    char * nome_arq;
} tabela_livros;

livro * ler_livro();
void imprimir_livro(livro *l);
char * tirar_enter(char *string);
void inicializar_tabela(tabela_livros *tabela, char *nome);

#endif
