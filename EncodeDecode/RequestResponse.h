struct Request {
	char TML;
	char ReqID;
	char opCode;
	char numOps;
	short operand1;
	short operand2;
};

 struct Response {
	char TML;
	char ReqID;
	char errCode;
	int result;
};

     
