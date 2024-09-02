# Estrutura de Dados - Luiz Felipe Elizeta dos Santos e Caio Cesar Oliva Coronel
## Agradecimentos
Agradecimentos especiais para Bruno Chevitarese, Aluno do IFES Serra, que nos ajudou a identificar erros de lógica durante o desenvolvimento. E Nailson Roveta, Ex gerente da arcelor e analista de sistemas, que nos ajudou a identificar problemas de documentação do código.
# Sistema de Gestão de Pacientes e Exames
Esse algoritimo realiza uma simulação de exames de raio-x. Um paciente chega ao hospital (com uma chance de 20% de ocorrer esse evento) e é alocado em uma fila de pacientes. Os pacientes em aguardo nessa fila são alocados entre 5 maquinas diferentes, e após a realização do exeme recebe um pre diagnóstico determinado por uma semi inteligencia artificial, em seguida um médico que não come, não dorme, e trabalha 24/7 irá analizar a situação desse paciente e determinar se o pre diagnóstico está correto ou não, dando uma nova condição ao paciente caso o exame realizado esteja incorreto. Durante o algoritimo, os pacientes que chegam ao hospital, os pré diagnósticos e os laudos médicos são salvos em seus respecitivos arquivos txt que simulam um banco de dados. Durante a execução, o programa imprime um relatório eventual (que ocorre 100 vezes durante a iteração do looping principal), ao final, também é impresso as informações dos pacientes, exames e laudos que não foram concluidos durante o programa principal. 

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

## Funções

### Exames
  - `QueueExam *queue_create_exam()`: Cria e retorna uma nova fila de exames.
  - `Report *create_report(Exam *exame, int id)`: Recebe um exame e o ID do exame, retornando um laudo correspondente.
  - `void write_report_in_file(FILE* report_file, Report* report, int i)`: Recebe um arquivo, um laudo, e a iteração atual do looping, escrevendo as informações do laudo no arquivo.
  - `int queue_is_empty_exam(QueueExam *queue)`: Recebe uma fila de exames, verifica se está vazia, e retorna um valor booleano.
  - `void queue_free_exam(QueueExam *queue)`: Recebe uma fila de exames e libera a memória alocada para ela.
  - `void queue_enqueue_exam(QueueExam *queue, Exam *data)`: Recebe uma fila de exames e um exame, adicionando este exame à fila.
  - `Exam *queue_dequeue_exam(QueueExam *queue)`: Recebe uma fila de exames e retorna o primeiro exame da fila.
  - `Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, char *condition_IA, int prio)`: Recebe um ID do exame, ID do paciente, ID da máquina de raio-X, timestamp, condição do paciente e prioridade, retornando um exame com essas informações.
  - `int get_exam_id(Exam *exame)`: Recebe um exame e retorna o ID deste exame.
  - `int get_exam_patient_id(Exam *exame)`: Recebe um exame e retorna o ID do paciente deste exame.
  - `int get_exam_rx_id(Exam *exame)`: Recebe um exame e retorna o ID da máquina de raio-X deste exame.
  - `int get_time_report(Exam *aux_exam_2)`: Recebe um exame e retorna o tempo de espera por laudo deste exame.
  - `struct tm* get_exam_time(Exam *exame)`: Recebe um exame e retorna o timestamp deste exame.
  - `char *get_exam_condition(Exam *exame)`: Recebe um exame e retorna a condição deste exame.
  - `int get_exam_prio(Exam* exame)`: Recebe um exame e retorna a prioridade deste exame.
  - `char *create_diagnosis()`: Retorna um novo diagnóstico gerado aleatoriamente por uma semi-IA.
  - `int get_diagnostico_prio(char *diagnostico)`: Recebe um diagnóstico e retorna o grau de prioridade deste diagnóstico.
  - `void write_exam_in_file(Exam *exam, FILE *file, int i)`: Recebe um exame e um arquivo, escrevendo as informações do exame no arquivo.
  - `void enqueue_priority(Exam *exame, QueueExam *priority_queue)`: Recebe um exame e uma fila de prioridade de exames, adicionando este exame à fila de maneira prioritária.
  - `void time_report_update(QueueExam *exam_priority_queue)`: Recebe uma fila de prioridades e atualiza o tempo de aguardo por laudo desta fila.

### Machine
  - `Machine* create_machine(Patient *paciente, int machine_id)`: Recebe um paciente e o ID desta máquina, retornando uma máquina com essas informações.
  - `QueueMachine *queue_create_machine()`: Retorna uma nova fila de máquinas.
  - `int queue_is_empty_machine(QueueMachine *queue)`: Recebe uma fila de máquinas, verifica se ela está vazia, e retorna um valor booleano.
  - `void queue_enqueue_machine(QueueMachine *queue, Machine *data)`: Recebe uma fila de máquinas e uma máquina, alocando essa máquina ao final da fila.
  - `Machine *queue_dequeue_machine(QueueMachine *queue)`: Recebe uma fila de máquinas, retira o elemento da frente da fila, e retorna a máquina removida.
  - `void queue_free_machine(QueueMachine *queue)`: Recebe uma fila de máquinas e libera a memória alocada para ela.
  - `void destroy_machine(Machine *machine)`: Recebe uma máquina e libera a memória alocada para ela.
  - `Patient *get_machine_patient(Machine *machine)`: Recebe uma máquina e retorna o paciente alocado nela.
  - `int get_machine_id(Machine *machine)`: Recebe uma máquina e retorna o ID inteiro desta máquina.
  - `int manage_machine_slots(QueueMachine *machinequeue, int machine_slots, QueuePatient *patientqueue, int machine_id)`: Recebe uma fila de máquinas, a quantidade de máquinas disponíveis, uma fila de pacientes e o ID de uma máquina. Caso haja uma máquina disponível, aloca o primeiro paciente da fila em uma dessas máquinas e retorna o número atualizado de máquinas disponíveis.
  - `void run_machine_queue(QueueMachine *machine)`: Recebe uma fila de máquinas e atualiza o tempo restante para o fim do exame de todas as máquinas desta fila.
  - `int is_timecount_zero(QueueMachine *maquina_queue)`: Recebe uma fila de máquinas e retorna um valor booleano caso o exame tenha chegado ao fim.
  - `void clear_terminal()`: Limpa o terminal.


### Pacientes
  - `Patient* create_patient(int id, const char *name, struct tm* timestamp)`: Recebe o ID de um paciente, o nome desse paciente e um timestamp, retornando um paciente com essas informações.
  - `QueuePatient *queue_create_patient()`: Retorna uma nova fila de pacientes.
  - `int queue_is_empty_patient(QueuePatient *queue)`: Recebe uma fila de pacientes, verifica se ela está vazia, e retorna um valor booleano.
  - `void queue_enqueue_patient(QueuePatient *queue, Patient *data)`: Recebe uma fila de pacientes e um paciente, alocando este novo paciente no final da fila.
  - `Patient *queue_dequeue_patient(QueuePatient *queue)`: Recebe uma fila de pacientes, desaloca o paciente do começo da fila, e retorna este paciente.
  - `void queue_free_patient(QueuePatient *queue)`: Recebe uma fila de pacientes e libera a memória alocada para ela.
  - `int get_patient_id(Patient* paciente)`: Recebe um paciente e retorna o ID dele.
  - `char* get_patient_name(Patient* paciente)`: Recebe um paciente e retorna o nome dele.
  - `struct tm* get_patient_timestamp(Patient *paciente)`: Recebe um paciente e retorna o timestamp desse paciente.
  - `void destroy_patient(Patient *paciente)`: Recebe um paciente e libera a memória alocada para ele.
  - `void write_patient_in_file(Patient *paciente, FILE *paciente_file, int i)`: Recebe um paciente, um arquivo e a iteração do looping, e escreve as informações desse paciente no arquivo.
  - `int get_n_patient_queue(QueuePatient *queue)`: Recebe uma fila de pacientes e retorna o número de pacientes nela.

## Implementações
A Implementação do código segue o formato do diagrama fornecido pela especificação do trabalho (arquivo tp2.pdf), com a decisão da dupla de manter o médico como uma váriavel e não como uma estrutura. Isso permitiu que o funcionamento do código fosse relativamente mais rápido a caso ele fosse uma estrutura(foi pouco, mas dá pra perceber a diferença, já que eu não preciso criar uma nova estrutura dentro do código principal). Outra decisão de implementação foi quanto às máquinas disponiveis, as estruturas maquinas somente são criadas caso haja um slot disponivel (slots são armazenados em uma variável chamada "machine_slots", que é um inteiro que vai de 0 a 5), isso deixa o código um pouco mais lento já que temos que criar varias máquinas a todo momento, porém nos ajuda muito quanto a impedir vazamento de memória.

Como decisão extra, terminamos todas as operações que estavam em aguardo ao fim do looping principal (que por definição dura 43200 ciclos)

## Complicações durante a implementação
Quanto as complicações encontramos muitos erros relacionados a alocação e liberação de memória, ao longo do tempo fomos corrigindo esses problemas e encontrando a melhor forma de impedir o vazamento de memória. Outro ponto crucial foi que percebemos durante a execução que o numero de pacientes na fila de paciente continuava zerado por um tempo prolongado e não haviamos entendido que isso era normal, isso ocorre por conta da quantidade de pacientes que chega que não é o suficiente para que todas as máquinas estejam ocupada por um periodo muito longo, diminuir a quantidade de máquinas disponiveis ou aumentar a quantidade de paciente que chega (ambos em algoritimos de teste, não no final) nos fez entender isso.

