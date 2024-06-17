# Projeto de Sistemas Operacionais

## Descrição
Este projeto tem como objetivo consolidar conhecimentos sobre programação multi-thread em C, realizando operações com matrizes de números inteiros. O programa desenvolvido em ambiente Linux executa operações de soma e multiplicação de matrizes, seguidas pela redução da matriz resultante.

## Compilação e Execução
Antes de compilar o programa, primeiro deve-se criar a pasta bin e build à partir do seguinte comando:
```
make criarDir
```
Para compilar o programa, gerando um executável projetoSO.exe no diretório bin/, utilize o comando no terminal na pasta Projeto_S:
``` 
make compilar
```
## Testes
O Makefile inclui comandos para realizar testes com diferentes números de threads e ordens de matrizes. Lembrando que todos os comandos make devem ser exetutados no diretório Projeto_SO, pois é onde está presente o Makefile:

- ``` make teste01 ``` : Executa o programa com 1 thread e matrizes de ordem 100.
* **make teste02** : Executa o programa com 2 threads e matrizes de ordem 100.
+ **make teste03** : Executa o programa com 4 threads e matrizes de ordem 100.
- **make teste04** : Executa o programa com 1 thread e matrizes de ordem 1000.
* **make teste05** : Executa o programa com 2 threads e matrizes de ordem 1000.
+ **make teste06** : Executa o programa com 4 threads e matrizes de ordem 1000.
Para limpar os arquivos objeto e executáveis gerados, use o comando 
```
make clean
```

## Entradas e Saídas
Os arquivos das matrizes A, B, C, D e E devem estar disponíveis no diretório data/ e devem seguir o formato texto em linha/coluna de uma matriz, assim como no exemplo abaixo:
```
1 1 1
1 1 1
1 1 1
```

O nome dos arquivos devem seguir o padrão: arqA.dat, arqB.dat... Além disso devem estar no diretório Projeto_SO/data/

Após a execução, o programa exibirá na tela o valor reduzido da matriz E e os tempos gastos em cada operação, além do tempo total de processamento.