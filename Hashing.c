#include <stdio.h>
#include <string.h>
#define N 11
#define TAM_MAX 100

typedef struct registro
{
    int mat;
    char nome[TAM_MAX];
    char curso[TAM_MAX];
    int disponibilidade;
} registro;

int hash(int key)
{
    return (key % N);
}

void inicializar(char *nomeArq)
{
    FILE *arq = fopen(nomeArq, "wb");
    registro a;
    a.disponibilidade = 1;
    for(int i = 0; i < N; i++)
    {
        fwrite(&a, sizeof(registro), 1, arq);
    }
    fclose(arq);
}

int acharPosicao(char *nomeArq, int x)
{
    int pos = hash(x);
    registro a;
    FILE *arq = fopen(nomeArq, "rb");

    fseek(arq, pos * sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);

    while(a.disponibilidade == 0)
    {
        pos = (pos + 1) % N;
        fseek(arq, pos * sizeof(registro), SEEK_SET);
        fread(&a, sizeof(registro), 1, arq);
    }

    fclose(arq);
    return pos;
}

void inserir(char *nomeArq, int matricula, char *nome, char *curso)
{
    int pos = acharPosicao(nomeArq, matricula);
    FILE *arq = fopen(nomeArq, "r+b");
    registro a;

    a.mat = matricula;
    strcpy(a.nome, nome);
    strcpy(a.curso, curso);
    a.disponibilidade = 0;

    fseek(arq, pos * sizeof(registro), SEEK_SET);
    fwrite(&a, sizeof(registro), 1, arq);

    fclose(arq);
}

void imprimirHashing(char *nomeArq)
{
    FILE *arq = fopen(nomeArq, "r+b");
    registro a;
    for(int i = 0; i <= N; i++)
    {
        fseek(arq, i * sizeof(registro), SEEK_SET);
        fread(&a, sizeof(registro), 1, arq);
        if(a.disponibilidade == 0)
        {
            printf("%d ", a.mat);
        }
    }
    printf("\n");
    fclose(arq);
}

int posicao(char *nomeArq, int mat)
{
    int pos = hash(mat);
    FILE *arq = fopen(nomeArq, "r+b");
    registro a;
    
    while(1)
    {
        fseek(arq, pos * sizeof(registro), SEEK_SET);
        fread(&a, sizeof(registro), 1, arq);
        if(a.mat == mat)
        {
            return pos;
        }
        else
        {
            pos = (pos + 1) % N;
        }
    }
    return -1;
}

void menu()
{
    int x, mat, pos;
    char nome[TAM_MAX];
    char curso[TAM_MAX];
    char nomeArq[] = "ArquivoHashing.txt";
    inicializar(nomeArq);
    
    while(x != 4)
    {
        printf("\n==============================Menu==============================\nEscolha uma opcao: \n");
        printf("1 - Inserir um estudante;\n2 - Imprimir as informacoes de um estudante;\n3 - Imprimir a tabela de dispersao;\n4 - Sair.\n");
        printf("================================================================\n\nOperacao: ");

        scanf("%d", &x);
        printf("\n");

        if(x == 1)
        {
            printf("Digite a matricula: ");
            scanf("%d", &mat);
            fflush(stdin);

            printf("Digite o nome: ");
            scanf("%[^\n]", nome);
            fflush(stdin);

            printf("Digite o curso: ");
            scanf("%[^\n]", curso);
            fflush(stdin);

            inserir(nomeArq, mat, nome, curso);
        }
        else if(x == 2)
        {
            FILE *arq = fopen(nomeArq, "r+b");
            registro Registro;

            printf("Digite a matricula: ");
            scanf("%d", &mat);
            printf("\n");

            pos = posicao(nomeArq, mat);
            fseek(arq, pos * sizeof(registro), SEEK_SET);
            fread(&Registro, sizeof(registro), 1, arq);
            printf("Matricula: %d\nNome: %s\nCurso: %s\n", Registro.mat, Registro.nome, Registro.curso);

            fclose(arq);
        }

        else if(x == 3)
        {
            imprimirHashing(nomeArq);
        }
        else if(x == 4)
        {
            printf("Encerrando o programa...\n");
        }
        else
        {
            printf("Por favor insira uma operacao valida...");
        }
    }
}

int main()
{
    menu();

    return 1;
}