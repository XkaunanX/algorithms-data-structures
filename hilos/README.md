# ¿Que son los Hilos?

Un **hilo** (thread) es la unidad basica de ejecucion dentro de un proceso. Un proceso puede contener uno o mas hilos, los cuales comparten el mismo espacio de memoria y recursos del proceso, pero cada hilo tiene su propio contador de programa, pila y registros. Los hilos permiten la ejecucion concurrente de tareas dentro de un programa.

### ¿Como Funcionan los Hilos?

Los hilos pueden ejecutarse en paralelo en sistemas con multiples nucleos de procesador, lo que mejora la eficiencia y el rendimiento de las aplicaciones. En sistemas con un solo nucleo, el sistema operativo puede intercambiar entre hilos rapidamente, dando la impresion de que se ejecutan en paralelo.

Los hilos pueden colaborar entre si, pero tambien pueden necesitar sincronizacion para evitar problemas como la **condicion de carrera** (race condition), donde dos o mas hilos intentan acceder o modificar los mismos datos simultaneamente, lo que puede generar resultados impredecibles.

```plaintext
Proceso Principal:
|
|--- Hilo 1: Tarea A
|      |
|      |--- Hilo 2: Tarea B
|      |
|      |--- Hilo 3: Tarea C
|
|--- Hilo 4: Tarea D
|      |
|      |--- Hilo 5: Tarea E
|
|--- Hilo 6: Tarea F
```

## ¿Que es la Seccion Critica?

Una **seccion critica** es una parte del codigo que accede a recursos compartidos, como variables o estructuras de datos, y que puede ser ejecutada simultaneamente por varios hilos. La ejecucion concurrente de una seccion critica sin control adecuado puede llevar a problemas como la corrupcion de datos.

```c
#include <stdio.h>
#include <pthread.h>

int recurso = 0; // Recurso compartido

// Función que simula una tarea con acceso a la sección crítica
void* tarea(void* arg) {
    printf("Hilo %d accediendo al recurso\n", *((int*)arg));
    
    // Sección crítica: acceso sin protección
    recurso++;
    printf("Recurso actualizado: %d\n", recurso);
    
    return NULL;
}

int main() {
    pthread_t hilos[3];
    int ids[3] = {1, 2, 3};

    // Crea los hilos
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, tarea, &ids[i]);
    }

    // Espera a que todos los hilos terminen
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("Valor final del recurso: %d\n", recurso);
    return 0;
}
```

### Sincronizacion de Hilos

Para evitar estos problemas, se utilizan mecanismos de **sincronizacion** que garantizan que solo un hilo pueda acceder a la seccion critica en un momento dado. Algunos de los mecanismos mas comunes son:

- **Mutexes (Mutual Exclusion Locks)**: Permiten que un hilo adquiera un bloqueo sobre la seccion critica, garantizando que otros hilos no puedan acceder a ella hasta que el primer hilo haya terminado.
- **Semaforos**: Son variables de sincronizacion que controlan el acceso a un recurso limitado. En lugar de bloquearse completamente, los semaforos permiten un control mas flexible sobre el acceso concurrente.

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo; // Semáforo para proteger la sección crítica
int recurso = 0; // Recurso compartido

// Función que simula una tarea con acceso a la sección crítica
void* tarea(void* arg) {
    printf("Hilo %d accediendo al recurso\n", *((int*)arg));

    sem_wait(&semaforo); // Espera (bloquea) el semáforo antes de entrar a la sección crítica

    // Sección crítica: acceso protegido por semáforo
    recurso++;
    printf("Recurso actualizado: %d\n", recurso);

    sem_post(&semaforo); // Libera el semáforo después de salir de la sección crítica

    return NULL;
}

int main() {
    pthread_t hilos[3];
    int ids[3] = {1, 2, 3};

    sem_init(&semaforo, 0, 1); // Inicializa el semáforo (valor inicial 1)

    // Crea los hilos
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, tarea, &ids[i]);
    }

    // Espera a que todos los hilos terminen
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    sem_destroy(&semaforo); // Destruye el semáforo

    printf("Valor final del recurso: %d\n", recurso);
    return 0;
}
```

# Librerias

### `#include <pthread.h>`
Esta libreria proporciona una interfaz para trabajar con hilos en programas concurrentes. Permite crear y gestionar multiples hilos dentro de un proceso, facilitando la ejecucion paralela de tareas.

#### Funciones principales:
- **Creacion y terminacion de hilos**:
  - `pthread_create()`: Crea un nuevo hilo.
  - `pthread_exit()`: Termina el hilo que lo llama.
  
- **Sincronizacion**:
  - `pthread_join()`: Espera a que un hilo termine.
  - `pthread_mutex_lock()` y `pthread_mutex_unlock()`: Gestionan el acceso a recursos compartidos mediante mutexes.
  - `pthread_cond_wait()` y `pthread_cond_signal()`: Permiten la sincronizacion basada en condiciones.
  
- **Atributos de hilos**:
  - `pthread_attr_init()`, `pthread_attr_setdetachstate()`: Establecen atributos especificos del hilo, como el estado de separacion (joinable o detached).

### `#include <semaphore.h>`
Esta libreria proporciona funciones para trabajar con semaforos, que son herramientas de sincronizacion utilizadas para controlar el acceso a recursos compartidos en entornos concurrentes.

#### Funciones importantes:
- **Inicializacion y destruccion de semaforos**:
  - `sem_init()`: Inicializa un semaforo.
  - `sem_destroy()`: Destruye un semaforo.
  
- **Operaciones sobre semaforos**:
  - `sem_wait()`: Decrementa el valor del semaforo; si el valor es cero, el hilo se bloquea hasta que el semaforo sea mayor que cero.
  - `sem_post()`: Incrementa el valor del semaforo, liberando a cualquier hilo bloqueado si el valor era cero.

- **Funciones de consulta**:
  - `sem_getvalue()`: Obtiene el valor actual del semaforo.

## Explicacion de los Elementos Utilizados

### `sem_t sem;`
`sem_t` es un tipo de dato definido en la libreria de semaforos POSIX. Este tipo se utiliza para declarar semaforos, que son mecanismos de sincronizacion que permiten controlar el acceso a recursos compartidos en programas concurrentes o multihilo.

> `sem_t` se usa para semaforos.

### `pthread_t hilo1, hilo2;`
`pthread_t` es un tipo de dato utilizado para representar identificadores de hilos. Los objetos de tipo `pthread_t` se utilizan para crear y manejar hilos en un programa que usa la programacion multihilo.

> `pthread_t` se usa para identificadores de hilos.

### `static void *function_hilo_1();`
La declaracion `static void *function_hilo_1()` define una funcion que puede ser utilizada unicamente dentro de su archivo de origen. La funcion devuelve un puntero generico a cualquier tipo de dato.

#### Desglose:
- **static**: La funcion solo es accesible dentro del archivo donde esta definida.
- **void ***: El tipo de retorno es un puntero void, que puede apuntar a cualquier tipo de dato.
- **function_hilo_1()**: Es el nombre de la funcion.

### `pthread_create(&hilo1, NULL, *function_hilo_1, NULL);`
La funcion `pthread_create()` crea un nuevo hilo y le asigna la funcion que debe ejecutar.

#### Desglose de parametros:
- **&hilo1**: El identificador del hilo que se esta creando.
- **NULL (segundo argumento)**: Atributos del hilo, en este caso, se usan los valores predeterminados.
- ***function_hilo_1**: La direccion de la funcion que se ejecutara en el nuevo hilo.
- **NULL (cuarto argumento)**: Argumento que se pasa a la funcion del hilo (si no se necesita, se pasa NULL).

### `sem_init(&sem, 0, 0);`
La funcion `sem_init()` inicializa un semaforo.

#### Desglose de parametros:
- **&sem**: Puntero al semaforo a inicializar.
- **0 (pshared)**: Si es 0, el semaforo solo se usara dentro del mismo proceso.
- **0 (value)**: El semaforo estara inicialmente bloqueado (valor 0).

### `pthread_join(hilo1, NULL);`
La funcion `pthread_join()` espera a que un hilo especifico termine su ejecucion.

#### Desglose de parametros:
- **hilo1**: El identificador del hilo que se espera.
- **NULL**: Puntero a un puntero void donde se almacenara el valor de retorno del hilo (si no se necesita, se pasa NULL).

### `sem_wait(&sem);`
La funcion `sem_wait()` decrementa el valor de un semaforo. Si el valor es cero, el hilo que la llama se bloquea hasta que el semaforo sea liberado.

#### Desglose de parametros:
- **&sem**: Puntero al semaforo a decrementar.

### `sem_post(&sem);`
La funcion `sem_post()` incrementa el valor de un semaforo, lo que puede liberar a un hilo bloqueado en `sem_wait()`.

#### Desglose de parametros:
- **&sem**: Puntero al semaforo a incrementar.
