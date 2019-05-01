#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(int argc,char* argv[]){
  No *raiz = NULL;

  while(1){
    int opcao,valor;
    scanf("%d",&opcao);

    switch(opcao){

      case 1:
        scanf("%d",&valor);
        adicionar(&raiz,valor);
        break;
      case 2:
        exibir_pre_order(raiz);
        printf("\n");
        break;
      case 3:
        scanf("%d",&valor);
        remover(&raiz,valor);
        break;
      case 999:
        exit(0);
    }
  }
  return 0;
}
