## Estrutura de Dados - Luiz Felipe Elizeta dos Santos e Caio Cesar Oliva Coronel
# Sistema de Gestão de Pacientes e Exames

Este projeto simples de um sistema para gerenciar pacientes e exames médicos. Com foco em manipulação de estruturas e criação de bibliotecas próprias em C.

## Requisito:
  - Compilador para C (gcc)
  - Linguagem C instalada e funcionando
  - Make instalado.
    
## Como executar
  Faça o download de todos os arquivos na main e abra-o em algum compilador.
  Utilizando o prompt de comandos utilize o comando `Make all` (no windows pode-se usar o comando `mingw32-make.exe all`)
  
  
  1. **instalar Dependências:**
  

  ### Dependências
  Para executar, basta fazer o download de todos os arquivos do repositório e utilizar o executavel make, que está dentro dos arquivos do mingw, utilizando o prompt de comando para executar o seguinte comando "mingw32-make.exe all" ou "mingw64-make.exe all" (pode mudar a depender da sua versão).

### Paciente (`Patient`)

Estrutura que representa um paciente (`patient`). Dividida em ID, Nome e data de nascimento,
onde são representados como `id`,`nome` e `birthdate`, respectivamente.

#### Funções

- `Patient *create_patient()`: Cria um novo paciente.
- `int get_patient_id()`: Retorna o ID do paciente.
- `const char *get_patient_name()`: Retorna o nome do paciente.
- `struct tm *get_patient_birthdate()`: Retorna a data de nascimento do paciente.
- `void destroy_patient()`: Libera a memória alocada para o paciente.

### Exame (`Exam`)

Estrutura que representa um exame médico (`exam`). Dividida em ID do exame, ID do paciente, ID di aparelho de Raio-X e Data do exame,
onde são representados como `id`,`patient_id`,`rx_id` e `time` respectivamente.

#### Funções

- `Exam *create_exam()`: Cria um novo exame.
- `int get_exam_id()`: Retorna o ID do exame.
- `int get_exam_patient_id()`: Retorna o ID do paciente associado ao exame.
- `int get_exam_rx_id()`: Retorna o ID do aparelho de Raio-X utilizado no exame.
- `struct tm *get_exam_time()`: Retorna a data e hora do exame.
- `void destroy_exam()`: Libera a memória alocada para o exame.


## Como usar

Para implementar o código basta usar o arquivo executar.bat !
