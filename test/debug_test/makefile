debug: main.o debug.o
	gcc -o debug main.o debug.o

main.o: main.c
	gcc -g -O -c main.c debug.h

debug.o: debug.c
	gcc -g -O -c debug.c debug.h

.PHONY: clean

clean:
	rm -f *.o *~ core *~
