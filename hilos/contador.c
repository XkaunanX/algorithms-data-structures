#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//DEFINO UN BUFFER
#define BUFFER_SIZE 5

//DECLARO EL BUFFER
int buffer[BUFFER_SIZE];
//DECLARO UN CONTADOR
int contador = 0;
//DECLARO SEMAFOROS
sem_t vacio, lleno;
//DECLARO HILOS
pthread_t prod, consu;
//FIRMAS
void *productor();
void *consumidor();

//HILO PRINCIPAL
int main()
{
    //INICIALIZO EL SEMAFORO
    sem_init(&vacio, 0, BUFFER_SIZE)   ;
    sem_init(&lleno, 0, 0);

    //INICIALIZO LOS HILOS
    pthread_create(&prod, NULL, productor, NULL);
    pthread_create(&consu, NULL, consumidor, NULL);

    //ESPERO A LOS HILOS
    pthread_join(prod, NULL);
    pthread_join(consu, NULL);

    //LIBERO LOS SEMAFOROS
    sem_destroy(&prod);
    sem_destroy(&consu);

    return 0;
}

void *productor()
{
    for (int i = 0; i < 10; i++) {
        sem_wait(&vacio);
        buffer[contador++] = i;
        printf("Productor: produjo %d\n", i);
        sem_post(&lleno);
    }
    return NULL;
}

void *consumidor()
{
    for (int i = 0; i < 10; i++) {
        sem_wait(&lleno);
        int item = buffer[--contador];
        printf("Consumidor: consumio %d\n", item);
        sem_post(&vacio);
    }
    return NULL;
}
