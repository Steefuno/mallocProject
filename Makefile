all: memgrind.c myalloc.o 
	gcc memgrind.c myalloc.o

myalloc.o: myalloc.c
	gcc -c myalloc.c

clean:
	rm a.out; rm myalloc.o
