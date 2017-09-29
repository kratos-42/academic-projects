import java.math.BigDecimal;
import java.sql.Time;
import java.sql.Timestamp;

/**
 * Created by kratos on 19-04-2017.
 */
public class InfoTable {

    Timestamp rtt;
    double packetLossRate;
    int nrConnections;
    Timestamp timeStart;
    int in;
    int out;


    public InfoTable(Timestamp r, double prl, int nrc, int in, int out){

        this.rtt = r;
        this.packetLossRate = prl;
        this.nrConnections = nrc;
        this.in = in;
        this.out = out;
    }

    public void infoUpdate(Timestamp r, double prl, int nr){
        this.rtt = r;
        this.packetLossRate = prl;
        this.nrConnections = nr;
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

    public double getPacketLossRate() {
        return packetLossRate;
    }

    public void setPacketLossRate(double packetLossRate) {
        this.packetLossRate = packetLossRate;
    }

    public int getNrConexoes() {
        return nrConnections;
    }

    public void setNrConexoes(int nrConnections) {
        this.nrConnections = nrConnections;
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
        this.nrConnections++;
    }



}
