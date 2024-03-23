#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define posicao(linha, colunas, numColunas) ((*linha) * ((ordMatriz)) + (*coluna))

void escreverMatriz(int ordMatriz, int *matriz, char *arqDat)
{     
    FILE *arquivo = fopen(arqDat, "r+");
    int *linha = (int *)malloc(sizeof(int));
    int *coluna = (int *)malloc(sizeof(int));
    if ((linha == NULL) || (coluna == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    for (*linha = 0; *linha < (ordMatriz); ++*linha)
    {
        for (*coluna = 0; *coluna < (ordMatriz); ++*coluna)
        {
            fprintf(arquivo, "%d ", matriz[posicao(linha, coluna, numColunas)]);
        }

        fseek(arquivo, -1, SEEK_CUR);
        fputc('\n', arquivo);
    }

    free(linha);
    free(coluna);
    fclose(arquivo);

}