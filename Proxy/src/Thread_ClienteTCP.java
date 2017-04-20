package cc;

import java.io.BufferedReader;
import java.io.IOException;

/**
 *
 * @author broken
 */
public class Thread_ClienteTCP implements Runnable {
     private BufferedReader inputServer;

    public Thread_ClienteTCP(BufferedReader in) {
        this.inputServer = in;
    }

    public void run() {
        try {
            //recebe mensagens do servidor e imprime
            String linha;
            while ((linha = inputServer.readLine()) != null) {
                System.out.println(linha);
            }
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
}