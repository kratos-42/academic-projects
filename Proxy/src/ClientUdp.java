import com.sun.security.ntlm.Client;

import javax.sound.sampled.Line;
import javax.xml.crypto.Data;
import java.io.*;
import java.net.*;
import java.util.Scanner;

import static java.lang.System.in;
import static java.lang.System.out;

public class ClientUdp extends Thread {

    InfoTable table = new InfoTable()

    public void run() {

        try {
            InetAddress address = InetAddress.getByName("localhost");
            DatagramSocket socket = new DatagramSocket(5555);
            byte[] toSend;
            byte[] toReceive = new byte[1024];


            while (true) {
                /*BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
                String outMessage = stdin.readLine();

                if (outMessage.equals("bye")) {
                    break;
                }

                String outString = "Client say: " + outMessage;
                toSend = outString.getBytes();

                DatagramPacket out = new DatagramPacket(toSend, toSend.length, address, 4242);
                socket.send(out);
*/

                DatagramPacket receiveDataPacket = new DatagramPacket(toReceive, toReceive.length);
                socket.receive(receiveDataPacket);
                String response = new String(receiveDataPacket.getData(), 0, receiveDataPacket.getLength());
                System.out.println(response);

                if(response.equals("PROBING")){

                }
            }
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

/*
                try {

                    DatagramPacket dataPacket = new DatagramPacket(toSend, toSend.length, address, 4242);
                    socket.send(dataPacket);
                    socket.receive(receiveDataPacket);

                    ObjectInputStream in = new ObjectInputStream(socket.)
                    String response = new String(receiveDataPacket.getData(), 0, receiveDataPacket.getLength());
                    System.out.println("Resposta" + response);


                } catch (Exception e) {
                    e.printStackTrace();

                }

        }
        catch (UnknownHostException e2) {
        }
        catch (IOException e3) {
        }
    }
*/

    public static void main(String args[]) throws Exception {
        ClientUdp c = new ClientUdp();
        c.start();
    }

}
