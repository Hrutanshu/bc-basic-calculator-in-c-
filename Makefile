all: project
project: infix.o stack.o functions.o
	gcc infix.o stack.o functions.o -o project
stack.o: stack.c stack.h
	gcc -c stack.c
functions.o: functions.c bc.h
	gcc -c functions.c
infix.o: infix.c stack.h
	gcc -c infix.c 
