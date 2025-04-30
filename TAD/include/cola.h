#ifndef COLA_H
#define COLA_H

typedef struct {
    char producto[50];
    int cantidad;
} ElementoCola;

typedef struct {
    ElementoCola elementos[10];
    int frente, fondo;
} Cola;

// Funciones de Cola
void inicializarCola(Cola* cola);
int estaVaciaCola(Cola* cola);
void encolar(Cola* cola, char* producto, int cantidad);
ElementoCola desencolar(Cola* cola);

#endif
