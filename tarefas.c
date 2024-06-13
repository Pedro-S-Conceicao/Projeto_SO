#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "tarefas.h"

#define posicao(linha, colunas, numColunas) ((linha) * ((ordMatriz)) + (coluna))

parametrosThread *alocaVetorParametrosThreads(unsigned int nThreads)
{
    parametrosThread *vetor;

    if ((vetor = (parametrosThread *)malloc(sizeof(parametrosThread) * nThreads)) == NULL)
    {
        fprintf(stderr, "Problemas na alocacao do vetor\n");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

/**
 * Função para alocar dinâmicamente um vetor de identificadores de threads.
 * @param tamanho Número de posicoes do vetor.
 * @return Vetor alocado.
 */
pthread_t *alocaIdsThreads(unsigned int tamanho)
{
    pthread_t *vetor;

    if (tamanho <= 0)
        return NULL;

    if ((vetor = (pthread_t *)malloc(sizeof(pthread_t) * tamanho)) == NULL)
    {
        fprintf(stderr, "Problemas na alocacao do vetor\n");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

/**
 * Funcao para alocar dinamicamente uma variável do tipo float.
 * @return Variável alocado.
 */
double *alocaVariavel()
{
    double *variavel;

    if ((variavel = (double *)malloc(sizeof(double))) == NULL)
    {
        fprintf(stderr, "Problemas na alocacao da variável\n");
        exit(EXIT_FAILURE);
    }

    return variavel;
}

/**
 * Funcao para alocar dinamicamente um vetor de inteiros.
 * @param ordMatriz Numero de posicoes do vetor.
 * @return Vetor alocado.
 */
int *alocaVetor(int ordMatriz)
{
    int *vetor;

    if ((vetor = (int *)malloc((ordMatriz) * (ordMatriz) * sizeof(int))) == NULL)
    {
        fprintf(stderr, "Problemas na alocacao do vetor\n");
        exit(EXIT_FAILURE);
    }

    return vetor;
}

/**
 * Funcao para escrever a matriz em arquivo.dat.
 * @param ordMatriz Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 *
 */
void lerEGravarMatriz(int ordMatriz, int *matriz_A, int *matriz_B, char *arqDat_A, char *arqDat_B, unsigned int nThreads)
{
    parametrosThread *parametros;
    unsigned int i;
    int err;

    if (nThreads == 1)
    {
        parametros = alocaVetorParametrosThreads(2);

        i = 0;
        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matriz_A;
        parametros[i].arquivo = arqDat_A;

        thrdLerEPeencherMatriz((void *)&parametros[i]);

        i = 1;
        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matriz_B;
        parametros[i].arquivo = arqDat_B;

        thrdGravarMatriz((void *)&parametros[i]);
    }

    else
    {
        pthread_t *idsThread;
        parametros = alocaVetorParametrosThreads(2);
        idsThread = alocaIdsThreads(2);

        for (i = 0; i < 2; i++)
        {
            if (i == 0)
            {
                parametros[i].ord_Matriz = ordMatriz;
                parametros[i].matriz_1 = matriz_A;
                parametros[i].arquivo = arqDat_A;

                /* Criação de um thread passando os parâmetros específicos
                 * na estrutura informada em parâmetros[i].
                 */
                err = pthread_create(&idsThread[i],
                                     NULL,
                                     thrdLerEPeencherMatriz,
                                     (void *)&parametros[i]);
            }
            else
            {
                parametros[i].ord_Matriz = ordMatriz;
                parametros[i].matriz_1 = matriz_B;
                parametros[i].arquivo = arqDat_B;

                /* Criação de um thread passando os parâmetros específicos
                 * na estrutura informada em parâmetros[i].
                 */
                err = pthread_create(&idsThread[i],
                                     NULL,
                                     thrdGravarMatriz,
                                     (void *)&parametros[i]);
            }

            if (err != 0)
            {
                fprintf(stderr, "Erro na criacao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        for (i = 0; i < 2; i++)
        {
            /* Junção dos threads com o retorno de cada thread
             * armazenado na variável soma parcial.
             */
            err = pthread_join(idsThread[i], NULL);

            if (err != 0)
            {
                fprintf(stderr, "Erro na juncao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * Funcao para ler o arquivo.dat, que possui os dados da matriz, e atribuí-los a uma matriz.
 * @param ordMatriz Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 */
void lerEPreencherMatriz(int ordMatriz, int *matriz_A, int *matriz_B, char *arqDat_A, char *arqDat_B, unsigned int nThreads)
{
    parametrosThread *parametros;
    unsigned int i;
    int err;

    if (nThreads == 1)
    {
        parametros = alocaVetorParametrosThreads(2);

        i = 0;
        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matriz_A;
        parametros[i].arquivo = arqDat_A;

        thrdLerEPeencherMatriz((void *)&parametros[i]);

        i = 1;
        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matriz_B;
        parametros[i].arquivo = arqDat_B;

        thrdLerEPeencherMatriz((void *)&parametros[i]);
    }

    else
    {
        pthread_t *idsThread;
        parametros = alocaVetorParametrosThreads(2);
        idsThread = alocaIdsThreads(2);

        for (i = 0; i < 2; i++)
        {
            if (i == 0)
            {
                parametros[i].ord_Matriz = ordMatriz;
                parametros[i].matriz_1 = matriz_A;
                parametros[i].arquivo = arqDat_A;
            }
            else
            {
                parametros[i].ord_Matriz = ordMatriz;
                parametros[i].matriz_1 = matriz_B;
                parametros[i].arquivo = arqDat_B;
            }

            /* Criação de um thread passando os parâmetros específicos
             * na estrutura informada em parâmetros[i].
             */
            err = pthread_create(&idsThread[i],
                                 NULL,
                                 thrdLerEPeencherMatriz,
                                 (void *)&parametros[i]);

            if (err != 0)
            {
                fprintf(stderr, "Erro na criacao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        for (i = 0; i < 2; i++)
        {
            /* Junção dos threads com o retorno de cada thread
             * armazenado na variável soma parcial.
             */
            err = pthread_join(idsThread[i], NULL);

            if (err != 0)
            {
                fprintf(stderr, "Erro na juncao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * Funcao para reduzir os valores da matriz em um valor do tipo float.
 * @param ordMatriz Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 */
float reduzirEGravarMatriz(int ordMatriz, int *matrizE, char *arqDat_E, unsigned int nThreads)
{
    parametrosThread *parametros;
    unsigned int i = 0;
    int err;
    int redPorSomaParcial;
    clock_t inicio;
    clock_t fim;
    double tempoTotal;

    inicio = clock();

    redPorSomaParcial = 0;

    if (nThreads == 4)
    {
        pthread_t *idsThread;

        parametros = alocaVetorParametrosThreads(4);
        idsThread = alocaIdsThreads(4);

        unsigned int elementosPorThread = (unsigned int)ordMatriz / (nThreads - 1);

        for (i = 0; i < 3; i++)
        {
            parametros[i].posInicio = i * elementosPorThread;
            parametros[i].posFinal = (i == nThreads - 2) ? (unsigned int)ordMatriz : (i + 1) * elementosPorThread;
            parametros[i].ord_Matriz = ordMatriz;
            parametros[i].matriz_1 = matrizE;
            parametros[i].resultadoParcial = &redPorSomaParcial;

            err = pthread_create(&idsThread[i],
                                 NULL,
                                 thrdReduzirMatriz,
                                 &parametros[i]);
            if (err != 0)
            {
                fprintf(stderr, "Erro na criacao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matrizE;
        parametros[i].arquivo = arqDat_E;

        err = pthread_create(&idsThread[i],
                             NULL,
                             thrdGravarMatriz,
                             (void *)&parametros[i]);
        if (err != 0)
        {
            fprintf(stderr, "Erro na criacao do thread %d\n", i);
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < 4; i++)
        {
            pthread_join(idsThread[i], NULL);
            if (err != 0)
            {
                fprintf(stderr, "Erro na juncao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
    }

    else
    {
        parametros = alocaVetorParametrosThreads(2);
        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matrizE;
        parametros[i].arquivo = arqDat_E;

        thrdGravarMatriz((void *)&parametros[i]);

        i = 1;
        parametros[i].posInicio = 0;
        parametros[i].posFinal = ordMatriz;
        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matrizE;
        parametros[i].resultadoParcial = &redPorSomaParcial;

        thrdReduzirMatriz((void *)&parametros[i]);
    }

    int redPorSoma = redPorSomaParcial;

    printf("Redução: %d\n", redPorSoma);

    fim = clock() - inicio;
    tempoTotal = ((double)fim) / CLOCKS_PER_SEC;

    return tempoTotal;
}

/**
 * Função para a tarefa de somar a matrizA com a matrizB gravando na matrizD e  a tarefa de multiplicar a matrizC pela matrizD gravando na matrizE.
 * @param ordMatriz Ordem da Matriz.
 * @param nThreads Número de threads usadas para as tarefas
 * @param matriz_(A/B/C) Ponteiro para o endereço da matriz A,B e D, respectivamente.
 * @param tarefa Indicação da tarefa a ser realizada ('a' para soma e 'b' para multiplicação)
 */
float tarefasSomarEMultiMatriz(unsigned int ordMatriz, unsigned int nThreads, int *matriz_A, int *matriz_B, int *matriz_C, char tarefa)
{
    clock_t inicio;
    clock_t fim;
    double tempoTotal;
    parametrosThread *parametros;
    unsigned int i = 0, quantElementos;
    int err;

    inicio = clock();

    if (nThreads == 1)
    {
        parametros = alocaVetorParametrosThreads(1);
        parametros[i].posInicio = 0;
        parametros[i].posFinal = ordMatriz;
        parametros[i].ord_Matriz = ordMatriz;
        parametros[i].matriz_1 = matriz_A;
        parametros[i].matriz_2 = matriz_B;
        parametros[i].matriz_3 = matriz_C;

        if (tarefa == 'a')
        {
            thrdSomarMatriz((void *)&parametros[i]);
        }
        else
        {
            thrdMultiplicarMatriz((void *)&parametros[i]);
        }
    }

    else
    {
        pthread_t *idsThread;
        parametros = alocaVetorParametrosThreads(nThreads);
        idsThread = alocaIdsThreads(nThreads);
        quantElementos = ordMatriz / nThreads;
        for (i = 0; i < nThreads; i++)
        {
            parametros[i].posInicio = quantElementos * i;
            parametros[i].posFinal = (quantElementos * (i + 1));
            parametros[i].ord_Matriz = ordMatriz;
            parametros[i].matriz_1 = matriz_A;
            parametros[i].matriz_2 = matriz_B;
            parametros[i].matriz_3 = matriz_C;

            /* Criação de um thread passando os parâmetros específicos
             * na estrutura informada em parâmetros[i].
             */
            if (tarefa == 'a')
            {
                err = pthread_create(&idsThread[i],
                                     NULL,
                                     thrdSomarMatriz,
                                     (void *)&parametros[i]);
            }

            else
            {
                err = pthread_create(&idsThread[i],
                                     NULL,
                                     thrdMultiplicarMatriz,
                                     (void *)&parametros[i]);
            }

            if (err != 0)
            {
                fprintf(stderr, "Erro na criacao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }

        for (i = 0; i < nThreads; i++)
        {
            /* Junção dos threads com o retorno de cada thread
             * armazenado na variável soma parcial.
             */
            err = pthread_join(idsThread[i], NULL);

            if (err != 0)
            {
                fprintf(stderr, "Erro na juncao do thread %d\n", i);
                exit(EXIT_FAILURE);
            }
        }
    }

    fim = clock() - inicio;
    tempoTotal = ((double)fim) / CLOCKS_PER_SEC;

    return tempoTotal;
}

/**
 * Funcao (thread) que calcula a soma de uma quantidade de elementos
 * informada como parametro.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 *             - A posicao inicial do vetor.
 *             - A posicao final do vetor.
 *             - A ordem da matriz
 *             - As matrizes 1,2 e 3
 * @return Soma dos elementos
 */
void *thrdSomarMatriz(void *args)
{
    register unsigned int inicio, final, ordMatriz;

    unsigned int linha, coluna;

    int *matriz_A, *matriz_B, *matriz_C;

    // Extracao dos parametros da estrutura args.
    inicio = ((parametrosThread *)args)->posInicio;
    final = ((parametrosThread *)args)->posFinal;
    ordMatriz = ((parametrosThread *)args)->ord_Matriz;
    matriz_A = ((parametrosThread *)args)->matriz_1;
    matriz_B = ((parametrosThread *)args)->matriz_2;
    matriz_C = ((parametrosThread *)args)->matriz_3;

    for (linha = inicio; linha < final; ++linha)
    {
        for (coluna = 0; coluna < ordMatriz; ++coluna)
        {

            matriz_C[posicao(linha, coluna, numColunas)] = matriz_A[posicao(linha, coluna, numColunas)] + matriz_B[posicao(linha, coluna, numColunas)];
        }
    }
    return NULL;
}

/**
 * Funcao (thread) que calcula a multiplicaçã de matrizes
 * informada como parametro.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 *             - A posicao inicial do vetor.
 *             - A posicao final do vetor.
 *             - A ordem da matriz
 *             - As matrizes 1,2 e 3 .
 * @return nulo
 */
void *thrdMultiplicarMatriz(void *args)
{
    register unsigned int inicio, final, ordMatriz;

    int *matriz_A, *matriz_B, *matriz_C;

    // Extracao dos parametros da estrutura args.
    inicio = ((parametrosThread *)args)->posInicio;
    final = ((parametrosThread *)args)->posFinal;
    ordMatriz = ((parametrosThread *)args)->ord_Matriz;
    matriz_A = ((parametrosThread *)args)->matriz_1;
    matriz_B = ((parametrosThread *)args)->matriz_2;
    matriz_C = ((parametrosThread *)args)->matriz_3;

    unsigned int linha, coluna, k;
    int somaProduto;

    for (linha = inicio; linha < final; ++linha)
    {
        for (coluna = 0; coluna < ordMatriz; ++coluna)
        {
            somaProduto = 0;
            for (k = 0; k < (ordMatriz); ++k)
            {
                somaProduto += (matriz_A[(linha * (ordMatriz)) + k]) * (matriz_B[(k * (ordMatriz)) + coluna]);
            }
            matriz_C[posicao(linha, coluna, numColunas)] = somaProduto;
        }
    }

    return NULL;
}

/**
 * Funcao (thread) lê um arquivo .dat e registra os dados na matriz
 * informada como parametro.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 *             - A ordem da matriz
 *             - A matriz.
 *             - O arquivo.Dat
 * @return nulo
 */
void *thrdLerEPeencherMatriz(void *args)
{
    register unsigned int ordMatriz;
    unsigned int linha, coluna;
    int *matriz_A;

    // Extracao dos parametros da estrutura args.
    ordMatriz = ((parametrosThread *)args)->ord_Matriz;
    matriz_A = ((parametrosThread *)args)->matriz_1;
    FILE *arqDat = fopen((((parametrosThread *)args)->arquivo), "r");

    char aux;

    for (linha = 0; linha < (ordMatriz); ++linha)
    {
        for (coluna = 0; coluna < (ordMatriz); ++coluna)
        {
            aux = fgetc(arqDat);
            matriz_A[posicao(linha, coluna, numColunas)] = (aux - 48);

            if ((aux == ' ') || (aux == '\n'))
                --coluna;
        }
    }

    return NULL;
}

/**
 * Funcao (thread) grava os dados de uma matriz no arquivo .dat
 * informada como parâmetro.
 * @param args Argumentos passados a thread. Esses argumentos sao:
 *             - A ordem da matriz
 *             - A matriz.
 *             - O arquivo.Dat
 * @return nulo
 */
void *thrdGravarMatriz(void *args)
{
    register unsigned int ordMatriz;
    int *matriz_A;
    unsigned int linha, coluna;

    // Extracao dos parametros da estrutura args.
    ordMatriz = ((parametrosThread *)args)->ord_Matriz;
    matriz_A = ((parametrosThread *)args)->matriz_1;
    FILE *arqDat = fopen((((parametrosThread *)args)->arquivo), "r+");

    for (linha = 0; linha < (ordMatriz); ++linha)
    {
        for (coluna = 0; coluna < (ordMatriz); ++coluna)
        {
            fprintf(arqDat, "%d ", matriz_A[posicao(linha, coluna, numColunas)]);
        }

        fseek(arqDat, -1, SEEK_CUR);
        fputc('\n', arqDat);
    }

    return NULL;
}

void *thrdReduzirMatriz(void *args)
{
    unsigned int inicio, final, ordMatriz;
    int *matriz_A;
    unsigned int linha, coluna;

    int redPorSoma = 0;

    // Extracao dos parametros da estrutura args.
    inicio = ((parametrosThread *)args)->posInicio;
    final = ((parametrosThread *)args)->posFinal;
    ordMatriz = ((parametrosThread *)args)->ord_Matriz;
    matriz_A = ((parametrosThread *)args)->matriz_1;

    for (linha = inicio; linha < final; ++linha)
    {
        for (coluna = 0; coluna < ordMatriz; ++coluna)
        {
            redPorSoma += matriz_A[(linha) * (ordMatriz) + (coluna)];
        }
    }

    *((parametrosThread *)args)->resultadoParcial += redPorSoma;

    return NULL;
}

/**
 * Funcao para ler o arquivo.dat, que possui os dados da matriz, e atribuí-los a uma matriz.
 * @param ordMatriz Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 */
// void preencherMatriz(int ordMatriz, int *matriz, char *arqDat)
// {
//     FILE *arquivo = fopen(arqDat, "r");
//     int linha = (int *)malloc(sizeof(int));
//     int coluna = (int *)malloc(sizeof(int));
//     if ((linha == NULL) || (coluna == NULL))
//     {
//         printf("Memória insuficiente!!!\n");
//         exit(EXIT_FAILURE);
//     }

//     for (linha = 0; linha < (ordMatriz); ++linha)
//     {
//         char aux = (char *)malloc(sizeof(char));
//         if (aux != 0)
//         {
//             fprintf(stderr, "Erro na alocação da variável\n");
//             exit(EXIT_FAILURE);
//         }

//         for (coluna = 0; coluna < (ordMatriz); ++coluna)
//         {
//             aux = fgetc(arquivo);
//             matriz[posicao(linha, coluna, numColunas)] = (aux - 48);

//             if ((aux == ' ') || (aux == '\n'))
//                 --coluna;
//         }

//         free(aux);
//     }

//     free(linha);
//     free(coluna);
//     fclose(arquivo);
// }

/**
 * Funcao para escrever a matriz em arquivo.dat.
 * @param ordMatriz Ordem da Matriz.
 * @param matriz Ponteiro para o endereço da matriz.
 * @param arqDat Pornteiro para o endereço do arquivo.dat.
 */
void escreverMatriz(int ordMatriz, int *matriz, char *arqDat)
{
    FILE *arquivo = fopen(arqDat, "r+");
    int linha, coluna;

    for (linha = 0; linha < (ordMatriz); ++linha)
    {
        for (coluna = 0; coluna < (ordMatriz); ++coluna)
        {
            fprintf(arquivo, "%d ", matriz[posicao(linha, coluna, numColunas)]);
        }

        fseek(arquivo, -1, SEEK_CUR);
        fputc('\n', arquivo);
    }
    fclose(arquivo);
}
