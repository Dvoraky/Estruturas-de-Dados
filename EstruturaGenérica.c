#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoas
{
    int tipo;
    void *item;
    struct pessoas *prox;
    struct pessoas *anterior;
} Pessoas;

typedef struct estudantes
{
    int matricula;
    char nome[100];
    char curso[100];
    int ano_de_ingresso;
} Estudante;

typedef struct professores
{
    int matricula;
    char nome[100];
    int salario;
} Professor;

int Vazio(Pessoas *L)
{
    if(L == NULL)
    {
        printf("A lista esta vazia...\n");
        return 1;
    }

    return 0;
}

Pessoas *Inserir(Pessoas *L, int tipo, void *item)
{
    Pessoas *no = (Pessoas*) malloc(sizeof(Pessoas));
    no -> tipo = tipo;
    no -> item = item;
    no -> prox = L;
    no -> anterior = NULL;

    if(L != NULL)
    {
        L -> anterior = no;
    }

    return no;
}

Pessoas *Buscar(Pessoas *L, int matricula)
{
    Pessoas *aux = L;
    Estudante *e;
    Professor *p;

    while(aux != NULL)
    {
        if(aux -> tipo == 1)
        {
            e = (Estudante*) aux -> item;
            if(e -> matricula == matricula)
            {
                return aux;
            }
        }
        else
        {
            p = (Professor*) aux -> item;
            if(p -> matricula == matricula)
            {
                return aux;
            }
        }
        aux = aux -> prox;
    }

    return NULL;
}

Pessoas *Remover(Pessoas *L, int matricula)
{
    Pessoas *aux = L;
    aux = Buscar(L, matricula);
    if(aux == NULL)
    {
        printf("Pessoa nao encontrada...\n");
    }
    else
    {
        if(aux -> anterior != NULL)
        {
            aux -> anterior -> prox = aux -> prox;
        }
        else
        {
            L = aux -> prox;
        }
        printf("Pessoa removida com sucesso!\n");
    }
    return L;
}

int Contar(Pessoas *L, char *curso)
{
    int cont = 0;
    Pessoas* aux = L;

    while(aux != NULL)
    {
        if(aux -> tipo == 1)
        {
            Estudante *e = (Estudante*) aux -> item;
            if(strcmp(e -> curso, curso) == 0)
            {
                cont++;
            }
    
        }
        aux = aux -> prox;
    }
    printf("Cont: %d\n", cont);
    return cont;
}

void ProfMaiorSalario(Pessoas *L)
{
    int maior_salario = -1;
    Pessoas *aux = L;

    while(aux != NULL)
    {
        if(aux -> tipo == 2)
        {
            Professor *p = (Professor*) aux -> item;
            if(p -> salario > maior_salario)
            {
                maior_salario = p -> salario;
            }
        }
        aux = aux -> prox;
    }
    aux = L;

    if(maior_salario == -1)
    {
        printf("Nao tem professores na lista...\n");
    }
    else
    {
        while(aux != NULL)
        {
            if(aux -> tipo == 2)
            {
                Professor *p2 = (Professor*) aux -> item;
                if(p2 -> salario == maior_salario)
                {
                    printf("Nome: %s\n", p2 -> nome);
                }
            }
            aux = aux -> prox;
        }
    }
    
}

void menu()
{
    int x, tipo, matricula, ano_ingresso, salario, resp, cont;
    char nome[100], curso[100];
    Pessoas * L = NULL;

    while(x != 6)
    {
        printf("\n==============================Menu==============================\nEscolha uma opcao: \n");
        printf("1 - Inserir uma pessoa na lista;\n2 - Remover uma pessoa pela matricula;\n3 - Buscar uma pessoa pela Matricula;\n4 - Contar o numero de estudantes em um determinado curso\n5 - Imprimir os professores de maior salario\n6 - Sair.\n");
        printf("================================================================\n\nOperacao: ");

        scanf("%d", &x);
        printf("\n");

        if(x == 1)
        {
           printf("Quer inserir estudante ou professor? (1: Estudante | 2: Professor)\nResposta: ");
           scanf("%d", &tipo);
           if(tipo == 1)
           {
                printf("\nPreencha os campos:\nMatricula: ");
                scanf("%d", &matricula);
                fflush(stdin);

                printf("Nome: ");
                scanf("%[^\n]", nome);
                fflush(stdin);

                printf("Curso: ");
                scanf("%[^\n]", curso);
                fflush(stdin);

                printf("Ano de ingresso: ");
                scanf("%d", &ano_ingresso);
                fflush(stdin);

                Estudante *e = (Estudante*) malloc(sizeof(Estudante));
                e -> matricula = matricula;
                strcpy(e -> nome, nome);
                strcpy(e -> curso, curso);
                e -> ano_de_ingresso = ano_ingresso;
                L = Inserir(L, tipo, e);
           }
           else if(tipo == 2)
           {
                printf("\nPreencha os campos:\nMatricula: ");
                scanf("%d", &matricula);
                fflush(stdin);

                printf("Nome: ");
                scanf("%[^\n]", nome);
                fflush(stdin);

                printf("Salario: ");
                scanf("%d", &salario);
                fflush(stdin);
                
                Professor *p = (Professor*) malloc(sizeof(Professor));
                p -> matricula = matricula;
                strcpy(p -> nome, nome);
                p -> salario = salario;

                L = Inserir(L, tipo, p);
           }
           else
           {
                printf("Digite uma opcao valida...\n");
           }
        }
        else if(x == 2)
        {
            resp = Vazio(L);
            if(resp == 0)
            {
                printf("Digite a matricula da pessoa que queira remover da lista: ");
                scanf("%d", &matricula);
                fflush(stdin);
                L = Remover(L, matricula);
            }
        }
        else if(x == 3)
        {
            resp = Vazio(L);
            if(resp == 0)
            {
                Pessoas *aux;
                Estudante *e;
                Professor *p;

                printf("Digite a matricula da pessoa que queira buscar na lista: ");
                scanf("%d", &matricula);
                fflush(stdin);

                aux = Buscar(L, matricula);
                if(aux == NULL)
                {
                    printf("Pessoa nao encontrada...\n");
                }
                else
                {
                    if(aux -> tipo == 1)
                    {
                        e = (Estudante*) aux -> item;
                        printf("Matricula: %d\nNome: %s\nCurso: %s\nAno de ingresso: %d\n", e -> matricula, e -> nome, e -> curso, e -> ano_de_ingresso);
                    }
                    else
                    {
                        p = (Professor*) aux -> item;
                        printf("Matricula: %d\nNome: %s\nSalario: %d\n", p -> matricula, p -> nome, p -> salario);
                    }
                }
            }
        }
        else if(x == 4)
        {
            resp = Vazio(L);
            if(resp == 0)
            {
                fflush(stdin);
                printf("Digite o nome do curso: ");
                scanf("%[^\n]", curso);
                fflush(stdin);

                cont = Contar(L, curso);
                printf("Existe %d estudantes nesse curso", cont);
            }
        }
        else if(x == 5)
        {
            resp = Vazio(L);
            if(resp == 0)
            {
                ProfMaiorSalario(L);
            }
        }
        else if(x == 6)
        {
            printf("Encerrando o programa...\n");
        }
        else
        {
            printf("Por favor insira uma operacao valida...\n");
        }
    }
}

int main()
{
    menu();

    return 1;
}