/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package packetcounter;

import java.io.IOException;
import static java.lang.Thread.sleep;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.snmp4j.smi.OID;

/**
 *
 * @author Sandra
 */
public class Poll extends Thread{

    private SNMPAgent sessao;
    private String oid;
    private String respAnt;
    private int delayPoll;
    private int dif;
    private String respAtual;
    private Grafico grafico;
    private String id;


    public Poll(SNMPAgent s, String oid, Grafico g, String id) {
        this.sessao = s;
        this.grafico = g;
        this.oid = oid;
        this.respAnt = "0";
        this.dif = 0;
        this.delayPoll = 1000;
        this.id=id;
    }


    public void run() {

        OID oidToPoll = new OID(oid);
        try {
            System.out.println("resp:" + sessao.getAsString(oidToPoll));
            respAnt = sessao.getAsString(oidToPoll);
        } catch (IOException ex) {
            Logger.getLogger(Poll.class.getName()).log(Level.SEVERE, null, ex);
        }

        while (true) {
            try {
                respAtual = sessao.getAsString(oidToPoll);
            } catch (IOException ex) {
                Logger.getLogger(Poll.class.getName()).log(Level.SEVERE, null, ex);
            }
            System.out.println(respAtual);
            dif = Integer.parseInt(respAtual) - Integer.parseInt(respAnt);
            //verifica se o valor da ultima poll é igual ao da autal
            if (dif == 0)
                delayPoll *= 1.5;
            else
                delayPoll -= delayPoll*0.01;

            respAnt = respAtual;
            if(id.equals("in"))
                grafico.atualizarIn(new Millisecond(), dif);
            else if (id.equals("out"))
                grafico.atualizarOut(new Millisecond(), dif);
            try {
                sleep(delayPoll);
            } catch (InterruptedException ex) {
                Logger.getLogger(Poll.class.getName()).log(Level.SEVERE, null, ex);
            }


        }
    }
}