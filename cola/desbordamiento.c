#include <stdio.h>
#include <stdlib.h>

#define MAX 5   // Tamaño maximo de la cola
#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
    int prioridad;  // Prioridad del elemento
} Data;

// Estructura para un nodo en la cola prioritaria
typedef struct Nodo {
    Data dato;
    struct Nodo* siguiente;
} Nodo;

// Estructura para la cola prioritaria
typedef struct ColaPrioritaria {
    Nodo* cabeza;
    int longitud;
} ColaPrioritaria;

// Firmas de funciones para la gestion de la cola prioritaria
void inicializar_cola_prioritaria(ColaPrioritaria* cola_prioritaria);
void enQueue(Data dato, ColaPrioritaria* cola_prioritaria);
Data deQueue(ColaPrioritaria* cola_prioritaria);
void imprimir_cola_prioritaria(ColaPrioritaria* cola_prioritaria);
int esta_llena(ColaPrioritaria* cola_prioritaria);
void reemplazar_elemento(Data dato, ColaPrioritaria* cola_prioritaria);

// Funcion para la gestion de la consola
void menu_consola(ColaPrioritaria* cola_prioritaria) {
    int interfaz = 1;
    int seleccion;
    Data dato;
    
    while (interfaz == STATUS_CONTINUAR) {
        // Limpiar consola
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar elemento en la cola prioritaria\n");
        printf("2. Eliminar elemento de la cola prioritaria\n");
        printf("3. Consultar longitud de la cola prioritaria\n");
        printf("4. Mostrar cola prioritaria\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        
        switch (seleccion) {
            case 1:
                id++;
                dato.i = id;
                dato.valor = rand() % 100;  // Valor aleatorio
                printf("> Ingrese la prioridad (1-10): ");
                scanf("%d", &dato.prioridad);
                
                if (esta_llena(cola_prioritaria)) {
                    printf("La cola esta llena. El elemento de menor prioridad sera reemplazado.\n");
                    reemplazar_elemento(dato, cola_prioritaria);
                } else {
                    enQueue(dato, cola_prioritaria);
                }
                break;
            case 2:
                deQueue(cola_prioritaria);
                break;
            case 3:
                printf("Longitud de la cola prioritaria: %d\n", cola_prioritaria->longitud);
                break;
            case 4:
                imprimir_cola_prioritaria(cola_prioritaria);
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
    
    ColaPrioritaria cola_prioritaria;
    inicializar_cola_prioritaria(&cola_prioritaria);  // Inicializa la cola prioritaria
    
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&cola_prioritaria);
    }
    return 0;
}

// Inicializa la cola prioritaria
void inicializar_cola_prioritaria(ColaPrioritaria* cola_prioritaria) {
    cola_prioritaria->cabeza = NULL;
    cola_prioritaria->longitud = 0;
}

// Inserta un elemento en la cola prioritaria (ordenado por prioridad)
void enQueue(Data dato, ColaPrioritaria* cola_prioritaria) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = NULL;
    
    if (cola_prioritaria->cabeza == NULL || cola_prioritaria->cabeza->dato.prioridad > dato.prioridad) {
        // Si la cola esta vacia o el nuevo nodo tiene mayor prioridad que el primero
        nuevo_nodo->siguiente = cola_prioritaria->cabeza;
        cola_prioritaria->cabeza = nuevo_nodo;
    } else {
        Nodo* nodo_actual = cola_prioritaria->cabeza;
        while (nodo_actual->siguiente != NULL && nodo_actual->siguiente->dato.prioridad <= dato.prioridad) {
            nodo_actual = nodo_actual->siguiente;
        }
        nuevo_nodo->siguiente = nodo_actual->siguiente;
        nodo_actual->siguiente = nuevo_nodo;
    }
    cola_prioritaria->longitud++;
}

// Elimina un elemento de la cola prioritaria (el de mayor prioridad)
Data deQueue(ColaPrioritaria* cola_prioritaria) {
    if (cola_prioritaria->cabeza == NULL) {
        printf("La cola esta vacia.\n");
        Data vacio = {0, 0, 0};
        return vacio;
    }
    
    Nodo* nodo_a_eliminar = cola_prioritaria->cabeza;
    Data dato = nodo_a_eliminar->dato;
    cola_prioritaria->cabeza = nodo_a_eliminar->siguiente;
    free(nodo_a_eliminar);
    cola_prioritaria->longitud--;
    
    printf("Elemento eliminado: ID=%d, Valor=%d, Prioridad=%d\n", dato.i, dato.valor, dato.prioridad);
    return dato;
}

// Imprime el contenido de la cola prioritaria
void imprimir_cola_prioritaria(ColaPrioritaria* cola_prioritaria) {
    if (cola_prioritaria->cabeza == NULL) {
        printf("La cola esta vacia\n");
        return;
    }
    
    Nodo* nodo_actual = cola_prioritaria->cabeza;
    printf("Contenido de la cola prioritaria:\n");
    printf("-------------------------------------------------\n");
    printf("|  ID  |   Valor   | Prioridad |   Direccion   |\n");
    printf("-------------------------------------------------\n");
    
    while (nodo_actual != NULL) {
        printf("| %3d | %9d |    %3d    | %p |\n", 
               nodo_actual->dato.i, 
               nodo_actual->dato.valor, 
               nodo_actual->dato.prioridad, 
               (void*)nodo_actual);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("-------------------------------------------------\n");
}

// Verifica si la cola esta llena
int esta_llena(ColaPrioritaria* cola_prioritaria) {
    return cola_prioritaria->longitud >= MAX;
}

// Reemplaza el elemento de menor prioridad si la cola esta llena
void reemplazar_elemento(Data dato, ColaPrioritaria* cola_prioritaria) {
    Nodo* nodo_actual = cola_prioritaria->cabeza;
    Nodo* nodo_anterior = NULL;
    
    // Buscar el nodo con menor prioridad
    while (nodo_actual != NULL) {
        if (nodo_actual->dato.prioridad < dato.prioridad) {
            // Reemplazar el nodo
            if (nodo_anterior == NULL) {
                cola_prioritaria->cabeza = nodo_actual->siguiente;
            } else {
                nodo_anterior->siguiente = nodo_actual->siguiente;
            }
            free(nodo_actual);
            enQueue(dato, cola_prioritaria);
            return;
        }
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }
}
