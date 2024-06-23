/*  
 * Ejercicio 1 del TP Hilos
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *hola(void * nro) {
  
   sleep(2);
   printf("Hola, soy el hilo %d\n", * (int*) nro);
   pthread_exit(NULL);
   //exit(0);

}

int main() {

    pthread_t hilo[1];
    int rc, t;

    t = 0;
     
    printf("Main creando el hilo nro %d\n", t);
        
    rc = pthread_create(&hilo[0], NULL, hola , (void *)(&t)  );
//Algunos de los atributos que comparten los hilos son:
//• ID del proceso. 
//• ID del proceso padre.
//• Descriptores de archivos abiertos.
//• Credenciales de proceso  (usuario y ID de grupo).
//Algunos de los atributos que no comparten los hilos son:
//• ID de hilos (TID).
//• Datos específicos del hilo.
//• Pila del hilo.
     
    if (rc != 0){
         printf("ERROR; pthread_create() = %d\n", rc);
         exit(-1);        
         };
//La creación del hilo es más rápida que la creación de un proceso (típicamente entre x10 y x100 más rápido). 
  
//Generalmente es necesario implementar mecanismos de 
//sincronización (mutex, semáforos) para que los hilos trabajen 
//correctamente en forma colaborativa.

   printf("Espera a que termine hilo\n");

   pthread_join(hilo[0],NULL);

   printf("Termina hilo main\n");

   pthread_exit(NULL);
   
   return 0;
}
