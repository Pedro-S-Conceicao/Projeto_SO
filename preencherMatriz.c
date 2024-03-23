#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define posicao(linha, colunas, numColunas) ((*linha) * ((ordMatriz)) + (*coluna))

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
