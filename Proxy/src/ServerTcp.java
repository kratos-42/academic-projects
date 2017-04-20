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
 * Created by broken on 20-04-2017.
 */
public class ServerTcp extends Thread  {
     public static void main(String[] args) throws IOException, InterruptedException
    {   
        ServerSocket serverSocket = new ServerSocket(80);
        System.out.println("Servidor criado!");
        ThreadServidorTcp servidorTCP;
        
        while(true)
        {
            try
            {
                Socket s = serverSocket.accept();
                servidorTCP = new ThreadServidorTcp(s);
                servidorTCP.start();
            }
            catch(Exception e) { e.printStackTrace(); }
        }
    }
}