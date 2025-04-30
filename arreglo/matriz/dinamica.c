int **matriz;
int filas = 3, columnas = 4;

matriz = (int**)malloc(filas * sizeof(int*));  // Crear 3 filas
for (int i = 0; i < filas; i++) {
    matriz[i] = (int*)malloc(columnas * sizeof(int));  // Crear 4 columnas por fila
}
