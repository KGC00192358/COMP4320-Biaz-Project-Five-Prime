#include <stdlib.h>

int deserialize_int(unsigned char * buffer, int loc); 
short deserialize_shr(unsigned char * buffer, int loc);
char deserialize_char(unsigned char * buffer, int loc);
char * deserialize_substr(unsigned char * buffer, int begin, int end);

int deserialize_request(unsigned char *buffer, char tml, char id, char op_code, char num_ops, short operand_one, short operand_two);

int deserialize_response(unsigned char * buffer, char *tml, char * id, char *err0, int *answer);
