#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
} Data;

// Estructura para la pila circular
typedef struct {
    Data datos[MAX];
    int top;
    int inicio;
    int fin;
    int size;
} PilaCircular;

// Funciones de la pila circular
void inicializar_pila(PilaCircular *pila);
int es_vacia(PilaCircular *pila);
int es_llena(PilaCircular *pila);
void push(PilaCircular *pila, Data dato);
Data pop(PilaCircular *pila);
void imprimir_pila(PilaCircular *pila);
int int_aleatorio();

int main() {
    ejecucion = 1;
    srand(time(NULL));
    PilaCircular pila;
    inicializar_pila(&pila);

    while (ejecucion == STATUS_CONTINUAR) {
        int seleccion;
        printf("\nMENU\n");
        printf("1. Push (insertar)\n");
        printf("2. Pop (extraer)\n");
        printf("3. Imprimir pila\n");
        printf("0. Salir\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);

        switch (seleccion) {
            case 1: {
                id++;
                Data dato;
                dato.i = id;
                dato.valor = int_aleatorio();
                push(&pila, dato);
                break;
            }
            case 2: {
                Data dato = pop(&pila);
                if (dato.i != -1) {
                    printf("Elemento extraido: ID = %d, Valor = %d\n", dato.i, dato.valor);
                }
                break;
            }
            case 3:
                imprimir_pila(&pila);
                break;
            case 0:
                printf("Fin del programa.\n");
                exit(0);
            default:
                printf("Opcion incorrecta.\n");
                break;
        }
    }
    return 0;
}

void inicializar_pila(PilaCircular *pila) {
    pila->top = -1;
    pila->inicio = 0;
    pila->fin = 0;
    pila->size = 0;
}

int es_vacia(PilaCircular *pila) {
    return pila->size == 0;
}

int es_llena(PilaCircular *pila) {
    return pila->size == MAX;
}

void push(PilaCircular *pila, Data dato) {
    if (es_llena(pila)) {
        printf("Error: La pila esta llena.\n");
        return;
    }
    pila->datos[pila->fin] = dato;
    pila->fin = (pila->fin + 1) % MAX;
    pila->size++;
    printf("Elemento insertado: ID = %d, Valor = %d\n", dato.i, dato.valor);
}

Data pop(PilaCircular *pila) {
    Data dato = {-1, -1}; // Nodo vacio para indicar error
    if (es_vacia(pila)) {
        printf("Error: La pila esta vacia.\n");
        return dato;
    }
    dato = pila->datos[pila->inicio];
    pila->inicio = (pila->inicio + 1) % MAX;
    pila->size--;
    return dato;
}

void imprimir_pila(PilaCircular *pila) {
    if (es_vacia(pila)) {
        printf("La pila esta vacia.\n");
        return;
    }
    printf("Contenido de la pila circular:\n");
    int i = pila->inicio;
    int count = pila->size;
    while (count > 0) {
        printf("ID = %d, Valor = %d\n", pila->datos[i].i, pila->datos[i].valor);
        i = (i + 1) % MAX;
        count--;
    }
}

int int_aleatorio() {
    return rand() % 100;
}
