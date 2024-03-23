#include <stdio.h>
#include <time.h>
void fun()
{
    printf("A fun() iniciou. \n");
    printf("Pressione enter para parar a função. \n");
    while (1)
        if (getchar())
            break;
    printf("A função parou \n");
}
int main()
{
    clock_t inicio, fim;
    double tempoTotal;
    inicio = clock();
    fun();

    fim = clock() - inicio;
    tempoTotal = ((double)fim) / CLOCKS_PER_SEC;
    printf("A função fun() gastou %f segundos. \n", tempoTotal);
    return 0;
}