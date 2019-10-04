Malloc Project Systems Programming

testplan.txt - details the two workloads
mymalloc.h - malloc headers and definitions
mymalloc.c - implement functions
memgrid.c - test the functions
Makefile - builds and cleans memgrind

The data is stored in a 4096 byte array as a linked list

The first item starts at 0+(size of metadata)
The first item's metadata starts at 0

The metadata stores only the size of the data
	You can get the next metadata with:
		index = indexOfMetadata + sizeOfMetadata + sizeOfData;
