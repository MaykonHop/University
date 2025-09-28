# Exercícios
## Cap 1,2,3
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

## Cap 4 


**1. O que significa _time sharing_ e qual a sua importância em um sistema operacional?**

---
 **2. Como e com base em que critérios é escolhida a duração de um _quantum_ de processamento?**

---

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

---
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

---
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

---


