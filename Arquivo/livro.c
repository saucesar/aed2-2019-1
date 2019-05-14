#include "livro.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

livro * ler_livro() {
    livro * novo = (livro *) malloc(sizeof(livro));
    char * buffer = (char *) malloc(sizeof(char) * 256);
    printf ("Digite o isbn: ");
    scanf("%d", &novo->isbn);
	getchar() ;
    printf ("Digite o titulo: ");
    fgets(buffer, 256, stdin);
    novo->titulo = strdup(tirar_enter(buffer));

    printf ("Digite o autor: ");
    fgets(buffer, 256, stdin);
    novo->autor = strdup(tirar_enter(buffer));

    printf ("Digite o editora: ");
    fgets(buffer, 256, stdin);
    novo->editora = strdup(tirar_enter(buffer));

    free(buffer);
    return novo;
}


void imprimir_livro(livro *l) {
    printf("ISBN: %d\n", l->isbn);
    printf("TITULO: %s\n", l->titulo);
    printf("AUTOR: %s\n", l->autor);
    printf("EDITORA: %s\n", l->editora);
}


char * tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
    return string;
}


void inicializar_tabela(tabela_livros *tabela, char *nome) {
    tabela->nome_arq = strdup(nome);
    tabela->dados = fopen(nome, "a");
    if(tabela->dados == NULL) {
        exit(1);
    }
    
    tabela->raiz = NULL;
}

void adicionar_livro(tabela_livros *tabela, livro * l) {
    int posicao;
    posicao = escrever_livro_arquivo(tabela, l);
    adicionar_indice(l->isbn, posicao, tabela->raiz);
}


int escrever_livro_arquivo(tabela_livros *tabela, livro * l) {
    int fim;
    fseek(tabela->dados, 0, SEEK_END);
    fim = ftell(tabela->dados);
    fprintf(tabela->dados, "%d|", l->isbn);
    fprintf(tabela->dados, "%s|", l->titulo);
    fprintf(tabela->dados, "%s|", l->autor);
    fprintf(tabela->dados, "%s|", l->editora);
    return fim;
}


livro * ler_livro_arquivo(tabela_livros *tabela, int posicao) {
    livro * novo = (livro *) malloc(sizeof(livro));
    fseek(tabela->dados, posicao, SEEK_SET);
    novo->isbn = atoi(ler_campo(tabela->dados));
    novo->titulo = strdup(ler_campo(tabela->dados));
    novo->autor = strdup(ler_campo(tabela->dados));
    novo->editora = strdup(ler_campo(tabela->dados));
    return novo;
}

char * ler_campo(FILE * fp) {
    char * buffer = malloc(sizeof(char) * 256);
    int i;
    for(i = 0; i < 256; i++) {
        buffer[i] = fgetc(tabela->dados);
        if(buffer[i] == '|') {
            buffer[i] = '\0';
            break;
        }
    }
    return buffer;

}
