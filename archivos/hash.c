#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define TABLE_SIZE 10  // Tamaño de la tabla hash

// Definimos una estructura para almacenar la informacion de una persona
typedef struct {
    int id;             // ID unico
    char nombre[50];    // Nombre de la persona
    int edad;           // Edad de la persona
} Persona;

// Definimos una estructura para las entradas de la tabla hash, que utiliza encadenamiento
typedef struct HashNode {
    Persona persona;        // Almacena la persona
    struct HashNode* next;  // Apunta al siguiente nodo (encadenamiento)
} HashNode;

// Definimos la tabla hash como un arreglo de punteros a HashNode
HashNode* hashTable[TABLE_SIZE];

// Funcion para calcular el hash SHA-256 de un valor (como un ID)
unsigned int sha256Hash(int id) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char str[50];
    
    // Convertimos el ID a una cadena
    snprintf(str, sizeof(str), "%d", id);

    // Calculamos el hash SHA-256
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, str, strlen(str));
    SHA256_Final(hash, &sha256_ctx);
    
    // Tomamos los primeros 4 bytes del hash y los usamos como indice (32 bits)
    unsigned int index = 0;
    for (int i = 0; i < 4; i++) {
        index = (index << 8) | hash[i];  // Convertimos los primeros 4 bytes en un numero
    }

    // Usamos el modulo para limitar el indice al tamaño de la tabla
    return index % TABLE_SIZE;
}

// Inicializa la tabla hash
void initializeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;  // Inicializamos todas las entradas a NULL
    }
}

// Crear un nuevo nodo en la tabla hash
HashNode* createNode(Persona p) {
    HashNode* newNode = (HashNode*) malloc(sizeof(HashNode));
    newNode->persona = p;
    newNode->next = NULL;
    return newNode;
}

// Insertar una persona en la tabla hash con manejo de colisiones por encadenamiento
void insert(Persona p) {
    unsigned int index = sha256Hash(p.id);
    HashNode* newNode = createNode(p);
    
    // Si no hay colision, simplemente insertamos el nodo en esa posicion
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        // Si hay una colision, agregamos el nuevo nodo al principio de la lista enlazada
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

// Buscar una persona en la tabla hash por ID
Persona* search(int id) {
    unsigned int index = sha256Hash(id);
    
    // Recorremos la lista enlazada en ese indice para encontrar la persona con el ID
    HashNode* current = hashTable[index];
    while (current != NULL) {
        if (current->persona.id == id) {
            return &current->persona;  // Persona encontrada
        }
        current = current->next;
    }
    return NULL;  // Persona no encontrada
}

int main() {
    // Inicializamos la tabla hash
    initializeHashTable();

    // Creamos algunas personas
    Persona p1 = {1, "Juan", 30};
    Persona p2 = {2, "Maria", 25};
    Persona p3 = {3, "Carlos", 40};

    // Insertamos las personas en la tabla hash
    insert(p1);
    insert(p2);
    insert(p3);

    // Buscamos una persona por su ID
    int idBusqueda = 2;
    Persona* resultado = search(idBusqueda);

    // Si la persona fue encontrada, mostramos los datos
    if (resultado != NULL) {
        printf("Persona encontrada: ID = %d, Nombre = %s, Edad = %d\n",
               resultado->id, resultado->nombre, resultado->edad);
    } else {
        printf("Persona con ID %d no encontrada.\n", idBusqueda);
    }

    return 0;
}
