#include <stdlib.h>
#include <stdio.h>
#include "grafo_matriz.h"

Grafo* start_grafo(){
  FILE *arquivo = fopen("arquivo.txt","r");

  if(arquivo == NULL){
    printf("O nao existe!!!\n");
    exit(1);
  }

  Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
  grafo->v = getc(arquivo)-'0';
  grafo->e = getc(arquivo)-'0';

  int a = grafo->v*sizeof(int*);

  grafo->elementos = (char*)malloc(grafo->v*sizeof(char));
  grafo->conexoes = malloc(a);

  for(int i = 0;i<grafo->v;i++){
    getc(arquivo);//para pular a linha
    grafo->conexoes[i] = (int*)malloc(a);
    grafo->elementos[i] = getc(arquivo);
    grafo->conexoes[i][i] = 1;
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
