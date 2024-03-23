#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define posicao(linha, colunas, numColunas) ((*linha) * ((ordMatriz)) + (*coluna))

float multiplicarMatriz(int ordMatriz, int *matrizC, int *matrizD, int *matrizE)
{
    
    clock_t *inicio = (clock_t *)malloc(sizeof(clock_t));
    clock_t *fim = (clock_t *)malloc(sizeof(clock_t));
    if ((inicio == NULL )||(fim == NULL ))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    double tempoTotal;
    *inicio = clock();

    int *linha = (int *)malloc(sizeof(int));
    int *coluna = (int *)malloc(sizeof(int));
    int *k = (int *)malloc(sizeof(int));
    int *somaProduto = (int *)malloc(sizeof(int));
    if ((linha == NULL) || (coluna == NULL) || (k == NULL) || (somaProduto == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    for (*linha = 0; *linha < (ordMatriz); ++*linha)
    {
        for (*coluna = 0; *coluna < (ordMatriz); ++*coluna)
        {
            *somaProduto = 0;
            for (*k = 0; *k < (ordMatriz); ++*k)
            {
                *somaProduto += (matrizC[(*linha * (ordMatriz)) + *k]) * (matrizD[(*k * (ordMatriz)) + *coluna]);
            }

            matrizE[posicao(linha, coluna, numColunas)] = *somaProduto;
        }
    }

    free(linha);
    free(coluna);
    free(k);
    free(somaProduto);

    *fim = clock() - *inicio;
    tempoTotal = ((double)*fim) / CLOCKS_PER_SEC;

    free(inicio);
    free(fim);
    return tempoTotal;
}
