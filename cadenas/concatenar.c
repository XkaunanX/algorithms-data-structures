#include <stdio.h>
#include <string.h>

int main() {
    char saludo[50] = "Hola ";
    char nombre[] = "Mundo";

    strcat(saludo, nombre);
    printf("Cadena concatenada: %s\n", saludo);

    return 0;
}
