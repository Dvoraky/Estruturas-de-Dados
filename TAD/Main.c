#include <stdio.h>
#include "Fila.h"

void menu()
{
    int x, elemento;
    Fila f = Inicializar();

    while(x != 4)
    {
        printf("\n==============================Menu==============================\nEscolha uma opcao: \n");
        printf("1 - Inserir um elemento na fila;\n2 - Remover um elemento da fila;\n3 - Imprimir a fila;\n4 - Sair.\n");
        printf("================================================================\n\nOperacao: ");

        scanf("%d", &x);
        printf("\n");

        if(x == 1)
        {
           printf("Digite o elemento que deseja insirir na fila: ");
           scanf("%d", &elemento);
           Push(f, elemento);
        }
        else if(x == 2)
        {
            elemento = Pop(f);
            if(elemento != -1)
            {
                printf("O elemento removido foi: %d\n", elemento); 
            }
        }
        else if(x == 3)
        {
            Imprimir(f);
        }
        else if(x == 4)
        {
            printf("Encerrando o programa...\n");
            f = Destruir(f);
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