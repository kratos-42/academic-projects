import java.io.IOException;
import java.net.*;

import static java.lang.Thread.sleep;

/**
 * Created by kratos on 23-05-2017.
 */
public class MonitorUDP {
    int packetsSent = 0;

    public MonitorUDP() throws UnknownHostException {
    }

    class ClientUdp extends Thread {
        InetAddress address = InetAddress.getByName("localhost");

        public ClientUdp() throws UnknownHostException {
        }

        InetAddress getAddress() {
            return address;
        }

        public void run() {
            try {
                DatagramSocket socket = new DatagramSocket(5555);
                byte[] toReceive = new byte[1024];

                while (true) {

                    DatagramPacket receiveDataPacket = new DatagramPacket(toReceive, toReceive.length);
                    socket.receive(receiveDataPacket);
                    String response = new String(receiveDataPacket.getData(), 0, receiveDataPacket.getLength());
                    System.out.println(response);

                    if (response.contains("PROBING.")){
                        String[] split1 = response.split("\\.");
                        String[] split2 = split1[1].split(":");
                        int sequenceNumber = Integer.parseInt(split2[1]);
                        System.out.println(split2[1]);
                        ProbingResponse probingResponse = new ProbingResponse(address, sequenceNumber);
                        probingResponse.run();
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
    }

    class ProbingResponse implements Runnable {

        DatagramSocket socket;
        InetAddress address;
        int seqID;

        public ProbingResponse(InetAddress ad, int seqN) throws SocketException {
            socket = new DatagramSocket();
            address = ad;
            seqID = seqN;
        }

        public void run() {
                byte[] toSend;

                try {
                    toSend = ("Probing response.Sequence number:" + seqID).getBytes();
                    DatagramPacket request = new DatagramPacket(toSend, toSend.length, address, 4242);
                    socket.send(request);
                    packetsSent++;
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }

    class ClientSending implements Runnable {

        DatagramSocket socket;
        InetAddress address;

        public ClientSending(InetAddress ad) throws SocketException {
            socket = new DatagramSocket();
            address = ad;
        }

        public void run() {
            while (true) {
                byte[] toSend;

                try {
                    toSend = ("I'm still available!").getBytes();
                    DatagramPacket request = new DatagramPacket(toSend, toSend.length, address, 4242);
                    socket.send(request);
                    sleep(7000);
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    void initMonitorUdp() throws UnknownHostException, SocketException {
        ClientUdp c = new ClientUdp();
        ClientSending cs = new ClientSending(c.getAddress());

        c.start();
        cs.run();
    }

    public static void main(String args[]) throws Exception {

        try {
            MonitorUDP monitor = new MonitorUDP();
            monitor.initMonitorUdp();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

