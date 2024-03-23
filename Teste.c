#include <stdio.h>
#include <stdlib.h>

#define ordemMatriz (*argv[1])
#define posicao(i, j, numColunas) ((*i) * ((ordMatriz - 48)) + (*j))
#define arquivouivoA (argv[2])
#define arquivouivoB (argv[3])
#define arquivouivoC (argv[4])
#define arquivouivoD (argv[5])
#define arquivouivoE (argv[6])

void somarMatriz(int ordMatriz, int *matrizA, int *matrizB, int *matrizD, FILE *arquivo);

void preencherMatriz(int ordMatriz, int *matriz, FILE *arquivo);

void multiplicarMatriz(int ordMatriz, int *matrizC, int *matrizD, int *matrizE, FILE *arquivo);

void reduzirMatriz(int ordMatriz, int *matrizE);

int main(int argc, char *argv[])
{
    int *matrizA = (int *)malloc((ordemMatriz - 48) * (ordemMatriz - 48) * sizeof(int));
    int *matrizB = (int *)malloc((ordemMatriz - 48) * (ordemMatriz - 48) * sizeof(int));
    int *matrizD = (int *)malloc((ordemMatriz - 48) * (ordemMatriz - 48) * sizeof(int));
    if ((matrizA == NULL) || (matrizB == NULL) || (matrizD == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    FILE *arquivo = fopen(arquivouivoA, "r");
    preencherMatriz(ordemMatriz, matrizA, arquivo);
    fclose(arquivo);

    arquivo = fopen(arquivouivoB, "r");
    preencherMatriz(ordemMatriz, matrizB, arquivo);
    fclose(arquivo);

    arquivo = fopen(arquivouivoD, "r+");
    somarMatriz(ordemMatriz, matrizA, matrizB, matrizD, arquivo);
    fclose(arquivo);

    free(matrizA);
    free(matrizB);

    int *matrizC = (int *)malloc((ordemMatriz - 48) * (ordemMatriz - 48) * sizeof(int));
    int *matrizE = (int *)malloc((ordemMatriz - 48) * (ordemMatriz - 48) * sizeof(int));
    if ((matrizC == NULL) || (matrizE == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    arquivo = fopen(arquivouivoC, "r");
    preencherMatriz(ordemMatriz, matrizC, arquivo);
    fclose(arquivo);

    arquivo = fopen(arquivouivoE, "r+");
    multiplicarMatriz(ordemMatriz, matrizC, matrizD, matrizE, arquivo);
    fclose(arquivo);

    free(matrizC);
    free(matrizD);

    reduzirMatriz(ordemMatriz, matrizE);

    free(matrizE);

    return 0;
}

void preencherMatriz(int ordMatriz, int *matriz, FILE *arquivo)
{
    int *i = (int *)malloc(sizeof(int));
    int *j = (int *)malloc(sizeof(int));
    if ((i == NULL) || (j == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    for (*i = 0; *i < (ordMatriz - 48); ++*i)
    {
        char *aux = (char *)malloc(sizeof(char));
        if ((aux == NULL))
        {
            printf("Memória insuficiente!!!\n");
            exit(EXIT_FAILURE);
        }

        for (*j = 0; *j < (ordMatriz - 48); ++*j)
        {
            *aux = fgetc(arquivo);
            matriz[posicao(i, j, numColunas)] = (*aux - 48);

            if ((*aux == ' ') || (*aux == '\n'))
                --*j;
        }
        free(aux);
    }

    free(i);
    free(j);
}

void somarMatriz(int ordMatriz, int *matrizA, int *matrizB, int *matrizD, FILE *arquivo)
{
    int *i = (int *)malloc(sizeof(int));
    int *j = (int *)malloc(sizeof(int));
    if ((i == NULL) || (j == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    for (*i = 0; *i < (ordMatriz - 48); ++*i)
    {
        for (*j = 0; *j < (ordMatriz - 48); ++*j)
        {

            matrizD[posicao(i, j, numColunas)] = matrizA[posicao(i, j, numColunas)] + matrizB[posicao(i, j, numColunas)];
            fprintf(arquivo, "%d ", matrizD[posicao(i, j, numColunas)]);
        }

        fseek(arquivo, -1, SEEK_CUR);
        fputc('\n', arquivo);
    }
 
    free(i);
    free(j);
}

void multiplicarMatriz(int ordMatriz, int *matrizC, int *matrizD, int *matrizE, FILE *arquivo)
{
    int *i = (int *)malloc(sizeof(int));
    int *j = (int *)malloc(sizeof(int));
    int *k = (int *)malloc(sizeof(int));
    int *somaProduto = (int *)malloc(sizeof(int));

    if ((i == NULL) || (j == NULL) || (somaProduto == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    for (*i = 0; *i < (ordMatriz - 48); ++*i)
    {
        for (*j = 0; *j < (ordMatriz - 48); ++*j)
        {
            *somaProduto = 0;
            for (*k = 0; *k < (ordMatriz - 48); ++*k)
            {
                *somaProduto += (matrizC[(*i * (ordMatriz - 48)) + *k]) * (matrizD[(*k * (ordMatriz - 48)) + *j]);
            }

            matrizE[posicao(i, j, numColunas)] = *somaProduto;
            fprintf(arquivo, "%d ", matrizE[posicao(i, j, numColunas)]);
        }

        fseek(arquivo, -1, SEEK_CUR);
        fputc('\n', arquivo);
    }

    free(i);
    free(j);
    free(k);
    free(somaProduto);
}

void reduzirMatriz(int ordMatriz, int *matrizE)
{
    int *i = (int *)malloc(sizeof(int));
    int *j = (int *)malloc(sizeof(int));
    int *redPorSoma = (int *)malloc(sizeof(int));
    if ((i == NULL) || (j == NULL) || (redPorSoma == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }

    *redPorSoma = 0;
    for (*i = 0; *i < (ordMatriz - 48); ++*i)
    {
        for (*j = 0; *j < (ordMatriz - 48); ++*j)
        {
            *redPorSoma += matrizE[(*i) * (ordMatriz - 48) + (*j)];
        }
    }
    printf("Redução: %d\n", *redPorSoma);
    free(i);
    free(j);
    free(redPorSoma);
}