#include <stdio.h>
#include <stdlib.h>

#define MAX_NODOS 100

// Estructura para un Nodo del DAG
typedef struct Nodo {
    int id;
    struct Nodo* siguiente;
} Nodo;

// Estructura para un DAG
typedef struct DAG {
    int numero_nodos;               // Numero de nodos en el DAG
    Nodo* lista_adjacencia[MAX_NODOS];  // Lista de adyacencia
} DAG;

// Funcion para inicializar el DAG
void inicializar_dag(DAG* dag) {
    dag->numero_nodos = 0;
    for (int i = 0; i < MAX_NODOS; i++) {
        dag->lista_adjacencia[i] = NULL;
    }
}

// Funcion para agregar un nodo al DAG
void agregar_nodo(DAG* dag) {
    if (dag->numero_nodos < MAX_NODOS) {
        dag->numero_nodos++;
        printf("Nodo %d agregado al DAG\n", dag->numero_nodos);
    } else {
        printf("No se pueden agregar mas nodos. Limite alcanzado.\n");
    }
}

// Funcion para agregar una arista dirigida entre dos nodos
void agregar_arista(DAG* dag, int origen, int destino) {
    if (origen < 1 || origen > dag->numero_nodos || destino < 1 || destino > dag->numero_nodos) {
        printf("Error: uno de los nodos no existe.\n");
        return;
    }
    
    // Crear un nuevo nodo para la arista
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->id = destino;
    nuevo_nodo->siguiente = dag->lista_adjacencia[origen - 1];
    dag->lista_adjacencia[origen - 1] = nuevo_nodo;
    printf("Arista de %d -> %d agregada.\n", origen, destino);
}

// Funcion para realizar la busqueda en orden topologico usando DFS
int dfs(int nodo, int* visitado, int* en_pila, DAG* dag, int* orden_topologico) {
    if (en_pila[nodo]) {
        // Se encontro un ciclo (retroceso)
        return 0;
    }
    if (visitado[nodo]) {
        // Ya fue visitado
        return 1;
    }

    // Marcar como visitado y agregar a la pila
    visitado[nodo] = 1;
    en_pila[nodo] = 1;

    // Recursion para todos los nodos adyacentes
    Nodo* adyacente = dag->lista_adjacencia[nodo];
    while (adyacente != NULL) {
        if (!dfs(adyacente->id - 1, visitado, en_pila, dag, orden_topologico)) {
            return 0; // Si hay un ciclo, no podemos ordenar
        }
        adyacente = adyacente->siguiente;
    }

    // Añadir el nodo al orden topologico
    orden_topologico[(*orden_topologico)++] = nodo + 1;
    
    // Eliminar de la pila
    en_pila[nodo] = 0;
    return 1;
}

// Funcion para obtener el orden topologico
int* orden_topologico(DAG* dag) {
    int* orden = (int*)malloc(dag->numero_nodos * sizeof(int));
    int* visitado = (int*)calloc(dag->numero_nodos, sizeof(int));
    int* en_pila = (int*)calloc(dag->numero_nodos, sizeof(int));
    int indice_orden = 0;

    // Ejecutar DFS en todos los nodos
    for (int i = 0; i < dag->numero_nodos; i++) {
        if (!visitado[i]) {
            if (!dfs(i, visitado, en_pila, dag, orden)) {
                printf("Error: El DAG contiene un ciclo. No se puede ordenar topologicamente.\n");
                free(orden);
                free(visitado);
                free(en_pila);
                return NULL;
            }
        }
    }

    free(visitado);
    free(en_pila);
    return orden;
}

// Funcion para imprimir el orden topologico
void imprimir_orden_topologico(DAG* dag) {
    int* orden = orden_topologico(dag);
    if (orden != NULL) {
        printf("Orden topologico: ");
        for (int i = dag->numero_nodos - 1; i >= 0; i--) {
            printf("%d ", orden[i]);
        }
        printf("\n");
        free(orden);
    }
}

// Funcion para imprimir el DAG
void imprimir_dag(DAG* dag) {
    for (int i = 0; i < dag->numero_nodos; i++) {
        printf("Nodo %d -> ", i + 1);
        Nodo* adyacente = dag->lista_adjacencia[i];
        while (adyacente != NULL) {
            printf("%d ", adyacente->id);
            adyacente = adyacente->siguiente;
        }
        printf("\n");
    }
}

// Funcion principal
int main() {
    DAG dag;
    inicializar_dag(&dag);

    // Agregar nodos al DAG
    agregar_nodo(&dag); // Nodo 1
    agregar_nodo(&dag); // Nodo 2
    agregar_nodo(&dag); // Nodo 3
    agregar_nodo(&dag); // Nodo 4

    // Agregar aristas
    agregar_arista(&dag, 1, 2);
    agregar_arista(&dag, 1, 3);
    agregar_arista(&dag, 2, 4);
    agregar_arista(&dag, 3, 4);

    // Imprimir el DAG
    printf("Estructura del DAG:\n");
    imprimir_dag(&dag);

    // Obtener y mostrar el orden topologico
    imprimir_orden_topologico(&dag);

    return 0;
}
