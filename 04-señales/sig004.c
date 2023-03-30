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
int lvl=1;
pid_t pid1, pid2, pid3;
signal(SIGCHLD, sigchild_hdl);

pid1 = fork();
if(pid1 == 0){
	printf("Proceso hijo %d. PID = %d\n",lvl, getpid());
	
	while(1);
	}
		pid2 = fork();
		if(pid2 == 0){ 
		lvl++;
		printf("Proceso hijo %d. PID = %d\n",lvl, getpid());
		
		while(1);
		}
			pid3 = fork();
			if(pid3 == 0){ 
			lvl++;
			printf("Proceso hijo %d. PID = %d\n",lvl, getpid());
			
			while(1);
			}
				sleep(5);
				kill(pid1, SIGKILL);
				sleep(5);
				kill(pid2, SIGKILL);
				sleep(5);
				kill(pid3, SIGKILL);
				sleep(5);
			
sleep(5); 

exit(0);

}
