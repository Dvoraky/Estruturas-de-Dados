#include <stdio.h>
#include <stdlib.h>

// Definindo a struct da Árvore binária
typedef struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

// Função para calcular a altura da árvore
int Altura(arvore *a)
{
    if(a == NULL)
    {
        return 0;
    }
    else
    {
        int hesq = Altura(a -> esq);
        int hdir = Altura(a -> dir);
        if(hesq > hdir)
        {
            return 1 + hesq;
        }
        else
        {
            return 1 + hdir;
        }
    }
}

// Função para criar a árvore com o arquivo aberto
arvore *LerArvore(FILE *arq)
{
    char c;
    int num;
    arvore *a;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    // -1 será usado para simbolizar o NULL
    if(num == -1) 
    {
        fscanf(arq, "%c", &c);
        return NULL;
    }

    else
    {
        a = (arvore*)malloc(sizeof(arvore));
        a -> info = num;
        a -> esq = LerArvore(arq);
        a -> dir = LerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

// Imprime a árvore em pré-ordem
void ImprimirPreOrdem(arvore *a)
{
    if(a != NULL)
    {
        printf("%d ", a -> info);
        ImprimirPreOrdem(a -> esq);
        ImprimirPreOrdem(a -> dir);
    }
}

// Imprime a árvore em ordem
void ImprimirOrdem(arvore *a)
{
    if(a != NULL)
    {
        ImprimirOrdem(a -> esq);
        printf("%d ", a -> info);
        ImprimirOrdem(a -> dir);
    }
}

// Imprime a árvore em pós-ordem
void ImprimirPosOrdem(arvore *a)
{
    if(a != NULL)
    {
        ImprimirPosOrdem(a -> esq);
        ImprimirPosOrdem(a -> dir);
        printf("%d ", a -> info);
    }
}

// Imprime um nível de uma árvore
void ImprimeNivel(arvore *a, int cont, int nivel)
{
    if(a != NULL)
    {
        if(cont == nivel)
        {
            printf("%d ", a -> info);
        }
        else
        {
            ImprimeNivel(a -> esq, cont + 1, nivel);
            ImprimeNivel(a -> dir, cont + 1, nivel);
        }
    }
}

// Imprime a árvore em largura
void ImprimirLargura(arvore *a)
{
    int altura = Altura(a);
    for(int i = 0; i < altura; i++)
    {
        ImprimeNivel(a, 0, i);
        printf("\n");
    }
}

// Menu de impressão
void Imprimir(arvore *a)
{
    int x = 0;
    while(x != 5)
    {
        printf("======================Menu de impressao=======================\nEscolha uma opcao: \n");
        printf("1 - Imprmir em Pre-ordem;\n2 - Imprimir em Ordem;\n3 - Imprmir em Pos-ordem;\n4 - Imprmir em largura;\n5 - Voltar ao menu.\n");
        printf("================================================================\n\nOperacao: ");
        
        scanf("%d", &x);
        printf("\n");

        if(x == 1)
        {
            printf("Pre-Ordem: ");
            ImprimirPreOrdem(a);
            printf("\n\n");
        }
        else if(x == 2)
        {
            printf("Em Ordem: ");
            ImprimirOrdem(a);
            printf("\n\n");
        }
        else if(x == 3)
        {
            printf("Pos-Ordem: ");
            ImprimirPosOrdem(a);
            printf("\n\n");
        }
        else if(x == 4)
        {
            printf("Em largura:\n\n");
            ImprimirLargura(a);
            printf("\n");
        }
        else if(x == 5)
        {
            printf("Retornando ao menu...\n");
        }
        
        else
        {
            printf("Por favor selecione uma operacao valida!\n\n");
        }
    }
}

// Função que verifica se um elemento está presente na árvore
int Existe(arvore *a, int x)
{
    if(a == NULL)
    {
        return 0;
    }
    else if(a -> info == x)
    {
        return 1;
    }
    else
    {
        int y = Existe(a -> esq, x);
        if(y == 1)
        {
            return 1;
        }
        return Existe(a -> dir, x);
    }
}

// Função para contar o número de elementos na árvore
int Contar(arvore *a, int contador)
{
    if(a == NULL)
    {
        return contador;
    }
    else
    {
        contador++;
        contador = Contar(a -> esq, contador);
        contador = Contar(a -> dir, contador);
    }

    return contador;
}

// Função para imprmir os nós folhas da árvore
void ImprimirFolha(arvore *a)
{
    if(a != NULL)
    {
        if(a -> esq == NULL && a -> dir == NULL)
        {
            printf("%d ", a -> info);
        }
        ImprimirFolha(a -> esq);
        ImprimirFolha(a -> dir);
    }
}

// Função para checar se a árvore está balanceada
int EstaBalanceada(arvore *a)
{
    if(a == NULL)
    {
        return 1;
    }
    else
    {
        int hesq = Altura(a -> esq);
        int hdir = Altura(a -> dir);
        if(abs(hesq - hdir) <= 1 && EstaBalanceada(a -> esq) && EstaBalanceada(a -> dir))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

// Função para verificar se uma árvore é cheia
int EstaCheia(arvore *a)
{
    if(a == NULL)
    {
        return 1;
    }
    if(a -> esq == NULL && a -> dir == NULL)
    {
        return 1;
    }
    if(a -> esq != NULL && a -> dir != NULL)
    {
        return EstaCheia(a -> esq) && EstaCheia(a -> dir);
    }

    return 0;
}

// Função para checar o nível de um certo nó
int Nivel(arvore *a, int nivel, int x)
{
    if(a == NULL)
    {
        return -1;
    }

    if(x == a -> info)
    {
        return nivel;
    }

    int nivelesq = Nivel(a -> esq, nivel + 1, x);
    if(nivelesq != -1)
    {
        return nivelesq;
    }

    int niveldir = Nivel(a -> dir, nivel + 1, x);
    return niveldir;

}

// Função para liberar a árvore da memória
void LiberarArvore(arvore *a)
{
    if(a == NULL)
    {
        return;
    }

    LiberarArvore(a -> esq);
    LiberarArvore(a -> dir);
    free(a);
}

// Função do Menu para selecionar as operações
void Menu()
{
    int x = 0;
    arvore *a = NULL;
    while(x != 9)
    {
        printf("\n==============================Menu==============================\nEscolha uma opcao: \n");
        printf("1 - Ler uma arvore de um arquivo;\n2 - Imprimir a arvore;\n3 - Verificar se um elemento existe na arvore;\n4 - Contar o numero de elementos na arvore;\n");
        printf("5 - Imprimir os nos das folhas da arvore;\n6 - Verificar se a arvore esta balanceada;\n7 - Verificar se a arvore e cheia;\n8 - Imprimir o nivel de um no X;\n9 - Sair.\n");
        printf("================================================================\n\nOperacao: ");

        scanf("%d", &x);
        printf("\n");
        
        // Ler uma árvore de um arquivo
        if(x == 1)
        {
            FILE *arq;
            char arquivo[100]; 

            printf("Digite o nome do arquivo: ");
            scanf("%s", arquivo);
            arq = fopen(arquivo, "r");
            
            
            if(arq == NULL)
            {
                printf("\nNao foi possivel abrir o arquivo.\n");
            }
            else
            {   
                printf("\nArquivo lido com sucesso!\n");
                if(a == NULL)
                {
                    a = LerArvore(arq);
                }
                else
                {
                   LiberarArvore(a);
                   a = LerArvore(arq); 
                }
            }

            fclose(arq);

        }

        // Imprimir uma árvore 
        else if(x == 2)
        {
            if(a == NULL)
            {
                printf("Por favor insira uma arvore primeiro.\n");
            }
            else
            {
                // Aqui inicializa o menu de impressão
                Imprimir(a); 
            }
        }

        // Verifica se um elemento está presente na árvore
        else if(x == 3)
        {
            int valor, y;

            if(a == NULL)
            {
                printf("Por favor insira uma arvore primeiro.\n");
            }
            else
            {
                printf("Digite o elemento que deseja verificar a existencia na arvore: ");
                scanf("%d", &valor);
                y = Existe(a, valor);
                if(y == 1)
                {
                    printf("\nO elemento existe na arvore!\n");
                }
                else
                {
                    printf("\nO elemento nao existe na arvore!\n");
                }
            }
        }

        // Conta o número de elementos de uma árvore
        else if(x == 4)
        {
            int contador = Contar(a, 0);
            printf("O numero de elementos na arvore e %d\n", contador);
        }

        // Imprime as folhas de uma árvore
        else if(x == 5)
        {
            if(a == NULL)
            {
                printf("A arvore esta vazia e nao possui folhas.\n");
            }
            else
            {
                printf("As folhas da arvore sao: ");
                ImprimirFolha(a);
                printf("\n");
            }
        }

        // Verifica se uma árvore está balanceada
        else if(x == 6)
        {
            int z = EstaBalanceada(a);
            if(z == 1)
            {
                printf("A arvore esta balanceada!\n");
            }
            else
            {
                printf("A arvore esta desbalanceada!\n");
            }
        }

        // Verifica se uma árvore está cheia
        else if(x == 7)
        {
            int retorno = EstaCheia(a);
            if(retorno == 1)
            {
                printf("A arvore esta cheia!\n");
            }
            else
            {
                printf("A arvore nao esta cheia!\n");
            }
        }

        // Imprime o nível de um certo nó de uma árvore
        else if(x == 8)
        {
            int no, k;
            
            if(a == NULL)
            {
                printf("Por favor insira uma arvore primeiro.\n");
            }
            else
            {
                printf("Digite o no que deseja saber o nivel: ");
                scanf("%d", &no);
                printf("\n");
                

                k = Existe(a, no);
                if(k == 1)
                {
                    int nivel = Nivel(a, 0, no);
                    printf("O nivel desse no e %d.\n", nivel);
                }
                else
                {
                    printf("Insira um no que esteja presente na arvore.\n");
                }
            }
        }

        // Encerra o programa
        else if(x == 9)
        {
            printf("Encerrando o programa, obrigada por utilizar!\n");
        }
        
        // Caso não seja inserido um número de 1 à 9 é impresso esta mensagem de erro
        else
        {
            printf("Por favor selecione uma operacao valida!\n");
        }
    }
}

int main()
{
    // Inicializa o menu
    Menu(); 

    return 0;
}