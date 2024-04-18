/*
 * Ejercicio 2 de TP PIPE
 * 
*/
#include <stdio.h> //Declaración de bibliotecas
#include <sys/types.h> //Declaración de bibliotecas
#include <unistd.h> //Declaración de bibliotecas
#include <string.h> //Declaración de bibliotecas
#include <stdlib.h> //Declaración de bibliotecas
#include<sys/wait.h>  //Declaración de bibliotecas

#define DATA "INFORMACION IMPORTANTE" //Mensaje a enviar
#define BUFF_SIZE 80 //tamaño de la pipe

int main (){

   int ipc[2], proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   if (pipe(ipc) == -1)
      exit(-1);

   switch (fork()){
      
      case 0:
         printf("Hijo escribiendo en tuberia, pid %d... \n", getpid());
         //close(ipc[1]); //El proceso hijo esta cerrando la pipe antes de escribir, por lo que no puede escribir
         
         strncpy(buff, DATA, sizeof(DATA)); 
         write(ipc[1], buff, sizeof(DATA));
         close(ipc[1]);
         exit(0);
         
      default:
         printf("Padre leyendo tuberia, pid %d... \n", getpid());
         leido = read(ipc[0], buff, sizeof(buff));	
         /*if(leido < 1){ 
            write (STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));
         }else { //No se considera si el proceso hijo cerró la pipe, se queda esperando y no avanza el programa
	    write (STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
            write (STDOUT_FILENO, buff, leido-1);
            printf("\" por el proceso padre.\n");
         }*/
         if(leido < 0){
            printf("%d\n",leido);
            write (STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));
         }else { if(leido == 0){
                                printf("El extremo de escritura de la tubería está cerrado por el proceso hijo.\n");
                                }
                                else{ printf("%d\n",leido);
                                    write (STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
                                    write (STDOUT_FILENO, buff, leido-1);
                                    printf("\" por el proceso padre.\n");
                                    }
	    
         }
         wait(NULL);

         exit(0);
   }
}
