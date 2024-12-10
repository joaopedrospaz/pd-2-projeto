#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum
{
    SERVICOS_GERAIS,
    ADMINISTRACAO,
    PSICOLOGIA,
    ASSISTENCIA_SOCIAL
} Departamentos;
struct funcionario
{
    char rg[11];
    char cpf[12];
    char nome[50];
    char telefone[15];
    char endereco[50];
    char cidade[50];
    char estado[50];
    float salario;
    Departamentos departamento;
};

void seed_funcionarios(FILE *pont_arq)
{
    fprintf(pont_arq, "1234567890,98765432100,João Silva,912345678,Rua A,Cidade X,Estado Y,3000.00,ADMINISTRACAO\n");
    fprintf(pont_arq, "6789012340,12345678900,Maria Oliveira,919876543,Rua B,Cidade Y,Estado Z,3500.00,PSICOLOGIA\n");
    fprintf(pont_arq, "3334343430,33445566700,José Santos,917654321,Rua E,Cidade Y,Estado Z,5000.00,SERVICOS_GERAIS\n");
}

char *number_to_str_departamento(int n, int type)
{
    if (type == 0)
    {

        switch (n)
        {
        case 0:
            return "Serviços Gerais";
        case 1:
            return "Administração";
        case 2:
            return "Psicologia";
        case 3:
            return "Assistência Geral";
        default:
            return "Serviços Gerais";
        }
    }
    if (type == 1)
    {

        switch (n)
        {
        case 0:
            return "SERVICOS_GERAIS";
        case 1:
            return "ADMINISTRACAO";
        case 2:
            return "PSICOLOGIA";
        case 3:
            return "Assistência Geral";
        default:
            return "SERVICOS_GERAIS";
        }
    }
}
Departamentos str_to_departamento(char *dep_str)
{
    if (strcmp(dep_str, "SERVICOS_GERAIS") == 0)
        return SERVICOS_GERAIS;
    else if (strcmp(dep_str, "ADMINISTRACAO") == 0)
        return ADMINISTRACAO;
    else if (strcmp(dep_str, "PSICOLOGIA") == 0)
        return PSICOLOGIA;
    else if (strcmp(dep_str, "ASSISTENCIA_SOCIAL") == 0)
        return ASSISTENCIA_SOCIAL;
    else
        return SERVICOS_GERAIS; // Retorno padrão (ou um valor que faça sentido para casos inválidos)
}
void find_all(FILE *pont_arq, struct funcionario *funcionarios, int *qtd)
{
    char dep_str[50];

    while (fscanf(pont_arq, " %10[^,], %11[^,], %49[^,], %14[^,], %49[^,], %49[^,], %49[^,], %f, %49[^\n]",
                  funcionarios[*qtd].rg,
                  funcionarios[*qtd].cpf,
                  funcionarios[*qtd].nome,
                  funcionarios[*qtd].telefone,
                  funcionarios[*qtd].endereco,
                  funcionarios[*qtd].cidade,
                  funcionarios[*qtd].estado,
                  &funcionarios[*qtd].salario,
                  dep_str) == 9)
    {
        funcionarios[*qtd].departamento = str_to_departamento(dep_str);
        (*qtd)++;
    }
}

void consulta(int qtd, struct funcionario *funcionarios)
{
    printf("\nLista de Funcionários:\n");
    for (int i = 0; i < qtd; i++)
    {
        printf("\nNome: %s\n", funcionarios[i].nome);
        printf("RG: %s\n", funcionarios[i].rg);
        printf("\n------------------------------------\n");
    }
}
int digitos_invalidos(char *campo)
{
    while (*campo)
    {
        if (!isdigit(*campo))
        {
            return 1;
        }
        campo++;
    }
    return 0;
}
char *verifica_campo(int tipo)
{
    char *campo[30];
    if (tipo == 1)
    {
        char rg[11];
        printf("Digite o RG: ");
        scanf("%s", rg);
        while (1)
        {
            if (strlen(rg) != 10 || digitos_invalidos(rg))
            {
                printf("RG inválido\n");
                printf("Digite o RG novamente: ");
                scanf("%s", rg);
            }
            else
            {
                break;
            }
        }
        *campo = rg;
    }

    if (tipo == 2)
    {
        char cpf[12];
        printf("Digite o CPF: ");
        scanf(" %[^\n]", cpf);
        while (1)
        {
            if (strlen(cpf) != 11 || digitos_invalidos(cpf))
            {
                printf("CPF inválido\n");
                printf("Digite o CPF novamente: ");
                scanf(" %[^\n]", cpf);
            }
            else
            {
                break;
            }
        }
        *campo = cpf;
    }

    if (tipo == 3)
    {
        char nome[30];
        printf("Digite o Nome: ");
        scanf(" %[^\n]", nome);
        while (1)
        {
            if (strlen(nome) < 4)
            {
                printf("Nome inválido\n");
                printf("Digite o Nome novamente: ");
                scanf(" %[^\n]", nome);
            }
            else
            {
                break;
            }
        }
        *campo = nome;
    }

    if (tipo == 4)
    {
        char telefone[15];
        printf("Digite o Telefone: ");
        scanf(" %[^\n]", telefone);
        while (1)
        {
            if (strlen(telefone) < 10 || digitos_invalidos(telefone))
            {
                printf("Telefone inválido\n");
                printf("Digite o Telefone novamente: ");
                scanf(" %[^\n]", telefone);
            }
            else
            {
                break;
            }
        }
        *campo = telefone;
    }
    return *campo;
}
void consulta_detalhada(int qtd, struct funcionario *funcionarios)
{
    int modo, index = -1;
    char *campo[30];
    {
        printf("Escolha o modo de consulta:\n");
        printf("1. Por RG\n");
        printf("2. Por CPF\n");
        printf("3. Por nome\n");
        printf("Escolha uma opção: ");
        scanf("%d", &modo);
    }
    if (modo == 1)
    {
        *campo = verifica_campo(1);
        for (int i = 0; i < qtd; i++)
            if (strcmp(*campo, funcionarios[i].rg) == 0)
            {
                index = i;
            }
    }
    if (modo == 2)
    {
        *campo = verifica_campo(2);
        for (int i = 0; i < qtd; i++)
            if (strcmp(*campo, funcionarios[i].cpf) == 0)
            {
                index = i;
            }
    }
    if (modo == 3)
    {
        *campo = verifica_campo(3);
        for (int i = 0; i < qtd; i++)
            if (strcmp(*campo, funcionarios[i].nome) == 0)
            {
                index = i;
            }
    }
    if (index == -1)
    {
        printf("Usuário não encontrado");
    }
    else
    {

        printf("Funcionário econtrado:\n\n");
        printf("Nome: %s\n", funcionarios[index].nome);
        printf("RG: %s\n", funcionarios[index].rg);
        printf("Telefone: %s\n", funcionarios[index].telefone);
        printf("CPF: %s\n", funcionarios[index].cpf);
        printf("Endereço: %s\n", funcionarios[index].endereco);
        printf("Cidade: %s\n", funcionarios[index].cidade);
        printf("Estado: %s\n", funcionarios[index].estado);
        printf("Salário: %.2f\n", funcionarios[index].salario);
        printf("Departamento: %s\n", number_to_str_departamento(funcionarios[index].departamento, 0));
    }
}
void cadastro(int *qtd, struct funcionario *funcionarios)
{

    strcpy(funcionarios[*qtd].nome, verifica_campo(3));

    strcpy(funcionarios[*qtd].cpf, verifica_campo(2));

    strcpy(funcionarios[*qtd].telefone, verifica_campo(4));

    printf("Digite o endereço: ");
    scanf(" %[^\n]", funcionarios[*qtd].endereco);

    printf("Digite a cidade: ");
    scanf(" %[^\n]", funcionarios[*qtd].cidade);

    printf("Digite o estado: ");
    scanf(" %[^\n]", funcionarios[*qtd].estado);

    strcpy(funcionarios[*qtd].rg, verifica_campo(1));

    printf("Digite o salário: ");
    scanf("%f", &funcionarios[*qtd].salario);

    int dep;
    printf("Escolha o departamento (0 - Serviços Gerais, 1 - Administração, 2 - Psicologia, 3 - Assistência Social): ");
    scanf("%d", &dep);
    funcionarios[*qtd].departamento = dep;
    (*qtd)++;
    printf("Funcionário cadastrado com sucesso\n");
}
void atualizar(int qtd, struct funcionario *funcionarios)
{
    printf("Digite apenas os números do RG do funcionário que deseja atualizar");
    char *campo = verifica_campo(1);
    for (int i = 0; i < qtd; i++)
    {
        if (strcmp(funcionarios[i].rg, campo) == 0)
        {
            strcpy(funcionarios[i].nome, verifica_campo(3));

            strcpy(funcionarios[i].cpf, verifica_campo(2));

            strcpy(funcionarios[i].telefone, verifica_campo(4));

            printf("Digite o endereço: ");
            scanf(" %[^\n]", funcionarios[i].endereco);

            printf("Digite a cidade: ");
            scanf(" %[^\n]", funcionarios[i].cidade);

            printf("Digite o estado: ");
            scanf(" %[^\n]", funcionarios[i].estado);

            strcpy(funcionarios[i].rg, verifica_campo(1));

            printf("Digite o salário: ");
            scanf("%f", &funcionarios[i].salario);

            int dep;
            printf("Escolha o departamento (0 - Serviços Gerais, 1 - Administração, 2 - Psicologia, 3 - Assistência Social): ");
            scanf("%d", &dep);
            funcionarios[i].departamento = dep;
            printf("Funcionário atualizado com sucesso!");
            break;
        }
    }
    printf("Usuário não encontrado.");
}
void salvar(int qtd, struct funcionario *funcionarios)
{
    FILE *pont_arq;
    pont_arq = fopen("funcionarios.txt", "w");
    for (int i = 0; i < qtd; i++)
    {
        fprintf(pont_arq, "%s,%s,%s,%s,%s,%s,%s,%.2f,%s\n",
                funcionarios[i].rg,
                funcionarios[i].cpf,
                funcionarios[i].nome,
                funcionarios[i].telefone,
                funcionarios[i].endereco,
                funcionarios[i].cidade,
                funcionarios[i].estado,
                funcionarios[i].salario,
                number_to_str_departamento(funcionarios[i].departamento, 1));
    }
    fclose(pont_arq);
}
void deletar(int *qtd, struct funcionario *funcionarios)
{
    printf("Digite apenas os números do RG do funcionário que deseja deletar");
    char *campo = verifica_campo(1);
    for (int i = 0; i < *qtd; i++)
    {
        if (strcmp(funcionarios[i].rg, campo) == 0)
        {
            printf("Funcionário econtrado:\n\n");
            printf("Nome: %s\n", funcionarios[i].nome);
            printf("RG: %s\n", funcionarios[i].rg);
            printf("Telefone: %s\n", funcionarios[i].telefone);
            printf("CPF: %s\n", funcionarios[i].cpf);
            printf("Endereço: %s\n", funcionarios[i].endereco);
            printf("Cidade: %s\n", funcionarios[i].cidade);
            printf("Estado: %s\n", funcionarios[i].estado);
            printf("Salário: %.2f\n", funcionarios[i].salario);
            printf("Departamento: %s\n\n", number_to_str_departamento(funcionarios[i].departamento, 0));

            int confirmacao;
            printf("\n\ntem certeza que deseja excluir o funcionário ?\n");
            printf("1. Sim\n2.Não\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &confirmacao);
            if (confirmacao == 1)
            {

                for (int j = i; j < *qtd - 1; j++)
                {

                    funcionarios[j] = funcionarios[j + 1];
                }
                printf("Funcionário removido com sucesso!");
                *qtd = *qtd - 1;
                break;
            }
        }
    }
    printf("\nUsuário não encontrado.");
}

void menu(int *qtd, struct funcionario *funcionarios)
{
    int opcao = 0;

    while (opcao != 6)
    {
        printf("\n********* Quadro de Funcionários *********\n");
        printf("Opções:\n");
        printf("1. Cadastrar novo funcionário\n");
        printf("2. Mostrar todos os funcionários\n");
        printf("3. Realizar busca detalhada\n");
        printf("4. Atualizar funcionário\n");
        printf("5. Excluir um funcionário\n");
        printf("6. Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastro(qtd, funcionarios);
            break;
        case 2:
            consulta(*qtd, funcionarios);
            break;
        case 3:
            consulta_detalhada(*qtd, funcionarios);
            break;
        case 4:
            atualizar(*qtd, funcionarios);
            break;
        case 5:
            deletar(qtd, funcionarios);
            break;
        case 6:
            salvar(*qtd, funcionarios);
            break;
        default:
            printf("Opção inválida.\n");
        }
    }
}

int main()
{
    int qtd_funcionarios = 0;
    struct funcionario funcionarios[100];

    FILE *pont_arq;
    pont_arq = fopen("funcionarios.txt", "r");

    if (pont_arq == NULL)
    {
        pont_arq = fopen("funcionarios.txt", "w");
        seed_funcionarios(pont_arq);
        fclose(pont_arq);
        pont_arq = fopen("funcionarios.txt", "r");
    }
    find_all(pont_arq, funcionarios, &qtd_funcionarios);
    fclose(pont_arq);

    menu(&qtd_funcionarios, funcionarios);
}
