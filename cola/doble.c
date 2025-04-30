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
    struct NodoEnlazado *anterior;
} Nodo;

// Estructura para gestionar la cola doblemente enlazada
typedef struct ColaDoble {
    Nodo *frente;   // Primer nodo de la cola
    Nodo *final;    // Ultimo nodo de la cola
    int longitud;   // Numero de nodos en la cola
} ColaDoble;

// Firmas de funciones para la gestion de la cola doble
void inicializar_cola(ColaDoble *punteros_cola);
void insertar_adelante(Data dato, ColaDoble *punteros_cola);
void insertar_atras(Data dato, ColaDoble *punteros_cola);
void eliminar_adelante(ColaDoble *punteros_cola);
void eliminar_atras(ColaDoble *punteros_cola);
Nodo* consultar_frente(ColaDoble *punteros_cola);
Nodo* consultar_final(ColaDoble *punteros_cola);

// Firmas de funciones auxiliares
int int_aleatorio();
void imprimir_cola(ColaDoble *punteros_cola);
void imprimir_nodo(Nodo *nodo);

// Funcion para la gestion de la consola
void menu_consola(ColaDoble *punteros_cola)
{
    int interfaz = 1;
    int seleccion;
    int size;
    int i;
    while (interfaz == STATUS_CONTINUAR)
    {
        // Limpiar consola
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar nodo al frente de la cola\n");
        printf("2. Insertar nodo al final de la cola\n");
        printf("3. Eliminar nodo desde el frente de la cola\n");
        printf("4. Eliminar nodo desde el final de la cola\n");
        printf("5. Consultar el nodo en el frente de la cola\n");
        printf("6. Consultar el nodo en el final de la cola\n");
        printf("7. Consultar longitud de la cola\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        switch (seleccion)
        {
        case 1:
            id++;
            Data dato;
            dato.i = id;
            dato.valor = int_aleatorio();
            insertar_adelante(dato, punteros_cola);
            break;
        case 2:
            id++;
            Data dato2;
            dato2.i = id;
            dato2.valor = int_aleatorio();
            insertar_atras(dato2, punteros_cola);
            break;
        case 3:
            eliminar_adelante(punteros_cola);
            break;
        case 4:
            eliminar_atras(punteros_cola);
            break;
        case 5:
            Nodo *frente = consultar_frente(punteros_cola);
            imprimir_nodo(frente);
            break;
        case 6:
            Nodo *final = consultar_final(punteros_cola);
            imprimir_nodo(final);
            break;
        case 7:
            size = punteros_cola->longitud;
            printf("Tamaño de la cola: %d\n", size);
            break;
        case 0:
            printf("Fin programa ...");
            exit(0);
            break;
        default:
            printf("Error: ingreso un valor incorrecto\n");
            break;
        }
        imprimir_cola(punteros_cola);
        system("PAUSE");
    }
}

// Hilo principal
int main()
{
    ejecucion = 1;
    srand(time(NULL));
    // Instancio los punteros de la cola
    ColaDoble *punteros_cola = malloc(sizeof(ColaDoble));
    // Inicializo la cola doble
    inicializar_cola(punteros_cola);
    while (ejecucion == STATUS_CONTINUAR)
    {
        menu_consola(punteros_cola);
    }
    return 0;
}

void inicializar_cola(ColaDoble *punteros_cola)
{
    punteros_cola->frente = NULL;
    punteros_cola->final = NULL;
    punteros_cola->longitud = 0;
}

void insertar_adelante(Data dato, ColaDoble *punteros_cola)
{
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->siguiente = punteros_cola->frente;
    nuevo_nodo->anterior = NULL;

    if (punteros_cola->frente != NULL)
    {
        punteros_cola->frente->anterior = nuevo_nodo;
    }
    punteros_cola->frente = nuevo_nodo;
    
    if (punteros_cola->final == NULL)
    {
        punteros_cola->final = nuevo_nodo;
    }

    punteros_cola->longitud++;
}

void insertar_atras(Data dato, ColaDoble *punteros_cola)
{
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->Dato = dato;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->anterior = punteros_cola->final;

    if (punteros_cola->final != NULL)
    {
        punteros_cola->final->siguiente = nuevo_nodo;
    }
    punteros_cola->final = nuevo_nodo;
    
    if (punteros_cola->frente == NULL)
    {
        punteros_cola->frente = nuevo_nodo;
    }

    punteros_cola->longitud++;
}

void eliminar_adelante(ColaDoble *punteros_cola)
{
    if (punteros_cola->frente == NULL)
    {
        printf("La cola esta vacia\n");
        return;
    }

    Nodo *nodo_a_eliminar = punteros_cola->frente;
    punteros_cola->frente = nodo_a_eliminar->siguiente;
    
    if (punteros_cola->frente != NULL)
    {
        punteros_cola->frente->anterior = NULL;
    }

    free(nodo_a_eliminar);
    punteros_cola->longitud--;
}

void eliminar_atras(ColaDoble *punteros_cola)
{
    if (punteros_cola->final == NULL)
    {
        printf("La cola esta vacia\n");
        return;
    }

    Nodo *nodo_a_eliminar = punteros_cola->final;
    punteros_cola->final = nodo_a_eliminar->anterior;
    
    if (punteros_cola->final != NULL)
    {
        punteros_cola->final->siguiente = NULL;
    }

    free(nodo_a_eliminar);
    punteros_cola->longitud--;
}

Nodo *consultar_frente(ColaDoble *punteros_cola)
{
    return punteros_cola->frente;
}

Nodo *consultar_final(ColaDoble *punteros_cola)
{
    return punteros_cola->final;
}

int int_aleatorio()
{
    return rand() % 100;
}

void imprimir_cola(ColaDoble *punteros_cola)
{
    Nodo *nodo_actual = punteros_cola->frente;
    printf("Contenido de la cola doble:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   |     Direccion     |   Anterior   |   Siguiente   |\n");
    printf("--------------------------------------------------\n");
    
    while (nodo_actual != NULL)
    {
        printf("| %3d | %9d | %p | %p | %p |\n",
               nodo_actual->Dato.i,
               nodo_actual->Dato.valor,
               (void *)nodo_actual,
               (void *)nodo_actual->anterior,
               (void *)nodo_actual->siguiente);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("--------------------------------------------------\n");
}

void imprimir_nodo(Nodo *nodo)
{
    if (nodo == NULL)
    {
        printf("El nodo es NULL. No se puede imprimir.\n");
        return;
    }
    printf("Detalles del nodo:\n");
    printf("ID: %d\n", nodo->Dato.i);
    printf("Valor: %d\n", nodo->Dato.valor);
    printf("Direccion: %p\n", (void *)nodo);
    printf("Anterior: %p\n", (void *)nodo->anterior);
    printf("Siguiente: %p\n", (void *)nodo->siguiente);
}
