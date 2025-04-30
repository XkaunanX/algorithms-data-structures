int* matriz[3];  // 3 filas
int columnas = 4;

for (int i = 0; i < 3; i++) {
    matriz[i] = (int*)malloc(columnas * sizeof(int));  // 4 columnas por fila
}
