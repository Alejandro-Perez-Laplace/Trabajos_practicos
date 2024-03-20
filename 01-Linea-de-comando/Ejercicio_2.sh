#!/bin/bash
mkdir /home/alejandro/Desktop/Ejercicio_bash_avanzado/ #se crea la carpeta
cd /home/alejandro/Desktop/Ejercicio_bash_avanzado/ #se ubaca dentro de la carpeta
wget https://github.com/td3-frm/practica/raw/master/01-linea-de-comando/hola.zip #descaga el archivo
unzip hola.zip
mv hola.c hola-mundo.c #cambia el nombre
nano hola-mundo.c
make hola-mundo.c #compila el programa
ls
./hola-mundo #ejecuta 
