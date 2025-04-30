#include <stdio.h>
#include <stdlib.h>

int main() {
    int X = 2, Y = 3, Z = 4;

    // Reservar memoria para un tensor 3D dinamico
    int ***tensor;
    tensor = (int ***)malloc(X * sizeof(int **));

    for (int i = 0; i < X; i++) {
        tensor[i] = (int **)malloc(Y * sizeof(int *));
        for (int j = 0; j < Y; j++) {
            tensor[i][j] = (int *)malloc(Z * sizeof(int));
        }
    }

    // Inicializacion del tensor
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                tensor[i][j][k] = i + j + k;  // Asignacion de valores
            }
        }
    }

    // Imprimir el tensor
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                printf("tensor[%d][%d][%d] = %d\n", i, j, k, tensor[i][j][k]);
            }
        }
    }

    // Liberar la memoria
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            free(tensor[i][j]);
        }
        free(tensor[i]);
    }
    free(tensor);

    return 0;
}
