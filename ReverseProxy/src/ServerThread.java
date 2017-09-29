import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 * Created by kratos on 18-04-2017.
 */
public class ServerThread extends Thread {

    InetAddress clientAddress;
    DatagramSocket ssocket;
    DatagramPacket request;
    byte[] toReceive;

    public ServerThread(DatagramSocket s, InetAddress address, DatagramPacket dp, byte[] tr){
        this.clientAddress = address;
        this.ssocket = s;
        this.request = dp;
        this.toReceive = tr;
    }

    public void run(){


            try {
                request = new DatagramPacket(toReceive, toReceive.length);
                ssocket.receive(request);
                String requestToString = new String(request.getData(), 0, request.getLength());
                System.out.println(requestToString);

                byte[] toSend = requestToString.getBytes();
                DatagramPacket response = new DatagramPacket(toSend, toSend.length, clientAddress, 5555);
                ssocket.send(response);
            } catch (IOException e) {
                e.printStackTrace();
            }


        //System.out.println(udpClientAddress);




    }






}
