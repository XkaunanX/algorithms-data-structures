#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // Para wait()

void crear_hijos_bifurcados(int nivel, int max_nivel) {
    if (nivel > max_nivel) {
        return;  // Si hemos alcanzado el maximo nivel, no crear mas hijos
    }

    pid_t pid1, pid2;

    // Primer hijo
    pid1 = fork();
    if (pid1 < 0) {
        perror("Error al crear el primer hijo");
        exit(1);
    }

    if (pid1 == 0) {  // Este es el primer hijo
        printf("Hijo de nivel %d con PID %d, Padre PID: %d\n", nivel, getpid(), getppid());
        crear_hijos_bifurcados(nivel + 1, max_nivel);  // Crear mas hijos recursivamente
        exit(0);  // Terminar el primer hijo
    } else {
        // Segundo hijo
        pid2 = fork();
        if (pid2 < 0) {
            perror("Error al crear el segundo hijo");
            exit(1);
        }

        if (pid2 == 0) {  // Este es el segundo hijo
            printf("Hijo de nivel %d con PID %d, Padre PID: %d\n", nivel, getpid(), getppid());
            crear_hijos_bifurcados(nivel + 1, max_nivel);  // Crear mas hijos recursivamente
            exit(0);  // Terminar el segundo hijo
        }
    }

    // El proceso padre espera a que ambos hijos terminen
    wait(NULL);
    wait(NULL);
}

int main() {
    int max_nivel = 3;  // Numero de niveles de profundidad
    printf("Creando hijos bifurcados hasta el nivel %d...\n", max_nivel);
    crear_hijos_bifurcados(1, max_nivel);  // Comienza desde el nivel 1
    return 0;
}
