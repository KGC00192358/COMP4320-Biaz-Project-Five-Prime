import java.io.*;

public class EncoderBin implements Encoder, EncoderDecoderConst {
	private String encoding;

	public EncoderBin() {
		encoding = DEFAULT_ENCODING;
	}

	public byte[] encodeRequest(Request request) throws Exception {
		
		ByteArrayOutputStream outs = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(outs);
		out.writeByte(request.TML);
		out.writeByte(request.RequestID);
		out.writeByte(request.Operation);
		out.writeByte(request.NumberofOperands);
		out.writeShort(request.Operand1);
		out.writeShort(request.Operand2);
		out.flush();
		return outs.toByteArray();


	}


	public byte[] encodeResponse(Response response) throws Exception {
		
		ByteArrayOutputStream outs = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(outs);
		out.writeByte(response.TML);
		out.writeByte(response.RequestID);
		out.writeByte(response.ErrorCode);
		out.writeInt(response.Result);
		out.flush();
		return outs.toByteArray();


	}



}
