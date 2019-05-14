#ifndef HASH
#define HASH
#define MAX 13

typedef struct livro {
    int isbn;
    char *titulo;
    char *autor;
    char *editora;
}Livro;

typedef struct no_encad{
  int chave;
  int ref;
  struct no_encad *prox;
}No;

typedef struct lista_encad{
  No *primeiro;
}Lista;

typedef struct tabela_hash{
  char* arquivo_dados;
  char*arquivo_indices;
  FILE *dados;
  FILE *indices;
  Lista* lista_indices[MAX];
}Tabela;

int hash(int chave);
Tabela* startTabela(char *dados,char *indices);
void salvar_indices(Tabela *tab);
void finalizar(Tabela *tab);
int buscar_indice(Tabela *tab, int chave);

char* tirar_enter(char *string);
Livro* ler_livro();
void imprimir_livro(Livro *l);
int salvar_livro(Tabela *tab, Livro * livro);

No* buscar_na_lista(Lista *lista, int chave);
No* startNo(int chave, int refer, No* proximo);
Lista* startLista();
void adic_no_inicio(Lista *lista, int chave, int refer);
void remover(Lista *lista, int valor);

#endif
