package projecto;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.HashMap;
import java.util.Scanner;

public class Cliente {
    private final static int porta = 55000;
    private final static String ip = "localhost";
    private static Socket clienteSocket;
    
    public static Scanner in = new Scanner(System.in);
    public static ObjectOutputStream o = null;
    public static ObjectInputStream i = null;
    public static HashMap<String, String> hash;
    public static String nick = null;
    public static PacoteDados p;       
    
    public static void main(String args[]) throws Exception{
        clienteSocket = new Socket(ip,porta);
         
        menuTipoUtilizador();
    }
    
    public static String menuInicial(){
        System.out.println("################### Serviço de Táxis #####################");
        System.out.println("#                                                        #");
        System.out.println("#   1 - Utilizador Passageiro                            #");
        System.out.println("#   2 - Utilizador Condutor                              #");
        System.out.println("#   3 - Sair da aplicação                                #");
	System.out.println("#                                                        #");
	System.out.println("#   Escolha uma opção:                                   #");
	System.out.println("##########################################################");
        String opt = in.next();

        if ( !(opt.equals("1") || opt.equals("2") || opt.equals("3")))
             opt = menuInicial();
        return opt;
    }
    
    public static void menuTipoUtilizador() throws IOException, ClassNotFoundException{
        String opt;
        opt = menuInicial();
        
        do{
            if(opt.equals("1")){
                menuRegEntPassageiro();
            }else{
                if(opt.equals("2")){
                    menuRegEntCondutor();
                }else{
                    if(opt.equals("3")){
                        System.exit(0);
                    }
                }
            }
        }while(true);
    }
    
    public static String menuLoginPassageiro(){
        String opt;
        
        System.out.println("################# Utilizador Passageiro ##################");
        System.out.println("#                                                        #");
        System.out.println("#   1 - Entrar                                           #");
        System.out.println("#   2 - Registar                                         #");
        System.out.println("#                                                        #");
        System.out.println("#   Escolha uma opção:                                   #");
        System.out.println("##########################################################");
        opt = in.next();
        
        if ( !(opt.equals("1") || opt.equals("2"))){
            opt = menuLoginPassageiro();
        }
        
        return opt;
    }  
    
    public static void menuRegEntPassageiro() throws IOException, ClassNotFoundException{
        String opt;
        
        opt = menuLoginPassageiro();
        
        if(opt.equals("1")){
            System.out.println("######################## Entrar ##########################");
            in.nextLine();
            System.out.println("#   Introduza um username                                #");
            String user = in.nextLine();
            System.out.println("#                                                        #");
            System.out.println("#   Introduza a password                                 #");
            String pw = in.nextLine();
            System.out.println("#                                                        #");
            System.out.println("##########################################################");
                 
            hash = new HashMap<>();
            hash.put(Servidor.NOME_PASSAGEIRO, user);
            hash.put(Servidor.PW_PASSAGEIRO, pw);
            p = new PacoteDados(Servidor.ENTRAR_PASSAGEIRO,hash);
                    
            o = new ObjectOutputStream(clienteSocket.getOutputStream());
            o.writeObject(p);
            o.flush();
                    
            BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
            String result = sktInput.readLine();
                    
            if(result.equals("Entrou")){
                nick = user;
                menuPrincipalPassageiro();
            }else{
                System.err.println("################   Autenticação falhada   ################");
                System.exit(0);
            } 
        }else{
            if(opt.equals("2")){
                System.out.println("####################### Registar #########################");
                System.out.println("#                                                        #");
                in.nextLine();
                System.out.println("#   Defina um username                                   #");
                String user = in.nextLine();
                System.out.println("#   Defina uma password                                  #");
                String pw = in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("##########################################################");

                hash = new HashMap<>();
                hash.put(Servidor.NOME_PASSAGEIRO, user);
                hash.put(Servidor.PW_PASSAGEIRO, pw);
                p = new PacoteDados(Servidor.REGISTAR_PASSAGEIRO,hash);

                o = new ObjectOutputStream(clienteSocket.getOutputStream());
                o.writeObject(p);
                o.flush();

                BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
                System.out.println("\n"+sktInput.readLine()+"\n");
            }else{
                System.exit(0);
            }
        }           
    }
    
    public static String menuLoginCondutor(){
        String opt;
        
        System.out.println("################## Utilizador Condutor ###################");
        System.out.println("#                                                        #");
        System.out.println("#   1 - Entrar                                           #");
        System.out.println("#   2 - Registar                                         #");
        System.out.println("#                                                        #");
        System.out.println("#   Escolha uma opção:                                   #");
        System.out.println("##########################################################");
        opt = in.next();
      
        if ( !(opt.equals("1") || opt.equals("2")))
            opt = menuLoginCondutor();
        
        return opt;
    }  
    
    public static void menuRegEntCondutor() throws IOException, ClassNotFoundException{
            String opt;
        
        opt = menuLoginCondutor();
        
        if(opt.equals("1")){
            System.out.println("######################## Entrar ##########################");
            System.out.println("#                                                        #");
            in.nextLine();
            System.out.println("#   Introduza um username                                #");
            String user = in.nextLine();
            System.out.println("#   Introduza a password                                 #");
            String pw = in.nextLine();
            System.out.println("#                                                        #");
            System.out.println("##########################################################");
                 
            hash = new HashMap<>();
            hash.put(Servidor.NOME_CONDUTOR, user);
            hash.put(Servidor.PW_CONDUTOR, pw);
            p = new PacoteDados(Servidor.ENTRAR_CONDUTOR,hash);
                    
            o = new ObjectOutputStream(clienteSocket.getOutputStream());
            o.writeObject(p);
            o.flush();
                    
            BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
            String result = sktInput.readLine();
                    
            if(result.equals("Entrou")){
                nick = user;
                menuPrincipalCondutor();
            }else{
                System.err.println("################   Autenticação falhada   ################");
                System.exit(0);
            } 
        }else{
            if(opt.equals("2")){
                System.out.println("####################### Registar #########################");
                System.out.println("#                                                        #");
                in.nextLine();
                System.out.println("#   Introduza um username                                #");
                String user = in.nextLine();
                System.out.println("#   Introduza a password                                 #");
                String pw = in.nextLine();
                System.out.println("#   Introduza o modelo da viatura                        #");
                String modelo = in.nextLine();
                System.out.println("#   Introduza a matrícula da viatura                     #");
                String matricula = in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("##########################################################");

                hash = new HashMap<>();
                hash.put(Servidor.NOME_CONDUTOR, user);
                hash.put(Servidor.PW_CONDUTOR, pw);
                hash.put(Servidor.MODELO_CONDUTOR,modelo);
                hash.put(Servidor.MATRICULA_CONDUTOR, matricula);
                p = new PacoteDados(Servidor.REGISTAR_CONDUTOR,hash);

                o = new ObjectOutputStream(clienteSocket.getOutputStream());
                o.writeObject(p);
                o.flush();

                BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
                System.out.println("\n"+sktInput.readLine()+"\n");
            }else{
                if(!(opt.equals("1") || opt.equals("2"))){
                   menuInicial();
                }
            }
        }            
    }
   
    public static void menuPrincipalPassageiro() throws IOException, ClassNotFoundException {
        System.out.println("############## Menu Principal Passageiro #################");
        System.out.println("#                                                        #");
        System.out.println("#   "  +  nick  );
        System.out.println("#                                                        #");
        System.out.println("#   1 - Solicitar Serviço                                #");
        System.out.println("#   2 - Logout                                           #");
        System.out.println("#                                                        #");
        System.out.println("#   Escolha uma opção                                    #");
        System.out.println("##########################################################");
        String opt = in.next();
           
        do {
            if(opt.equals("1")){
               menuSolicitaServico();
            }    
            if(opt.equals("2")) {
               logoutPassageiro();
            }else{
               System.out.println("Opcão inválida!");
               menuPrincipalPassageiro();
            }
        } while(!(opt.equals("1") || opt.equals("2")));
    }
    
    public static void menuSolicitaServico() throws IOException, ClassNotFoundException{
        System.out.println("################### Solicitar Viagem #####################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        in.nextLine();
        System.out.println("#   Indique local partida -> (X,Y)                       #");
        String partida = in.nextLine();
        System.out.println("#   Indique local destino -> (X,Y)                       #");
        String destino = in.nextLine();
        System.out.println("#                                                        #");
        System.out.println("##########################################################");

        //hash = new HashMap<>();
        hash.put(Servidor.COORD_PARTIDA_PASS, partida);
        hash.put(Servidor.COORD_DESTINO_PASS, destino);
        hash.put(Servidor.NOME_PASSAGEIRO,nick);
        p = new PacoteDados(Servidor.SOLICITAR_SERVICO_PASS,hash);

        o = new ObjectOutputStream(clienteSocket.getOutputStream());
        o.writeObject(p);
        o.flush();

        BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
        System.out.println("\n"+sktInput.readLine()+"\n");
        System.out.println(sktInput.readLine());
        System.out.println(sktInput.readLine());
        System.out.println(sktInput.readLine());
        System.out.println(sktInput.readLine()+"\n");
        System.out.println(sktInput.readLine()+"\n");
        System.out.println(sktInput.readLine());
        System.out.println(sktInput.readLine()+"\n");
        System.out.println(sktInput.readLine()+"\n");      
        menuPrincipalPassageiro();
    }
    
    public static void menuMandaMensagemChegada() throws IOException, ClassNotFoundException{
        System.out.println("############### Menu Principal Condutor ##################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        System.out.println("#   1 - Indica que chegou ao local                       #");
        System.out.println("#                                                        #");
        System.out.println("##########################################################");
        String opt = in.next();
        do {   
            if(opt.equals("1")){
                System.out.println("########### Mensagem de chegada à origem #################");
                System.out.println("#                                                        #");
                System.out.println("#   "   + nick  );
                in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("#   Deixe mensagem de aviso de chegada                   #");
                String mensagem = in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("##########################################################");
                
                hash.put(Servidor.MENSAGEM_COND_PARTIDA, mensagem);
                hash.put(Servidor.NOME_CONDUTOR,nick);
                p = new PacoteDados(Servidor.INDICA_MENSAGEM_PARTIDA,hash);

                o = new ObjectOutputStream(clienteSocket.getOutputStream());
                o.writeObject(p);
                o.flush();

                menuMandaMensagemFim();
            }    			
        } while(!(opt.equals("1")));
    }
    
    public static void menuMandaMensagemFim()throws IOException, ClassNotFoundException{
        System.out.println("############### Menu Principal Condutor ##################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        System.out.println("#   1 - Indica que chegou ao destino e preço             #");
        System.out.println("#                                                        #");
        System.out.println("##########################################################");
        String opt = in.next();
        
        do {    			
            if(opt.equals("1")){
                System.out.println("########### Mensagem de chegada ao destino ###############");
                System.out.println("#                                                        #");
                System.out.println("#   "   + nick  );
                in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("#   Deixe mensagem de aviso de chegada                   #");
                String mensagem = in.nextLine();
                System.out.println("#   Indique preço da viagem                              #");
                String preco = in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("##########################################################");
                
                hash.put(Servidor.MENSAGEM_COND_CHEGADA, mensagem);
                hash.put(Servidor.NOME_CONDUTOR,nick);
                hash.put(Servidor.PRECO_VIAGEM,preco);
                p = new PacoteDados(Servidor.INDICA_MENSAGEM_CHEGADA,hash);

                o = new ObjectOutputStream(clienteSocket.getOutputStream());
                o.writeObject(p);
                o.flush();

                BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
                System.out.println("\n"+sktInput.readLine()+"\n");//indica que serviço foi terminado
                novoServico();
            } 
        } while(!(opt.equals("1")));
    }
    
    public static void novoServico()throws IOException, ClassNotFoundException{
        System.out.println("############### Menu Principal Condutor ##################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        System.out.println("#   1 - Disponibilizar serviço                           #");
        System.out.println("#   2 - Logout                                           #");
        System.out.println("#                                                        #");
        System.out.println("##########################################################");
        String opt = in.next();
        
        do{
            if(opt.equals("1")){
                menuPrincipalCondutor();
            }
            if(opt.equals("2")){
                logoutCondutor();
                System.exit(0);
            }
        } while(!(opt.equals("1")) || (opt.equals("2")));
    }
    
    public static void menuPrincipalCondutor() throws IOException, ClassNotFoundException {
        System.out.println("############### Menu Principal Condutor ##################");
        System.out.println("#                                                        #");
        System.out.println("#   "   + nick  );
        System.out.println("#                                                        #");
        System.out.println("#   1 - Disponibiliza Serviço                            #");
        System.out.println("#                                                        #");
        System.out.println("##########################################################");
        String opt = in.next();
           
        do {
            if(opt.equals("1")){
                System.out.println("############### Disponibilizar serviço ###################");
                System.out.println("#                                                        #");
                System.out.println("#   "   + nick  );
                in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("#   Indique local partida -> (X,Y)                       #");
                String local = in.nextLine();
                System.out.println("#                                                        #");
                System.out.println("##########################################################");

                hash.put(Servidor.COORD_PARTIDA_COND, local);
                hash.put(Servidor.NOME_CONDUTOR,nick);
                p = new PacoteDados(Servidor.INDICA_LOCAL_COND,hash);

                o = new ObjectOutputStream(clienteSocket.getOutputStream());
                o.writeObject(p);
                o.flush();

                BufferedReader sktInput = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
                System.out.println("\n"+sktInput.readLine());
                System.out.println(sktInput.readLine());
                System.out.println(sktInput.readLine());
                System.out.println(sktInput.readLine()+"\n");
                menuMandaMensagemChegada();
            }
        } while(!(opt.equals("1") || opt.equals("2") || opt.equals("3") || opt.equals("4")));
    }
    
    private static void logoutCondutor() throws IOException, ClassNotFoundException {
    	hash = new HashMap<>();
        hash.put(Servidor.NOME_CONDUTOR, nick);
        p = new PacoteDados(Servidor.SAIR_CONDUTOR,hash);
        
        o = new ObjectOutputStream(clienteSocket.getOutputStream());
        o.writeObject(p);
        o.flush();
        
        nick = null;
        System.exit(0);
    }
    
    private static void logoutPassageiro() throws IOException, ClassNotFoundException {
    	hash = new HashMap<>();
        hash.put(Servidor.NOME_PASSAGEIRO, nick);
        p = new PacoteDados(Servidor.SAIR_PASSAGEIRO,hash);
        
        o = new ObjectOutputStream(clienteSocket.getOutputStream());
        o.writeObject(p);
        o.flush();
        
        nick = null;
        System.exit(0);
    }
    
}

