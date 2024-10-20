#include <stdio.h>

void ImprimirCombicoes(char *combinacoes, int pos, int tam, char *vetAux)
{
    int i, a = 0;
    if(pos == tam)
    {
        for(int j = 0; j < tam; j++)
        {
            if(combinacoes[j] == 'a')
            {
                a++;
            }
        }

        if(a > tam / 2)
        {
            for(i = 0; i < tam; i++)
            {
                printf("%c ", combinacoes[i]);
            }
            printf("\n");
        }
    }
    
    else
    {
        for(i = 0; i <= 2; i++)
        {
            combinacoes[pos] = vetAux[i];
            ImprimirCombicoes(combinacoes, pos + 1, tam, vetAux);
        }
    }
}

int main()
{
    int tam;
    char vet[] = {"aei"}, combinacoes[tam];
    printf("Digite o tamanho das combinacoes: ");
    scanf("%d", &tam);

    ImprimirCombicoes(combinacoes, 0, tam, vet);


    return 0;
}