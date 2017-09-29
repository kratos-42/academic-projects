import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;

/**
 * Created by kratos on 24-05-2017.
 */
public class TCPClient extends Thread {

    private Socket csocket; // CLIENT SOCKET
    private InetAddress IPaddress = InetAddress.getByName("localhost");

    public TCPClient() throws UnknownHostException {

    }

    public void run() {

        try {
            csocket = new Socket(IPaddress, 80);
            csocket.setSoTimeout(10000);
            csocket.close();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void main(String argv[]) throws Exception {

        TCPClient tcpClient = new TCPClient();

        tcpClient.run();

    }
}


