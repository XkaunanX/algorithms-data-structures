#include <stdio.h>
#include <string.h>

int main() {
    char texto[] = "Bienvenido a C";
    char *subcadena = strstr(texto, "C");
    
    if (subcadena != NULL) {
        printf("Subcadena encontrada en la posicion: %ld\n", subcadena - texto);
    } else {
        printf("Subcadena no encontrada\n");
    }

    return 0;
}
