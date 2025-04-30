#include <stdio.h>

// Definimos los tipos de las funciones: cada una toma dos enteros y devuelve un entero
typedef int (*Operacion)(int, int);

// Funciones de operaciones matematicas
int sumar(int a, int b) {
    return a + b;
}

int restar(int a, int b) {
    return a - b;
}

int multiplicar(int a, int b) {
    return a * b;
}

int dividir(int a, int b) {
    if (b != 0)
        return a / b;
    else
        return 0;  // Evitar division por cero
}

int main() {
    // Arreglo de punteros a funciones
    Operacion operaciones[] = {sumar, restar, multiplicar, dividir};

    int a = 10, b = 5;
    
    // Usamos el arreglo de funciones para realizar diferentes operaciones
    printf("Suma: %d\n", operaciones[0](a, b));           // Sumar
    printf("Resta: %d\n", operaciones[1](a, b));          // Restar
    printf("Multiplicacion: %d\n", operaciones[2](a, b)); // Multiplicar
    printf("Division: %d\n", operaciones[3](a, b));       // Dividir

    return 0;
}
