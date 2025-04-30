## Archivos

Un archivo es un conjunto identificable de bits almacenados en un sistema de almacenamiento, como un disco duro o una unidad SSD. Los archivos se utilizan para almacenar datos de manera persistente y pueden contener diversos tipos de informacion, como texto, imagenes o datos binarios.

## ¿Que son los metadatos?

Los metadatos son datos que describen o proporcionan informacion sobre otros datos. En el contexto de los archivos, los metadatos incluyen detalles como:

- **Owner**: El propietario del archivo.
- **Group**: El grupo asociado con el archivo.
- **Executable**: Un indicador de si el archivo es ejecutable.
- **Tipo de archivo**: Determina si el archivo es de texto, binario, registro, etc.
- **Permisos**: Controla quien puede leer, escribir o ejecutar el archivo.

El tipo de archivo es parte de los metadatos, indicando si el archivo contiene datos binarios, texto u otros tipos especificos.

## Tipos de archivos que maneja el SO

El sistema operativo maneja varios tipos de archivos:

- **Archivos binarios**: Contienen datos en formato binario, como ejecutables o bibliotecas compartidas.
- **Archivos de texto**: Contienen datos en formato legible por humanos, con delimitadores de linea que separan las lineas de texto.
- **Archivos de registro**: Utilizados para almacenar registros.

Los archivos de registro no deben confundirse con los archivos de logs, ya que los primeros se utilizan para almacenar registros estructurados, mientras que los logs contienen informacion de eventos o errores.

## Estructura de Archivos

Los archivos pueden tener dos partes principales:

1. **Cabecera**: Contiene metadatos y, a veces, informacion adicional que describe la estructura del archivo.
2. **Cuerpo**: Contiene los datos reales o la informacion que el archivo esta destinado a almacenar.

## System Calls para Manejo de Archivos

Las system calls en Unix proporcionan las funciones basicas para interactuar con archivos. Algunas de las mas utilizadas son:

- **open()**: Abre un archivo para lectura, escritura o ambas.
- **read()**: Lee datos de un archivo abierto.
- **write()**: Escribe datos en un archivo abierto.
- **close()**: Cierra un archivo previamente abierto.
- **lseek()**: Mueve el puntero de lectura/escritura de un archivo a una posicion especifica.

## Tipos de Accesos

Los accesos a archivos pueden realizarse de diferentes maneras, dependiendo de como se gestionen los datos en el archivo:

- **Secuencial**: Los datos se leen o escriben de manera continua, sin saltar a posiciones especificas.
- **Indexado**: Utiliza un indice para acceder a los datos de manera mas eficiente.
- **Hash**: Utiliza una funcion hash para acceder a datos.
- **Directo**: Permite acceso aleatorio a los datos sin seguir un orden especifico.
- **Aleatorio**: Similar al acceso directo, pero con la capacidad de leer o escribir en cualquier posicion del archivo.
- 
## Operaciones Comunes

1. **Abrir un Archivo (open)**: Solicita acceso a un archivo para leer o escribir.

2. **Leer Datos (read)**: Extrae datos de un archivo y los coloca en un buffer en memoria.

3. **Escribir Datos (write)**: Almacena datos en un archivo.

4. **Cerrar un Archivo (close)**: Libera recursos y asegura que los datos se escriban correctamente.

5. **Mover el Puntero (lseek)**: Ajusta la posición de lectura o escritura en un archivo.

6. **Eliminar un Archivo (remove)**: Borra un archivo y libera el espacio ocupado.

7. **Renombrar un Archivo (rename)**: Cambia el nombre o mueve un archivo.

8. **Comprobar la Existencia de un Archivo (stat)**: Verifica si un archivo existe y obtiene detalles sobre él.
