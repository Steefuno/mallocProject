#include <stdio.h>
#include <stdlib.h>

char data[4096]; //Initialize the data

/* Malloc function
 * Scans starting from Node0
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
void* mymalloc(int bytes, int line, char* fileName) {
	
}

/* Free function
 * 
 */
void free(void* ptr, int line, char* fileName) {
	
}
