#include <stdio.h>
#include <math.h>
#define N 10

int totalElementos =  0;

void ImprimirHeap(int *heap)
{
    printf("Min-Heap: ");
    for(int i = 0; i < totalElementos; i++)
    {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int indiceFilhoEsq(int x)
{
    int indice = (2 * x) + 1;
    if(x >= totalElementos || indice >= totalElementos)
    {
        return -1;
    }
    else
    {
        return indice;
    }
}

int indiceFilhodir(int x)
{
    int indice = (2 * x) + 2;
    if(x >= totalElementos || indice >= totalElementos)
    {
        return -1;
    }
    else
    {
        return indice;
    }
}

int indicePai(int x)
{
    int indice = (int) floor((x - 1)/ 2);
    if(x <= 0 || x  >= totalElementos)
    {
        return -1;
    }
    else
    {
        return indice;
    }
}

void AjustarSubindo(int  *heap, int pos)
{
    if(pos != -1)
    {
        int pai = indicePai(pos);
        if(pai != -1)
        {
            if(heap[pos] < heap[pai])
            {
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;
                AjustarSubindo(heap, pai);
            }
        }
    }
}

void AjustarDescendo(int *heap,int pos)
{
    if(pos != -1 && indiceFilhoEsq(pos) != -1)
    {
        int indiceMaiorFilho = indiceFilhoEsq(pos);
        if(indiceFilhodir(pos) != -1 && heap[indiceFilhodir(pos)] < heap[indiceMaiorFilho])
        {
            indiceMaiorFilho = indiceFilhodir(pos);
        }
        if(heap[indiceMaiorFilho] < heap[pos])
        {
            int aux = heap[pos];
            heap[pos] = heap[indiceMaiorFilho];
            heap[indiceMaiorFilho] = aux;
            AjustarDescendo(heap, indiceMaiorFilho);
        }
    }
}

void inserir(int *heap, int x)
{
    heap[totalElementos] = x;
    totalElementos++;

    AjustarSubindo(heap, totalElementos - 1);
}

int Remover(int *heap)
{
    if(totalElementos == 0)
    {
        return -1;
    }
    else
    {
        int retorno = heap[0];
        heap[0] = heap[totalElementos - 1];
        totalElementos--;
        AjustarDescendo(heap,  0);
        return retorno;
    }
}

void menu()
{
    int heap[N];
    int x, elemento;

    while(x != 4)
    {
        printf("\n==============================Menu==============================\nEscolha uma opcao: \n");
        printf("1 - Inserir uma elemento na min-heap;\n2 - Remover um elemento na min-heap;\n3 - Imprimir a min-heap;\n4 - Sair.\n");
        printf("================================================================\n\nOperacao: ");

        scanf("%d", &x);
        printf("\n");

        if(x == 1)
        {
            if(totalElementos > N)
            {
                printf("A min-heap esta cheia.\n");
            }
            else
            {
                printf("Digite o elemento que deseja inserir: ");
                scanf("%d", &elemento);
                inserir(heap, elemento);
            }
        }
        else if(x == 2)
        {
            elemento = Remover(heap);
            if(elemento != -1)
            {
                printf("O elemento removido foi: %d\n", elemento);
            }
            else
            {
                printf("A min-heap esta vazia.\n");
            }
                
        }
        else if(x == 3)
        {
            if(totalElementos == 0)
            {
                printf("A min-heap esta vazia.\n");
            }
            else
            {
                ImprimirHeap(heap);
            }
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