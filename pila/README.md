## ¿Qué es una pila?

Una **pila** es una estructura de datos que sigue el principio **LIFO (Last In, First Out)**, lo que significa que el último elemento en ser insertado es el primero en ser retirado. Esta característica hace que la pila sea útil en situaciones donde el orden de procesamiento debe ser inverso al de llegada.

## ¿Qué cosa modela de la vida real?

En la vida real, una pila puede modelar situaciones donde los elementos deben ser procesados en orden inverso al que llegaron. Algunos ejemplos incluyen:

- **Pilas de platos**: El último plato colocado es el primero en ser retirado.
- **Pilas de documentos**: El último documento agregado a una pila es el primero que debe ser procesado.
- **Deshacer en editores de texto**: Las acciones más recientes son las primeras en deshacerse.
- **Recursión**: El sistema de llamadas de una función maneja las funciones en una pila, de modo que las últimas llamadas realizadas son las primeras en finalizar.

## ¿Qué se necesita para implementar la pila?

Para implementar una pila, se necesitan las siguientes estructuras y punteros:

1. **Estructura de los nodos**:
   Cada nodo de la pila contiene un conjunto de datos que deseamos almacenar. Los nodos también deben tener un puntero al siguiente nodo, formando una lista enlazada. Esto permite la manipulación dinámica de la pila, agregando y eliminando elementos desde la parte superior.

2. **Estructura de la pila**:
   La pila en sí misma se representa mediante una estructura que tiene un puntero único (`tope`) que apunta al nodo superior. El `tope` facilita la inserción y eliminación de elementos sin necesidad de recorrer toda la estructura. Además, la pila puede mantener un contador que lleva el seguimiento de la cantidad de elementos que contiene.

3. **Puntero cabeza**:
   La pila se gestiona mediante un único puntero cabeza (`tope`). Este puntero siempre apunta al nodo superior de la pila, lo que permite realizar las operaciones de inserción (push) y eliminación (pop) de manera eficiente.

```plaintext

  +----------+
  |  NODO 3  |  <----- Top (Puntero a la pila)
  |----------|
  | valor=2  |
  |----------|
  | siguiente|
  +----------+              
        |
        v
  +----------+
  |  NODO 2  |
  |----------|
  | valor=0  |
  |----------|     
  | siguiente|
  +----------+
        |                  
        v
  +----------+
  |  NODO 1  |
  |----------|
  | valor=7  |
  |----------|      
  | siguiente|
  +----------+
        |                  
        v
       NULL
```

## Operaciones típicas de una pila

Las operaciones más comunes realizadas sobre una pila incluyen:

1. **Push**: Insertar un nuevo elemento en la pila, colocándolo en la parte superior.
2. **Pop**: Eliminar el elemento superior de la pila. El siguiente elemento se convierte en el nuevo elemento superior.
3. **Peek**: Consultar el elemento superior sin eliminarlo, obteniendo el valor sin modificar la pila.
4. **Longitud**: Obtener el número de elementos almacenados en la pila.
5. **Vacia**: Verificar si la pila está vacía, lo cual es importante para evitar operaciones inválidas como pop o peek cuando no hay elementos.

## Tipos de pilas

Existen varios tipos de pilas que se pueden adaptar a diferentes necesidades y aplicaciones:

1. **Pila LIFO (Last In, First Out)**:
   Es la forma más común de pila, donde el último elemento insertado es el primero en ser retirado. Es ampliamente utilizada en algoritmos y estructuras que requieren acceso inverso a los elementos.

2. **Pila Circular**:
   En una pila circular, cuando se alcanza el final de la estructura, el espacio libre se reutiliza en la parte inicial, creando un ciclo. Esto es útil para optimizar el uso del espacio en sistemas con recursos limitados.

3. **Pila Múltiple**:
   Este tipo de pila maneja varias pilas independientes dentro de una misma estructura. Es útil cuando se necesita gestionar diferentes conjuntos de datos de forma aislada pero bajo un mismo sistema.

4. **Pila de Prioridad**:
   Aunque no sigue estrictamente el principio LIFO, las pilas de prioridad gestionan los elementos según su prioridad en lugar del orden de llegada. Esto es útil cuando los elementos deben ser procesados con un orden de prioridad específico.

5. **Pila Reversible**:
   Una pila reversible permite invertir el orden de los elementos de manera eficiente, permitiendo acceder a los elementos en orden inverso de inserción sin alterar la estructura fundamental.

## Comparación entre los tipos de pilas

| Tipo de Pila         | Propósito                                                         | Orden de Procesamiento             | Reutilización de Espacio | Prioridad en el Procesamiento | Ejemplos de Uso                     |
|----------------------|-------------------------------------------------------------------|------------------------------------|--------------------------|------------------------------|--------------------------------------|
| **Pila LIFO**         | Proceso de elementos en el orden inverso de inserción             | Último en entrar, primero en salir | No                       | No                           | Deshacer en editores, recursión     |
| **Pila Circular**     | Optimización de espacio reutilizando memoria                      | Último en entrar, primero en salir | Sí                       | No                           | Buffers, sistemas con memoria limitada|
| **Pila Múltiple**     | Gestión de varias pilas independientes dentro de una estructura  | Depende de la pila individual      | No                       | No                           | Manejo de diferentes tipos de datos  |
| **Pila de Prioridad** | Gestionar elementos con prioridad (no necesariamente LIFO)       | Según la prioridad de los elementos| No                       | Sí                           | Planificación de tareas, colas de prioridad |
| **Pila Reversible**   | Acceso eficiente a elementos en orden inverso                     | Depende de la operación de inversión| No                       | No                           | Inversión de datos, almacenamiento temporal |
