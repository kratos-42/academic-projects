import java.math.BigDecimal;
import java.sql.Time;
import java.sql.Timestamp;

/**
 * Created by kratos on 19-04-2017.
 */
public class InfoTable {

    Timestamp rtt;
    double taxaPacotesPerdidos;
    int nrConexoes;
    Timestamp timeStart;
    int in;
    int out;


    public InfoTable(Timestamp r, double tpp, int nrc, int in, int out){

        this.rtt = r;
        this.taxaPacotesPerdidos = tpp;
        this.nrConexoes = nrc;
        this.in = in;
        this.out = out;
    }

    public InfoTable(){
        this.out = 1;
    }

    public Timestamp getRtt() {
        return rtt;
    }

    public void setRtt(Timestamp rtt) {
        this.rtt = rtt;
    }

    public double getTaxaPacotesPerdidos() {
        return taxaPacotesPerdidos;
    }

    public void setTaxaPacotesPerdidos(double taxaPacotesPerdidos) {
        this.taxaPacotesPerdidos = taxaPacotesPerdidos;
    }

    public int getNrConexoes() {
        return nrConexoes;
    }

    public void setNrConexoes(int nrConexoes) {
        this.nrConexoes = nrConexoes;
    }

    public int getIn() {
        return in;
    }

    public void setIn(int in) {
        this.in = in;
    }


    public int getOut() {
        return out;
    }

    public void setOut(int out) {
        this.out = out;
    }


    public Timestamp getTimeStart() {
        return timeStart;
    }

    public void setTimeStart(Timestamp timeStart) {
        this.timeStart = timeStart;

    }

    public void updateNrConexoes(){
        this.nrConexoes++;
    }



}
