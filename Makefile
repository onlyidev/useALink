main: main.c htmlFunctions.h
	gcc -xc -Wall -pedantic -ansi -std=c99 main.c -o main

remove:
	rm main

exec: main
	./main
