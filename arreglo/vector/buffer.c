#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    size_t bufferSize = 1024;  // Tamaño inicial del buffer
    char *buffer = malloc(bufferSize);  // Buffer dinamico

    if (buffer == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Abrir archivo para lectura
    file = fopen("archivo.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        free(buffer);
        return 1;
    }

    // Leer datos en el buffer y procesarlos
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, bufferSize, file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    // Liberar memoria y cerrar archivo
    free(buffer);
    fclose(file);
    return 0;
}
