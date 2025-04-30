#include <stdio.h>
#include <string.h>

int main() {
    char cadena1[] = "Manzana";
    char cadena2[] = "Manzana";
    char cadena3[] = "Pera";

    int resultado1 = strcmp(cadena1, cadena2);
    int resultado2 = strcmp(cadena1, cadena3);

    printf("Comparacion 1: %d\n", resultado1); // 0, iguales
    printf("Comparacion 2: %d\n", resultado2); // Valor distinto de 0, diferentes

    return 0;
}
