import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.*;
import java.util.HashMap;

import static java.lang.Thread.sleep;
import static sun.misc.Version.println;

/**
 * Created by kratos on 16-03-2017.
 */
public class ServerUdp {

    public static HashMap<InetAddress, InfoTable> serversConnected = new HashMap<>();



    public static void main(String args[]) throws IOException, InterruptedException {

        InfoTable table = new InfoTable(1,2,3);
        serversConnected.put(InetAddress.getByName("127.0.0.1"), table);

        System.out.println(table.getNrConexoes());

        ServerSend sending = new ServerSend(serversConnected);
        sending.start();
    }
}

/*


import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.HashMap;

import static sun.misc.Version.println;


 Created by kratos on 16-03-2017.

public class ServerUdp {

    HashMap<InetAddress, InfoTable> serversConnected;

    public static void main(String args[]) throws SocketException, IOException{

        DatagramSocket socket = new DatagramSocket(4242);
        byte[] toReceive = new byte[1024];
        byte[] toSend = new byte[1024];

        while(true){

            DatagramPacket request = new DatagramPacket(toReceive, toReceive.length);
            socket.receive(request);
            String requestToString = new String(request.getData(), 0, request.getLength());


            InetAddress udpClientAddress = request.getAddress();
            System.out.println(requestToString);

            int port = request.getPort();
            System.out.println(port);
            toSend = "fode-te".getBytes();
            DatagramPacket response = new DatagramPacket(toSend, toSend.length, udpClientAddress, port);
            socket.send(response);
*/