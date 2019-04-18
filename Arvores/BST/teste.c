#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc,char* argv[]){
  No *raiz = NULL;

  while(1){
    int opcao,valor;
    scanf("%d",&opcao);

    switch(opcao){
      No *buscado;
      case 1:
        scanf("%d",&valor);
        raiz = adicionar(raiz,valor);
        break;
      case 2:
        exibir_pre_order(raiz);
        printf("\n");
        break;
      case 3:
        exibir_in_order(raiz);
        printf("\n");
        break;
      case 4:
        exibir_pos_order(raiz);
        printf("\n");
        break;
      case 5:
        scanf("%d", &valor);
        raiz = remover(raiz, valor);
        break;
      case 6:
        printf("%d\n",maior_elemento(raiz));
        break;
      case 7:
        printf("%d\n",menor_elemento(raiz));
        break;
      case 8:
        printf("%d\n",altura(raiz));
        break;
      case 9:
        scanf("%d", &valor);
        printf("%d\n",buscar_pai(NULL,raiz,valor));
        break;
      case 10:
        scanf("%d", &valor);
        printf("%d\n",sucessor(raiz,valor));
        break;
      case 11:
        scanf("%d", &valor);
        printf("%d\n",antecessor(raiz,valor));
        break;
      case 999:
        exit(0);
    }
  }
  return 0;
}
