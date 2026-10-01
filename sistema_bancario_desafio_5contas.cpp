#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// ============ DESAFIO DA ETAPA 1: ATE 5 CONTAS ============
// Pergunta do trabalho: "Se quisessemos cadastrar de ate 5 contas,
// qual solucao seria possivel?"
//
// RESPOSTA: como a Etapa 1 ainda nao trabalha com structs nem arrays de
// registros, a solucao mais simples dentro do conteudo ja visto e usar
// ARRAYS PARALELOS: um array para cada atributo (numeroConta[], nomeCliente[],
// cpf[], tipoConta[], saldo[], contaAtiva[]), todos com tamanho fixo 5,
// onde a posicao "i" de cada array representa os dados da mesma conta.
// Um contador (totalContas) controla quantas posicoes ja foram preenchidas.
// Essa abordagem antecipa o conteudo de arrays, mas sem usar structs/funcoes,
// mantendo a proposta de evolucao gradual do sistema.
// ============================================================

const int MAX_CONTAS = 5;

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // ---- Arrays paralelos: cada indice = uma conta ----
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];

    int totalContas = 0; // quantas contas ja foram cadastradas (0 a 5)
    int opcao = 0;

    do {
        cout << "\n********************************\n";
        cout << "**   BANCO INF101 (ate 5 contas) **\n";
        cout << "********************************\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Consultar conta\n";
        cout << "3 - Verificar saldo\n";
        cout << "4 - Alterar tipo da conta\n";
        cout << "5 - Ativar/Desativar conta\n";
        cout << "6 - Sair\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) {
            cout << "Entrada invalida! Digite um numero.\n";
            limparBuffer();
            continue;
        }

        switch (opcao) {

        case 1: { // ---------------- CADASTRAR CONTA ----------------
            if (totalContas >= MAX_CONTAS) {
                cout << "Limite de " << MAX_CONTAS << " contas atingido!\n";
                break;
            }

            int i = totalContas; // proxima posicao livre

            do {
                cout << "Numero da conta: ";
                if (!(cin >> numeroConta[i])) {
                    cout << "Valor invalido!\n";
                    limparBuffer();
                    numeroConta[i] = 0;
                    continue;
                }
                if (numeroConta[i] <= 0)
                    cout << "O numero da conta deve ser maior que zero.\n";
            } while (numeroConta[i] <= 0);

            limparBuffer();

            cout << "Nome do titular: ";
            getline(cin, nomeCliente[i]);

            cout << "CPF do titular: ";
            getline(cin, cpf[i]);

            do {
                cout << "Tipo da conta (1-Corrente / 2-Poupanca): ";
                if (!(cin >> tipoConta[i])) {
                    cout << "Valor invalido!\n";
                    limparBuffer();
                    tipoConta[i] = 0;
                    continue;
                }
                if (tipoConta[i] != 1 && tipoConta[i] != 2)
                    cout << "Tipo invalido! Digite 1 ou 2.\n";
            } while (tipoConta[i] != 1 && tipoConta[i] != 2);

            do {
                cout << "Saldo inicial: ";
                if (!(cin >> saldo[i])) {
                    cout << "Valor invalido!\n";
                    limparBuffer();
                    saldo[i] = -1;
                    continue;
                }
                if (saldo[i] < 0)
                    cout << "O saldo inicial nao pode ser negativo.\n";
            } while (saldo[i] < 0);

            contaAtiva[i] = true;
            totalContas++;

            cout << "\nConta cadastrada com sucesso na posicao " << i << "!\n";
            break;
        }

        case 2: { // ---------------- CONSULTAR CONTA ----------------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            int busca;
            cout << "Digite o numero da conta a consultar: ";
            cin >> busca;

            bool encontrou = false;
            for (int i = 0; i < totalContas; i++) {
                if (numeroConta[i] == busca) {
                    encontrou = true;
                    cout << "\n----- Dados da conta -----\n";
                    cout << "Numero da conta : " << numeroConta[i] << "\n";
                    cout << "Titular         : " << nomeCliente[i] << "\n";
                    cout << "CPF             : " << cpf[i] << "\n";
                    cout << "Tipo da conta   : " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << "\n";
                    cout << "Saldo           : R$ " << fixed << setprecision(2) << saldo[i] << "\n";
                    cout << "Status          : " << (contaAtiva[i] ? "Ativa" : "Inativa") << "\n";
                    break;
                }
            }
            if (!encontrou)
                cout << "Conta nao encontrada.\n";
            break;
        }

        case 3: { // ---------------- VERIFICAR SALDO ----------------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            int busca;
            cout << "Digite o numero da conta: ";
            cin >> busca;

            bool encontrou = false;
            for (int i = 0; i < totalContas; i++) {
                if (numeroConta[i] == busca) {
                    encontrou = true;
                    if (!contaAtiva[i])
                        cout << "Conta inativa! Nao e possivel consultar o saldo.\n";
                    else
                        cout << "Saldo atual: R$ " << fixed << setprecision(2) << saldo[i] << "\n";
                    break;
                }
            }
            if (!encontrou)
                cout << "Conta nao encontrada.\n";
            break;
        }

        case 4: { // ---------------- ALTERAR TIPO DA CONTA ----------------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            int busca;
            cout << "Digite o numero da conta: ";
            cin >> busca;

            bool encontrou = false;
            for (int i = 0; i < totalContas; i++) {
                if (numeroConta[i] == busca) {
                    encontrou = true;
                    if (!contaAtiva[i]) {
                        cout << "Conta inativa! Nao e possivel alterar o tipo.\n";
                        break;
                    }
                    int novoTipo;
                    do {
                        cout << "Novo tipo (1-Corrente / 2-Poupanca): ";
                        if (!(cin >> novoTipo)) {
                            cout << "Valor invalido!\n";
                            limparBuffer();
                            novoTipo = 0;
                            continue;
                        }
                        if (novoTipo != 1 && novoTipo != 2)
                            cout << "Tipo invalido! Digite 1 ou 2.\n";
                    } while (novoTipo != 1 && novoTipo != 2);
                    tipoConta[i] = novoTipo;
                    cout << "Tipo da conta atualizado com sucesso!\n";
                    break;
                }
            }
            if (!encontrou)
                cout << "Conta nao encontrada.\n";
            break;
        }

        case 5: { // ---------------- ATIVAR/DESATIVAR CONTA ----------------
            if (totalContas == 0) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            int busca;
            cout << "Digite o numero da conta: ";
            cin >> busca;

            bool encontrou = false;
            for (int i = 0; i < totalContas; i++) {
                if (numeroConta[i] == busca) {
                    encontrou = true;
                    contaAtiva[i] = !contaAtiva[i];
                    cout << "Conta agora esta " << (contaAtiva[i] ? "ATIVA." : "INATIVA.") << "\n";
                    break;
                }
            }
            if (!encontrou)
                cout << "Conta nao encontrada.\n";
            break;
        }

        case 6:
            cout << "Encerrando o sistema. Ate logo!\n";
            break;

        default:
            cout << "Opcao invalida! Escolha uma opcao de 1 a 6.\n";
            break;
        }

    } while (opcao != 6);

    return 0;
}
