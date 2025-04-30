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

// Estructura para el nodo de la cola
typedef struct NodoEnlazado {
    Data Dato;
    struct NodoEnlazado *siguiente;
} Nodo;

// Estructura para gestionar la cola
typedef struct Cola {
    Nodo *frente;  // Primer nodo (frente) de la cola
    Nodo *final;   // Ultimo nodo (final) de la cola
    int longitud;  // Numero de elementos en la cola
} Cola;

// Firmas de funciones para la gestion de la cola
void inicializar_cola(Cola *punteros_cola);
void encolar(Data dato, Cola *punteros_cola);
void desencolar(Cola *punteros_cola);
Nodo *consultar_frente(Cola *punteros_cola);

// Firmas de funciones auxiliares
int int_aleatorio();
void imprimir_cola(Cola *punteros_cola);
void imprimir_nodo(Nodo *nodo);

// Funcion para la gestion de la consola
void menu_consola(Cola *punteros_cola) {
    int interfaz = 1;
    int seleccion;

    while (interfaz == STATUS_CONTINUAR) {
        system("CLS");
        printf("MENU COLA SIMPLE\n\n");
        printf("1. Encolar (Agregar a la cola)\n");
        printf("2. Desencolar (Eliminar del frente de la cola)\n");
        printf("3. Consultar frente de la cola\n");
        printf("4. Consultar longitud de la cola\n");
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
                encolar(dato, punteros_cola);
                break;
            case 2:
                desencolar(punteros_cola);
                break;
            case 3: {
                Nodo *nodo = consultar_frente(punteros_cola);
                imprimir_nodo(nodo);
                break;
            }
            case 4:
                printf("Longitud de la cola: %d\n", punteros_cola->longitud);
                break;
            case 0:
                printf("Fin programa...\n");
                exit(0);
            default:
                printf("Error: ingreso un valor incorrecto\n");
                break;
        }
        imprimir_cola(punteros_cola);
        system("PAUSE");
    }
}

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));

    Cola *punteros_cola;
    punteros_cola = malloc(sizeof(Cola));

    inicializar_cola(punteros_cola);

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(punteros_cola);
    }

    return 0;
}

// Inicializar la cola
void inicializar_cola(Cola *punteros_cola) {
    punteros_cola->frente = NULL;
    punteros_cola->final = NULL;
    punteros_cola->longitud = 0;
}

// Encolar (Agregar un nodo al final de la cola)
void encolar(Data dato, Cola *punteros_cola) {
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->siguiente = NULL;

    if (punteros_cola->final == NULL) {
        punteros_cola->frente = nuevo_nodo;
        punteros_cola->final = nuevo_nodo;
    } else {
        punteros_cola->final->siguiente = nuevo_nodo;
        punteros_cola->final = nuevo_nodo;
    }

    punteros_cola->longitud++;
}

// Desencolar (Eliminar el nodo del frente de la cola)
void desencolar(Cola *punteros_cola) {
    if (punteros_cola->frente == NULL) {
        printf("La cola esta vacia\n");
        return;
    }

    Nodo *nodo_a_eliminar = punteros_cola->frente;
    punteros_cola->frente = punteros_cola->frente->siguiente;

    if (punteros_cola->frente == NULL) {
        punteros_cola->final = NULL;
    }

    free(nodo_a_eliminar);
    punteros_cola->longitud--;
}

// Consultar el frente de la cola
Nodo *consultar_frente(Cola *punteros_cola) {
    return punteros_cola->frente;
}

// Generar un numero aleatorio
int int_aleatorio() {
    return rand() % 100;
}

// Imprimir la cola
void imprimir_cola(Cola *punteros_cola) {
    Nodo *nodo_actual = punteros_cola->frente;

    printf("Contenido de la cola:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   |     Direccion     |   Siguiente   |\n");
    printf("--------------------------------------------------\n");

    while (nodo_actual != NULL) {
        printf("| %3d | %9d | %p | %p |\n",
               nodo_actual->Dato.i,
               nodo_actual->Dato.valor,
               (void *)nodo_actual,
               (void *)nodo_actual->siguiente);
        nodo_actual = nodo_actual->siguiente;
    }

    printf("--------------------------------------------------\n");
}

// Imprimir un nodo
void imprimir_nodo(Nodo *nodo) {
    if (nodo == NULL) {
        printf("El nodo es NULL. No se puede imprimir.\n");
        return;
    }

    printf("Detalles del nodo:\n");
    printf("ID: %d\n", nodo->Dato.i);
    printf("Valor: %d\n", nodo->Dato.valor);
    printf("Direccion: %p\n", (void *)nodo);
    printf("Siguiente: %p\n", (void *)nodo->siguiente);
}
