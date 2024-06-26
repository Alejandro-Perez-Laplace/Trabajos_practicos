/*
* Ejercicio 2 del TP de Cola de mensajes
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define MENSAJE "DATA PARA PROCESO"
#define MQ_PATH "/MQ_TD3" 

int err, leido;
char buff[1024];   
mqd_t mqd; 
struct mq_attr attr, attr_rcv;

void sig_user1(int a){
   
	err = mq_close(mqd);
	if (( err < 0 )){
		write(STDOUT_FILENO, "error en mq_close()\n", sizeof("error en mq_close()\n"));
		exit(-1);   }

	write(STDOUT_FILENO, "Cola de mensajes cerrada\n", sizeof("Cola de mensajes cerrada\n"));

	err = mq_unlink(MQ_PATH);
	if(err == -1){
        write(STDOUT_FILENO, "error en mq_unlink()\n", sizeof("error en mq_unlink()\n"));
		exit(-1);    }

	write(STDOUT_FILENO, "Cola de mensajes eliminada\n", sizeof("Cola de mensajes eliminada\n"));

	write(STDOUT_FILENO, "Terminando proceso...\n", sizeof("Terminando proceso...\n"));
   
	exit(0);
}

int main() {
   
	signal(SIGUSR1, sig_user1);

	printf ("Mi pid es %d\n", getpid());

	attr.mq_msgsize = sizeof(buff);
	attr.mq_maxmsg = 8;

	mqd = mq_open(MQ_PATH, O_RDONLY | O_CREAT, 0666, &attr); 
	if (mqd < 0) {
		printf ("error en mq_open()\n");      
		exit(-1) ;}

		printf("Cola de mensajes creada\n");
   
	while(1) {
      
		err = mq_send(mqd, MENSAJE, strlen(MENSAJE)+1, 1);  // strlen nos da la longitud de una cadena
		if(err == -1){
			printf ("error en mq_send()\n");
			exit(-1);}
 
		printf("Mensaje enviado (%d)\n", err);

		sleep(2);
	}

	exit(0);
}
