FILE* matriz[3][2];  // 3 filas y 2 columnas de archivos abiertos

int main() {
    matriz[0][0] = fopen("archivo1.txt", "r");
    matriz[0][1] = fopen("archivo2.txt", "r");
    matriz[1][0] = fopen("archivo3.txt", "w");
    matriz[1][1] = fopen("archivo4.txt", "w");
    // Aqui puedes manipular los archivos como desees
    return 0;
}
