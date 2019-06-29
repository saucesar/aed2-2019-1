#ifndef GRAFO_MATRIZ
#define GRAFO_MATRIZ

typedef enum cor{BRANCO,CINZA,PRETO}Cor;

typedef struct grafo_matriz{
  int v,e;
  char *elementos;
  int **conexoes;
}Grafo;

Grafo* start_grafo();
void exibir_grafo();
void exibir_elementos(Grafo *grafo);
int buscar_posicao(Grafo *grafo,char elemento);

#endif
