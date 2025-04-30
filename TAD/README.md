# TAD

Un **Tipo Abstracto de Datos (TAD)** es una estructura que define un conjunto de operaciones que pueden realizarse sobre un conjunto de datos sin especificar como estan implementados esos datos. Un TAD describe que operaciones se pueden realizar y cual es el comportamiento de esas operaciones, pero no se enfoca en los detalles de implementacion.

## Caracteristicas de los TAD

1. **Encapsulamiento**: El TAD oculta los detalles de implementacion y solo proporciona una interfaz publica.
2. **Operaciones Definidas**: Los TAD tienen un conjunto de operaciones bien definidas que se pueden realizar sobre los datos que encapsulan.
3. **Independencia de Implementacion**: El mismo TAD puede ser implementado de diferentes maneras, y el usuario solo interactua con la interfaz, no con los detalles internos.

## Implementacion en C

En C, los TAD se implementan utilizando archivos `.h` y `.c`.

### Archivos `.h` (Archivos de Cabecera)

Los archivos `.h` son archivos de cabecera que contienen las **declaraciones** de las estructuras de datos y las funciones que operan sobre ellas. Sirven como una interfaz para el usuario de las funciones, permitiendo que otras partes del programa conozcan las operaciones disponibles sin ver los detalles de la implementacion. Estos archivos son incluidos en los archivos `.c` o en cualquier otro archivo que necesite utilizar las funciones definidas.

### Archivos `.c` (Archivos de Implementacion)

Los archivos `.c` contienen la **implementacion** de las funciones definidas en el archivo de cabecera. Aqui se especifica como se manejan internamente las operaciones sobre las estructuras de datos.

## ¿Como Funcionan los Archivos `.h` y `.c`?

- El archivo `.h` define las interfaces: las estructuras y las funciones que se pueden usar.
- El archivo `.c` contiene la implementacion de esas funciones.
- El archivo `.h` es incluido en el archivo `.c` (o en cualquier otro archivo que necesite usar las funciones definidas).
- El archivo `.h` usa directivas de preprocesador como `#ifndef`, `#define` y `#endif` para evitar la inclusion multiple.
