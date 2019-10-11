#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
static char myblock[4096]; //Initialize the data

//Format for metadata before each allocated data in myblock
typedef struct metadata
{
	//# of bytles until next node/end of memory
	unsigned short int size;
	//# of bytes allocated with malloc
	unsigned short int used;
} metadata;
metadata* node0;

/* Malloc function
 * Scans starting from 0
 * 	if size >= bytes (if current node is big enough)
 * 		if used == 0 (if current node is open)
 * 			set used to bytes
 * 			return pointer to node + metadataSize
 * 		else if size - used >= bytes + metadataSize (if enough space to squeeze new node before next node)
 * 			new node is at currentPosition + metadataSize + used
 * 			set new metadata to have size = size - used - metadataSize
 * 			set new metadata to have used = bytes
 * 			set current metadata to have size = used
 * 			return pointer to new node + metadataSize
 * 		else (if not enough space between current and next node)
 * 			if next node, continue to next node
 * 			else (if no more space)
 * 				return NULL
 * 	else
 * 		if next node, continue to next node
 * 		else (if no more nodes)
 * 			return NULL
 */
void* mymalloc(size_t bytes, char* fileName, int line)
{
	//Setup Node0 if NULL
	if (node0 == NULL)
	{
		printf("node0 is NULL, setting up\n");
		node0 = (metadata*)myblock;
		node0->used = 0;
		node0->size = 4096 - sizeof(metadata);
	}

	printf("Attempting to allocate %zu bytes\n", bytes);
	if (bytes == 0) //allocating 0 bytes, return NULL
	{
		printf("\tReturning NULL, allocated 0 bytes\n");
		return NULL; 	
	}
	//Allocating a value greater than max size also stops cases when size_t is smaller then casting
	if (bytes > (size_t)(4096 - sizeof(metadata)))
	{
		printf("\tReturn NULL, no space\n");
		return NULL;
	}
	//Note: size_t is an unsigned decimal, cannot be negative
	
	metadata* currentNode = node0;
	printf("\tStarting allocate from %x\n", currentNode);
	while (1)
	{
		if (currentNode->size >= (unsigned short)bytes)
		{
			//Current node has enough space to allocate
			if (currentNode->used == 0) 
			{
				currentNode->used = (unsigned short)bytes;
				
				printf("\t%x is an empty node, allocating space\n",
					(void*)currentNode + sizeof(metadata),
					(unsigned short)bytes
				);
				return (void*)currentNode + sizeof(metadata);
			}

			//Current node is used, but still has enough space
			if (currentNode->size - currentNode->used >= (unsigned short)bytes + sizeof(metadata))
			{
				unsigned short size = currentNode->size - currentNode->used - sizeof(metadata);
				unsigned short used = (unsigned short)bytes;

				//Create newNode right after used data for currentNode
				void* newNode = (void*)currentNode + sizeof(metadata) + currentNode->used;
				((metadata*)newNode)->size = size;
				((metadata*)newNode)->used = used;

				printf("\t%x is used, but has enough space, so created new node at %x\n",
					currentNode,
					newNode);

				//Resize currnetNode to 
				currentNode->size = currentNode->used;
				return (void*)newNode + sizeof(metadata); //return pointer to data for newNode
			}
		}
		//Current node is too small or big enough, but too full, continue to next node

		//Next node cannot exist, no space
		if ((void*)currentNode == (void*)myblock + 4096)
		{
			printf("\tReturning NULL, no more space\n");
			return NULL;
		}

		//Change current to next node
		printf("\t%x is unavailable, continuing to ", currentNode);
		currentNode = (metadata*)((void*)currentNode + currentNode->size + sizeof(metadata));
		printf("%x\n", currentNode);

		//continue to check next node
	}

	return NULL; //Never occurs, idk if we need to leave this here
}

/* Free function
 * backtrack from ptr to get metadata of node to be freed, Node1
 * Scan starting from 0
 * 	if next node's index is the outside of the given memory
 * 		error: User is trying to free a node that doesnt exist
 * 	if next node's index is Node1's, save current position as Node0
 * 	if next node's index is after Node1's
 * 		error: User is trying to free a node that doesnt exist
 * get node after Node1, Node2, if it is not the end of memory
 *
 * set currentNode to Node1
 * if Node2 exists and has used=0 (erase node2 and merge into node1)
 * 	set Node1.size to Node1.size + metadataSize(of Node2) + Node2.Size
 * if Node0 has used=0 (erase node1 and merge into node0)
 * 	set currentNode to Node0
 * 	set Node0.size to Node0.size + metadataSize(of Node1) + Node1.Size
 */
void myfree(void* ptr, char* fileName, int line) {
	
}
