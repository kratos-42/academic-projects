package projecto;

public class Servico {
    private String passageiro;
    private int coordx;
    private int coordy;
    private int coordDestinox;
    private int coordDestinoy;
    private double preco;
    private String mensagemChegada;
    private String mensagemFim;
    
    //Construtor
    public Servico(String passageiro, int x, int y,int dx,int dy, double p,String mc, String mf) {
        this.passageiro = passageiro;
        this.coordx = x;
        this.coordy = y;
        this.coordDestinox = dx;
        this.coordDestinoy = dy;
        this.preco = p;
        this.mensagemChegada = mc;
        this.mensagemFim = mf;
    }
    public Servico(){
        this.passageiro = null;
        this.coordx = 0;
        this.coordy = 0;
        this.coordDestinox = 0;
        this.coordDestinoy = 0;
        this.preco = 0;
        this.mensagemChegada = null;
        this.mensagemFim = null;
    }
    public Servico(Servico s){
        this.passageiro = s.getPassageiro();
        this.coordx = s.getCoordx();
        this.coordy = s.getCoordy();
        this.coordDestinox = s.getCoordDestinox();
        this.coordDestinoy = s.getCoordDestinoy();
        this.preco = s.getPreco();
        this.mensagemChegada = s.getMensagemChegada();
        this.mensagemFim = s.getMensagemFim();
    }

    //getters
    public String getPassageiro() {
        return passageiro;
    }
    public int getCoordx() {
        return coordx;
    }
    public int getCoordy() {
        return coordy;
    }
    public double getPreco() {
        return preco;
    }
    public String getMensagemChegada() {
        return mensagemChegada;
    }
    public String getMensagemFim() {
        return mensagemFim;
    }
    public int getCoordDestinox() {
        return coordDestinox;
    }
    public int getCoordDestinoy() {
        return coordDestinoy;
    }
    
    
    //setters
    public void setPassageiro(String passageiro) {
        this.passageiro = passageiro;
    }
    public void setCoordx(int coordx) {
        this.coordx = coordx;
    }
    public void setCoordy(int coordy) {
        this.coordy = coordy;
    }
    public void setPreco(double preco) {
        this.preco = preco;
    }
    public void setMensagemChegada(String mensagemChegada) {
        this.mensagemChegada = mensagemChegada;
    }
    public void setMensagemFim(String mensagemFim) {
        this.mensagemFim = mensagemFim;
    }
    public void setCoordDestinox(int coordDestinox) {
        this.coordDestinox = coordDestinox;
    }
    public void setCoordDestinoy(int coordDestinoy) {
        this.coordDestinoy = coordDestinoy;
    }
    
    
    //clone
    public Servico clone(){
        return new Servico(this);
    }
    
    //toString
    public String toString() {
        StringBuilder s = new StringBuilder("***Serviço Utilizador Condutor***\n");
        s.append("Passageiro: " + this.getPassageiro()+"\n");
	s.append("Coordenada x: " + this.getCoordx()+"\n");
        s.append("Coordenada y: " + this.getCoordy()+"\n");
	s.append("Coordenada destino x: " + this.getCoordDestinox()+"\n");
        s.append("Coordenada destino y: " + this.getCoordDestinoy()+"\n");
        s.append("Preço: " + this.getPreco() + "\n");
        s.append("Mensagem de chegada: " + this.getMensagemChegada() + "\n");
        s.append("Preço: " + this.getPreco() + "\n");
        return s.toString();
    }
    
    //Equals
    public boolean equals(Object o) {
        if (this == o)
            return true;
	if ((o == null) || (o.getClass() != this.getClass())){
            return false;
        }else {
            Servico c = (Servico) o;
            return (this.getPassageiro().equals(c.getPassageiro()) && (this.getCoordx() == c.getCoordx()) &&
                    this.getCoordy()==c.getCoordy() && this.getPreco()==c.getPreco() && 
                    this.getCoordDestinox() == c.getCoordDestinox() && this.getCoordDestinoy() == c.getCoordDestinoy() &&
                    this.getMensagemChegada().equals(c.getMensagemChegada())&& 
                    this.getMensagemFim().equals(c.getMensagemFim()));
	}
    }    
    
}
