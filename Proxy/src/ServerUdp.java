import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.HashMap;

import static java.lang.Thread.sleep;
import static sun.misc.Version.println;

/**
 * Created by kratos on 16-03-2017.
 */
public class ServerUdp {

    HashMap<InetAddress, InfoTable> serversConnected;

    public static void main(String args[]) throws SocketException, IOException, InterruptedException {

        DatagramSocket socket = new DatagramSocket(4242);
        byte[] toReceive = new byte[1024];
        byte[] toSend = new byte[1024];

        while (true) {
            InetAddress address = InetAddress.getByName("localhost");
            probing(socket, address, 5555);
            sleep(2000);
        }
    }


    public static void probing(DatagramSocket socket, InetAddress udpClientAddress, int port) throws IOException{

        byte[] toReceive = new byte[1024];
        byte[] toSend;
        toSend = "PROBING".getBytes();

        DatagramPacket request = new DatagramPacket(toSend, toSend.length, udpClientAddress, port);
        socket.send(request);
        String requestToString = new String(request.getData(), 0, request.getLength());

        socket.setSoTimeout(1000);
        System.out.println(requestToString);
        DatagramPacket response = new DatagramPacket(toReceive, toReceive.length, udpClientAddress, port);
        socket.send(response);

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