public class Request {

	public final byte TML = 8;
	public byte RequestID;
	public byte Operation;
	public byte NumberofOperands;
	public short Operand1;
	public short Operand2;

	public Request(byte inId, byte Op, byte numOp, short op1, short op2) {
		this.RequestID = inId;
		this.Operation = Op;
		this.NumberofOperands = numOp;
		this.Operand1 = op1;
		this.Operand2 = op2;


	}	

	public String toString() {
		final String EOLN = java.lang.System.getProperty("line.separator");
		String value = "ID: " + RequestID + EOLN +
				"Operation Code: " + Operation + EOLN +
				"Number of Operands: " + NumberofOperands + EOLN +
				"Operand One: " + Operand1 + EOLN +
				"Operand Two: " + Operand2 + EOLN;
		return value;
	}

}
