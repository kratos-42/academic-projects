/**
 * Created by kratos on 19-04-2017.
 */
public class InfoTable {


    public double getRtt() {
        return rtt;
    }

    public void setRtt(double rtt) {
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

    double rtt;
    double taxaPacotesPerdidos;
    int nrConexoes;

    public InfoTable(double r, double tpp, int nrc){

        this.rtt = r;
        this.taxaPacotesPerdidos = tpp;
        this.nrConexoes = nrc;
    }


}
