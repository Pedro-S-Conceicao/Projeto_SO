#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define posicao(linha, colunas, numColunas) ((*linha) * ((ordMatriz)) + (*coluna))

float somarMatriz(int ordMatriz, int *matrizA, int *matrizB, int *matrizD)
{
    clock_t *inicio = (clock_t *)malloc(sizeof(clock_t));
    clock_t *fim = (clock_t *)malloc(sizeof(clock_t));
    if ((inicio == NULL) || (fim == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    double tempoTotal;
    *inicio = clock();

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

            matrizD[posicao(linha, coluna, numColunas)] = matrizA[posicao(linha, coluna, numColunas)] + matrizB[posicao(linha, coluna, numColunas)];
        }
    }

    free(linha);
    free(coluna);

    *fim = clock() - *inicio;
    tempoTotal = ((double)*fim) / CLOCKS_PER_SEC;

    free(inicio);
    free(fim);

    return tempoTotal;
}