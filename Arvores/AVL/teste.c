#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc,char* argv[]){
  No *raiz = NULL;

  while(1){
    int opcao,valor,cresceu,diminuiu;
    scanf("%d",&opcao);

    switch(opcao){

      case 1:
        scanf("%d",&valor);
        raiz = adicionar(raiz,valor,&cresceu);
        break;
      case 2:
        exibir_pre_order(raiz);
        printf("\n");
        break;
      case 3:
        scanf("%d", &valor);
        raiz = remover(raiz, valor,&diminuiu);
        break;
      case 999:
        exit(0);
    }
  }
  return 0;
}
