# Implementacion de Concurrencia con Procesos Hijos en C

## Que es un proceso hijo?

En sistemas operativos, un **proceso hijo** es un proceso que es creado por otro proceso, conocido como el **proceso padre**. Un proceso hijo hereda ciertos atributos del proceso padre, pero puede ejecutar tareas de forma independiente. Los procesos hijos son utiles para realizar tareas concurrentes, permitiendo que un programa ejecute multiples tareas simultaneamente.

```plaintext
       +------------------+
       |  Proceso Padre   |
       |  (Main Process)   |
       +------------------+
                |
    +-----------+-----------+
    |                       |
+------------------+   +------------------+
|  Proceso Hijo 1  |   |  Proceso Hijo 2  |
|  (Child Process) |   |  (Child Process)  |
+------------------+   +------------------+
```

## Que es un PID?

El **PID** (Process Identifier) es un numero unico asignado por el sistema operativo a cada proceso que se ejecuta en el sistema. Cada proceso en ejecucion tiene un PID que lo identifica de manera unica. El proceso padre y sus procesos hijos tienen PIDs diferentes. El proceso hijo puede conocer el PID de su proceso padre, pero el padre no necesariamente sabe el PID de su hijo de manera inmediata.

```plaintext
       +------------------+  
       |  Proceso Padre   |  
       |  PID: 1234       |  
       +------------------+  
                |
    +-----------+-----------+
    |                       |
+------------------+   +------------------+
|  Proceso Hijo 1  |   |  Proceso Hijo 2  |
|  PID: 5678       |   |  PID: 9101       |
+------------------+   +------------------+
```

## Comportamiento de los procesos hijos

El comportamiento de los procesos hijos depende de la programacion y el sistema operativo. En general:

- **Proceso padre**: Al invocar una llamada como `fork()`, el proceso padre crea un proceso hijo. Despues de la creacion, el proceso padre puede esperar la finalizacion del hijo, o seguir ejecutando otras tareas de forma concurrente.
- **Proceso hijo**: El proceso hijo empieza a ejecutarse en paralelo al proceso padre, generalmente ejecutando una tarea diferente de la que ejecutaba el padre.

Ambos procesos, el padre y el hijo, continúan ejecutandose independientemente, permitiendo la ejecucion de multiples tareas en paralelo.

## Comunicacion entre procesos hijos y padre

La comunicacion entre un proceso padre y sus procesos hijos se puede realizar de varias maneras. Algunas de las tecnicas mas comunes incluyen:

1. **Pipes (tuberias)**: Son mecanismos de comunicacion que permiten que un proceso escriba datos en una tuberia y otro proceso los lea desde la misma tuberia.
2. **Memoria compartida**: Permite que los procesos compartan una region de memoria comun, donde pueden leer y escribir datos de manera eficiente.
3. **Sockets**: Los sockets permiten la comunicacion entre procesos, tanto dentro de la misma maquina como entre diferentes maquinas a traves de una red.
4. **Senales**: Los procesos pueden enviarse senales entre si para notificar eventos o iniciar acciones especificas, como la interrupcion de la ejecucion de un proceso.

## Que pasa con la PCB cuando se crea un proceso hijo y que es la PCB?

La **PCB** (Process Control Block) es una estructura de datos utilizada por el sistema operativo para almacenar informacion critica sobre un proceso. Cada proceso tiene una PCB que contiene:

```plaintext
+---------------------------------------------------------------------------------+
|                 Bloque de Control de Proceso (BCP)                              |
+---------------------------------------------------------------------------------+
| ID de Proceso (PID)                 | <pid_unico>                               |
| Estado del Proceso                  | <nuevo/listo/ejecutando/bloqueado>        |
| Contador de Programa (PC)           | <direccion_siguiente_instruccion>         |
| Registros de la CPU                 | <valores_de_registros_cpu>                |
| Información de Gestión de Memoria   | <registro_base, registro_limite>          |
| Información de Estado de I/O        | <cola_dispositivos, asignacion_recursos>  |
| Prioridad del Proceso               | <valor_prioridad>                         |
| Información de Planificación de CPU | <tiempo_corte, info_planificacion>        |
| Información de Contabilidad         | <tiempo_cpu_usado, tiempo_proceso>        |
+---------------------------------------------------------------------------------+
```

- PID del proceso.
- Estado del proceso (ejecutando, esperando, detenido).
- Contadores de programa y registros.
- Informacion sobre la memoria utilizada.
- Punteros a estructuras de datos necesarias para la gestion del proceso.

Cuando se crea un proceso hijo utilizando una llamada como `fork()`, el sistema operativo realiza una copia de la PCB del proceso padre, creando una nueva PCB para el proceso hijo. El proceso hijo hereda muchos atributos del proceso padre, pero ambos procesos tienen su propia PCB y contexto de ejecucion.

## Que es la system call `fork()`?

La **system call `fork()`** es una llamada al sistema que se utiliza para crear un nuevo proceso hijo. Cuando un proceso invoca `fork()`, se crea un proceso hijo que comienza a ejecutarse en paralelo con el proceso padre.

### Comportamiento de `fork()`:

- **En el proceso padre**: La llamada a `fork()` devuelve el **PID** del proceso hijo.
- **En el proceso hijo**: La llamada a `fork()` devuelve **0**.

Ambos procesos continúan ejecutandose despues de la llamada a `fork()`, pero con sus propios contextos y ejecuciones concurrentes.

## Planificacion de los procesos por parte del sistema operativo

El **sistema operativo** se encarga de gestionar la ejecucion de los procesos, incluidas las tareas de planificacion y asignacion de tiempo de CPU a cada proceso. La **planificacion de procesos** es el mecanismo utilizado por el sistema operativo para determinar que procesos deben ejecutarse y en que orden.

- **Planificacion preemptiva**: En sistemas multitarea, el sistema operativo puede interrumpir un proceso en ejecucion para darle tiempo de CPU a otro proceso. Esto asegura que todos los procesos, incluidos los procesos hijos, reciban atencion.
- **Planificacion no preemptiva**: En sistemas no preemptivos, un proceso debe liberar el control de la CPU antes de que otro proceso pueda ejecutarse. En este caso, los procesos pueden ejecutarse por un tiempo indefinido hasta que terminen su tarea o sean suspendidos.

El sistema operativo utiliza diferentes algoritmos de planificacion (como Round Robin, Prioridades, FIFO, etc.) para gestionar la ejecucion de los procesos de manera eficiente.

## Comportamiento en sistemas multinucleo y mononucleo

El comportamiento de los procesos hijos puede variar dependiendo de si el sistema operativo esta corriendo en un **procesador multinucleo** o **mononucleo**.

### En un sistema **mononucleo**:
- **Solo un proceso a la vez** puede ejecutarse en el CPU fisico, incluso si hay multiples procesos hijos. El sistema operativo utiliza un mecanismo de **multitarea** para cambiar entre los procesos, dándole a cada uno una fraccion de tiempo en la CPU. 
- La concurrencia es simulada mediante la rapida conmutacion de contexto entre los procesos padre e hijo.

### En un sistema **multinucleo**:
- El sistema operativo puede asignar diferentes nucleos del procesador a diferentes procesos, lo que permite que los procesos padre e hijo **ejecuten en paralelo** en diferentes nucleos. Esto mejora el rendimiento de las aplicaciones concurrentes.
- Sin embargo, el sistema operativo sigue gestionando la ejecucion de los procesos y asegurando que se respeten las reglas de concurrencia, como el manejo adecuado de los recursos compartidos.

# Libreria: `#include <unistd.h>`
La libreria `unistd.h` proporciona acceso a funciones y constantes del sistema operativo Unix y sistemas basados en Unix. Algunas de sus funciones mas utilizadas son:

- **Lectura y escritura de archivos**: `read()`, `write()`
- **Gestion de procesos**: `fork()`, `exec()`, `getpid()`
- **Control de dispositivos**: `open()`, `close()`
- **Manipulacion de directorios**: `chdir()`, `getcwd()`
- **Uso de identificadores de usuario y grupo**: `getuid()`, `getgid()`

## Funciones de Gestion de Procesos

### `int pid = fork();`
La funcion `fork()` se utiliza para crear un nuevo proceso, denominado "proceso hijo", a partir del proceso que realiza la llamada, denominado "proceso padre".

#### Valor de Retorno:
- **En el proceso padre**: Devuelve el **PID** del proceso hijo. Esto permite al proceso padre identificar y gestionar el proceso hijo.
- **En el proceso hijo**: Devuelve **0**, indicando que es el proceso hijo.
- **En caso de error**: Devuelve **-1** si ocurre un error al intentar crear el proceso (por ejemplo, si se alcanza el limite maximo de procesos).

### `getpid();`
La funcion `getpid()` devuelve el identificador del proceso que esta ejecutando la llamada.

#### Retorno:
- Devuelve un valor de tipo `pid_t`, que es un numero entero unico asignado al proceso actual.
- Se utiliza para obtener el PID del proceso en ejecucion, lo cual es util para la depuracion o para manejar logica que dependa de dicho identificador.

### `getppid();`
La funcion `getppid()` devuelve el identificador del proceso padre del proceso actual.

#### Retorno:
- Devuelve el **PID** del proceso padre, lo cual es util cuando un proceso hijo necesita conocer quien lo creo, por ejemplo, para gestionar registros o realizar operaciones de depuracion.

## Funciones de Terminacion y Control de Procesos

### `exit(0);`
La funcion `exit(0)` termina el proceso actual de manera inmediata.

#### Codigo de Salida:
- **0**: Indica que el proceso ha terminado con exito.
- **Cualquier valor distinto de 0**: Indica que el proceso termino debido a un error o una condicion excepcional, lo que permite al sistema operativo o a otros procesos conocer el resultado de la ejecucion.

### `exit(EXIT_FAILURE);`
Llama a `exit()` con el codigo de salida `EXIT_FAILURE`, lo que indica que el proceso ha fallado.

### `perror("Error al crear el proceso H1");`
La funcion `perror()` imprime un mensaje de error en la salida estandar que describe por que una operacion fallo, utilizando la variable global `errno` para obtener detalles del error.

## Ejecucion de Comandos del Sistema

### `system("./script.sh");`
La funcion `system()` se utiliza para ejecutar un comando del sistema operativo desde un programa en C.

#### Comportamiento:
- Crea un nuevo proceso para ejecutar el comando especificado en el shell del sistema operativo (por ejemplo, Bash).
- **Retorno**: Devuelve un valor entero:
  - Si el comando se ejecuta correctamente, devuelve el codigo de salida del shell.
  - Si ocurre un error (por ejemplo, si el comando no existe), devuelve un valor negativo.
- **Bloqueo**: La funcion `system()` bloquea la ejecucion del programa original hasta que el comando haya terminado de ejecutarse.

## Reemplazo de Proceso

### `execl("/bin/ls", "ls", NULL);`
La funcion `execl()` reemplaza el proceso actual con un nuevo programa. En este caso, ejecuta el comando `ls` para listar el contenido de un directorio.

#### Argumentos:
- **path**: La ruta completa del programa que deseas ejecutar (por ejemplo, "/bin/ls").
- **arg0**: El primer argumento que se pasa al programa ejecutado (usualmente, el nombre del propio ejecutable).
- **...**: Puedes pasar otros argumentos adicionales que el programa pueda necesitar, separados por comas.
- **NULL**: La lista de argumentos debe terminar con `NULL`.

#### Comportamiento:
- **Reemplazo de proceso**: El proceso original se reemplaza completamente por el nuevo proceso que se esta ejecutando.
- Si `execl()` se ejecuta correctamente, **no retorna** al proceso original. Si hay un error, devuelve **-1** y se puede utilizar `errno` para obtener detalles del fallo.

## Espera de un Proceso Hijo

### `wait(NULL);`
La funcion `wait()` permite que un proceso padre espere a que uno de sus procesos hijos termine su ejecucion.

#### Comportamiento:
- **Argumentos**: Si se pasa un puntero a un entero, se almacenara el estado de finalizacion del proceso hijo. Si se pasa `NULL`, se ignora el estado.
- **Espera**: El proceso padre se bloquea y espera hasta que uno de sus procesos hijos termine.
- **Retorno**: Devuelve el PID del proceso hijo que termino. Si no hay mas hijos que esperar, devuelve **-1** y establece `errno` a `ECHILD`.
  
#### Uso del Estado:
- Si se proporciona un puntero `status`, puede usarse para determinar si el proceso hijo termino correctamente o si hubo algun error.

#### Consideraciones:
- **Bloqueo**: `wait()` bloquea al proceso padre hasta que el hijo termine. Esto es util cuando el padre necesita esperar resultados de su hijo o asegurar que el hijo haya completado su tarea.
- **Multiples Hijos**: Si el proceso tiene varios hijos, puede llamar a `wait()` en un bucle o usar `waitpid()` con los PIDs de los hijos.

# Tipos de creacion de procesos hijos

## 1. Creacion Lineal de Procesos Hijos

### Descripcion
La creacion lineal de procesos hijos implica que cada proceso padre crea un solo proceso hijo en una secuencia ordenada. Es decir, el proceso padre crea un hijo, espera (o no) que el hijo termine y luego procede a crear otro hijo. Este proceso se repite de manera secuencial.

### Caracteristicas:
- **Secuencial**: Los procesos se crean uno por uno en un orden determinado.
- **Control del padre**: El proceso padre tiene control sobre cuando y cuantos hijos se crean.
- **Ideal para**: Situaciones donde se necesita un control estricto sobre la creacion y ejecucion de los procesos hijos.

## 2. Creacion Exponencial de Procesos Hijos

### Descripcion
En la creacion exponencial de procesos hijos, cada proceso creado (ya sea un proceso padre o hijo) crea multiples procesos hijos, lo que provoca un crecimiento exponencial en el numero de procesos. Este enfoque es util cuando se necesitan crear una gran cantidad de procesos rapidamente.

### Caracteristicas:
- **Crecimiento rapido**: La cantidad de procesos crece exponencialmente, lo que puede generar muchos procesos en poco tiempo.
- **Menos control**: El padre no tiene un control preciso sobre la cantidad exacta de procesos que se crean debido al comportamiento exponencial.
- **Ideal para**: Escenarios que requieren crear muchos procesos en poco tiempo, como en tareas paralelizadas a gran escala.

## 3. Creacion en Arbol (Jerarquica)

### Descripcion
En la creacion en arbol de procesos, cada proceso padre crea multiples procesos hijos, pero estos hijos tambien pueden crear mas procesos, resultando en una estructura jerarquica. Es decir, los procesos se organizan en niveles, donde un proceso padre puede generar varios procesos hijos que a su vez generan mas hijos.

### Caracteristicas:
- **Estructura jerarquica**: Los procesos siguen una organizacion en niveles, creando una estructura tipo arbol.
- **Escalable**: El numero de procesos puede crecer de manera controlada, permitiendo una mejor gestion.
- **Ideal para**: Situaciones en las que los procesos deben organizarse de manera jerarquica y gestionarse de manera eficiente.

## 4. Creacion en Paralelo (Sincronizacion Opcional)

### Descripcion
En la creacion en paralelo, multiples procesos son creados simultaneamente, sin necesidad de que el proceso padre espere que los hijos terminen antes de crear mas procesos. Este enfoque permite la ejecucion de tareas en paralelo, optimizando el tiempo de ejecucion.

### Caracteristicas:
- **Ejecucion simultanea**: Los procesos hijos se ejecutan de manera paralela.
- **Sincronizacion opcional**: No se requiere que el padre espere la finalizacion de los hijos antes de crear mas.
- **Ideal para**: Tareas que se pueden ejecutar en paralelo sin necesidad de secuenciar los procesos.
