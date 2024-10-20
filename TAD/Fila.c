#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#define N 100

struct fila
{
    int Vetor[N];
    int inicio;
    int final;
};

Fila Inicializar(Fila f)
{
    Fila fila2 = (Fila) malloc(sizeof(struct fila));
    fila2 -> inicio = 0;
    fila2 -> final = 0;
    return fila2;
}

Fila Destruir(Fila f)
{
    free(f);
    return NULL;
}

void Push(Fila f, int x)
{
    if(f -> final == N)
    {
        printf("\nA fila esta cheia...\n");
    }
    else
    {
        f -> Vetor[f -> final] = x;
        f -> final++;
        printf("\nElemento inserido!\n");
    }
}

int Pop(Fila f)
{
    int aux;
    if(f -> inicio == f -> final)
    {
        printf("A fila esta vazia...\n");
        return -1;
    }
    else
    {
        aux = f -> Vetor[f -> inicio];
        f -> inicio++;
        return aux;
    }
}

void Imprimir(Fila f)
{
    if(f -> inicio == f -> final)
    {
        printf("A fila esta vazia...\n");
    }
    else
    {
        printf("Fila: ");
        for(int i = f -> inicio; i < f -> final; i++)
        {
            printf("%d ", f -> Vetor[i]);
        }
        printf("\n");
    }
}