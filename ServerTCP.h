#include "GenericFunctions/Generic_Functions.h"
#include "EncodeDecode/Encoder.h"
#include "EncodeDecode/Decoder.h"

int die(char *s);
int setUp(int port);
int waitForConnection();
int performCalculation(unsigned char * buffer);
void sendAndRec();
