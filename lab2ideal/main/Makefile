staticlist: mainlist readline.o inputOutput.o
	cc main.o inputOutput.o readline.o -o lab2 -std=c11 -L../listlib -llist1

staticvector: mainvector readline.o inputOutput.o
	cc main.o inputOutput.o readline.o -o lab2 -std=c11 -L../vectorlib -lvector1

dynamiclist: mainlist readline.o inputOutput.o
	cc main.o inputOutput.o readline.o -o lab2 -std=c11 -L../listlib -llist2 -Wl,-rpath,../listlib

dynamicvector: mainvector readline.o inputOutput.o
	cc main.o inputOutput.o readline.o -o lab2 -std=c11 -L../vectorlib -lvector2 -Wl,-rpath,../vectorlib

readline.o:
	cc -c readline.c

inputOutput.o:
	cc -c inputOutput.c

mainlist:
	cc -c main.c

mainvector:
	cc -c main.c -DVECTOR

clean:
	rm -rf *.o