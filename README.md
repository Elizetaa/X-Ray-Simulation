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
O primeiro passo é fazer o download de todos os arquivos na branch main. Em seguida compile o código do programa, o arquivo makefile contém as receitas all, que pode ser utilizada para compilação de todo o código, e clean, a qual irá remover os arquivos binários gerados da receita all. A receita all irá gerar o arquivo executável trabalho.exe, o qual é responsável por executar o projeto. Ao final da execução, serão criados três arquivos.txt referentes ao banco de dados do programa, você pode observar e alterar ele de acordo com sua vontade.

## TAD's
Os tipos abstratos de dados utilizados no programa, são responsáveis por armazenar informações referentes aos objetos. Os TAD's utilizadas são divididas em três categorias: Filas (First in First out), Nós (Elementos dentro das filas), e objetos (Exames, Pacientes, Máquinas e Laudos). Segue abaixo todos os TAD's e suas respectivas bibliotecas onde estão armazenadas:

### Exames
  - `Exam:` Estrutura da categoria objeto referente ao exame realizado após o paciente sair da máquina. Contem: um ID para o exame, o ID da maquina em que o exame foi realizado, o ID do paciente, a condição do gerada, o timestamp, a prioridade desse exame, e uma variavel report para contador de tempo de aguardo.
  - `QueueExam:` Uma estrutura da categoria fila que armazena estruturas do tipo QueueNodeExam. Recebe o nó da frente e do final da fila.
  - `QueueNodeExam:` Estrutura da categoria nó, cada nó contem uma estrutura do tipo Exam e outra estrutura do tipo QueueNodeExam referente ao elemento á seguinte este .
  - `Report:` Estrutura da categoria objeto referente ao laudo gerado pelo médico. Contem: um ID para o laudo, o ID do exame referente ao laudo, a condição dada pelo médico (podendo ser, ou não, a condição do exame) e seu timestamp.

### Machine
  - `Machine:` Uma estrutura da categoria objeto referente as máquinas que irão realizar os atendimentos, a lógica do código permite que somente cinco dessas existam de maneira simultanea. Contem: uma estrutura paciente pra armazenar o paciente alocado na máquina, um ID referente ao ID da maquina em uso (de 1 a 5) e um inteiro TimeCount referente ao contador do tempo que o paciente deve ficar na máquina
  - `QueueMachine:` Uma estrutura da categoria fila que armazena estruturas do tipo QueueNodeExam. Recebe o nó da frente e do final da fila.
  - `QueueNodeMachine:` Estrutura da categoria Nó, cada nó contem uma estrutura do tipo Machine e outra estrutura do tipo QueueNodeMachine referente ao nó seguinte da fila.

### Pacientes
  - `Patient:` Estrutura da categoria objeto referente aos pacientes que chegam ao hospital. Contem: um ID para cada paciente, um char referente ao nome deste paciente e seu Timestamp.
  - `QueuePatient:` Uma estrutura da categoria fila que armazena estruturas do tipo QueueNodePatient. Recebe o nó da frente e do final da fila.
  - `QueueNodePatient:` Estrutura da categoria nó que será armazenada em estruturas do tipo QueuePatient. Contem: uma estrutura do tipo Patient referente ao paciente que está nessa posição da fila e outra estrutura QueueNodePatient referente ao próximo paciente na fila.

## Implementações
A Implementação do código segue o formato do diagrama fornecido pela especificação do trabalho (arquivo tp2.pdf), com a decisão da dupla de manter o médico como uma váriavel e não como uma estrutura. Isso permitiu que o funcionamento do código fosse relativamente mais rápido a caso ele fosse uma estrutura(foi pouco, mas dá pra perceber a diferença, já que eu não preciso criar uma nova estrutura dentro do código principal). Outra decisão de implementação foi quanto às máquinas disponiveis, as estruturas maquinas somente são criadas caso haja um slot disponivel (slots são armazenados em uma variável chamada "machine_slots", que é um inteiro que vai de 0 a 5), isso deixa o código um pouco mais lento já que temos que criar varias máquinas a todo momento, porém nos ajuda muito quanto a impedir vazamento de memória.

Como decisão extra, terminamos todas as operações que estavam em aguardo ao fim do looping principal (que por definição dura 43200 ciclos)

## Complicações durante a implementação
Quanto as complicações encontramos muitos erros relacionados a alocação e liberação de memória, ao longo do tempo fomos corrigindo esses problemas e encontrando a melhor forma de impedir o vazamento de memória. Outro ponto crucial foi que percebemos durante a execução que o numero de pacientes na fila de paciente continuava zerado por um tempo prolongado e não haviamos entendido que isso era normal, isso ocorre por conta da quantidade de pacientes que chega que não é o suficiente para que todas as máquinas estejam ocupada por um periodo muito longo, diminuir a quantidade de máquinas disponiveis ou aumentar a quantidade de paciente que chega (ambos em algoritimos de teste, não no final) nos fez entender isso.

