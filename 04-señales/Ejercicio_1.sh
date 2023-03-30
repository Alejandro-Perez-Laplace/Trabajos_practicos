#!/bin/bash
alejandro@laplace:~/Desktop/TDIII/practica/04-señales$ gcc -o sig001 sig01.c
alejandro@laplace:~/Desktop/TDIII/practica/04-señales$ ./sig01
# bash: ./sig01: No such file or directory ##
alejandro@laplace:~/Desktop/TDIII/practica/04-señales$ >echo $? # Se revisa como termino el programa
# 127: command not found
alejandro@laplace:~/Desktop/TDIII/practica/04-señales$ ./sig01
# bash: ./sig01: No such file or directory
alejandro@laplace:~/Desktop/TDIII/practica/04-señales$ ^C # Se revisa como termino el programa
alejandro@laplace:~/Desktop/TDIII/practica/04-señales$ >echo $?
# 130: command not found
