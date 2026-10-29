// =============================================================
// UNIVIÇOSA - INF101 Programação de Computadores I
// Trabalho: Sistema de Registro e Gestão de Contas Bancárias
// ETAPA 2 - Múltiplas contas e histórico de movimentações
// Aluno: Sérgio Augusto Dias Filho
// =============================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// -------------------- Dados das contas --------------------
const int MAX_CONTAS = 100; // é previsto um limite máximo de 100 contas

int numeroConta[MAX_CONTAS];
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS];     // 1 = Corrente, 2 = Poupança
double saldo[MAX_CONTAS];
bool contaAtiva[MAX_CONTAS];

int quantidadeContas = 0;

// -------------------- Histórico de movimentações --------------------
const int MAX_MOVIMENTACOES = 500;

int contaMovimentacao[MAX_MOVIMENTACOES];
char tipoMovimentacao[MAX_MOVIMENTACOES]; // 'D' = Depósito, 'S' = Saque
double valorMovimentacao[MAX_MOVIMENTACOES];

int quantidadeMovimentacoes = 0;

// -------------------- Funções auxiliares --------------------

// Lê um número inteiro, repetindo enquanto a entrada for inválida
int lerInteiro(string mensagem) {
    int valor;
    cout << mensagem;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. " << mensagem;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

// Lê um número real, repetindo enquanto a entrada for inválida
double lerReal(string mensagem) {
    double valor;
    cout << mensagem;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. " << mensagem;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

// Procura a conta pelo número e retorna o índice, ou -1 se não existir
int buscarConta(int numero) {
    for (int i = 0; i < quantidadeContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

// Grava uma movimentação no histórico
void registrarMovimentacao(int conta, char tipo, double valor) {
    contaMovimentacao[quantidadeMovimentacoes] = conta;
    tipoMovimentacao[quantidadeMovimentacoes] = tipo;
    valorMovimentacao[quantidadeMovimentacoes] = valor;
    quantidadeMovimentacoes++;
}

string descricaoTipoConta(int tipo) {
    if (tipo == 1) return "Corrente";
    if (tipo == 2) return "Poupanca";
    return "Desconhecido";
}

void exibirDadosConta(int i) {
    cout << "Numero: " << numeroConta[i] << endl;
    cout << "Cliente: " << nomeCliente[i] << endl;
    cout << "CPF: " << cpf[i] << endl;
    cout << "Tipo: " << descricaoTipoConta(tipoConta[i]) << endl;
    cout << "Saldo: R$ " << saldo[i] << endl;
    cout << "Situacao: " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
}

// -------------------- 1. Cadastrar conta --------------------
void cadastrarConta() {
    cout << "\n=== CADASTRAR CONTA ===" << endl;

    if (quantidadeContas >= MAX_CONTAS) {
        cout << "Limite de " << MAX_CONTAS << " contas atingido." << endl;
        return;
    }

    int numero = lerInteiro("Numero da conta: ");
    if (numero <= 0) {
        cout << "Numero de conta invalido." << endl;
        return;
    }
    if (buscarConta(numero) != -1) {
        cout << "Ja existe uma conta com esse numero." << endl;
        return;
    }

    string nome;
    cout << "Nome do cliente: ";
    getline(cin, nome);
    if (nome == "") {
        cout << "Nome nao pode ser vazio." << endl;
        return;
    }

    string documento;
    cout << "CPF: ";
    getline(cin, documento);
    if (documento == "") {
        cout << "CPF nao pode ser vazio." << endl;
        return;
    }

    int tipo = lerInteiro("Tipo da conta (1 - Corrente, 2 - Poupanca): ");
    if (tipo != 1 && tipo != 2) {
        cout << "Tipo de conta invalido." << endl;
        return;
    }

    double saldoInicial = lerReal("Saldo inicial: R$ ");
    if (saldoInicial < 0) {
        cout << "Saldo inicial nao pode ser negativo." << endl;
        return;
    }

    // Grava a nova conta na próxima posição livre dos arrays
    numeroConta[quantidadeContas] = numero;
    nomeCliente[quantidadeContas] = nome;
    cpf[quantidadeContas] = documento;
    tipoConta[quantidadeContas] = tipo;
    saldo[quantidadeContas] = saldoInicial;
    contaAtiva[quantidadeContas] = true;
    quantidadeContas++;

    cout << "Conta cadastrada com sucesso!" << endl;
}

// -------------------- 2. Listar contas --------------------
void listarContas() {
    cout << "\n=== CONTAS CADASTRADAS ===" << endl;

    if (quantidadeContas == 0) {
        cout << "Nenhuma conta cadastrada." << endl;
        return;
    }

    for (int i = 0; i < quantidadeContas; i++) {
        cout << "----------------------------" << endl;
        exibirDadosConta(i);
    }
    cout << "----------------------------" << endl;
    cout << "Total de contas: " << quantidadeContas << endl;
}

// -------------------- 3. Consultar conta --------------------
void consultarConta() {
    cout << "\n=== CONSULTAR CONTA ===" << endl;

    int numero = lerInteiro("Numero da conta: ");
    int indice = buscarConta(numero);

    if (indice == -1) {
        cout << "Conta nao encontrada." << endl;
        return;
    }
    exibirDadosConta(indice);
}

// -------------------- 4. Depositar --------------------
void depositar() {
    cout << "\n=== DEPOSITO ===" << endl;

    int numero = lerInteiro("Numero da conta: ");
    int indice = buscarConta(numero);

    if (indice == -1) {
        cout << "Conta nao encontrada." << endl;
        return;
    }
    if (!contaAtiva[indice]) {
        cout << "Conta inativa." << endl;
        return;
    }
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
        cout << "Limite de movimentacoes atingido." << endl;
        return;
    }

    double valor = lerReal("Valor do deposito: R$ ");
    if (valor <= 0) {
        cout << "O valor deve ser positivo." << endl;
        return;
    }

    saldo[indice] = saldo[indice] + valor;
    registrarMovimentacao(numeroConta[indice], 'D', valor);

    cout << "Deposito realizado. Novo saldo: R$ " << saldo[indice] << endl;
}

// -------------------- 5. Sacar --------------------
void sacar() {
    cout << "\n=== SAQUE ===" << endl;

    int numero = lerInteiro("Numero da conta: ");
    int indice = buscarConta(numero);

    if (indice == -1) {
        cout << "Conta nao encontrada." << endl;
        return;
    }
    if (!contaAtiva[indice]) {
        cout << "Conta inativa." << endl;
        return;
    }
    if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
        cout << "Limite de movimentacoes atingido." << endl;
        return;
    }

    double valor = lerReal("Valor do saque: R$ ");
    if (valor <= 0) {
        cout << "O valor deve ser positivo." << endl;
        return;
    }
    if (valor > saldo[indice]) {
        cout << "Saldo insuficiente. Saldo atual: R$ " << saldo[indice] << endl;
        return;
    }

    saldo[indice] = saldo[indice] - valor;
    registrarMovimentacao(numeroConta[indice], 'S', valor);

    cout << "Saque realizado. Novo saldo: R$ " << saldo[indice] << endl;
}

// -------------------- 6. Transferir --------------------
void transferir() {
    cout << "\n=== TRANSFERENCIA ===" << endl;

    int numeroOrigem = lerInteiro("Conta de origem: ");
    int indiceOrigem = buscarConta(numeroOrigem);
    if (indiceOrigem == -1) {
        cout << "Conta de origem nao encontrada." << endl;
        return;
    }
    if (!contaAtiva[indiceOrigem]) {
        cout << "Conta de origem inativa." << endl;
        return;
    }

    int numeroDestino = lerInteiro("Conta de destino: ");
    int indiceDestino = buscarConta(numeroDestino);
    if (indiceDestino == -1) {
        cout << "Conta de destino nao encontrada." << endl;
        return;
    }
    if (!contaAtiva[indiceDestino]) {
        cout << "Conta de destino inativa." << endl;
        return;
    }
    if (indiceOrigem == indiceDestino) {
        cout << "Origem e destino devem ser contas diferentes." << endl;
        return;
    }

    // A transferência gera dois registros: é preciso espaço para ambos
    if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
        cout << "Limite de movimentacoes atingido." << endl;
        return;
    }

    double valor = lerReal("Valor da transferencia: R$ ");
    if (valor <= 0) {
        cout << "O valor deve ser positivo." << endl;
        return;
    }
    if (valor > saldo[indiceOrigem]) {
        cout << "Saldo insuficiente na conta de origem. Saldo atual: R$ "
             << saldo[indiceOrigem] << endl;
        return;
    }

    saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
    saldo[indiceDestino] = saldo[indiceDestino] + valor;

    registrarMovimentacao(numeroConta[indiceOrigem], 'S', valor);  // saída
    registrarMovimentacao(numeroConta[indiceDestino], 'D', valor); // entrada

    cout << "Transferencia realizada com sucesso!" << endl;
    cout << "Conta " << numeroConta[indiceOrigem] << " - " << nomeCliente[indiceOrigem]
         << ": R$ " << saldo[indiceOrigem] << endl;
    cout << "Conta " << numeroConta[indiceDestino] << " - " << nomeCliente[indiceDestino]
         << ": R$ " << saldo[indiceDestino] << endl;
}

// -------------------- 7. Extrato --------------------
void exibirExtrato() {
    cout << "\n=== EXTRATO ===" << endl;

    int numero = lerInteiro("Numero da conta: ");
    int indice = buscarConta(numero);

    if (indice == -1) {
        cout << "Conta nao encontrada." << endl;
        return;
    }

    cout << "Conta " << numeroConta[indice] << " - " << nomeCliente[indice] << endl;
    cout << "----------------------------" << endl;

    int encontradas = 0;
    for (int i = 0; i < quantidadeMovimentacoes; i++) {
        if (contaMovimentacao[i] == numero) {
            if (tipoMovimentacao[i] == 'D') {
                cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
            }
            else if (tipoMovimentacao[i] == 'S') {
                cout << "Saque:    R$ " << valorMovimentacao[i] << endl;
            }
            encontradas++;
        }
    }

    if (encontradas == 0) {
        cout << "Nenhuma movimentacao registrada." << endl;
    }
    cout << "----------------------------" << endl;
    cout << "Saldo atual: R$ " << saldo[indice] << endl;
}

// -------------------- Programa principal --------------------
int main() {
    cout << fixed << setprecision(2);

    int opcao;
    do {
        cout << "\n===== SISTEMA BANCARIO =====" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Listar contas" << endl;
        cout << "3 - Consultar conta" << endl;
        cout << "4 - Depositar" << endl;
        cout << "5 - Sacar" << endl;
        cout << "6 - Transferir" << endl;
        cout << "7 - Extrato" << endl;
        cout << "0 - Sair" << endl;
        opcao = lerInteiro("Opcao: ");

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: listarContas(); break;
            case 3: consultarConta(); break;
            case 4: depositar(); break;
            case 5: sacar(); break;
            case 6: transferir(); break;
            case 7: exibirExtrato(); break;
            case 0: cout << "Encerrando o sistema..." << endl; break;
            default: cout << "Opcao invalida." << endl;
        }
    } while (opcao != 0);

    return 0;
}
