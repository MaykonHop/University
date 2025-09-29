# Exercícios
## Capítulos 1,2,3
**1. O que diferencia o núcleo do restante do sistema operacional?**

O núcleo (kernel) é o componente central do sistema operacional que executa em modo privilegiado (modo núcleo), dando-lhe acesso total ao hardware. O restante do sistema (aplicativos, interface de usuário) roda em modo restrito (modo usuário). A principal função do núcleo é gerenciar os recursos do sistema, como memória, processos e dispositivos, atuando como uma ponte entre o hardware e o software.  

**2. Seria possível construir um sistema operacional seguro usando um processador que não tenha níveis de privilégio? Por quê?**

Não. Pois sem essa separação, qualquer programa poderia acessar o hardware diretamente, modificar a memória do sistema e executar operações críticas, tornando o sistema instável e inseguro.  

**3. Haveria alguma utilidade para os níveis intermediários (anéis 1 e 2) da arquitetura x86?**

Sim, os anéis intermediários foram projetados para tarefas que exigem mais privilégios que aplicações comuns, mas menos que o núcleo, como drivers de dispositivo e virtualização.

**4. Quais as diferenças entre interrupções, exceções e traps?**

| Característica | Interrupção                  | Exceção                            | Trap (Interrupção de Software)          |
|----------------|------------------------------|------------------------------------|------------------------------------------|
| Origem         | Hardware externo             | Erro na execução de instrução (CPU) | Instrução de software intencional        |
| Sincronicidade | Assíncrona                   | Síncrona                           | Síncrona                                 |
| Propósito      | Lidar com eventos de hardware (E/S) | Lidar com erros de programa       | Solicitar serviço do SO (chamada de sistema) |

  

**5. O comando em linguagem C fopen é uma chamada de sistema ou uma função de biblioteca? Por quê?**

fopen é uma função de biblioteca. A razão é que ela faz parte da biblioteca padrão C (stdio.h) e fornece uma interface de alto nível e portátil. Internamente, fopen invoca a chamada de sistema específica do sistema operacional (como open() no Linux) para realizar a tarefa.

**6. Quais das seguintes operações não deveriam ser permitidas em nível usuário? Por quê?**

As operações que não deveriam ser permitidas em modo usuário são:

    (a) Ler uma porta de entrada/saída: Permite acesso direto ao hardware, o que é um risco de segurança e estabilidade.   

    (d) Ajustar o valor do relógio do hardware: O relógio é um recurso global crítico para a segurança e o funcionamento do sistema.  

    (f) Mascarar uma ou mais interrupções: Permitiria que um processo monopolizasse a CPU, podendo congelar todo o sistema.  

**7. Quais das seguintes ações teriam de ser realizadas através de chamadas de sistema?**

As ações que requerem chamadas de sistema são aquelas que interagem com recursos gerenciados pelo núcleo:

    (a) Ler o relógio de tempo real do hardware: Requer chamada de sistema por ser acesso a hardware.

    (b) Enviar um pacote através da rede: Requer chamada de sistema para usar o hardware de rede.

    (e) Remover um arquivo do disco: Requer chamada de sistema para manipular o sistema de arquivos, que é um recurso protegido pelo núcleo.   

As ações que não requerem chamadas de sistema são:

    (c) Calcular uma exponenciação: É uma operação puramente computacional.

    (d) Preencher uma área de memória do processo com zeros: O processo pode manipular livremente a memória que já lhe foi alocada.

**8. Coloque na ordem correta as ações abaixo, que ocorrem durante a execução da função printf("Hello world").**

    (h) O processo chama a função printf da biblioteca C. ➜ O programa, rodando em modo usuário, chama printf().

    (c) A função de biblioteca printf recebe e processa os parâmetros de entrada (a string “Hello world”) ➜ A função interpreta a string e os argumentos de formatação, se houver.

    (d) A função de biblioteca printf prepara os registradores para solicitar a chamada de sistema write() ➜ Isso inclui preparar os parâmetros e fazer o "trampolim" para o kernel.

    (g) Uma interrupção de software é acionada. ➜ No Linux, por exemplo, isso seria a instrução syscall, que provoca uma mudança para o modo kernel.

    (a) A rotina de tratamento da interrupção de software é ativada dentro do núcleo. ➜ O kernel reconhece que é uma syscall e executa a rotina associada (ex: sys_write).

    (i) A operação de escrita no terminal é efetuada ou agendada pela rotina de tratamento da interrupção. ➜ O kernel escreve no buffer do terminal ou envia os dados diretamente, dependendo da situação.

    (j) O controle volta para a função printf em modo usuário. ➜ Após a execução da syscall, retorna-se ao espaço do usuário.

    (b) A função printf finaliza sua execução e devolve o controle ao código do processo. ➜ Após receber o retorno da syscall, printf termina.

Ações irrelevantes ou não pertencentes diretamente à sequência:

    (e) O disco rígido gera uma interrupção indicando a conclusão da operação. 
    ✘ Isso não acontece nessa sequência, já que não há acesso ao disco. Escrevendo no terminal geralmente não envolve o disco.

    (f) O escalonador escolhe o processo mais prioritário para execução. 
    ✘ Isso pode acontecer a qualquer momento no sistema, mas não faz parte direta da sequência de chamada e execução de printf.

## Capítulo 4


**1. O que significa _time sharing_ e qual a sua importância em um sistema operacional?**


 **2. Como e com base em que critérios é escolhida a duração de um _quantum_ de processamento?**



 **3. Considerando o diagrama de estados dos processos apresentado na figura a seguir, complete o diagrama com a transição de estado que está faltando (t₆) e apresente o significado de cada um dos estados e transições.**
 
  **Diagrama de estados (representação textual):**

```
         [e1]
           |
          t5
           v
         [e3] ---> t2 ---> [e4]
          |               ^
         t4               |
          v              t3
         [e5] <---        |
           ^              |
           |              |
          t1              |
           |              |
         [e2] ------------
```

- **Estados**:
  - e1
  - e2
  - e3
  - e4
  - e5

- **Transições conhecidas**:
  - t1, t2, t3, t4, t5  
  - **(Falta a transição t₆)**


**4. Indique se cada uma das transições de estado de tarefas a seguir definidas é possível ou não. Se a transição for possível, dê um exemplo de situação na qual ela ocorre.**  
**(N: Nova, P: Pronta, E: Executando, S: Suspensa, T: Terminada)**

- [ ] **E → P**
- [ ] **E → S**
- [ ] **S → E**
- [ ] **P → N**
- [ ] **S → T**
- [ ] **E → T**
- [ ] **N → S**
- [ ] **P → S**


**5. Relacione as afirmações abaixo aos respectivos estados no ciclo de vida das tarefas**  
**(N: Nova, P: Pronta, E: Executando, S: Suspensa, T: Terminada)**

1. [ ] O código da tarefa está sendo carregado.  
2. [ ] As tarefas são ordenadas por prioridades.  
3. [ ] A tarefa sai deste estado ao solicitar uma operação de entrada/saída.  
4. [ ] Os recursos usados pela tarefa são devolvidos ao sistema.  
5. [ ] A tarefa vai a este estado ao terminar seu _quantum_.  
6. [ ] A tarefa só precisa do processador para poder executar.  
7. [ ] O acesso a um semáforo em uso pode levar a tarefa a este estado.  
8. [ ] A tarefa pode criar novas tarefas.  
9. [ ] Há uma tarefa neste estado para cada processador do sistema.  
10. [ ] A tarefa aguarda a ocorrência de um evento externo.


## Capítulo 5

**Explique o que é, para que serve e o que contém um TCB - Task Control Block.**

  Um TCB (Task Control Block) é uma estrutura de dados mantida pelo núcleo do sistema operacional para representar uma tarefa. Ele serve para armazenar todas as informações necessárias para gerenciar a tarefa, incluindo seu estado, contexto e recursos. O TCB typically contém:
  - Identificador da tarefa (como um PID).
  - Estado da tarefa (nova, pronta, executando, suspensa, terminada).
  - Informações de contexto do processador (valores dos registradores, como PC, SP, etc.).
  - Lista de áreas de memória usadas pela tarefa.
  - Listas de arquivos abertos, conexões de rede e outros recursos.
  - Informações de gerência (prioridade, usuário, tempo de processamento, etc.).


**2.Desenhe o diagrama de tempo da execução do código a seguir, informe qual a saída do programa na tela (com os valores de x) e calcule a duração aproximada de sua execução.**
```c
int main()
{
    int x = 0;
    fork();
    x++;
    sleep(5);
    wait(0);
    fork();
    wait(0);
    sleep(5);
    x++;
    printf("Valor de x: %d\n", x);
}
```

  **Diagrama de Tempo (descrição):**
  - Tempo 0: Processo P (pai) inicia, x=0. Executa `fork()`, criando processo C1 (filho).
  - Tempo 0-5: P e C1 executam `x++` (x=1 em cada) e `sleep(5)` (ambos dormem).
  - Tempo 5: P e C1 acordam. P executa `wait(0)` e bloqueia esperando C1 terminar. C1 executa `wait(0)` (retorna -1 pois não tem filhos), então executa `fork()`, criando C2 (filho de C1). C1 e C2 executam `wait(0)`: C1 bloqueia esperando C2, C2 retorna immediately (sem filhos) e executa `sleep(5)` (dorme).
  - Tempo 10: C2 acorda, executa `x++` (x=2 em C2) e `printf` ("Valor de x: 2"). C2 termina.
  - Tempo 10: C1, que estava esperando, acorda, executa `sleep(5)` (dorme).
  - Tempo 15: C1 acorda, executa `x++` (x=2 em C1) e `printf` ("Valor de x: 2"). C1 termina.
  - Tempo 15: P, que estava esperando, acorda, executa `fork()`, criando C3 (filho). P e C3 executam `wait(0)`: P bloqueia esperando C3, C3 retorna immediately e executa `sleep(5)` (dorme).
  - Tempo 20: C3 acorda, executa `x++` (x=2 em C3) e `printf` ("Valor de x: 2"). C3 termina.
  - Tempo 20: P acorda, executa `sleep(5)` (dorme).
  - Tempo 25: P acorda, executa `x++` (x=2 em P) e `printf` ("Valor de x: 2"). P termina.

  **Saída:**
  ```
  Valor de x: 2
  Valor de x: 2
  Valor de x: 2
  Valor de x: 2
  ```
  (4 impressões, uma de cada processo: C2, C1, C3, P)

  **Duração aproximada:** 25 segundos.

**3.Indique quantas letras "X" serão impressas na tela pelo programa abaixo quando for executado com a seguinte linha de comando: `a.out 4 3 2 1`**

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid[10];
    int i;
    int N = atoi(argv[argc-2]);
    for (i=0; i<N; i++)
        pid[i] = fork();
    if (pid[0] != 0 && pid[N-1] != 0)
        pid[N] = fork();
    printf("X");
    return 0;
}
```

**Resposta:** 5 letras "X" serão impressas.

**Explicação:** Com `a.out 4 3 2 1`, `argc=5`, `argv[argc-2] = argv[3] = "2"`, então `N=2`. O código cria 2 processos no loop (P0, P1, P2, P3) e, devido à condição, apenas P0 cria um processo adicional (P4). Total de processos: 5, cada um imprime "X".


**4. O que são threads e para que servem?**

Threads são fluxos de execução independentes dentro de um processo. Eles permitem que um processo execute múltiplas tarefas concorrentemente, compartilhando o mesmo espaço de endereçamento e recursos. Threads servem para melhorar a responsividade de aplicações, permitir concorrência e aproveitar múltiplos processadores em sistemas multiprocessados.


**5. Quais as principais vantagens e desvantagens de threads em relação a processos?**

**Vantagens:**
- Criação e troca de contexto mais rápidas.
- Compartilhamento de dados é mais fácil (memória compartilhada).
- Menor overhead de memória e recursos.

**Desvantagens:**
- Menor robustez: um erro em uma thread pode afetar todo o processo.
- Segurança: threads herdam as permissões do processo, não podendo ter permissões diferentes.
- Sincronização mais complexa devido ao compartilhamento de memória.


**6. Forneça dois exemplos de problemas cuja implementação multi-thread não tem desempenho melhor que a respectiva implementação sequencial.**

1. **Problemas inerentemente sequenciais:** Como cálculo de fatorial ou Fibonacci recursivo, onde cada passo depende do resultado do anterior, não havendo ganho com paralelismo.
2. **Problemas com muita contenção por dados compartilhados:** Como incrementar um contador global por múltiplas threads, onde o overhead de sincronização (ex: mutex) anula os benefícios da concorrência.

**7. Associe as afirmações aos modelos de threads: a) many-to-one (N:1); b) one-to-one (1:1); c) many-to-many (N:M)**

(a) Tem a implementação mais simples, leve e eficiente. → **N:1**  
(b) Multiplexa os threads de usuário em um pool de threads de núcleo. → **N:M**  
(c) Pode impor uma carga muito pesada ao núcleo. → **1:1**  
(d) Não permite explorar a presença de várias CPUs pelo mesmo processo. → **N:1**  
(e) Permite uma maior concorrência sem impor muita carga ao núcleo. → **N:M**  
(f) Geralmente implementado por bibliotecas. → **N:1**  
(g) É o modelo implementado no Windows NT e seus sucessores. → **1:1**  
(h) Se um thread bloquear, todos os demais têm de esperar por ele. → **N:1**  
(i) Cada thread no nível do usuário tem sua correspondente dentro do núcleo. → **1:1**  
(j) É o modelo com implementação mais complexa. → **N:M**


**8. Considerando as implementações de threads N:1 e 1:1 para o trecho de código a seguir, a) desenhe os diagramas de execução, b) informe as durações aproximadas de execução e c) indique a saída do programa na tela.**

```c
int y = 0;
void threadBody()
{
    int x = 0;
    sleep(10);
    printf("x: %d, y:%d\n", ++x, ++y);
    thread_exit();
}
main()
{
    thread_create(&tA, threadBody, ...);
    thread_create(&tB, threadBody, ...);
    sleep(1);
    thread_join(&tA);
    thread_join(&tB);
    sleep(1);
    thread_create(&tC, threadBody, ...);
    thread_join(&tC);
}
```

**Modelo N:1:**
- **Diagrama de execução:** Não é possível desenhar detalhadamente aqui, mas o comportamento é que, como há apenas uma thread de núcleo, quando uma thread bloqueia (ex: `sleep`), toda a processo bloqueia. Assim, após `main` criar `tA` e `tB`, o `sleep(1)` bloqueia a thread de núcleo, impedindo `tA` e `tB` de executarem. Quando `main` executa `thread_join`, ele espera por `tA` e `tB`, que nunca executaram, resultando em deadlock.
- **Duração:** Indeterminada (deadlock).
- **Saída:** Nenhuma (ou não definida).

**Modelo 1:1:**
- **Diagrama de execução:** 
  - Tempo 0: `main` cria `tA` e `tB`. Ambas começam a executar concorrentemente e entram em `sleep(10)`.
  - Tempo 1: `main` acorda do `sleep(1)` e executa `thread_join(tA)` e `thread_join(tB)`, bloqueando até `tA` e `tB` terminarem.
  - Tempo 10: `tA` e `tB` acordam, executam `printf` e terminam. A ordem de execução não é determinística: `tA` pode imprimir `x:1, y:1` e `tB` `x:1, y:2`, ou vice-versa (devido ao incremento não atômico de `y`).
  - Tempo 11: `main` acorda do `sleep(1)`, cria `tC` e executa `thread_join(tC)`, bloqueando até `tC` terminar.
  - Tempo 21: `tC` acorda do `sleep(10)`, executa `printf` (`x:1, y:3`) e termina.
- **Duração:** 21 segundos.
- **Saída:** 
  ```
  x:1, y:1
  x:1, y:2
  x:1, y:3
  ```
  (a ordem das duas primeiras impressões pode variar).



## Capítulo 6


**1. Explique o que é escalonamento Round-Robin, dando um exemplo.**  

  **Resposta:**  
  Round-Robin é um algoritmo **preemptivo** em que cada tarefa recebe um quantum `tq`.  
  Se não terminar, retorna ao fim da fila de prontos.  
  **Exemplo:** Para `t1=5`, `t2=4`, `t3=3` e `tq=2`:  
  ```

  t1 0–2 | t2 2–4 | t3 4–6 | t1 6–8 | t2 8–10 | t3 10–11 | t1 11–12

  ```

---

**2. Considere um sistema de tempo compartilhado com valor de quantum tq e duração da troca de contexto ttc. Considere tarefas de entrada/saída que usam em média p% de seu quantum de tempo cada vez que recebem o processador. Defina a eficiência E do sistema como uma função dos parâmetros tq, ttc e p.**  
**Resposta:**  
Tempo útil médio: `(p/100)·tq`  
Tempo total médio: `(p/100)·tq + ttc`  
$$
E(tq, ttc, p) = \frac{\left(\frac{p}{100}\right) \cdot tq}{\left(\frac{p}{100}\right) \cdot tq + ttc}
$$
---

**3. Explique o que é, para que serve e como funciona a técnica de aging.**  
**Resposta:**  
- **O que é:** mecanismo de aumento gradual da prioridade dinâmica de tarefas esperando.  
- **Para que serve:** evitar **inanição** em sistemas de prioridade.  
- **Como funciona:** enquanto espera, prioridade dinâmica é incrementada (`pd += α`). Ao executar, retorna à prioridade estática (`pd = pe`). Assim, tarefas “envelhecem” até serem escalonadas.

---

**4. No algoritmo de envelhecimento definido na Seção 6.4.6, o que seria necessário modificar para suportar uma escala de prioridades negativa?**  
**Resposta:**  
- Se **menor valor = maior prioridade**, basta inverter o aging:  
  - Escalas normais: `pd += α`.  
  - Escalas negativas: `pd -= α`.  
- Deve-se também limitar os valores dentro do intervalo válido (ex.: `-20 a +19`).  

---

**5. A tabela a seguir representa um conjunto de tarefas prontas para utilizar um processador. Represente graficamente a sequência de execução das tarefas e calcule os tempos médios de vida (turnaround time, Tt) e de espera (waiting time, Tw), para as políticas:**

| Tarefa | Ingresso | Duração | Prioridade |
|--------|---------:|--------:|-----------:|
| t1     | 0        | 5       | 2          |
| t2     | 0        | 4       | 3          |
| t3     | 3        | 5       | 5          |
| t4     | 5        | 6       | 9          |
| t5     | 7        | 4       | 6          |

- **(a) FCFS cooperativa** → Tt = 11.4, Tw = 6.6  
- **(b) SJF cooperativa** → Tt = 10.6, Tw = 5.8  
- **(c) SJF preemptiva (SRTF)** → Tt = 10.6, Tw = 5.8  
- **(d) PRIO cooperativa** → Tt = 10.6, Tw = 5.8  
- **(e) PRIO preemptiva** → Tt = 14.4, Tw = 9.6  
- **(f) RR (tq=2, sem aging)** → Tt = 15.0, Tw = 10.2  

---

**6. Idem, para as tarefas da tabela a seguir:**

| Tarefa | Ingresso | Duração | Prioridade |
|--------|---------:|--------:|-----------:|
| t1     | 0        | 5       | 2          |
| t2     | 0        | 6       | 3          |
| t3     | 1        | 2       | 4          |
| t4     | 7        | 6       | 7          |
| t5     | 11       | 4       | 9          |

- **(a) FCFS cooperativa** → Tt = 10.2, Tw = 5.8  
- **(b) SJF cooperativa** → Tt = 9.2, Tw = 4.6  
- **(c) SJF preemptiva (SRTF)** → Tt = 8.8, Tw = 4.2  
- **(d) PRIO cooperativa** → Tt = 10.2, Tw = 5.6  
- **(e) PRIO preemptiva** → Tt = 10.2, Tw = 5.6  
- **(f) RR (tq=2, sem aging)** → Tt = 12.4, Tw = 7.8  

## Capítulo 7

**1. Explique os conceitos de inversão e herança de prioridade.**  
**Resposta:**  
- **Inversão de prioridade:** ocorre quando uma tarefa de alta prioridade fica bloqueada esperando uma tarefa de baixa prioridade que detém um recurso, mas que não consegue prosseguir porque tarefas de prioridade intermediária estão ocupando o processador.  
- **Herança de prioridade:** solução para o problema. A tarefa de baixa prioridade que detém o recurso herda temporariamente a prioridade da tarefa de alta prioridade bloqueada, garantindo que execute até liberar o recurso. Depois, retorna à sua prioridade original.



**2. O sistema operacional da sonda Mars Pathfinder usa escalonamento por prioridades preemptivo, sem envelhecimento e sem compartilhamento de tempo. Suponha que as tarefas tg e tm detêm a área de transferência de dados durante todo o período em que executam. Os dados de um trecho de execução das tarefas são indicados na tabela a seguir. Desenhe o diagrama de tempo da execução sem e com o protocolo de herança de prioridades e discuta as diferenças.**

| Tarefa | Ingresso   | Duração | Prioridade |
|--------|-----------:|--------:|-----------:|
| tg     | 0, 5, 10   | 1       | Alta       |
| tm     | 2          | 2       | Baixa      |
| tc     | 3          | 10      | Média      |

**Resposta:**  
- **Sem herança de prioridade:**  
  - `tg` inicia em 0 e executa por 1 unidade (0–1).  
  - Em 2, `tm` começa e pega a área de transferência.  
  - Em 3, `tc` chega (prioridade maior que `tm`) e ocupa o processador por 10 unidades.  
  - `tg` volta em 5 e 10, mas não pode executar porque o recurso está preso em `tm`. Isso gera bloqueio e reinicializações da sonda.  

- **Com herança de prioridade:**  
  - Quando `tg` precisa do recurso em 5, `tm` herda prioridade alta.  
  - `tm` executa imediatamente, libera o recurso e devolve a prioridade.  
  - `tg` prossegue normalmente.  
  - Assim, o bloqueio prolongado é evitado e o sistema não sofre reinicializações.  

**Diferença principal:** o protocolo de herança evita que tarefas críticas fiquem bloqueadas indefinidamente por causa de tarefas de menor prioridade, garantindo maior confiabilidade em sistemas de tempo real.













