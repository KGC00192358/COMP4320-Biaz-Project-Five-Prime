import java.io.*;
import java.net.*;

public class DecoderBin implements EncoderDecoderConst, Decoder {


private String encoding;  // Character encoding

  public DecoderBin() {
    encoding = DEFAULT_ENCODING;
  }

  public DecoderBin(String encoding) {
    this.encoding = encoding;
  }

  public Request decodeRequest(DataInputStream src) throws Exception {
	  System.out.println("Reading Request..");
		byte TML, ID, Operation, numOps;
	        short op1, op2;	
		TML = src.readByte();
	        ID = src.readByte();	
		Operation = src.readByte();
		numOps = src.readByte();
		op1 = src.readShort();
		op2 = src.readShort();
		System.out.println("Request read");
		return new Request(ID, Operation, numOps, op1, op2);
  }
	public Response decodeResponse(DataInputStream src) throws Exception {
		byte TML, ID, err0;
	        int res0;
		TML = src.readByte();
	        ID = src.readByte();	
		err0 = src.readByte();
		res0 = src.readInt();
		return new Response(ID, err0, res0);
  }


}
