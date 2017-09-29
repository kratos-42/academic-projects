import java.io.IOException;
import java.net.*;

/**
 * Created by kratos on 09-05-2017.
 */
public class ClientSending extends Thread {

    DatagramSocket socket = new DatagramSocket(4242);

    public ClientSending() throws SocketException {
    }

    public void run(){

        while(true){

            byte[] toReceive = new byte[1024];
            byte[] toSend = new byte[1024];

            try {
                toSend = "Pronto a utilizar!".getBytes();
                DatagramPacket request = new DatagramPacket(toSend, toSend.length, InetAddress.getByName("localhost"), 4242);
                socket.send(request);
                String requestToString = new String(request.getData(), 0, request.getLength());
                System.out.println(requestToString);
                sleep(7);

            } catch (IOException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
}
