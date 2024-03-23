#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define posicao(linha, colunas, numColunas) ((*linha) * ((ordemMatriz)) + (*coluna))

float reduzirMatriz(int ordMatriz, int *matrizE)
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
    int *redPorSoma = (int *)malloc(sizeof(int));
    if ((linha == NULL) || (coluna == NULL) || (redPorSoma == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    *redPorSoma = 0;
    
    for (*linha = 0; *linha < (ordMatriz); ++*linha)
    {
        for (*coluna = 0; *coluna < (ordMatriz); ++*coluna)
        {
            *redPorSoma += matrizE[(*linha) * (ordMatriz) + (*coluna)];
        }
    }

    printf("Redução: %d\n", *redPorSoma);

    free(linha);
    free(coluna);
    free(redPorSoma);

    *fim = clock() - *inicio;
    tempoTotal = ((double)*fim) / CLOCKS_PER_SEC;

    free(inicio);
    free(fim);

    return tempoTotal;
}
