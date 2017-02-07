import org.snmp4j.agent.MOAccess;
import org.snmp4j.agent.mo.snmp.DisplayStringScalar;
import org.snmp4j.agent.request.SubRequest;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.OctetString;
import org.snmp4j.smi.Variable;

/**
* Created by kratos on 07-02-2017.
*/ // Scalars
public class Reset extends DisplayStringScalar<OctetString> {
  Reset(OID oid, MOAccess access) {
    super(oid, access, new OctetString(),
          0,
          255);
//--AgentGen BEGIN=reset
//--AgentGen END
  }

  public int isValueOK(SubRequest request) {
    Variable newValue =
      request.getVariableBinding().getVariable();
    int valueOK = super.isValueOK(request);
    if (valueOK != SnmpConstants.SNMP_ERROR_SUCCESS) {
      return valueOK;
    }
    OctetString os = (OctetString)newValue;
    if (!(((os.length() >= 0) && (os.length() <= 255)))) {
      valueOK = SnmpConstants.SNMP_ERROR_WRONG_LENGTH;
    }
   //--AgentGen BEGIN=reset::isValueOK
   //--AgentGen END
    return valueOK;
  }

  public OctetString getValue() {
   //--AgentGen BEGIN=reset::getValue
   //--AgentGen END
    return super.getValue();
  }

  public int setValue(OctetString newValue) {
   //--AgentGen BEGIN=reset::setValue
   //--AgentGen END
    return super.setValue(newValue);
  }

   //--AgentGen BEGIN=reset::_METHODS
   //--AgentGen END

}
