import javax.sound.sampled.Line;
import javax.swing.plaf.synth.SynthTextAreaUI;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.OutputStream;
import java.math.BigDecimal;
import java.net.*;
import java.sql.Timestamp;
import java.util.HashMap;
import java.util.Map;

import static java.lang.System.currentTimeMillis;

/**
 * Created by kratos on 23-05-2017.
 */
public class Proxy {

    private volatile HashMap<InetAddress, InfoTable> serversConnected = new HashMap<>();

    public Proxy(){

    }

    public Proxy(HashMap<InetAddress, InfoTable> t){
            this.serversConnected = t;


    }





    class ServerUdp extends Thread {

        //public HashMap<InetAddress, InfoTable> serversConnected = new HashMap<>();
        DatagramSocket socket = new DatagramSocket(4242);

        public ServerUdp() throws SocketException {
        }

        public void run() {

            int counter = 0;

            while (true) {

                byte[] toReceive = new byte[1024];
                DatagramPacket receiveDataPacket = new DatagramPacket(toReceive, toReceive.length);
                try {
                    socket.receive(receiveDataPacket);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                String response = new String(receiveDataPacket.getData(), 0, receiveDataPacket.getLength());

                System.out.println(response);
                if (response.contains("Sequence number:")) {
                    counter++;
                    long currTime = currentTimeMillis();

                    Timestamp initialTime = serversConnected.get(receiveDataPacket.getAddress()).getTimeStart();
                    long calculate =  currTime - initialTime.getTime();
                    serversConnected.get(receiveDataPacket.getAddress()).setRtt(new Timestamp(calculate-initialTime.getTime()));

                    Timestamp rttCalculated = new Timestamp(calculate);
                    System.out.println("TIME STAMP CALCULADO: " + rttCalculated);


                    String[] parts = response.split(":");
                    int sequenceNumber = Integer.parseInt(parts[1]);
                    InetAddress receivedAd = receiveDataPacket.getAddress();
                    int currOut = serversConnected.get(receivedAd).getOut();

                    if(currOut-1 != sequenceNumber && sequenceNumber != 0){
                        double newT = sequenceNumber / (currOut-1);
                        serversConnected.get(receivedAd).setTaxaPacotesPerdidos(newT);

                    }
                    serversConnected.get(receivedAd).setIn(counter);



                    //UPDATE INFO


                }

                if (response.equals("Pronto a utilizar!")) {
                    if (serversConnected.containsKey(receiveDataPacket.getAddress())) {

                    }
                    else{
                        serversConnected.put(receiveDataPacket.getAddress(), new InfoTable());

                        try {
                            ServerSending sv = new ServerSending();
                            sv.start();
                        } catch (SocketException e) {
                            e.printStackTrace();
                            System.exit(0);
                        }
                    }
                }

            }
        }
    }



    class ServerSending extends Thread {

        DatagramSocket ssocket = new DatagramSocket();

        public ServerSending() throws SocketException {

        }
  /*
        public ServerSending(HashMap<InetAddress, InfoTable> sc) throws SocketException {
            this.serversConnected = sc;
        }
*/
        public void run() {

            while (true) {

                for (Map.Entry<InetAddress, InfoTable> table : serversConnected.entrySet()) {
                    try {
                        long tStart =currentTimeMillis();
                        table.getValue().setTimeStart(new Timestamp(tStart));

                        probing(ssocket, table.getKey(), 5555);
                        //probing(ssocket, table.getKey(), 5556);
                       // probing(ssocket, table.getKey(), 5557);
                        sleep(5000);
                    } catch (IOException e) {
                        e.printStackTrace();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }


                }
            }
        }

        public void probing(DatagramSocket socket, InetAddress udpClientAddress, int port) throws IOException {

            byte[] toSend;
            int currOut = serversConnected.get(udpClientAddress).getOut();
            toSend = ("PROBING. Sequence number:" + currOut).getBytes();
            currOut++;
            serversConnected.get(udpClientAddress).setOut(currOut);

            DatagramPacket request = new DatagramPacket(toSend, toSend.length, udpClientAddress, port);
            socket.send(request);
            String requestToString = new String(request.getData(), 0, request.getLength());
            //System.out.println(requestToString);
        }
    }



    public InetAddress calculateRating(){
        double rating;
        double bestRating = 1000;
        InetAddress cadidateAddress = null;

        for(Map.Entry<InetAddress, InfoTable> table: serversConnected.entrySet()){

            rating = table.getValue().getNrConexoes()*0.4 + table.getValue().getTaxaPacotesPerdidos()*5.5 + (table.getValue().getRtt()).getTime()*2;

            if(bestRating > rating){
                cadidateAddress = table.getKey();
                bestRating = rating;
            }
        }

        if(cadidateAddress == null){
            System.err.println("SEM SERVIDORES DISPONÍVEIS!");
            return null;
        }
        return cadidateAddress;
    }

    public void initProxy() throws IOException {
        ServerUdp serverUdp = new ServerUdp();

        serverUdp.start();

        //RedirectConnection redirect = new RedirectConnection();
        //redirect.start();

    }

    public static void main(String args[]) throws IOException, InterruptedException {

        try{
            Proxy proxy = new Proxy();
            proxy.initProxy();


        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    class RedirectConnection extends Thread{


        private Socket ssocket;

        private ServerSocket serverSocket = new ServerSocket(80); // SERVER SOCKET


        public RedirectConnection() throws IOException {

        }

        public void run(){

            while(true){
                try {
                    Socket csocket = serverSocket.accept(); // CLIENT ACCEPTED
                    InetAddress chosenAddress = calculateRating();

                    if(chosenAddress == null){
                        String msg = ("Sem servidores disponíveis!");
                        byte[] error = msg.getBytes();
                        OutputStream osClient = csocket.getOutputStream();
                        osClient.write(error);
                        csocket.close();
                    }

                    else {
                        serversConnected.get(chosenAddress).updateNrConexoes();

                        ssocket = new Socket(chosenAddress, 80);
                        TCPServer tcpS = new TCPServer(csocket, ssocket);
                        tcpS.start();
                        csocket.close();
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }


            }



        }
    }


}

