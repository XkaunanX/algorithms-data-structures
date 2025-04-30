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

// Estructura para el nodo de una lista doblemente circular
typedef struct NodoEnlazado {
    Data Dato;
    struct NodoEnlazado *siguiente;
    struct NodoEnlazado *anterior;
} Nodo;

// Estructura para gestionar la lista doblemente circular
typedef struct ListaEnlazada {
    Nodo *cabeza;      // Primer nodo de la lista
    Nodo *final;       // Ultimo nodo de la lista
    int longitud;      // Numero de nodos en la lista
} ListaEnlazada;

// Firmas de funciones para la gestion de la lista doblemente circular
void inicializar_lista(ListaEnlazada *punteros_lista);
void insertar_nodo(Data dato, ListaEnlazada *punteros_lista);
void eliminar_nodo(int id, ListaEnlazada *punteros_lista);
void modificar_nodo(int id, ListaEnlazada *punteros_lista);
Nodo* consultar_nodo(int id, ListaEnlazada *punteros_lista);

// Firmas de funciones auxiliares
int int_aleatorio();
void imprimir_lista(ListaEnlazada *punteros_lista);
void imprimir_nodo(Nodo *nodo);

// Funcion para la gestion de la consola
void menu_consola(ListaEnlazada *punteros_lista)
{
    int interfaz = 1;
    int seleccion;
    int size;
    int i;
    while (interfaz == STATUS_CONTINUAR)
    {
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar nodo a la lista\n");
        printf("2. Eliminar nodo de la lista\n");
        printf("3. Modificar un nodo\n");
        printf("4. Consultar nodo\n");
        printf("5. Consultar longitud de lista\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        switch (seleccion)
        {
        case 1:  
            id++;
            Data dato;
            dato.i = id;
            dato.valor = int_aleatorio();
            insertar_nodo(dato, punteros_lista);
            break;
        case 2:
            printf("> Ingrese un id: ");
            scanf("%d", &i);
            eliminar_nodo(i , punteros_lista);
            break;
        case 3:
            printf("> Ingrese un id: ");
            scanf("%d", &i);
            modificar_nodo(i , punteros_lista);
            break;
        case 4:
            printf("> Ingrese un id: ");
            scanf("%d", &i);
            Nodo* nodo = consultar_nodo(i , punteros_lista);
            imprimir_nodo(nodo);
            break;
        case 5:
            size = punteros_lista->longitud;
            printf("Tamaño de la lista doblemente circular: %d\n", size);
            break;
        case 0:
            printf("Fin programa ...");
            exit(0);
            break;   
        default:
            printf("Error: ingreso un valor incorrecto\n");
            break;
        }
        imprimir_lista(punteros_lista);
        system("PAUSE");
    }
}

// Hilo principal
int main()
{
    ejecucion = 1;
    srand(time(NULL));
    ListaEnlazada *punteros_lista = (ListaEnlazada *)malloc(sizeof(ListaEnlazada));
    inicializar_lista(punteros_lista);
    while (ejecucion == STATUS_CONTINUAR)
    {
        menu_consola(punteros_lista);
    }
    return 0;
}

void inicializar_lista(ListaEnlazada *punteros_lista)
{
    punteros_lista->cabeza = NULL;
    punteros_lista->final = NULL;
    punteros_lista->longitud = 0;
}

void insertar_nodo(Data dato, ListaEnlazada *punteros_lista)
{
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->Dato.i = dato.i;
    nuevo_nodo->Dato.valor = dato.valor;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->anterior = NULL;

    if (punteros_lista->cabeza == NULL) {
        // Si la lista esta vacia, el nodo es el unico en la lista y se apunta a si mismo
        punteros_lista->cabeza = nuevo_nodo;
        punteros_lista->final = nuevo_nodo;
        nuevo_nodo->siguiente = nuevo_nodo;
        nuevo_nodo->anterior = nuevo_nodo;
    } else {
        // Si la lista tiene nodos, insertamos al final
        nuevo_nodo->anterior = punteros_lista->final;
        nuevo_nodo->siguiente = punteros_lista->cabeza;
        punteros_lista->final->siguiente = nuevo_nodo;
        punteros_lista->cabeza->anterior = nuevo_nodo;
        punteros_lista->final = nuevo_nodo;
    }
    punteros_lista->longitud++;
}

void eliminar_nodo(int id, ListaEnlazada *punteros_lista)
{
    if (punteros_lista->cabeza == NULL) {
        printf("La lista esta vacia\n");
        return;
    }

    Nodo *nodo_actual = punteros_lista->cabeza;
    do {
        if (nodo_actual->Dato.i == id) {
            if (nodo_actual == punteros_lista->cabeza && nodo_actual == punteros_lista->final) {
                // Si solo hay un nodo en la lista
                punteros_lista->cabeza = NULL;
                punteros_lista->final = NULL;
            } else if (nodo_actual == punteros_lista->cabeza) {
                // Si es el primer nodo
                punteros_lista->cabeza = nodo_actual->siguiente;
                punteros_lista->cabeza->anterior = punteros_lista->final;
                punteros_lista->final->siguiente = punteros_lista->cabeza;
            } else if (nodo_actual == punteros_lista->final) {
                // Si es el ultimo nodo
                punteros_lista->final = nodo_actual->anterior;
                punteros_lista->final->siguiente = punteros_lista->cabeza;
                punteros_lista->cabeza->anterior = punteros_lista->final;
            } else {
                // Si es un nodo intermedio
                nodo_actual->anterior->siguiente = nodo_actual->siguiente;
                nodo_actual->siguiente->anterior = nodo_actual->anterior;
            }
            free(nodo_actual);
            punteros_lista->longitud--;
            return;
        }
        nodo_actual = nodo_actual->siguiente;
    } while (nodo_actual != punteros_lista->cabeza);
}

void modificar_nodo(int id, ListaEnlazada *punteros_lista)
{
    Nodo *nodo_actual = punteros_lista->cabeza;
    do {
        if (nodo_actual->Dato.i == id) {
            nodo_actual->Dato.valor = int_aleatorio();
            return;
        }
        nodo_actual = nodo_actual->siguiente;
    } while (nodo_actual != punteros_lista->cabeza);
    printf("Nodo con ID %d no encontrado.\n", id);
}

Nodo *consultar_nodo(int id, ListaEnlazada *punteros_lista)
{
    Nodo *nodo_actual = punteros_lista->cabeza;
    do {
        if (nodo_actual->Dato.i == id) {
            return nodo_actual;
        }
        nodo_actual = nodo_actual->siguiente;
    } while (nodo_actual != punteros_lista->cabeza);
    return NULL;
}

int int_aleatorio()
{
    return rand() % 100;
}

void imprimir_lista(ListaEnlazada *punteros_lista)
{
    if (punteros_lista->cabeza == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    Nodo *nodo_actual = punteros_lista->cabeza;
    printf("Contenido de la lista doblemente circular:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   |     Direccion     |   Anterior   |   Siguiente   |\n");
    printf("--------------------------------------------------\n");

    do {
        printf("| %3d | %9d | %p | %p | %p |\n", 
               nodo_actual->Dato.i, 
               nodo_actual->Dato.valor, 
               (void*)nodo_actual, 
               (void*)nodo_actual->anterior, 
               (void*)nodo_actual->siguiente);
        nodo_actual = nodo_actual->siguiente;
    } while (nodo_actual != punteros_lista->cabeza);
    printf("--------------------------------------------------\n");
}

void imprimir_nodo(Nodo *nodo)
{
    if (nodo == NULL) {
        printf("El nodo es NULL. No se puede imprimir.\n");
        return;
    }
    printf("Detalles del nodo:\n");
    printf("ID: %d\n", nodo->Dato.i);
    printf("Valor: %d\n", nodo->Dato.valor);
    printf("Direccion: %p\n", (void*)nodo);
    printf("Anterior: %p\n", (void*)nodo->anterior);
    printf("Siguiente: %p\n", (void*)nodo->siguiente);
}
