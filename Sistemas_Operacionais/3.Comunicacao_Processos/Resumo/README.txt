Implementação de um programa multiprocesso que utiliza *pipe*para comunicação entre processos para buscar um valor em um vetor ordenado.

O programa funciona da seguinte forma:

    -cria um pipe para comunicação entre o processo pai e filho

    -o processo pai realiza uma busca simples(n consegui implementar busca binaria) no vetor ordenado

    -O resultado da busca (*posição* ou *-1*) é enviado através do pipe

    -O processo filho recebe o resultado e imprime na tela
