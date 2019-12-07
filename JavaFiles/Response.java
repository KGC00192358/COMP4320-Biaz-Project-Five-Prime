public class Response {

	public final byte TML = 7;
	public byte RequestID;
	public byte ErrorCode;
	public int Result;

	public Response(byte inId, byte err, int res) {
		this.RequestID = inId;
		this.ErrorCode = err;
		this.Result = res;


	}	

	public String toString() {
		final String EOLN = java.lang.System.getProperty("line.separator");
		String value = "\tID: " + RequestID + EOLN +
				"\tError Code: " + ErrorCode + EOLN +
				"\tResult: " + Result + EOLN;
		return value;
	}
	public byte[] toByteArray() {
		String value = "" + TML + RequestID + ErrorCode + Result;
		return value.getBytes();
	}
	public void printByteArray() {
		System.out.println("[" + TML + ", " + RequestID + ", " + ErrorCode + ", " + Result + "]");
	}

}
