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
 * @throw 'h'
 * @throw 'i'
 * @throw 'j'
 * @throw 'k'
 * @throw 'l'
 * @throw 'm'
 * @throw 'n'
 * @throw 'o'
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
        /* code */
        break;
    case 'i':
        /* code */
        break;
    case 'j':
        /* code */
        break;

    default:
        break;
    }
};
