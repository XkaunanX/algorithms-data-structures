#include <stdio.h>
#include <string.h>
#include "Cola.h"

void inicializarCola(Cola* cola) {
    cola->frente = cola->fondo = 0;
}

int estaVaciaCola(Cola* cola) {
    return cola->frente == cola->fondo;
}

void encolar(Cola* cola, char* producto, int cantidad) {
    if ((cola->fondo + 1) % 10 != cola->frente) {
        strcpy(cola->elementos[cola->fondo].producto, producto);
        cola->elementos[cola->fondo].cantidad = cantidad;
        cola->fondo = (cola->fondo + 1) % 10;
    } else {
        printf("Cola llena. No se puede encolar mas elementos.\n");
    }
}

ElementoCola desencolar(Cola* cola) {
    if (!estaVaciaCola(cola)) {
        ElementoCola elemento = cola->elementos[cola->frente];
        cola->frente = (cola->frente + 1) % 10;
        return elemento;
    }
    ElementoCola vacio = {"", 0};
    return vacio;
}
