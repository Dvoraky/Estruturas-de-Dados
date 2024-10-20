#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    int destino;
    int custo;
    struct lista *prox;
} lista;

void ImprimirLista(lista *l)
{
    if(l != NULL)
    {
        printf("-(%d, %d)", l -> destino, l -> custo);
        ImprimirLista(l -> prox);
    }
}

void imprimirGrafo(lista **g, int n)
{
    int i;
    printf("Grafo: ");
    for(i = 1; i <= n; i++)
    {
        printf("\n\t%d", i);
        ImprimirLista(g[i]);
    }
}

lista *InserirLista(lista *l, int d, int c)
{
    lista *no = (lista *) malloc(sizeof(lista));
    no -> destino = d;
    no -> custo = c;
    no -> prox = l;
    return no;
}

void InserirAresta(lista **g, int origem, int destino, int custo)
{
    g[origem] = InserirLista(g[origem], destino, custo);
}

void inicializar(lista **g, int n)
{
    for(int i = 0; i <= n; i++)
    {
        g[i] = NULL;
    }
}

int existe(int *vet, int valor, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(vet[i] == valor)
        {
            return 1;
        }
    }
    return 0;
}

void Caminhos(lista **g, int b, int *vet, int pos)
{
    if(vet[pos - 1] == b)
    {
        int i;
        for(i = 0; i < pos; i++)
        {
            printf("%d", vet[i]);
        }
    }
    else
    {
        lista *p = g[vet[pos - 1]];
        while(p != NULL)
        {
            if(!existe(vet, p -> destino, pos))
            {
                vet[pos] = p -> destino;
                Caminhos(g, b, vet, pos + 1);
            }
            p = p -> prox;
        }
    }
}

lista* removerAresta(lista* l, int destino)
{
    lista* atual = l;
    lista* anterior = NULL;

    while(atual != NULL)
    {
        if(atual -> destino == destino)
        {
            if(anterior == NULL)
            {
                // O nó a ser removido é o primeiro da lista
                l = atual -> prox;
            } 
            else 
            {
                anterior -> prox = atual -> prox;
            }

            free(atual);
            printf("Aresta com destino %d removida com sucesso\n", destino);
            return l;
        }

        anterior = atual;
        atual = atual -> prox;
    }

    printf("Não há aresta com destino %d\n", destino);
    return l;
}

void Graus(lista *g[], int vertice, int n)
{
    int graus_entrada = 0; int graus_saidas = 0;
    lista *aux;
    for(int i = 1; i <= n; i++)
    {
        aux = g[i];
        if(i == vertice)
        {
            while(aux != NULL)
            {
                graus_saidas++;
                aux = aux -> prox;
            }   
        }
        else
        {
            while(aux != NULL)
            {
                if(aux -> destino == vertice)
                {
                    graus_entrada++;
                }
                aux = aux -> prox;
            }
            
        }
    }
    free(aux);
    printf("\nGraus de entrada e saida de %d:\nEntrada: %d\nSaida: %d\n", vertice, graus_entrada, graus_saidas);
}

void menu()
{
    int x = 0;
    int n = 5;
    lista ** g = (lista**) malloc ((n + 1) * sizeof(lista*));
    inicializar(g, n);

    InserirAresta(g, 1, 2, 1);
    InserirAresta(g, 2, 2, 1);
    InserirAresta(g, 3, 2, 1);
    InserirAresta(g, 4, 2, 1);
    InserirAresta(g, 5, 2, 1);
    InserirAresta(g, 3, 3, 1);
    InserirAresta(g, 1, 3, 1);
    InserirAresta(g, 2, 4, 1);
    InserirAresta(g, 1, 4, 1);

    while(x != 9)
    {

        int origem, destino, custo;
        printf("\n==============================Menu==============================\nEscolha uma opcao: \n");
        printf("1 - Inserir uma aresta no grafo;\n2 - Remover uma aresta do grafo;\n3 - Imprimir o grafo;\n4 - Verificar os graus de entrada e saida de um vertice;\n");
        printf("5 - Verificar se um grafo e completo;\n6 - Imprimir todos os caminhos entre uma origem e um destino;\n7 - Imprimir o caminho mais curto;\n8 - Imprmir o caminho de menor custo;\n9 - Sair.\n");
        printf("================================================================\n\nOperacao: ");

        scanf("%d", &x);
        printf("\n");



        if(x == 1)
        {
            printf("Insira a origem, o destino e o custo respectivamente: ");
            scanf("%d %d %d", &origem, &destino, &custo);

            if(origem > n || destino > n)
            {
                printf("\nDigite valores dentro do limite estabelecido.\n");
            }
            else
            {
                InserirAresta(g, origem, destino, custo);
                printf("\nNo inserido corretamente!\n");
            }
        }
        else if(x == 2)
        {
            printf("\nInsira respectivamente a origem e o destino da aresta a ser removida: ");
            scanf("%d %d", &origem, &destino);
            g[origem] = removerAresta(g[origem], destino);
        }
        else if(x == 3)
        {
            imprimirGrafo(g, n);
        }
        else if(x == 4)
        {
            printf("Digite o valor do vertice que deseja verificar os graus de entrada e saida: ");
            scanf("%d", &origem);
            Graus(g, origem, n);

        }
        else if(x == 5)
        {
            
        }
        else if(x == 6)
        {
            int vet[n];
            printf("Digite o destino dos caminhos: ");
            scanf("%d", &destino);
            Caminhos(g, destino, vet, 0); 
        }
        else if(x == 7)
        {
        }
        else if(x == 8)
        {
            
        }
        else if(x == 9)
        {
            printf("Encerrando o programa...");
        }
        else
        {
            printf("Insira uma opcao valida...\n");
        }
    }
}

int main()
{
    menu();

    return 1;
}