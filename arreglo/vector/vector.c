#include <stdio.h>
#include <stdlib.h>

#define MAX 10   // Tamaño maximo del arreglo
#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos del arreglo
typedef struct {
    int i;
    int valor;
} Data;

// Arreglo unidimensional para almacenar los elementos
Data arreglo[MAX];

// Funciones para gestionar el arreglo
void inicializar_arreglo();
void insertar_elemento(Data dato, int index);
void eliminar_elemento(int index);
void modificar_elemento(int index, int nuevo_valor);
void consultar_elemento(int index);
void imprimir_arreglo();
void menu_consola();

// Metodos de ordenamiento
void bubble_sort();
void selection_sort();
void insertion_sort();
void quick_sort(int low, int high);
int partition(int low, int high);
void merge_sort(int low, int high);
void merge(int low, int mid, int high);
void heapify(int n, int i);
void heap_sort();
void shell_sort();
void cocktail_sort();
void bidirectional_bubble_sort();
void adaptive_selection_sort();

// Funcion para la gestion de la consola
void menu_consola() {
    int interfaz = 1;
    int seleccion;
    int index;
    int nuevo_valor;
    Data dato;

    while (interfaz == STATUS_CONTINUAR) {
        // Limpiar consola
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar elemento en el arreglo\n");
        printf("2. Eliminar elemento del arreglo\n");
        printf("3. Modificar un elemento del arreglo\n");
        printf("4. Consultar un elemento del arreglo\n");
        printf("5. Mostrar arreglo\n");
        printf("6. Ordenar arreglo (Bubble Sort)\n");
        printf("7. Ordenar arreglo (Selection Sort)\n");
        printf("8. Ordenar arreglo (Insertion Sort)\n");
        printf("9. Ordenar arreglo (Quick Sort)\n");
        printf("10. Ordenar arreglo (Merge Sort)\n");
        printf("11. Ordenar arreglo (Heap Sort)\n");
        printf("12. Ordenar arreglo (Shell Sort)\n");
        printf("13. Ordenar arreglo (Cocktail Sort)\n");
        printf("14. Ordenar arreglo (Bidirectional Bubble Sort)\n");
        printf("15. Ordenar arreglo (Adaptive Selection Sort)\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");

        switch (seleccion) {
            case 1:
                id++;
                dato.i = id;
                printf("> Ingrese el valor para el nuevo elemento: ");
                scanf("%d", &dato.valor);
                printf("> Ingrese el indice (0-9) donde insertar el elemento: ");
                scanf("%d", &index);
                if (index >= 0 && index < MAX) {
                    insertar_elemento(dato, index);
                } else {
                    printf("Indice fuera de rango.\n");
                }
                break;
            case 2:
                printf("> Ingrese el indice (0-9) para eliminar el elemento: ");
                scanf("%d", &index);
                if (index >= 0 && index < MAX) {
                    eliminar_elemento(index);
                } else {
                    printf("Indice fuera de rango.\n");
                }
                break;
            case 3:
                printf("> Ingrese el indice (0-9) del elemento a modificar: ");
                scanf("%d", &index);
                if (index >= 0 && index < MAX) {
                    printf("> Ingrese el nuevo valor: ");
                    scanf("%d", &nuevo_valor);
                    modificar_elemento(index, nuevo_valor);
                } else {
                    printf("Indice fuera de rango.\n");
                }
                break;
            case 4:
                printf("> Ingrese el indice (0-9) para consultar el elemento: ");
                scanf("%d", &index);
                if (index >= 0 && index < MAX) {
                    consultar_elemento(index);
                } else {
                    printf("Indice fuera de rango.\n");
                }
                break;
            case 5:
                imprimir_arreglo();
                break;
            case 6:
                bubble_sort();
                printf("Arreglo ordenado con Bubble Sort.\n");
                break;
            case 7:
                selection_sort();
                printf("Arreglo ordenado con Selection Sort.\n");
                break;
            case 8:
                insertion_sort();
                printf("Arreglo ordenado con Insertion Sort.\n");
                break;
            case 9:
                quick_sort(0, MAX - 1);
                printf("Arreglo ordenado con Quick Sort.\n");
                break;
            case 10:
                merge_sort(0, MAX - 1);
                printf("Arreglo ordenado con Merge Sort.\n");
                break;
            case 11:
                heap_sort();
                printf("Arreglo ordenado con Heap Sort.\n");
                break;
            case 12:
                shell_sort();
                printf("Arreglo ordenado con Shell Sort.\n");
                break;
            case 13:
                cocktail_sort();
                printf("Arreglo ordenado con Cocktail Sort.\n");
                break;
            case 14:
                bidirectional_bubble_sort();
                printf("Arreglo ordenado con Bidirectional Bubble Sort.\n");
                break;
            case 15:
                adaptive_selection_sort();
                printf("Arreglo ordenado con Adaptive Selection Sort.\n");
                break;
            case 0:
                printf("Fin del programa ...\n");
                exit(0);
                break;
            default:
                printf("Error: ingreso un valor incorrecto\n");
                break;
        }
        system("PAUSE");
    }
}

// Hilo principal
int main() {
    ejecucion = 1;

    inicializar_arreglo();  // Inicializa el arreglo con valores por defecto

    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola();  // Ejecuta el menu
    }
    return 0;
}

// Inicializa el arreglo con valores por defecto
void inicializar_arreglo() {
    for (int i = 0; i < MAX; i++) {
        arreglo[i].i = i;
        arreglo[i].valor = rand() % 100;  // Valores aleatorios
    }
}

// Inserta un elemento en el arreglo en la posicion indicada
void insertar_elemento(Data dato, int index) {
    if (arreglo[index].valor == -1) {  // Verifica si la posicion esta vacia
        arreglo[index] = dato;
        printf("Elemento insertado correctamente en el indice %d\n", index);
    } else {
        printf("El indice %d ya esta ocupado.\n", index);
    }
}

// Elimina un elemento del arreglo en la posicion indicada
void eliminar_elemento(int index) {
    if (arreglo[index].valor != -1) {  // Verifica si la posicion no esta vacia
        arreglo[index].valor = -1;
        printf("Elemento eliminado correctamente del indice %d\n", index);
    } else {
        printf("No hay ningun elemento en el indice %d para eliminar.\n", index);
    }
}

// Modifica el valor de un elemento en el arreglo
void modificar_elemento(int index, int nuevo_valor) {
    if (arreglo[index].valor != -1) {  // Verifica si la posicion no esta vacia
        arreglo[index].valor = nuevo_valor;
        printf("Elemento modificado correctamente en el indice %d\n", index);
    } else {
        printf("No hay ningun elemento en el indice %d para modificar.\n", index);
    }
}

// Consulta un elemento del arreglo en la posicion indicada
void consultar_elemento(int index) {
    if (arreglo[index].valor != -1) {  // Verifica si la posicion no esta vacia
        printf("Elemento en el indice %d: ID=%d, Valor=%d\n", index, arreglo[index].i, arreglo[index].valor);
    } else {
        printf("No hay ningun elemento en el indice %d.\n", index);
    }
}

// Imprime el contenido del arreglo
void imprimir_arreglo() {
    printf("Contenido del arreglo:\n");
    printf("-------------------------------------------------\n");
    printf("| Indice |   ID   |   Valor   |\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < MAX; i++) {
        if (arreglo[i].valor != -1) {
            printf("|   %2d   |   %2d   |    %3d    |\n", i, arreglo[i].i, arreglo[i].valor);
        } else {
            printf("|   %2d   |   -    |    -     |\n", i);
        }
    }
    printf("-------------------------------------------------\n");
}

// Implementaciones de los algoritmos de ordenamiento

// Bubble Sort
void bubble_sort() {
    int temp;
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = 0; j < MAX - 1 - i; j++) {
            if (arreglo[j].valor > arreglo[j + 1].valor) {
                temp = arreglo[j].valor;
                arreglo[j].valor = arreglo[j + 1].valor;
                arreglo[j + 1].valor = temp;
            }
        }
    }
}

// Selection Sort
void selection_sort() {
    int min_idx, temp;
    for (int i = 0; i < MAX - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < MAX; j++) {
            if (arreglo[j].valor < arreglo[min_idx].valor) {
                min_idx = j;
            }
        }
        temp = arreglo[i].valor;
        arreglo[i].valor = arreglo[min_idx].valor;
        arreglo[min_idx].valor = temp;
    }
}

// Insertion Sort
void insertion_sort() {
    int key, j;
    for (int i = 1; i < MAX; i++) {
        key = arreglo[i].valor;
        j = i - 1;
        while (j >= 0 && arreglo[j].valor > key) {
            arreglo[j + 1].valor = arreglo[j].valor;
            j--;
        }
        arreglo[j + 1].valor = key;
    }
}

// Quick Sort
int partition(int low, int high) {
    int pivot = arreglo[high].valor;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arreglo[j].valor <= pivot) {
            i++;
            int temp = arreglo[i].valor;
            arreglo[i].valor = arreglo[j].valor;
            arreglo[j].valor = temp;
        }
    }
    int temp = arreglo[i + 1].valor;
    arreglo[i + 1].valor = arreglo[high].valor;
    arreglo[high].valor = temp;
    return i + 1;
}

void quick_sort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quick_sort(low, pi - 1);
        quick_sort(pi + 1, high);
    }
}

// Merge Sort
void merge(int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    Data L[n1], R[n2];
    
    for (int i = 0; i < n1; i++) {
        L[i] = arreglo[low + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arreglo[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i].valor <= R[j].valor) {
            arreglo[k] = L[i];
            i++;
        } else {
            arreglo[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arreglo[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arreglo[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
}

// Heap Sort
void heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arreglo[left].valor > arreglo[largest].valor)
        largest = left;

    if (right < n && arreglo[right].valor > arreglo[largest].valor)
        largest = right;

    if (largest != i) {
        Data temp = arreglo[i];
        arreglo[i] = arreglo[largest];
        arreglo[largest] = temp;
        heapify(n, largest);
    }
}

void heap_sort() {
    for (int i = MAX / 2 - 1; i >= 0; i--) {
        heapify(MAX, i);
    }

    for (int i = MAX - 1; i >= 0; i--) {
        Data temp = arreglo[0];
        arreglo[0] = arreglo[i];
        arreglo[i] = temp;
        heapify(i, 0);
    }
}

// Shell Sort
void shell_sort() {
    int gap, temp, i, j;
    for (gap = MAX / 2; gap > 0; gap /= 2) {
        for (i = gap; i < MAX; i++) {
            temp = arreglo[i].valor;
            j = i;
            while (j >= gap && arreglo[j - gap].valor > temp) {
                arreglo[j].valor = arreglo[j - gap].valor;
                j -= gap;
            }
            arreglo[j].valor = temp;
        }
    }
}

// Cocktail Sort
void cocktail_sort() {
    int temp, swapped = 1;
    int start = 0, end = MAX - 1;

    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (arreglo[i].valor > arreglo[i + 1].valor) {
                temp = arreglo[i].valor;
                arreglo[i].valor = arreglo[i + 1].valor;
                arreglo[i + 1].valor = temp;
                swapped = 1;
            }
        }
        if (!swapped)
            break;

        swapped = 0;
        end--;

        for (int i = end - 1; i >= start; i--) {
            if (arreglo[i].valor > arreglo[i + 1].valor) {
                temp = arreglo[i].valor;
                arreglo[i].valor = arreglo[i + 1].valor;
                arreglo[i + 1].valor = temp;
                swapped = 1;
            }
        }
        start++;
    }
}

// Bidirectional Bubble Sort
void bidirectional_bubble_sort() {
    int temp, start = 0, end = MAX - 1;
    int swapped = 1;

    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (arreglo[i].valor > arreglo[i + 1].valor) {
                temp = arreglo[i].valor;
                arreglo[i].valor = arreglo[i + 1].valor;
                arreglo[i + 1].valor = temp;
                swapped = 1;
            }
        }
        end--;

        if (!swapped)
            break;

        swapped = 0;
        for (int i = end; i > start; i--) {
            if (arreglo[i].valor < arreglo[i - 1].valor) {
                temp = arreglo[i].valor;
                arreglo[i].valor = arreglo[i - 1].valor;
                arreglo[i - 1].valor = temp;
                swapped = 1;
            }
        }
        start++;
    }
}

// Adaptive Selection Sort
void adaptive_selection_sort() {
    int min_idx, temp;
    int swapped = 1;

    for (int i = 0; i < MAX - 1 && swapped; i++) {
        swapped = 0;
        min_idx = i;
        for (int j = i + 1; j < MAX; j++) {
            if (arreglo[j].valor < arreglo[min_idx].valor) {
                min_idx = j;
                swapped = 1;
            }
        }
        if (swapped) {
            temp = arreglo[i].valor;
            arreglo[i].valor = arreglo[min_idx].valor;
            arreglo[min_idx].valor = temp;
        }
    }
}
