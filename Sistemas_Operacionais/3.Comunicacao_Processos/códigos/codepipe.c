// Arquivo: busca_simples.c
// Para compilar: cc -Wall busca_simples.c -o busca_simples -lrt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    int fd[2]; // fd[0] para leitura, fd[1] para escrita

    if (pipe(fd) == -1) {
        perror("deu ruim no pipe"); // Se falhar
        return 1;
    }
    
    int vetor[] = {2, 5, 8, 12, 16, 23, 38, 45, 50, 55};
    int tam = 10;
    int valor = 16;
    
      
    int id = fork();
    if (id == -1) {
        perror("deu ruim"); // Se falhar
        return 1;
    }
    
    if (id == 0) { // PROCESSO FILHO
        close(fd[1]); // Fecha lado de escrita 
        
        int resultado;
        read(fd[0], &resultado, sizeof(resultado)); // Lê resultado do pipe
        
        if (resultado == -1) {
            printf("nao achou\n");
        } else {
            printf("posicao: %d\n", resultado);
        }
        
        close(fd[0]); // Fecha lado de leitura
    } 
    else { // PROCESSO PAI
        close(fd[0]); // Fecha lado de leitura
        
        int posicao = -1;
        
        // Busca simples 
        for (int i = 0; i < tam; i++) {
            if (vetor[i] == valor) {
                posicao = i;
                break;
            }
        }
        
        write(fd[1], &posicao, sizeof(posicao)); // Envia resultado pelo pipe
        close(fd[1]); // Fecha lado de escrita
        
        wait(NULL); // Espera processo filho terminar
    }
    
    return 0;
}