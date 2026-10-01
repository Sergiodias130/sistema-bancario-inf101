#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// ===================== SISTEMA BANCARIO - ETAPA 1 =====================
// INF101 - Programacao de Computadores I
// Cadastro e gestao de UMA conta bancaria usando apenas variaveis
// individuais (sem arrays, sem structs, sem funcoes), conforme pede a Etapa 1.
// ========================================================================

// Limpa o buffer de entrada apos falha ou apos usar cin >>
void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // ---- Variaveis obrigatorias da conta ----
    int numeroConta = 0;
    string nomeCliente = "";
    string cpf = "";
    int tipoConta = 0;      // 1 = Corrente; 2 = Poupanca
    double saldo = 0.0;
    bool contaAtiva = false;

    // Controle: indica se ja existe uma conta cadastrada nesta execucao
    bool contaCadastrada = false;

    int opcao = 0;

    do {
        // ---------------- MENU ----------------
        cout << "\n********************************\n";
        cout << "**       BANCO INF101         **\n";
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
            if (contaCadastrada) {
                cout << "Ja existe uma conta cadastrada nesta versao (Etapa 1 "
                        "trabalha com uma unica conta).\n";
                break;
            }

            // Numero da conta (deve ser > 0)
            do {
                cout << "Numero da conta: ";
                if (!(cin >> numeroConta)) {
                    cout << "Valor invalido!\n";
                    limparBuffer();
                    numeroConta = 0;
                    continue;
                }
                if (numeroConta <= 0)
                    cout << "O numero da conta deve ser maior que zero.\n";
            } while (numeroConta <= 0);

            limparBuffer();

            // Nome do titular
            cout << "Nome do titular: ";
            getline(cin, nomeCliente);

            // CPF
            cout << "CPF do titular: ";
            getline(cin, cpf);

            // Tipo da conta (1 ou 2)
            do {
                cout << "Tipo da conta (1-Corrente / 2-Poupanca): ";
                if (!(cin >> tipoConta)) {
                    cout << "Valor invalido!\n";
                    limparBuffer();
                    tipoConta = 0;
                    continue;
                }
                if (tipoConta != 1 && tipoConta != 2)
                    cout << "Tipo invalido! Digite 1 ou 2.\n";
            } while (tipoConta != 1 && tipoConta != 2);

            // Saldo inicial (nao pode ser negativo)
            do {
                cout << "Saldo inicial: ";
                if (!(cin >> saldo)) {
                    cout << "Valor invalido!\n";
                    limparBuffer();
                    saldo = -1;
                    continue;
                }
                if (saldo < 0)
                    cout << "O saldo inicial nao pode ser negativo.\n";
            } while (saldo < 0);

            contaAtiva = true;
            contaCadastrada = true;

            cout << "\nConta cadastrada com sucesso!\n";
            break;
        }

        case 2: { // ---------------- CONSULTAR CONTA ----------------
            if (!contaCadastrada) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            cout << "\n----- Dados da conta -----\n";
            cout << "Numero da conta : " << numeroConta << "\n";
            cout << "Titular         : " << nomeCliente << "\n";
            cout << "CPF             : " << cpf << "\n";
            cout << "Tipo da conta   : " << (tipoConta == 1 ? "Corrente" : "Poupanca") << "\n";
            cout << "Saldo           : R$ " << fixed << setprecision(2) << saldo << "\n";
            cout << "Status          : " << (contaAtiva ? "Ativa" : "Inativa") << "\n";
            break;
        }

        case 3: { // ---------------- VERIFICAR SALDO ----------------
            if (!contaCadastrada) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            if (!contaAtiva) {
                cout << "Conta inativa! Nao e possivel consultar o saldo.\n";
                break;
            }
            cout << "Saldo atual: R$ " << fixed << setprecision(2) << saldo << "\n";
            break;
        }

        case 4: { // ---------------- ALTERAR TIPO DA CONTA ----------------
            if (!contaCadastrada) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            if (!contaAtiva) {
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

            tipoConta = novoTipo;
            cout << "Tipo da conta atualizado com sucesso!\n";
            break;
        }

        case 5: { // ---------------- ATIVAR/DESATIVAR CONTA ----------------
            if (!contaCadastrada) {
                cout << "Nenhuma conta cadastrada ainda.\n";
                break;
            }
            contaAtiva = !contaAtiva;
            cout << "Conta agora esta " << (contaAtiva ? "ATIVA." : "INATIVA.") << "\n";
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
