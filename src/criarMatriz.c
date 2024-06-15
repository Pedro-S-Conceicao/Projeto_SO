#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *arquivo = fopen(argv[2], "r+");
    int *linha = (int *)malloc(sizeof(int));
    int *coluna = (int *)malloc(sizeof(int));
    if ((linha == NULL) || (coluna == NULL))
    {
        printf("Memória insuficiente!!!\n");
        exit(EXIT_FAILURE);
    }
     printf("%d\n", atoi(argv[1]));
    for (*linha = 0; *linha <= (atoi(argv[1])); ++*linha)
    {
        for (*coluna = 0; *coluna < (atoi(argv[1])); ++*coluna)
        {
            fprintf(arquivo, "2 ");
        }

        fseek(arquivo, -1, SEEK_CUR);
        fputc('\n', arquivo);
    }
    atoi(argv[1]);
    free(linha);
    free(coluna);
    fclose(arquivo);
}
