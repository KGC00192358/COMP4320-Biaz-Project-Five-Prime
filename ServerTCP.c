#include "ServerTCP.h"

/**
 * These are the all the variables for the connection set up.
 * server_fd, new_socket, valread
 *
 * */

int server_fd, client_socket_fd, valread, recv_len;
struct sockaddr_in address_struct, client_address_struct;
int opt = 1;
int addrlen = sizeof(address_struct);
// Driver code 

int die(char *s)
{
	perror(s);
	return EXIT_FAILURE;
}

int setUp(int port) {
	//create a TCP socket
	if ((server_fd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		return die("socket creation failed");
	}

	//set socket options
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		return die("socket options failed");	
	}

	// zero out the structure
	// just in case there is garbage
	memset((char *) &address_struct, 0, sizeof(address_struct));
		
	//Set up the address struct
	address_struct.sin_family = AF_INET;
	address_struct.sin_port = htons(port);
	address_struct.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to port
	if( bind(server_fd, (struct sockaddr*)&address_struct, sizeof(address_struct) ) == -1)
	{
		return die("bind failed");
	}
	return 0;
}
int waitForConnection() {
	//wait for a connection request
	//THIS IS A BLOCKING CALL
	if(listen(server_fd, 3) < 0) {
		die("Listening failed");
		return EXIT_FAILURE;
	}
	printf("Establishing Connection...\n");
	if ((client_socket_fd = accept(server_fd, (struct sockaddr *)&address_struct, (socklen_t *)&addrlen)) < 0) {
		die("Accept Failed");
		return EXIT_FAILURE;	
	}
	printf("Connection established\n");
	return 0;
}


void sendAndRec() {
	while(1)
	{
		printf("Waiting for data...");
		fflush(stdout);

		unsigned char incoming_request_header[REQ_SIZE];
		unsigned char outgoing_response_header[RES_SIZE];
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(client_socket_fd, incoming_request_header, REQ_SIZE, 0, (struct sockaddr *) &client_address_struct, (socklen_t * )&addrlen)) == -1)
		{
			die("recvfrom()");
		}
		int answer = performCalculation(incoming_request_header);
		char err0 = 0;
		char size = deserialize_char(incoming_request_header, 0);
		char id = deserialize_char(incoming_request_header, 1);
		if (size != sizeof(incoming_request_header)) {
			err0 = 127;
		}
		unsigned char * outgoing_answer = serialize_response(outgoing_response_header, RES_SIZE, id, err0, answer);
		//print details of the client/peer and the data received
		
		printf("Sending Out this packet: ");
		printArray(outgoing_response_header, RES_SIZE);

		//now reply the client with the same data
		if (sendto(client_socket_fd, outgoing_answer, RES_SIZE, 0, (struct sockaddr*) &client_address_struct, addrlen) == -1)
		{
			die("failed");
		}
	}


}

int performCalculation(unsigned char * buffer) {
	int ret = 0;
	short operand_one = deserialize_shr(buffer, 4);
	short operand_two = deserialize_shr(buffer, 6);
	const char operation = deserialize_char(buffer, 2);
	printf("Operation Code: %i\n", operation);
	printf("Operand One: %i\n", operand_one);
	printf("Operand Two: %i\n", operand_two);
	switch (operation) {
		case (0) :
			ret = operand_one + operand_two;
			break;
		case (1) :
			ret = operand_one - operand_two;
			break;
		case (2) :
			ret = operand_one * operand_two;
			break;
		case (3) :
			ret = operand_one / operand_two;
			break;
		case (4) :
			ret = operand_one >> 1;
			 break;
		case (5) :
			 ret = operand_one << 1;
			 break;
		case (6) :
			 ret = ~operand_one;
	}
	printf("Answer: %i\n", ret);
	return ret;
}
int main(int argc, char const *argv[])
{
	if(argc < 2) {
		die("Syntax is: \'Server [port]\'");
	}

	

	if (setUp(atoi(argv[1])) == EXIT_FAILURE) {
		exit(EXIT_FAILURE);
	}
	if (waitForConnection() == EXIT_FAILURE) {
		exit(EXIT_FAILURE);
	}

	sendAndRec();
	close(server_fd);
	return 0;
}
