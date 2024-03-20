#!/bin/bash
mkdir /home/alejandro/Desktop/Ejercicio_bash/ #se crea la carpeta
ls /home/alejandro/Desktop/ #Comprobacion 
cd /home/alejandro/Desktop/Ejercicio_bash/ #se ubaca dentro de la carpeta
ls
echo "Hola mundo " >  ejercicio.txt # se crea y escribe en el archivo "Hola mundo"
cat ejercicio.txt #Se verifica el paso anterior si hay un "Hola mundo"
mkdir subcarpeta/ #se crea "subcarpeta"
ls # comprobacion por consola
cp ejercicio.txt subcarpeta/	#se copia ejercicio.txt a subcarpeta
ls subcarpeta/ #comprobacion
