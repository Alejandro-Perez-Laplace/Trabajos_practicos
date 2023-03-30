/*
 * TP Señales, Ejercicio 6 
*/
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

void sigchild_hdl (int a){
write(STDOUT_FILENO, "\nTermino hijo\n", sizeof("\nTermino hijo"));
}
int main (){

pid_t pid1, pid2, pid3;
signal(SIGCHLD, sigchild_hdl);

pid1 = fork();
if(pid1 == 0){
	printf("Proceso hijo 1. PID = %d\n", getpid());
	while(1);
	}
	else
	{
		pid2 = fork();
		if(pid2 == 0){ 
		printf("Proceso hijo 2. PID = %d\n", getpid());
		while(1);
		}
		else
		{
			pid3 = fork();
			if(pid3 == 0){ 
			printf("Proceso hijo 3. PID = %d\n", getpid());
			while(1);
			}
			else
			{
				sleep(2);
				kill(pid1, SIGKILL);
				sleep(2);
				kill(pid2, SIGKILL);
				sleep(2);
				kill(pid3, SIGKILL);
				sleep(2);
			}
		}
	}
sleep(5); 

exit(0);

}
