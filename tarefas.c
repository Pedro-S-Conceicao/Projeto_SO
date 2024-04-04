#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tarefas.h"

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

float reduzirMatriz(int ordMatriz, int *matrizE)
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

void preencherMatriz(int ordMatriz, int *matriz, char *arqDat)
{
    FILE *arquivo = fopen(arqDat, "r");
    int *linha = (int *)malloc(sizeof(int));
    int *coluna = (int *)malloc(sizeof(int));
    if ((linha == NULL) || (coluna == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    for (*linha = 0; *linha < (ordMatriz); ++*linha)
    {
        char *aux = (char *)malloc(sizeof(char));
        if ((aux == NULL))
        {
            printf("Memória insuficiente!!!\n");
            exit(EXIT_FAILURE);
        }

        for (*coluna = 0; *coluna < (ordMatriz); ++*coluna)
        {
            *aux = fgetc(arquivo);
            matriz[posicao(linha, coluna, numColunas)] = (*aux - 48);

            if ((*aux == ' ') || (*aux == '\n'))
                --*coluna;
        }

        free(aux);
    }

    free(linha);
    free(coluna);
    fclose(arquivo);
}

float multiplicarMatriz(int ordMatriz, int *matrizC, int *matrizD, int *matrizE)
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