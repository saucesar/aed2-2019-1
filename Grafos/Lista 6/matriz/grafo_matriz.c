#include <stdlib.h>
#include <stdio.h>
#include "grafo_matriz.h"

Grafo* start_grafo(){
  FILE *arquivo = fopen("arquivo.txt","r");

  if(arquivo == NULL){
    printf("O arquivo nao existe!!!\n");
    exit(1);
  }

  Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
  grafo->v = getc(arquivo)-'0';//converte char para inteiro
  grafo->e = getc(arquivo)-'0';

  int a = grafo->v*sizeof(int*);

  grafo->elementos = (char*)malloc(grafo->v*sizeof(char));
  grafo->conexoes = malloc(a);

  for(int i = 0;i<grafo->v;i++){
    getc(arquivo);//para pular a linha
    grafo->conexoes[i] = (int*)malloc(a);
    grafo->elementos[i] = getc(arquivo);
    for(int j = 0;j<grafo->v;j++){
      if(i == j){grafo->conexoes[i][j] = 1;}
      else{grafo->conexoes[i][j] = 0;}
    }
  }

  for(int j = 0;j<grafo->e;j++){
    getc(arquivo);//para pular a linha
    char elemento1 = getc(arquivo);
    char elemento2 = getc(arquivo);

    int posicao_e1 = buscar_posicao(grafo,elemento1);
    int posicao_e2 = buscar_posicao(grafo,elemento2);
    if(posicao_e1 != -1 && posicao_e2 != -1){
      grafo->conexoes[posicao_e1][posicao_e2] = 1;
      grafo->conexoes[posicao_e2][posicao_e1] = 1;
    }
  }

  fclose(arquivo);
  return grafo;
}

void exibir_elementos(Grafo *grafo){
  printf("  ");
  for(int i = 0;i<grafo->v;i++){
    printf("%c ",grafo->elementos[i]);
  }
  printf("\n");
}

void exibir_grafo(Grafo *grafo){
  exibir_elementos(grafo);
  for(int i = 0; i<grafo->v;i++){
    printf("%c ",grafo->elementos[i]);
    for(int j = 0; j<grafo->v;j++){printf("%d ",grafo->conexoes[i][j]);}
    printf("\n");
  }
}

int buscar_posicao(Grafo *grafo,char elemento){
  int posicao = -1;
  for(int i = 0;i<grafo->v;i++){
    if(grafo->elementos[i] == elemento){
      posicao = i;
      break;
    }
  }
  return posicao;
}

Vertice** busca_largura(Grafo *grafo,char vert_raiz,char vert_destino){

  Vertice** vertices = (Vertice**)malloc(grafo->v*sizeof(Vertice*));
  for(int i = 0;i<grafo->v;i++){vertices[i] = start_vertice(grafo->elementos[i]);}

  Fila *fila = start_fila();

  add_fim_fila(fila,buscar_vertice_vetor(vertices,vert_raiz,grafo->v));
  fila->primeiro->cor = CINZA;
  fila->primeiro->d = 0;

  while (fila->primeiro != NULL) {
    Vertice *u = remove_prim_fila(fila);
    int posicao_u = buscar_posicao(grafo,u->valor);

    for(int k = 0;k<grafo->v;k++){
      if(grafo->conexoes[posicao_u][k] && u->valor != grafo->elementos[k]){
        Vertice *v = buscar_vertice_vetor(vertices,grafo->elementos[k],grafo->v);
        if(v->cor == BRANCO){
          v->d = u->d + 1;
          v->cor = CINZA;
          v->raiz_arvore = add_vert_arvore(v->raiz_arvore,u->valor);
          add_fim_fila(fila,v);
        }
      }
    }
    u->cor = PRETO;
  }
  for(int i = 0;i<grafo->v;i++){
    Vertice *c = vertices[i]->raiz_arvore;
    printf("ARVORE DE %c\n",vertices[i]->valor );
    printf("%c, ",vertices[i]->valor);
    while (c!=NULL) {
      printf("%c, ",c->valor);
      c = c->proximo;
    }
    printf("\n" );
    //printf("%c[%d], ",vertices[i]->valor,vertices[i]->cor);
  }
  printf("\n====================================================================\n");
  exibir_caminho(grafo,vertices,vert_raiz,vert_destino);
  return vertices;
}

Vertice* start_vertice(char valor){
  Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
  novo->valor = valor;
  novo->cor = BRANCO;
  novo->d = INFINITO;
  novo->proximo = NULL;
  novo->raiz_arvore = NULL;
  return novo;
}

Fila* start_fila(){
  Fila *f = (Fila*)malloc(sizeof(Fila));
  f->primeiro = NULL;
  f->ultimo = NULL;
  return f;
}

void add_fim_fila(Fila *fila,Vertice *v){
  if(fila->primeiro == NULL){
    fila->primeiro = v;
    fila->ultimo = fila->primeiro;
  }
  else{
    fila->ultimo->proximo = v;
    fila->ultimo = fila->ultimo->proximo;
  }
}

Vertice* remove_prim_fila(Fila *fila){
  Vertice* primeiro = fila->primeiro;
  if(primeiro != NULL){fila->primeiro = primeiro->proximo;}
  return primeiro;
}

Vertice* buscar_vertice_vetor(Vertice* vetor[],char procurado,int tamanho){
  for(int i = 0;i<tamanho;i++){if(vetor[i]->valor == procurado){return vetor[i];}}
  return NULL;
}

Vertice* buscar_vertice(Fila *fila, char valor){
  Vertice *v = fila->primeiro;
  while (v != NULL && v->valor != valor) {v = v->proximo;}
  return v;
}

Vertice* add_vert_arvore(Vertice *raiz,char novo){
  if(raiz == NULL){return start_vertice(novo);}

  Vertice *v = raiz,*anterior = NULL;
  while (v != NULL) {
    v = v->proximo;
    anterior = v;
  }
  anterior->proximo = start_vertice(novo);
  return raiz;
}

void exibir_caminho(Grafo *grafo,Vertice **vertices,char vert_raiz,char vert_destino){
  if(vert_raiz == vert_destino){printf("%c\n",vert_raiz);}
  else{
    Vertice *v = buscar_vertice_vetor(vertices,vert_destino,grafo->v);
    if(v->raiz_arvore == NULL){printf("NAO EXISTE CAMINHO\n");}
    else{
      exibir_caminho(grafo,vertices,vert_raiz,v->raiz_arvore->valor);
      printf("%c ",v->valor);
    }
  }
}
