#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>

#define REQ_SIZE 8
#define RES_SIZE 7
#define PLUS_OP_CODE 0
#define MINS_OP_CODE 1
#define MULT_OP_CODE 2
#define DIVS_OP_CODE 3
#define SHFL_OP_CODE 4
#define SHFR_OP_CODE 5
#define NOTS_OP_CODE 6

#define TEST_PORT 8080
#define TEST_ADDR 127.0.0.1
#define MAXLINE 1024 

void printArray(unsigned char * buffer, int size);
