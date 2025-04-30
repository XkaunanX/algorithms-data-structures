#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void crearHijosH1() {
    for (int i = 1; i <= 3; i++) {
        int pid = fork();
        if (pid == -1) {
            perror("Error al crear el proceso");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Proceso hijo
            printf("Soy H1%d (PID: %d), creado por mi padre (PID: %d)\n", i, getpid(), getppid());
            exit(0); // Salir del hijo
        }
    }
}

int main() {
    int pid_hijo1, pid_hijo2, pid_hijo3;

    // Crear el primer hijo
    pid_hijo1 = fork();
    if (pid_hijo1 == -1) {
        perror("Error al crear el proceso H1");
        return EXIT_FAILURE;
    }

    if (pid_hijo1 == 0) { // Proceso hijo 1
        printf("Soy el H1 (PID: %d), creado por mi padre (PID: %d)\n", getpid(), getppid());
        crearHijosH1(); // H1 crea 3 hijos (H11, H12, H13)
        exit(0); // Salir del hijo
    } else { // Proceso padre
        // Crear el segundo hijo
        pid_hijo2 = fork();
        if (pid_hijo2 == -1) {
            perror("Error al crear el proceso H2");
            return EXIT_FAILURE;
        }

        if (pid_hijo2 == 0) { // Proceso hijo 2
            printf("Soy H2 (PID: %d), creado por mi padre (PID: %d)\n", getpid(), getppid());
            // Ejecutar un script de Linux
            system("./script.sh");
            exit(0);
        } else { // Proceso padre
            // Crear el tercer hijo
            pid_hijo3 = fork();
            if (pid_hijo3 == -1) {
                perror("Error al crear el proceso H3");
                return EXIT_FAILURE;
            }

            if (pid_hijo3 == 0) { // Proceso hijo 3
                printf("Soy H3 (PID: %d), creado por mi padre (PID: %d)\n", getpid(), getppid());
                // Ejecutar un comando usando execl
                execl("/bin/ls", "ls", NULL); // Cambia "ls" por el comando que desees ejecutar
                perror("Error al ejecutar execl");
                exit(1);
            }
        }
    }

    // Esperar a que terminen los hijos (opcional)
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}
