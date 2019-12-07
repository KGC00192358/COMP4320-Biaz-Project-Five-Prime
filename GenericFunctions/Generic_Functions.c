#include "Generic_Functions.h"

void printArray(unsigned char * buffer, int size) {
	int i  = 0;
	printf("|");
	for(i = 0; i < size; ++i) {
		printf("%i|", buffer[i]);
	}
	printf("\n");	
}
