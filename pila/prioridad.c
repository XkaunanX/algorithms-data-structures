#include <stdio.h>
#include <stdlib.h>

#define STATUS_CONTINUAR 1
#define CAPACIDAD 30  // Capacidad maxima de la pila

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
    int prioridad;
} Data;

// Estructura para gestionar la pila de prioridad
typedef struct NodoEnlazado {
    Data Dato;
    struct NodoEnlazado *siguiente;
} Nodo;

// Estructura para la pila de prioridad
typedef struct {
    Nodo *cabeza;
    int longitud;
} PilaPrioridad;

// Firmas de funciones
void inicializar_pila(PilaPrioridad *pila);
void push(Data dato, PilaPrioridad *pila);
int pop(PilaPrioridad *pila);
Nodo* peek(PilaPrioridad *pila);
void imprimir_pila(PilaPrioridad *pila);
int int_aleatorio();
void menu_consola(PilaPrioridad *pila);

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));

    PilaPrioridad pila;
    inicializar_pila(&pila);

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&pila);
    }

    return 0;
}

// Inicializar la pila
void inicializar_pila(PilaPrioridad *pila) {
    pila->cabeza = NULL;
    pila->longitud = 0;
}

// Insertar un elemento en la pila con prioridad
void push(Data dato, PilaPrioridad *pila) {
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->siguiente = NULL;

    // Si la pila esta vacia o el nuevo nodo tiene mayor prioridad
    if (pila->cabeza == NULL || dato.prioridad > pila->cabeza->Dato.prioridad) {
        nuevo_nodo->siguiente = pila->cabeza;
        pila->cabeza = nuevo_nodo;
    } else {
        // Buscar la posicion correcta para insertar el nodo
        Nodo *actual = pila->cabeza;
        while (actual->siguiente != NULL && actual->siguiente->Dato.prioridad >= dato.prioridad) {
            actual = actual->siguiente;
        }
        nuevo_nodo->siguiente = actual->siguiente;
        actual->siguiente = nuevo_nodo;
    }

    pila->longitud++;
    printf("Push: ID=%d, Valor=%d, Prioridad=%d\n", dato.i, dato.valor, dato.prioridad);
}

// Eliminar el elemento con la prioridad mas alta
int pop(PilaPrioridad *pila) {
    if (pila->cabeza == NULL) {
        printf("Error: La pila esta vacia\n");
        return -1;
    }

    Nodo *nodo_eliminado = pila->cabeza;
    int valor = nodo_eliminado->Dato.valor;

    pila->cabeza = pila->cabeza->siguiente;
    free(nodo_eliminado);
    pila->longitud--;

    printf("Pop: Valor=%d eliminado\n", valor);
    return valor;
}

// Obtener el elemento con la prioridad mas alta
Nodo* peek(PilaPrioridad *pila) {
    if (pila->cabeza == NULL) {
        printf("Error: La pila esta vacia\n");
        return NULL;
    }
    return pila->cabeza;
}

// Imprimir el contenido de la pila
void imprimir_pila(PilaPrioridad *pila) {
    Nodo *actual = pila->cabeza;
    if (actual == NULL) {
        printf("La pila esta vacia\n");
        return;
    }

    printf("Contenido de la pila de prioridad:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   | Prioridad |   Direccion   |\n");
    printf("--------------------------------------------------\n");

    while (actual != NULL) {
        printf("| %3d | %9d | %9d | %p |\n",
               actual->Dato.i,
               actual->Dato.valor,
               actual->Dato.prioridad,
               (void *)actual);
        actual = actual->siguiente;
    }
    printf("--------------------------------------------------\n");
}

// Generar un numero aleatorio
int int_aleatorio() {
    return rand() % 100;
}

// Menu de consola
void menu_consola(PilaPrioridad *pila) {
    int seleccion;
    Data dato;
    int valor;

    printf("MENU\n\n");
    printf("1. Push (Insertar en la pila de prioridad)\n");
    printf("2. Pop (Eliminar de la pila de prioridad)\n");
    printf("3. Peek (Consultar el elemento con mayor prioridad)\n");
    printf("4. Imprimir pila\n");
    printf("0. Fin programa\n\n");
    printf("> Seleccione una opcion: ");
    scanf("%d", &seleccion);

    switch (seleccion) {
        case 1:
            id++;
            dato.i = id;
            dato.valor = int_aleatorio();
            printf("> Ingrese la prioridad del nodo: ");
            scanf("%d", &dato.prioridad);
            push(dato, pila);
            break;

        case 2:
            pop(pila);
            break;

        case 3: {
            Nodo *nodo = peek(pila);
            if (nodo != NULL) {
                printf("Peek: ID=%d, Valor=%d, Prioridad=%d\n",
                       nodo->Dato.i, nodo->Dato.valor, nodo->Dato.prioridad);
            }
            break;
        }

        case 4:
            imprimir_pila(pila);
            break;

        case 0:
            printf("Fin programa ...\n");
            exit(0);

        default:
            printf("Error: Ingreso un valor incorrecto\n");
            break;
    }

    system("PAUSE");
}
