#include "../Encoder.c"
#include "../Encoder.h"
#include "../Decoder.c"
#include "../Decoder.h"
#include <stdio.h>
#include <iostream>
#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

unsigned char expArray[4];
unsigned char testArray[4];
int expectedAns;
int testAns;
class EncoderTestSuit : public testing::Test
{	

	void setUp(){
			}

	void tearDown(){}

};
/*
TEST_F(EncoderTestSuit, check_request_encoding) {
	testReq.TML = 7;
	testReq.ReqID = 1;
	testReq.opCode = 1;
	testReq.numOps = 2;
	testReq.operand1 = 1;
	testReq.operand2 = 2;
	expArray[0] = 7;
	expArray[1] = 1;
	expArray[2] = 1;
	expArray[3] = 2;
	expArray[4] = 0;
	expArray[5] = 1;
	expArray[6] = 0;
	expArray[7] = 2;

	encodeRequest(testArray, testReq);
	for(int i=0; i<8; ++i){
		std::cout << "Request header at " << i << ": " <<testArray[i];
		std::cout << "Expected header at " << i << ": " <<expArray[i];

	}
	ASSERT_EQ(expArray[0], testArray[0]);
	ASSERT_EQ(expArray[1], testArray[1]);
	ASSERT_EQ(expArray[2], testArray[2]);
	ASSERT_EQ(expArray[3], testArray[3]);
	ASSERT_EQ(expArray[4], testArray[4]);
	ASSERT_EQ(expArray[5], testArray[5]);
	ASSERT_EQ(expArray[6], testArray[6]);
	ASSERT_EQ(expArray[7], testArray[7]);



}*/
TEST_F(EncoderTestSuit, check_integer_encoding_value_is_one) {
	int val = 1;
	unsigned char * tmp = serialize_int(testArray, val);
	expArray[0] = 0;
	expArray[1] = 0;
	expArray[2] = 0;
	expArray[3] = 1;
	ASSERT_EQ(expArray[0], tmp[0]);
	ASSERT_EQ(expArray[1], tmp[1]);
	ASSERT_EQ(expArray[2] , tmp[2]);
	ASSERT_EQ(expArray[3], tmp[3]);
	ASSERT_EQ(val, deserialize_int(tmp, 0));
	
}


