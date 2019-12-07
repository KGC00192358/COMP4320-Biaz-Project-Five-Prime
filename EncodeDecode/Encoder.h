unsigned char * serialize_request(unsigned char *buffer, char tml, char id, char op_code, int num_ops, short operand_one, short operand_two);
unsigned char * serialize_response(unsigned char *buffer, char tml, char id, char err0, int answer);

unsigned char * serialize_shrt(unsigned char * buffer, short value);
unsigned char * serialize_int(unsigned char * buffer, int value);
