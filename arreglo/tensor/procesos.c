#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define X 5   // Dimension X
#define Y 5   // Dimension Y
#define Z 5   // Dimension Z
#define NUM_PROCESOS 125 // Numero de procesos (5x5x5)

#define FUNCION_A 0
#define FUNCION_B 1
#define FUNCION_C 2
#define FUNCION_D 3
#define FUNCION_E 4

// Definir un tensor 3D donde cada elemento sea un puntero a funcion
void (**tensor)(void);

// Funciones que se ejecutaran en los procesos hijos
void funcion_a() {
    printf("Ejecutando funcion A\n");
}

void funcion_b() {
    printf("Ejecutando funcion B\n");
}

void funcion_c() {
    printf("Ejecutando funcion C\n");
}

void funcion_d() {
    printf("Ejecutando funcion D\n");
}

void funcion_e() {
    printf("Ejecutando funcion E\n");
}

// Funcion que ejecutara una funcion basada en la direccion del tensor
void ejecutar_funcion(int x, int y, int z) {
    // Ejecutar la funcion correspondiente desde el tensor
    tensor[x][y][z]();
}

// Inicializar el tensor con direcciones de las funciones
void inicializar_tensor() {
    tensor = (void ***)malloc(X * sizeof(void **));

    for (int i = 0; i < X; i++) {
        tensor[i] = (void **)malloc(Y * sizeof(void *));
        for (int j = 0; j < Y; j++) {
            tensor[i][j] = (void *)malloc(Z * sizeof(void *));
        }
    }

    // Asignar funciones a posiciones del tensor
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                if (i == 0) {
                    tensor[i][j][k] = funcion_a;
                } else if (i == 1) {
                    tensor[i][j][k] = funcion_b;
                } else if (i == 2) {
                    tensor[i][j][k] = funcion_c;
                } else if (i == 3) {
                    tensor[i][j][k] = funcion_d;
                } else {
                    tensor[i][j][k] = funcion_e;
                }
            }
        }
    }
}

// Liberar la memoria utilizada por el tensor
void liberar_tensor() {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            free(tensor[i][j]);
        }
        free(tensor[i]);
    }
    free(tensor);
}

int main() {
    srand(time(NULL));

    // Inicializar el tensor
    inicializar_tensor();

    // Crear procesos
    pid_t pid;
    int indices[NUM_PROCESOS];

    for (int i = 0; i < NUM_PROCESOS; i++) {
        indices[i] = i;  // Asignar un indice a cada proceso
        pid = fork();

        if (pid == 0) {
            // Hijo: Ejecuta la funcion correspondiente
            int x = indices[i] / (Y * Z); // Posicion X en el tensor
            int y = (indices[i] / Z) % Y; // Posicion Y en el tensor
            int z = indices[i] % Z;       // Posicion Z en el tensor

            // Ejecutar la funcion del tensor
            ejecutar_funcion(x, y, z);

            // Terminar el proceso hijo
            exit(0);
        }
    }

    // El proceso padre espera a que todos los hijos terminen
    for (int i = 0; i < NUM_PROCESOS; i++) {
        wait(NULL);
    }

    // Liberar la memoria
    liberar_tensor();

    return 0;
}
