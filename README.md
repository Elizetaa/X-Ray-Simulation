## Estrutura de Dados - Luiz Felipe Elizeta dos Santos e Caio Cesar Oliva Coronel
# Sistema de Gestão de Pacientes e Exames

Este projeto simples com foco em manipulação de estruturas, criação de TAD's e bibliotecas próprias em C.
O programa realiza uma simulação de realizações de exames de Raio-X e cria arquivos contendo os dados gerados e cria relatórios periódicos no terminal.

## Requisito:
  - Compilador para C (gcc)
  - Linguagem C instalada e funcionando
  - Make instalado.
    
## Como executar
  Faça o download de todos os arquivos na branch main e abra a pasta com os downloads em algum compilador que compile C.
  Utilize o comando `Make all` (este comando pode variar, consulte como será em seu sistema.) e execute o trabalho.exe que deverá ser criado.
  Nota: Serão criados três arquivos.txt referentes ao programa, você pode observar e alterar ele de acordo com sua vontade.

## TAD's
Os Tipos Abstratos de Dados criados para suprir as necessidades ficaram de certa forma padronizados, a maior parte seguindo a ideia de uma fila, e separados entre três bibliotecas próprias.

### Exames
  - `Exam:` Contém todas as informações relativas ao exame em si para manipulações.
  - `QueueExam:` Base da fila, onde através dela você pode acessar todos os elementos da fila.
  - `QueueNodeExam:` Um elemento na fila.
  - `Report:` Estrutura do documento final.

### Machine
  - `Machine:` Contém informações internas da máquina.
  - `QueueMachine:` Base da fila de Máquinas.
  - `QueueNodeMachine:` Um elemento na fila.

### Pacientes
  - `Patient:` Contém informações internas do paciente.
  - `QueuePatient:` Base da fila de pacientes.
  - `QueueNodePatient:` Um elemento na fila.

## Implementações
Dentro de cada biblioteca há funções para manipulação de cada TAD definido dentro do próprio arquivoa, em que todas tem seu funcionamento documentado dentro de cada arquivo.h. Em cada arquivo, as funções são muito parecidas, como a criação de filas, o adicionar e remover de elementos na fila e a liberação de memória alocada presente em todas elas. 
Obs. Nem todas funções foram utilizadas.

## Decisões de Implementação
Algumas implementações foram feitas de maneira específica para facilitar o desenvolvimento, como a padronização na criação de filas para cada processo, já que essa estrutura estava sendo amplamente utilizada. Devido às necessidades comuns entre as bibliotecas, padronizamos as funções e adotamos a convenção de utilizar inglês nas variáveis do código. Além disso, decidimos utilizar as bibliotecas `assert.h` para garantir a alocação de memória após o uso do malloc, `string.h` para copiar dados, `unistd.h` para criar e editar arquivos, e `time.h` para adquirir datas e horas específicas e fazer pausas no programa. Também foi criada uma função separada para calcular as horas extras dos médicos, permitindo a finalização dos exames após o período definido, além de possibilitar a alteração de alguns parâmetros no código principal (`main`).
