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

// Estructura para el nodo de una lista doblemente enlazada
typedef struct NodoEnlazado {
    Data Dato;
    struct NodoEnlazado *siguiente;
    struct NodoEnlazado *anterior; // Puntero al nodo anterior
} Nodo;

// Estructura para gestionar la lista doblemente enlazada
typedef struct ListaEnlazada {
    Nodo *cabeza;      // Primer nodo de la lista
    Nodo *final;       // Ultimo nodo de la lista
    int longitud;      // Numero de nodos en la lista
} ListaEnlazada;

// Firmas de funciones para la gestion de la lista doblemente enlazada
void inicializar_lista(ListaEnlazada *punteros_lista);
void insertar_nodo(Data dato, ListaEnlazada *punteros_lista);
void eliminar_nodo(int id, ListaEnlazada *punteros_lista);
void modificar_nodo(int id, ListaEnlazada *punteros_lista);
Nodo* consultar_nodo(int id, ListaEnlazada *punteros_lista);

// Firmas de funciones auxiliares
int int_aleatorio();
void imprimir_lista(ListaEnlazada *punteros_lista);
void imprimir_nodo(Nodo *nodo);

// Firmas de funciones de ordenamiento
void burbuja(ListaEnlazada *punteros_lista);
void selection(ListaEnlazada *punteros_lista);
void insercion(ListaEnlazada *punteros_lista);
void shell_sort(ListaEnlazada *punteros_lista);
void quicksort(ListaEnlazada *punteros_lista, Nodo *inicio, Nodo *final);
void cocktail_shaker_sort(ListaEnlazada *punteros_lista);

// Funciones auxiliares de quicksort y merge_sort
Nodo* particionar(ListaEnlazada *punteros_lista, Nodo *inicio, Nodo *final);
Nodo* merge(Nodo *left, Nodo *right);
Nodo* merge_sort(Nodo *head);
Nodo* obtener_medio(Nodo *head);

// Funcion para la gestion de la consola
void menu_consola(ListaEnlazada *punteros_lista) {
    int interfaz = 1;
    int seleccion;
    int size;
    int i;
    while (interfaz == STATUS_CONTINUAR) {
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar nodo a la lista\n");
        printf("2. Eliminar nodo de la lista\n");
        printf("3. Modificar un nodo\n");
        printf("4. Consultar nodo\n");
        printf("5. Consultar longitud de lista\n");
        printf("6. Ordenar por Burbuja\n");
        printf("7. Ordenar por Seleccion\n");
        printf("8. Ordenar por Insercion\n");
        printf("9. Ordenar por Shell Sort\n");
        printf("10. Ordenar por Quicksort\n");
        printf("11. Ordenar por Cocktail Shaker\n");
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
                insertar_nodo(dato, punteros_lista);
                break;
            case 2:
                printf("> Ingrese un id: ");
                scanf("%d", &i);
                eliminar_nodo(i , punteros_lista);
                break;
            case 3:
                printf("> Ingrese un id: ");
                scanf("%d", &i);
                modificar_nodo(i , punteros_lista);
                break;
            case 4:
                printf("> Ingrese un id: ");
                scanf("%d", &i);
                Nodo* nodo = consultar_nodo(i , punteros_lista);
                imprimir_nodo(nodo);
                break;
            case 5:
                size = punteros_lista->longitud;
                printf("Tamaño de la lista enlazada: %d\n", size);
                break;
            case 6:
                burbuja(punteros_lista);
                break;
            case 7:
                selection(punteros_lista);
                break;
            case 8:
                insercion(punteros_lista);
                break;
            case 9:
                shell_sort(punteros_lista);
                break;
            case 10:
                quicksort(punteros_lista, punteros_lista->cabeza, punteros_lista->final);
                break;
            case 11:
                cocktail_shaker_sort(punteros_lista);
                break;
            case 0:
                printf("Fin programa ...");
                exit(0);
                break;
            default:
                printf("Error: ingreso un valor incorrecto\n");
                break;
        }
        imprimir_lista(punteros_lista);
        system("PAUSE");
    }
}

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));
    ListaEnlazada *punteros_lista = (ListaEnlazada *)malloc(sizeof(ListaEnlazada));
    inicializar_lista(punteros_lista);
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(punteros_lista);
    }
    return 0;
}

void inicializar_lista(ListaEnlazada *punteros_lista) {
    punteros_lista->cabeza = NULL;
    punteros_lista->final = NULL;
    punteros_lista->longitud = 0;
}

void insertar_nodo(Data dato, ListaEnlazada *punteros_lista) {
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->anterior = NULL;

    if (punteros_lista->cabeza == NULL) {
        punteros_lista->cabeza = nuevo_nodo;
        punteros_lista->final = nuevo_nodo;
    } else {
        punteros_lista->final->siguiente = nuevo_nodo;
        nuevo_nodo->anterior = punteros_lista->final;
        punteros_lista->final = nuevo_nodo;
    }
    punteros_lista->longitud++;
}

void eliminar_nodo(int id, ListaEnlazada *punteros_lista) {
    Nodo *nodo_anterior = NULL;
    Nodo *nodo_actual = punteros_lista->cabeza;
    if (punteros_lista->cabeza == NULL) {
        printf("La lista esta vacia\n");
        return;
    }

    while (nodo_actual != NULL) {
        if (nodo_actual->Dato.i == id) {
            if (nodo_anterior == NULL) {
                punteros_lista->cabeza = nodo_actual->siguiente;
                if (punteros_lista->cabeza != NULL) {
                    punteros_lista->cabeza->anterior = NULL;
                }
            } else {
                nodo_anterior->siguiente = nodo_actual->siguiente;
                if (nodo_actual->siguiente != NULL) {
                    nodo_actual->siguiente->anterior = nodo_anterior;
                }
            }
            if (nodo_actual == punteros_lista->final) {
                punteros_lista->final = nodo_anterior;
            }
            free(nodo_actual);
            punteros_lista->longitud--;
            return;
        }
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }
}

void modificar_nodo(int id, ListaEnlazada *punteros_lista) {
    Nodo *nodo_actual;
    if (punteros_lista->cabeza == NULL) {
        printf("Vacio\n");
    } else {
        nodo_actual = punteros_lista->cabeza;
        while (nodo_actual != NULL) {
            if (nodo_actual->Dato.i == id) {
                nodo_actual->Dato.valor = int_aleatorio();
                return;
            }
            nodo_actual = nodo_actual->siguiente;
        }
    }
}

Nodo *consultar_nodo(int id, ListaEnlazada *punteros_lista) {
    Nodo *nodo_actual;
    if (punteros_lista->cabeza == NULL) {
        return NULL;
    } else {
        nodo_actual = punteros_lista->cabeza;
        while (nodo_actual != NULL) {
            if (nodo_actual->Dato.i == id) {
                return nodo_actual;
            }
            nodo_actual = nodo_actual->siguiente;
        }
    }
    return NULL;
}

int int_aleatorio() {
    return rand() % 100;
}

void imprimir_lista(ListaEnlazada *punteros_lista) {
    Nodo *nodo_actual = punteros_lista->cabeza;
    printf("Contenido de la lista doblemente enlazada:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   | Direccion | Siguiente | Anterior |\n");
    printf("--------------------------------------------------\n");
    
    while (nodo_actual != NULL) {
        printf("| %3d | %9d | %p | %p | %p |\n", 
               nodo_actual->Dato.i, nodo_actual->Dato.valor, 
               nodo_actual, nodo_actual->siguiente, nodo_actual->anterior);
        nodo_actual = nodo_actual->siguiente;
    }
}

void imprimir_nodo(Nodo *nodo) {
    if (nodo == NULL) {
        printf("Nodo no encontrado\n");
    } else {
        printf("Nodo ID: %d\n", nodo->Dato.i);
        printf("Valor: %d\n", nodo->Dato.valor);
    }
}

// Implementacion de los algoritmos de ordenacion

void intercambiar_nodos(ListaEnlazada *punteros_lista, Nodo *nodo1, Nodo *nodo2) {
    Data temp = nodo1->Dato;
    nodo1->Dato = nodo2->Dato;
    nodo2->Dato = temp;
}

void burbuja(ListaEnlazada *punteros_lista) {
    if (punteros_lista->longitud < 2) return;
    
    int intercambiado;
    Nodo *nodo_actual, *nodo_siguiente;
    
    do {
        intercambiado = 0;
        nodo_actual = punteros_lista->cabeza;
        while (nodo_actual != NULL && nodo_actual->siguiente != NULL) {
            nodo_siguiente = nodo_actual->siguiente;
            if (nodo_actual->Dato.valor > nodo_siguiente->Dato.valor) {
                intercambiar_nodos(punteros_lista, nodo_actual, nodo_siguiente);
                intercambiado = 1;
            }
            nodo_actual = nodo_actual->siguiente;
        }
    } while (intercambiado);
}

void selection(ListaEnlazada *punteros_lista) {
    if (punteros_lista->longitud < 2) return;

    Nodo *nodo_actual, *nodo_minimo, *nodo_iterador;
    nodo_actual = punteros_lista->cabeza;

    while (nodo_actual != NULL) {
        nodo_minimo = nodo_actual;
        nodo_iterador = nodo_actual->siguiente;

        while (nodo_iterador != NULL) {
            if (nodo_iterador->Dato.valor < nodo_minimo->Dato.valor) {
                nodo_minimo = nodo_iterador;
            }
            nodo_iterador = nodo_iterador->siguiente;
        }

        if (nodo_minimo != nodo_actual) {
            intercambiar_nodos(punteros_lista, nodo_actual, nodo_minimo);
        }

        nodo_actual = nodo_actual->siguiente;
    }
}

void insercion(ListaEnlazada *punteros_lista) {
    if (punteros_lista->longitud < 2) return;

    Nodo *nodo_actual, *nodo_iterador;
    nodo_actual = punteros_lista->cabeza->siguiente;

    while (nodo_actual != NULL) {
        nodo_iterador = nodo_actual->anterior;
        while (nodo_iterador != NULL && nodo_actual->Dato.valor < nodo_iterador->Dato.valor) {
            intercambiar_nodos(punteros_lista, nodo_iterador, nodo_actual);
            nodo_actual = nodo_iterador;
            nodo_iterador = nodo_actual->anterior;
        }
        nodo_actual = nodo_actual->siguiente;
    }
}

void shell_sort(ListaEnlazada *punteros_lista) {
    if (punteros_lista->longitud < 2) return;

    int gap, i, j;
    Nodo *nodo_actual, *nodo_siguiente;

    for (gap = punteros_lista->longitud / 2; gap > 0; gap /= 2) {
        for (i = gap; i < punteros_lista->longitud; i++) {
            nodo_actual = punteros_lista->cabeza;
            for (j = 0; j < i; j++) {
                nodo_actual = nodo_actual->siguiente;
            }
            nodo_siguiente = nodo_actual;
            for (j = i; j >= gap && nodo_actual != NULL && nodo_siguiente != NULL; j -= gap) {
                if (nodo_actual->Dato.valor > nodo_siguiente->Dato.valor) {
                    intercambiar_nodos(punteros_lista, nodo_actual, nodo_siguiente);
                }
                nodo_actual = nodo_actual->siguiente;
                nodo_siguiente = nodo_siguiente->siguiente;
            }
        }
    }
}


void quicksort(ListaEnlazada *punteros_lista, Nodo *inicio, Nodo *final) {
    if (inicio == NULL || final == NULL || inicio == final || inicio == final->siguiente) {
        return;
    }

    Nodo *pivot = particionar(punteros_lista, inicio, final);
    quicksort(punteros_lista, inicio, pivot->anterior);
    quicksort(punteros_lista, pivot->siguiente, final);
}

Nodo* particionar(ListaEnlazada *punteros_lista, Nodo *inicio, Nodo *final) {
    int pivot_value = final->Dato.valor;
    Nodo *i = inicio->anterior;
    Nodo *j = inicio;

    while (j != final) {
        if (j->Dato.valor <= pivot_value) {
            i = (i == NULL) ? inicio : i->siguiente;
            intercambiar_nodos(punteros_lista, i, j);
        }
        j = j->siguiente;
    }
    i = (i == NULL) ? inicio : i->siguiente;
    intercambiar_nodos(punteros_lista, i, final);
    return i;
}


Nodo* merge(Nodo *left, Nodo *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->Dato.valor <= right->Dato.valor) {
        left->siguiente = merge(left->siguiente, right);
        left->siguiente->anterior = left;
        left->anterior = NULL;
        return left;
    } else {
        right->siguiente = merge(left, right->siguiente);
        right->siguiente->anterior = right;
        right->anterior = NULL;
        return right;
    }
}

Nodo* merge_sort(Nodo *head) {
    if (head == NULL || head->siguiente == NULL) return head;
    
    Nodo *mid = obtener_medio(head);
    Nodo *left = merge_sort(head);
    Nodo *right = merge_sort(mid);
    
    return merge(left, right);
}

Nodo* obtener_medio(Nodo *head) {
    Nodo *slow = head;
    Nodo *fast = head->siguiente;

    while (fast != NULL) {
        fast = fast->siguiente;
        if (fast != NULL) {
            slow = slow->siguiente;
            fast = fast->siguiente;
        }
    }

    Nodo *mid = slow->siguiente;
    slow->siguiente = NULL;
    return mid;
}


void cocktail_shaker_sort(ListaEnlazada *punteros_lista) {
    if (punteros_lista->longitud < 2) return;

    int intercambiado;
    Nodo *nodo_actual, *nodo_siguiente;

    do {
        intercambiado = 0;
        nodo_actual = punteros_lista->cabeza;
        while (nodo_actual != NULL && nodo_actual->siguiente != NULL) {
            nodo_siguiente = nodo_actual->siguiente;
            if (nodo_actual->Dato.valor > nodo_siguiente->Dato.valor) {
                intercambiar_nodos(punteros_lista, nodo_actual, nodo_siguiente);
                intercambiado = 1;
            }
            nodo_actual = nodo_actual->siguiente;
        }
        
        if (!intercambiado) break;

        intercambiado = 0;
        nodo_siguiente = punteros_lista->final;
        while (nodo_siguiente != NULL && nodo_siguiente->anterior != NULL) {
            nodo_actual = nodo_siguiente->anterior;
            if (nodo_siguiente->Dato.valor < nodo_actual->Dato.valor) {
                intercambiar_nodos(punteros_lista, nodo_actual, nodo_siguiente);
                intercambiado = 1;
            }
            nodo_siguiente = nodo_siguiente->anterior;
        }
    } while (intercambiado);
}
