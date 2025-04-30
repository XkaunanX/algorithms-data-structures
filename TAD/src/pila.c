#include <stdio.h>
#include <string.h>
#include "Pila.h"

void inicializarPila(Pila* pila) {
    pila->top = -1;
}

int estaVaciaPila(Pila* pila) {
    return pila->top == -1;
}

void apilar(Pila* pila, char* producto, int cantidad) {
    if (pila->top < 9) {
        pila->top++;
        strcpy(pila->elementos[pila->top].producto, producto);
        pila->elementos[pila->top].cantidad = cantidad;
    } else {
        printf("Pila llena. No se puede apilar mas elementos.\n");
    }
}

ElementoPila desapilar(Pila* pila) {
    if (!estaVaciaPila(pila)) {
        return pila->elementos[pila->top--];
    }
    ElementoPila vacio = {"", 0};
    return vacio;
}
