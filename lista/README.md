# Lista Enlazada

## ¿Que es una lista?

Una **lista enlazada** es una estructura de datos compuesta por una secuencia de nodos, donde cada nodo contiene un dato y un puntero al siguiente nodo en la secuencia. A diferencia de los arreglos, las listas enlazadas no requieren un tamaño fijo ni contiguo en memoria, lo que les permite crecer y reducir su tamaño dinamicamente.

## ¿Que cosa modela de la vida real?

En la vida real, las listas enlazadas pueden modelar situaciones donde se requiere almacenar y procesar una secuencia de elementos de forma flexible. Algunos ejemplos incluyen:

- **Carrito de compras**: Los artículos en un carrito de compras en línea pueden ser modelados como nodos enlazados, donde cada producto es un nodo y no necesariamente deben estar ordenados. El carrito es un conjunto de productos, sin importar su orden de aparición.
  
- **Lista de contactos**: Un sistema de gestión de contactos podría tener una lista enlazada, donde cada contacto es un nodo, y no hay necesidad de ordenar los contactos. Cada nuevo contacto se enlaza al siguiente sin un criterio de orden.
  
- **Lista de eventos**: En una agenda de eventos, los eventos se pueden agregar de manera independiente a la lista. Los eventos no necesariamente siguen un orden de importancia o fecha, simplemente se agregan y se enlazan al siguiente evento.
  
- **Inventario de productos**: Un sistema de inventario que almacena productos de manera flexible, donde cada producto es un nodo, y el orden no es importante. Cada producto puede ser accedido o modificado independientemente de su ubicación en la lista.
  
## ¿Que se necesita para implementar la lista?

Para implementar una lista enlazada, se requieren las siguientes estructuras y punteros:

1. **Estructura de Nodo**:
   Cada nodo contiene:
   - **Dato**: El valor almacenado en el nodo (puede ser cualquier tipo de dato, como enteros, cadenas, etc.).
   - **Puntero al siguiente nodo**: Un puntero que apunta al siguiente nodo en la lista.

2. **Estructura de la Lista**:
   - **Cabeza (head)**: Un puntero que apunta al primer nodo de la lista.
   - **Final (tail)**: Un puntero que apunta al ultimo nodo de la lista (opcional, pero util en algunos casos para optimizar ciertas operaciones).
   - **Longitud**: Un contador que mantiene el numero de nodos en la lista para evitar la necesidad de recorrer la lista completamente en algunas operaciones.

```plaintext

                    +----------+     +----------+     +----------+
                    |  NODO 1  |     |  NODO 2  |     |  NODO 3  | 
                    |----------|     |----------|     |----------|
      Cabeza --->   |   dato   |     |   dato   |     |   dato   |
                    |----------|     |----------|     |----------|
                    | siguiente| --> | siguiente| --> | siguiente| --> NULL
                    +----------+     +----------+     +----------+

```

## Operaciones tipicas de una lista

Las operaciones mas comunes realizadas sobre una lista enlazada incluyen:

1. **Insertar nodo**: Agregar un nuevo nodo a la lista.
2. **Eliminar nodo**: Eliminar un nodo de la lista especificado por su ID.
3. **Modificar nodo**: Cambiar los valores almacenados en un nodo especifico.
4. **Consultar nodo**: Buscar un nodo en la lista por su ID.
5. **Imprimir lista**: Mostrar todos los elementos de la lista.
6. **Consultar longitud**: Obtener el numero de nodos en la lista.

## Tipos de listas

Existen varios tipos de listas enlazadas que se pueden adaptar a diferentes necesidades:

1. **Lista enlazada simple**:
   - Cada nodo contiene un puntero al siguiente nodo.
   - Operacion de insercion y eliminacion eficientes al principio de la lista.

2. **Lista enlazada doble**:
   - Cada nodo contiene dos punteros: uno al siguiente nodo y otro al nodo anterior.
   - Permite recorrer la lista en ambas direcciones, pero requiere mas memoria por nodo.

3. **Lista circular**:
   - El ultimo nodo de la lista apunta de nuevo al primer nodo, formando un ciclo.
   - Puede ser util en estructuras donde se requiere un recorrido continuo, como colas circulares.

4. **Lista circular doble**:
   - Es una combinacion de las listas dobles y circulares. El primer nodo apunta al ultimo nodo y viceversa.
   - Permite recorrer la lista de manera eficiente en ambas direcciones y de forma circular.

5. **Lista enlazada con insercion ordenada**:
   - Los nodos se insertan en un orden especifico (por ejemplo, numerico o alfabetico), manteniendo la lista siempre ordenada.
   - Es util cuando se necesitan realizar busquedas o accesos rapidos a elementos de forma ordenada.

6. **Lista de adyacencia**:
   - Se usa en la representacion de grafos, donde cada nodo de la lista representa un vertice y sus nodos adyacentes.
   - Utilizada en algoritmos de grafos como BFS y DFS.

7. **Lista de arrays**:
   - Cada nodo de la lista contiene un arreglo de elementos en lugar de un solo dato.
   - Ideal cuando se necesita almacenar varios elementos relacionados en un solo nodo.

8. **Lista de listas**:
   - Una lista cuyo contenido son otras listas, proporcionando una forma de organizar estructuras de datos complejas.
   - Util cuando se manejan colecciones jerarquicas de elementos.

9. **Lista de punteros**:
   - Cada nodo contiene un puntero a un objeto o estructura, en lugar de un valor directo.
   - Se usa en estructuras complejas donde los datos son dinamicos o polimorfos.

10. **Lista reversible**:
    - Se puede recorrer la lista en ambas direcciones mediante la inversion de los punteros.
    - Util en algoritmos que requieren recorrer la lista en orden inverso.

11. **Lista de prioridad**:
    - Los nodos tienen una prioridad asociada, y los elementos con mayor prioridad se procesan antes.
    - Utilizada en algoritmos como el de Dijkstra o para la gestion de tareas.

## Comparación de Tipos de Listas

| Tipo de Lista                 | Propósito                                                         | Orden de Acceso                 | Reutilización de Espacio | Prioridad en el Procesamiento | Ejemplos de Uso                            |
|-------------------------------|-------------------------------------------------------------------|---------------------------------|--------------------------|------------------------------|-------------------------------------------|
| **Lista Enlazada Simple**      | Almacenar una secuencia de elementos con un puntero al siguiente   | No tiene un orden fijo          | No                       | No                           | Recorridos secuenciales, almacenamiento de datos |
| **Lista Enlazada Doble**       | Almacenar una secuencia de elementos con punteros al siguiente y anterior | No tiene un orden fijo          | No                       | No                           | Navegación bidireccional, edición de textos |
| **Lista Circular**             | Optimizar el recorrido de la lista con un ciclo continuo           | No tiene un orden fijo          | Sí                       | No                           | Administración de buffers, recorridos continuos |
| **Lista Circular Doble**       | Permitir recorrido eficiente en ambas direcciones y de forma continua | No tiene un orden fijo          | Sí                       | No                           | Algoritmos de navegación, implementación de navegación circular |
| **Lista de Adyacencia**        | Representar grafos mediante nodos adyacentes                      | No tiene un orden fijo          | No                       | No                           | Representación de grafos, algoritmos de búsqueda |
| **Lista con Inserción Ordenada**| Mantener los elementos ordenados durante la inserción             | Depende de la inserción ordenada | No                       | Sí                           | Algoritmos de búsqueda binaria, inserción ordenada |
| **Lista de Arrays**            | Almacenar múltiples elementos en cada nodo                        | No tiene un orden fijo          | No                       | No                           | Almacenamiento de datos estructurados en nodos |
| **Lista de Punteros**          | Almacenar punteros a estructuras u objetos                        | No tiene un orden fijo          | No                       | No                           | Manejo de referencias a objetos, estructuras dinámicas |
| **Lista Reversible**           | Permitir recorrer la lista en orden inverso                       | No tiene un orden fijo          | No                       | No                           | Inversión de datos, almacenamiento temporal |
| **Lista de Prioridad**         | Gestionar elementos según su prioridad                            | Depende de la prioridad         | No                       | Sí                           | Planificación de tareas, colas de prioridad |
