all: memgrind.c myalloc.o 
	gcc memgrind.c mymalloc.o

myalloc.o: myalloc.c
	gcc -c mymalloc.c

clean:
	rm a.out; rm mymalloc.o
