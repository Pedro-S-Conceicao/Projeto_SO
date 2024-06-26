//  Projeto Prático da disciplina TT304 – Sistemas Operacionais

//  Prof. André Leon S. Gradvohl, Dr. gradvohl@ft.unicamp.br

//  GRUPO : Threadreapper
//  Pedro dos Santos Conceição - 195514
//  Sérgio Carlos de Sousa Gregório Junior - 195505

//  projeto prático da disciplina TT304 – Sistemas Operacionais propõe desenvolvimento de um programa para resolução
//  do seguinte problema:
//  "O problema a ser resolvido é o seguinte. Dadas três matrizes de entrada, 𝐴ₙₓₙ,𝐵ₙₓₙ e 𝐶ₙₓₙ, o programa deverá calcular
//  inicialmente a matriz 𝐷ₙₓₙ, tal que 𝐷ₙₓₙ=(𝐴ₙₓₙ + 𝐵ₙₓₙ) e gravá-la em arquivo. Em seguida, o programa deverá calcular a
//  matriz 𝐸ₙₓₙtal que 𝐸ₙₓₙ=(𝐶ₙₓₙ × 𝐷ₙₓₙ). Por último, a matriz 𝐸ₙₓₙ deve ser gravada em arquivo e reduzida por soma, isto é,
//  todos os seus componentes devem ser somados, resultando em um único valor final."
//  Para tanto, o projeto propõe a realização de uma sequência de operações com matrizes de números inteiros, lidos a partir de
//  arquivos de entradas, e posterior gravação dos resultados em arquivos de saída.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tasks.h"
#include "errorSigns.h"

#define nThreadsArgv (argv[1])
#define matrixOrdArgv (argv[2])
#define fileA (argv[3])
#define fileB (argv[4])
#define fileC (argv[5])
#define fileD (argv[6])
#define fileE (argv[7])

int main(int argc, char *argv[])
{
    register double sumTime;
    register double multTime;
    register double reduceTime;
    register double totalTime = 0;
    long int nThreads;
    long int matrixOrd;

    InitialParamCheck(nThreadsArgv, &nThreads, matrixOrdArgv, &matrixOrd, argc);

    long int *matrixA = MatrixAlloc(matrixOrd);
    long int *matrixB = MatrixAlloc(matrixOrd);
    long int *matrixC = MatrixAlloc(matrixOrd);
    long int *matrixD = MatrixAlloc(matrixOrd);
    long int *matrixE = MatrixAlloc(matrixOrd);

    FilesReaderAndAssignment((matrixOrd), matrixA, matrixB, fileA, fileB, nThreads);

    sumTime = MatrixSum((unsigned)(matrixOrd), matrixA, matrixB, matrixD, (unsigned)(nThreads));

    free(matrixB);

    FilesReaderAndWriter((matrixOrd), matrixC, matrixD, fileC, fileD, nThreads);

    multTime = MatrixMult((unsigned)(matrixOrd), matrixC, matrixD, matrixE, (unsigned)(nThreads));

    free(matrixC);
    free(matrixD);

    reduceTime = MatrixReduceAndWriter((matrixOrd), matrixE, fileE, nThreads);

    free(matrixE);


    totalTime = (sumTime+multTime+totalTime);

    printf("Tempo soma: %lf segundos.\n", sumTime);
    printf("Tempo multiplicação: %lf segundos.\n", multTime);
    printf("Tempo redução: %lf segundos.\n", reduceTime);
    printf("Tempo total: %lf segundos.\n", totalTime);

    return 0;
}
