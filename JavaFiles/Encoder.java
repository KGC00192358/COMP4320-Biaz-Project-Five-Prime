import java.net.*;
import java.io.*;

public interface Encoder {
	byte[] encodeRequest(Request request) throws Exception;
	byte[] encodeResponse(Response response) throws Exception;
}
