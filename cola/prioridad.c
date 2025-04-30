#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Tamaño maximo de la cola
#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
    int prioridad; // Prioridad del elemento
} Data;

// Estructura para la cola de prioridad
typedef struct ColaPrioridad {
    Data elementos[MAX]; // Array para almacenar los elementos
    int longitud;         // Numero de elementos en la cola
} ColaPrioridad;

// Firmas de funciones para la gestion de la cola de prioridad
void inicializar_cola(ColaPrioridad *cola);
void enQueue(Data dato, ColaPrioridad *cola);
Data deQueue(ColaPrioridad *cola);
void imprimir_cola(ColaPrioridad *cola);
void ordenar_cola(ColaPrioridad *cola);

// Funcion para la gestion de la consola
void menu_consola(ColaPrioridad *cola) {
    int interfaz = 1;
    int seleccion;
    int size;
    Data dato;
    
    while (interfaz == STATUS_CONTINUAR) {
        // Limpiar consola
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar elemento a la cola de prioridad\n");
        printf("2. Eliminar elemento de la cola de prioridad\n");
        printf("3. Consultar longitud de cola\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        
        switch (seleccion) {
            case 1:
                id++;
                dato.i = id;
                dato.valor = rand() % 100;
                dato.prioridad = rand() % 10;  // Prioridad aleatoria (0-9)
                enQueue(dato, cola);
                break;
            case 2:
                deQueue(cola);
                break;
            case 3:
                size = cola->longitud;
                printf("Tamaño de la cola de prioridad: %d\n", size);
                break;
            case 0:
                printf("Fin del programa ...\n");
                exit(0);
                break;
            default:
                printf("Error: ingreso un valor incorrecto\n");
                break;
        }
        imprimir_cola(cola);
        system("PAUSE");
    }
}

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));
    
    ColaPrioridad cola;
    inicializar_cola(&cola);  // Inicializa la cola de prioridad
    
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&cola);
    }
    return 0;
}

// Inicializa la cola de prioridad
void inicializar_cola(ColaPrioridad *cola) {
    cola->longitud = 0;
}

// Inserta un elemento en la cola de prioridad
void enQueue(Data dato, ColaPrioridad *cola) {
    if (cola->longitud == MAX) {
        printf("Error: La cola de prioridad esta llena\n");
    } else {
        cola->elementos[cola->longitud] = dato;
        cola->longitud++;
        ordenar_cola(cola);  // Ordena la cola despues de insertar
    }
}

// Elimina un elemento de la cola de prioridad (el de mayor prioridad)
Data deQueue(ColaPrioridad *cola) {
    if (cola->longitud == 0) {
        printf("Error: La cola de prioridad esta vacia\n");
        Data vacio = {0, 0, 0}; // Valor vacio
        return vacio;
    } else {
        Data dato = cola->elementos[0];
        
        // Desplaza todos los elementos hacia la izquierda
        for (int i = 0; i < cola->longitud - 1; i++) {
            cola->elementos[i] = cola->elementos[i + 1];
        }
        cola->longitud--;
        return dato;
    }
}

// Ordena la cola de prioridad segun la prioridad (de mayor a menor)
void ordenar_cola(ColaPrioridad *cola) {
    for (int i = 0; i < cola->longitud - 1; i++) {
        for (int j = i + 1; j < cola->longitud; j++) {
            if (cola->elementos[i].prioridad < cola->elementos[j].prioridad) {
                // Intercambia los elementos
                Data temp = cola->elementos[i];
                cola->elementos[i] = cola->elementos[j];
                cola->elementos[j] = temp;
            }
        }
    }
}

// Imprime los elementos de la cola de prioridad
void imprimir_cola(ColaPrioridad *cola) {
    if (cola->longitud == 0) {
        printf("La cola de prioridad esta vacia\n");
        return;
    }
    printf("Contenido de la cola de prioridad:\n");
    printf("------------------------------------------------------------\n");
    printf("|  i  |   Valor   | Prioridad |     Direccion     |\n");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < cola->longitud; i++) {
        printf("| %3d | %9d | %9d | %p |\n", 
               cola->elementos[i].i, 
               cola->elementos[i].valor, 
               cola->elementos[i].prioridad, 
               (void*)&cola->elementos[i]);
    }
    printf("------------------------------------------------------------\n");
}
