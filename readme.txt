Malloc Project Systems Programming

testplan.txt - details the two workloads
mymalloc.h - malloc headers and definitions
mymalloc.c - implement functions
memgrid.c - test the functions
Makefile - builds and cleans memgrind

The data is stored in a 4096 byte array as a linked list

The first item starts at 0+(size of metadata)
The first item's metadata starts at 0

Metadata group with the data will be referred to as a Node 
The metadata stores the size of the data and the size of used data
	node.size is the # of bytes until the next node or the end of the memory
	node.used is the # of bytes allocated with malloc
	both values are stored as unsigned short ints (0 to some number above 65k)

	You can get the next metadata with:
		index = indexOfMetadata + sizeOfMetadata + size;
	You can get the next open space for a used node with:
		index = indexOfMetadata + sizeOfMetadata + used;
	used is 0 in an open node
