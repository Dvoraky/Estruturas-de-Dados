#include <stdio.h>
#define TAM 5

void ImprimirCombinacao(int valor, int *moedas, int *combinacao, int index) 
{
    if(valor == 0) 
    {
        for(int i = 0; i < TAM; i++)
        {
            if (combinacao[i] > 0) 
            {
                printf("%d moeda(s) de %d centavo(s)\n", combinacao[i], moedas[i]);
            }
        }
        printf("\n");
        return;
    }

    if(index >= TAM) 
    {
        return;
    }

    for(int i = 0; i <= valor / moedas[index]; i++)
    {
        combinacao[index] = i;
        ImprimirCombinacao(valor - i * moedas[index], moedas, combinacao, index + 1);
    }
}

int main() 
{
    int valor;
    printf("Digite o valor em centavos: ");
    scanf("%d", &valor);

    int moedas[TAM] = {1, 5, 10, 20, 50};
    int combinacao[TAM];

    for(int i = 0; i < TAM; i++) 
    {
        combinacao[i] = 0;
    }

    printf("Combinacoes:\n");
    ImprimirCombinacao(valor, moedas, combinacao, 0);

    return 0;
}
