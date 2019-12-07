// Client side implementation of UDP client-server model #include "ClientTCP.h"
#include "ClientTCP.h"
// Driver code 

struct sockaddr_in server_address_struct;
int s;
unsigned int slen=sizeof(server_address_struct);
char id = 0;

int die(char *s)
{
	perror(s);
	return -1;
}

int setUpAndConnect(int port, char const *address) {
	if ( (s=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		return die("socket creation failure");
	}

	memset((char *) &server_address_struct, 0, sizeof(server_address_struct));
	server_address_struct.sin_family = AF_INET;
	//server_address_struct.sin_addr = inet_addr("127.0.0.1");
	server_address_struct.sin_port = htons(port);

	if (inet_pton(AF_INET, address, &server_address_struct.sin_addr) <= 0) 
	{
		fprintf(stderr, "inet_pton() failed\n");
		return -1;
	}
	
	if (connect(s, (struct sockaddr *)&server_address_struct, sizeof(server_address_struct)) < 0) {
		return die("Connection failed");
	}
	return 0;
}

unsigned char * generateRequest(unsigned char * buffer) {
	char op_code;
	char num_ops;
	short operand_one;
	short operand_two = 0;
	char msg_in[MAXLINE];
	printf("Enter operation (+ - * / >> << ~)");
	fgets(msg_in, MAXLINE, stdin);
	const char op_check = msg_in[0]; 
	switch (op_check) {
		case('+') :
			op_code = PLUS_OP_CODE;
			num_ops = 2;
			break;
		case('-') :
			op_code = 1;
			num_ops = 2;
			break;
		case('*') :
			op_code = 2;
			num_ops = 2;
			break;
		case('/') :
			op_code = 3;
			num_ops = 2;
			break;
		case('>') :
			op_code = 4;
			num_ops = 1;
			break;
		case('<') :
			op_code = 5;
			num_ops = 1;
			break;
		case('~') :
			op_code = 6;
			num_ops = 1;
			break;
		default:
			op_code = op_check;
			num_ops = '3';
			break;	
	}
	memset(msg_in, '\0', MAXLINE);
	printf("Enter operand_one: ");
	fgets(msg_in, MAXLINE, stdin);
	operand_one = atoi(msg_in);
	if (num_ops == 2) {
	printf("Enter operand_two: ");
	fgets(msg_in, MAXLINE, stdin);
	operand_two = atoi(msg_in);
	}
	return serialize_request(buffer, REQ_SIZE, ++id, op_code, num_ops, operand_one, operand_two);


}

void sendAndRec(){
	while(1)
	{
		unsigned char buf[MAXLINE];
		unsigned char outcoming_request_header[REQ_SIZE];
		unsigned char * out = generateRequest(outcoming_request_header);
		unsigned char incoming_response_header[RES_SIZE];

		//send the message
		if (sendto(s, out, REQ_SIZE , 0 , (struct sockaddr *) &server_address_struct, slen)==-1)
		{
			die("sendto()");
		}

		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', MAXLINE);
		//receive a reply and print it
		//try to receive some data, this is a blocking call
		if (recvfrom(s, incoming_response_header, RES_SIZE, 0, (struct sockaddr *) &server_address_struct, &slen) == -1)
		{
			die("recvfrom()");
		}
		int answer = deserialize_int(incoming_response_header, 3);
		char idIn = deserialize_char(incoming_response_header, 1);

		memset(outcoming_request_header, '\0', REQ_SIZE);

		printf("Header recieved from server: ");
		printArray(incoming_response_header, RES_SIZE);
		printf("\n");


		printf("Answer for request with Id %i: %i\n", idIn, answer);
	}
}



int main(int argc, char const *argv[])
{

	if(argc < 3) {
		printf("Syntax is: \'Client [server address] [port]\'\n");
		die("insufficient parameters");
	}

		if (setUpAndConnect(atoi(argv[2]), argv[1]) < 0) {
			exit(EXIT_FAILURE);
	}


	sendAndRec();
	close(s);

	/*while(1) {
	unsigned char intBuffer[4];
	printf("enter val: ");
	fgets(message, MAXLINE, stdin);
	int value = atoi(message);
	printf("value: %i\n", value);
	unsigned char * out = serialize_int(intBuffer, value);
	printArray(out, 4);
	int recieInt = deserialize_int(out, 0);
	printf("Got: %i\n", recieInt);
	}*/
	
	return 0;
}
