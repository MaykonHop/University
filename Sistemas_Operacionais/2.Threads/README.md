# ⚙️ Gestão de Tasks

Sistemas de computação geralmente têm mais tarefas a executar do que processadores disponíveis. Por isso, é necessário **multiplexar o processador**, ou seja, **compartilhá-lo entre as tarefas**.

## 🎯 Objetivos da Gestão de Tasks

- Executar várias tarefas **simultaneamente**, mesmo com processador(es) limitado(s).
- Atribuir **tempo de CPU** a cada tarefa conforme suas **necessidades**.

    - Solução ingênua :Um processador por tarefa → **Inviável** técnica e economicamente.

    - Solução prática: **Compartilhamento inteligente do processador** entre tarefas (multiplexação).

## 🔄 Conceito de Task

- **Tarefa**  é uma **execução de um fluxo sequencial de instruções** por um processador.
- Representa uma **atividade dinâmica**, com:
  - **Estado interno** que muda com o tempo
  - **Interações** com o usuário, dispositivos ou outras tasks
- Pode ser implementada como **processo** ou **thread**.

### 📝 Diferença entre Programa e Task

| Conceito | Programa | Task |
|----------|----------|--------|
| Natureza | Estático | Dinâmico |
| Definição | Conjunto de instruções (código) | Execução das instruções por um processador |
| Estado interno | Não possui | Possui (evolui com a execução) |
| Interações | Nenhuma | Com usuário, SO e outras tarefas |
| Exemplo | `/usr/bin/vi` ou `notepad.exe` | Vi aberto editando um arquivo |



### Lei de Amdahl

A **Lei de Amdahl** é um princípio da computação que calcula o máximo ganho de desempenho (ou **Speedup**) que se pode obter ao otimizar um sistema. Sua principal conclusão é que esse ganho é sempre limitado pela parte do sistema que não foi melhorada.

#### Termos Técnicos Principais

* **Parte Sequencial (`1 - f`):** É a fração de um programa que deve ser executada em ordem, passo a passo, e não pode ser dividida entre múltiplos processadores. Ela funciona como uma "âncora" ou um **gargalo (bottleneck)**, determinando o limite máximo de aceleração.

* **Parte Paralelizável (`f`):** É a fração do programa que pode ser dividida em tarefas menores e executada simultaneamente por vários processadores para economizar tempo.

* **N (Número de Processadores):** Refere-se à quantidade de unidades de processamento disponíveis para executar a parte paralelizável da tarefa.

* **Speedup (Aceleração):** É o fator que mede "quantas vezes mais rápido" um programa se torna após uma melhoria. É calculado pela fórmula `Speedup = 1 / ((1 - f) + f / N)`. Conforme `N` aumenta, o `Speedup` se aproxima do seu limite máximo de `1 / (1 - f)`.

Em resumo, a Lei de Amdahl nos ensina que adicionar mais processadores a um sistema tem um **retorno decrescente**: os ganhos de velocidade são grandes no início, mas se tornam cada vez menores à medida que a parte sequencial do trabalho se torna o fator dominante.