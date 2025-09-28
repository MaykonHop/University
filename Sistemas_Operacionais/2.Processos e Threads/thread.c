#include <pthread.h> // posix thread
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 4
#define TAM 500000000

//contenção de cash ou contenção de memória

typedef struct {
    int *vetor; // O ponteiro para os dados
    int inicial;  // O índice de início
    int final;    // O índice de fim
    long long int *resultado;
} Thread;

void* soma(void* arg){
    //casting para Thread
    Thread *argumentos  = (Thread *)arg;
    argumentos 
    int ini = argumentos -> inicial;
    int fim = argumentos -> final;
    int *v = argumentos->vetor;
    long long int soma = 0;

    for(int i = ini; i <= fim; i++){
        soma += v[i];
    }
    *(argumentos->resultado) = soma;
    return NULL
}

// lógica para dividir o vetor 
for(int i = 0 ; i < NUM_THREADS; i++){

    int bloco = TAM/NUM_THREADS;
    int inicial = bloco *i;
    int final = bloco * (i+1) - 1

    if (i ==NUM_THREADS -1 ){
        final = TAM - 1;
    }
    // operação com thread

    //-----

}