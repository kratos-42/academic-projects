package projecto;

import java.io.Serializable;
import java.util.HashMap;


public class PacoteDados implements Serializable {
    private final String accao;
    private final HashMap<String,String> argumentos;
    
    public PacoteDados(String a, HashMap<String,String> args){
        this.accao = a;
        this.argumentos = args;
    }
    
    public String getAccao(){
        return accao;
    }
    
    public HashMap<String,String> getArgumentos(){
        return argumentos;
    }
}
