import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * Created by kratos on 10-05-2017.
 */
public class ClientProbingResponse extends Thread {


    public void run() {

        String resposta;
        byte[] toSend;
        DatagramPacket out;

        try{
            DatagramSocket socket = new DatagramSocket();
            resposta = "probing response";
            toSend = resposta.getBytes();
            out = new DatagramPacket(toSend, toSend.length, InetAddress.getByName("localhost"), 4242);
            socket.send(out);
            Thread.currentThread().interrupt();
            return;
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
