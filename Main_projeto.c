#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tarefas.h"

#define ordemMatriz (atoi(argv[2]))
#define arquivoA (argv[3])
#define arquivoB (argv[4])
#define arquivoC (argv[5])
#define arquivoD (argv[6])
#define arquivoE (argv[7])

int main(int argc, char *argv[])
{
    clock_t *inicio = (clock_t *)malloc(sizeof(clock_t));
    clock_t *fim = (clock_t *)malloc(sizeof(clock_t));
    double *tempoTotal = (double *)malloc(sizeof(double));
    *inicio = clock();

    float *tempoSoma = (float *)malloc(sizeof(float));
    float *tempoMultiplicar = (float *)malloc(sizeof(float));
    float *tempoReduzir = (float *)malloc(sizeof(float));
    if ((inicio == NULL) || (fim == NULL) || (tempoTotal == NULL) || (tempoSoma == NULL) || (tempoMultiplicar == NULL) || (tempoReduzir == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    int *matrizA = (int *)malloc((ordemMatriz) * (ordemMatriz) * sizeof(int));
    int *matrizB = (int *)malloc((ordemMatriz) * (ordemMatriz) * sizeof(int));
    int *matrizC = (int *)malloc((ordemMatriz) * (ordemMatriz) * sizeof(int));
    int *matrizD = (int *)malloc((ordemMatriz) * (ordemMatriz) * sizeof(int));
    int *matrizE = (int *)malloc((ordemMatriz) * (ordemMatriz) * sizeof(int));
    if ((matrizA == NULL) || (matrizB == NULL) || (matrizC == NULL) || (matrizD == NULL) || (matrizE == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    preencherMatriz((ordemMatriz), matrizA, arquivoA);

    preencherMatriz((ordemMatriz), matrizB, arquivoB);

    *tempoSoma = somarMatriz((ordemMatriz), matrizA, matrizB, matrizD);


    free(matrizB);

    escreverMatriz((ordemMatriz), matrizD, arquivoD);

    preencherMatriz((ordemMatriz), matrizC, arquivoC);

    *tempoMultiplicar = multiplicarMatriz((ordemMatriz), matrizC, matrizD, matrizE);

    free(matrizC);
    free(matrizD);

    escreverMatriz((ordemMatriz), matrizE, arquivoE);

    *tempoReduzir = reduzirMatriz((ordemMatriz), matrizE);

    free(matrizE);

    *fim = clock() - *inicio;
    *tempoTotal = ((double)*fim) / CLOCKS_PER_SEC;

    printf("Tempo soma: %f segundos.\n", *tempoSoma);
    printf("Tempo multiplicação: %f segundos.\n", *tempoMultiplicar);
    printf("Tempo redução: %f segundos.\n", *tempoReduzir);
    printf("Tempo total: %f segundos.\n", *tempoTotal);

    free(tempoSoma);
    free(tempoMultiplicar);
    free(tempoReduzir);
    free(inicio);
    free(fim);
    free(tempoTotal);

    return 0;
}
