package projecto;

import java.io.ObjectInputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class Handler implements Runnable {
    private final Socket s;
    private final Central sk;
    private ObjectInputStream sInput;
    private PrintWriter sOutput;
    
    //construtor por argumentos
    public Handler(Socket cliente, Central sk){
        this.s = cliente;
        this.sk = sk;
        this.sInput = null;
        this.sOutput = null;
    }

    @Override
    public void run() {
        try{
            do {
                this.sInput = new ObjectInputStream(s.getInputStream());
    		this.sOutput = new PrintWriter(s.getOutputStream());
    				
    		PacoteDados pacote = (PacoteDados) sInput.readObject();

    		if (pacote.getAccao().equals(Servidor.REGISTAR_CONDUTOR)) {
                    System.err.println("Recebeu Registar Condutor");
                    String nick = pacote.getArgumentos().get(Servidor.NOME_CONDUTOR);
                    String pw = pacote.getArgumentos().get(Servidor.PW_CONDUTOR);
                    String mod = pacote.getArgumentos().get(Servidor.MODELO_CONDUTOR);
                    String matricula = pacote.getArgumentos().get(Servidor.MATRICULA_CONDUTOR);

                    System.out.println("USER: " + nick + " " + pw);
                    boolean existe = sk.registaUtilizadorCondutor(nick, pw, mod, matricula);

                    if(existe){
                        sOutput.println("Registado com Sucesso");
                    }else{
                        sOutput.println("Condutor já existe");
                    }	
                    sOutput.flush();
    		}else{
                    if (pacote.getAccao().equals(Servidor.ENTRAR_CONDUTOR)){
                        System.err.println("Pacote Entrar");
                        String nick = pacote.getArgumentos().get(Servidor.NOME_CONDUTOR);
                        String pw = pacote.getArgumentos().get(Servidor.PW_CONDUTOR);
                    
                        boolean on = false;
                        
                        if(sk.getUtilizadorCondutor().containsKey(nick)){
                           on = sk.getUtilizadorCondutor().get(nick).isAtivo();
                        }
                       
                        System.out.println("USER: " + nick + " " + pw);
                        boolean existe = sk.AutenticaCondutor(nick, pw);
    						
                        if(existe && !on){
    			    sOutput.println("Entrou");
                        }else{ 
                            sOutput.println("Nao Entrou");
                        }
                        sOutput.flush();
                    }else{
                        if (pacote.getAccao().equals(Servidor.REGISTAR_PASSAGEIRO)) {
                            System.err.println("Recebeu Registar Passageiro");
                            String nick = pacote.getArgumentos().get(Servidor.NOME_PASSAGEIRO);
                            String pw = pacote.getArgumentos().get(Servidor.PW_PASSAGEIRO);

                            System.out.println("USER: " + nick + " " + pw);
                            boolean existe = sk.registaUtilizadorPassageiro(nick, pw);

                            if(existe){
                                sOutput.println("Registado com Sucesso");
                            }else{
                                sOutput.println("Passageiro já existe");
                            }	
                            sOutput.flush();
                        }else{
                            if (pacote.getAccao().equals(Servidor.ENTRAR_PASSAGEIRO)){
                                System.err.println("Pacote Entrar");
                                String nick = pacote.getArgumentos().get(Servidor.NOME_PASSAGEIRO);
                                String pw = pacote.getArgumentos().get(Servidor.PW_PASSAGEIRO);

                                boolean on = false;

                                if(sk.getUtilizadorPassageiro().containsKey(nick)){
                                    on = sk.getUtilizadorPassageiro().get(nick).isAtivo();
                                }

                                System.out.println("USER: " + nick + " " + pw);
                                boolean existe = sk.AutenticaPassageiro(nick, pw);
                                
                                if(existe && !on){
                                    sOutput.println("Entrou");
                                }else{ 
                                    sOutput.println("Nao Entrou");
                                }
                                sOutput.flush();    
                            }else {
                                if(pacote.getAccao().equals(Servidor.SAIR_PASSAGEIRO)){
                                    System.err.println("Pacote Sair");
                                                                        
                                    String user = pacote.getArgumentos().get(Servidor.NOME_PASSAGEIRO);
                                    sk.logoutPassageiro(user);
                                    //System.out.println(sk.getUtilizadorPassageiro().get(user).isAtivo());
                                }else{
                                    if(pacote.getAccao().equals(Servidor.SAIR_CONDUTOR)){
                                        System.err.println("Pacote Sair");
                                        
                                        String user = pacote.getArgumentos().get(Servidor.NOME_CONDUTOR);
                                        sk.logoutCondutor(user);
                                        //System.out.println(sk.getUtilizadorCondutor().get(user).isAtivo());
                                    }else{
                                        if(pacote.getAccao().equals(Servidor.SOLICITAR_SERVICO_PASS)){
                                            System.err.println("Pacote Solicitar Viagem");
                                            String nomePassageiro = pacote.getArgumentos().get(Servidor.NOME_PASSAGEIRO);
                                            String origem = pacote.getArgumentos().get(Servidor.COORD_PARTIDA_PASS);
                                            String destino = pacote.getArgumentos().get(Servidor.COORD_DESTINO_PASS);
                                            
                                            int px,py;//coordenadas passageiro
                                            int cx,cy;//coordenadas condutor
                                                                                        
                                            if(sk.atualizarCoordPassageiro(nomePassageiro, origem, destino)){
                                                sOutput.println("Coordenadas atualizadas com sucesso!");
                                                sOutput.flush();
                                            }else{
                                                sOutput.println("Erro a atualizar coordenadas!");
                                                sOutput.flush();
                                            }
                                            
                                            int velocidade = 50;// assume-se que o carro tem de velocidade média 50km/h
                                            
                                            String nomeCondutor = sk.solicitarViagemPass(nomePassageiro);
                                            System.out.println(nomeCondutor);
                                            px = sk.getUtilizadorPassageiro().get(nomePassageiro).getCoordOX();
                                            py = sk.getUtilizadorPassageiro().get(nomePassageiro).getCoordOY();
                                            
                                            cx = sk.getUtilizadorCondutor().get(nomeCondutor).getCoordOX();
                                            cy = sk.getUtilizadorCondutor().get(nomeCondutor).getCoordOY();
                                            
                                            //inserir nos servicos ativos, e fazer signalAll
                                            sk.insereServicosAtivos(nomeCondutor,nomePassageiro);
                                            
                                            sOutput.println("Condutor: " + nomeCondutor);
                                            sOutput.println("Matricula: " + sk.getUtilizadorCondutor().get(nomeCondutor).getMatricula()); 
                                            sOutput.println("Modelo: " + sk.getUtilizadorCondutor().get(nomeCondutor).getModelo());
                                            sOutput.println("Tempo de deslocação: " + ((Math.abs((px-cx)+(py-cy)))/velocidade));
                                            sOutput.flush();
                                            
                                            if(sk.recebeMensagemChegada(nomeCondutor)){
                                                sOutput.println("Mensagem de chegada ao local de origem: "+sk.getServicosAtivos().get(nomeCondutor).getMensagemChegada()+".");
                                                sOutput.flush();
                                            }
                                            
                                            if(sk.recebeMensagemFim(nomeCondutor)){
                                                sOutput.println("Mensagem de fim de viagem: " + sk.getServicosAtivos().get(nomeCondutor).getMensagemFim()+".");
                                                sOutput.println("Preço da viagem: " + sk.getServicosAtivos().get(nomeCondutor).getPreco() + "€");
                                                sOutput.flush();
                                            }
                                            
                                            if(sk.removerServico(nomeCondutor)){
                                                sOutput.println("Serviço terminado!");
                                                sOutput.flush();
                                            }
                                        }else{
                                            if(pacote.getAccao().equals(Servidor.INDICA_LOCAL_COND)){
                                                System.err.println("Disponibilizar serviço");
                                                String nome = pacote.getArgumentos().get(Servidor.NOME_CONDUTOR);
                                                String local = pacote.getArgumentos().get(Servidor.COORD_PARTIDA_COND);
                                                
                                                if(sk.atualizarCoordCondutor(nome, local)){
                                                    sOutput.println("Coordenadas atualizadas com sucesso!");
                                                    sOutput.flush();
                                                }else{
                                                    sOutput.println("Erro ao actualizar coordenadas!");
                                                    sOutput.flush();
                                                }
                                                //Disponibilizar para o serviço
                                                System.out.println("Serviço inserido: " + sk.inserirServicoCondutor(nome));
                                                
                                                //tem que ficar a espera da resposta do passageiro
                                                //nome do passageiro e coordenadas
                                                if(sk.mandaCoordenadas(nome)){
                                                    sOutput.println("Passageiro: " + sk.getServicosAtivos().get(nome).getPassageiro());
                                                    sOutput.println("Coordenadas onde se encontra passageiro: (" + sk.getServicosAtivos().get(nome).getCoordx() + ", " + sk.getServicosAtivos().get(nome).getCoordy() + ")");
                                                    sOutput.println("Coordenadas do destino do passageiro: ("+sk.getServicosAtivos().get(nome).getCoordDestinox() + ", " + sk.getServicosAtivos().get(nome).getCoordDestinoy() + ")");
                                                    sOutput.flush();
                                                }
                                            }else{
                                                if(pacote.getAccao().equals(Servidor.INDICA_MENSAGEM_PARTIDA)){
                                                    System.err.println("Condutor chegou à origem do Passageiro!");
                                                    String nome = pacote.getArgumentos().get(Servidor.NOME_CONDUTOR);
                                                    String mensagem = pacote.getArgumentos().get(Servidor.MENSAGEM_COND_PARTIDA);
                                                    
                                                    //manda mensagem para o cliente que já chegou ao local indicado
                                                    sk.enviaMensagemChegada(nome,mensagem);
                                                }else{
                                                    if(pacote.getAccao().equals(Servidor.INDICA_MENSAGEM_CHEGADA)){
                                                        System.err.println("Condutor chegou ao destino do Passageiro!");
                                                        String valor = pacote.getArgumentos().get(Servidor.PRECO_VIAGEM);
                                                        String nome = pacote.getArgumentos().get(Servidor.NOME_CONDUTOR);
                                                        String mensagem = pacote.getArgumentos().get(Servidor.MENSAGEM_COND_CHEGADA);
                                                        
                                                        //manda mensagem para o cliente que terminou a viagem e manda preço
                                                        double preco = Double.parseDouble(valor);
                                                        sk.enviaMensagemFim(nome,mensagem,preco);
                                                        
                                                        sOutput.println("Serviço terminado!");
                                                        sOutput.flush();
                                                    }
                                                }    
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }    
                }
            }while(true);
        }catch (Exception e) {}        
    }    
}
