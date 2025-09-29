// gcc exemplo.c -o exemplo -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

void *print_hello (void *threadid){

    printf("%ld: Hello World\n", (long) threadid);
    sleep(5);
    printf("%ld: Bye bye World!\n", (long) threadid);
    pthread_exit(NULL);
}

int main(int arc, char *argv[]){
    pthread_t thread[NUM_THREADS];
    long status, i;
    for (i=0; i<NUM_THREADS; i++){
        printf("Creating thread %ld\n", i);
        status = pthread_create(&thread[i], NULL, print_hello, (void *)i);
        if(status){
            perror("pthread_create\n");
            exit(-1);
        }
    }
    pthread_exit(NULL);
}