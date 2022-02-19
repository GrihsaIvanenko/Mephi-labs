all: lab1

lab1: main.o
	cc main.o -o lab1 -std=c11 -lreadline

main.o:
	cc -c main.c -std=c11 -lreadline

clean:
	rm -rf *.o
