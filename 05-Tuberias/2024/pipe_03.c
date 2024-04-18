/*
 * Ejercicio 3 de TP PIPE
*/
#include <stdio.h> //Inclusion de bibliotecas necesarias
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define FRASE_A "INFORMACION IMPORTANTE A" //Mensajes a enviar
#define FRASE_B "INFORMACION IMPORTANTE B"
#define BUFF_SIZE 80 //Tamaño de la tuberia

void pipe_sign_handler(int a){
   
   printf ("SIGPIPE\n");
}

int main (){

   int ipc[2]/*Descriptor del archivo de tuberias*/, proc;
   int leido, success;
   char buff[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler);
   
   pipe(ipc);//creacion de la tuberia

   switch (fork()){ //creacion de proceso hijo 
      
      case 0:
      printf("proceso hijo, pid %d \n", getpid());
	   close(ipc[0]);      
	   strncpy(buff, FRASE_A, sizeof(FRASE_A)); 
	   //strncpy(buff, " ", sizeof(" "));
	   write(ipc[1], buff, sizeof(FRASE_A));
	   write(ipc[1], " ", sizeof(" "));
	   close(ipc[1]);
	   exit(0);
      break;
      
      default:
      switch (fork()){ 
            
         case 0:
         printf("proceso hijo, pid %d \n", getpid());
            close(ipc[0]);               
            strncpy(buff, FRASE_B, sizeof(FRASE_B)); 
            //strncpy(buff, " ", sizeof(" "));
            write(ipc[1], buff,    sizeof(FRASE_B));
            write(ipc[1], " ", sizeof(" "));
            close(ipc[1]);
            exit(0);      
         break;
         
         default:
            close(ipc[1]);
            int i;
            
            sleep(1);
            printf("proceso padre, pid %d \n", getpid());
            for(i=0; i<2; i++){
               leido = read(ipc[0], buff, sizeof(buff));
              /* if(leido < 1){//No contempla que este la pipe cerrada
                  write (STDOUT_FILENO, "Padre, Error al leer tuberia\n", sizeof("Padre, Error al leer tuberia\n"));
               }else {
                  write (STDOUT_FILENO, "Padre, Leido de la tuberia \"", sizeof("Padre, Leido de la tuberia \""));
                  write (STDOUT_FILENO, buff, leido-1);
                  printf("\" por el proceso padre\n.");
               }*/
               if(leido < 0){
                  write (STDOUT_FILENO, "Padre, Error al leer tuberia\n", sizeof("Padre, Error al leer tuberia\n"));
               }else{
                    if (leido == 0) {
                                    printf("El extremo de escritura de la tubería está cerrado por el proceso hijo.\n");
                                    break;//Sale del bucle de lectura
                                    } else { // Datos leídos correctamente
                                            write (STDOUT_FILENO, "Padre, Leido de la tuberia \"", sizeof("Padre, Leido de la tuberia \""));
                                            write (STDOUT_FILENO, buff, leido-1);
                                            printf("\" por el proceso padre\n.");
                                          }
               
                    }
            }

            close(ipc[0]);
            wait(NULL);
            wait(NULL);
            exit(0);
         break;
      }
   }   
}
