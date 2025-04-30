#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int size, i;
    
    // Solicitar el tamaño del arreglo
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &size);

    // Asignacion dinamica de memoria
    arr = (int *)malloc(size * sizeof(int));

    // Verificar si la memoria fue asignada correctamente
    if (arr == NULL) {
        printf("Error en la asignacion de memoria\n");
        return 1;
    }

    // Inicializar el arreglo
    for (i = 0; i < size; i++) {
        arr[i] = i * 10;
    }

    // Mostrar los elementos del arreglo
    printf("Elementos del arreglo:\n");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Liberar la memoria cuando ya no se necesite
    free(arr);

    return 0;
}
