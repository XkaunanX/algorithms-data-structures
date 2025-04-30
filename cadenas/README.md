# Uso de Cadenas en C

En C, una cadena es un arreglo de caracteres que se termina con un caracter especial llamado **null terminator** (`'\0'`). A diferencia de otros lenguajes de programacion, C no tiene un tipo de dato especifico para cadenas, por lo que las cadenas se manejan como arreglos de caracteres.

## ¿Que es una Cadena en C?

Una **cadena** en C es un conjunto de caracteres almacenados de manera contigua en memoria. El ultimo caracter de una cadena es siempre un **null terminator** (`'\0'`), que indica el final de la cadena. Este caracter es esencial para que las funciones que manipulan cadenas en C puedan saber hasta donde deben leer.

```plaintext
   0       1       2       3       4
+-----+ +-----+ +-----+ +-----+ +-----+
| 'H' | | 'o' | | 'l' | | 'a' | | '\0'|
+-----+ +-----+ +-----+ +-----+ +-----+ 
   ^
   |
Puntero
```

```c
#include <stdio.h>

int main() {
    char vector[] = "Hola";
    
    // Imprimir el contenido del vector
    printf("%s\n", vector);

    return 0;
}
```

### Caracteristicas Claves de las Cadenas en C

1. **Arreglo de Caracteres**: Las cadenas son simplemente arreglos de caracteres (`char[]`).
2. **Null Terminator**: Una cadena en C siempre termina con el caracter especial `'\0'`.
3. **Tamaño Fijo**: Una cadena en C tiene un tamaño fijo, lo que significa que su longitud no se puede cambiar despues de ser definida.

## Manipulacion de Cadenas en C

Aunque C no proporciona un tipo de datos especifico para cadenas, ofrece varias funciones estandar para manipularlas. La biblioteca estandar `string.h` contiene muchas funciones utiles para trabajar con cadenas.

### Funciones Comunes de Cadenas

- **strlen()**: Devuelve la longitud de la cadena (sin contar el `'\0'`).
- **strcpy()**: Copia una cadena en otra.
- **strcat()**: Concadena dos cadenas.
- **strcmp()**: Compara dos cadenas lexicograficamente.
- **strchr()**: Busca un caracter en una cadena.
- **strstr()**: Busca una subcadena dentro de una cadena.

## Consideraciones Importantes

1. **Buffer Overflow**: Como las cadenas en C no verifican automaticamente su tamaño, es crucial asegurarse de que el arreglo de caracteres tenga suficiente espacio para almacenar la cadena y el caracter de terminacion `'\0'`. Si no hay suficiente espacio, se puede producir un desbordamiento de buffer (buffer overflow).
   
2. **Manipulacion Manual del Null Terminator**: Si en algun momento trabajas con cadenas de longitud variable, asegurate de agregar manualmente el terminador `'\0'` al final de la cadena para evitar errores.

3. **Cadenas Inmutables**: Una cadena en C es un arreglo de caracteres, por lo que los elementos de la cadena pueden modificarse directamente (por ejemplo, cambiando un caracter). Sin embargo, si la cadena es un literal (por ejemplo, `"Hola Mundo"`), no debes intentar modificarla, ya que esta almacenada en una seccion de solo lectura de la memoria.

4. **Punteros a Cadenas**: Tambien puedes manejar cadenas como punteros a caracteres. Esto es util cuando se necesita pasar cadenas a funciones que las manipulen sin necesidad de copiar toda la cadena.
