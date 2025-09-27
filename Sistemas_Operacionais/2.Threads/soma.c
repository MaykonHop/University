#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 500000000

int vector[TAM];

int main() {
    long long total = 0;

    srand(time(NULL));
    
    for (long i = 0; i < TAM; i++) {
        vector[i] = rand() % 10;
    }
    for (long i = 0; i < TAM; i++) {
        total += vector[i];
    }

    printf("Soma total: %lld\n", total);

 
    return 0;
}