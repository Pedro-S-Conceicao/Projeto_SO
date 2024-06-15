#ifndef _TASKS
#define _TASKS
#include <pthread.h>

/**
 * Definição da estrutura que contém os parâmetros para
 * uma thread.
 * @param start_Pos Posição inicial.
 * @param end_Pos Posição final.
 * @param matrix_Ord Ordem da Matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param file_Dat Pornteiro para o endereço do arquivo.dat.
 * @param partialResult Ponteiro para o endereço do valor parcial da redução por soma.
 */
typedef struct
{
    unsigned int start_Pos;
    unsigned int end_Pos;
    unsigned int matrix_Ord;
    long int *matrix_1;
    long int *matrix_2;
    long int *matrix_3;
    char *file_Dat;
    long int *partial_Result;
} ThreadParameters;

void InitialParamCheck(char *argThreads,long int *nThreads, char *argmatrixOrd,long int *matrixOrd, int argc);

double timeCalc(struct timespec tstart, struct timespec tend);

ThreadParameters *vectorParameterAlloc(unsigned int nThreads);

pthread_t *ThreadIDAlloc(unsigned int size);

long int *MatrixAlloc(int matrixOrd);

void FilesReaderAndWriter(int matrixOrd, long int *matrix_A, long int *matrix_B, char *arqDat_A, char *arqDat_B, unsigned int nThreads);

void FilesReaderAndAssignment(int matrixOrd, long int *matrix_A, long int *matrix_B, char *fileDat_A, char *fileDat_B, unsigned int nThreads);

double MatrixReduceAndWriter(int matrixOrd, long int *matrizE, char *arqDat_E, unsigned int nThreads);

float SumAndMultTasks(unsigned int matrixOrd, long int *matriz_A, long int *matriz_B, long int *matriz_C, char task, unsigned int nThreads);

void *thrdP_Sum(void *args);

void *thrdP_Mult(void *args);

void *thrdReading(void *args);

void *thrdWriting(void *args);

void *thrdP_Reduce(void *args);

void preencherMatriz(int matrixOrd, long int *matriz, char *arqDat);

#endif