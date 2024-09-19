#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

// Prototipos de funciones
void imprimeDePipe(int leePipe);  // Funcionalidad para el hijo
void enviaAPipe(int escribePipe); // Funcionalidad para el padre

int main() {
    pid_t procHijo;
    int pipeFileDescriptors[2]; // Descriptores de ambos extremos

    // Intento de creación del pipe
    if (pipe(pipeFileDescriptors) == -1) {
        // Error al crear el pipe, por lo que se termina el programa
        printf("Error al crear pipe\n");
        exit(1);
    }

    procHijo = fork(); // Crea proceso hijo
    if (procHijo < 0) {
        // Si fork() retorna un valor negativo, hubo un error
        int errnum = errno; // Preserva el código de error para describirlo
        printf("Error %d al generar proceso hijo con fork(): %s\n", errnum, strerror(errnum));
        exit(1); // Termina el proceso debido al error
    }

    if (procHijo == 0) {
        // Código que se ejecuta en el proceso hijo
        close(pipeFileDescriptors[1]); // Cierra el extremo de escritura del pipe
        imprimeDePipe(pipeFileDescriptors[0]); // Llama a la función que lee del pipe
    } else if (procHijo > 0) {
        // Código que se ejecuta en el proceso padre
        close(pipeFileDescriptors[0]); // Cierra el extremo de lectura del pipe
        enviaAPipe(pipeFileDescriptors[1]); // Llama a la función que escribe en el pipe
        wait(NULL); // Espera a que termine el proceso hijo
        printf("Hijo terminado, terminando proceso padre\n");
    }

    return 0; // Fin del proceso padre
}

// Funcionalidad para el hijo: lee del pipe la cadena enviada, imprime el contenido, cierra su extremo del pipe y termina
void imprimeDePipe(int leePipe) {
    char buf; // Carácter de buffer

    printf("Proceso hijo, esperando cadena...\n");

    // Lee del pipe byte por byte hasta que no haya más datos (EOF)
    while (read(leePipe, &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1); // Escribe lo que leyó en la salida estándar
    }

    // Escribe un salto de línea después de terminar de leer
    write(STDOUT_FILENO, "\n", 1);

    // Cierra el extremo de lectura del pipe
    close(leePipe);
    printf("Proceso hijo, finalizando\n");

    // Termina el proceso hijo
    exit(0);
}

// Funcionalidad para el padre: lee una cadena de hasta 10 caracteres, la escribe a su extremo del pipe y espera la terminación del hijo
void enviaAPipe(int escribePipe) {
    char buf[10]; // Buffer para almacenar la entrada del usuario (hasta 10 caracteres)

    printf("Proceso padre, ingresa una cadena de 10 caracteres y presiona enter:\n");
    //corrección
    // El formato %10c es incorrecto para leer hasta 10 caracteres. Debería ser %9s para asegurar el \0.
    // scanf("%10c", buf); - Incorrecto
    scanf("%9s", buf); // Lee la entrada del usuario

    printf("\n\n"); // Separa la entrada de las futuras salidas

    // Escribe la cadena al pipe
    write(escribePipe, buf, strlen(buf));

    // Cierra el extremo de escritura del pipe para indicar el EOF al proceso hijo
    close(escribePipe);

    // Espera la terminación del proceso hijo
    //corrección
    //Llamada a wait(NULL): La espera del proceso hijo estaba dentro del bloque del padre, pero en la declaración original no había la llamada a wait(). 
    //Se añadió correctamente dentro del bloque del proceso padre.
    wait(NULL);
}