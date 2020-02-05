package projecto;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Servidor {
    private static final int porta = 55000;
    private static Central k = null;
    
    //Acções do Passageiro
    public static final String REGISTAR_PASSAGEIRO = "RegistarPassageiro";
    public static final String ENTRAR_PASSAGEIRO = "EntrarPassageiro";
    public static final String SAIR_PASSAGEIRO = "SairPassageiro";
    public static final String NOME_PASSAGEIRO = "NomePasageiro";
    public static final String PW_PASSAGEIRO = "PasswordPassageiro";
    public static final String COORD_PARTIDA_PASS = "CoordenadaPartidaCondutor";
    public static final String COORD_DESTINO_PASS = "CoordenadaDestinoCondutor";
    public static final String SOLICITAR_SERVICO_PASS = "SolicitarViagemPassageiro";
    
    //Acções do Condutor
    public static final String REGISTAR_CONDUTOR = "RegistarCondutor";
    public static final String ENTRAR_CONDUTOR = "EntrarCondutor";
    public static final String SAIR_CONDUTOR = "SairCondutor";
    public static final String NOME_CONDUTOR = "NomeCondutor";
    public static final String PW_CONDUTOR = "PasswordCondutor";
    public static final String MATRICULA_CONDUTOR = "MatriculaCondutor";
    public static final String MODELO_CONDUTOR = "ModeloCondutor";
    public static final String COORD_PARTIDA_COND = "CoordenadaCondutor";
    public static final String INDICA_LOCAL_COND = "LocalPartidaCondutor";
    public static final String INDICA_MENSAGEM_PARTIDA = "IndicaMensagemPartida";
    public static final String MENSAGEM_COND_PARTIDA = "MensagemCondutorPartida";
    public static final String INDICA_MENSAGEM_CHEGADA = "IndicaMensagemChegada";
    public static final String MENSAGEM_COND_CHEGADA = "MensagemCondutorChegada";
    public static final String PRECO_VIAGEM = "PrecoViagem";
    
    
    public static void main(String args[]) throws IOException{
        ServerSocket ws = new ServerSocket(porta);
        
        Central k = new Central();
        
        //Exemplos de vários utilizadores 
        k.registaUtilizadorCondutor("adminc","adminc", "civic","56-56-GL");
        k.registaUtilizadorPassageiro("adminp", "adminp");
        k.registaUtilizadorCondutor("joao","adminc", "civic","57-56-GL");
        k.registaUtilizadorPassageiro("gil", "adminp");
        k.registaUtilizadorCondutor("tiago","adminc", "civic","58-56-GL");
        k.registaUtilizadorPassageiro("sandra", "adminp");
        k.registaUtilizadorCondutor("carlos","adminc", "civic","59-56-GL");
        k.registaUtilizadorPassageiro("jose", "adminp");
        k.registaUtilizadorCondutor("antonio","adminc", "civic","60-56-GL");
        k.registaUtilizadorPassageiro("fernando", "adminp");
        k.registaUtilizadorCondutor("xavier","adminc", "jaguar","61-56-GL");
        k.registaUtilizadorPassageiro("faria", "adminp");
        k.registaUtilizadorCondutor("daniel","adminc", "ferrari","62-56-GL");
        k.registaUtilizadorPassageiro("pedro", "adminp");
        k.registaUtilizadorCondutor("antonio","adminc", "honda","63-56-GL");
        k.registaUtilizadorPassageiro("diogo", "adminp");
        
        
        while(true) {
            Socket cliente = ws.accept();
            System.out.println("Entrou no servidor\nIP: " + cliente.getInetAddress());

            new Thread(new Handler(cliente,k)).start();
        }
    }    
}
