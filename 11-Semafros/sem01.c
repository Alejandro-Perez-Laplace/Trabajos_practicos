/* Ejercicio 1 del TP de semaforos sin nombre */

//---------------- Uso de semáforos sin nombre ----------------//

#include <stdio.h>
#include <pthread.h>    
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

//------- variables globales

pthread_t hilo[2];//hilo: Un arreglo de hilos (en este caso, se usa solo el primer hilo).
sem_t sem;//sem: Un semáforo sin nombre que será utilizado para la sincronización.


//---------------- Hilo ---------------------------//

void *HILO(){
int s;

	sleep(3);
	
	printf ("Soy el HILO voy a incrementar semaforo\n");

//------ Se incrementa sem 
	s=sem_post(&sem);//Incrementa el semáforo, señalando que está disponible.
	if (s != 0) {
		printf("ERROR sem_post()\n");
		exit(-1);     }
	
	pthread_exit (NULL);//Termina la ejecución del hilo.

}

//-----------------------------------------------------------//

int main() {
	
	int s,sval,rc;
	
	printf ("Main crea el semaforo\n");

//------ inicializa el sem sin nombre 
	s=sem_init(&sem, 0, 0);//Inicializa el semáforo sin nombre sem con un valor inicial de 0. El segundo parámetro 0 indica que el semáforo es compartido entre hilos en el mismo proceso.
	if (s != 0) {
		printf("ERROR sem_init()\n");
		exit(-1);     }

//------lee valor de sem 
	sem_getvalue(&sem, &sval);//Obtiene el valor actual del semáforo y lo almacena en sval. Imprime el valor del semáforo.
	printf("Valor de semaforo: %d\n",sval);

//------ Crea los hilos 
	rc = pthread_create (&hilo[0], NULL, HILO, NULL);//Crea un hilo que ejecuta la función HILO.
	if (rc)    {
		printf ("ERROR; pthread_create() = %d\n", rc);
		exit (-1);    }
	
	printf ("Soy el main voy a decrementar semaforo\n");

//------decremento de sem
	s = sem_wait(&sem);//Decrementa el semáforo, bloqueando si el valor del semáforo es 0 hasta que otro hilo lo incremente (lo que ocurre en HILO).
	if (s != 0) {
		printf("ERROR sem_wait()\n");
		exit(-1);     }

//------elimina de sem
	printf("Se elimina el semaforo\n");
	s=sem_destroy(&sem);//Destruye el semáforo, liberando cualquier recurso asociado.
	if (s != 0) {
		printf("ERROR sem_unlink()\n");
		exit(-1);  }

//--------------------------------------------
   
	pthread_join (hilo[0], NULL);
	
	printf("Fin del main() \n");
	
	pthread_exit (NULL);

}

