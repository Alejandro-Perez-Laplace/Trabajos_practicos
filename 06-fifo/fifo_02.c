/*
 * Ejercicio 2 del TP FIFO  Tipica implementacion de una FIFO.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h> 

#define MENSAJE "HOLA PROCESO HIJO, SOY TU PADRE"
#define RESPUESTA "HOLA PROCESO PADRE, SOY TU HIJO"
#define FIFO_PATH "/tmp/MI_FIFO"

int main() {
    int err, fifo_d, fifo_r;
    char buff[80];
    int leido;

    unlink(FIFO_PATH);

    err = mkfifo(FIFO_PATH, 0777);
    if(err == -1) {
        write(STDOUT_FILENO, "Error al crear FIFO, la FIFO ya existe\n", sizeof("Error al crear FIFO, la FIFO ya existe\n"));
    } else {
        write(STDOUT_FILENO, "FIFO creada correctamente\n", sizeof("FIFO creada correctamente\n"));
    }

    switch (fork()) {
        case -1:
            write(STDOUT_FILENO, "Error al crear hijo\n", sizeof("Error al crear hijo\n"));
            return -1;
            break;

        case 0: // Hijo
            write(STDOUT_FILENO, "Hijo inicia\n", sizeof("Hijo inicia\n"));
            sleep(5);

            // Abre FIFO en modo lectura
            fifo_d = open(FIFO_PATH, O_RDONLY, 0);
            if (fifo_d == -1) {
                write(STDOUT_FILENO, "Hijo, error al abrir FIFO\n", sizeof("Hijo: error al abrir FIFO\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Hijo, FIFO abierta correctamente\n", sizeof("Hijo: FIFO abierta correctamente\n"));
            }

            // Lee de la FIFO
            leido = read(fifo_d, buff, sizeof(buff));
            if (leido < 1) {
                write(STDOUT_FILENO, "Hijo, FIFO vacia\n", sizeof("Hijo, FIFO vacia\n"));
            } else {
                write(STDOUT_FILENO, "Hijo, leido de la FIFO \n", sizeof("Hijo, leido de la FIFO \n"));
                write(STDOUT_FILENO, buff, leido-1);
                write(STDOUT_FILENO, "\n", sizeof("\n"));
            }
            close(fifo_d);

            // Abre FIFO en modo escritura
            fifo_r = open(FIFO_PATH, O_WRONLY, 0);
            if (fifo_r == -1) {
                write(STDOUT_FILENO, "Hijo, error al abrir FIFO_r\n", sizeof("Hijo: error al abrir FIFO_r\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Hijo, FIFO_r abierta correctamente\n", sizeof("Hijo: FIFO_r abierta correctamente\n"));
            }

            // Escribe en FIFO_r
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
                write(STDOUT_FILENO, "Padre, error al abrir FIFO\n", sizeof("Padre: error al abrir FIFO\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Padre, FIFO abierta correctamente\n", sizeof("Padre: FIFO abierta correctamente\n"));
            }

            // Escribe en FIFO
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
                write(STDOUT_FILENO, "Padre, error al abrir FIFO_r\n", sizeof("Padre: error al abrir FIFO_r\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "Padre, FIFO_r abierta correctamente\n", sizeof("Padre: FIFO_r abierta correctamente\n"));
            }

            // Lee de FIFO_r
            leido = read(fifo_r, buff, sizeof(buff));
            if (leido < 1) {
                write(STDOUT_FILENO, "Padre, FIFO_r vacia\n", sizeof("Padre, FIFO_r vacia\n"));
            } else {
                write(STDOUT_FILENO, "Padre, leido de la FIFO_r \n", sizeof("Padre, leido de la FIFO_r \n"));
                write(STDOUT_FILENO, buff, leido-1);
                write(STDOUT_FILENO, "\n", sizeof("\n"));
            }
            close(fifo_r);

            wait(NULL); // Espera a que el proceso hijo termine

            write(STDOUT_FILENO, "Padre termina\n", sizeof("Padre termina\n"));
            break;
    }
      
    exit(0);
}

