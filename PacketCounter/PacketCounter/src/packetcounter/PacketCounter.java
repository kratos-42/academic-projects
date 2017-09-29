/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package packetcounter;

import static java.lang.System.out;

/**
 *
 * @author Sandra
 */
public class PacketCounter {
    private static SNMPAgent sessao;
    private static Poll pollIn;
    private static Poll pollIn2;
    private static Poll pollOut;
    private static Poll pollOut2;
    private static String endereco;
    private static String ip;
    private static String porta;

    public static void main(String[] args) {
        System.out.println("Insira os seguintes dados:IP Porta \n");
        if(args.length!=2){
            System.out.println("Os argumentos inseridos não estão de acordo com o pedido \n");
            System.out.println("Insira os seguintes dados:IP Porta \n");
        }
        else{
            ip=args[0];
            porta= args[1];
            endereco= ip+"/"+porta;
            sessao= new SNMPAgent(endereco);
            sessao.start();


            Grafico grafico = new Grafico("Packet Counter","Monitorização");
            grafico.pack();
            //public AtualizaGrafico(SNMPAgent s, String oidIn, oidOut, Grafico g)
            //pollin
            pollIn = new Poll(sessao, "1.3.6.1.2.1.2.2.1.10.2", grafico, "in");
            pollIn.start();

            //poll out
            pollOut = new Poll(sessao, "1.3.6.1.2.1.2.2.1.16.2", grafico, "out");
            pollOut.start();


            grafico.setVisible(true);
        }
    }

}