#include <stdio.h>

int main() {
    // Crear un arreglo de punteros a cadenas (strings)
    char *frutas[] = {
        "Manzana", 
        "Banana", 
        "Cereza", 
        "Pera", 
        "Naranja"
    };

    // Calcular el numero de frutas (elementos del arreglo de punteros)
    int num_frutas = sizeof(frutas) / sizeof(frutas[0]);

    // Imprimir todas las frutas usando el arreglo de punteros
    printf("Lista de frutas:\n");
    for (int i = 0; i < num_frutas; i++) {
        printf("%d. %s\n", i + 1, frutas[i]);
    }

    return 0;
}
