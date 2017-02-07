import org.snmp4j.agent.mo.DefaultMOMutableRow2PC;
import org.snmp4j.smi.Integer32;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.OctetString;
import org.snmp4j.smi.Variable;

/**
* Created by kratos on 07-02-2017.
*/
public class UnpredictableEntryRow extends DefaultMOMutableRow2PC {

   //--AgentGen BEGIN=unpredictableEntry::RowMembers
   //--AgentGen END

  public UnpredictableEntryRow(OID index, Variable[] values) {
    super(index, values);
   //--AgentGen BEGIN=unpredictableEntry::RowConstructor
   //--AgentGen END
  }

  public Integer32 getIndice() {
   //--AgentGen BEGIN=unpredictableEntry::getIndice
   //--AgentGen END
    return (Integer32) super.getValue(idxIndice);
  }

  public void setIndice(Integer32 newColValue) {
   //--AgentGen BEGIN=unpredictableEntry::setIndice
   //--AgentGen END
    super.setValue(idxIndice, newColValue);
  }

  public OctetString getValueH() {
   //--AgentGen BEGIN=unpredictableEntry::getValueH
   //--AgentGen END
    return (OctetString) super.getValue(idxValueH);
  }

  public void setValueH(OctetString newColValue) {
   //--AgentGen BEGIN=unpredictableEntry::setValueH
   //--AgentGen END
    super.setValue(idxValueH, newColValue);
  }

  public Variable getValue(int column) {
   //--AgentGen BEGIN=unpredictableEntry::RowGetValue
   //--AgentGen END
    switch(column) {
      case idxIndice:
          return getIndice();
      case idxValueH:
          return getValueH();
      default:
        return super.getValue(column);
    }
  }

  public void setValue(int column, Variable value) {
   //--AgentGen BEGIN=unpredictableEntry::RowSetValue
   //--AgentGen END
    switch(column) {
      case idxIndice:
          setIndice((Integer32)value);
          break;
      case idxValueH:
          setValueH((OctetString)value);
          break;
      default:
        super.setValue(column, value);
    }
  }

   //--AgentGen BEGIN=unpredictableEntry::Row
   //--AgentGen END
}
