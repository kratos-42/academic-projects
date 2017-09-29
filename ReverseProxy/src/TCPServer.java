import java.io.*;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Created by kratos on 24-05-2017.
 */
public class TCPServer extends Thread {

        Socket csocket = new Socket();
        Socket ssocket = new Socket();


        public TCPServer(Socket csocket, Socket ssocket) throws IOException {
            this.csocket = csocket;
            this.ssocket = ssocket;

        }

        public void run() {

            while (true) {

                InputStream inputClient;
                OutputStream outputClient;
                try {

                    inputClient = this.csocket.getInputStream();
                    outputClient = this.csocket.getOutputStream();


                    if (this.ssocket != null) {
                        InputStream inputServer = ssocket.getInputStream();
                        OutputStream outputServer = ssocket.getOutputStream();
                        byte[] requiredInfo = new byte[1024];
                        byte[] toClient = new byte[1024];

                        while (inputClient.read(requiredInfo) != 1) {
                            outputServer.write(requiredInfo);

                            while (inputServer.read(toClient) != -1) {
                                outputClient.write(toClient);
                            }

                            requiredInfo = null;
                            toClient = null;

                            outputServer.flush();
                            outputClient.flush();
                        }
                        inputServer.close();
                        inputClient.close();
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }

                try {
                    this.csocket.close();
                    this.ssocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        }
    }

