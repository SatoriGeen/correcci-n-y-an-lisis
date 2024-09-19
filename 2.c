//CORECCION Y ANALISIS //
//VERSION 1//
//EQUIPO: MIOPÍA//
//INTEGRANTES://
//GONZÁLEZ ESCALANTE KEVIN JEREMY //
//HERNÁNDEZ ALVIRDE MARÍA GUADALUPE//
//DÍAZ CASTAÑAREZ AILTON DAVID//
//PÉREZ OLIVARES JÓSE JULIO//

#include <sys/types.h>
#include <unistd.h> //esta libreria es para poder crear hilos
#include <stdlib.h> //las librerias estandas de c para entrada y salida
#include <stdio.h>

int main() {
    pid_t rf;   //aqui estamos declarando un hilo con nombre rf
    rf = fork(); //aqui se le esta asignando a rf el comportamiento fork

    switch (rf) { //aqui se inicializa un switch donde la condicion es el valor que regrese rf
        case -1:    //en el caso de -1 significa que hubo un error y fork falla
            printf("\nNo he podido crear un proceso hijo");
            break;

        case 0: //en el caso 0 significa que no hubo ningun problema al crear el proceso
            printf("\nSoy el hijo, mi PID es %d y mi PPID es %d", getpid(), getppid());
            sleep(20);  //aqui se suspende el proceso 20 segundos
            break;

        default:    //es en el caso donde no es -1 y 0
            printf("\nSoy el padre, mi PID es %d y el PID de mi hijo es %d", getpid(), rf);
            sleep(30);  /*aqui se suspende el proceso 30 segundos eso signica que va dejar que termine
            primero el proceso hijo y despues el proceso padre*/
    }
    printf("\nFinal de ejecucion de %d\n", getpid()); //aqui se despliega que termino la ejecucion del proceso padre
    exit(0); //con eso se marca el termino del programa
}