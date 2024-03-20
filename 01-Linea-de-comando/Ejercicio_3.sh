#!/bin/bash
mkdir /home/alejandro/Desktop/Ejercicio_rutas/ #se crea la carpeta
cd /home/alejandro/Desktop/Ejercicio_rutas/ #se ubaca dentro de la carpeta
mkdir /home/alejandro/Desktop/Ejercicio_rutas/fotos/ #se crea la carpeta fotos
mkdir /home/alejandro/Desktop/Ejercicio_rutas/videos/ #se crea la carpeta videos
mkdir /home/alejandro/Desktop/Ejercicio_rutas/documentos/ #se crea la carpeta documentos
wget https://github.com/td3-frm/practica/raw/master/01-linea-de-comando/Paul-Cezanne_Still-Life-With-Apples.jpeg #se descarga el archivo de imagen
mv Paul-Cezanne_Still-Life-With-Apples.jpeg fotos/
echo "" > 1342-0.txt
mv 1342-0.txt documentos/
mkdir /home/alejandro/Desktop/Ejercicio_rutas/backup/ #se crea la carpeta backup
pwd
cd /home/alejandro/Desktop/Ejercicio_rutas/documentos/
cp 1342-0.txt /home/alejandro/Desktop/Ejercicio_rutas/backup/ #se copia el archivo
