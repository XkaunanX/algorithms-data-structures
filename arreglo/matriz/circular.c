#define FILAS 3
#define COLUMNAS 3

int matriz[FILAS][COLUMNAS];  // 3 filas y 3 columnas

int inicio = 0, fin = 0;

void insertar_elemento(int valor) {
    matriz[inicio / COLUMNAS][inicio % COLUMNAS] = valor;
    inicio = (inicio + 1) % (FILAS * COLUMNAS);  // Circular
}

int obtener_elemento() {
    int valor = matriz[fin / COLUMNAS][fin % COLUMNAS];
    fin = (fin + 1) % (FILAS * COLUMNAS);  // Circular
    return valor;
}

int main()
{

    return 0;
}
