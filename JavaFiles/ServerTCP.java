import java.io.*;   // for Input/OutputStream
import java.net.*;  // for Socket and ServerSocket

class ServerTCP                                                              
{                                                                               
	private ServerSocket serverSock;
	private Socket recSocket;
	private BufferedReader inFromClient;
	private DataOutputStream outToClient;



	public static void main(String args[]) throws Exception                       
	{                                                                            
		if (args.length != 1) 
			throw new IllegalArgumentException("Parameter(s): <Port>");

		int port = Integer.parseInt(args[0]);               // Destination port
		boolean shutdownSIG = false;
		ServerTCP serv = new ServerTCP(port);
		serv.standUp();
		while(!shutdownSIG) {
			serv.run();
		}

		serv.closeDown();



	}      

	public ServerTCP(int port) throws Exception {
		serverSock = new ServerSocket(port);
		System.out.println("New Socket Created on IP: " + serverSock.getInetAddress());

	}	
	private void run() throws Exception {

		DecoderBin dec = new DecoderBin();

		Request req = dec.decodeRequest(new DataInputStream(recSocket.getInputStream()));
		Response resp = performRequest(req);

		//Thread.sleep(200000);
		EncoderBin enc = new EncoderBin();
		byte[] responseHeader = enc.encodeResponse(resp);
		System.out.println("Response sent with answer:" + resp.Result);
		outToClient.write(responseHeader);

		/*	while((line=inFromClient.readLine()) != null)                                                     
			{                                                               
			System.out.println("Sever waiting...");
			System.out.println("Server Recieved: " + line);
			System.out.println("Sending Response");
			line = line + '\n';
			outToClient.writeBytes(line);
			System.out.println("Response sent");
			} */

	}
	public Response performRequest(Request op) throws Exception {
		int recLngth = 8;
		int result = 0;
		int operation = -1;


		operation = op.Operation;


		System.out.println("Attempting Request below: ");   
		System.out.println(op);

		switch (operation) {
			case(0):
				result = op.Operand1 + op.Operand2;
				break;
			case(1): 
				result = op.Operand1 - op.Operand2;
				break;
			case(2):
				result = op.Operand1*op.Operand2;
				break;
			case(3):
				result = op.Operand1/op.Operand2;
				break;
			case(4):
				result = op.Operand1 >> 1;
				break;
			case(5):
				result = op.Operand1 << 1;
				break;
			case(6):
				result = ~op.Operand1;
				break;
			default:
				break;
		}
		Response tmp = null;
		if(recLngth == op.TML) {
			return new Response(op.RequestID, (byte) 0, result);
		} else {
			return new Response(op.RequestID, (byte) 127, result);
		}


	}
	private void standUp() throws Exception {
		System.out.println("Server Listening");                      
		recSocket = serverSock.accept();
		System.out.println("Connection Established");	
		outToClient = new DataOutputStream(recSocket.getOutputStream());

	}
	private void closeDown() throws Exception {
		outToClient.close();
		recSocket.close();
		serverSock.close();
		//System.exit(0);
	}

}  

