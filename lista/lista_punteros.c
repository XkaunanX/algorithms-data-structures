#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_CONTINUAR 1

int ejecucion;

// Definimos una estructura "Persona"
typedef struct Persona {
    char nombre[50];
    int edad;
} Persona;

// Nodo de la lista enlazada que contiene un puntero a una estructura Persona
typedef struct Nodo {
    Persona *persona;            // Puntero a una estructura Persona
    struct Nodo *siguiente;      // Puntero al siguiente nodo
} Nodo;

// Estructura para gestionar la lista enlazada
typedef struct ListaEnlazada {
    Nodo *cabeza;                // Primer nodo de la lista
    Nodo *final;                 // Ultimo nodo de la lista
    int longitud;                // Numero de nodos en la lista
} ListaEnlazada;

// Funciones de gestion de la lista enlazada
void inicializar_lista(ListaEnlazada *punteros_lista);
void insertar_nodo(Persona *persona, ListaEnlazada *punteros_lista);
void eliminar_nodo(int posicion, ListaEnlazada *punteros_lista);
void imprimir_lista(ListaEnlazada *punteros_lista);
void menu_consola(ListaEnlazada *punteros_lista);

int main() {
    ejecucion = 1;
    ListaEnlazada *punteros_lista = (ListaEnlazada*) malloc(sizeof(ListaEnlazada));
    inicializar_lista(punteros_lista);

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(punteros_lista);
    }

    return 0;
}

// Inicializa la lista enlazada
void inicializar_lista(ListaEnlazada *punteros_lista) {
    punteros_lista->cabeza = NULL;
    punteros_lista->final = NULL;
    punteros_lista->longitud = 0;
}

// Inserta un nuevo nodo con puntero a una estructura Persona
void insertar_nodo(Persona *persona, ListaEnlazada *punteros_lista) {
    Nodo *nuevo_nodo = (Nodo*) malloc(sizeof(Nodo));
    nuevo_nodo->persona = persona;   // Asignamos el puntero a la estructura Persona
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

// Elimina un nodo en una posicion especifica
void eliminar_nodo(int posicion, ListaEnlazada *punteros_lista) {
    if (punteros_lista->cabeza == NULL || posicion < 0 || posicion >= punteros_lista->longitud) {
        printf("Posicion invalida o lista vacia\n");
        return;
    }

    Nodo *nodo_actual = punteros_lista->cabeza;
    Nodo *nodo_anterior = NULL;

    for (int i = 0; i < posicion; i++) {
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }

    if (nodo_anterior == NULL) {
        punteros_lista->cabeza = nodo_actual->siguiente;
    } else {
        nodo_anterior->siguiente = nodo_actual->siguiente;
    }

    if (nodo_actual == punteros_lista->final) {
        punteros_lista->final = nodo_anterior;
    }

    free(nodo_actual->persona);  // Liberar la memoria de la estructura Persona
    free(nodo_actual);
    punteros_lista->longitud--;
}

// Imprime la lista enlazada de punteros a estructuras Persona
void imprimir_lista(ListaEnlazada *punteros_lista) {
    Nodo *nodo_actual = punteros_lista->cabeza;
    printf("Contenido de la lista enlazada de personas:\n");
    printf("--------------------------------------------------\n");
    while (nodo_actual != NULL) {
        printf("Nombre: %s, Edad: %d\n", nodo_actual->persona->nombre, nodo_actual->persona->edad);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("--------------------------------------------------\n");
}

// Funcion para gestionar el menu de la consola
void menu_consola(ListaEnlazada *punteros_lista) {
    int seleccion;
    int posicion;
    Persona *persona;

    printf("MENU\n\n");
    printf("1. Insertar persona a la lista\n");
    printf("2. Eliminar persona de la lista\n");
    printf("3. Imprimir lista\n");
    printf("0. Fin programa\n\n");
    printf("> Seleccione una opcion: ");
    scanf("%d", &seleccion);

    switch (seleccion) {
    case 1:
        persona = (Persona*) malloc(sizeof(Persona));  // Crear una nueva persona
        printf("> Ingrese el nombre: ");
        scanf(" %[^\n]", persona->nombre);  // Leer nombre con espacios
        printf("> Ingrese la edad: ");
        scanf("%d", &persona->edad);
        insertar_nodo(persona, punteros_lista);
        break;
    case 2:
        printf("> Ingrese la posicion del nodo a eliminar: ");
        scanf("%d", &posicion);
        eliminar_nodo(posicion, punteros_lista);
        break;
    case 3:
        imprimir_lista(punteros_lista);
        break;
    case 0:
        printf("Fin programa ...\n");
        exit(0);
        break;
    default:
        printf("Error: ingreso un valor incorrecto\n");
        break;
    }
    system("PAUSE");
}
