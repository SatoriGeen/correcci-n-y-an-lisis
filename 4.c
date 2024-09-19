#include <unistd.h>  // Librería para fork(), getpid(), getppid(), sleep()
#include <stdlib.h>  // Librería para exit()
#include <stdio.h>   // Librería para printf()

//correcciones
//Llamada a wait(NULL) en el proceso padre:
//En la versión original, el proceso padre no espera que el hijo termine antes de continuar con su ejecución.
//Se añadió la función wait(NULL); en el bloque del padre para que espere a que el proceso hijo termine antes de que el padre continúe. 
//Esto evita que el padre termine antes que el hijo o de forma simultánea, lo que podría producir resultados desordenados en la consola.

int main() {
    pid_t rf;  // Variable para almacenar el valor retornado por fork()
    
    rf = fork();  // Crea un nuevo proceso

    switch (rf) {
        case -1:
            // Este bloque se ejecuta si fork() falla
            printf("\nNo he podido crear el proceso hijo");
            break;

        case 0:
            // Este bloque se ejecuta en el proceso hijo (rf == 0)
            printf("\nSoy el hijo, mi PID es %d y mi PPID es %d", getpid(), getppid());
            // El hijo duerme por 10 segundos para simular alguna operación
            sleep(10); 
            break;

        default:
            // Este bloque se ejecuta en el proceso padre (rf contiene el PID del hijo)
            printf("\nSoy el padre, mi PID es %d y el PID de mi hijo es %d", getpid(), rf);
            // Se recomienda usar wait() para que el padre espere al hijo antes de terminar
            wait(NULL);  // Espera a que el hijo termine
            printf("\nEl proceso hijo ha terminado");
    }
    
    // Este printf se ejecutará tanto en el padre como en el hijo, después de sus respectivos bloques
    printf("\nFinal de ejecucion de %d \n", getpid());
    
    exit(0);  // Termina el proceso actual (tanto para el padre como para el hijo)
}