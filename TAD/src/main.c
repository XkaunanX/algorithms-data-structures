#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "Pila.h"
#include "Cola.h"

int main() {
    Lista listaCompras;
    Pila pilaDeshacer;
    Cola colaPendientes;

    // Inicializamos los TADs
    inicializarLista(&listaCompras);
    inicializarPila(&pilaDeshacer);
    inicializarCola(&colaPendientes);

    // Agregamos productos a la lista de compras
    agregarProducto(&listaCompras, "Manzanas", 5);
    agregarProducto(&listaCompras, "Leche", 2);
    agregarProducto(&listaCompras, "Pan", 3);
    
    // Mostramos la lista de compras
    printf("Lista de compras:\n");
    mostrarLista(&listaCompras);
    printf("\n");

    // Realizamos una operacion de deshacer (pila)
    apilar(&pilaDeshacer, "Pan", 3);  // Simulamos un deshacer
    apilar(&pilaDeshacer, "Leche", 2);
    
    // Mostramos el ultimo elemento deshecho (Pila)
    ElementoPila elemento = desapilar(&pilaDeshacer);
    printf("Deshacer la compra de: %s, Cantidad: %d\n\n", elemento.producto, elemento.cantidad);

    // Agregar elementos pendientes en la cola
    encolar(&colaPendientes, "Cereal", 4);
    encolar(&colaPendientes, "Huevos", 12);

    // Procesamos los elementos de la cola
    printf("Procesando elementos pendientes:\n");
    while (!estaVaciaCola(&colaPendientes)) {
        ElementoCola pendiente = desencolar(&colaPendientes);
        printf("Procesado: %s, Cantidad: %d\n", pendiente.producto, pendiente.cantidad);
    }

    return 0;
}
