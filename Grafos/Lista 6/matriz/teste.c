#include "grafo_matriz.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[]) {
  Grafo *g = start_grafo();
  exibir_grafo(g);
  busca_largura(g,'A','D');
  return 0;
}
