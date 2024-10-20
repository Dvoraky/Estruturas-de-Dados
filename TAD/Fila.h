#ifndef Fila_h
#define Fila_h

typedef struct fila *Fila;
void Push(Fila f, int x);
int Pop(Fila f);
void Imprimir(Fila f);
Fila Inicializar();
Fila Destruir();

#endif