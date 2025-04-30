#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para fork(), getpid(), getppid()

void crear_hijos_lineales(int nivel, int max_nivel) {
    if (nivel > max_nivel) {
        return;  // Si hemos alcanzado el maximo nivel, no crear mas hijos
    }

    int pid = fork();  // Crear un proceso hijo

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("Error al crear el hijo");
        exit(1);
    }

    if (pid == 0) {
        // Este codigo se ejecuta solo en el hijo
        printf("  Hijo de nivel %d: PID %d, Padre PID: %d\n", nivel, getpid(), getppid());
        printf("  Creando hijo de nivel %d...\n", nivel + 1);
        
        // Crear el siguiente hijo en la jerarquia
        crear_hijos_lineales(nivel + 1, max_nivel);
        exit(0);  // El hijo termina aqui
    } else {
        // Este codigo se ejecuta solo en el padre
        printf("Padre: PID %d, Creo hijo PID: %d\n", getpid(), pid);
        wait(NULL);  // Espera a que el hijo termine antes de continuar
    }
}

void generar_grafico(int max_nivel) {
    printf("\nGenerando grafico de la jerarquia de procesos...\n");
    printf("digraph G {\n");
    printf("  rankdir=TB;\n");
    
    // Empezamos desde el proceso principal (padre)
    printf("  // Nodo raiz\n");
    printf("  \"%d\" [label=\"Padre PID %d\"];\n", getpid(), getpid());
    
    // Generamos los hijos en el grafico
    for (int i = 1; i <= max_nivel; i++) {
        int padre = getpid();
        printf("  \"%d\" -> \"%d\" [label=\"Hijo de nivel %d\"];\n", padre, padre + i, i);
    }

    printf("}\n");
}

int main() {
    int max_nivel = 3;  // Numero de niveles de hijos a crear (ajustable)

    // Crear la jerarquia de procesos lineales
    printf("Creando procesos lineales hasta el nivel %d...\n", max_nivel);
    crear_hijos_lineales(1, max_nivel);

    // Generar el grafico
    generar_grafico(max_nivel);

    return 0;
}
