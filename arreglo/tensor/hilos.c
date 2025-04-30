#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define X 5   // Dimension X
#define Y 5   // Dimension Y
#define Z 5   // Dimension Z
#define NUM_THREADS 125 // Numero de hilos (5x5x5)

#define FUNCION_A 0
#define FUNCION_B 1
#define FUNCION_C 2
#define FUNCION_D 3
#define FUNCION_E 4

// Definir un tensor 3D donde cada elemento sea un puntero a funcion
void (**tensor)(void);

// Semaforo para sincronizacion
sem_t sem;

// Definir funciones para cada posicion en el tensor
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

// Hilo que ejecutara una funcion basada en la direccion del tensor
void *ejecutar_funcion(void *args) {
    int x = *((int *)args) / (Y * Z); // Posicion X en el tensor
    int y = ((*((int *)args) / Z) % Y); // Posicion Y en el tensor
    int z = *((int *)args) % Z;  // Posicion Z en el tensor

    // Sincronizar acceso con el semaforo
    sem_wait(&sem);

    // Ejecutar la funcion correspondiente desde el tensor
    tensor[x][y][z]();

    // Liberar semaforo
    sem_post(&sem);

    pthread_exit(NULL);
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

    // Inicializar semaforo
    sem_init(&sem, 0, 1);  // Semaforo binario

    // Inicializar el tensor
    inicializar_tensor();

    // Crear hilos
    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i;  // Asignar un indice a cada hilo
        pthread_create(&threads[i], NULL, ejecutar_funcion, (void *)&indices[i]);
    }

    // Esperar que todos los hilos terminen su ejecucion
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Liberar semaforo y memoria
    sem_destroy(&sem);
    liberar_tensor();

    return 0;
}
