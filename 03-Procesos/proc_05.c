/*
 * Ejercicio 5 de TP Procesos
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

pid_t pid;

int main (){

    printf ("Unico proceso antes del fork(), con pid %d\n ",getpid());
	
	pid = fork();

//---- ejemplo de switch ---------------------------	
    switch (pid ) {//Es la mejor opcion para ejecutar los procesos padre e hijo por separado, solo con una funcion se determina las operaciones a realizar
           
    case -1:
        printf ("Error. No se crea proceso hijo");
        return -1;
        break ;

    case 0:
        printf("_switch: Soy el hijo: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
	   	break ;

    default:
        printf("switch: Soy el padre: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
        break ;
   }    

//----fin ejemplo de switch ---------------------------	

//acá llegan todos los procesos

//---- ejemplo de if ----------------------------------	
//Se necesita mas de una funcion realizar todas las posibilidades de la generacion de proceso
	if(pid==-1){
	            printf ("Error. No se crea proceso hijo");
                    return -1;
	            }
	            else{
	    if (pid==0) { 	//hijo	
		    printf("_if: Soy el hijo: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);

	                }else {//Padre
		    printf(" if: Soy el padre: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
	                      }
	    }//Falta en el caso que no se crea el proceso hijo

//---- fin ejemplo de if ----------------------------------	

//acá llegan todos los procesos


    	
//---- ejemplo de while ----------------------------------
       
       while(pid<0)//Se necesitan tres oporadores para todas las posibilidades 
              {
              printf ("Error. No se crea proceso hijo");
              return -1;
              }
        while(pid==0)
              {
              printf("_While: Soy el hijo: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
              return -1;
              }      
        while(pid>0)
              {
	      printf(" While: Soy el padre: %d, mi papa es: %d, fork() devolvio %d\n", getpid(),getppid(),pid);
	      return -1;
	      }
//---- fin ejemplo de while ----------------------------------	

//---- ejemplo de for ----------------------------------
       /* int b;
        for(a=-1;a=pid;a++)
        {
          
        }*/
//---- fin ejemplo de for ----------------------------------
        exit(0);
}


