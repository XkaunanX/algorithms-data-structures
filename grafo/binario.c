#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo
typedef struct Nodo {
    int id;
    struct Nodo* siguiente;
} Nodo;

// Estructura para el grafo
typedef struct Grafo {
    int num_nodos_conjunto_1;  // Numero de nodos en el conjunto 1
    int num_nodos_conjunto_2;  // Numero de nodos en el conjunto 2
    Nodo** lista_adjacencia_conjunto_1;  // Lista de adyacencia para los nodos del conjunto 1
    Nodo** lista_adjacencia_conjunto_2;  // Lista de adyacencia para los nodos del conjunto 2
} Grafo;

// Funcion para inicializar un grafo bipartito
void inicializar_grafo(Grafo* grafo, int num_nodos_conjunto_1, int num_nodos_conjunto_2) {
    grafo->num_nodos_conjunto_1 = num_nodos_conjunto_1;
    grafo->num_nodos_conjunto_2 = num_nodos_conjunto_2;

    // Inicializar las listas de adyacencia
    grafo->lista_adjacencia_conjunto_1 = (Nodo**)malloc(num_nodos_conjunto_1 * sizeof(Nodo*));
    grafo->lista_adjacencia_conjunto_2 = (Nodo**)malloc(num_nodos_conjunto_2 * sizeof(Nodo*));

    // Inicializar las listas de adyacencia a NULL
    for (int i = 0; i < num_nodos_conjunto_1; i++) {
        grafo->lista_adjacencia_conjunto_1[i] = NULL;
    }
    for (int i = 0; i < num_nodos_conjunto_2; i++) {
        grafo->lista_adjacencia_conjunto_2[i] = NULL;
    }
}

// Funcion para agregar una arista entre un nodo de conjunto 1 y un nodo de conjunto 2
void agregar_arista(Grafo* grafo, int nodo_conjunto_1, int nodo_conjunto_2) {
    // Verificar que los nodos esten en el rango correcto
    if (nodo_conjunto_1 < 1 || nodo_conjunto_1 > grafo->num_nodos_conjunto_1 ||
        nodo_conjunto_2 < 1 || nodo_conjunto_2 > grafo->num_nodos_conjunto_2) {
        printf("Error: Nodo fuera de rango.\n");
        return;
    }

    // Crear el nuevo nodo de la lista de adyacencia del conjunto 1
    Nodo* nuevo_nodo_1 = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo_1->id = nodo_conjunto_2;
    nuevo_nodo_1->siguiente = grafo->lista_adjacencia_conjunto_1[nodo_conjunto_1 - 1];
    grafo->lista_adjacencia_conjunto_1[nodo_conjunto_1 - 1] = nuevo_nodo_1;

    // Crear el nuevo nodo de la lista de adyacencia del conjunto 2
    Nodo* nuevo_nodo_2 = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo_2->id = nodo_conjunto_1;
    nuevo_nodo_2->siguiente = grafo->lista_adjacencia_conjunto_2[nodo_conjunto_2 - 1];
    grafo->lista_adjacencia_conjunto_2[nodo_conjunto_2 - 1] = nuevo_nodo_2;

    printf("Arista agregada entre nodo %d (conjunto 1) y nodo %d (conjunto 2)\n", nodo_conjunto_1, nodo_conjunto_2);
}

// Funcion para imprimir el grafo
void imprimir_grafo(Grafo* grafo) {
    printf("Conjunto 1 (Nodo | Adyacentes):\n");
    for (int i = 0; i < grafo->num_nodos_conjunto_1; i++) {
        Nodo* temp = grafo->lista_adjacencia_conjunto_1[i];
        printf("Nodo %d: ", i + 1);
        while (temp != NULL) {
            printf("%d ", temp->id);
            temp = temp->siguiente;
        }
        printf("\n");
    }

    printf("\nConjunto 2 (Nodo | Adyacentes):\n");
    for (int i = 0; i < grafo->num_nodos_conjunto_2; i++) {
        Nodo* temp = grafo->lista_adjacencia_conjunto_2[i];
        printf("Nodo %d: ", i + 1);
        while (temp != NULL) {
            printf("%d ", temp->id);
            temp = temp->siguiente;
        }
        printf("\n");
    }
}

// Funcion para liberar la memoria del grafo
void liberar_grafo(Grafo* grafo) {
    for (int i = 0; i < grafo->num_nodos_conjunto_1; i++) {
        Nodo* temp = grafo->lista_adjacencia_conjunto_1[i];
        while (temp != NULL) {
            Nodo* eliminar = temp;
            temp = temp->siguiente;
            free(eliminar);
        }
    }

    for (int i = 0; i < grafo->num_nodos_conjunto_2; i++) {
        Nodo* temp = grafo->lista_adjacencia_conjunto_2[i];
        while (temp != NULL) {
            Nodo* eliminar = temp;
            temp = temp->siguiente;
            free(eliminar);
        }
    }

    free(grafo->lista_adjacencia_conjunto_1);
    free(grafo->lista_adjacencia_conjunto_2);
}

// Funcion principal
int main() {
    Grafo grafo;
    
    // Inicializar un grafo bipartito con 3 nodos en el conjunto 1 y 4 nodos en el conjunto 2
    inicializar_grafo(&grafo, 3, 4);

    // Agregar algunas aristas
    agregar_arista(&grafo, 1, 2);
    agregar_arista(&grafo, 1, 4);
    agregar_arista(&grafo, 2, 3);
    agregar_arista(&grafo, 3, 2);
    agregar_arista(&grafo, 3, 4);

    // Imprimir el grafo
    imprimir_grafo(&grafo);

    // Liberar la memoria del grafo
    liberar_grafo(&grafo);

    return 0;
}
