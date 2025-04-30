#include <stdio.h>
#include <stdlib.h>

#define MAX 5   // Tamaño maximo de las colas
#define NUM_COLAS 3  // Numero de colas en la cola de multiples colas
#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
} Data;

// Estructura para un nodo en la cola
typedef struct Nodo {
    Data dato;
    struct Nodo* siguiente;
} Nodo;

// Estructura para una cola
typedef struct Cola {
    Nodo* cabeza;
    Nodo* final;
    int longitud;
} Cola;

// Estructura para la cola de multiples colas
typedef struct ColaMultiple {
    Cola colas[NUM_COLAS]; // Arreglo de colas
} ColaMultiple;

// Firmas de funciones para la gestion de las colas
void inicializar_cola_multiple(ColaMultiple* cola_multiple);
void enQueue(int cola_num, Data dato, ColaMultiple* cola_multiple);
Data deQueue(int cola_num, ColaMultiple* cola_multiple);
void imprimir_cola_multiple(ColaMultiple* cola_multiple);
void imprimir_cola(int cola_num, ColaMultiple* cola_multiple);

// Funcion para la gestion de la consola
void menu_consola(ColaMultiple* cola_multiple) {
    int interfaz = 1;
    int seleccion;
    int cola_num;
    Data dato;
    
    while (interfaz == STATUS_CONTINUAR) {
        // Limpiar consola
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar elemento en una cola\n");
        printf("2. Eliminar elemento de una cola\n");
        printf("3. Consultar longitud de una cola\n");
        printf("4. Mostrar todas las colas\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        
        switch (seleccion) {
            case 1:
                printf("> Seleccione el numero de la cola (0-%d): ", NUM_COLAS - 1);
                scanf("%d", &cola_num);
                if (cola_num < 0 || cola_num >= NUM_COLAS) {
                    printf("Error: Numero de cola invalido\n");
                    break;
                }
                id++;
                dato.i = id;
                dato.valor = rand() % 100;  // Valor aleatorio
                enQueue(cola_num, dato, cola_multiple);
                break;
            case 2:
                printf("> Seleccione el numero de la cola (0-%d): ", NUM_COLAS - 1);
                scanf("%d", &cola_num);
                if (cola_num < 0 || cola_num >= NUM_COLAS) {
                    printf("Error: Numero de cola invalido\n");
                    break;
                }
                deQueue(cola_num, cola_multiple);
                break;
            case 3:
                printf("> Seleccione el numero de la cola (0-%d): ", NUM_COLAS - 1);
                scanf("%d", &cola_num);
                if (cola_num < 0 || cola_num >= NUM_COLAS) {
                    printf("Error: Numero de cola invalido\n");
                    break;
                }
                printf("Longitud de la cola %d: %d\n", cola_num, cola_multiple->colas[cola_num].longitud);
                break;
            case 4:
                imprimir_cola_multiple(cola_multiple);
                break;
            case 0:
                printf("Fin del programa ...\n");
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
    
    ColaMultiple cola_multiple;
    inicializar_cola_multiple(&cola_multiple);  // Inicializa la cola de multiples colas
    
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&cola_multiple);
    }
    return 0;
}

// Inicializa las colas dentro de la cola de multiples colas
void inicializar_cola_multiple(ColaMultiple* cola_multiple) {
    for (int i = 0; i < NUM_COLAS; i++) {
        cola_multiple->colas[i].cabeza = NULL;
        cola_multiple->colas[i].final = NULL;
        cola_multiple->colas[i].longitud = 0;
    }
}

// Inserta un elemento en una cola especifica
void enQueue(int cola_num, Data dato, ColaMultiple* cola_multiple) {
    if (cola_num < 0 || cola_num >= NUM_COLAS) {
        printf("Error: Numero de cola invalido\n");
        return;
    }
    
    Cola* cola = &cola_multiple->colas[cola_num];
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = NULL;
    
    if (cola->cabeza == NULL) {
        cola->cabeza = nuevo_nodo;
        cola->final = nuevo_nodo;
    } else {
        cola->final->siguiente = nuevo_nodo;
        cola->final = nuevo_nodo;
    }
    cola->longitud++;
}

// Elimina un elemento de una cola especifica
Data deQueue(int cola_num, ColaMultiple* cola_multiple) {
    if (cola_num < 0 || cola_num >= NUM_COLAS) {
        printf("Error: Numero de cola invalido\n");
        Data vacio = {0, 0};
        return vacio;
    }
    
    Cola* cola = &cola_multiple->colas[cola_num];
    if (cola->cabeza == NULL) {
        printf("Error: La cola esta vacia\n");
        Data vacio = {0, 0};
        return vacio;
    }
    
    Nodo* nodo_a_eliminar = cola->cabeza;
    Data dato = nodo_a_eliminar->dato;
    cola->cabeza = nodo_a_eliminar->siguiente;
    
    if (cola->cabeza == NULL) {
        cola->final = NULL;
    }
    
    free(nodo_a_eliminar);
    cola->longitud--;
    
    return dato;
}

// Imprime el contenido de todas las colas de la cola de multiples colas
void imprimir_cola_multiple(ColaMultiple* cola_multiple) {
    for (int i = 0; i < NUM_COLAS; i++) {
        printf("Contenido de la cola %d:\n", i);
        imprimir_cola(i, cola_multiple);
        printf("\n");
    }
}

// Imprime el contenido de una cola especifica
void imprimir_cola(int cola_num, ColaMultiple* cola_multiple) {
    if (cola_num < 0 || cola_num >= NUM_COLAS) {
        printf("Error: Numero de cola invalido\n");
        return;
    }
    
    Cola* cola = &cola_multiple->colas[cola_num];
    
    if (cola->longitud == 0) {
        printf("La cola esta vacia\n");
        return;
    }
    
    printf("-------------------------------------------------\n");
    printf("|  i  |   Valor   |     Direccion     | Siguiente |\n");
    printf("-------------------------------------------------\n");
    
    Nodo* nodo_actual = cola->cabeza;
    while (nodo_actual != NULL) {
        printf("| %3d | %9d | %p | %p |\n", 
               nodo_actual->dato.i, 
               nodo_actual->dato.valor, 
               (void*)nodo_actual, 
               (void*)nodo_actual->siguiente);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("-------------------------------------------------\n");
}
