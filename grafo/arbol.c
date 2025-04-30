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

// Estructura para el nodo del arbol binario
typedef struct NodoArbol {
    Data Dato;
    struct NodoArbol *izquierda;
    struct NodoArbol *derecha;
} NodoArbol;

// Estructura para gestionar el arbol binario
typedef struct ArbolBinario {
    NodoArbol *raiz;
} ArbolBinario;

// Firmas de funciones para la gestion del arbol binario
void inicializar_arbol(ArbolBinario *arbol);
void insertar_nodo(Data dato, ArbolBinario *arbol);
NodoArbol *eliminar_nodo(NodoArbol *nodo, int id);
void modificar_nodo(int id, ArbolBinario *arbol);
NodoArbol *buscar_nodo(int id, NodoArbol *nodo);
void imprimir_arbol(NodoArbol *nodo, int tipo_recorrido);

// Firmas de funciones auxiliares
int int_aleatorio();
NodoArbol *crear_nodo(Data dato);
NodoArbol *minimo_nodo(NodoArbol *nodo);

// Funcion para la gestion de la consola
void menu_consola(ArbolBinario *arbol) {
    int interfaz = 1;
    int seleccion;
    int id_nodo;
    Data dato;
    while (interfaz == STATUS_CONTINUAR) {
        system("CLS");
        printf("MENU ARBOL BINARIO\n\n");
        printf("1. Insertar nodo\n");
        printf("2. Eliminar nodo\n");
        printf("3. Modificar nodo\n");
        printf("4. Buscar nodo\n");
        printf("5. Imprimir arbol (Preorden)\n");
        printf("6. Imprimir arbol (Inorden)\n");
        printf("7. Imprimir arbol (Postorden)\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");

        switch (seleccion) {
        case 1:
            id++;
            dato.i = id;
            dato.valor = int_aleatorio();
            insertar_nodo(dato, arbol);
            break;
        case 2:
            printf("> Ingrese el id del nodo a eliminar: ");
            scanf("%d", &id_nodo);
            arbol->raiz = eliminar_nodo(arbol->raiz, id_nodo);
            break;
        case 3:
            printf("> Ingrese el id del nodo a modificar: ");
            scanf("%d", &id_nodo);
            modificar_nodo(id_nodo, arbol);
            break;
        case 4:
            printf("> Ingrese el id del nodo a buscar: ");
            scanf("%d", &id_nodo);
            NodoArbol *nodo = buscar_nodo(id_nodo, arbol->raiz);
            if (nodo != NULL) {
                printf("Nodo encontrado - ID: %d, Valor: %d\n", nodo->Dato.i, nodo->Dato.valor);
            } else {
                printf("Nodo no encontrado\n");
            }
            break;
        case 5:
            printf("Recorrido Preorden:\n");
            imprimir_arbol(arbol->raiz, 1);
            break;
        case 6:
            printf("Recorrido Inorden:\n");
            imprimir_arbol(arbol->raiz, 2);
            break;
        case 7:
            printf("Recorrido Postorden:\n");
            imprimir_arbol(arbol->raiz, 3);
            break;
        case 0:
            printf("Fin programa ...\n");
            exit(0);
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
    ArbolBinario arbol;
    inicializar_arbol(&arbol);
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&arbol);
    }
    return 0;
}

void inicializar_arbol(ArbolBinario *arbol) {
    arbol->raiz = NULL;
}

NodoArbol *crear_nodo(Data dato) {
    NodoArbol *nuevo_nodo = (NodoArbol *)malloc(sizeof(NodoArbol));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;
    return nuevo_nodo;
}

void insertar_nodo(Data dato, ArbolBinario *arbol) {
    NodoArbol *nuevo_nodo = crear_nodo(dato);
    NodoArbol *actual = arbol->raiz;
    NodoArbol *padre = NULL;

    if (arbol->raiz == NULL) {
        arbol->raiz = nuevo_nodo;
        return;
    }

    while (actual != NULL) {
        padre = actual;
        if (dato.valor < actual->Dato.valor) {
            actual = actual->izquierda;
        } else {
            actual = actual->derecha;
        }
    }

    if (dato.valor < padre->Dato.valor) {
        padre->izquierda = nuevo_nodo;
    } else {
        padre->derecha = nuevo_nodo;
    }
}

NodoArbol *eliminar_nodo(NodoArbol *nodo, int id) {
    if (nodo == NULL) return NULL;
    if (id < nodo->Dato.i) {
        nodo->izquierda = eliminar_nodo(nodo->izquierda, id);
    } else if (id > nodo->Dato.i) {
        nodo->derecha = eliminar_nodo(nodo->derecha, id);
    } else {
        if (nodo->izquierda == NULL) {
            NodoArbol *temp = nodo->derecha;
            free(nodo);
            return temp;
        } else if (nodo->derecha == NULL) {
            NodoArbol *temp = nodo->izquierda;
            free(nodo);
            return temp;
        }
        NodoArbol *temp = minimo_nodo(nodo->derecha);
        nodo->Dato = temp->Dato;
        nodo->derecha = eliminar_nodo(nodo->derecha, temp->Dato.i);
    }
    return nodo;
}

NodoArbol *minimo_nodo(NodoArbol *nodo) {
    while (nodo && nodo->izquierda != NULL) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

void modificar_nodo(int id, ArbolBinario *arbol) {
    NodoArbol *nodo = buscar_nodo(id, arbol->raiz);
    if (nodo != NULL) {
        nodo->Dato.valor = int_aleatorio();
    }
}

NodoArbol *buscar_nodo(int id, NodoArbol *nodo) {
    if (nodo == NULL || nodo->Dato.i == id) {
        return nodo;
    }
    if (id < nodo->Dato.i) {
        return buscar_nodo(id, nodo->izquierda);
    } else {
        return buscar_nodo(id, nodo->derecha);
    }
}

void imprimir_arbol(NodoArbol *nodo, int tipo_recorrido) {
    if (nodo == NULL) return;
    if (tipo_recorrido == 1) {
        printf("%d ", nodo->Dato.valor);
        imprimir_arbol(nodo->izquierda, 1);
        imprimir_arbol(nodo->derecha, 1);
    } else if (tipo_recorrido == 2) {
        imprimir_arbol(nodo->izquierda, 2);
        printf("%d ", nodo->Dato.valor);
        imprimir_arbol(nodo->derecha, 2);
    } else if (tipo_recorrido == 3) {
        imprimir_arbol(nodo->izquierda, 3);
        imprimir_arbol(nodo->derecha, 3);
        printf("%d ", nodo->Dato.valor);
    }
}

int int_aleatorio() {
    return rand() % 100;
}
