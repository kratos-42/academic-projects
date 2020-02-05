package projecto;

public class UtilizadorPassageiro {
    private String nick;
    private String pass;
    private boolean ativo;
    private int coordOX;
    private int coordOY;
    private int coordDX;
    private int coordDY;
    
    //Construtores
    public UtilizadorPassageiro(){
        this.nick = "";
        this.pass = "";
        this.ativo = false;
        this.coordOX = 0;
        this.coordOY = 0;
        this.coordDX = 0;
        this.coordDY = 0;
    }   
    public UtilizadorPassageiro(String n, String p){
        this.nick = n;
        this.pass = p;
        this.ativo = false;
        this.coordOX = 0;
        this.coordOY = 0;
        this.coordDX = 0;
        this.coordDY = 0;
    } 
    public UtilizadorPassageiro(UtilizadorPassageiro u){
        this.nick = u.getNick();
        this.pass = u.getPass();
        this.ativo = u.isAtivo();
        this.coordOX = u.getCoordOX();
        this.coordOY = u.getCoordOY();
        this.coordDX = u.getCoordDX();
        this.coordDY = u.getCoordDY();
    }
    
    //getters
    public String getNick() {
        return nick;
    }
    public String getPass() {
        return pass;
    }
    public boolean isAtivo() {
        return ativo;
    }    
    public int getCoordOX() {
        return coordOX;
    }
    public int getCoordOY() {
        return coordOY;
    }
    public int getCoordDX() {
        return coordDX;
    }
    public int getCoordDY() {
        return coordDY;
    }
    
    //setters
    public void setNick(String nick) {
        this.nick = nick;
    }
    public void setPass(String pass) {
        this.pass = pass;
    }
    public void setAtivo(boolean ativo) {
        this.ativo = ativo;
    } 
    public void setCoordOX(int coordOX) {
        this.coordOX = coordOX;
    }
    public void setCoordOY(int coordOY) {
        this.coordOY = coordOY;
    }
    public void setCoordDX(int coordDX) {
        this.coordDX = coordDX;
    }
    public void setCoordDY(int coordDY) {
        this.coordDY = coordDY;
    }
    
    //clone
    public UtilizadorPassageiro clone(){
        return new UtilizadorPassageiro(this);
    }
    
    //toString
    public String toString() {
        StringBuilder s = new StringBuilder("***Utilizador Passageiro***\n");
        s.append("Utilizador: " + this.getNick());
	s.append("Password: " + this.getPass());
        s.append("Coordenas Origem: (" + this.getCoordOX()+","+this.getCoordOY()+")" );
        s.append("Coordenas Destino: (" + this.getCoordDX()+","+this.getCoordDY()+")" );
	return s.toString();
    }
    
    //Equals
    public boolean equals(Object o) {
        if (this == o)
            return true;
	if ((o == null) || (o.getClass() != this.getClass())){
            return false;
        }else {
            UtilizadorPassageiro c = (UtilizadorPassageiro) o;
            return (this.getNick().equals(c.getNick()) && (this.getPass().equals(c.getPass())));
	}
    }
}
