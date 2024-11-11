#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls" // define comando para limpar tela no windows
#else
#define CLEAR_SCREEN "clear" // define comando para limpar tela em sistemas unix
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_CLIENTES 100 // número máximo de clientes
#define MAX_NOME 50 // tamanho máximo para o nome do cliente
#define MAX_CPF 12 // tamanho máximo para o cpf do cliente

float total_emprestado = 0; // variável para armazenar o total emprestado

// estrutura de dados para armazenar informações de um cliente
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

typedef struct cliente cliente; // definição de tipo para simplificar uso da estrutura cliente

cliente clientes[MAX_CLIENTES]; // array para armazenar clientes
int num_clientes = 0; // contador de clientes cadastrados

// função para limpar a tela
void limparTela() {
    fflush(stdin); // limpa o buffer de entrada
    char qualquer;
    do
    {
        scanf("%c", &qualquer);
    } while (qualquer != '\n'); // espera o usuário apertar enter
}

// função para esperar o usuário apertar enter
void aguardarEnter()
{
    printf("\x1b[33m\nPressione ENTER para continuar...\x1b[0m");
    limparTela();
}

// função para exibir um cabeçalho
void cabecalho()
{
    for (int i = 0; i < 40; i++)
    {
        printf("\x1b[32m-\x1b[0m");
    }
    printf("\n");
}

// função para realizar um empréstimo para um cliente
void fazerEmprestimo()
{
    int numero_conta;

    printf("Digite o número da conta: ");
    scanf("%i", &numero_conta);

    int indice_cliente = -1; // índice para localizar o cliente

    // procura o cliente com o número da conta informado
    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    // verifica se o cliente foi encontrado
    if (indice_cliente == -1) {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Conta não encontrada...\n");
        limparTela();
        return;
    }

    float valor_emprestimo;
    
    printf("Informe o valor desejado para o emprestimo: ");
    scanf("%f", &valor_emprestimo);

    // verifica se o valor do empréstimo é maior que o limite permitido
    if (valor_emprestimo > 2 * clientes[indice_cliente].saldo)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Valor maior que o seu limite. \x1b[32mInforme um novo valor.\n\x1b[0m");
        limparTela();
        return;
    }

    float soma_saldo = 0;

    // calcula o saldo total de todos os clientes
    for (int i = 0; i < num_clientes; i++)
    {
        soma_saldo += clientes[i].saldo;
    }

    float limite_emprestimo = 0.2 * soma_saldo; // calcula o limite total de empréstimos disponível

    // verifica se o valor do empréstimo ultrapassa o limite geral de empréstimos
    if (valor_emprestimo > limite_emprestimo)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Valor maior que o crédito disponível\n");
        limparTela();
        return;
    }

    printf("\x1b[32mEMPRÉSTIMO EFETUADO!\n\x1b[0m");

    clientes[indice_cliente].saldo += valor_emprestimo; // adiciona o valor do empréstimo ao saldo do cliente

    total_emprestado += valor_emprestimo; // atualiza o total emprestado

    limparTela();
}

// função para fechar a conta de um cliente
void fecharConta()
{
    int numero_conta;

    printf("Digite o número da conta: ");
    scanf("%i", &numero_conta);

    int indice_cliente = -1; // índice para localizar o cliente

    // procura o cliente com o número da conta informado
    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    // verifica se o cliente foi encontrado
    if (indice_cliente == -1)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Conta não encontrada!\n");
    } 
    // verifica se a conta pode ser fechada (saldo zerado)
    else if (clientes[indice_cliente].saldo == 0.0)
    {
        clientes[indice_cliente].status = 'F'; // marca a conta como fechada
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

    int indice_cliente = -1; // índice para localizar o cliente

    // procura o cliente com o número da conta informado
    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    // verifica se o cliente foi encontrado
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

    // verifica se o valor do saque é positivo
    if (valor <= 0)
    {
        cabecalho();
        printf("\x1b[31mATENÇÃO!!\x1b[0m O valor do saque deve ser \x1b[32mpositivo!\n\x1b[0m");
        limparTela();
        return;
    }

    // verifica se o saldo é suficiente para o saque
    if (clientes[indice_cliente].saldo < valor)
    {
        printf("\x1b[31mATENÇÃO!!\x1b[0m Não foi possível realizar o saque, \x1b[31msaldo insuficiente...\n\x1b[0m");
        limparTela();
        return;
    }

    clientes[indice_cliente].saldo -= valor; // realiza o saque do saldo do cliente

    printf("\x1b[32mSaque realizado com sucesso!\x1b[0m Saldo atual: \x1b[32m%.2f\n\x1b[0m", clientes[indice_cliente].saldo);

    limparTela();
}

void fazerDeposito()
{
    int numero_conta;
    float valor;

    printf("Digite o número da conta: ");
    scanf("%d", &numero_conta);

    int indice_cliente = -1; // índice para localizar o cliente

    // procura o cliente com o número da conta informado
    for (int i = 0; i < num_clientes; i++)
    {
        if (clientes[i].numero_conta == numero_conta)
        {
            indice_cliente = i;
            break;
        }
    }

    // verifica se o cliente foi encontrado
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

    // verifica se o valor do depósito é positivo
    if (valor <= 0)
    {
        cabecalho();
        printf("\x1b[31mATENÇÃO!!\x1b[0m O valor do depósito deve ser \x1b[32mpositivo! \n\x1b[0m");
        limparTela();
        return;
    }

    clientes[indice_cliente].saldo += valor; // realiza o depósito no saldo do cliente

    printf("\x1b[32mDepósito realizado com sucesso!\x1b[0m Saldo atual: \x1b[32m%.2f\n\x1b[0m", clientes[indice_cliente].saldo);

    limparTela();
}
void inserirCliente()
{
    if (num_clientes >= MAX_CLIENTES) // verifica se o número máximo de clientes foi atingido
    {
        printf("\x1b[31mNúmero máximo de clientes atingido.\n\x1b[0m");
        return;
    }

    cliente novoCliente;

    printf("Digite o nome completo \x1b[31m(max %i caracteres)\x1b[0m: ", MAX_NOME);
    scanf(" %50[^\n]", novoCliente.nome); // lê o nome do cliente

    printf("Digite a idade: ");
    scanf("%i", &(novoCliente.idade)); // lê a idade do cliente
    getchar();

    if (novoCliente.idade < 18) // verifica se o cliente é maior de idade
    {
        printf("\x1b[31mATENÇÃO!\x1b[0m Cliente precisa ser maior de idade!\n");
        return;
    }

    printf("Digite o CPF: ");
    scanf("%11[^\n]", novoCliente.cpf); // lê o CPF do cliente

    // verifica se o CPF já está cadastrado
    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].cpf, novoCliente.cpf) == 0) {
            if (clientes[i].status == 'F') { // reabre conta se o cliente já foi excluído
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
    scanf("%d", &novoCliente.conta); // escolhe o tipo de conta

    // verifica se o tipo de conta é válido
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

    novoCliente.numero_conta = rand() % 1000000; // gera um número aleatório para a conta
    novoCliente.status = 'A'; // define que a conta está ativa
    novoCliente.saldo = 0.0; // define o saldo inicial da conta

    clientes[num_clientes] = novoCliente; // adiciona o cliente à lista
    num_clientes++; // aumenta o número de clientes

    printf("\x1b[32mConta criada!\x1b[0m Número da conta: %i\n", novoCliente.numero_conta);

    limparTela();
}

void listarClientes() {
    if (num_clientes == 0) // verifica se não há clientes cadastrados
    {
        printf("\x1b[31mNenhum cliente cadastrado! \n\x1b[0m");
        limparTela();
        return;
    }

    printf("\x1b[35mLista de Clientes:\n\x1b[0m");
    // imprime cabeçalho da tabela
    printf("\x1b[34m| %-4s | %-20s | %-5s | %-12s | %-15s | %-7s | %-6s | %-6s |\n",
           "Num", "Nome", "Idade", "CPF", "Tipo de Conta", "Status", "Saldo", "Nº Conta");
    printf("|------|----------------------|-------|--------------|-----------------|---------|--------|--------|\n\x1b[0m");

    // imprime a lista de clientes
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
        system(CLEAR_SCREEN); // limpa a tela
        cabecalho();
        printf("\x1b[32m       SEJA BEM VINDO AO CFinance!\n\x1b[0m");
        cabecalho();

        // imprime o menu com as opções
        printf("\x1b[36m1 | \x1b[0mAbrir Conta\n");
        printf("\x1b[36m2 | \x1b[0mListar Clientes\n");
        printf("\x1b[36m3 | \x1b[0mFazer Depósito\n");
        printf("\x1b[36m4 | \x1b[0mFazer Saque\n");
        printf("\x1b[36m5 | \x1b[0mFechar Conta\n");
        printf("\x1b[36m6 | \x1b[0mFazer Empréstimo\n");
        printf("\x1b[36m0 | \x1b[0mSair\n");

        printf("\nDigite uma opção: ");

        int opcao;
        scanf("%i", &opcao); // lê a opção do menu

        // executa a ação conforme a opção escolhida
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
    SetConsoleOutputCP(65001); // configura a codificação de caracteres no Windows
#endif

    menu(); // chama o menu principal.

    return 0;
}