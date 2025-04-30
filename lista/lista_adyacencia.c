#include <stdio.h>
#include <stdlib.h>

#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct{
    int i;   // ID del vertice
} Data;

// Estructura para el nodo de la lista de adyacencia
typedef struct NodoAdyacencia {
    int destino;                 // Vertice adyacente
    struct NodoAdyacencia *siguiente;  // Siguiente nodo adyacente
} NodoAdyacencia;

// Estructura para gestionar la lista de adyacencia
typedef struct Grafo {
    int V;  // Numero de vertices
    NodoAdyacencia **lista; // Lista de adyacencia
} Grafo;

// Firmas de funciones para la gestion de la lista de adyacencia
Grafo* crear_grafo(int V);
void agregar_arista(Grafo *grafo, int origen, int destino);
void eliminar_arista(Grafo *grafo, int origen, int destino);
void imprimir_grafo(Grafo *grafo);
void menu_consola(Grafo *grafo);

int main() {
    ejecucion = 1;
    srand(time(NULL));
    
    int V = 5;  // Numero de vertices en el grafo
    Grafo *grafo = crear_grafo(V);

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(grafo);
    }

    return 0;
}

// Funcion para crear un grafo con V vertices
Grafo* crear_grafo(int V) {
    Grafo *grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->V = V;
    grafo->lista = (NodoAdyacencia**) malloc(V * sizeof(NodoAdyacencia*));

    for (int i = 0; i < V; i++) {
        grafo->lista[i] = NULL;
    }

    return grafo;
}

// Funcion para agregar una arista entre dos vertices (origen, destino)
void agregar_arista(Grafo *grafo, int origen, int destino) {
    NodoAdyacencia *nuevo_nodo = (NodoAdyacencia*) malloc(sizeof(NodoAdyacencia));
    nuevo_nodo->destino = destino;
    nuevo_nodo->siguiente = grafo->lista[origen];
    grafo->lista[origen] = nuevo_nodo;

    // Si el grafo es no dirigido, agregamos la arista en ambas direcciones
    nuevo_nodo = (NodoAdyacencia*) malloc(sizeof(NodoAdyacencia));
    nuevo_nodo->destino = origen;
    nuevo_nodo->siguiente = grafo->lista[destino];
    grafo->lista[destino] = nuevo_nodo;
}

// Funcion para eliminar una arista entre dos vertices (origen, destino)
void eliminar_arista(Grafo *grafo, int origen, int destino) {
    NodoAdyacencia *nodo_actual = grafo->lista[origen];
    NodoAdyacencia *nodo_anterior = NULL;

    // Eliminar la arista en el origen
    while (nodo_actual != NULL && nodo_actual->destino != destino) {
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }

    if (nodo_actual != NULL) {
        if (nodo_anterior == NULL) {
            grafo->lista[origen] = nodo_actual->siguiente;
        } else {
            nodo_anterior->siguiente = nodo_actual->siguiente;
        }
        free(nodo_actual);
    }

    // Eliminar la arista en el destino (si el grafo es no dirigido)
    nodo_actual = grafo->lista[destino];
    nodo_anterior = NULL;

    while (nodo_actual != NULL && nodo_actual->destino != origen) {
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }

    if (nodo_actual != NULL) {
        if (nodo_anterior == NULL) {
            grafo->lista[destino] = nodo_actual->siguiente;
        } else {
            nodo_anterior->siguiente = nodo_actual->siguiente;
        }
        free(nodo_actual);
    }
}

// Funcion para imprimir el grafo
void imprimir_grafo(Grafo *grafo) {
    for (int i = 0; i < grafo->V; i++) {
        NodoAdyacencia *nodo_actual = grafo->lista[i];
        printf("Vertice %d: ", i);
        while (nodo_actual != NULL) {
            printf("%d ", nodo_actual->destino);
            nodo_actual = nodo_actual->siguiente;
        }
        printf("\n");
    }
}

// Funcion para gestionar el menu de la consola
void menu_consola(Grafo *grafo) {
    int seleccion;
    int origen, destino;

    printf("MENU\n\n");
    printf("1. Agregar arista\n");
    printf("2. Eliminar arista\n");
    printf("3. Imprimir grafo\n");
    printf("0. Fin programa\n\n");
    printf("> Seleccione una opcion: ");
    scanf("%d", &seleccion);

    switch (seleccion) {
    case 1:
        printf("> Ingrese origen y destino (0-%d): ", grafo->V - 1);
        scanf("%d %d", &origen, &destino);
        agregar_arista(grafo, origen, destino);
        break;
    case 2:
        printf("> Ingrese origen y destino (0-%d): ", grafo->V - 1);
        scanf("%d %d", &origen, &destino);
        eliminar_arista(grafo, origen, destino);
        break;
    case 3:
        imprimir_grafo(grafo);
        break;
    case 0:
        printf("Fin programa ...");
        exit(0);
        break;
    default:
        printf("Error: ingreso un valor incorrecto\n");
        break;
    }
    system("PAUSE");
}
