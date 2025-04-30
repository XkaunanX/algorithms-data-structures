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
} Data;

// Estructura para gestionar la pila
typedef struct NodoEnlazado {
    Data Dato;
    struct NodoEnlazado *siguiente;
} Nodo;

// Estructura para la pila reversible
typedef struct {
    Nodo *tope;
    int longitud;
} PilaReversible;

// Firmas de funciones
void inicializar_pila(PilaReversible *pila);
void push(Data dato, PilaReversible *pila);
int pop(PilaReversible *pila);
Nodo* peek(PilaReversible *pila);
void imprimir_pila(PilaReversible *pila);
void revertir_pila(PilaReversible *pila);
int int_aleatorio();
void menu_consola(PilaReversible *pila);

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));

    PilaReversible pila;
    inicializar_pila(&pila);

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&pila);
    }

    return 0;
}

// Inicializar la pila
void inicializar_pila(PilaReversible *pila) {
    pila->tope = NULL;
    pila->longitud = 0;
}

// Insertar un elemento en la pila
void push(Data dato, PilaReversible *pila) {
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->siguiente = pila->tope;
    pila->tope = nuevo_nodo;
    pila->longitud++;
    printf("Push: ID=%d, Valor=%d\n", dato.i, dato.valor);
}

// Eliminar el elemento en el tope de la pila
int pop(PilaReversible *pila) {
    if (pila->tope == NULL) {
        printf("Error: La pila esta vacia\n");
        return -1;
    }

    Nodo *nodo_eliminado = pila->tope;
    int valor = nodo_eliminado->Dato.valor;

    pila->tope = pila->tope->siguiente;
    free(nodo_eliminado);
    pila->longitud--;

    printf("Pop: Valor=%d eliminado\n", valor);
    return valor;
}

// Obtener el elemento en el tope de la pila
Nodo* peek(PilaReversible *pila) {
    if (pila->tope == NULL) {
        printf("Error: La pila esta vacia\n");
        return NULL;
    }
    return pila->tope;
}

// Imprimir el contenido de la pila
void imprimir_pila(PilaReversible *pila) {
    Nodo *actual = pila->tope;
    if (actual == NULL) {
        printf("La pila esta vacia\n");
        return;
    }

    printf("Contenido de la pila:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   |   Direccion   |\n");
    printf("--------------------------------------------------\n");

    while (actual != NULL) {
        printf("| %3d | %9d | %p |\n",
               actual->Dato.i,
               actual->Dato.valor,
               (void *)actual);
        actual = actual->siguiente;
    }
    printf("--------------------------------------------------\n");
}

// Revertir el contenido de la pila
void revertir_pila(PilaReversible *pila) {
    if (pila->tope == NULL || pila->tope->siguiente == NULL) {
        printf("La pila esta vacia o tiene un solo elemento. No se necesita revertir.\n");
        return;
    }

    Nodo *prev = NULL;
    Nodo *current = pila->tope;
    Nodo *next = NULL;

    while (current != NULL) {
        next = current->siguiente;
        current->siguiente = prev;
        prev = current;
        current = next;
    }

    pila->tope = prev;
    printf("La pila ha sido revertida.\n");
}

// Generar un numero aleatorio
int int_aleatorio() {
    return rand() % 100;
}

// Menu de consola
void menu_consola(PilaReversible *pila) {
    int seleccion;
    Data dato;
    int valor;

    printf("MENU\n\n");
    printf("1. Push (Insertar en la pila)\n");
    printf("2. Pop (Eliminar de la pila)\n");
    printf("3. Peek (Consultar el tope de la pila)\n");
    printf("4. Revertir pila\n");
    printf("5. Imprimir pila\n");
    printf("0. Fin programa\n\n");
    printf("> Seleccione una opcion: ");
    scanf("%d", &seleccion);

    switch (seleccion) {
        case 1:
            id++;
            dato.i = id;
            dato.valor = int_aleatorio();
            push(dato, pila);
            break;

        case 2:
            pop(pila);
            break;

        case 3: {
            Nodo *nodo = peek(pila);
            if (nodo != NULL) {
                printf("Peek: ID=%d, Valor=%d\n", nodo->Dato.i, nodo->Dato.valor);
            }
            break;
        }

        case 4:
            revertir_pila(pila);
            break;

        case 5:
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
