package packetcounter;

import java.io.IOException;
import static org.jfree.util.Log.log;
import org.snmp4j.CommunityTarget;
import org.snmp4j.PDU;
import org.snmp4j.Snmp;
import org.snmp4j.TransportMapping;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.smi.Address;
import org.snmp4j.smi.GenericAddress;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.OctetString;
import org.snmp4j.smi.VariableBinding;
import org.snmp4j.transport.DefaultUdpTransportMapping;

/**
 *
 * @author Sandra
 */
public class SNMPAgent {

    private static Snmp session;
    private static String address;

    public SNMPAgent(String address) {
        this.address = address;
    }

    public static String getAsString(OID oid) throws IOException {

        System.out.println("oid    " + oid);
        ResponseEvent event = get(new OID[] { oid });
        System.out.println("event     " + event);
        System.out.println("resp     " + event.getResponse());
        return event.getResponse().get(0).getVariable().toString();

    }

    public static ResponseEvent get(OID oids[]) throws IOException {
        PDU pdu = new PDU();
        for (OID oid : oids) {
            pdu.add(new VariableBinding(oid));
        }
        pdu.setType(PDU.GET);
        ResponseEvent event = session.send(pdu, (org.snmp4j.Target) getTarget(), null);
        if(event != null) {
            return event;
        }
        throw new RuntimeException("GET timed out");
    }

    private static org.snmp4j.Target getTarget() {
        Address targetAddress = GenericAddress.parse(address);
        CommunityTarget target = new CommunityTarget();
        target.setCommunity(new OctetString("public"));
        target.setAddress(targetAddress);
        target.setRetries(2);
        target.setTimeout(1500);
        target.setVersion(SnmpConstants.version2c);
        return (org.snmp4j.Target) target;
    }

    /**
     * Start snmp Session
     */
    public static void start() {
        try {
            TransportMapping transport = new DefaultUdpTransportMapping();
            session = new Snmp(transport);
            transport.listen();
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
}