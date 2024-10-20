#include <stdio.h>
#include <stdlib.h>

// Definindo a struct da Árvore binária
typedef struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

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
        if(a -> info > x)
        {
            return Existe(a -> esq, x);
        }
        else
        {
            return Existe(a -> dir, x);
        }
    }
}


// Função para imprmir os nós folhas da árvore
int ImprimirFolha(arvore *a, int x)
{
    int contador = 0;
    if(a != NULL)
    {
        if(a -> esq == NULL && a -> dir == NULL && a -> info < x)
        {
            printf("%d ", a -> info);
            contador++;
        }
        
        if(a -> info > x)
        {
            return contador + ImprimirFolha(a -> esq, x);
        }
        else
        {
            contador += ImprimirFolha(a -> esq, x);
            contador += ImprimirFolha(a -> dir, x);
            return contador;
        } 
    }

    return contador;
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

    if(a -> info > x)
    {
        return Nivel(a -> esq, nivel + 1, x);
    }
    else
    {
        return Nivel(a -> dir, nivel + 1, x);
    }

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

// Função para inserir um nó x na árvore
arvore *Inserir(arvore *a, int x)
{
    if(a == NULL)
    {
        a = (arvore*) malloc(sizeof(arvore));
        a -> info = x;
        a -> esq = NULL;
        a -> dir = NULL;
    }
    else if(x <= a -> info)
    {
        a -> esq = Inserir(a -> esq, x);
    }
    else
    {
        a -> dir = Inserir(a -> dir, x);
    }

    return a;
}

// Função para remover um nó x de uma árvore
arvore *Remover(arvore *a, int x)
{
    if(a != NULL)
    {
        if(a -> info == x)
        {
            if(a -> esq == NULL && a -> dir == NULL)
            {
                free(a);
                return NULL;
            }
            else if(a -> esq == NULL)
            {
                arvore *aux = a -> dir;
                free(a);
                return aux;
            }
            else if(a -> dir == NULL)
            {
                arvore *aux = a -> esq;
                free(a);
                return aux;
            }
            else
            {
                arvore *aux = a -> esq;
                while(aux -> dir != NULL)
                {
                    aux = aux -> dir;
                }
                a -> info = aux -> info;
                a -> esq = Remover(a -> esq, aux -> info);
            }
        }
        else if(x < a -> info)
        {
            a -> esq = Remover(a -> esq, x);
        }
        else
        {
            a -> dir = Remover(a -> dir, x);
        }
    }
    return a;
}

// Função do Menu para selecionar as operações
void Menu()
{
    int x = 0;
    arvore *a = NULL;
    while(x != 8)
    {
        printf("\n==============================Menu==============================\nEscolha uma opcao: \n");
        printf("1 - Ler uma arvore de um arquivo;\n2 - Imprimir a arvore;\n3 - Verificar se um elemento existe na arvore;\n4 - Imprimir o nivel de um no X;\n");
        printf("5 - Imprimir as folhas menores que um valor X;\n6 - Inserir um no X na arvore;\n7 - Remover um no X da arvore;\n8 - Sair.\n");
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

        // Imprime uma árvore 
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

        // Imprime um nível de um nó X
        else if(x == 4)
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

        // Imprime as folhas de uma árvore menores que um valor X
        else if(x == 5)
        {
            if(a == NULL)
            {
                printf("A arvore esta vazia e nao possui folhas.\n");
            }
            else
            {   
                int g;
                printf("Digite um valor para imprimir as folhas menores que ele: ");
                scanf("%d", &g);
                printf("As folhas da arvore sao: ");
                printf("\n");
                int contador = ImprimirFolha(a, g);
                if(contador == 0)
                {
                    printf("\n\nNao ha folhas menores do que %d", g);
                }
                printf("\n");
            }
        }

        // Insere um nó x na árvore
        else if(x == 6)
        {
            int w;
            printf("Digite o valor que deseja inserir na arvore: ");
            scanf("%d", &w);
            printf("\n");
            a = Inserir(a, w);
            printf("O no foi inserido com sucesso!\n");
        }

        // Remove um nó x da árvore
        else if(x == 7)
        {   
            if(a != NULL)
            {
                int e, r;
                printf("Digite o valor que deseja remover da arvore: ");
                scanf("%d", &e);
                printf("\n");
                r = Existe(a, e);
                if(r == 1)
                {
                    a = Remover(a, e);
                    printf("O no foi removido com sucesso!\n");
                }
                else
                {
                    printf("Digite um valor que exista na arvore!\n");
                }
            }
            else
            {
                printf("Por favor insira uma arvore primeiro.\n");
            }
        }

        // Encerra o programa
        else if(x == 8)
        {
            LiberarArvore(a);
            printf("Encerrando o programa, obrigada por utilizar!\n"); 
        }

        // Caso não seja inserido um número de 1 à 8 é impresso esta mensagem de erro
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