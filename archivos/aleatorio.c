#include <stdio.h>
#include <string.h>

typedef struct {
    int idAuto;             // ID unico del auto
    char marca[30];         // Marca del auto
    char modelo[30];        // Modelo del auto
    int stockDisponible;    // Cantidad de autos disponibles
    float precio;           // Precio del auto
} Auto;

void buscarAutoPorID(FILE *autoFile, int idAuto);
void actualizarStockPorID(FILE *autoFile, int idAuto, int stockNuevo);

int main() {
    FILE *autoFile;
    int opcion, id, stock;

    // Abrir el archivo binario de autos
    autoFile = fopen("autos.dat", "rb+"); // Leer y escribir
    if (autoFile == NULL) {
        printf("Error al abrir el archivo de autos.\n");
        return 1;
    }

    do {
        printf("\n--- Concesionaria: Gestion de Autos ---\n");
        printf("1. Buscar auto por ID\n");
        printf("2. Actualizar stock por ID\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el ID del auto: ");
                scanf("%d", &id);
                buscarAutoPorID(autoFile, id);
                break;

            case 2:
                printf("Ingrese el ID del auto: ");
                scanf("%d", &id);
                printf("Ingrese la nueva cantidad de stock: ");
                scanf("%d", &stock);
                actualizarStockPorID(autoFile, id, stock);
                break;

            case 3:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 3);

    // Cerrar el archivo de autos
    fclose(autoFile);

    return 0;
}

// Funcion para buscar un auto por su ID
void buscarAutoPorID(FILE *autoFile, int idAuto) {
    Auto autoActual;
    int found = 0;

    // Buscar el auto por su ID utilizando acceso aleatorio
    fseek(autoFile, (idAuto - 1) * sizeof(Auto), SEEK_SET);  // Mover el puntero al registro correspondiente
    if (fread(&autoActual, sizeof(Auto), 1, autoFile)) {
        printf("Auto encontrado: \n");
        printf("ID: %d\n", autoActual.idAuto);
        printf("Marca: %s\n", autoActual.marca);
        printf("Modelo: %s\n", autoActual.modelo);
        printf("Stock Disponible: %d\n", autoActual.stockDisponible);
        printf("Precio: %.2f\n", autoActual.precio);
        found = 1;
    }

    if (!found) {
        printf("No se encontro el auto con ID: %d\n", idAuto);
    }
}

// Funcion para actualizar el stock de un auto por su ID
void actualizarStockPorID(FILE *autoFile, int idAuto, int stockNuevo) {
    Auto autoActual;

    // Buscar el auto por su ID utilizando acceso aleatorio
    fseek(autoFile, (idAuto - 1) * sizeof(Auto), SEEK_SET);  // Mover el puntero al registro correspondiente
    if (fread(&autoActual, sizeof(Auto), 1, autoFile)) {
        // Si el auto existe, actualizar su stock
        autoActual.stockDisponible = stockNuevo;

        // Mover el puntero nuevamente a la posicion del registro para actualizarlo
        fseek(autoFile, (idAuto - 1) * sizeof(Auto), SEEK_SET);
        fwrite(&autoActual, sizeof(Auto), 1, autoFile);  // Escribir el auto con el stock actualizado
        printf("Stock del auto con ID %d actualizado a %d.\n", idAuto, stockNuevo);
    } else {
        printf("No se encontro el auto con ID: %d\n", idAuto);
    }
}
