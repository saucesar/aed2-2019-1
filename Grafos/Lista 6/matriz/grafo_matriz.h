#ifndef GRAFO_MATRIZ
#define GRAFO_MATRIZ
#define INFINITO 99999999
typedef enum cor{BRANCO,CINZA,PRETO}Cor;

typedef struct grafo_matriz{
  int v,e;
  char *elementos;
  int **conexoes;
}Grafo;

typedef struct vertice{
  char valor;
  Cor cor;
  int d;
  struct vertice *proximo;
  struct vertice *raiz_arvore;
}Vertice;

typedef struct fila{
  Vertice *primeiro;
  Vertice *ultimo;
}Fila;

Vertice* start_vertice(char valor);
Fila* start_fila();
void add_fim_fila(Fila *fila,Vertice *v);
Vertice* remove_prim_fila(Fila *fila);
Vertice* buscar_vertice(Fila *fila, char valor);

Vertice* add_vert_arvore(Vertice *raiz,char novo);

Grafo* start_grafo();
void exibir_grafo();
void exibir_elementos(Grafo *grafo);
int buscar_posicao(Grafo *grafo,char elemento);
Vertice* buscar_vertice_vetor(Vertice* vetor[],char procurado,int tamanho);
Vertice** busca_largura(Grafo *grafo,char vert_inicio,char vert_destino);
void exibir_caminho(Grafo *grafo,Vertice **vertices,char vert_raiz,char vert_destino);

#endif
