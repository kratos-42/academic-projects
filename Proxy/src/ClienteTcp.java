import com.sun.security.ntlm.Client;

import javax.sound.sampled.Line;
import javax.xml.crypto.Data;
import java.io.*;
import java.net.*;
import java.util.Scanner;

import static java.lang.System.in;
import static java.lang.System.out;

/**
 * Created by broken on 20-04-2017.
 */

public class ClienteTcp extends Thread {
     public static void main(String[] args) throws IOException, InterruptedException {
        try (
            Socket socket = new Socket("localhost", 80)) {
            String run;
            BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));
            BufferedReader serverInput = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter output = new PrintWriter(socket.getOutputStream());

            //Usado para ler as mensagens do Cliente
            Thread cliente = new Thread(new Thread_ClienteTCP(serverInput));
            cliente.start();
            //le as mensagens do user e envia para o Servidor
            run = userInput.readLine()
            while (!(run.equals("Logout")) {
                output.println(run);
                output.flush();
            }

            socket.shutdownInput();
            socket.shutdownOutput();
            socket.close();
        }
    }
