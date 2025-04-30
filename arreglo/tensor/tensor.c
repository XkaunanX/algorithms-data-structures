#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 4   // Tamaño en la dimension X
#define Y 3   // Tamaño en la dimension Y
#define Z 5   // Tamaño en la dimension Z

// Definir el tensor como un puntero a punteros en 3D
int ***tensor;

// Prototipos de funciones
void inicializar_tensor();
void imprimir_tensor();
void modificar_elemento(int x, int y, int z, int valor);
int consultar_elemento(int x, int y, int z);
void inicializar_con_valores_aleatorios();

void menu() {
    int opcion, x, y, z, valor;
    while (1) {
        system("CLS");
        printf("MENU DE OPERACIONES SOBRE EL TENSOR 3D\n");
        printf("1. Inicializar tensor con valores aleatorios\n");
        printf("2. Modificar un elemento del tensor\n");
        printf("3. Consultar un elemento del tensor\n");
        printf("4. Imprimir tensor completo\n");
        printf("5. Salir\n");
        printf("\n> Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                inicializar_con_valores_aleatorios();
                printf("Tensor inicializado con valores aleatorios.\n");
                break;
            case 2:
                printf("> Ingrese las coordenadas (x, y, z) del elemento a modificar: ");
                scanf("%d %d %d", &x, &y, &z);
                printf("> Ingrese el nuevo valor: ");
                scanf("%d", &valor);
                modificar_elemento(x, y, z, valor);
                printf("Elemento [%d][%d][%d] modificado a %d.\n", x, y, z, valor);
                break;
            case 3:
                printf("> Ingrese las coordenadas (x, y, z) del elemento a consultar: ");
                scanf("%d %d %d", &x, &y, &z);
                valor = consultar_elemento(x, y, z);
                printf("Valor en [%d][%d][%d]: %d\n", x, y, z, valor);
                break;
            case 4:
                imprimir_tensor();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                // Liberar memoria antes de salir
                for (int i = 0; i < X; i++) {
                    for (int j = 0; j < Y; j++) {
                        free(tensor[i][j]);
                    }
                    free(tensor[i]);
                }
                free(tensor);
                exit(0);
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
        printf("\n");
        system("PAUSE");
    }
}

// Funcion para inicializar el tensor dinamicamente
void inicializar_tensor() {
    tensor = (int ***)malloc(X * sizeof(int **));
    for (int i = 0; i < X; i++) {
        tensor[i] = (int **)malloc(Y * sizeof(int *));
        for (int j = 0; j < Y; j++) {
            tensor[i][j] = (int *)malloc(Z * sizeof(int));
        }
    }
}

// Funcion para inicializar el tensor con valores aleatorios
void inicializar_con_valores_aleatorios() {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                tensor[i][j][k] = rand() % 100;  // Asignar valores aleatorios entre 0 y 99
            }
        }
    }
}

// Funcion para modificar un elemento del tensor
void modificar_elemento(int x, int y, int z, int valor) {
    if (x >= 0 && x < X && y >= 0 && y < Y && z >= 0 && z < Z) {
        tensor[x][y][z] = valor;
    } else {
        printf("Indices fuera de rango.\n");
    }
}

// Funcion para consultar un elemento del tensor
int consultar_elemento(int x, int y, int z) {
    if (x >= 0 && x < X && y >= 0 && y < Y && z >= 0 && z < Z) {
        return tensor[x][y][z];
    } else {
        printf("Indices fuera de rango.\n");
        return -1;  // Valor de error
    }
}

// Funcion para imprimir el tensor completo
void imprimir_tensor() {
    for (int i = 0; i < X; i++) {
        printf("Capa %d:\n", i);
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                printf("%d ", tensor[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    inicializar_tensor();  // Inicializar la memoria para el tensor
    menu();  // Mostrar el menu y permitir la interaccion
    return 0;
}
