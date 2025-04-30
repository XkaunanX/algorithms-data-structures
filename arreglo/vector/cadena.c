#include <stdio.h>
#include <string.h>

int main() {
    char cadena1[50] = "Hola";
    char cadena2[] = "mundo";
    
    // Concatenar cadenas
    strcat(cadena1, ", ");
    strcat(cadena1, cadena2);
    printf("Cadena concatenada: %s\n", cadena1);
    
    // Comparar cadenas
    int resultado = strcmp(cadena1, cadena2);
    printf("Resultado de comparacion: %d\n", resultado);
    
    // Copiar cadenas
    char copia[50];
    strcpy(copia, cadena1);
    printf("Cadena copiada: %s\n", copia);
    
    // Buscar subcadena
    char *subcadena = strstr(cadena1, "mundo");
    if (subcadena != NULL) {
        printf("Subcadena encontrada: %s\n", subcadena);
    }
    
    return 0;
}
