import java.io.*;
import java.net.*;

public interface Decoder {

	public Request decodeRequest(DataInputStream src) throws Exception;
	public Response decodeResponse(DataInputStream src) throws Exception;

}
