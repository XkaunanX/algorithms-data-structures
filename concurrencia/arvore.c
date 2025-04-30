#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // Para wait()

void crear_arbol_balanceado(int nivel, int max_nivel) {
    if (nivel > max_nivel) {
        return;  // Si alcanzamos el nivel maximo, no creamos mas hijos
    }

    // Numero de hijos que creara este proceso (en este caso, 2 por proceso)
    int num_hijos = 2;
    printf("Proceso de nivel %d con PID %d, Padre PID: %d, Creando %d hijos\n", 
           nivel, getpid(), getppid(), num_hijos);

    for (int i = 0; i < num_hijos; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error al crear hijo");
            exit(1);
        }

        if (pid == 0) {  // Este es el hijo
            crear_arbol_balanceado(nivel + 1, max_nivel);  // Llamada recursiva para crear mas hijos
            exit(0);  // El hijo termina despues de crear sus propios hijos
        }
    }

    // El proceso padre espera a que todos sus hijos terminen
    for (int i = 0; i < num_hijos; i++) {
        wait(NULL);  // Espera a que cada hijo termine
    }
}

int main() {
    int max_nivel = 3;  // Profundidad maxima de creacion de hijos
    printf("Creando arbol balanceado de procesos hasta el nivel %d...\n", max_nivel);
    crear_arbol_balanceado(1, max_nivel);  // Inicia la creacion desde el nivel 1
    return 0;
}
