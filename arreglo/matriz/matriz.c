#include <stdio.h>
#include <stdlib.h>

#define STATUS_CONTINUAR 1
#define FILAS 100
#define COLUMNAS 100

int ejecucion;
int matriz[FILAS][COLUMNAS];

// Funciones para trabajar con la matriz
void inicializar_matriz();
void mostrar_matriz();

// Metodos de ordenamiento
void burbuja();
void seleccion();
void insercion();
void quicksort(int arr[], int low, int high);
int particionar(int arr[], int low, int high);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);

// Funciones del menu
void menu_consola();
void ordenar_matriz(int metodo);
void aplanar_matriz(int arr[]);  // Aplana la matriz en un arreglo unidimensional
void reconstruir_matriz(int arr[]);  // Reconstruye la matriz a partir de un arreglo unidimensional

int main() {
    ejecucion = 1;
    inicializar_matriz();
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola();
    }
    return 0;
}

// Funcion para inicializar la matriz con numeros aleatorios
void inicializar_matriz() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz[i][j] = rand() % 1000;  // Rellenar con numeros aleatorios entre 0 y 999
        }
    }
}

// Funcion para mostrar la matriz
void mostrar_matriz() {
    printf("Matriz actual:\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Funcion para mostrar el menu
void menu_consola() {
    int seleccion;
    while (ejecucion == STATUS_CONTINUAR) {
        system("CLS");
        printf("MENU\n\n");
        printf("1. Mostrar matriz\n");
        printf("2. Ordenar matriz con Burbuja\n");
        printf("3. Ordenar matriz con Seleccion\n");
        printf("4. Ordenar matriz con Insercion\n");
        printf("5. Ordenar matriz con QuickSort\n");
        printf("6. Ordenar matriz con HeapSort\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        
        switch (seleccion) {
        case 1:
            mostrar_matriz();
            break;
        case 2:
            ordenar_matriz(1);  // Burbuja
            break;
        case 3:
            ordenar_matriz(2);  // Seleccion
            break;
        case 4:
            ordenar_matriz(3);  // Insercion
            break;
        case 5:
            ordenar_matriz(4);  // QuickSort
            break;
        case 6:
            ordenar_matriz(5);  // HeapSort
            break;
        case 0:
            printf("Fin programa...\n");
            exit(0);
            break;
        default:
            printf("Error: ingreso un valor incorrecto\n");
            break;
        }
        system("PAUSE");
    }
}

// Aplana la matriz a un arreglo unidimensional
void aplanar_matriz(int arr[]) {
    int index = 0;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            arr[index++] = matriz[i][j];
        }
    }
}

// Reconstruye la matriz desde un arreglo unidimensional
void reconstruir_matriz(int arr[]) {
    int index = 0;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz[i][j] = arr[index++];
        }
    }
}

// Metodo de ordenamiento Burbuja
void burbuja() {
    int arr[FILAS * COLUMNAS];
    aplanar_matriz(arr);

    for (int i = 0; i < FILAS * COLUMNAS - 1; i++) {
        for (int j = 0; j < FILAS * COLUMNAS - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    reconstruir_matriz(arr);
}

// Metodo de ordenamiento por Seleccion
void seleccion() {
    int arr[FILAS * COLUMNAS];
    aplanar_matriz(arr);

    for (int i = 0; i < FILAS * COLUMNAS - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < FILAS * COLUMNAS; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

    reconstruir_matriz(arr);
}

// Metodo de ordenamiento por Insercion
void insercion() {
    int arr[FILAS * COLUMNAS];
    aplanar_matriz(arr);

    for (int i = 1; i < FILAS * COLUMNAS; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    reconstruir_matriz(arr);
}

// Funcion de particion para QuickSort
int particionar(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Funcion QuickSort
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = particionar(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Metodo de ordenamiento HeapSort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Metodo que elige el tipo de ordenamiento
void ordenar_matriz(int metodo) {
    int arr[FILAS * COLUMNAS];
    aplanar_matriz(arr);

    switch (metodo) {
    case 1:
        burbuja();
        break;
    case 2:
        seleccion();
        break;
    case 3:
        insercion();
        break;
    case 4:
        quicksort(arr, 0, FILAS * COLUMNAS - 1);
        reconstruir_matriz(arr);
        break;
    case 5:
        heapSort(arr, FILAS * COLUMNAS);
        reconstruir_matriz(arr);
        break;
    default:
        printf("Metodo no valido.\n");
    }
}
