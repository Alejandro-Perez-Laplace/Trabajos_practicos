/*
 * Ejercicio 4 del TP FIFO  Tipica implementacion de una FIFO.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "HOLA PROCESO HIJO, SOY TU PADRE"//mesaje a enviar
#define RESPUESTA "HOLA PROCESO PADRE, SOY TU HIJO"//mensaje a responder
#define FIFO_PATH "/tmp/MI_FIFO" //direccion de la fifo

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;

   unlink(FIFO_PATH);    // si la FIFO existe la borro

   // FIFO puede ser leida, escrita y ejecutada por:
  err = mkfifo(FIFO_PATH, 0777);//crea la fifo y acepta dos argumentos FIFO_PATH (direccion de la fifo), 0777, permisos)
   if(err == -1) {
      write (STDOUT_FILENO, "Error al crear FIFO, la FIFO ya existe\n", sizeof("Error al crear FIFO, la FIFO ya existe\n"));
   }else {
      write (STDOUT_FILENO, "FIFO creada correctamente\n", sizeof("FIFO creada correctamente\n"));
   }
sleep(5);
//write(STDOUT_FILENO, "FIFO\n", sizeof("FIFO\n"));

// Se abre FIFO	
         fifo_d = open(FIFO_PATH, O_RDONLY, 0); // O_NONBLOCK parametros
         //Lectura del hijo
         
         if(fifo_d == -1){
            write (STDOUT_FILENO, "Error al abrir FIFO\n", sizeof("Error al abrir FIFO\n"));
            return -1;
         }else {
            write (STDOUT_FILENO, "FIFO abierta correctamente\n", sizeof("FIFO abierta correctamente\n"));
         }
         // Se lee FIFO
         //write(STDOUT_FILENO, "FIFO\n", sizeof("FIFO\n"));
         leido = read(fifo_d, buff, sizeof(buff));
         //write(STDOUT_FILENO, "FIFO\n", sizeof("FIFO\n"));
         if(leido < 1){
            write(STDOUT_FILENO, "FIFO vacia\n", sizeof("FIFO vacia\n"));
         }else {
            write(STDOUT_FILENO, "Leido de la FIFO \n", sizeof("Leido de la FIFO \n"));
            write(STDOUT_FILENO, buff, leido-1);
            write(STDOUT_FILENO, "\n", sizeof("\n"));
         }
         close(fifo_d);
 
   //Eliminación FIFO
   //if (unlink(FIFO_PATH) < 0){
   //   printf("No se puede borrar FIFO.\n"); }
      
   exit(0);

}
