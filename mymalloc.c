#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
static char myblock[4096]; //Initialize the data

struct node
{
//# of bytles until next node/end of memory
unsigned short int size;
//# of bytes allocated with malloc
unsigned short int used;

};
//Setup Node0 here

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


 
void* mymalloc(size_t bytes, char* fileName, int line) {

	//Malloc of 0 bytes should result in NULL
	//Can return null since it is a void pointer
	
	//need a way to see if it is the first time called
	//not sure if this works, check later	 
	static int called = 0; 	

	if (bytes == 0)
		{
		return NULL; 	
		}

	if (bytes < 0 )
		{
		//ERROR Do stuff
		
		}
//	static struct node *first;
	static struct node *first;	
	//if first time called
	if (called == 0){
		
		//create the first node at the start of the memory
		first = (struct node*) myblock;
		first->size = 4096;
		printf("size aka: %d", first->size);			
	}

	
	
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
