#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//DECLARO EL SEMAFORO
sem_t sem;
//DECLARO LOS HILOS
pthread_t hilo1, hilo2, hilo3;
//FIRMAS
static void *function_hilo_1();
static void *function_hilo_2();
static void *function_hilo_3();

//HILO PRINCIPAL
int main() {
    //INICIALIZO EL HILO
    sem_init(&sem, 0, 0);
    //CREO LOS HILOS
    pthread_create(&hilo1, NULL, function_hilo_1, NULL);
    pthread_create(&hilo2, NULL, function_hilo_2, NULL);
    pthread_create(&hilo3, NULL, function_hilo_3, NULL);
    //PERMITO QUE EL HILO 1 SE EJECUTE PRIMERO
    sem_post(&sem); 
    //ESPERO A LOS HILOS
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    //LIBERO EL SEMAFORO
    sem_destroy(&sem);
    return 0;
}

static void *function_hilo_1() {
    sem_wait(&sem);
    printf("Soy el hilo 1 (TID: %lu), en el proceso (PID: %d)\n", pthread_self(), getpid());
    sem_post(&sem);
    return NULL;
}

static void *function_hilo_2() {
    sem_wait(&sem);
    printf("Soy el hilo 2 (TID: %lu), en el proceso (PID: %d)\n", pthread_self(), getpid());
    sem_post(&sem);
    return NULL;
}

static void *function_hilo_3() {
    sem_wait(&sem);
    printf("Soy el hilo 3 (TID: %lu), en el proceso (PID: %d)\n", pthread_self(), getpid());
    return NULL;
}
