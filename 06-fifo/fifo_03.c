/*
 * Ejercicio 3 del TP FIFO  Tipica implementacion de una FIFO.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h> 

#define MENSAJE "HOLA PROCESO HIJO, SOY TU PADRE" // Mensaje a enviar
#define RESPUESTA "HOLA PROCESO PADRE, SOY TU HIJO" // Mensaje a responder
#define FIFO_PATH "/tmp/MI_FIFO" // Dirección de la FIFO

int main() {
    int err, fifo_d, fifo_r;
    char buff[80];
    int leido;

    unlink(FIFO_PATH); // Si la FIFO existe la borro

    // FIFO puede ser leída, escrita y ejecutada por todos los usuarios
    err = mkfifo(FIFO_PATH, 0777);
    if (err == -1) {
        write(STDOUT_FILENO, "Error al crear FIFO, la FIFO ya existe\n", sizeof("Error al crear FIFO, la FIFO ya existe\n"));
    } else {
        write(STDOUT_FILENO, "FIFO creada correctamente\n", sizeof("FIFO creada correctamente\n"));
    }

    switch (fork()) {
        case -1: // Error
            write(STDOUT_FILENO, "Error al crear hijo\n", sizeof("Error al crear hijo\n"));
            return -1;
            break;

        case 0: // Hijo
            write(STDOUT_FILENO, "Hijo inicia\n", sizeof("Hijo inicia\n"));
            sleep(5);

            // Se abre FIFO para lectura
            fifo_d = open(FIFO_PATH, O_RDONLY, 0);
            // Lectura del hijo
            if (fifo_d == -1) {
                write(STDOUT_FILENO, "Hijo, error al abrir FIFO\n", sizeof("Hijo, error al abrir FIFO\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Hijo, FIFO abierta correctamente\n", sizeof("Hijo, FIFO abierta correctamente\n"));
            }

            // Se lee FIFO
            leido = read(fifo_d, buff, sizeof(buff));
            if (leido < 1) {
                write(STDOUT_FILENO, "Hijo, FIFO vacía\n", sizeof("Hijo, FIFO vacía\n"));
            } else {
                write(STDOUT_FILENO, "Hijo, leído de la FIFO \n", sizeof("Hijo, leído de la FIFO \n"));
                write(STDOUT_FILENO, buff, leido-1);
                write(STDOUT_FILENO, "\n", sizeof("\n"));
            }
            close(fifo_d);

            // Respuesta del Hijo
            fifo_r = open(FIFO_PATH, O_WRONLY, 0);
            if (fifo_r == -1) {
                write(STDOUT_FILENO, "Hijo, error al abrir FIFO_r\n", sizeof("Hijo, error al abrir FIFO_r\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Hijo, FIFO_r abierta correctamente\n", sizeof("Hijo, FIFO_r abierta correctamente\n"));
            }
            // Se escribe en FIFO_r
            err = write(fifo_r, RESPUESTA, sizeof(RESPUESTA));
            if (err == -1) {
                write(STDOUT_FILENO, "Hijo, error al escribir en FIFO_r\n", sizeof("Hijo, error al escribir en FIFO_r\n"));
            } else {
                write(STDOUT_FILENO, "Hijo, escrito RESPUESTA en FIFO_r\n", sizeof("Hijo, escrito RESPUESTA en FIFO_r\n"));
            }
            close(fifo_r);

            write(STDOUT_FILENO, "Hijo termina\n", sizeof("Hijo termina\n")); 
            exit(0);

        break;

        default: // Padre
            write(STDOUT_FILENO, "Padre inicia\n", sizeof("Padre inicia\n"));
            sleep(2);

            // Abre FIFO en modo escritura
            fifo_d = open(FIFO_PATH, O_WRONLY, 0);
            if (fifo_d == -1) {
                write(STDOUT_FILENO, "Padre, error al abrir FIFO\n", sizeof("Padre, error al abrir FIFO\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Padre, FIFO abierta correctamente\n", sizeof("Padre, FIFO abierta correctamente\n"));
            }

            // Se escribe en el FIFO
            err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
            if (err == -1) {
                write(STDOUT_FILENO, "Padre, error al escribir en FIFO\n", sizeof("Padre, error al escribir en FIFO\n"));
            } else {
                write(STDOUT_FILENO, "Padre, escrito MENSAJE en FIFO\n", sizeof("Padre, escrito MENSAJE en FIFO\n"));
            }
            close(fifo_d);

            // Abre FIFO en modo lectura
            fifo_r = open(FIFO_PATH, O_RDONLY, 0);
            if (fifo_r == -1) {
                write(STDOUT_FILENO, "Padre, error al abrir FIFO_r\n", sizeof("Padre, error al abrir FIFO_r\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Padre, FIFO_r abierta correctamente\n", sizeof("Padre, FIFO_r abierta correctamente\n"));
            }

            // Lee de FIFO_r
            leido = read(fifo_r, buff, sizeof(buff));
            if (leido < 1) {
                write(STDOUT_FILENO, "Padre, FIFO_r vacía\n", sizeof("Padre, FIFO_r vacía\n"));
            } else {
                write(STDOUT_FILENO, "Padre, leído de la FIFO_r \n", sizeof("Padre, leído de la FIFO_r \n"));
                write(STDOUT_FILENO, buff, leido-1);
                write(STDOUT_FILENO, "\n", sizeof("\n"));
            }
            close(fifo_r);

            wait(NULL); // Espera que el proceso hijo termine

            write(STDOUT_FILENO, "Padre termina\n", sizeof("Padre termina\n")); 
        break;
    }
   
    // Eliminación FIFO
    // if (unlink(FIFO_PATH) < 0){
    //     printf("No se puede borrar FIFO.\n"); }
      
    exit(0);
}
