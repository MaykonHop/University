# Monitores

Monitores dependem da linguaagem de programação - não tem em C

Usados em sistemas de memória compartilhada a biblioteca que controla o acesso a região crítica


# DeadLocks
Ocorre quando sistemas multiprogramados competem por recursos do sistema.
    - Recursos Preemptíveis: POdem ser retirados do processo sem problemas
    - Não-Preemptíveis: retirada gera falha -> Geram Deadlocks


- **Def**: Um processo está em situação de deadlock se todo processo pertencente ao conjunto estiver esperando por um evento que somente um processo desse mesmo conjunto poderá provocar” 

 Aumentar o numero de threads e transferências
 
 
 perf stat ./tarefa
