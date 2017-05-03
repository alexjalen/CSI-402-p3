p3: main.o initialize.o queryFile.o error.o
	gcc main.o initialize.o queryFile.o error.o -o p3
main.o: main.c headers.h prototypes.h
	gcc -c main.c
initialize.o: initialize.c headers.h prototypes.h
	gcc -c initialize.c
queryFile.o: queryFile.c headers.h prototypes.h
	gcc -c queryFile.c
error.o: error.c
	gcc -c error.c
clean:
	rm -f *.o core p3
