#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para fork(), getpid(), getppid()

void crear_hijos_exponenciales(int nivel, int max_nivel) {
    if (nivel > max_nivel) {
        return;  // Si hemos alcanzado el maximo nivel, no crear mas hijos
    }

    int pid1, pid2;

    // Crear el primer hijo
    pid1 = fork();
    if (pid1 < 0) {
        perror("Error al crear el primer hijo");
        exit(1);
    }

    if (pid1 == 0) {
        // Este codigo se ejecuta solo en el primer hijo
        printf("Hijo de nivel %d: PID %d, Padre PID: %d\n", nivel, getpid(), getppid());
        // Llamar recursivamente para crear mas hijos exponencialmente
        crear_hijos_exponenciales(nivel + 1, max_nivel);
        exit(0);  // Terminar el primer hijo
    } else {
        // Crear el segundo hijo
        pid2 = fork();
        if (pid2 < 0) {
            perror("Error al crear el segundo hijo");
            exit(1);
        }

        if (pid2 == 0) {
            // Este codigo se ejecuta solo en el segundo hijo
            printf("Hijo de nivel %d: PID %d, Padre PID: %d\n", nivel, getpid(), getppid());
            // Llamar recursivamente para crear mas hijos exponencialmente
            crear_hijos_exponenciales(nivel + 1, max_nivel);
            exit(0);  // Terminar el segundo hijo
        } else {
            // Este codigo se ejecuta en el padre, espera a que ambos hijos terminen
            wait(NULL);
            wait(NULL);
        }
    }
}

int main() {
    int max_nivel = 3;  // Numero de niveles de hijos a crear (ajustable)

    // Crear los procesos exponencialmente hasta el maximo nivel
    printf("Creando procesos exponencialmente hasta el nivel %d...\n", max_nivel);
    crear_hijos_exponenciales(1, max_nivel);

    return 0;
}
