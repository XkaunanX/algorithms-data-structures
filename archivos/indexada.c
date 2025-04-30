#include <stdio.h>
#include <string.h>

typedef struct {
    int idZapatilla;       // ID unico de la zapatilla
    char marca[30];        // Marca de la zapatilla
    int tamaño;            // Talla de la zapatilla
    int stockDisponible;   // Cantidad disponible en stock
    float precio;          // Precio de la zapatilla
} Zapatilla;

typedef struct {
    int idZapatilla;       // ID de la zapatilla
    long offset;           // Desplazamiento del registro en el archivo de datos
} Indice;

// Funciones
void crearIndice(FILE *dataFile, FILE *indexFile);
void buscarZapatillaPorID(FILE *dataFile, FILE *indexFile, int idZapatilla);
void imprimirZapatilla(Zapatilla *zapatilla);

int main() {
    FILE *dataFile, *indexFile;
    int opcion, id;

    // Abrir el archivo de datos de zapatillas y el archivo de indice
    dataFile = fopen("zapatillas.dat", "rb+"); // Leer y escribir
    indexFile = fopen("indice.dat", "rb+"); // Leer y escribir

    if (dataFile == NULL || indexFile == NULL) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    do {
        printf("\n--- Concesionaria de Zapatillas ---\n");
        printf("1. Crear indice de zapatillas\n");
        printf("2. Buscar zapatilla por ID\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearIndice(dataFile, indexFile);
                printf("Indice creado con exito.\n");
                break;

            case 2:
                printf("Ingrese el ID de la zapatilla a buscar: ");
                scanf("%d", &id);
                buscarZapatillaPorID(dataFile, indexFile, id);
                break;

            case 3:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 3);

    // Cerrar los archivos
    fclose(dataFile);
    fclose(indexFile);

    return 0;
}

// Funcion para crear el indice basado en el archivo de datos
void crearIndice(FILE *dataFile, FILE *indexFile) {
    Zapatilla zapatilla;
    Indice indice;
    long offset;

    // Moverse al inicio del archivo de indice
    fseek(indexFile, 0, SEEK_SET);
    
    // Leer el archivo de datos y generar el indice
    fseek(dataFile, 0, SEEK_SET);
    while (fread(&zapatilla, sizeof(Zapatilla), 1, dataFile)) {
        offset = ftell(dataFile) - sizeof(Zapatilla);  // Obtener el desplazamiento del registro

        indice.idZapatilla = zapatilla.idZapatilla;
        indice.offset = offset;

        // Escribir el indice en el archivo de indice
        fwrite(&indice, sizeof(Indice), 1, indexFile);
    }
}

// Funcion para buscar una zapatilla por su ID utilizando el indice
void buscarZapatillaPorID(FILE *dataFile, FILE *indexFile, int idZapatilla) {
    Indice indice;
    Zapatilla zapatilla;
    int encontrado = 0;

    // Buscar en el archivo de indice
    fseek(indexFile, 0, SEEK_SET);
    while (fread(&indice, sizeof(Indice), 1, indexFile)) {
        if (indice.idZapatilla == idZapatilla) {
            // Encontramos el indice, ahora vamos a leer el registro correspondiente en el archivo de datos
            fseek(dataFile, indice.offset, SEEK_SET);
            fread(&zapatilla, sizeof(Zapatilla), 1, dataFile);
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
