#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "tasks.h"
#include "errorSigns.h"

/**
 * Definição para acesso às posições do vetor bidimensional alocado dinâmicamente.
 * @param line Indicação da linha no vetor.
 * @param columns Indicação da coluna no vetor.
 * @param numColumns Número de colunas do vetor.
 * @param matrixOrd Ordem da Matriz.
 */
#define position(line, columns, numColumns) ((line) * ((matrixOrd)) + (column))

/**
 * Funcao para calcular o tempo decorrido entre duas marcacoes.
 * @param tstart Marcacao do inicio da contagem de tempo.
 * @param tend Marcacao do final da contagem de tempo.
 */
double timeCalc(struct timespec tstart, struct timespec tend)
{
    return ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
           ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
}

/**
 * Função para alocar dinâmicamente um vetor do tipo ThreadParameters.
 * @param nThreads Número de threads usadas para as tarefas
 * @return Vetor alocado do tipo ThreadParameters.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na alocação do vetor.
 */
ThreadParameters *vectorParameterAlloc(unsigned int nThreads)
{
    ThreadParameters *vector;

    if ((vector = (ThreadParameters *)malloc(sizeof(ThreadParameters) * nThreads)) == NULL)
    {
        fprintf(stderr, "Problemas na alocação do vetor\n");
        exit(EXIT_FAILURE);
    }

    return vector;
}

/**
 * Função para alocar dinâmicamente um vetor de identificadores de threads.
 * @param size Número de posicoes do vetor.
 * @return Vetor alocado do tipo pthread_t.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na alocação do vetor.
 */
pthread_t *ThreadIDAlloc(unsigned int size)
{
    pthread_t *vector;

    if (size <= 0)
        return NULL;

    if ((vector = (pthread_t *)malloc(sizeof(pthread_t) * size)) == NULL)
    {
        fprintf(stderr, "Problemas na alocação do vetor\n");
        exit(EXIT_FAILURE);
    }

    return vector;
}

/**
 * Função para alocar dinâmicamente uma matriz de inteiros longos.
 * @return Matriz alocada.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na alocação da matriz
 */
long int *MatrixAlloc(int matrixOrd)
{
    long int *matrix;

    if ((matrix = (long int *)malloc((matrixOrd) * (matrixOrd) * sizeof(long int))) == NULL)
    {
        fprintf(stderr, "Problemas na alocação do vetor\n");
        exit(EXIT_FAILURE);
    }

    return matrix;
}

/**
 * Função para criação e chamada da função thrdReading e thrdWriting, que lê e escreve matrizes em arquivo.dat, respectivamente.
 * @param matrixOrd Ordem da Matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param arqDat Ponteiro para o endereço do arquivo.dat.
 * @param nThreads Número de threads T.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na criação ou junção das threads.
 */
void FilesReaderAndWriter(int matrixOrd, long int *matrix_A, long int *matrix_B, char *arqDat_A, char *arqDat_B, unsigned int nThreads)
{
    ThreadParameters *parameters;
    register unsigned int i = 0;
    register unsigned errDetector;

    if (nThreads == 1)
    {
        parameters = vectorParameterAlloc(2);

        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrix_A;
        parameters[i].file_Dat = arqDat_A;

        thrdReading((void *)&parameters[i]);

        i = 1;
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrix_B;
        parameters[i].file_Dat = arqDat_B;

        thrdWriting((void *)&parameters[i]);
    }

    else
    {
        pthread_t *idsThread;
        parameters = vectorParameterAlloc(2);
        idsThread = ThreadIDAlloc(2);

        for (i = 0; i < 2; i++)
        {
            if (i == 0)
            {
                parameters[i].matrix_Ord = matrixOrd;
                parameters[i].matrix_1 = matrix_A;
                parameters[i].file_Dat = arqDat_A;

                errDetector = pthread_create(&idsThread[i],
                                             NULL,
                                             thrdReading,
                                             (void *)&parameters[i]);
            }
            else
            {
                parameters[i].matrix_Ord = matrixOrd;
                parameters[i].matrix_1 = matrix_B;
                parameters[i].file_Dat = arqDat_B;

                errDetector = pthread_create(&idsThread[i],
                                             NULL,
                                             thrdWriting,
                                             (void *)&parameters[i]);
            }

            if (errDetector != 0)
            {
                fprintf(stderr, "Erro na criação do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        for (i = 0; i < 2; i++)
        {
            errDetector = pthread_join(idsThread[i], NULL);

            if (errDetector != 0)
            {
                fprintf(stderr, "Erro na junção do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * Função para criação e chamada da função thrdReading que lê o arquivo.dat, que possui os dados da matriz, e atribui à uma matriz.
 * @param matrixOrd Ordem da Matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param file Ponteiro para o endereço do arquivo.dat.
 * @param nThreads Número de threads T.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na criação ou junção das threads.
 */
void FilesReaderAndAssignment(int matrixOrd, long int *matrix_A, long int *matrix_B, char *fileDat_A, char *fileDat_B, unsigned int nThreads)
{
    ThreadParameters *parameters;
    register unsigned int i = 0;
    register int errDetector;

    if (nThreads == 1)
    {
        parameters = vectorParameterAlloc(2);

        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrix_A;
        parameters[i].file_Dat = fileDat_A;

        thrdReading((void *)&parameters[i]);

        i = 1;
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrix_B;
        parameters[i].file_Dat = fileDat_B;

        thrdReading((void *)&parameters[i]);
    }

    else
    {
        pthread_t *idsThread;
        parameters = vectorParameterAlloc(2);
        idsThread = ThreadIDAlloc(2);

        for (i = 0; i < 2; i++)
        {
            if (i == 0)
            {
                parameters[i].matrix_Ord = matrixOrd;
                parameters[i].matrix_1 = matrix_A;
                parameters[i].file_Dat = fileDat_A;
            }
            else
            {
                parameters[i].matrix_Ord = matrixOrd;
                parameters[i].matrix_1 = matrix_B;
                parameters[i].file_Dat = fileDat_B;
            }

            errDetector = pthread_create(&idsThread[i],
                                         NULL,
                                         thrdReading,
                                         (void *)&parameters[i]);

            if (errDetector != 0)
            {
                fprintf(stderr, "Erro na criação do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        for (i = 0; i < 2; i++)
        {
            errDetector = pthread_join(idsThread[i], NULL);

            if (errDetector != 0)
            {
                fprintf(stderr, "Erro na junção do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * Função para criação e chamada da função thrdP_Reduce e thrdWriting, que realiza a redução por soma da matriz em um valor do tipo int e escreve num arquivo.dat, respectivamente.
 * @param matrixOrd Ordem da Matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param file Ponteiro para o endereço do arquivo.dat.
 * @param nThreads Número de threads T.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na criação ou junção das threads.
 */
double MatrixReduceAndWriter(int matrixOrd, long int *matrizE, char *fileDat_A, unsigned int nThreads)
{

    register unsigned int i = 0;
    long int partialResult = 0;
    register int errDetector;
    double reduceTime;
    ThreadParameters *parameters;
    struct timespec timeStart = {0, 0};
    struct timespec timeEnd = {0, 0};

    if (nThreads == 4)
    {
        pthread_t *idsThread;

        parameters = vectorParameterAlloc(4);
        idsThread = ThreadIDAlloc(4);

        unsigned int elementosPorThread = (unsigned int)matrixOrd / (nThreads - 1);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        for (i = 0; i < 3; i++)
        {
            parameters[i].start_Pos = i * elementosPorThread;
            parameters[i].end_Pos = (i == nThreads - 2) ? (unsigned int)matrixOrd : (i + 1) * elementosPorThread;
            parameters[i].matrix_Ord = matrixOrd;
            parameters[i].matrix_1 = matrizE;
            parameters[i].partial_Result = &partialResult;

            errDetector = pthread_create(&idsThread[i],
                                         NULL,
                                         thrdP_Reduce,
                                         &parameters[i]);
            if (errDetector != 0)
            {
                fprintf(stderr, "Erro na criação do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrizE;
        parameters[i].file_Dat = fileDat_A;

        errDetector = pthread_create(&idsThread[i],
                                     NULL,
                                     thrdWriting,
                                     (void *)&parameters[i]);
        if (errDetector != 0)
        {
            fprintf(stderr, "Erro na criação do thread %d\n", i);
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < 4; i++)
        {
            pthread_join(idsThread[i], NULL);
            if (errDetector != 0)
            {
                fprintf(stderr, "Erro na junção do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }

    else
    {

        parameters = vectorParameterAlloc(2);
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrizE;
        parameters[i].file_Dat = fileDat_A;

        thrdWriting((void *)&parameters[i]);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        i = 1;
        parameters[i].start_Pos = 0;
        parameters[i].end_Pos = matrixOrd;
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrizE;
        parameters[i].partial_Result = &partialResult;

        thrdP_Reduce((void *)&parameters[i]);

        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }

    int redPorSoma = partialResult;

    printf("Redução: %d\n", redPorSoma);

    reduceTime = timeCalc(timeStart, timeEnd);

    return reduceTime;
}

/**
 * Função para a tarefa de somar a matrizA com a matrizB gravando na matrizD ou a tarefa de multiplicar a matrizC pela matrizD gravando na matrizE.
 * @param matrixOrd Ordem da Matriz.
 * @param matriz_(A/B/C) Ponteiro para o endereço da matriz A,B e D, respectivamente.
 * @param task Indicação da tarefa a ser realizada ('a' para soma e 'b' para multiplicação)
 * @param nThreads Número de threads usadas para as tarefas
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na criação ou junção das threads.
 */
float SumAndMultTasks(unsigned int matrixOrd, long int *matriz_A, long int *matriz_B, long int *matriz_C, char task, unsigned int nThreads)
{
    register unsigned int i = 0;
    unsigned int quantElementos;
    register int err;
    double totalTime;
    ThreadParameters *parameters;
    struct timespec timeStart = {0, 0};
    struct timespec timeEnd = {0, 0};

    if (nThreads == 1)
    {
        parameters = vectorParameterAlloc(1);
        parameters[i].start_Pos = 0;
        parameters[i].end_Pos = matrixOrd;
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matriz_A;
        parameters[i].matrix_2 = matriz_B;
        parameters[i].matrix_3 = matriz_C;

        if (task == 'a')
        {
            clock_gettime(CLOCK_MONOTONIC, &timeStart);

            thrdP_Sum((void *)&parameters[i]);

            clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        }
        else
        {
            clock_gettime(CLOCK_MONOTONIC, &timeStart);

            thrdP_Mult((void *)&parameters[i]);

            clock_gettime(CLOCK_MONOTONIC, &timeEnd);
        }
    }

    else
    {
        pthread_t *idsThread;
        parameters = vectorParameterAlloc(nThreads);
        idsThread = ThreadIDAlloc(nThreads);
        quantElementos = matrixOrd / nThreads;

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        for (i = 0; i < nThreads; i++)
        {
            parameters[i].start_Pos = quantElementos * i;
            parameters[i].end_Pos = (quantElementos * (i + 1));
            parameters[i].matrix_Ord = matrixOrd;
            parameters[i].matrix_1 = matriz_A;
            parameters[i].matrix_2 = matriz_B;
            parameters[i].matrix_3 = matriz_C;

            if (task == 'a')
            {
                err = pthread_create(&idsThread[i],
                                     NULL,
                                     thrdP_Sum,
                                     (void *)&parameters[i]);
            }

            else
            {
                err = pthread_create(&idsThread[i],
                                     NULL,
                                     thrdP_Mult,
                                     (void *)&parameters[i]);
            }

            if (err != 0)
            {
                fprintf(stderr, "Erro na criação do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        for (i = 0; i < nThreads; i++)
        {
            err = pthread_join(idsThread[i], NULL);

            if (err != 0)
            {
                fprintf(stderr, "Erro na junção do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }
    totalTime = timeCalc(timeStart, timeEnd);

    return totalTime;
}

/**
 * Função (thread) que calcula a soma de duas matrizes e guarda o resultado numa terceira matriz.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 * @param start_Pos Posicao inicial do vetor.
 * @param end_Pos A posicao final do vetor.
 * @param matrix_Ord A ordem da matriz
 * @param matrix Ponteiro para o endereço da matriz.
 * @return Soma dos elementos
 */
void *thrdP_Sum(void *args)
{
    register unsigned int start;
    register unsigned int end;
    register unsigned int matrixOrd;
    register unsigned int line;
    register unsigned int column;
    long int *matriz_A;
    long int *matriz_B;
    long int *matriz_C;

    start = ((ThreadParameters *)args)->start_Pos;
    end = ((ThreadParameters *)args)->end_Pos;
    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    matriz_B = ((ThreadParameters *)args)->matrix_2;
    matriz_C = ((ThreadParameters *)args)->matrix_3;

    for (line = start; line < end; ++line)
    {
        for (column = 0; column < matrixOrd; ++column)
        {

            matriz_C[position(line, column, numColumns)] = matriz_A[position(line, column, numColumns)] + matriz_B[position(line, column, numColumns)];
        }
    }
    return NULL;
}

/**
 * Função (thread) que calcula a multiplicação de duas matrizes e guarda o resultado numa terceira matriz.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 * @param start_Pos Posicao inicial do vetor.
 * @param end_Pos A posicao final do vetor.
 * @param matrix_Ord A ordem da matriz
 * @param matrix Ponteiro para o endereço da matriz.
 * @return Soma dos elementos
 */
void *thrdP_Mult(void *args)
{
    register unsigned int start;
    register unsigned int end;
    register unsigned int matrixOrd;
    register unsigned int line;
    register unsigned int column;
    register unsigned int k;
    long int somaProduto;
    long int *matriz_A;
    long int *matriz_B;
    long int *matriz_C;

    start = ((ThreadParameters *)args)->start_Pos;
    end = ((ThreadParameters *)args)->end_Pos;
    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    matriz_B = ((ThreadParameters *)args)->matrix_2;
    matriz_C = ((ThreadParameters *)args)->matrix_3;

    for (line = start; line < end; ++line)
    {
        for (column = 0; column < matrixOrd; ++column)
        {
            somaProduto = 0;
            for (k = 0; k < (matrixOrd); ++k)
            {
                somaProduto += (matriz_A[(line * (matrixOrd)) + k]) * (matriz_B[(k * (matrixOrd)) + column]);
            }
            matriz_C[position(line, column, numColumns)] = somaProduto;
        }
    }

    return NULL;
}

/**
 * Função (thread) que lê um arquivo.dat e atribui à uma matriz
 * @param args Argumentos passados a thread. Esses argumentos sao:
 * @param matrix_Ord A ordem da matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param file_Dat Ponteiro para o endereço do arquivo.dat.
 * @return Soma dos elementos
 */
void *thrdReading(void *args)
{
    register unsigned int matrixOrd;
    register unsigned int line;
    register unsigned int column;
    long int *matriz_A;

    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    FILE *fileDat = fopen((((ThreadParameters *)args)->file_Dat), "r");

    for (line = 0; line < matrixOrd; line++)
    {
        for (column = 0; column < matrixOrd; column++)
        {
            if (!fscanf(fileDat, "%ld", &matriz_A[position(line, column, numColumns)]))
            {
                perror("Erro ao ler o arquivo");
                fclose(fileDat);
                exit(1);
            }
        }
    }

    fclose(fileDat);
    return NULL;
}

/**
 * Função (thread) para escrever matrizes em arquivo.dat.
 * de uma matriz
 * @param args Argumentos passados a thread. Esses argumentos sao:
 * @param matrix_Ord A ordem da matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param file_Dat Ponteiro para o endereço do arquivo.dat.
 * @return Soma dos elementos
 */
void *thrdWriting(void *args)
{
    register unsigned int matrixOrd;
    register unsigned int line;
    register unsigned int column;
    long int *matriz_A;

    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    FILE *arqDat = fopen((((ThreadParameters *)args)->file_Dat), "r+");

    for (line = 0; line < (matrixOrd); ++line)
    {
        for (column = 0; column < (matrixOrd); ++column)
        {
            fprintf(arqDat, "%ld ", matriz_A[position(line, column, numColumns)]);
        }

        fseek(arqDat, -1, SEEK_CUR);
        fputc('\n', arqDat);
    }

    return NULL;
}

/**
 * Função (thread) para escrever matrizes em arquivo.dat.
 * de uma matriz
 * @param args Argumentos passados a thread. Esses argumentos sao:
 * @param start_Pos Posicao inicial do vetor.
 * @param end_Pos A posicao final do vetor.
 * @param matrix_Ord A ordem da matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param partial_Result Resultado parcial da redução por soma
 * @return Soma dos elementos
 */
void *thrdP_Reduce(void *args)
{
    register unsigned int inicio;
    register unsigned int final;
    register unsigned int matrixOrd;
    register unsigned int line;
    register unsigned int column;
    long int *matriz_A;
    long int redPorSoma = 0;

    inicio = ((ThreadParameters *)args)->start_Pos;
    final = ((ThreadParameters *)args)->end_Pos;
    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    matriz_A = ((ThreadParameters *)args)->matrix_1;

    for (line = inicio; line < final; ++line)
    {
        for (column = 0; column < matrixOrd; ++column)
        {
            redPorSoma += matriz_A[(line) * (matrixOrd) + (column)];
        }
    }

    *((ThreadParameters *)args)->partial_Result += redPorSoma;

    return NULL;
}

/**
 * Funcao para ler o arquivo.dat, que possui os dados da matriz, e atribuí-los a uma matriz.
 * @param matrixOrd Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 */
// void preencherMatriz(int matrixOrd, int *matriz, char *arqDat)
// {
//     FILE *arquivo = fopen(arqDat, "r");
//     int line = (int *)malloc(sizeof(int));
//     int column = (int *)malloc(sizeof(int));
//     if ((line == NULL) || (column == NULL))
//     {
//         printf("Memória insuficiente!!!\n");
//         exit(EXIT_FAILURE);
//     }

//     for (line = 0; line < (matrixOrd); ++line)
//     {
//         char aux = (char *)malloc(sizeof(char));
//         if (aux != 0)
//         {
//             fprintf(stderr, "Erro na alocação da variável\n");
//             exit(EXIT_FAILURE);
//         }

//         for (column = 0; column < (matrixOrd); ++column)
//         {
//             aux = fgetc(arquivo);
//             matriz[posicao(line, column, numColumns)] = (aux - 48);

//             if ((aux == ' ') || (aux == '\n'))
//                 --column;
//         }

//         free(aux);
//     }

//     free(line);
//     free(column);
//     fclose(arquivo);
// }

/**
 * Funcao para escrever a matriz em arquivo.dat.
 * @param matrixOrd Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 */
