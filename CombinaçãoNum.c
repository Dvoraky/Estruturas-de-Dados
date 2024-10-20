#include <stdio.h>

void ImprimirCombicoes(int *combinacao, int pos, int n, int *vetaux)
{
    int i; int soma = 0;  

    if(pos == n)
    {
        for(int j = 0; j < n; j++)
        {
            soma += combinacao[j];
        }

        if(soma % 2 == 0)
        {
            for(i = 0; i < n; i++)
            {
                printf("%d ", combinacao[i]);
            }
            printf("\n");
        }
    }

    else
    {
        for(i = 0; i <= 3; i++)
        {
            combinacao[pos] = vetaux[i];
            ImprimirCombicoes(combinacao, pos + 1, n, vetaux);
        }
    }
}

int main()
{
    int vet[5] = {15, 31, 55, 44}, tam;
    
    printf("Digite o tamanho das combinacoes: ");
    scanf("%d", &tam);
    int combinacao[tam];

    ImprimirCombicoes(combinacao, 0, tam, vet);

    return 0;
}