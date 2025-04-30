#include <stdio.h>
#include <stdlib.h>

// Estructura para representar una arista
typedef struct Arista {
    int destino;
    int peso;
    struct Arista* siguiente;
} Arista;

// Estructura para el grafo
typedef struct Grafo {
    int num_nodos;         // Numero de nodos
    Arista** lista_adjacencia;  // Lista de adyacencia para las aristas
} Grafo;

// Funcion para inicializar un grafo con un numero de nodos
void inicializar_grafo(Grafo* grafo, int num_nodos) {
    grafo->num_nodos = num_nodos;
    grafo->lista_adjacencia = (Arista**)malloc(num_nodos * sizeof(Arista*));

    for (int i = 0; i < num_nodos; i++) {
        grafo->lista_adjacencia[i] = NULL;
    }
}

// Funcion para agregar una arista ponderada entre dos nodos
void agregar_arista(Grafo* grafo, int origen, int destino, int peso) {
    // Crear la nueva arista para el nodo origen
    Arista* nueva_arista = (Arista*)malloc(sizeof(Arista));
    nueva_arista->destino = destino;
    nueva_arista->peso = peso;
    nueva_arista->siguiente = grafo->lista_adjacencia[origen];
    grafo->lista_adjacencia[origen] = nueva_arista;

    // Como es un grafo no dirigido, agregar tambien la arista en el sentido contrario
    nueva_arista = (Arista*)malloc(sizeof(Arista));
    nueva_arista->destino = origen;
    nueva_arista->peso = peso;
    nueva_arista->siguiente = grafo->lista_adjacencia[destino];
    grafo->lista_adjacencia[destino] = nueva_arista;

    printf("Arista agregada entre %d y %d con peso %d\n", origen, destino, peso);
}

// Funcion para imprimir el grafo
void imprimir_grafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_nodos; i++) {
        Arista* temp = grafo->lista_adjacencia[i];
        printf("Nodo %d:", i);
        while (temp != NULL) {
            printf(" -> %d (peso: %d)", temp->destino, temp->peso);
            temp = temp->siguiente;
        }
        printf("\n");
    }
}

// Funcion para liberar la memoria del grafo
void liberar_grafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_nodos; i++) {
        Arista* temp = grafo->lista_adjacencia[i];
        while (temp != NULL) {
            Arista* eliminar = temp;
            temp = temp->siguiente;
            free(eliminar);
        }
    }
    free(grafo->lista_adjacencia);
}

// Funcion principal
int main() {
    Grafo grafo;
    
    // Inicializar un grafo con 5 nodos
    inicializar_grafo(&grafo, 5);

    // Agregar algunas aristas ponderadas
    agregar_arista(&grafo, 0, 1, 10);
    agregar_arista(&grafo, 0, 4, 20);
    agregar_arista(&grafo, 1, 2, 30);
    agregar_arista(&grafo, 1, 3, 40);
    agregar_arista(&grafo, 2, 4, 50);

    // Imprimir el grafo
    imprimir_grafo(&grafo);

    // Liberar la memoria del grafo
    liberar_grafo(&grafo);

    return 0;
}
