# Grafos

## ¿Que es un grafo?

Un **grafo** es una estructura de datos que se compone de un conjunto de nodos (tambien llamados vertices) y un conjunto de aristas (o enlaces) que conectan a estos nodos. Los grafos pueden ser utilizados para modelar una amplia variedad de situaciones, desde redes de comunicacion hasta rutas en mapas.

### Componentes de un grafo:
- **Nodos (Vertices)**: Elementos que representan entidades dentro del grafo.
- **Aristas (Enlaces)**: Conexiones entre dos nodos, pueden ser dirigidas (unidireccionales) o no dirigidas (bidireccionales).

```plaintext
    A
   / \
  B   C
   \ /
    D
```

## ¿Que cosa modela de la vida real?

Los grafos son utilizados para modelar muchas situaciones del mundo real, tales como:

- **Redes de computadoras**: Donde cada nodo representa un dispositivo (como una computadora o router) y cada arista representa una conexion entre dispositivos.
- **Redes sociales**: Los usuarios son nodos y las relaciones entre ellos (amigos, seguidores) son aristas.
- **Rutas de transporte**: En mapas, las ciudades son nodos y las carreteras o rutas de transporte son aristas.
- **Sistemas de navegacion**: Para modelar el camino entre puntos en un sistema de coordenadas.
- **Redes electricas**: Los nodos son generadores, transformadores o estaciones, y las aristas representan las conexiones entre ellos.
  
## ¿Que se necesita para implementar un grafo?

Para implementar un grafo en C, se requieren las siguientes estructuras:

### Estructuras y punteros:

1. **Nodo del grafo**: Cada nodo almacena informacion sobre el dato y tiene un puntero a los nodos adyacentes.
2. **Arista**: Representa una conexion entre nodos, tiene un puntero al siguiente nodo en la lista de adyacencia.
3. **Grafo**: Contiene el puntero a la cabeza de la lista de nodos y la cantidad total de nodos.

El uso de **punteros** en la implementacion del grafo es crucial para gestionar de manera dinamica las conexiones entre nodos y aristas. Los punteros permiten:

- **Conectar nodos**: En lugar de usar indices fijos o arrays, cada nodo contiene un puntero al siguiente nodo en la lista de nodos. Esto hace que los grafos sean dinamicos, ya que pueden crecer o reducir su tamaño de manera eficiente sin necesidad de reestructurar toda la memoria.
- **Gestionar las aristas**: Las aristas tambien se gestionan mediante punteros. Cada nodo tiene un puntero a la lista de sus aristas adyacentes, lo que facilita la exploracion de los nodos conectados sin necesidad de tener una estructura fija para todas las posibles conexiones.
- **Dinamismo**: Los punteros permiten una administracion flexible de la memoria, lo que permite añadir o eliminar nodos y aristas sin requerir una estructura de datos fija como los arrays.

## Matriz de Adyacencia

La **matriz de adyacencia** es una estructura de datos que representa un grafo en una tabla bidimensional. Si el grafo tiene `n` nodos, la matriz tendra dimensiones `n x n`, donde cada elemento de la matriz indica si hay o no una arista entre los nodos correspondientes.

Ventajas:
- Facil de implementar.
- Eficiente para grafos densos.

Desventajas:
- Usa mucho espacio para grafos dispersos (cuando hay pocas conexiones entre nodos).

```plaintext
      Nodo1   Nodo2   Nodo3   Nodo4
Nodo1    0       1       1       0
Nodo2    1       0       0       1
Nodo3    1       0       0       1
Nodo4    0       1       1       0
```

## Lista de Adyacencia

La **lista de adyacencia** es una estructura mas eficiente en terminos de espacio para representar grafos dispersos. Consiste en un arreglo de listas enlazadas, donde cada nodo tiene una lista de aristas que lo conectan con otros nodos.

Ventajas:
- Mejor uso de memoria para grafos dispersos.
- Permite un acceso rapido a los nodos adyacentes.

Desventajas:
- Acceder a las conexiones entre todos los nodos puede ser mas lento que con la matriz de adyacencia.

```plaintext
       +------------------+         +------------------+
       |  NODO A          |         |  NODO B          |
       |------------------|         |------------------|
       |   dato           |         |   dato           |
       |------------------|         |------------------|
       | lista de aristas | ------> | lista de aristas |
       +------------------+         +------------------+
               |                            |
               v                            v
       +------------------+         +------------------+
       |  NODO C          |         |  NODO D          |
       |------------------|         |------------------|
       |   dato           |         |   dato           |
       |------------------|         |------------------|
       | lista de aristas | <------ | lista de aristas |
       +------------------+         +------------------+
```

## Comparacion entre Lista de Adyacencia y Matriz de Adyacencia

| Caracteristica                  | Matriz de Adyacencia                    | Lista de Adyacencia                |
|----------------------------------|-----------------------------------------|------------------------------------|
| **Espacio**                      | O(n²), usa mas memoria para grafos dispersos | O(n + e), mas eficiente en grafos dispersos |
| **Acceso a aristas**             | O(1), rapido para verificar existencia de una arista | O(d), donde `d` es el numero de nodos adyacentes |
| **Insercion de aristas**         | O(1), rapido para añadir aristas | O(1) o O(d) dependiendo de la implementacion |
| **Busqueda de adyacentes**       | O(n) para cada nodo                    | O(d) para cada nodo |
| **Eficiencia en grafos dispersos** | Baja eficiencia, desperdicia espacio  | Alta eficiencia, consume menos memoria |

## Operaciones tipicas de un grafo

Las operaciones mas comunes que se realizan en un grafo incluyen:

- **Insertar un nodo**: Anadir un nuevo nodo al grafo.
- **Eliminar un nodo**: Remover un nodo y todas sus aristas del grafo.
- **Insertar una arista**: Anadir una arista entre dos nodos.
- **Eliminar una arista**: Eliminar una arista entre dos nodos.
- **Consultar un nodo**: Buscar un nodo especifico en el grafo.
- **Recorrer el grafo**: Realizar un recorrido, como el de **BFS** (Busqueda en Anchura) o **DFS** (Busqueda en Profundidad), para visitar todos los nodos.
  
## Tipos de grafos

Los grafos pueden clasificarse en varios tipos, dependiendo de sus caracteristicas. Algunos de los tipos mas comunes incluyen:

- **Grafo no dirigido**: Las aristas no tienen direccion (el recorrido puede ir en ambas direcciones).
- **Grafo dirigido (DAG)**: Las aristas tienen direccion, solo se puede recorrer de un nodo a otro en la direccion especificada.
- **Grafo ponderado**: Cada arista tiene un peso (valor asociado).
- **Arbol**: Un grafo no dirigido, aciclico y conectado. Es un caso especial de grafo.
- **Arbol de expansion minima (MST)**: Un arbol con el peso total minimo de sus aristas.
- **Grafo bipartito**: Los nodos se pueden dividir en dos conjuntos disjuntos, con aristas solo entre nodos de diferentes conjuntos.
- **Grafo completo**: Cada par de nodos esta conectado por una arista.
- **Grafo k-DAG**: Un grafo dirigido aciclico con k dimensiones.

## Tipos de busquedas en grafos

Algunas de las busquedas mas comunes en grafos incluyen:

- **Busqueda en amplitud (BFS)**: Recorrido del grafo en niveles, comenzando por el nodo raiz y explorando sus nodos adyacentes antes de mover a los nodos siguientes.
  - **Uso tipico**: Encontrar el camino mas corto en un grafo no ponderado.
  
- **Busqueda en profundidad (DFS)**: Recorrido del grafo donde se explora lo mas profundo posible antes de retroceder y explorar otras ramas.
  - **Uso tipico**: Resolver problemas como el de encontrar ciclos en un grafo, recorrer todos los nodos.
  
- **Algoritmo de Dijkstra**: Encuentra el camino mas corto desde un nodo fuente hasta todos los demas nodos en un grafo ponderado.
  - **Uso tipico**: Redes de transporte o de comunicacion.
  
- **Algoritmo de Floyd-Warshall**: Encuentra el camino mas corto entre todos los pares de nodos en un grafo ponderado.
  - **Uso tipico**: Matrices de distancias en grafos densos.
  
- **Algoritmo de Bellman-Ford**: Similar a Dijkstra, pero puede manejar aristas con pesos negativos.
  - **Uso tipico**: Redes con aristas de costos negativos.
  
- **Algoritmo de Prim**: Encuentra el arbol de expansion minima en un grafo ponderado.
  - **Uso tipico**: Construccion de redes de conexion optima.
  
- **Algoritmo de Kruskal**: Otro algoritmo para encontrar el arbol de expansion minima, que usa una tecnica de unificar componentes conectados.
  - **Uso tipico**: Redes de telecomunicaciones.

## Tabla de comparacion entre tipos de grafos

| Tipo de grafo                 | Caracteristicas                                         | Ejemplos de uso                     |
|-------------------------------|---------------------------------------------------------|--------------------------------------|
| **Grafo no dirigido**          | Las aristas no tienen direccion.                       | Redes de amistad, rutas sin direccion |
| **Grafo dirigido (DAG)**       | Las aristas tienen direccion y no contienen ciclos.    | Sistemas de dependencias, programacion concurrente |
| **Grafo ponderado**            | Cada arista tiene un peso asociado.                     | Rutas de navegacion, redes electricas |
| **Arbol**                      | Grafo aciclico y conectado, con un solo nodo raiz.      | Jerarquias, estructura de archivos  |
| **Arbol de expansion minima**  | Arbol con el peso minimo total de las aristas.          | Redes de computadoras, optimizacion de rutas |
| **Grafo bipartito**            | Los nodos se dividen en dos conjuntos disjuntos.        | Reparticion de tareas, redes sociales |
| **Grafo completo**             | Cada par de nodos esta conectado por una arista.        | Redes completamente conectadas |
| **Grafo k-DAG**                | Grafo dirigido aciclico con k dimensiones.              | Modelado de dependencias multivariantes |

