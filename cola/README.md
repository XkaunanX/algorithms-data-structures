# Cola

## ¿Que es una Cola?

Una **cola** es una estructura de datos que sigue el principio de "Primero en entrar, primero en salir" (FIFO, por sus siglas en ingles: **First In, First Out**). Es una estructura lineal donde los elementos se agregan por un extremo (final) y se eliminan por otro (frente). Las colas se utilizan en situaciones donde el orden de procesamiento debe ser respetado.

## ¿Que cosa modela de la vida real?

Una cola modela situaciones en la vida real donde los elementos deben esperar su turno en una fila. Algunos ejemplos incluyen:

- **Notificaciones** que deben ser procesadas en el orden en que llegan.
- **Cola de impresión**, donde los documentos se imprimen en el orden en que son enviados a la impresora.
- **Cola de procesos** en un sistema operativo, donde los procesos se ejecutan en el orden en que se solicitan.

## ¿Que se necesita para implementar una cola?

Para implementar una cola, se requieren dos componentes principales:

- **Nodo**: Cada nodo almacena los datos y un puntero al siguiente nodo en la cola.
- **Cola**: La cola mantiene un puntero a la cabeza (frente) y a la cola (final), ademas de la longitud de la cola.

```plaintext
+------------+     +------------+     +------------+
|  NODO A    |     |  NODO B    |     |  NODO C    |
|------------|     |------------|     |------------|
|   dato     |     |   dato     |     |   dato     |
|------------|     |------------|     |------------|
| siguiente  |---->| siguiente  |---->| siguiente  |----> NULL
+------------+     +------------+     +------------+
       |                                    |
  puntero (head)                        puntero (tail)
```

## Operaciones tipicas de una cola

Las operaciones básicas de una cola son:

1. **Encolar**: Agregar un elemento al final de la cola.
2. **Desencolar**: Eliminar el elemento en el frente de la cola.
3. **Consultar frente**: Ver el primer elemento de la cola sin eliminarlo.
4. **Consultar longitud**: Obtener el numero de elementos en la cola.

## Tipos de colas

Existen diferentes tipos de colas que varían en el modo en que los elementos se gestionan. A continuación, se presenta una tabla de comparación:

| Tipo de Cola         | Proposito                                                         | Orden de Procesamiento             | Reutilizacion de Espacio | Prioridad en el Procesamiento | Ejemplos de Uso                     |
|----------------------|-------------------------------------------------------------------|------------------------------------|--------------------------|------------------------------|--------------------------------------|
| **Cola FIFO**         | Proceso de elementos en el orden en que entran                    | Primero en entrar, primero en salir | No                       | No                           | Notificaciones, correos electronicos, carrito de compras |
| **Cola Circular**     | Optimizacion de espacio reutilizando memoria                      | Primero en entrar, primero en salir | Si                       | No                           | Buffers, sistemas con memoria limitada |
| **Cola Multiple**     | Gestion de varias colas independientes dentro de una estructura  | Depende de la cola individual      | No                       | No                           | Manejo de diferentes tipos de datos |
| **Cola de Prioridad** | Gestion de elementos con prioridad (no necesariamente FIFO)      | Segun la prioridad de los elementos| No                       | Si                           | Planificacion de tareas, colas de prioridad |
