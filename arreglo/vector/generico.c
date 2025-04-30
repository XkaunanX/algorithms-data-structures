#include <stdio.h>
#include <stdlib.h>

int main() {
    // Crear un arreglo de 3 punteros a void, es decir, un arreglo de 3 elementos que pueden almacenar cualquier tipo de datos
    void* arr[3];

    // Asignar un entero al primer elemento
    int a = 10;
    arr[0] = &a;  // arr[0] apunta a un entero

    // Asignar un flotante al segundo elemento
    float b = 3.14;
    arr[1] = &b;  // arr[1] apunta a un flotante

    // Asignar una cadena de caracteres al tercer elemento
    char* c = "Hola Mundo";
    arr[2] = c;  // arr[2] apunta a una cadena de caracteres

    // Ahora vamos a acceder y imprimir los datos de cada tipo usando casting

    // Acceder al entero
    printf("El valor del entero es: %d\n", *((int*)arr[0]));

    // Acceder al flotante
    printf("El valor del flotante es: %.2f\n", *((float*)arr[1]));

    // Acceder a la cadena
    printf("El valor de la cadena es: %s\n", (char*)arr[2]);

    return 0;
}
