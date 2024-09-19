#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// obs. doble for, errores de sintaxis, no habia argumentos en el arreglo, no estaba comentado.

int main () {
    
    int i;
    
    int argc = 4;
    
    // se definen los argumentos
    char *argv[] = {"./execprog1", "pattern", "file.txt", NULL};
    
    printf("Ejecutando el programa invocador (execprog1). Sus argumentos son:\n");
    
    // Imprime los argumentos iniciales
    for (i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    sleep(2);
    
    // Cambiar el nombre del programa en argv
    strcpy(argv[0], "execprog2");

    // Llamar a execv para ejecutar execprog2
    if (execv ("./execprog2", argv) < 0) {
        //se imprime si hubo erorr en la invocacion
        printf("Error en la invocación a execprog2\n");
        exit(1);
    }
    
    exit(0);
}
