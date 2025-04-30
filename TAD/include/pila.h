#ifndef PILA_H
#define PILA_H

typedef struct {
    char producto[50];
    int cantidad;
} ElementoPila;

typedef struct {
    ElementoPila elementos[10];
    int top;
} Pila;

// Funciones de Pila
void inicializarPila(Pila* pila);
int estaVaciaPila(Pila* pila);
void apilar(Pila* pila, char* producto, int cantidad);
ElementoPila desapilar(Pila* pila);

#endif
