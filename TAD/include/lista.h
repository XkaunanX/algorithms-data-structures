#ifndef LISTA_H
#define LISTA_H

typedef struct Nodo {
    char producto[50];
    int cantidad;
    struct Nodo* siguiente;
} Nodo;

typedef struct {
    Nodo* cabeza;
} Lista;

// Funciones de Lista
void inicializarLista(Lista* lista);
void agregarProducto(Lista* lista, char* producto, int cantidad);
void mostrarLista(Lista* lista);

#endif
