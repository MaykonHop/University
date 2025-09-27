#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define N_CONTAS 10000
#define MAX_N_TRANS_P_THREAD 10000
#define MAX_NTHR 10

// aumentando o numero de transacoes e diminuindo o numero de contas o programa trava a mesma conta é acessada mais vezes
// e a thread fica esperando a liberação do semaforo
typedef struct conta_t
{
    int numero;
    float saldo;
    sem_t trava;
}conta_t;

conta_t *contas;
long n_contas;

void transferir (conta_t *contaDeb, conta_t *contaCred, float valor){
    sem_wait(&(contaDeb->trava));
    sem_wait(&(contaCred->trava));
    if(contaDeb->saldo >= valor){
        contaDeb->saldo -= valor;
        contaCred->saldo += valor;
        //printf("Transação realizada: conta %d --> conta %d Valor: R$%.2f\n",contaDeb->numero,contaCred->numero,valor);
    }
    else{
        //printf("SALDO INSUSIFICENTE PARA Transação: conta %d --> conta %d Valor: R$%.2f\n",contaDeb->numero,contaCred->numero,valor);
    }
    sem_post(&(contaDeb->trava));
    sem_post(&(contaCred->trava));
       
}

void inicializa(conta_t *conta, int id, float valor){
    sem_wait(&(conta->trava));
    conta->saldo=valor;
    conta->numero=id;
    sem_post(&(conta->trava));
}

void depositar(conta_t *conta, float valor){
    sem_wait(&(conta->trava));
    conta->saldo+=valor;
    sem_post(&(conta->trava));
}

void consultaSaldo(conta_t *conta){
    sem_wait(&(conta->trava));
    printf("Conta %d: Saldo: %.2f\n",conta->numero,conta->saldo);
    sem_post(&(conta->trava));
}

void *auxThread(void *arg){
    int origem,destino;
    long n_trans=(long)arg;
    float valor;
    for (int i=0;i<n_trans;i++){
        origem=random()%n_contas;
        destino=random()%n_contas;
        while(destino==origem){
            destino=random()%n_contas;
        }
        valor=1.0*(random()%10);
        transferir(&contas[origem],&contas[destino],valor);
    }
}

int main(int argc, char * argv[])
{
    pthread_t *thr;
    srand(time(NULL));
    char *ptrfim;
    int i,t,rc;
    long n_threads,n_trans;
    
    /* o numero de threads e' passado na linha de comando */
    if (argc < 4) {
        fprintf(stderr, "uso: %s <num-threads> <n-trans> <num-contas>", argv[0]);
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

    n_trans = strtol(argv[2], &ptrfim, 10);
    printf("Transações por Thread: %ld\n",n_trans);
    if ((errno != 0) || (ptrfim != NULL && *ptrfim != '\0') || (n_trans < 1) ||
	(n_trans > MAX_N_TRANS_P_THREAD)) {
        fprintf(stderr, "erro: numero de transacoes invalido\n");
        exit(1);
    }

    n_contas = strtol(argv[3], &ptrfim, 10);
    printf("Contas: %ld\n",n_contas);
    if ((errno != 0) || (ptrfim != NULL && *ptrfim != '\0') || (n_contas < 1) ||
	(n_contas > N_CONTAS)) {
        fprintf(stderr, "erro: numero de contas invalido\n");
        exit(1);
    }

    contas=(conta_t*)calloc(n_contas,sizeof(conta_t));
    system("pause");

    /*inicializando as contas*/
    for(i=0; i<n_contas; i++){
        sem_init(&(contas[i].trava),0,1);
        inicializa(&contas[i],i+1,0.0);
    }

    /*depositos aleatorios*/
    for(i=0; i<n_contas;i++){
        depositar(&contas[i],1.0*(random()%100));
        consultaSaldo(&contas[i]);
    }

    /* aloca os descritores de thread */
    thr = (pthread_t *)calloc(n_threads, sizeof(pthread_t));
    if (thr == NULL) {
        fprintf(stderr, "erro em calloc()\n");
        exit(1);
    }

    /* cria as threads para realizar transferencias aleatorias */
    for (t = 0; t < n_threads; t++) {
        rc = pthread_create(&thr[t], NULL, auxThread, (void*)n_trans);
        if (rc != 0) {
            fprintf(stderr, "erro em pthread_create()\n");
            exit(1);
        }
    }

    for(t=0; t<n_threads;t++){
        pthread_join(thr[t], NULL);
    }
    for(i=0;i<n_contas;i++){
        consultaSaldo(&contas[i]);
    }
    return(0);
}
