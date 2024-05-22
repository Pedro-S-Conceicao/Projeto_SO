#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tarefas.h"

#define nThreads (atoi(argv[1]))
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

    float *tempoSoma = alocaVariavel();
    float *tempoMultiplicar = alocaVariavel();
    float *tempoReduzir = alocaVariavel();

    int *matrizA = alocaVetor(ordemMatriz);
    int *matrizB = alocaVetor(ordemMatriz);
    int *matrizC = alocaVetor(ordemMatriz);
    int *matrizD = alocaVetor(ordemMatriz);
    int *matrizE = alocaVetor(ordemMatriz);

    lerEPreencherMatriz((ordemMatriz), matrizA, matrizB, arquivoA, arquivoB, nThreads);

    *tempoSoma = tarefasSomarEMultiMatriz((unsigned)(ordemMatriz), (unsigned)(nThreads), matrizA, matrizB, matrizD, 'a');

    free(matrizB);

    lerEGravarMatriz((ordemMatriz), matrizC, matrizD, arquivoC, arquivoD, nThreads);

    *tempoMultiplicar = tarefasSomarEMultiMatriz((unsigned)(ordemMatriz), (unsigned)(nThreads), matrizC, matrizD, matrizE, 'b');

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
