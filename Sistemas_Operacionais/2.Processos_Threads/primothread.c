#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>

#define MAX_NTHR 100
#define NMAX 10000000
long n_threads=1;
int part=0;

int fastPrime(int x){
    if(x==2) return 1;
    if(x%2==0) return 0;
    for(int i=3;i<=(int)sqrt(x);i+=2){
        if(x%i==0) return(0);
    }
    return(1);
}

void* contPrimes(void *arg){
    int thread_part = part++; 
    unsigned long cont=0;
    int ehPrimo=0;
    for (unsigned long i = thread_part * (NMAX / n_threads); i < (thread_part + 1) * (NMAX / n_threads); i++) {
        ehPrimo=fastPrime(i);
        cont+=ehPrimo;
    }
    pthread_exit((void*)cont);
}

int main(int argc, char *argv[])
{
     char *ptrfim;
     pthread_t *thr;
     int rc;
     unsigned long parc, resto, total_thr, t, total=0;
     void *ret;

     /* o numero de threads e' passado na linha de comando */
     if (argc < 2) {
        fprintf(stderr, "uso: %s <num-threads>", argv[0]);
        fprintf(stderr, " (entre 1 e %u)\n", MAX_NTHR);
        exit(1);
     }

     /* valida o numero de threads */
     errno = 0;
     n_threads = strtol(argv[1], &ptrfim, 10);
     if ((errno != 0) || (ptrfim != NULL && *ptrfim != '\0') || (n_threads < 1) ||
	 (n_threads > MAX_NTHR)) {
        fprintf(stderr, "erro: numero de threads invalido\n");
        exit(1);
     }
     

     /* aloca os descritores de thread */
     thr = (pthread_t *)calloc(n_threads, sizeof(pthread_t));
     if (thr == NULL) {
        fprintf(stderr, "erro em calloc()\n");
        exit(1);
     }


     /* cria as threads */
     for (t = 0; t < n_threads; t++) {

        rc = pthread_create(&thr[t], NULL, contPrimes, NULL);
        if (rc != 0) {
	       fprintf(stderr, "erro em pthread_create()\n");
	       exit(1);
	  }
     }

     /* espera as threads terminarem e recupera o valor de retorno */
     for (t = 0; t < n_threads; t++) {
     	  pthread_join(thr[t], &ret);
	  total_thr = (unsigned long)ret;
	  total += total_thr;
     }
     printf("TOTAL: %ld\n", total);
     
     pthread_exit(NULL);
}
