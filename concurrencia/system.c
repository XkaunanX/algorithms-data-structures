#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
    //CREO UN HIJO DEL PROCESO QUE EJECUTA ESTE SCRIPT C
    int pid = fork();

    //Si devuelve -1 ocurrio un error
    if (pid == -1)
    {
        printf("Error en el fork\n");
        //Finalizar script
        exit(-1);
    }

    //EJECUTO EN EL PROCESO HIJO
    if (pid == 0)
    {
        printf("Proceso hijo del proceso que ejecuta el script abuelo.c\n");
        printf("Hijo - id: %d\n", getpid());
        printf("El id del proceso que ejecuta el script abuelo.c\n");
        printf("Padre - id: %d\n", getppid());
        system("/bin/echo 'Imprimiendo desde el hijo\n'");
        system("/bin/ls");
    }

    //EJECUTO EN EL PROCESO PADRE
    if(pid > 0){    
        printf("PID %d\n", pid);
        printf("Padre - id: %d\n", getpid());
        system("mkdir Misdocumentos");
        system("touch Misdocumentos/process");
    }

    return 0;
}
