import java.io.*;   // for Input/OutputStream
import java.net.*;  // for Socket
import java.util.Scanner;
import java.util.Arrays;

class ClientTCP
{                                                                               
	final static char NOT = '~';
	final static char SHIFTR = '>';
	final static char SHIFTL = '<';

	private Socket clientSocket;
	private BufferedReader inFromServer;
	private BufferedReader inFromKeyBoard;
	private DataOutputStream outToServer;


	public static void main(String args[])throws Exception                  
	{                                                                       
		String line, newLine;                                           

		if (args.length != 2)  // Test for correct # of args
			throw new IllegalArgumentException("Parameter(s): <Destination> <Port>");

		InetAddress destAddr = InetAddress.getByName(args[0]);  // Destination address
		int destPort = Integer.parseInt(args[1]);               // Destination port


		ClientTCP client = new ClientTCP(destAddr, destPort);
		System.out.println("Input a Calculation Request (y/n)");
		client.inFromKeyBoard = new BufferedReader(new InputStreamReader(System.in));
		line = client.inFromKeyBoard.readLine();
		while(!line.equals("n") && !line.equals("N")) {
		client.standUp();
		client.sendRequest();
		long startTime = System.nanoTime();
		client.handleAnswer();
		long endTime = System.nanoTime();
		long eTime = endTime - startTime;
			System.out.println("Time of Request: " + eTime / 1000000 + "ms");
			System.out.println("\nInput another Calculation Request (y/n)");
			line = client.inFromKeyBoard.readLine();
		}


	}                                                                       



	public ClientTCP(InetAddress addr, int port) throws Exception {
		clientSocket = new Socket(addr, port);
	}

	public void standUp() throws Exception {
		inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		outToServer = new DataOutputStream(clientSocket.getOutputStream());


	}

	public void sendRequest() throws Exception {
		byte ID = 0;
		
			ID++;
			Request req = getOperationFromUser(ID);
			EncoderBin enc = new EncoderBin();
			byte[] requestHeader = enc.encodeRequest(req);

			outToServer.write(requestHeader);
			
			}
	public Request getOperationFromUser(byte ID) throws Exception {
		Request retOp;
		char operation;
		short operand1 = 0;
		short operand2 = 0;
		byte op_code;
		System.out.println("Please enter your operation (+,-,*,/,>>,<<,~) ");
		Scanner in = new Scanner(System.in);
		operation = in.next().charAt(0);
		if (operation == NOT || operation == SHIFTL || operation == SHIFTR) {
			System.out.println("Please input your operand: ");
			operand1 = in.nextShort();
		} else {
			System.out.println("Please input your first operand: ");
			operand1 = in.nextShort();
			System.out.println("Please input your second operand: ");
			operand2 = in.nextShort();
		}
		switch (operation) {
			case '+':
				op_code = 0;
				break;
			case '-':
				op_code = 1;
				break;
			case '*':
				op_code = 2;
				break;
			case '/':
				op_code = 3;
				break;
			case '>':
				op_code = 4;
				break;
			case '<':
				op_code = 5;
				break;
			case '~':
				op_code = 6;
				break;		
			default:
				op_code = 7;
				break;
		}
		if (op_code >= 4) {
			retOp = new Request(ID, op_code, (byte) 1, operand1, (short) 0);
		} else {
			retOp = new Request(ID, op_code, (byte) 2, operand1, operand2);
		}
		return retOp;

	}
	public void handleAnswer() throws Exception {
		DecoderBin dec = new DecoderBin();
		Response resp = dec.decodeResponse(new DataInputStream(clientSocket.getInputStream()));
		System.out.println("\nByte Array of Response: ");
		resp.printByteArray();
		System.out.println();
		System.out.println("Answer to request #" + resp.RequestID + ": " + resp.Result);
		System.out.println();
	}
}     
