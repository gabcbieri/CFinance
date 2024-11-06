#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_CLIENTES 100
#define MAX_NOME 50
#define MAX_CPF 12

float total_emprestado = 0;

struct cliente
{
    char nome[MAX_NOME + 1];
    int idade;
    char cpf[MAX_CPF + 1];
    int conta;
    int numero_conta;
    int conta_corrente;
    int conta_poupanca;
    float saldo;
    char status;
};

typedef struct cliente cliente;

cliente clientes[MAX_CLIENTES];
int num_clientes = 0;

void limparTela() {
    fflush(stdin);
    char qualquer;
    do
    {
        scanf("%c", &qualquer);
    } while (qualquer != '\n');
}

void aguardarEnter()
{
    printf("\x1b[33m\nPressione ENTER para continuar...\x1b[0m");

    limparTela();
}

void cabecalho()
{
    for (int i = 0; i < 40; i++)
    {
        printf("\x1b[32m-\x1b[0m");
    }
    printf("\n");
}

void fazerEmprestimo()
{

    int numero_conta;

    printf("Digite o número da conta: ");
    scanf("%i", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }
      if (indice_cliente == -1) {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Conta não encontrada...\n");
        limparTela();
        return;
    }


    float valor_emprestimo;
    
    printf("Informe o valor desejado para o emprestimo: ");
    scanf("%f", &valor_emprestimo);

    if (valor_emprestimo > 2 * clientes[indice_cliente].saldo)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Valor maior que o seu limite. \x1b[32mInforme um novo valor.\n\x1b[0m");
        limparTela();
        return;
    }

    float soma_saldo = 0;

    for (int i = 0; i < num_clientes; i++)
    {
        soma_saldo += clientes[i].saldo;
    }

    float limite_emprestimo = 0.2 * soma_saldo;

    if (valor_emprestimo > limite_emprestimo)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Valor maior que o crédito disponível\n");
        limparTela();
        return;
    }

    printf("\x1b[32mEMPRÉSTIMO EFETUADO!\n\x1b[0m");

    clientes[indice_cliente].saldo += valor_emprestimo;

    total_emprestado += valor_emprestimo;

    limparTela();
}

void fecharConta()
{

    int numero_conta;

    printf("Digite o número da conta: ");
    scanf("%i", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }
    if (indice_cliente == -1)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Conta não encontrada!\n");
    } else if (clientes[indice_cliente].saldo == 0.0)
    {
        clientes[indice_cliente].status = 'F';
        printf("\x1b[32mConta fechada com sucesso!\x1b[0m\n");
    }
    else
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m É necessário \x1b[31mesvaziar\x1b[0m a conta antes de fechá-la!\n");
    }

    limparTela();
}

void fazerSaque()
{
    int numero_conta;
    float valor;

    printf("Digite o número da conta: ");
    scanf("%d", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    if (indice_cliente == -1)
    {
        cabecalho();
        printf("\x1b[31mATENÇÃO!!\x1b[0m Conta não encontrada! \n");
        limparTela();
        return;
    }

    cabecalho();
    printf("Digite o valor a ser sacado: ");
    scanf("%f", &valor);

    if (valor <= 0)
    {
        cabecalho();
        printf("\x1b[31mATENÇÃO!!\x1b[0m O valor do saque deve ser \x1b[32mpositivo!\n\x1b[0m");
        limparTela();
        return;
    }

    if (clientes[indice_cliente].saldo < valor)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Não foi possível realizar o saque, \x1b[31msaldo insuficiente...\n\x1b[0m");
        limparTela();
        return;
    }

    clientes[indice_cliente].saldo -= valor;

    printf("\x1b[32mSaque realizado com sucesso!\x1b[0m Saldo atual: \x1b[32m%.2f\n\x1b[0m", clientes[indice_cliente].saldo);

    limparTela();
}

void fazerDeposito()
{
    int numero_conta;
    float valor;

    printf("Digite o número da conta: ");
    scanf("%d", &numero_conta);

    int indice_cliente = -1;

    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    if (indice_cliente == -1)
    {
        cabecalho();
        printf("\x1b[31mATENÇÂO!!\x1b[0m Conta não encontrada! \n");
        limparTela();
        return;
    }

    cabecalho();
    printf("Digite o valor a ser depositado: ");
    scanf("%f", &valor);

    if (valor <= 0)
    {
        cabecalho();
        printf("\x1b[31mATENÇÃO!!\x1b[0m O valor do depósito deve ser \x1b[32mpositivo! \n\x1b[0m");
        limparTela();
        return;
    }

    clientes[indice_cliente].saldo += valor;

    printf("\x1b[32mDepósito realizado com sucesso!\x1b[0m Saldo atual: \x1b[32m%.2f\n\x1b[0m", clientes[indice_cliente].saldo);

    limparTela();
}

void inserirCliente()
{
    if (num_clientes >= MAX_CLIENTES)
    {
        printf("\x1b[31mNúmero máximo de clientes atingido.\n\x1b[0m");
        return;
    }

    cliente novoCliente;

    printf("Digite o nome completo \x1b[31m(max %i caracteres)\x1b[0m: ", MAX_NOME);
    scanf(" %50[^\n]", novoCliente.nome);

    printf("Digite a idade: ");
    scanf("%i", &(novoCliente.idade));
    getchar();

    if (novoCliente.idade < 18)
    {
        printf("\x1b[31mATENÇÃO!\x1b[0m Cliente precisa ser maior de idade!\n");
        return;
    }

    printf("Digite o CPF: ");
    scanf("%11[^\n]", novoCliente.cpf);

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, novoCliente.cpf) == 0) {
            if (clientes[i].status == 'F') {
                clientes[i].status = 'A';
                printf("\x1b[32mConta reaberta com sucesso!\x1b[0m Número da conta: %i\n", clientes[i].numero_conta);
                limparTela();
                return;
            } else {
                printf("\x1b[31mATENÇÃO!\x1b[0m Cliente ja cadastrado!\n");
                limparTela();
                return;
            }
        }
    }

    cabecalho();
    printf("\x1b[36m1 | \x1b[0mConta Corrente\n");
    printf("\x1b[36m2 | \x1b[0mConta Poupanca\n");
    cabecalho();
    printf("\nEscolha o tipo da Conta: ");
    scanf("%d", &novoCliente.conta);

    if (novoCliente.conta == 1)
    {
        novoCliente.conta = 1;
    }
    else if (novoCliente.conta == 2)
    {
        novoCliente.conta = 2;
    }
    else
    {
        printf("\x1b[31mERRO!!\x1b[0m Tipo de conta invalida!\n");
        limparTela();
        return;
    }

    novoCliente.numero_conta = rand() % 1000000;
    novoCliente.status = 'A';
    novoCliente.saldo = 0.0;

    clientes[num_clientes] = novoCliente;
    num_clientes++;

    printf("\x1b[32mConta criada!\x1b[0m Número da conta: %i\n", novoCliente.numero_conta);

    limparTela();
}

void listarClientes() {
    if (num_clientes == 0)
    {
        printf("\x1b[31mNenhum cliente cadastrado! \n\x1b[0m");
        limparTela();
        return;
    }

    printf("\x1b[35mLista de Clientes:\n\x1b[0m");
    printf("\x1b[34m| %-4s | %-20s | %-5s | %-12s | %-15s | %-7s | %-6s | %-6s |\n",
           "Num", "Nome", "Idade", "CPF", "Tipo de Conta", "Status", "Saldo", "Nº Conta");
    printf("|------|----------------------|-------|--------------|-----------------|---------|--------|--------|\n\x1b[0m");

    for (int i = 0; i < num_clientes; i++)
    {
        printf("\x1b[34m| %-4d | %-20s | %-5d | %-12s | %-15s | %-7c | %-6.2f | %-6d |\n\x1b[0m",
               i + 1, clientes[i].nome, clientes[i].idade, clientes[i].cpf,
               clientes[i].conta == 1 ? "Conta Corrente" : "Conta Poupança ",
               clientes[i].status, clientes[i].saldo, clientes[i].numero_conta);
    }

    limparTela();
}

int menu()
{
    while (1)
    {
        system(CLEAR_SCREEN);
        cabecalho();
        printf("\x1b[32m       SEJA BEM VINDO AO C-WALLET\n\x1b[0m");
        cabecalho();

        printf("\x1b[36m1 | \x1b[0mAbrir Conta\n");
        printf("\x1b[36m2 | \x1b[0mListar Clientes\n");
        printf("\x1b[36m3 | \x1b[0mFazer Depósito\n");
        printf("\x1b[36m4 | \x1b[0mFazer Saque\n");
        printf("\x1b[36m5 | \x1b[0mFechar Conta\n");
        printf("\x1b[36m6 | \x1b[0mFazer Empréstimo\n");
        printf("\x1b[36m0 | \x1b[0mSair\n");

        printf("\nDigite uma opção: ");

        int opcao;
        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            inserirCliente();
            aguardarEnter();
            break;
        case 2:
            listarClientes();
            aguardarEnter();
            break;
        case 3:
            fazerDeposito();
            aguardarEnter();
            break;
        case 4:
            fazerSaque();
            aguardarEnter();
            break;
        case 5:
            fecharConta();
            aguardarEnter();
            break;
        case 6:
            fazerEmprestimo();
            aguardarEnter();
            break;
        case 0:
            return 0;

        default:
            printf("\x1b[31mOpção inválida!!\n\x1b[0m");
            limparTela();
            aguardarEnter();
            break;
        }
    }
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    menu();

    return 0;
}