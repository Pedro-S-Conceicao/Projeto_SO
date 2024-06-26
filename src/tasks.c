#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "tasks.h"
#include "errorSigns.h"

/**
 * Função que checa os argumentos de entrada, verificando se a quantidade de argumentos é válida e convertendo a parte inicial da string dos argumentos em um valor long int. Caso a quantidade de argumentos seja inválida ou a string seja iniciada de caracteres, o programa se encerra.
 * @param argThreads Ponteiro para endereço do argumento das threads.
 * @param nThreads Ponteiro para endereço de memória do número de threads de tipo long int.
 * @param argmatrixOrd Ponteiro para endereço do argumento da ordem da matriz.
 * @param matrixOrd Ponteiro para endereço de memória da ordem da matriz tipo long int.
 * @param argc Número de argumentos de entrada.
 * @throw Argumentos na linha de comando inválidos.
 */
void InitialParamCheck(char *argThreads, long int *nThreads, char *argmatrixOrd, long int *matrixOrd, int argc)
{
    char *str;

    if (argc != 8)
    {
        errorSign('c');
    }
    else if ((*nThreads = (strtol(argThreads, &str, 10))) == 0)
    {
        fprintf(stderr, "O argumento \"%s\" é uma string\nExecute o Programa com um argumento válido", str);
        errorSign('g');
    }
    else if ((*matrixOrd = (strtol(argmatrixOrd, &str, 10))) == 0)
    {
        fprintf(stderr, "O argumento \"%s\" é uma string\nExecute o Programa com um argumento válido", str);
        errorSign('g');
    }
    else if ((*nThreads < 1)||(*nThreads == 3)||(*nThreads > 4))
    {
        errorSign('k');
    }
}

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
 * @return Tempo decorrido.
 */
double timeCalc(struct timespec timeStart, struct timespec timeEnd)
{
    return ((double)timeEnd.tv_sec + 1.0e-9 * timeEnd.tv_nsec) -
           ((double)timeStart.tv_sec + 1.0e-9 * timeStart.tv_nsec);
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
        errorSign('d');
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

    if ((vector = (pthread_t *)malloc(sizeof(pthread_t) * size)) == NULL)
    {
        errorSign('e');
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
        errorSign('f');
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

    unsigned int errDetector;

    if (nThreads == 1)
    {
        parameters = vectorParameterAlloc(2);

        parameters[0].matrix_Ord = matrixOrd;
        parameters[0].matrix_1 = matrix_A;
        parameters[0].file_Dat = arqDat_A;

        thrdReading((void *)&parameters[0]);

        parameters[1].matrix_Ord = matrixOrd;
        parameters[1].matrix_1 = matrix_B;
        parameters[1].file_Dat = arqDat_B;

        thrdWriting((void *)&parameters[1]);
    }

    else
    {
        pthread_t *idsThread;
        parameters = vectorParameterAlloc(2);
        idsThread = ThreadIDAlloc(2);

        parameters[0].matrix_Ord = matrixOrd;
        parameters[0].matrix_1 = matrix_A;
        parameters[0].file_Dat = arqDat_A;

        errDetector = pthread_create(&idsThread[0],
                                     NULL,
                                     thrdReading,
                                     (void *)&parameters[0]);

        if (errDetector != 0)
        {
            errorSign('a');
        }

        parameters[1].matrix_Ord = matrixOrd;
        parameters[1].matrix_1 = matrix_B;
        parameters[1].file_Dat = arqDat_B;

        errDetector = pthread_create(&idsThread[1],
                                       NULL,
                                       thrdWriting,
                                       (void *)&parameters[1]);

        if (errDetector != 0)
        {
            errorSign('a');
        }

        for (unsigned int i = 0; i < 2; i++)
        {
            errDetector = pthread_join(idsThread[i], NULL);

            if (errDetector != 0)
            {
                errorSign('b');
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
    

    parameters = vectorParameterAlloc(2);

    int errDetector;

    if (nThreads == 1)
    {
        parameters[0].matrix_Ord = matrixOrd;
        parameters[0].matrix_1 = matrix_A;
        parameters[0].file_Dat = fileDat_A;

        thrdReading((void *)&parameters[0]);

        parameters[1].matrix_Ord = matrixOrd;
        parameters[1].matrix_1 = matrix_B;
        parameters[1].file_Dat = fileDat_B;

        thrdReading((void *)&parameters[1]);
    }

    else
    {
        pthread_t *idsThread;
        idsThread = ThreadIDAlloc(2);

        parameters[0].matrix_Ord = matrixOrd;
        parameters[0].matrix_1 = matrix_A;
        parameters[0].file_Dat = fileDat_A;

        parameters[1].matrix_Ord = matrixOrd;
        parameters[1].matrix_1 = matrix_B;
        parameters[1].file_Dat = fileDat_B;

        for (unsigned int i = 0; i < 2; i++)
        {
            errDetector = pthread_create(&idsThread[i],
                                         NULL,
                                         thrdReading,
                                         (void *)&parameters[i]);

            if (errDetector != 0)
            {
                errorSign('a');
            }
        }

        for (unsigned int i = 0; i < 2; i++)
        {
            errDetector = pthread_join(idsThread[i], NULL);

            if (errDetector != 0)
            {
                errorSign('b');
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
 * @return Tempo de redução.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na criação ou junção das threads.
 */
double MatrixReduceAndWriter(int matrixOrd, long int *matrizE, char *fileDat_A, unsigned int nThreads)
{

    unsigned int i = 0;
    long int partialResult = 0;
    int errDetector;
    double reduceTime;
    ThreadParameters *parameters;
    struct timespec timeStart = {0, 0};
    struct timespec timeEnd = {0, 0};

    if (nThreads == 1)
    {
        parameters = vectorParameterAlloc(2);
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrizE;
        parameters[i].file_Dat = fileDat_A;

        thrdWriting((void *)&parameters[i]);

        i = 1;
        parameters[i].start_Pos = 0;
        parameters[i].end_Pos = matrixOrd;
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].matrix_1 = matrizE;
        parameters[i].n_Threads = nThreads;
        parameters[i].partial_Result = &partialResult;

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        thrdP_Reduce((void *)&parameters[i]);

        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }
    else
    {
        pthread_t *idsThread;

        parameters = vectorParameterAlloc(nThreads + 1);
        idsThread = ThreadIDAlloc(nThreads + 1);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        for (i = 0; i < nThreads; i++)
        {
            parameters[i].start_Pos = i;
            parameters[i].end_Pos = (matrixOrd + 1) - (nThreads - i);
            parameters[i].matrix_Ord = matrixOrd;
            parameters[i].matrix_1 = matrizE;
            parameters[i].n_Threads = nThreads;
            parameters[i].partial_Result = &partialResult;

            errDetector = pthread_create(&idsThread[i],
                                         NULL,
                                         thrdP_Reduce,
                                         &parameters[i]);
            if (errDetector != 0)
            {
                errorSign('a');
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
            errorSign('a');
        }

        for (i = 0; i < (nThreads + 1); i++)
        {
            pthread_join(idsThread[i], NULL);
            if (errDetector != 0)
            {
                errorSign('b');
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }

    printf("Redução: %ld\n", partialResult);

    reduceTime = timeCalc(timeStart, timeEnd);

    return reduceTime;
}

/**
 * Função para criação e chamada da função thrdP_Sum de somar a matrizA com a matrizB gravando na matrizD.
 * @param matrixOrd Ordem da Matriz.
 * @param matriz_(A/B/C) Ponteiro para o endereço da matriz A,B e D, respectivamente.
 * @param nThreads Número de threads usadas para as tarefas.
 * @return Tempo de soma.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na criação ou junção das threads.
 */
float MatrixSum(unsigned int matrixOrd, long int *matriz_A, long int *matriz_B, long int *matriz_C, unsigned int nThreads)
{
    unsigned int i = 0;
    int err;
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
        parameters[i].n_Threads = nThreads;
        parameters[i].matrix_1 = matriz_A;
        parameters[i].matrix_3 = matriz_C;
        parameters[i].matrix_2 = matriz_B;

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        thrdP_Sum((void *)&parameters[i]);

        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }

    else
    {
        pthread_t *idsThread;
        parameters = vectorParameterAlloc(nThreads);
        idsThread = ThreadIDAlloc(nThreads);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        for (i = 0; i < nThreads; i++)
        {
            parameters[i].start_Pos = i;
            parameters[i].end_Pos = (matrixOrd + 1) - (nThreads - i);
            parameters[i].matrix_Ord = matrixOrd;
            parameters[i].n_Threads = nThreads;
            parameters[i].matrix_1 = matriz_A;
            parameters[i].matrix_3 = matriz_C;
            parameters[i].matrix_2 = matriz_B;

            err = pthread_create(&idsThread[i],
                                 NULL,
                                 thrdP_Sum,
                                 (void *)&parameters[i]);

            if (err != 0)
            {
                errorSign('a');
            }
        }

        for (i = 0; i < nThreads; i++)
        {
            err = pthread_join(idsThread[i], NULL);

            if (err != 0)
            {
                errorSign('b');
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }
    totalTime = timeCalc(timeStart, timeEnd);

    return totalTime;
}

/**
 * Função para criação e chamada da função thrdP_Mult de multiplicar a matrizC pela matrizD gravando na matrizE.
 * @param matrixOrd Ordem da Matriz.
 * @param matriz_(A/B/C) Ponteiro para o endereço da matriz A,B e D, respectivamente.
 * @param nThreads Número de threads usadas para as tarefas.
 * @return Tempo de multiplicação.
 * @throw Saída de fluxo de texto e posterior encerramento do programa quando há erro na criação ou junção das threads.
 */
float MatrixMult(unsigned int matrixOrd, long int *matriz_A, long int *matriz_B, long int *matriz_C, unsigned int nThreads)
{
    unsigned int i = 0;
    int err;
    double totalTime;
    ThreadParameters *parameters;
    struct timespec timeStart = {0, 0};
    struct timespec timeEnd = {0, 0};
    long int *transpose = NULL;

    transpose = MatrixAlloc(matrixOrd);
    for (unsigned int i = 0; i < matrixOrd; i++)
    {
        for (unsigned int j = 0; j < matrixOrd; j++)
        {
            transpose[(i * (matrixOrd)) + j] = matriz_B[(j * (matrixOrd)) + i];
        }
    }

    if (nThreads == 1)
    {
        parameters = vectorParameterAlloc(1);
        parameters[i].start_Pos = 0;
        parameters[i].end_Pos = matrixOrd;
        parameters[i].matrix_Ord = matrixOrd;
        parameters[i].n_Threads = nThreads;
        parameters[i].matrix_1 = matriz_A;
        parameters[i].matrix_3 = matriz_C;
        parameters[i].matrix_2 = transpose;

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        thrdP_Mult((void *)&parameters[i]);

        clock_gettime(CLOCK_MONOTONIC, &timeEnd);
    }

    else
    {
        pthread_t *idsThread;
        parameters = vectorParameterAlloc(nThreads);
        idsThread = ThreadIDAlloc(nThreads);

        clock_gettime(CLOCK_MONOTONIC, &timeStart);

        for (i = 0; i < nThreads; i++)
        {
            parameters[i].start_Pos = i;
            parameters[i].end_Pos = (matrixOrd + 1) - (nThreads - i);
            parameters[i].matrix_Ord = matrixOrd;
            parameters[i].n_Threads = nThreads;
            parameters[i].matrix_1 = matriz_A;
            parameters[i].matrix_3 = matriz_C;
            parameters[i].matrix_2 = transpose;

            err = pthread_create(&idsThread[i],
                                 NULL,
                                 thrdP_Mult,
                                 (void *)&parameters[i]);

            if (err != 0)
            {
                errorSign('a');
            }
        }

        for (i = 0; i < nThreads; i++)
        {
            err = pthread_join(idsThread[i], NULL);

            if (err != 0)
            {
                errorSign('b');
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
 * @param matrix_Ord A ordem da matriz.
 * @param n_Threads Número de threads.
 * @param matrix Ponteiro para o endereço da matriz.
 */
void *thrdP_Sum(void *args)
{
    unsigned int start;
    unsigned int end;
    unsigned int matrixOrd;
    unsigned int nThreads;
    unsigned int line;
    unsigned int column;
    long int *matriz_A;
    long int *matriz_B;
    long int *matriz_C;

    start = ((ThreadParameters *)args)->start_Pos;
    end = ((ThreadParameters *)args)->end_Pos;
    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    nThreads = ((ThreadParameters *)args)->n_Threads;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    matriz_B = ((ThreadParameters *)args)->matrix_2;
    matriz_C = ((ThreadParameters *)args)->matrix_3;

    for (line = start; line < end; line += nThreads)
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
 * @param n_Threads Número de threads
 * @param matrix Ponteiro para o endereço da matriz.
 */
void *thrdP_Mult(void *args)
{
    unsigned int start;
    unsigned int end;
    unsigned int matrixOrd;
    unsigned int nThreads;
    unsigned int line;
    unsigned int column;
    unsigned int k;
    long int *matriz_A;
    long int *matriz_B;
    long int *matriz_C;

    start = ((ThreadParameters *)args)->start_Pos;
    end = ((ThreadParameters *)args)->end_Pos;
    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    nThreads = ((ThreadParameters *)args)->n_Threads;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    matriz_B = ((ThreadParameters *)args)->matrix_2;
    matriz_C = ((ThreadParameters *)args)->matrix_3;

    for (line = start; line < end; line += nThreads)
    {
        for (column = 0; column < matrixOrd; ++column)
        {
            for (k = 0; k < (matrixOrd); ++k)
            {
                matriz_C[position(line, column, numColumns)] += (matriz_A[(line * (matrixOrd)) + k]) * (matriz_B[(line * (matrixOrd)) + k]);
            }
        }
    }

    return NULL;
}

/**
 * Função (thread) que lê um arquivo.dat e atribui os valores à uma matriz
 * @param args Argumentos passados a thread. Esses argumentos sao:
 * @param matrix_Ord A ordem da matriz.
 * @param matrix Ponteiro para o endereço da matriz.
 * @param file_Dat Ponteiro para o endereço do arquivo.dat.
 */
void *thrdReading(void *args)
{
    unsigned int matrixOrd;
    unsigned int line;
    unsigned int column;
    long int *matriz_A;

    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    FILE *fileDat = fopen((((ThreadParameters *)args)->file_Dat), "r");
    if (fileDat == NULL)
    {
        errorSign('h');
    }

    for (line = 0; line < matrixOrd; line++)
    {
        for (column = 0; column < matrixOrd; column++)
        {
            if (!fscanf(fileDat, "%ld", &matriz_A[position(line, column, numColumns)]))
            {
                fclose(fileDat);
                errorSign('i');
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
 */
void *thrdWriting(void *args)
{
    unsigned int matrixOrd;
    unsigned int line;
    unsigned int column;
    long int *matriz_A;

    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    matriz_A = ((ThreadParameters *)args)->matrix_1;
    FILE *fileDat = fopen((((ThreadParameters *)args)->file_Dat), "r+");
    if (fileDat == NULL)
    {
        errorSign('h');
    }

    for (line = 0; line < (matrixOrd); ++line)
    {
        for (column = 0; column < (matrixOrd); ++column)
        {
            if (!fprintf(fileDat, "%ld ", matriz_A[position(line, column, numColumns)]))
            {
                errorSign('j');
            };
        }

        fseek(fileDat, -1, SEEK_CUR);
        if ((fputc('\n', fileDat)) == EOF)
        {
            errorSign('j');
        }
    }
    fclose(fileDat);
    return NULL;
}

/**
 * Função (thread) para escrever matrizes em arquivo.dat.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 * @param start_Pos Posicao inicial do vetor.
 * @param end_Pos A posicao final do vetor.
 * @param matrix_Ord A ordem da matriz.
 * @param n_Threads Número de threads
 * @param matrix Ponteiro para o endereço da matriz.
 * @param partial_Result Ponteiro para endereço do resultado parcial da redução por soma
 */
void *thrdP_Reduce(void *args)
{
    unsigned int start;
    unsigned int end;
    unsigned int matrixOrd;
    unsigned int nThreads;
    unsigned int line;
    unsigned int column;
    long int *matriz_A;
    long int redPorSoma = 0;

    start = ((ThreadParameters *)args)->start_Pos;
    end = ((ThreadParameters *)args)->end_Pos;
    matrixOrd = ((ThreadParameters *)args)->matrix_Ord;
    nThreads = ((ThreadParameters *)args)->n_Threads;
    matriz_A = ((ThreadParameters *)args)->matrix_1;

    for (line = start; line < end; line += nThreads)
    {
        for (column = 0; column < matrixOrd; ++column)
        {
            redPorSoma += matriz_A[(line) * (matrixOrd) + (column)];
        }
    }

    *((ThreadParameters *)args)->partial_Result += redPorSoma;

    return NULL;
}
