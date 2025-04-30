#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//Declaro semaforo
sem_t sem;
//Declaro hilo
pthread_t hilo1, hilo2;
//Contador
int contador = 0;
//Firmas
static void *function_hilo_1();
static void *function_hilo_2();

int main(){
    //INICIALIZO SEMAFORO
    sem_init(&sem, 0, 0);
    //CREO LOS HILOS
    pthread_create(&hilo1, NULL, *function_hilo_1, NULL);
    pthread_create(&hilo2, NULL, *function_hilo_2, NULL);
    //ESPERO A LOS HILOS
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    return 0;
}

//FUNCIONES

static void *function_hilo_1(){
    sem_wait(&sem);
    for (int i = 0; i < 10000; i++)
    {
        contador--;
        printf("Funcion 1: %d \n", contador);
    }
}

static void *function_hilo_2(){
    for (int i = 0; i < 10000; i++)
    {
        contador++;
        printf("Funcion 2: %d\n", contador);
       
    }
    sem_post(&sem);
}
