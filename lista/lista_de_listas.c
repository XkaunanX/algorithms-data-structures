#include <stdio.h>
#include <stdlib.h>

#define STATUS_CONTINUAR 1

int ejecucion;

// Definimos una estructura de nodo para una lista interna
typedef struct NodoInterno {
    int valor;
    struct NodoInterno *siguiente;
} NodoInterno;

// Estructura para gestionar una lista interna
typedef struct ListaInterna {
    NodoInterno *cabeza;  // Primer nodo de la lista interna
    NodoInterno *final;   // Ultimo nodo de la lista interna
    int longitud;         // Numero de nodos en la lista interna
} ListaInterna;

// Estructura de nodo para la lista principal que contiene una lista interna
typedef struct NodoListaDeListas {
    ListaInterna *lista_interna;  // Puntero a una lista interna
    struct NodoListaDeListas *siguiente;  // Puntero al siguiente nodo de la lista principal
} NodoListaDeListas;

// Estructura para gestionar la lista de listas
typedef struct ListaDeListas {
    NodoListaDeListas *cabeza;   // Primer nodo de la lista principal
    NodoListaDeListas *final;    // Ultimo nodo de la lista principal
    int longitud;                // Numero de nodos en la lista principal
} ListaDeListas;

// Funciones de gestion de la lista de listas
void inicializar_lista_de_listas(ListaDeListas *punteros_lista);
void insertar_lista_interna(ListaDeListas *punteros_lista);
void insertar_nodo_en_lista_interna(ListaInterna *lista_interna, int valor);
void eliminar_lista_interna(int posicion, ListaDeListas *punteros_lista);
void eliminar_nodo_en_lista_interna(ListaInterna *lista_interna, int valor);
void imprimir_lista_de_listas(ListaDeListas *punteros_lista);
void imprimir_lista_interna(ListaInterna *lista_interna);
void menu_consola(ListaDeListas *punteros_lista);

int main() {
    ejecucion = 1;
    ListaDeListas *punteros_lista = (ListaDeListas*) malloc(sizeof(ListaDeListas));
    inicializar_lista_de_listas(punteros_lista);

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(punteros_lista);
    }

    return 0;
}

// Inicializa la lista de listas
void inicializar_lista_de_listas(ListaDeListas *punteros_lista) {
    punteros_lista->cabeza = NULL;
    punteros_lista->final = NULL;
    punteros_lista->longitud = 0;
}

// Inserta una nueva lista interna en la lista de listas
void insertar_lista_interna(ListaDeListas *punteros_lista) {
    NodoListaDeListas *nuevo_nodo = (NodoListaDeListas*) malloc(sizeof(NodoListaDeListas));
    ListaInterna *lista_interna = (ListaInterna*) malloc(sizeof(ListaInterna));
    lista_interna->cabeza = NULL;
    lista_interna->final = NULL;
    lista_interna->longitud = 0;

    nuevo_nodo->lista_interna = lista_interna;
    nuevo_nodo->siguiente = NULL;

    if (punteros_lista->cabeza == NULL) {
        punteros_lista->cabeza = nuevo_nodo;
        punteros_lista->final = nuevo_nodo;
    } else {
        punteros_lista->final->siguiente = nuevo_nodo;
        punteros_lista->final = nuevo_nodo;
    }
    punteros_lista->longitud++;
}

// Inserta un nuevo nodo con valor en una lista interna
void insertar_nodo_en_lista_interna(ListaInterna *lista_interna, int valor) {
    NodoInterno *nuevo_nodo = (NodoInterno*) malloc(sizeof(NodoInterno));
    nuevo_nodo->valor = valor;
    nuevo_nodo->siguiente = NULL;

    if (lista_interna->cabeza == NULL) {
        lista_interna->cabeza = nuevo_nodo;
        lista_interna->final = nuevo_nodo;
    } else {
        lista_interna->final->siguiente = nuevo_nodo;
        lista_interna->final = nuevo_nodo;
    }
    lista_interna->longitud++;
}

// Elimina una lista interna en la lista de listas
void eliminar_lista_interna(int posicion, ListaDeListas *punteros_lista) {
    if (punteros_lista->cabeza == NULL || posicion < 0 || posicion >= punteros_lista->longitud) {
        printf("Posicion invalida o lista vacia\n");
        return;
    }

    NodoListaDeListas *nodo_actual = punteros_lista->cabeza;
    NodoListaDeListas *nodo_anterior = NULL;

    for (int i = 0; i < posicion; i++) {
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }

    if (nodo_anterior == NULL) {
        punteros_lista->cabeza = nodo_actual->siguiente;
    } else {
        nodo_anterior->siguiente = nodo_actual->siguiente;
    }

    NodoInterno *nodo_interno = nodo_actual->lista_interna->cabeza;
    while (nodo_interno != NULL) {
        NodoInterno *temp = nodo_interno;
        nodo_interno = nodo_interno->siguiente;
        free(temp);
    }
    free(nodo_actual->lista_interna);
    free(nodo_actual);
    punteros_lista->longitud--;
}

// Elimina un nodo con un valor especifico en una lista interna
void eliminar_nodo_en_lista_interna(ListaInterna *lista_interna, int valor) {
    NodoInterno *nodo_actual = lista_interna->cabeza;
    NodoInterno *nodo_anterior = NULL;

    while (nodo_actual != NULL) {
        if (nodo_actual->valor == valor) {
            if (nodo_anterior == NULL) {
                lista_interna->cabeza = nodo_actual->siguiente;
            } else {
                nodo_anterior->siguiente = nodo_actual->siguiente;
            }

            if (nodo_actual == lista_interna->final) {
                lista_interna->final = nodo_anterior;
            }

            free(nodo_actual);
            lista_interna->longitud--;
            return;
        }
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }

    printf("Valor no encontrado en la lista interna\n");
}

// Imprime la lista de listas
void imprimir_lista_de_listas(ListaDeListas *punteros_lista) {
    NodoListaDeListas *nodo_actual = punteros_lista->cabeza;
    printf("Contenido de la lista de listas:\n");
    printf("--------------------------------------------------\n");
    int lista_numero = 1;
    while (nodo_actual != NULL) {
        printf("Lista interna %d:\n", lista_numero++);
        imprimir_lista_interna(nodo_actual->lista_interna);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("--------------------------------------------------\n");
}

// Imprime una lista interna
void imprimir_lista_interna(ListaInterna *lista_interna) {
    NodoInterno *nodo_actual = lista_interna->cabeza;
    while (nodo_actual != NULL) {
        printf("%d -> ", nodo_actual->valor);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("NULL\n");
}

// Funcion para gestionar el menu de la consola
void menu_consola(ListaDeListas *punteros_lista) {
    int seleccion, valor, posicion;

    printf("MENU\n\n");
    printf("1. Insertar una nueva lista interna\n");
    printf("2. Insertar un valor en una lista interna\n");
    printf("3. Eliminar una lista interna\n");
    printf("4. Eliminar un valor de una lista interna\n");
    printf("5. Imprimir lista de listas\n");
    printf("0. Fin programa\n\n");
    printf("> Seleccione una opcion: ");
    scanf("%d", &seleccion);

    switch (seleccion) {
    case 1:
        insertar_lista_interna(punteros_lista);
        break;
    case 2:
        printf("> Ingrese la lista interna donde insertar: ");
        scanf("%d", &posicion);
        printf("> Ingrese el valor a insertar: ");
        scanf("%d", &valor);
        {
            NodoListaDeListas *nodo_actual = punteros_lista->cabeza;
            for (int i = 0; i < posicion && nodo_actual != NULL; i++) {
                nodo_actual = nodo_actual->siguiente;
            }
            if (nodo_actual != NULL) {
                insertar_nodo_en_lista_interna(nodo_actual->lista_interna, valor);
            } else {
                printf("Lista interna no encontrada\n");
            }
        }
        break;
    case 3:
        printf("> Ingrese la posicion de la lista interna a eliminar: ");
        scanf("%d", &posicion);
        eliminar_lista_interna(posicion, punteros_lista);
        break;
    case 4:
        printf("> Ingrese la posicion de la lista interna: ");
        scanf("%d", &posicion);
        printf("> Ingrese el valor a eliminar: ");
        scanf("%d", &valor);
        {
            NodoListaDeListas *nodo_actual = punteros_lista->cabeza;
            for (int i = 0; i < posicion && nodo_actual != NULL; i++) {
                nodo_actual = nodo_actual->siguiente;
            }
            if (nodo_actual != NULL) {
                eliminar_nodo_en_lista_interna(nodo_actual->lista_interna, valor);
            } else {
                printf("Lista interna no encontrada\n");
            }
        }
        break;
    case 5:
        imprimir_lista_de_listas(punteros_lista);
        break;
    case 0:
        printf("Fin del programa ...\n");
        ejecucion = 0;
        break;
    default:
        printf("Opcion invalida\n");
        break;
    }
}
