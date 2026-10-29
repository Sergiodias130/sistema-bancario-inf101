# Sistema de Registro e Gestão de Contas Bancárias — Etapa 1

Trabalho da disciplina **INF101 - Programação de Computadores I**
Centro Universitário de Viçosa (UNIVIÇOSA)
Professores: Anderson R. Lamas e Vanderlea Queiroz

## Descrição

Este repositório contém a **Etapa 1** de um sistema incremental de Registro e
Gestão de Contas Bancárias, desenvolvido em C++. Nesta etapa o sistema
trabalha apenas com **variáveis individuais** (sem arrays, structs ou
funções), consolidando os fundamentos da linguagem: variáveis, estruturas de
controle (`if`, `switch`, `do while`) e validação de entradas.

## Arquivos

| Arquivo | Descrição |
|---|---|
| `sistema_bancario_etapa1.cpp` | Programa principal da Etapa 1. Cadastra e gerencia **uma única conta bancária** usando somente variáveis individuais, conforme especificado no enunciado. |
| `sistema_bancario_desafio_5contas.cpp` | Extensão opcional que responde à pergunta do desafio: *"Se quiséssemos cadastrar até 5 contas, qual solução seria possível?"* |

## Variáveis utilizadas

| Variável | Tipo | Finalidade |
|---|---|---|
| `numeroConta` | `int` | Número da conta |
| `nomeCliente` | `string` | Nome do titular |
| `cpf` | `string` | CPF do titular |
| `tipoConta` | `int` | 1 = Corrente; 2 = Poupança |
| `saldo` | `double` | Saldo atual |
| `contaAtiva` | `bool` | Indica se a conta está ativa |

## Menu

```
********************************
**       BANCO INF101         **
********************************
1 - Cadastrar conta
2 - Consultar conta
3 - Verificar saldo
4 - Alterar tipo da conta
5 - Ativar/Desativar conta
6 - Sair
```

O menu permanece em execução em um laço `do while` até que a opção **6** seja
escolhida, e a seleção da operação é feita com `switch`.

## Validações implementadas

- Número da conta deve ser maior que zero.
- Saldo inicial não pode ser negativo.
- Tipo da conta deve ser 1 (Corrente) ou 2 (Poupança).
- Operações que dependem de conta ativa (verificar saldo, alterar tipo)
  checam a variável `contaAtiva`.

## Desafio: cadastro de até 5 contas

A Etapa 1 pede apenas uma conta com variáveis individuais. Como ainda não
foram vistos structs nem funções neste ponto da disciplina, a solução mais
coerente com o conteúdo já estudado é usar **arrays paralelos**: um array
para cada atributo (`numeroConta[5]`, `nomeCliente[5]`, `cpf[5]`,
`tipoConta[5]`, `saldo[5]`, `contaAtiva[5]`), em que a posição `i` de cada
array representa os dados de uma mesma conta. Um contador (`totalContas`)
controla quantas posições já foram preenchidas, e a busca por conta nas
demais operações é feita percorrendo os arrays com `numeroConta[i]`.

Essa solução está implementada em `sistema_bancario_desafio_5contas.cpp`,
mantendo o mesmo menu e as mesmas validações da versão principal.

## Como compilar e executar

```bash
# Versão principal (Etapa 1 - uma conta)
g++ -std=c++17 -Wall -o sistema_bancario sistema_bancario_etapa1.cpp
./sistema_bancario

# Versão do desafio (até 5 contas)
g++ -std=c++17 -Wall -o sistema_bancario_desafio sistema_bancario_desafio_5contas.cpp
./sistema_bancario_desafio
```

No Windows (MinGW), basta trocar `./sistema_bancario` por
`sistema_bancario.exe`.

---

# Etapa 2 — Múltiplas contas e histórico de movimentações

Arquivo: `sistema_bancario_etapa2.cpp`

Nesta etapa o sistema passa a gerenciar **até 100 contas** usando arrays
paralelos e é organizado em **funções**. Também guarda um **histórico de
movimentações** (até 500 registros) em arrays separados.

## Estruturas de dados

| Array | Tipo | Finalidade |
|---|---|---|
| `numeroConta[MAX_CONTAS]` | `int` | Número da conta |
| `nomeCliente[MAX_CONTAS]` | `string` | Nome do titular |
| `cpf[MAX_CONTAS]` | `string` | CPF do titular |
| `tipoConta[MAX_CONTAS]` | `int` | 1 = Corrente; 2 = Poupança |
| `saldo[MAX_CONTAS]` | `double` | Saldo atual |
| `contaAtiva[MAX_CONTAS]` | `bool` | Indica se a conta está ativa |
| `contaMovimentacao[MAX_MOVIMENTACOES]` | `int` | Conta da movimentação |
| `tipoMovimentacao[MAX_MOVIMENTACOES]` | `char` | `'D'` = Depósito; `'S'` = Saque |
| `valorMovimentacao[MAX_MOVIMENTACOES]` | `double` | Valor movimentado |

## Menu

```
===== SISTEMA BANCARIO =====
1 - Cadastrar conta
2 - Listar contas
3 - Consultar conta
4 - Depositar
5 - Sacar
6 - Transferir
7 - Extrato
0 - Sair
```

## Funções

`cadastrarConta()`, `listarContas()`, `consultarConta()`, `depositar()`,
`sacar()`, `transferir()`, `exibirExtrato()`, além das auxiliares
`buscarConta()`, `registrarMovimentacao()`, `lerInteiro()` e `lerReal()`.

## Regras e validações

- Não permite número de conta repetido nem limite de 100 contas excedido.
- Depósito, saque e transferência exigem conta existente e ativa e valor positivo.
- Saque e transferência não são realizados com saldo insuficiente.
- A transferência debita a origem, credita o destino e gera **dois registros**
  no histórico: `'S'` na conta de origem e `'D'` na conta de destino.
- O extrato mostra apenas as movimentações da conta informada e o saldo atual.

## Como compilar e executar

```bash
g++ -std=c++17 -Wall -o sistema_bancario_etapa2 sistema_bancario_etapa2.cpp
./sistema_bancario_etapa2
```
