/*
 * Ejercicio 4 del TP FIFO  Tipica implementacion de una FIFO.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h> 

#define FIFO_PATH "/tmp/MI_FIFO" // Dirección de la FIFO
int main() {
    char buff[80];
    int leido;
    int fifo_d, err;
    fifo_d = open(FIFO_PATH, O_RDONLY, 0);
            if (fifo_d == -1) {
                write(STDOUT_FILENO, "Error al abrir FIFO\n", sizeof("Error al abrir FIFO\n"));
                return -1;
            } else {
                write(STDOUT_FILENO, "FIFO abierta correctamente\n", sizeof("FIFO abierta correctamente\n"));
            }

    // Lee de la FIFO
    leido = read(fifo_d, buff, sizeof(buff));
    if (leido < 0) {
        write(STDOUT_FILENO, "Error al leer FIFO\n", sizeof("Error al leer FIFO\n"));
        close(fifo_d);
        return -1;
    }
      if (leido > 0) {
        write(STDOUT_FILENO, buff, leido);
        write(STDOUT_FILENO, "\n", sizeof("\n"));
    } else {
        write(STDOUT_FILENO, "FIFO vacía\n", sizeof("FIFO vacía\n"));
    }
            // Cierra la FIFO
            close(fifo_d);
            exit(0);
}