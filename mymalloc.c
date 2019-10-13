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
		//setup of metadata
		printf("node0 is NULL, setting up\n");
		node0 = (metadata*)myblock;
		node0->used = 0;
		node0->size = 4096 - sizeof(metadata);
		printf("Data starts at %x and ends at %x\n", node0, (void*)node0 + 4096 - sizeof(metadata));
	}

	printf("Attempting to allocate %zu bytes\n", bytes);
	if (bytes == 0) //allocating 0 bytes, return NULL
	{
		printf("\tReturning NULL, allocated 0 bytes\n"
		"\tFile: %s, Line:%d" , fileName, line);
		return NULL; 	
	}
	//Allocating a value greater than max size also stops cases when size_t is smaller then casting
	if (bytes > (size_t)(4096 - sizeof(metadata)))
	{
		printf("\tReturn NULL, no space\n"
		"\tFile: %s, Line:%d" , fileName, line);
		return NULL;
	}
	//Note: size_t is an unsigned decimal, cannot be negative
	
	metadata* currentNode = node0;
	printf("\tStarting allocate from %x\n", currentNode);
	while (1)
	{	//make sure size of currentNode is greater than or equal to how much is being allocated
		if (currentNode->size >= (unsigned short)bytes)
		{
			//Current node has enough space to allocate
			//when will this not be 0? 
				//when it is not the first time allocating 
			if (currentNode->used == 0) 
			{
				currentNode->used = (unsigned short)bytes;
				
				printf("\t%x is an empty node, allocating %d bytes\n",
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

				printf("\t%x is used, but has enough space, so created new node at %x with %d\n",
					currentNode,
					newNode,
					used
				);

				//Resize currnetNode to 
				currentNode->size = currentNode->used;
				return (void*)newNode + sizeof(metadata); //return pointer to data for newNode
			}
			printf("\tFull: ");
		} else {
			printf("\tToo Small: "
			"\tFile: %s, Line:%d" , fileName, line);
		}
		//Current node is too small or big enough, but too full, continue to next node

		//Next node cannot exist, no space
		if ((void*)currentNode + currentNode->size > (void*)myblock + 4096 - (unsigned short)bytes - sizeof(metadata))
		{
			printf("\tReturning NULL, no more space\n"
			"\tFile: %s, Line:%d" , fileName, line);
			return NULL;
		}

		//Change current to next node
		printf("%x is unavailable with size %d, continuing to ", currentNode, currentNode->size);
		currentNode = (metadata*)((void*)currentNode + sizeof(metadata) + currentNode->size);
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
//Node 1 is before it's being freed
//Node 2 is the one being freed
//Node 3 is after the one being freed

void myfree(void* ptr, char* fileName, int line) {
	
	if(ptr == NULL ) {
		//error print something
		return; 
		}

	if(ptr < (void*)node0 + sizeof(metadata) ) {
		
		//error print something
		//invalid pointer??
		return;
		}
	printf("\t IS SOMETHING HAPPENING?? \n"
					"\tFile: %s, Line:%d" , fileName, line);	
			
	//metadata of node to be freed 
	metadata* node2 = ptr - sizeof(metadata);

	metadata* currentNode = node0;  
 	metadata* node1 = currentNode; 
	metadata* node3; 
	
	//change this
	printf("Number bytes being freed are %d\n",currentNode->used);


	/*
	//check this again (may not be proper error message) 
	if(currentNode->used == 0) {
	printf("\terror: User is trying to free something more than once\n"
					"\tFile: %s, Line:%d" , fileName, line);

	}
*/ 


	//if node0 doesn't exist
	if(currentNode==NULL){ 
	
		printf("error: No data has been allocated");	
		return;
	} 
			
	
	printf("\tfree: %d\n",node0->used);
		
	//may be beneficial to change this later
	while(1) {
		//nodes index is outside of the given memory
		//IF STATEMENT CHECK THIS 
		if( (void*)currentNode > (void*)myblock + 4096 ){
			printf("\terror: User is trying to free a node that doesnt exist\n"
					"\tFile: %s, Line:%d" , fileName, line);	
			
			return; 
			}
	
		//if we came across the  node 
		if (currentNode == node2) {
			break;

		// maybe we should set the next node? 
			}
		
		//passed the node2	
		if (currentNode>node2){
			printf("\terror: User is trying to free a node that doesnt exist\n"
					"\tFile: %s, Line:%d" , fileName, line);
			
			return;
			}  	

			

		//lagging node
		node1=currentNode;		
	
		//move onto the next node 
		currentNode = (void*)currentNode + currentNode->used + sizeof(metadata); 
		
		
		
	}

	//get node 3 if it exists	
	if((void*)node2 + sizeof(metadata) + node2->size < (void*)myblock+4096 - sizeof(metadata)) {
			
		node3 = (void*)node2 + node2->used + sizeof(metadata); 	
		//printf("yeee HAW %d ", node3->used); 	
	} 
	
	//if node3 exists
	if (node3!=NULL){
		if(node3->used == 0){
		//erase node 3 and merge into node 2

		//merge
		node2->size = node2->size + node3->size + sizeof(metadata); 
		node2->size = node2->used + node3->used + sizeof(metadata);
		}
		
		node3 = NULL;
	}
	
	//if our node isn't the first node
	if (node1!=node2){
		//printf("gang gang out here");
		
		if(node1->used == 0){
			//erase node2 and merge into node1 
			
			//merge
			node1->size = node1->size + node2->size + sizeof(metadata);	
			node1->used = node1->used + node2->used + sizeof(metadata); 
			
			//erase
			node2 = NULL;				
				
			}
			 	
		}
	
	else{
		//node before and after not available
		node2->used = 0;
	
	}


}
