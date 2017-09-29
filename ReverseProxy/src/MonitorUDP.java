import java.io.IOException;
import java.net.*;

import static java.lang.Thread.sleep;

/**
 * Created by kratos on 23-05-2017.
 */
public class MonitorUDP {

    //InetAddress address = (InetAddress.getByName("localhost"));
    int port = 5555;
    int packetsReceived;
    int packetsSent = 0;

    public MonitorUDP() throws UnknownHostException {
    }

    class ClientUdp extends Thread {

        int prova = 2;
        InetAddress address = InetAddress.getByName("localhost");

        public ClientUdp() throws UnknownHostException {
        }

        InetAddress getAddress() {
            return address;
        }

        public void run() {

            try {

                DatagramSocket socket = new DatagramSocket(5555);
                byte[] toSend;
                byte[] toReceive = new byte[1024];
                DatagramPacket out;
                String resposta;
                InetAddress serverAddress;
                boolean firstConn = true;

                while (true) {

                    DatagramPacket receiveDataPacket = new DatagramPacket(toReceive, toReceive.length);
                    socket.receive(receiveDataPacket);
                    String response = new String(receiveDataPacket.getData(), 0, receiveDataPacket.getLength());
                    System.out.println(response);
                    serverAddress = socket.getInetAddress();


                    if (response.contains("PROBING.")) {/*
                        resposta = "Response from:" + address + " : " + socket.getLocalPort();
                        toSend = resposta.getBytes();
                        out = new DatagramPacket(toSend, toSend.length, address, 4242);
                        socket.send(out);*/
                        String[] split1 = response.split("\\.");
                        String[] split2 = split1[1].split(":");
                        int sequenceNumber = Integer.parseInt(split2[1]);
                        System.out.println(split2[1]);
                        //String[] split2 = split1[1].split(":");
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

                    //String requestToString = new String(request.getData(), 0, request.getLength());


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
                    toSend = ("Pronto a utilizar!").getBytes();
                    DatagramPacket request = new DatagramPacket(toSend, toSend.length, address, 4242);
                    socket.send(request);

                    String requestToString = new String(request.getData(), 0, request.getLength());
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

