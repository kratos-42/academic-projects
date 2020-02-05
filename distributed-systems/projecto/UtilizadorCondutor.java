package projecto;

public class UtilizadorCondutor {
    private String nick;
    private String pass;
    private String modelo;
    private String matricula;
    private boolean ativo;
    private int coordOX;
    private int coordOY;
    
    //Construtores
    public UtilizadorCondutor(){
        this.nick = "";
        this.pass = "";
        this.modelo = "";
        this.matricula = "";
        this.ativo = false;
        this.coordOX = 0;
        this.coordOY = 0;
    }
    public UtilizadorCondutor(String n, String p, String m, String mat){
        this.nick = n;
        this.pass = p;
        this.modelo = m;
        this.matricula = mat;
        this.ativo = false;
        this.coordOX = 0;
        this.coordOY = 0;
    }  
    public UtilizadorCondutor(UtilizadorCondutor u){
        this.nick = u.getNick();
        this.pass = u.getPass();
        this.modelo = u.getModelo();
        this.matricula = u.getMatricula();
        this.ativo = u.isAtivo();
        this.coordOX = u.getCoordOX();
        this.coordOY = u.getCoordOY();
    }
    
    //getters
    public String getNick() {
        return nick;
    }
    public String getPass() {
        return pass;
    }
    public String getModelo() {
        return modelo;
    }
    public String getMatricula() {
        return matricula;
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

    //setters
    public void setNick(String nick) {
        this.nick = nick;
    }
    public void setPass(String pass) {
        this.pass = pass;
    }
    public void setModelo(String modelo) {
        this.modelo = modelo;
    }
    public void setMatricula(String matricula) {
        this.matricula = matricula;
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
    
    //clone
    public UtilizadorCondutor clone(){
        return new UtilizadorCondutor(this);
    }
    
    //toString
    public String toString() {
        StringBuilder s = new StringBuilder("***Utilizador Condutor***\n");
        s.append("Utilizador: " + this.getNick()+"\n");
	s.append("Password: " + this.getPass()+"\n");
        s.append("Modelo do carro: " + this.getModelo()+"\n");
        s.append("Matricula do carro: " + this.getMatricula()+"\n");
	return s.toString();
    }
    
    //Equals
    public boolean equals(Object o) {
        if (this == o)
            return true;
	if ((o == null) || (o.getClass() != this.getClass())){
            return false;
        }else {
            UtilizadorCondutor c = (UtilizadorCondutor) o;
            return (this.getNick().equals(c.getNick()) && (this.getPass().equals(c.getPass())) &&
                    this.getModelo().equals(c.getModelo()) && this.getMatricula().equals(c.getModelo()));
	}
    }    
}
