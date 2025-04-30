#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // Para wait()

void crear_cadena(int nivel, int max_nivel) {
    if (nivel > max_nivel) {
        return;  // Si alcanzamos el nivel maximo, no creamos mas hijos
    }

    printf("Proceso de nivel %d con PID %d, Padre PID: %d\n", nivel, getpid(), getppid());

    pid_t pid = fork();  // Crear un hijo

    if (pid < 0) {
        perror("Error al crear hijo");
        exit(1);
    }

    if (pid == 0) {  // Este es el hijo
        // El hijo crea su propio hijo, pasando el siguiente nivel
        crear_cadena(nivel + 1, max_nivel); 
        exit(0);  // El hijo termina despues de crear su propio hijo
    }

    // El proceso padre espera que el hijo termine antes de continuar
    wait(NULL);  // Espera a que el hijo termine
}

int main() {
    int max_nivel = 5;  // Profundidad maxima de creacion de hijos
    printf("Creando cadena de procesos hasta el nivel %d...\n", max_nivel);
    crear_cadena(1, max_nivel);  // Inicia la creacion desde el nivel 1
    return 0;
}
