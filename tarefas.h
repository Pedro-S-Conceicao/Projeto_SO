#ifndef _TAREFAS
#define _TAREFAS
#include <pthread.h>

/* Definição da estrutura que contém os parâmetros para
 * uma thread.
 * Os parâmetros são a posição de início, a posição do final, a ordem da matriz e as matrizes
 * e o endereço do vetor.
 */
typedef struct
{
    unsigned int posInicio;
    unsigned int posFinal;
    unsigned int ord_Matriz;
    int *matriz_1;
    int *matriz_2;
    int *matriz_3;
    char *arquivo;
} parametrosThread;

parametrosThread *alocaVetorParametrosThreads(unsigned int nThreads);

pthread_t *alocaIdsThreads(unsigned int tamanho);

float *alocaVariavel();

int *alocaVetor(int ordMatriz);

void escreverMatriz(int ordMatriz, int *matriz, char *arqDat);

void lerEGravarMatriz(int ordMatriz, int *matriz_A, int *matriz_B, char *arqDat_A, char *arqDat_B, unsigned int nThreads);

void lerEPreencherMatriz(int ordMatriz, int *matriz_A, int *matriz_B, char *arqDat_A, char *arqDat_B, unsigned int nThreads);

float reduzirMatriz(int ordMatriz, int *matrizE);

float tarefasSomarEMultiMatriz(unsigned int ordMatriz, unsigned int nThreads, int *matriz_A, int *matriz_B, int *matriz_C, char tarefa);

void *thrdSomarMatriz(void *args);

void *thrdMultiplicarMatriz(void *args);

void *thrdLerEPeencherMatriz(void *args);

void *thrdGravarMatriz(void *args);

void *thrdReduzirMatriz(void *args);

void preencherMatriz(int ordMatriz, int *matriz, char *arqDat);

#endif