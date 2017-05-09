import java.io.IOException;
import java.net.*;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by kratos on 04-05-2017.
 */
public class ServerSend extends Thread {

    HashMap<InetAddress, InfoTable> serversConnected;
    DatagramSocket ssocket = new DatagramSocket(4242);

    public ServerSend(HashMap<InetAddress, InfoTable> sc) throws SocketException {
        this.serversConnected = sc;
    }

    public void run() {

        while (true) {
            for (Map.Entry<InetAddress, InfoTable> table : serversConnected.entrySet()) {
                try {
                    probing(ssocket, table.getKey(), 5555);
                    sleep(5000);
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

            }
        }
    }

    public static void probing(DatagramSocket socket, InetAddress udpClientAddress, int port)
            throws IOException {

        byte[] toReceive = new byte[1024];
        byte[] toSend;
        toSend = "PROBING".getBytes();

        DatagramPacket request = new DatagramPacket(toSend, toSend.length, udpClientAddress, port);
        socket.send(request);
        String requestToString = new String(request.getData(), 0, request.getLength());
        //System.out.println(requestToString);

        socket.setSoTimeout(2000);
        DatagramPacket response = new DatagramPacket(toReceive, toReceive.length, udpClientAddress, port);
        socket.receive(response);
        String responseToString = new String(response.getData(), 0, response.getLength());
        System.out.println(responseToString);



    }
}
