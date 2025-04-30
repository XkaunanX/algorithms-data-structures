#include <stdio.h>
#include <stdlib.h>

#define STATUS_CONTINUAR 1
#define NUM_STACKS 3       // Numero de pilas
#define CAPACIDAD 30       // Capacidad total del array compartido

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
} Data;

// Estructura para gestionar las pilas multiples
typedef struct {
    int stackArray[CAPACIDAD];  // Array compartido para todas las pilas
    int tops[NUM_STACKS];       // Indices de los tops de cada pila
    int sizes[NUM_STACKS];      // Tamaños actuales de cada pila
} PilaMultiple;

// Firmas de funciones
void inicializar_pilas(PilaMultiple *pila);
void push(int stackNum, Data dato, PilaMultiple *pila);
int pop(int stackNum, PilaMultiple *pila);
int peek(int stackNum, PilaMultiple *pila);
void imprimir_pila(int stackNum, PilaMultiple *pila);
int int_aleatorio();
void menu_consola(PilaMultiple *pila);

// Funcion principal
int main() {
    ejecucion = 1;
    srand(time(NULL));
    PilaMultiple pila;
    inicializar_pilas(&pila);

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&pila);
    }

    return 0;
}

// Inicializar las pilas
void inicializar_pilas(PilaMultiple *pila) {
    for (int i = 0; i < NUM_STACKS; i++) {
        pila->tops[i] = i * (CAPACIDAD / NUM_STACKS) - 1;
        pila->sizes[i] = 0;
    }
}

// Verificar si una pila esta llena
int esta_llena(int stackNum, PilaMultiple *pila) {
    return pila->sizes[stackNum] >= (CAPACIDAD / NUM_STACKS);
}

// Verificar si una pila esta vacia
int esta_vacia(int stackNum, PilaMultiple *pila) {
    return pila->sizes[stackNum] == 0;
}

// Insertar un elemento en la pila seleccionada
void push(int stackNum, Data dato, PilaMultiple *pila) {
    if (esta_llena(stackNum, pila)) {
        printf("Error: La pila %d esta llena\n", stackNum);
        return;
    }

    pila->tops[stackNum]++;
    pila->stackArray[pila->tops[stackNum]] = dato.valor;
    pila->sizes[stackNum]++;
    printf("Push: %d en la pila %d\n", dato.valor, stackNum);
}

// Eliminar un elemento de la pila seleccionada
int pop(int stackNum, PilaMultiple *pila) {
    if (esta_vacia(stackNum, pila)) {
        printf("Error: La pila %d esta vacia\n", stackNum);
        return -1;
    }

    int valor = pila->stackArray[pila->tops[stackNum]];
    pila->tops[stackNum]--;
    pila->sizes[stackNum]--;
    printf("Pop: %d de la pila %d\n", valor, stackNum);
    return valor;
}

// Obtener el elemento superior de la pila seleccionada
int peek(int stackNum, PilaMultiple *pila) {
    if (esta_vacia(stackNum, pila)) {
        printf("Error: La pila %d esta vacia\n", stackNum);
        return -1;
    }

    return pila->stackArray[pila->tops[stackNum]];
}

// Imprimir el contenido de una pila
void imprimir_pila(int stackNum, PilaMultiple *pila) {
    if (esta_vacia(stackNum, pila)) {
        printf("La pila %d esta vacia\n", stackNum);
        return;
    }

    printf("Contenido de la pila %d: ", stackNum);
    for (int i = pila->tops[stackNum] - pila->sizes[stackNum] + 1; i <= pila->tops[stackNum]; i++) {
        printf("%d ", pila->stackArray[i]);
    }
    printf("\n");
}

// Generar un numero aleatorio
int int_aleatorio() {
    return rand() % 100;
}

// Menu de consola
void menu_consola(PilaMultiple *pila) {
    int seleccion, stackNum;
    Data dato;

    printf("MENU\n\n");
    printf("1. Push (Insertar en una pila)\n");
    printf("2. Pop (Eliminar de una pila)\n");
    printf("3. Peek (Consultar tope de una pila)\n");
    printf("4. Imprimir pila\n");
    printf("0. Fin programa\n\n");
    printf("> Seleccione una opcion: ");
    scanf("%d", &seleccion);

    switch (seleccion) {
        case 1:
            printf("> Ingrese el numero de la pila (0-%d): ", NUM_STACKS - 1);
            scanf("%d", &stackNum);
            if (stackNum < 0 || stackNum >= NUM_STACKS) {
                printf("Error: Numero de pila invalido\n");
                break;
            }
            id++;
            dato.i = id;
            dato.valor = int_aleatorio();
            push(stackNum, dato, pila);
            break;

        case 2:
            printf("> Ingrese el numero de la pila (0-%d): ", NUM_STACKS - 1);
            scanf("%d", &stackNum);
            pop(stackNum, pila);
            break;

        case 3:
            printf("> Ingrese el numero de la pila (0-%d): ", NUM_STACKS - 1);
            scanf("%d", &stackNum);
            int valor = peek(stackNum, pila);
            if (valor != -1) {
                printf("Peek: %d en la pila %d\n", valor, stackNum);
            }
            break;

        case 4:
            printf("> Ingrese el numero de la pila (0-%d): ", NUM_STACKS - 1);
            scanf("%d", &stackNum);
            imprimir_pila(stackNum, pila);
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
