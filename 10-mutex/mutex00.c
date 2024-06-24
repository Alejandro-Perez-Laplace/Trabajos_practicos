/* Ejercicio 1 del TP mutex: uso de mutex */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/* Variables Globales */
int t,total,s ; 

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; // inicializacion estatica del mutex


void *HILO0(void *nro) {

/* Variables Locales*/
int numero;

	numero= *(int*)nro;
	
	s=pthread_mutex_lock(&mtx); //Bloqueo del Mutex: El hilo intenta bloquear el mutex mtx para asegurar el acceso exclusivo a la variable total.
   	if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);   }

   	total=total+numero;//Operación Segura: Imprime el valor de total, lo modifica sumando numero y lo imprime nuevamente.
   	printf("Hilo 0, recibe nro=%d, total= %d\n",numero, total);

   	s=pthread_mutex_unlock(&mtx); //Desbloqueo del Mutex: Libera el mutex para que otros hilos puedan acceder a la variable total.
   	if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);    }

   	pthread_exit(NULL);
   	
}

int main() {

/* Variables Locales*/
pthread_t hilo;
int rc ;

	total=20;
	t=5;

	printf("Total= %d\n",total);
 
	printf("Main crea a hilo 0\n");
    
	rc = pthread_create(&hilo, NULL, HILO0 , (void *)&t  ); //Creación del Hilo: El hilo HILO0 se crea y se le pasa el valor de t como parámetro.
	if (rc){
       printf("ERROR; pthread_create() = %d\n", rc);//Bloqueo del Mutex: El hilo intenta bloquear el mutex mtx para asegurar el acceso exclusivo a la variable total.
       exit(-1);    }

	s=pthread_mutex_lock(&mtx);  
	if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);   }

	total=total+t;

	s=pthread_mutex_unlock(&mtx);  //Desbloqueo del Mutex: Libera el mutex para que otros hilos puedan acceder a la variable total.
	if (s!=0){
      printf("ERROR; pthread_mutex() = %d\n", s);
      exit(-1);    }
 
 	pthread_join(hilo,NULL); //espero al hilo

	printf("Total final= %d\n",total);

	pthread_exit(NULL);
	
}

