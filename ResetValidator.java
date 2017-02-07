import org.snmp4j.agent.mo.MOValueValidationEvent;
import org.snmp4j.agent.mo.MOValueValidationListener;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.smi.OctetString;
import org.snmp4j.smi.Variable;

/**
 * The <code>ResetValidator</code> implements the value
 * validation for <code>Reset</code>.
 */
class ResetValidator implements MOValueValidationListener {

  public void validate(MOValueValidationEvent validationEvent) {
    Variable newValue = validationEvent.getNewValue();
    OctetString os = (OctetString)newValue;
    if (!(((os.length() >= 0) && (os.length() <= 255)))) {
      validationEvent.setValidationStatus(SnmpConstants.SNMP_ERROR_WRONG_LENGTH);
      return;
    }
   //--AgentGen BEGIN=reset::validate
   //--AgentGen END
  }
}
