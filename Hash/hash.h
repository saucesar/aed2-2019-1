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

typedef struct tabela_hash{
  char* arquivo_dados;
  char* arquivo_indices;
  FILE *dados;
  FILE *indices;
  No* lista_indices[MAX];
}Tabela;

void menu();

int hash(int chave);
int buscar_refer(Tabela *tab, int chave);
Tabela* startTabela(char *dados,char *indices);
void salvar_indices(Tabela *tab);
void finalizar(Tabela *tab);

char* tirar_enter(char *string);
char* ler_campo(FILE *dados);
Livro* ler_livro_arquivo(Tabela *tab, int posicao);
Livro* ler_livro();
void adicionar_livro(Tabela *tab, Livro *livro);
void remover_da_tabela(Tabela *tab, int chave);
void editar(Tabela *tab,int chave);
void adicionar_indice(Tabela *tab, int chave, int ref);
void buscar_na_tabela(Tabela *tab,int chave);
void exibir_livro(Livro *l);
void exibir_tabela(Tabela *tab);
int salvar_livro(Tabela *tab, Livro * livro);

No* buscar_na_lista(No *no, int chave);
No* startNo(int chave, int refer, No *proximo);
No* adic_no_inicio(No *proximo, int chave, int refer);
No* remover_da_lista(No *inicial, int chave);

#endif
