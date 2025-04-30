#include <stdio.h>
#include <string.h>

typedef struct {
    int idZapatilla;       // ID unico de la zapatilla
    char marca[30];        // Marca de la zapatilla
    int tamaño;            // Talla de la zapatilla
    int stockDisponible;   // Cantidad disponible en stock
    float precio;          // Precio de la zapatilla
} Zapatilla;

// Funciones
void buscarZapatillaPorID(FILE *dataFile, int idZapatilla);
void imprimirZapatilla(Zapatilla *zapatilla);

int main() {
    FILE *dataFile;
    int opcion, id;

    // Abrir el archivo de datos de zapatillas
    dataFile = fopen("zapatillas.dat", "rb"); // Solo lectura

    if (dataFile == NULL) {
        printf("Error al abrir el archivo de datos.\n");
        return 1;
    }

    do {
        printf("\n--- Concesionaria de Zapatillas ---\n");
        printf("1. Buscar zapatilla por ID (Acceso Secuencial)\n");
        printf("2. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el ID de la zapatilla a buscar: ");
                scanf("%d", &id);
                buscarZapatillaPorID(dataFile, id);
                break;

            case 2:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 2);

    // Cerrar el archivo
    fclose(dataFile);

    return 0;
}

// Funcion para buscar una zapatilla por su ID de manera secuencial
void buscarZapatillaPorID(FILE *dataFile, int idZapatilla) {
    Zapatilla zapatilla;
    int encontrado = 0;

    // Leer el archivo de datos de manera secuencial
    fseek(dataFile, 0, SEEK_SET); // Asegurarse de comenzar desde el inicio del archivo
    while (fread(&zapatilla, sizeof(Zapatilla), 1, dataFile)) {
        if (zapatilla.idZapatilla == idZapatilla) {
            imprimirZapatilla(&zapatilla);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Zapatilla con ID %d no encontrada.\n", idZapatilla);
    }
}

// Funcion para imprimir los detalles de la zapatilla
void imprimirZapatilla(Zapatilla *zapatilla) {
    printf("\n--- Zapatilla Encontrada ---\n");
    printf("ID: %d\n", zapatilla->idZapatilla);
    printf("Marca: %s\n", zapatilla->marca);
    printf("Tamaño: %d\n", zapatilla->tamaño);
    printf("Stock Disponible: %d\n", zapatilla->stockDisponible);
    printf("Precio: %.2f\n", zapatilla->precio);
}
