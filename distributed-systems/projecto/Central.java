package projecto;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Central {
    private HashMap<String, UtilizadorCondutor> condutor;//Todos os condutores registados
    private HashMap<String, UtilizadorPassageiro> passageiro;//Todos os passageiros registados
    

    //Como um condutor ou passageiro podem estar registados e não solicitarem serviço, 
    //então tem-se que registar so os que efetuaram pedidos
    //Guardando assim os serviços pelo nick
    private ArrayList<String> servicoCondutor;
    
    //Servicos activos, aqueles que já estão em viagem
    private HashMap<String,Servico> servicosAtivos;
    
    private Lock lock = new ReentrantLock();
    //variável condição usada para quando não há condutor
    private Condition naoCondutores = lock.newCondition();
    
    //variável condição usada para quando não há mensagem do condutor para o passageiro a informar que chegou
    private Condition naoMensagemChegada = lock.newCondition();
    
    //variável condição usada para quando não há mensagem do condutor para o passageiro a informar que chegou ao destino e o preço
    private Condition naoMensagemFim = lock.newCondition();
    
    //Construtor vazio
    public Central(){
        this.condutor = new HashMap<>();
        this.passageiro = new HashMap<>();
        this.servicoCondutor = new ArrayList<>();
        this.servicosAtivos = new HashMap<>();
    }
    
    //getters
    public HashMap<String,UtilizadorCondutor> getUtilizadorCondutor(){
        return this.condutor;
    }
    public HashMap<String,UtilizadorPassageiro> getUtilizadorPassageiro(){
        return this.passageiro;
    }
    public ArrayList<String> getServicoCondutor(){
        return this.servicoCondutor;
    }
    public HashMap<String, Servico> getServicosAtivos() {
        return servicosAtivos;
    }
     
    //setters
    public void setUtilizadorPassageiro(HashMap<String,UtilizadorPassageiro> p){
        this.passageiro = p;
    }
    public void setUtilizadorCondutor(HashMap<String,UtilizadorCondutor> c){
        this.condutor = c;
    }
    public void setServicoCondutor(ArrayList<String> servicoCondutor) {
        this.servicoCondutor = servicoCondutor;
    }
    public void setServicosAtivos(HashMap<String, Servico> servicosAtivos) {
        this.servicosAtivos = servicosAtivos;
    }
    
    
    public boolean registaUtilizadorPassageiro(String nick, String pass){
        boolean res = false;
        
        lock.lock();
        try{
            if(!this.passageiro.containsKey(nick)){
                UtilizadorPassageiro p = new UtilizadorPassageiro(nick,pass);
                this.passageiro.put(nick, p);
                res = true;
            }
            
            return res;
            
        }finally{
            lock.unlock();
        }  
        
    }
    public boolean registaUtilizadorCondutor(String nick, String pass, String modelo, String matricula){
        boolean res = false;
        
        lock.lock();
        try{
            if(!this.condutor.containsKey(nick)){
                UtilizadorCondutor c = new UtilizadorCondutor(nick,pass,modelo,matricula);
                this.condutor.put(nick, c);
                res = true;
            }
            
            
             return res;
            
        }finally{
            lock.unlock();
        }  
        
        
    }
    
    //Se o cliente não estiver ativo, fica "online"
    public boolean AutenticaCondutor(String nick, String pass){
        boolean res = false;
        
        lock.lock();
        
        try{
            if(this.condutor.containsKey(nick)){
                if((!this.condutor.get(nick).isAtivo()) && this.condutor.get(nick).getPass().equals(pass)){
                    this.condutor.get(nick).setAtivo(true);
                    res = true;
                }
            }
            
             return res;
            
        }finally{
            lock.unlock();
        }
        
        
    }
    public boolean AutenticaPassageiro(String nick, String pass){
        boolean res = false;
        
        lock.lock();
        
        try{
            if(this.passageiro.containsKey(nick)){
                if((!this.passageiro.get(nick).isAtivo()) && this.passageiro.get(nick).getPass().equals(pass)){
                    this.passageiro.get(nick).setAtivo(true);
                    res = true;
                }
            }
            
            return res;
            
        }finally{
            lock.unlock();
        }
       
    }    
    
    public void logoutCondutor(String nick) {
            lock.lock();
            
            try {
                this.condutor.get(nick).setAtivo(false);
            } finally {
                lock.unlock();
            }
	}   
    public void logoutPassageiro(String nick) {
            lock.lock();
            
            try {
                this.passageiro.get(nick).setAtivo(false);
            } finally {
                lock.unlock();
            }
	}
    
    public boolean atualizarCoordPassageiro(String nick, String o, String d){
        boolean res=false;
        lock.lock();
        try{
            //Coordenadas origem
            String[] partsO = o.split("[,]");
            String[] partsO2 = partsO[1].split("[)]");
            String[] partsO1 = partsO[0].split("[(]");
                                            
            String esqO = partsO1[1];
            String dirO = partsO2[0];

            esqO = esqO.replaceAll(" ","");
            dirO = dirO.replaceAll(" ","");
            
            this.passageiro.get(nick).setCoordOX(Integer.parseInt(esqO));
            this.passageiro.get(nick).setCoordOY(Integer.parseInt(dirO));
            
            //Coordenadas partida
            String[] partsD = d.split("[,]");
            String[] partsD1 = partsD[0].split("[(]");
            String[] partsD2 = partsD[1].split("[)]");

            String esqD = partsD1[1];
            String dirD = partsD2[0];
            
            esqD = esqD.replaceAll(" ","");
            dirD = dirD.replaceAll(" ","");
            
            this.passageiro.get(nick).setCoordDX(Integer.parseInt(esqD));
            this.passageiro.get(nick).setCoordDY(Integer.parseInt(dirD));
            
            res = true;
            
            return res;
        }finally{
            lock.unlock();
        }
        
    }
    public boolean atualizarCoordCondutor(String nick,String d){
        boolean res=false;
        lock.lock();
        try{
            //Coordenadas origem
            String[] parts = d.split("[,]");
            String[] parts2 = parts[1].split("[)]");
            String[] parts1 = parts[0].split("[(]");
                                            
            String esq = parts1[1];
            String dir = parts2[0];

            esq = esq.replaceAll(" ","");
            dir = dir.replaceAll(" ","");
            
            this.condutor.get(nick).setCoordOX(Integer.parseInt(esq));
            this.condutor.get(nick).setCoordOY(Integer.parseInt(dir));
            
            res = true;
            this.naoCondutores.signalAll();
            return res;
            
        }finally{
            lock.unlock();
        }
       
    }
    
    //Condutor disponibiliza serviço
    public boolean inserirServicoCondutor(String nick){
        boolean res = false;
        lock.lock();
        try{
            this.servicoCondutor.add(nick);
            res = true;
             this.naoCondutores.signalAll();
             
             return res;
             
        }finally{
            
            lock.unlock();
        }
        
    }
    
    //Passageiro solicita serviço, e devolve nome do condutor que foi atribuído
    public String solicitarViagemPass(String nick) throws InterruptedException{       
        int px,py;//coordenadas passageiro
        int cx,cy;//coordenadas condutor
        int total;//variável para ver condutor mais perto
        String nome = null;//nome condutor
        lock.lock();
        try{
            while(this.servicoCondutor.isEmpty()){
                this.naoCondutores.await();
            }
            px = this.passageiro.get(nick).getCoordOX();
            py = this.passageiro.get(nick).getCoordOY();
                
            //Para a primeira posição
            nome = this.servicoCondutor.get(0);
            cx = this.condutor.get(nome).getCoordOX();
            cy = this.condutor.get(nome).getCoordOY();
            
            total = (Math.abs(px-cx)+Math.abs(py-cy));    
            for (int i = 1; i < this.servicoCondutor.size();i++) {
                cx = this.condutor.get(nome).getCoordOX();
                cy = this.condutor.get(nome).getCoordOY();
                    
                if((Math.abs(px-cx)+Math.abs(py-cy)) < total){
                    nome = this.servicoCondutor.get(i);
                }
            }
            
            this.servicoCondutor.remove(nome);
            
            return nome;
        }finally{
            
            lock.unlock();
        }
        
    }
    
    //Depois de finalizado o serviço, remove da hash
    public boolean removerServico(String nome){
        boolean res = false;
        lock.lock();
        
        try{
            this.servicosAtivos.remove(nome);//remover elemento na hash, com chave condutor
            res = true;
             return res;
            
        }finally{
            lock.unlock();
        }
        
    }
    
    //nome -> nome condutor
    //Quando devolver true(sai do wait), então vai mandar mensagem para o passageiro
    public boolean mandaCoordenadas(String nome) throws InterruptedException{
        boolean res = false;
    
        lock.lock();
        
        try{
            while(!this.servicosAtivos.containsKey(nome)){
                this.naoCondutores.await();
            }
            
            res = true;
            
             return res;
        }finally{
          
            lock.unlock();
        }
        
    }
    
    //Insere serviço nos serviços ativos
    public void insereServicosAtivos(String condutor,String passageiro){
        lock.lock();
        try{
            int px = this.passageiro.get(passageiro).getCoordOX();
            int py = this.passageiro.get(passageiro).getCoordOY();
            
            //Estas coordenadas é para depois calcular o preço, mas em principio será passado no menu do cliente
            int cx = this.passageiro.get(passageiro).getCoordDX();
            int cy = this.passageiro.get(passageiro).getCoordDY(); 
            
            this.servicosAtivos.put(condutor, new Servico(passageiro,px,py,cx,cy,0,null,null));
           
            this.naoCondutores.signalAll();
        }finally{
            
            lock.unlock();
        }
    }
    
    //manda e acorda threads em espera
    public void enviaMensagemChegada(String nome, String mensagem){
        lock.lock();
        try{            
            this.servicosAtivos.get(nome).setMensagemChegada(mensagem);
            
            this.naoMensagemChegada.signalAll();
        
        }finally{
            
            lock.unlock();
        }
    }
    public void enviaMensagemFim(String nome, String mensagem,double preco){
        lock.lock();
        try{            
            this.servicosAtivos.get(nome).setMensagemFim(mensagem);
            this.servicosAtivos.get(nome).setPreco(preco);
        
        this.naoMensagemFim.signalAll();
        }finally{
           
            lock.unlock();
        }
    }
    
    public boolean recebeMensagemFim(String nome) throws InterruptedException{
        boolean res = false;
        lock.lock();
        try {
            while(this.servicosAtivos.get(nome).getMensagemFim() == null && this.servicosAtivos.get(nome).getPreco() == 0){
                this.naoMensagemFim.await();
            }
            
            res = true;
            return res;
        } finally {
           
            lock.unlock();
        }
        
    }
    public boolean recebeMensagemChegada(String nome) throws InterruptedException{
        boolean res = false;
        lock.lock();
        try{
            while(this.servicosAtivos.get(nome).getMensagemChegada() == null){
                this.naoMensagemChegada.await();
            }
            
             res = true;
             return res;
        }finally{
          
            lock.unlock();
        }
       
    }
    
}
