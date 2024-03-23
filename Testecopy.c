#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ordemMatriz (atoi(argv[1]))
#define posicao(linha, colunas, numColunas) ((*linha) * ((ordMatriz)) + (*coluna))
#define arquivouivoA (argv[2])
#define arquivouivoB (argv[3])
#define arquivouivoC (argv[4])
#define arquivouivoD (argv[5])
#define arquivouivoE (argv[6])

void preencherMatriz(int ordMatriz, int *matriz, char *arqDat);

float somarMatriz(int ordMatriz, int *matrizA, int *matrizB, int *matrizD);

void escreverMatriz(int ordMatriz, int *matriz, char *arqDat);

float multiplicarMatriz(int ordMatriz, int *matrizC, int *matrizD, int *matrizE);

float reduzirMatriz(int ordMatriz, int *matrizE);

int main(int argc, char *argv[])
{
    clock_t *inicio = (clock_t *)malloc(sizeof(clock_t));
    clock_t *fim = (clock_t *)malloc(sizeof(clock_t));
    double *tempoTotal = (double *)malloc(sizeof(double));
    *inicio = clock();

    float *tempoSoma = (float *)malloc(sizeof(float));
    float *tempoMultiplicar = (float *)malloc(sizeof(float));
    float *tempoReduzir = (float *)malloc(sizeof(float));
    if ((inicio == NULL )||(fim == NULL )||(tempoTotal == NULL )||(tempoSoma == NULL) || (tempoMultiplicar == NULL) || (tempoReduzir == NULL))
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

    preencherMatriz((ordemMatriz), matrizA, arquivouivoA);

    preencherMatriz((ordemMatriz), matrizB, arquivouivoB);

    *tempoSoma = somarMatriz((ordemMatriz), matrizA, matrizB, matrizD);

    free(matrizA);
    free(matrizB);

    escreverMatriz((ordemMatriz), matrizD, arquivouivoD);

    preencherMatriz((ordemMatriz), matrizC, arquivouivoC);

    *tempoMultiplicar = multiplicarMatriz((ordemMatriz), matrizC, matrizD, matrizE);

    free(matrizC);
    free(matrizD);

    escreverMatriz((ordemMatriz), matrizE, arquivouivoE);

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

float somarMatriz(int ordMatriz, int *matrizA, int *matrizB, int *matrizD)
{
    clock_t *inicio = (clock_t *)malloc(sizeof(clock_t));
    clock_t *fim = (clock_t *)malloc(sizeof(clock_t));
    if ((inicio == NULL )||(fim == NULL ))
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

float multiplicarMatriz(int ordMatriz, int *matrizC, int *matrizD, int *matrizE)
{
    clock_t *inicio = (clock_t *)malloc(sizeof(clock_t));
    clock_t *fim = (clock_t *)malloc(sizeof(clock_t));
    if ((inicio == NULL )||(fim == NULL ))
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
    return tempoTotal;

    free(inicio);
    free(fim);
}

float reduzirMatriz(int ordMatriz, int *matrizE)
{
    clock_t *inicio = (clock_t *)malloc(sizeof(clock_t));
    clock_t *fim = (clock_t *)malloc(sizeof(clock_t));
    if ((inicio == NULL )||(fim == NULL ))
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
