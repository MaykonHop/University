#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000000

long count = 0;
pthread_mutex_t mutex;  // Declaração do mutex

void * ThreadAdd(void * a)
{
    int i;
    long tmp;
    for(i = 0; i < NITER; i++)
    {
        pthread_mutex_lock(&mutex);  // Bloqueia o mutex
        
        tmp = count;      /* copy the global count locally */
        tmp = tmp+1;      /* increment the local copy */
        count = tmp;      /* store the local value into the global count */
        
        pthread_mutex_unlock(&mutex);  // Libera o mutex
    }
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;

    // Inicializa o mutex
    if (pthread_mutex_init(&mutex, NULL)) {
        printf("\n ERROR initializing mutex");
        exit(1);
    }

    if(pthread_create(&tid1, NULL, ThreadAdd, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, ThreadAdd, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    // Destroi o mutex
    pthread_mutex_destroy(&mutex);

    if (count < 2 * NITER) 
        printf("\n BOOM! count is [%ld], should be %ld\n", count, (long)2*NITER);
    else
        printf("\n OK! count is [%ld]\n", count);
  
    pthread_exit(NULL);
}