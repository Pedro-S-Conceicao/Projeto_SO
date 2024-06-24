#include <stdio.h>
#include <stdlib.h>
#include "errorSigns.h"

/**
 * Função para detecção de excessões e erros com saída de fluxo de texto e posterior encerramento do programa quando há alguma excessão ou erro
 *
 * @throw 'a' Erro na criação do thread
 * @throw 'b' Erro na junção do thread
 * @throw 'c' Número de parâmetros de entrada incorreto
 * @throw 'd' Problemas na alocação do vetor do tipo ThreadParameters
 * @throw 'e' Problemas na alocação do vetor do tipo pthread_t
 * @throw 'f' Problemas na alocação da matrix
 * @throw 'g' Argumentos na linha de comando inválidos.
 * @throw 'h' Erro ao abrir o arquivo.dat
 * @throw 'i' Erro ao ler o arquivo.dat
 * @throw 'j' Erro ao escrever no arquivo.dat
 * @throw 'k' Número de Threads inválido
 *
 */
void errorSign(char sign)
{
    switch (sign)
    {
    case 'a':
        fprintf(stderr, "Erro na criação do thread\n");
        exit(EXIT_FAILURE);
        break;
    case 'b':
        fprintf(stderr, "Erro na junção do thread\n");
        exit(EXIT_FAILURE);
        break;
    case 'c':
        fprintf(stderr, "Número de parâmetros de entrada incorreto\n");
        exit(EXIT_FAILURE);
        break;
    case 'd':
        fprintf(stderr, "Problemas na alocação do vetor do tipo ThreadParameters\n");
        exit(EXIT_FAILURE);
        break;
    case 'e':
        fprintf(stderr, "Problemas na alocação do vetor do tipo pthread_t\n");
        exit(EXIT_FAILURE);
        break;
    case 'f':
        fprintf(stderr, "Problemas na alocação da matrix\n");
        exit(EXIT_FAILURE);
        break;
    case 'g':
        exit(EXIT_FAILURE);
        break;
    case 'h':
        fprintf(stderr, "Erro ao abrir o arquivo.dat\n");
        exit(EXIT_FAILURE);
        break;
    case 'i':
        fprintf(stderr, "Erro ao ler o arquivo.dat\n");
        exit(EXIT_FAILURE);
        break;
    case 'j':
        fprintf(stderr, "Erro ao escrever no arquivo.dat\n");
        exit(EXIT_FAILURE);
        break;
    case 'k':
        fprintf(stderr, "Número de Threads inválido\n");
        exit(EXIT_FAILURE);
    default:
        fprintf(stderr, "Erro desconhecido\n");
        exit(EXIT_FAILURE);
        break;
    }
};
