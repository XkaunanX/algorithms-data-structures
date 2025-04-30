# C

El lenguaje C es un lenguaje de programacion de bajo nivel con capacidades de alto nivel, ampliamente utilizado para el desarrollo de sistemas operativos, control de hardware, y aplicaciones de alto rendimiento. Disenado por Dennis Ritchie en los anos 70, C sigue siendo fundamental en la informatica moderna debido a su eficiencia, flexibilidad y control detallado sobre los recursos del sistema.

## Caracteristicas Principales

### 1. Lenguaje de Bajo Nivel
C proporciona acceso directo al hardware, permitiendo operaciones a nivel de bits y manipulacion de registros de memoria. Esto lo convierte en una opcion ideal para programacion de sistemas y desarrollo de controladores. 

**Ejemplo:**  
En C, puedes manipular directamente los valores de memoria usando punteros, lo que te da un control preciso sobre la memoria del sistema. Un ejemplo simple es el uso de punteros para acceder y modificar el contenido de una variable de memoria específica:

```c
int x = 10;
int *ptr = &x;
*ptr = 20;  // Cambia el valor de 'x' a 20
```
Este tipo de manipulacion de memoria es caracteristico de un lenguaje de bajo nivel, ya que permite al programador trabajar directamente con direcciones de memoria y registros.

### 2. Ausencia de Recoleccion de Basura
A diferencia de muchos lenguajes modernos, C no incluye un recolector de basura. Esto brinda a los desarrolladores control total sobre la asignacion y liberacion de memoria, pero tambien requiere una gestion manual cuidadosa para evitar fugas de memoria y errores.

**Ejemplo:**

En C, cuando se utiliza memoria dinámica con `malloc` o `calloc`, es responsabilidad del programador liberar esa memoria con `free` cuando ya no se necesite. Si no se libera, la memoria seguirá reservada y generará una fuga de memoria.

```c
#include <stdlib.h>

int main() {
    int *ptr = (int*) malloc(sizeof(int));  // Asignacion de memoria dinamica
    *ptr = 10;  // Uso de la memoria asignada
    
    free(ptr);  // Liberar la memoria al final
    return 0;
}
```
Si olvidas llamar a `free`, el sistema no liberará esa memoria, lo que puede causar un consumo innecesario de recursos durante la ejecución del programa.

### 3. Uso de Punteros

C destaca por su potente manejo de punteros, permitiendo:
- Acceso directo a direcciones de memoria.
- Manipulación de estructuras complejas.
- Creación y navegación de estructuras de datos dinámicas como listas enlazadas, árboles y grafos.

**Ejemplo:**

El siguiente ejemplo muestra cómo se puede usar punteros para modificar directamente el valor de una variable desde dentro de una función, así como la manipulación de memoria dinámica usando `malloc` y `free` para gestionar dinámicamente un bloque de memoria:

```c
#include <stdio.h>
#include <stdlib.h>

// Función que modifica el valor de una variable usando punteros
void modificarValor(int *ptr) {
    *ptr = 50;  // Modifica el valor al que apunta el puntero
}

// Función que usa punteros para manejar memoria dinámica
void manejarMemoriaDinamica() {
    int *ptr = (int*) malloc(sizeof(int));  // Asignación dinamica de memoria

    if (ptr == NULL) {
        printf("Error al asignar memoria\n");
        return;
    }

    *ptr = 100;  // Asignar un valor a la memoria dinamica
    printf("Valor almacenado en memoria dinamica: %d\n", *ptr);

    free(ptr);  // Liberar la memoria dinamica
}

int main() {
    int a = 10;
    printf("Valor antes de modificar: %d\n", a);

    // Llamada a la funcion que modifica el valor de la variable
    modificarValor(&a);

    printf("Valor despues de modificar: %d\n", a);

    // Llamada a la funcion que maneja memoria dinamica
    manejarMemoriaDinamica();

    return 0;
}
```

### 4. Paradigma Procedimental e Imperativo
C adopta un paradigma de programacion estructurada o procedimental. Esto implica:
- Uso de funciones para dividir el codigo en modulos.
- Fomenta la reutilizacion y la legibilidad.
- Es un lenguaje de paradigma imperativo, lo que significa que el programador da instrucciones secuenciales al sistema para que ejecute una serie de operaciones.

**Ejemplo:**

```c
#include <stdio.h>

void saludo() {
    printf("Hola, mundo!\n");
}

int main() {
    saludo();  // Llamada a la funcion saludo
    return 0;
}
```

### 5. Portabilidad
El codigo en C puede compilarse en una amplia variedad de plataformas con cambios minimos o nulos. Esto lo convierte en una opcion comun para el desarrollo multiplataforma.

### 6. Bibliotecas Estandar
C cuenta con una rica biblioteca estandar que incluye:

- `<stdio.h>`: Manejo de entrada/salida.
- `<stdlib.h>`: Manejo de memoria dinamica y utilidades varias (como `malloc`, `free`, `calloc`, `realloc`).
- `<math.h>`: Funciones matematicas (como `sin`, `cos`, `sqrt`).
- `<string.h>`: Manipulacion de cadenas de caracteres (como `strcpy`, `strlen`, `strcat`).

### 7. Tipado Estático
C es un lenguaje con tipado estático, lo que significa que los tipos de las variables deben ser definidos en tiempo de compilación y no pueden cambiar durante la ejecución. Esto permite una mayor eficiencia en la compilación y ejecución, pero requiere que los desarrolladores definan claramente las variables y sus tipos.

**Ejemplo:**

```c
#include <stdio.h>

int main() {
    int numero = 10;  // Tipo definido como entero
    numero = "Texto"; // Error: no se puede asignar un string a una variable de tipo entero
    printf("%d\n", numero);
    return 0;
}
```

### 8. Compilado
C es un lenguaje compilado, lo que significa que el código fuente es transformado en código de máquina antes de ser ejecutado. Este proceso se realiza mediante un compilador que traduce el código a un archivo ejecutable.

El compilador más comúnmente utilizado para C es **gcc** (GNU Compiler Collection). A través de este compilador, el código fuente se puede convertir en un archivo ejecutable que puede ser ejecutado directamente en el sistema operativo.

**Ejemplo de comando en Bash para compilar un archivo `test.c`:**

```bash
gcc test.c -o test
```

### 9. Sintaxis y Declaracion de Funciones
En C, las funciones son declaradas especificando su tipo de retorno y los parámetros. La sintaxis es sencilla pero rigurosa. Las funciones deben ser declaradas antes de ser utilizadas o bien definidas en archivos de cabecera (`.h`).

Una declaración de función en C típicamente tiene la siguiente forma:

```c
tipo_de_retorno nombre_de_funcion(tipo_de_parametro parametro1, tipo_de_parametro parametro2);
```
Ejemplo:

```c
int suma(int a, int b) {
    return a + b;
}
```

### 10. Palabras Claves
Algunas de las principales palabras clave en C son:
- `if`, `else`, `for`, `while`, `switch` (estructuras de control)
- `return`, `break`, `continue` (control de flujo)
- `void`, `struct`, `enum`, `typedef` (declaracion de tipos y estructuras)
- `sizeof`, `static`, `extern`, `const` (modificadores y operadores)
- **Manejo de Memoria:**
  - `malloc`, `free`, `calloc`, `realloc` (asignacion y liberacion de memoria dinamica)
  
### 11. Operadores
C soporta una amplia gama de operadores, incluyendo:
- `*`, `&` (operadores de punteros)
- `%` (operador de modulo)
- `+`, `-`, `*`, `/`, `=` (operadores aritmeticos y de asignacion)
- `==`, `!=`, `>`, `<`, `>=`, `<=` (operadores de comparacion)
- `&&`, `||` (operadores logicos)

### 12. Especificadores de Formato
Los especificadores de formato se usan para mostrar variables en la salida estandar. Algunos de los mas comunes son:
- `%d` para enteros.
- `%p` para punteros.
- `%s` para cadenas de caracteres.
- `%f` para numeros flotantes.

## Comparativa con otros lenguajes

| Caracteristica             | C             | Python       | Java        |
|----------------------------|---------------|--------------|-------------|
| Tipado                     | Estatico      | Dinamico     | Estatico    |
| Compilado/Interpretado      | Compilado     | Interpretado | Compilado   |
| Punteros                   | Si            | No           | No          |
| Paradigma                  | Procedimental | Multiparadigma| Orientado a objetos|
| Recoleccion de Basura      | No            | Si           | Si          |
| Sintaxis                   | Rigida        | Flexible     | Moderada    |
| Bibliotecas Estandar       | Si            | Si           | Si          |

