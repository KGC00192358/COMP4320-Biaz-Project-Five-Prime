#include "Decoder.h"
int deserialize_int(unsigned char * buffer, int loc) {
	int value = buffer[loc] << 24;
	value += buffer[loc+1] << 16;
	value += buffer[loc+2] << 8;
	value += buffer[loc+3];
	return value;
}
short deserialize_shr(unsigned char * buffer, int loc) {
	short value = buffer[loc] << 8;
	value += buffer[loc +1];
	return value;
}

char deserialize_char(unsigned char * buffer, int loc) {
	char ret = buffer[loc];
	return ret;
}	

/*char * deserialize_substr(unsigned char * buffer, int begin, int end) {
	char * substring = malloc(end - begin + 1);
	int i=begin, loc = 0;
	while(i < end) {
		substring[loc] = buffer[i];
		++i;
		++loc;
	}
	substring[end - begin] = '\0';
	return substring;

}*/	



int deserialize_request(unsigned char * buffer, char tml, char id, char op_code, char num_ops, short operand_one, short operand_two) {
	tml = deserialize_char(buffer, 0);
	id = deserialize_char(buffer, 1);
	op_code = deserialize_char(buffer, 2);
	num_ops = deserialize_char(buffer, 3);
	operand_one = deserialize_shr(buffer, 4);
	operand_two = deserialize_shr(buffer, 6);
	return 0;


}


