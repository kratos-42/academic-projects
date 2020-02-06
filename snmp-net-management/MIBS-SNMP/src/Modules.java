 

//--AgentGen BEGIN=_BEGIN
//--AgentGen END

import org.snmp4j.agent.mo.*;
import org.snmp4j.log.LogFactory;
import org.snmp4j.log.LogAdapter;
import org.snmp4j.agent.MOGroup;
import org.snmp4j.agent.MOServer;
import org.snmp4j.agent.DuplicateRegistrationException;
import org.snmp4j.smi.OctetString;

import java.io.IOException;
import java.text.ParseException;


//--AgentGen BEGIN=_IMPORT
//--AgentGen END

public class Modules implements MOGroup {

  private static final LogAdapter LOGGER = 
      LogFactory.getLogger(Modules.class);

  private SNMPv2_CONF sNMPv2Conf;
  private SNMPv2_SMI sNMPv2Smi;
  private SNMPv2_TC sNMPv2Tc;
  private RANDOM_MIB randomMib;

  private MOFactory factory;

//--AgentGen BEGIN=_MEMBERS
//--AgentGen END

  public Modules() {
   sNMPv2Conf = new SNMPv2_CONF();
   sNMPv2Smi = new SNMPv2_SMI();
   sNMPv2Tc = new SNMPv2_TC();
   randomMib = new RANDOM_MIB();
//--AgentGen BEGIN=_DEFAULTCONSTRUCTOR
//--AgentGen END
  }

  public Modules(MOFactory factory) throws IOException, ParseException{
   sNMPv2Conf = new SNMPv2_CONF(factory);
   sNMPv2Smi = new SNMPv2_SMI(factory);
   sNMPv2Tc = new SNMPv2_TC(factory);
   randomMib = new RANDOM_MIB(factory);
//--AgentGen BEGIN=_CONSTRUCTOR
//--AgentGen END
  } 

  public void registerMOs(MOServer server, OctetString context) 
    throws DuplicateRegistrationException 
  {
	  sNMPv2Conf.registerMOs(server, context);
	  sNMPv2Smi.registerMOs(server, context);
	  sNMPv2Tc.registerMOs(server, context);
	  randomMib.registerMOs(server, context);
//--AgentGen BEGIN=_registerMOs
//--AgentGen END
  }

  public void unregisterMOs(MOServer server, OctetString context) {
	  sNMPv2Conf.unregisterMOs(server, context);
	  sNMPv2Smi.unregisterMOs(server, context);
	  sNMPv2Tc.unregisterMOs(server, context);
	  randomMib.unregisterMOs(server, context);
//--AgentGen BEGIN=_unregisterMOs
//--AgentGen END
  }

  public SNMPv2_CONF getSNMPv2Conf() {
    return sNMPv2Conf;
  }
  public SNMPv2_SMI getSNMPv2Smi() {
    return sNMPv2Smi;
  }
  public SNMPv2_TC getSNMPv2Tc() {
    return sNMPv2Tc;
  }
  public RANDOM_MIB getRandomMib() {
    return randomMib;
  }


//--AgentGen BEGIN=_METHODS
//--AgentGen END

//--AgentGen BEGIN=_CLASSES
//--AgentGen END

//--AgentGen BEGIN=_END
//--AgentGen END

}

