#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idIngrediente;  // ID del ingrediente
    int stockActual;    // Cantidad disponible en el stock
    float precioUnit;   // Precio por unidad del ingrediente
} Ingrediente;

typedef struct {
    int idIngrediente;  // ID del ingrediente vendido
    int cantidadVendida; // Cantidad utilizada en las ventas
} Venta;

int main() {
    FILE *stockFile, *ventasFile;
    Ingrediente ingrediente;
    Venta venta;

    // Abrir los archivos binarios
    stockFile = fopen("stock_ingredientes.dat", "rb+"); // Leer y escribir
    ventasFile = fopen("ventas.dat", "rb");

    if (stockFile == NULL || ventasFile == NULL) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    // Leer el archivo de ventas
    while (fread(&venta, sizeof(Venta), 1, ventasFile)) {
        // Calcular el desplazamiento directo basado en el ID del ingrediente
        long offset = (venta.idIngrediente - 1) * sizeof(Ingrediente);

        // Mover el puntero del archivo a la posicion correspondiente
        fseek(stockFile, offset, SEEK_SET);

        // Leer el registro del ingrediente
        if (fread(&ingrediente, sizeof(Ingrediente), 1, stockFile)) {
            // Actualizar el stock
            ingrediente.stockActual -= venta.cantidadVendida;

            // Volver a la posicion para escribir el registro actualizado
            fseek(stockFile, offset, SEEK_SET);
            fwrite(&ingrediente, sizeof(Ingrediente), 1, stockFile);
        } else {
            printf("Ingrediente con ID %d no encontrado.\n", venta.idIngrediente);
        }
    }

    // Cerrar los archivos
    fclose(stockFile);
    fclose(ventasFile);

    printf("Stock actualizado directamente en 'stock_ingredientes.dat'.\n");

    return 0;
}
