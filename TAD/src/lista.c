#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

void inicializarLista(Lista* lista) {
    lista->cabeza = NULL;
}

void agregarProducto(Lista* lista, char* producto, int cantidad) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevoNodo->producto, producto);
    nuevoNodo->cantidad = cantidad;
    nuevoNodo->siguiente = lista->cabeza;
    lista->cabeza = nuevoNodo;
}

void mostrarLista(Lista* lista) {
    Nodo* temp = lista->cabeza;
    while (temp != NULL) {
        printf("Producto: %s, Cantidad: %d\n", temp->producto, temp->cantidad);
        temp = temp->siguiente;
    }
}
