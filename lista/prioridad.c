#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;       // El valor o dato del nodo
    int prioridad;  // La prioridad del nodo
    struct Nodo* siguiente;  // Puntero al siguiente nodo
} Nodo;

typedef struct ListaPrioridad {
    Nodo* cabeza;  // Puntero al primer nodo de la lista
} ListaPrioridad;

// Funciones para manejar la lista de prioridad
void inicializar_lista(ListaPrioridad* lista);
void insertar_nodo(ListaPrioridad* lista, int dato, int prioridad);
void eliminar_nodo(ListaPrioridad* lista);
void imprimir_lista(ListaPrioridad* lista);

int main() {
    // Crear la lista de prioridad
    ListaPrioridad lista;
    inicializar_lista(&lista);
    
    // Insertar nodos en la lista
    insertar_nodo(&lista, 10, 2); // Dato 10, prioridad 2
    insertar_nodo(&lista, 20, 1); // Dato 20, prioridad 1
    insertar_nodo(&lista, 30, 3); // Dato 30, prioridad 3
    
    // Imprimir la lista de prioridad
    printf("Lista de prioridad:\n");
    imprimir_lista(&lista);
    
    // Eliminar el nodo con la mayor prioridad
    eliminar_nodo(&lista);
    
    // Imprimir nuevamente la lista de prioridad
    printf("\nLista de prioridad despues de eliminar el nodo de mayor prioridad:\n");
    imprimir_lista(&lista);
    
    return 0;
}

// Inicializa la lista de prioridad (la lista esta vacia al principio)
void inicializar_lista(ListaPrioridad* lista) {
    lista->cabeza = NULL;
}

// Inserta un nodo en la lista de prioridad
void insertar_nodo(ListaPrioridad* lista, int dato, int prioridad) {
    Nodo* nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->prioridad = prioridad;
    nuevo_nodo->siguiente = NULL;
    
    // Si la lista esta vacia o el nuevo nodo tiene mayor prioridad que el primer nodo
    if (lista->cabeza == NULL || lista->cabeza->prioridad < prioridad) {
        nuevo_nodo->siguiente = lista->cabeza;
        lista->cabeza = nuevo_nodo;
    } else {
        // Insertar en la posicion correcta segun la prioridad
        Nodo* actual = lista->cabeza;
        while (actual->siguiente != NULL && actual->siguiente->prioridad >= prioridad) {
            actual = actual->siguiente;
        }
        nuevo_nodo->siguiente = actual->siguiente;
        actual->siguiente = nuevo_nodo;
    }
}

// Elimina el nodo con la mayor prioridad (el primer nodo)
void eliminar_nodo(ListaPrioridad* lista) {
    if (lista->cabeza == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
    
    Nodo* temp = lista->cabeza;
    lista->cabeza = lista->cabeza->siguiente;
    free(temp);
}

// Imprime la lista de prioridad
void imprimir_lista(ListaPrioridad* lista) {
    if (lista->cabeza == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
    
    Nodo* actual = lista->cabeza;
    while (actual != NULL) {
        printf("Dato: %d, Prioridad: %d\n", actual->dato, actual->prioridad);
        actual = actual->siguiente;
    }
}
