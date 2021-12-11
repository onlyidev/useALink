main: main.c htmlFunctions.h
	gcc -xc -Wall -pedantic main.c -o main

remove:
	rm main

exec: main
	./main