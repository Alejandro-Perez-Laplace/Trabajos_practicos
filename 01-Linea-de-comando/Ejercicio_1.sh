#!/bin/bash
alejandro@laplace:~/Desktop$ mkdir ejercicio_bash/ #se crea la carpeta
alejandro@laplace:~/Desktop$ ls #Comprobacion 
ejercicio_bash
alejandro@laplace:~/Desktop$ cd ejercicio_bash/ #se crea la carpeta ejercicio_bash
alejandro@laplace:~/Desktop/ejercicio_bash$ nano ejercicio.txt #se crea el archivo ejercicio_.txt
alejandro@laplace:~/Desktop/ejercicio_bash$ ls
ejercicio.txt
alejandro@laplace:~/Desktop/ejercicio_bash$ echo "Hola mundo " >  ejercicio.txt # se escribe en el archivo "Hola mundo"
alejandro@laplace:~/Desktop/ejercicio_bash$ cat ejercicio.txt #Se verifica el paso anterior
Hola mundo 
alejandro@laplace:~/Desktop/ejercicio_bash$ mkdir subcarpeta/ #se crea "subcarpeta"
alejandro@laplace:~/Desktop/ejercicio_bash$ ls # comprobacion
ejercicio.txt  subcarpeta
alejandro@laplace:~/Desktop/ejercicio_bash$ cp ejercicio.txt subcarpeta/	#se copia ejercicio.txt a subcarpeta
alejandro@laplace:~/Desktop/ejercicio_bash$ ls subcarpeta/ #comprobacion
ejercicio.txt
