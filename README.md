# Estrutura de Dados - Luiz Felipe Elizeta dos Santos e Caio Cesar Oliva Coronel
## Agradecimentos
Agradecimentos especiais para Bruno Chevitarese, Aluno do IFES Serra, que nos ajudou a identificar erros de lógica durante o desenvolvimento. E Nailson Roveta, Ex gerente da arcelor e analista de sistemas, que nos ajudou a identificar problemas de documentação do código.
# Sistema de Gestão de Pacientes e Exames
Esse algoritimo realiza uma simulação de exames de raio-x. Um paciente chega ao hospital (com uma chance de 20% de ocorrer esse evento) e é alocado em uma fila de pacientes. Os pacientes em aguardo nessa fila são alocados entre 5 maquinas diferentes, e após a realização do exeme recebe um pre diagnóstico determinado por uma semi inteligencia artificial, em seguida um médico que não come, não dorme, e trabalha 24/7 irá analizar a situação desse paciente e determinar se o pre diagnóstico está correto ou não, dando uma nova condição ao paciente caso o exame realizado esteja incorreto. Durante o algoritimo, os pacientes que chegam ao hospital, os pré diagnósticos e os laudos médicos são salvos em seus respecitivos arquivos txt que simulam um banco de dados.

## Requisito:
  - Compilador para C (gcc versão 11)
  - Linguagem C instalada e funcionando
  - Make instalado.
  - Sistema operacional Ubuntu(22.04)
    
## Como executar
O primeiro passo é fazer o download de todos os arquivos na branch main e abrir a pasta contendo os downloads em algum compilador que compile C. Utilize o comando `make clean` para garantir que não haja nenhum arquivo já compilado com o mesmo nome instalado, e após isso utilize o comando `Make all`. Em seguida digite ./trabalho.exe para executar o programa.
Nota: Serão criados três arquivos.txt referentes ao programa, você pode observar e alterar ele de acordo com sua vontade.

## TAD's
Os Tipos Abstratos de Dados criados para suprir as necessidades ficaram de certa forma padronizados, a maior parte seguindo a ideia de uma fila, e separados entre três bibliotecas próprias.

### Exames
  - `Exam:` Estrutura referente ao exame realizado após o paciente sair da máquina. Contem: um ID para o exame, o ID da maquina em que o exame foi realizado, o ID do paciente, a condição do gerada, o timestamp, a prioridade desse exame, e uma variavel report para contador de tempo de aguardo.
  - `QueueExam:` Uma estrutura de fila que armazena estruturas do tipo QueueNodeExam. Recebe o nó da frente e do final da fila.
  - `QueueNodeExam:` Estrutura do tipo nó, cada nó contem uma estrutura do tipo Exam e outra estrutura do tipo QueueNodeExam referente ao elemento á seguinte este .
  - `Report:` Estrutura referente ao laudo gerado pelo médico. Contem: um ID para o laudo, o ID do exame referente ao laudo, a condição dada pelo médico (podendo ser, ou não, a condição do exame) e seu timestamp.

### Machine
  - `Machine:` Uma estrutura referente as máquinas que irão realizar os atendimentos, a lógica do código permite que somente cinco dessas existam de maneira simultanea. Contem: uma estrutura paciente pra armazenar o paciente alocado na máquina, um ID referente ao ID da maquina em uso (de 1 a 5) e um inteiro TimeCount referente ao contador do tempo que o paciente deve ficar na máquina
  - `QueueMachine:` Uma estrutura do tipo fila que armazena estruturas do tipo QueueNodeExam. Recebe o nó da frente e do final da fila.
  - `QueueNodeMachine:` Estrutura do tipo Nó, cada nó contem uma estrutura do tipo Machine e outra estrutura do tipo QueueNodeMachine referente ao nó seguinte da fila.

### Pacientes
  - `Patient:` Estrutura referente aos pacientes que chegam ao hospital. Contem: um ID para cada paciente, um char referente ao nome deste paciente e seu Timestamp.
  - `QueuePatient:` Uma estrutura do tipo fila que armazena estruturas do tipo QueueNodePatient. Recebe o nó da frente e do final da fila.
  - `QueueNodePatient:` Estrutura do tipo nó que será armazenada em estruturas do tipo QueuePatient. Contem: uma estrutura do tipo Patient referente ao paciente que está nessa posição da fila e outra estrutura QueueNodePatient referente ao próximo paciente na fila.

## Implementações
Dentro de cada biblioteca há funções para manipulação de cada TAD definido dentro do próprio arquivoa, em que todas tem seu funcionamento documentado dentro de cada arquivo.h. Em cada arquivo, as funções são muito parecidas, como a criação de filas, o adicionar e remover de elementos na fila e a liberação de memória alocada presente em todas elas. 

## Decisões e complicações durante a implementação
Algumas implementações foram feitas de maneira específica para facilitar o desenvolvimento, como a padronização na criação de filas para cada processo, já que essa estrutura estava sendo amplamente utilizada. Devido às necessidades comuns entre as bibliotecas, padronizamos as funções e adotamos a convenção de utilizar inglês nas variáveis do código. Além disso, decidimos utilizar as bibliotecas `assert.h` para garantir a alocação de memória após o uso do malloc, `string.h` para copiar dados, `unistd.h` para criar e editar arquivos, e `time.h` para adquirir datas e horas específicas e fazer pausas no programa. 

Como decisão extra, realizamos as operações restantes fora do looping principal e salvamos ela nos arquivos TXT em uma área separada. 

Quanto as complicações encontramos muitos erros relacionados a alocação e liberação de memória, ao longo do tempo fomos corrigindo esses problemas e encontrando a melhor forma de impedir o vazamento de memória. Outro ponto crucial foi que percebemos durante a execução que o numero de pacientes na fila de paciente continuava zerado por um tempo prolongado e não haviamos entendido que isso era normal, isso ocorre por conta  da quantidade de pacientes que chega que não é o suficiente para que todas as máquinas estejam ocupada por um periodo muito longo, diminuir a quantidade de máquinas disponiveis ou aumentar a quantidade de paciente que chega (ambos em algoritimos de teste, não no final) nos fez entender isso.

