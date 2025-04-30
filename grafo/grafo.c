#include <stdio.h>
#include <stdlib.h>

#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
} Data;

// Estructura para el nodo de la lista de adyacencia
typedef struct Arista {
    int destino;
    struct Arista *siguiente;
} Arista;

// Estructura para el nodo del grafo
typedef struct NodoGrafo {
    Data Dato;
    Arista *adyacentes;
    struct NodoGrafo *siguiente;
} NodoGrafo;

// Estructura para gestionar el grafo
typedef struct Grafo {
    NodoGrafo *cabeza;
    int num_nodos;
} Grafo;

// Firmas de funciones para la gestion del grafo
void inicializar_grafo(Grafo *grafo);
void insertar_nodo(Data dato, Grafo *grafo);
void insertar_arista(int origen, int destino, Grafo *grafo);
void eliminar_nodo(int id, Grafo *grafo);
void eliminar_arista(int origen, int destino, Grafo *grafo);
void modificar_nodo(int id, Grafo *grafo);
NodoGrafo *consultar_nodo(int id, Grafo *grafo);
void imprimir_grafo(Grafo *grafo);

// Firmas de funciones auxiliares
int int_aleatorio();
void imprimir_nodo(NodoGrafo *nodo);
void imprimir_adyacentes(Arista *adyacente);

// Funcion para la gestion de la consola
void menu_consola(Grafo *grafo) {
    int interfaz = 1;
    int seleccion;
    int id_origen, id_destino;
    Data dato;
    while (interfaz == STATUS_CONTINUAR) {
        system("CLS");
        printf("MENU GRAFO\n\n");
        printf("1. Insertar nodo\n");
        printf("2. Insertar arista\n");
        printf("3. Eliminar nodo\n");
        printf("4. Eliminar arista\n");
        printf("5. Modificar nodo\n");
        printf("6. Consultar nodo\n");
        printf("7. Imprimir grafo\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");

        switch (seleccion) {
        case 1:
            id++;
            dato.i = id;
            dato.valor = int_aleatorio();
            insertar_nodo(dato, grafo);
            break;
        case 2:
            printf("> Ingrese el id del nodo origen: ");
            scanf("%d", &id_origen);
            printf("> Ingrese el id del nodo destino: ");
            scanf("%d", &id_destino);
            insertar_arista(id_origen, id_destino, grafo);
            break;
        case 3:
            printf("> Ingrese el id del nodo a eliminar: ");
            scanf("%d", &id_origen);
            eliminar_nodo(id_origen, grafo);
            break;
        case 4:
            printf("> Ingrese el id del nodo origen: ");
            scanf("%d", &id_origen);
            printf("> Ingrese el id del nodo destino: ");
            scanf("%d", &id_destino);
            eliminar_arista(id_origen, id_destino, grafo);
            break;
        case 5:
            printf("> Ingrese el id del nodo a modificar: ");
            scanf("%d", &id_origen);
            modificar_nodo(id_origen, grafo);
            break;
        case 6:
            printf("> Ingrese el id del nodo a consultar: ");
            scanf("%d", &id_origen);
            imprimir_nodo(consultar_nodo(id_origen, grafo));
            break;
        case 7:
            imprimir_grafo(grafo);
            break;
        case 0:
            printf("Fin programa ...\n");
            exit(0);
        default:
            printf("Error: ingreso un valor incorrecto\n");
            break;
        }
        system("PAUSE");
    }
}

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));
    Grafo grafo;
    inicializar_grafo(&grafo);
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&grafo);
    }
    return 0;
}

void inicializar_grafo(Grafo *grafo) {
    grafo->cabeza = NULL;
    grafo->num_nodos = 0;
}

void insertar_nodo(Data dato, Grafo *grafo) {
    NodoGrafo *nuevo_nodo = malloc(sizeof(NodoGrafo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->adyacentes = NULL;
    nuevo_nodo->siguiente = grafo->cabeza;
    grafo->cabeza = nuevo_nodo;
    grafo->num_nodos++;
}

void insertar_arista(int origen, int destino, Grafo *grafo) {
    NodoGrafo *nodo_origen = consultar_nodo(origen, grafo);
    if (nodo_origen == NULL) return;
    Arista *nueva_arista = malloc(sizeof(Arista));
    nueva_arista->destino = destino;
    nueva_arista->siguiente = nodo_origen->adyacentes;
    nodo_origen->adyacentes = nueva_arista;
}

void eliminar_nodo(int id, Grafo *grafo) {
    NodoGrafo *anterior = NULL;
    NodoGrafo *actual = grafo->cabeza;
    while (actual != NULL && actual->Dato.i != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) return;
    if (anterior == NULL) grafo->cabeza = actual->siguiente;
    else anterior->siguiente = actual->siguiente;
    free(actual);
    grafo->num_nodos--;
}

void eliminar_arista(int origen, int destino, Grafo *grafo) {
    NodoGrafo *nodo_origen = consultar_nodo(origen, grafo);
    if (nodo_origen == NULL) return;
    Arista *anterior = NULL;
    Arista *actual = nodo_origen->adyacentes;
    while (actual != NULL && actual->destino != destino) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == NULL) return;
    if (anterior == NULL) nodo_origen->adyacentes = actual->siguiente;
    else anterior->siguiente = actual->siguiente;
    free(actual);
}

void modificar_nodo(int id, Grafo *grafo) {
    NodoGrafo *nodo = consultar_nodo(id, grafo);
    if (nodo == NULL) return;
    nodo->Dato.valor = int_aleatorio();
}

NodoGrafo *consultar_nodo(int id, Grafo *grafo) {
    NodoGrafo *actual = grafo->cabeza;
    while (actual != NULL && actual->Dato.i != id) {
        actual = actual->siguiente;
    }
    return actual;
}

int int_aleatorio() {
    return rand() % 100;
}

void imprimir_nodo(NodoGrafo *nodo) {
    if (nodo == NULL) {
        printf("Nodo no encontrado.\n");
        return;
    }
    printf("ID: %d, Valor: %d\n", nodo->Dato.i, nodo->Dato.valor);
    imprimir_adyacentes(nodo->adyacentes);
}

void imprimir_adyacentes(Arista *adyacente) {
    while (adyacente != NULL) {
        printf(" -> %d", adyacente->destino);
        adyacente = adyacente->siguiente;
    }
    printf("\n");
}

void imprimir_grafo(Grafo *grafo) {
    NodoGrafo *nodo = grafo->cabeza;
    while (nodo != NULL) {
        printf("Nodo %d:", nodo->Dato.i);
        imprimir_adyacentes(nodo->adyacentes);
        nodo = nodo->siguiente;
    }
}
