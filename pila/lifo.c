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

// Estructura para el nodo de una lista enlazada (pila)
typedef struct NodoEnlazado {
    Data Dato;
    struct NodoEnlazado *siguiente;
} Nodo;

// Estructura para gestionar la pila
typedef struct Pila {
    Nodo *tope;       // Nodo superior de la pila
    int longitud;     // Numero de nodos en la pila
} Pila;

// Firmas de funciones para la gestion de la pila
void inicializar_pila(Pila *pila);
void push(Data dato, Pila *pila);
void pop(Pila *pila);
Nodo* peek(Pila *pila);
int pila_vacia(Pila *pila);

// Firmas de funciones auxiliares
int int_aleatorio();
void imprimir_pila(Pila *pila);
void imprimir_nodo(Nodo *nodo);
void menu_consola(Pila *pila);

// Funcion para la gestion de la consola
void menu_consola(Pila *pila) {
    int interfaz = 1;
    int seleccion;
    while (interfaz == STATUS_CONTINUAR) {
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar elemento (push)\n");
        printf("2. Eliminar elemento (pop)\n");
        printf("3. Consultar elemento superior (peek)\n");
        printf("4. Imprimir pila\n");
        printf("5. Consultar longitud de la pila\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        switch (seleccion) {
            case 1:
                id++;
                Data dato;
                dato.i = id;
                dato.valor = int_aleatorio();
                push(dato, pila);
                break;
            case 2:
                pop(pila);
                break;
            case 3:
                imprimir_nodo(peek(pila));
                break;
            case 4:
                imprimir_pila(pila);
                break;
            case 5:
                printf("Tamaño de la pila: %d\n", pila->longitud);
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
}

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));
    Pila pila;
    inicializar_pila(&pila);
    menu_consola(&pila);
    return 0;
}

// Inicializar la pila
void inicializar_pila(Pila *pila) {
    pila->tope = NULL;
    pila->longitud = 0;
}

// Insertar elemento en la pila (push)
void push(Data dato, Pila *pila) {
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->siguiente = pila->tope;
    pila->tope = nuevo_nodo;
    pila->longitud++;
    printf("Elemento insertado: ID = %d, Valor = %d\n", dato.i, dato.valor);
}

// Eliminar elemento de la pila (pop)
void pop(Pila *pila) {
    if (pila_vacia(pila)) {
        printf("La pila esta vacia. No se puede eliminar.\n");
        return;
    }
    Nodo *nodo_a_eliminar = pila->tope;
    pila->tope = pila->tope->siguiente;
    printf("Elemento eliminado: ID = %d, Valor = %d\n", nodo_a_eliminar->Dato.i, nodo_a_eliminar->Dato.valor);
    free(nodo_a_eliminar);
    pila->longitud--;
}

// Consultar el elemento superior de la pila (peek)
Nodo* peek(Pila *pila) {
    if (pila_vacia(pila)) {
        printf("La pila esta vacia.\n");
        return NULL;
    }
    return pila->tope;
}

// Verificar si la pila esta vacia
int pila_vacia(Pila *pila) {
    return pila->tope == NULL;
}

// Generar un numero aleatorio
int int_aleatorio() {
    return rand() % 100;
}

// Imprimir la pila
void imprimir_pila(Pila *pila) {
    Nodo *nodo_actual = pila->tope;
    printf("Contenido de la pila:\n");
    printf("------------------------------------------\n");
    printf("|  i  |   Valor   |     Direccion     |\n");
    printf("------------------------------------------\n");
    while (nodo_actual != NULL) {
        printf("| %3d | %9d | %p |\n",
               nodo_actual->Dato.i,
               nodo_actual->Dato.valor,
               (void*)nodo_actual);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("------------------------------------------\n");
}

// Imprimir un nodo
void imprimir_nodo(Nodo *nodo) {
    if (nodo == NULL) {
        printf("El nodo es NULL. No se puede imprimir.\n");
        return;
    }
    printf("Detalles del nodo superior:\n");
    printf("ID: %d\n", nodo->Dato.i);
    printf("Valor: %d\n", nodo->Dato.valor);
    printf("Direccion: %p\n", (void*)nodo);
}
