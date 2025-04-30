# Arreglos

## ¿Qué es un Arreglo?

Un arreglo es una estructura de datos que almacena una coleccion de elementos del mismo tipo. Los elementos estan ubicados de manera contigua en memoria y se pueden acceder de forma eficiente mediante un indice. 

## ¿Qué modelo de la vida real?

Un arreglo puede modelar situaciones como una lista de tareas, donde cada tarea es representada por un elemento y cada una tiene un indice que la identifica. De esta manera, se puede acceder a cualquier tarea rapidamente utilizando su indice.

## ¿Qué se necesita para implementar un arreglo?

Para implementar un arreglo se necesita un puntero inicial, que señala el primer elemento del arreglo en memoria, y un tamaño que indica cuántos elementos puede contener. Dependiendo del tipo de arreglo, los elementos pueden ser de tipos simples como enteros o complejos como estructuras.

```plaintext
Indice:  0    1    2    3    4    5
        +----+----+----+----+----+----+
Valores:| 4  |  1 |  9 | 3  | 8  | 2  |
        +----+----+----+----+----+----+
          ^
          |
    Puntero inicial
```
```c
#include <stdio.h>

int main() {
    int vector[] = {4, 1, 9, 3, 8, 2}; // El tamaño de un entero es 1B
    
    // Imprimir el contenido del vector
    for(int i = 0; i < 6; i++) {
        printf("Valor en el índice %d: %d\n", i, vector[i]);
    }

    return 0;
}
```

## Operaciones típicas de un arreglo

- **Acceso a un elemento**: Acceder a un elemento usando su indice.
- **Inserción**: Agregar un nuevo elemento al arreglo.
- **Eliminación**: Quitar un elemento del arreglo.
- **Modificación**: Cambiar el valor de un elemento existente.
- **Búsqueda**: Localizar un elemento dentro del arreglo.
- **Ordenamiento**: Organizar los elementos en un cierto orden.

## Tipos de Arreglos

- **Arreglo unidimensional**: Una sola lista de elementos, accesibles mediante un solo indice.
- **Arreglo bidimensional**: Un arreglo de arreglos, similar a una matriz.
- **Arreglo tridimensional**: Un arreglo de matrices, puede verse como una caja de elementos organizados en filas, columnas y capas.

## Representación de Vectores, Matrices y Tensores en Memoria

- **Vectores**: Los vectores son representados por una secuencia de elementos contiguos en memoria. El acceso a los elementos se realiza mediante un indice único.
- **Matrices**: Una matriz es un arreglo bidimensional, representado como un arreglo de arreglos. Se puede representar en memoria de forma lineal o en forma de punteros a punteros.
- **Tensores**: Un tensor es un arreglo multidimensional que puede tener más de dos dimensiones. Su representación en memoria es similar a la de las matrices, pero con más dimensiones de punteros anidados.

## ¿Por qué los arreglos son homogeneos?

Todos los elementos de un arreglo deben ser del mismo tipo de dato porque la memoria se reserva de manera continua y uniforme para esos elementos. Esto permite el acceso eficiente y directo a cualquier elemento, pero limita la flexibilidad a la hora de almacenar diferentes tipos de datos.

## Tipos de Ordenamiento

- **Bubble Sort**: Compara elementos adyacentes y los intercambia si están en el orden incorrecto.
- **Selection Sort**: Encuentra el elemento más pequeño y lo coloca en la primera posición, luego repite para el resto del arreglo.
- **Insertion Sort**: Inserta los elementos en la posición correcta dentro de un subarreglo ya ordenado.
- **Quick Sort**: Utiliza un pivote para dividir el arreglo en dos partes y ordenarlas recursivamente.
- **Merge Sort**: Divide el arreglo en dos mitades, las ordena recursivamente y luego las fusiona.
- **Heap Sort**: Convierte el arreglo en un heap y luego ordena los elementos extrayendo el mayor.
- **Shell Sort**: Realiza una ordenación por inserción, pero con un intervalo variable entre los elementos.
- **Cocktail Sort**: Una variante del Bubble Sort que recorre el arreglo en ambas direcciones.
- **Bidirectional Bubble Sort**: Similar al Cocktail Sort, pero utilizando el Bubble Sort en ambas direcciones.
- **Adaptive Selection Sort**: Selección adaptativa que mejora la eficiencia al detectar ya elementos ordenados.

## Comparación entre Arreglo y Otras Estructuras de Datos

| Estructura de Datos         | Propósito                                  | Acceso a Elementos  | Eficiencia en Inserción | Eficiencia en Eliminación | Ejemplos de Uso                   |
|----------------------------|--------------------------------------------|---------------------|------------------------|--------------------------|----------------------------------|
| **Arreglo**                | Almacenar elementos de un mismo tipo       | Directo por indice  | Baja (requiere desplazamiento) | Baja (requiere desplazamiento) | Listas estáticas, matrices      |
| **Lista Enlazada**         | Almacenar elementos de manera dinámica    | Secuencial (por punteros) | Alta (sin desplazamiento) | Alta (sin desplazamiento) | Manejo de colas, estructuras dinámicas |
| **Pila**                   | Almacenar elementos de manera LIFO        | Último en entrar, primero en salir | Baja (al final)         | Baja (al final)            | Deshacer acciones, recursión    |
| **Cola**                   | Almacenar elementos en orden FIFO         | Primero en entrar, primero en salir | Baja (al final)         | Baja (al principio)         | Procesamiento de tareas, colas de impresión |
| **Grafo**                  | Relacionar elementos de manera flexible   | No lineal            | Variable (depende de implementación) | Variable (depende de implementación) | Redes sociales, rutas de navegación |
