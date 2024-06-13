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
    if (argc != 8)
    {
        fprintf(stderr, "Número de parâmetros de entrada incorreto\n");
        exit(EXIT_FAILURE);
    }

    clock_t inicio, fim;
    double *tempoTotal = alocaVariavel();
    inicio = clock();

    double *tempoSoma = alocaVariavel();
    double *tempoMultiplicar = alocaVariavel();
    double *tempoReduzir = alocaVariavel();

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

    *tempoReduzir = reduzirEGravarMatriz((ordemMatriz), matrizE, arquivoE, nThreads);

    free(matrizE);

    fim = clock() - inicio;
    *tempoTotal = ((double)fim) / CLOCKS_PER_SEC;

    printf("Tempo soma: %f segundos.\n", *tempoSoma);
    printf("Tempo multiplicação: %f segundos.\n", *tempoMultiplicar);
    printf("Tempo redução: %f segundos.\n", *tempoReduzir);
    printf("Tempo total: %f segundos.\n", *tempoTotal);

    return 0;
}

/**
 * Funcao para escrever a matriz em arquivo.dat.
 * @param ordMatriz Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 */

/**
 * Funcao para escrever a matriz em arquivo.dat.
 * @param ordMatriz Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 */