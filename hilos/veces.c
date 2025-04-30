#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// Declaracion del semaforo
sem_t sem;

// Declaracion de los hilos
pthread_t hilo1, hilo2;

// Firmas de las funciones de los hilos
static void *fun_hilo1(void* arg);
static void *fun_hilo2(void* arg);

int main() {
    // Inicializar semaforo, valor inicial 0
    sem_init(&sem, 0, 0);

    // Crear los hilos
    pthread_create(&hilo1, NULL, *fun_hilo1, NULL);
    pthread_create(&hilo2, NULL, *fun_hilo2, NULL);

    // Esperar a que los hilos terminen
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Destruir el semaforo
    sem_destroy(&sem);

    return 0;
}

static void* fun_hilo1(void* arg) {
    // Hilo 1: Publicar en el semaforo para permitir que hilo 2 continue
    printf("Hilo 1: Publicando en el semaforo\n");
    sem_post(&sem);
    return NULL;
}

static void* fun_hilo2(void* arg) {
    // Hilo 2: Esperar 10 veces en el semaforo
    for (int i = 0; i < 10; i++) {
        sem_wait(&sem);
        printf("Hilo 2: Esperando... %d veces\n", i + 1);
    }
    return NULL;
}
