#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//DEFINO CONSTANTES
#define MAX_LECTORES 5
#define NUM_ESCRITURAS 3

//DEFINO SEMAFOROS
sem_t mutex;
sem_t mutex_escritura;

//DEFINO CONTADOR
int contador_lectores = 0;

//DEFINO HILOS
pthread_t lectores[MAX_LECTORES];
pthread_t escritores[NUM_ESCRITURAS];

//FIRMAS
void* lector();
void* escritor();

//DECLARO VECTORES
int id_lectores[MAX_LECTORES];
int id_escritores[NUM_ESCRITURAS];

//HILO PRINCIPAL
int main() {
    
    //INICIALIZO SEMAFOROS
    sem_init(&mutex, 0, 1);
    sem_init(&mutex_escritura, 0, 1);

    //CREO HILOS DE LECTORES
    for (int i = 0; i < MAX_LECTORES; i++) {
        id_lectores[i] = i + 1;
        pthread_create(&lectores[i], NULL, lector, &id_lectores[i]);
    }

    //CREP HILOS DE ESCRITORES
    for (int i = 0; i < NUM_ESCRITURAS; i++) {
        id_escritores[i] = i + 1;
        pthread_create(&escritores[i], NULL, escritor, &id_escritores[i]);
    }

    //MERGEO HILO DE LECTORES
    for (int i = 0; i < MAX_LECTORES; i++) {
        pthread_join(lectores[i], NULL);
    }

    //MERGEO HILOS DE ESCRITORES
    for (int i = 0; i < NUM_ESCRITURAS; i++) {
        pthread_join(escritores[i], NULL);
    }

    //LIBERO SEMAFOROS
    sem_destroy(&mutex);
    sem_destroy(&mutex_escritura);

    return 0;
}

void* lector(void* arg) {
    int id = *((int*)arg);
    FILE *archivo;

    sem_wait(&mutex);
    contador_lectores++;
    if (contador_lectores == 1) {
        sem_wait(&mutex_escritura);
    }
    sem_post(&mutex);

    archivo = fopen("hola.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    printf("Lector %d esta leyendo el archivo...\n", id);
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), archivo)) {
        printf("Lector %d leyo: %s", id, buffer);
    }
    fclose(archivo);

    sem_wait(&mutex);
    contador_lectores--;
    if (contador_lectores == 0) {
        sem_post(&mutex_escritura);
    }
    sem_post(&mutex);

    return NULL;
}

void* escritor(void* arg) {
    int id = *((int*)arg);
    FILE *archivo;

    sem_wait(&mutex_escritura);
    archivo = fopen("hola.txt", "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    printf("Escritor %d esta escribiendo en el archivo...\n", id);
    fprintf(archivo, "Escritor %d añadio esta linea.\n", id);
    fclose(archivo);

    sem_post(&mutex_escritura);

    return NULL;
}
