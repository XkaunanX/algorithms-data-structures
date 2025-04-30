#include <stdio.h>
#include <ctype.h>

void convertirAMinusculas(char *cadena) {
    while (*cadena) {
        *cadena = tolower(*cadena);
        cadena++;
    }
}

int main() {
    char texto[] = "Hola Mundo";
    convertirAMinusculas(texto);
    printf("Texto en minusculas: %s\n", texto);

    return 0;
}
