#include <stdio.h>
#include <ctype.h>

void convertirAMayusculas(char *cadena) {
    while (*cadena) {
        *cadena = toupper(*cadena);
        cadena++;
    }
}

int main() {
    char texto[] = "Hola Mundo";
    convertirAMayusculas(texto);
    printf("Texto en mayusculas: %s\n", texto);

    return 0;
}
