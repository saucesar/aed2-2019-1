#include "grafo_matriz.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[]) {
  Grafo *g = start_grafo();
  exibir_grafo(g);
  return 0;
}
