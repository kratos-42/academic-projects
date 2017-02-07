import org.snmp4j.agent.mo.MOFactory;
import org.snmp4j.agent.mo.MOTableRowFactory;
import org.snmp4j.smi.OID;
import org.snmp4j.smi.Variable;

/**
 * Created by kratos on 07-02-2017.
 */
class UnpredictableEntryRowFactory
        implements MOTableRowFactory<UnpredictableEntryRow>
  {
    public synchronized UnpredictableEntryRow createRow(OID index, Variable[] values)
        throws UnsupportedOperationException
    {
      UnpredictableEntryRow row =
        new UnpredictableEntryRow(index, values);
     //--AgentGen BEGIN=unpredictableEntry::createRow
     //--AgentGen END
      return row;
    }

    public synchronized void freeRow(UnpredictableEntryRow row) {
     //--AgentGen BEGIN=unpredictableEntry::freeRow
     //--AgentGen END
    }

     //--AgentGen BEGIN=unpredictableEntry::RowFactory
     //--AgentGen END
  }


//--AgentGen BEGIN=_METHODS
//--AgentGen END

  // Textual Definitions of MIB module RANDOM-MIB
  protected void addTCsToFactory(MOFactory moFactory) {
  }


//--AgentGen BEGIN=_TC_CLASSES_IMPORTED_MODULES_BEGIN
//--AgentGen END

  // Textual Definitions of other MIB modules
  public void addImportedTCsToFactory(MOFactory moFactory) {
  }


//--AgentGen BEGIN=_TC_CLASSES_IMPORTED_MODULES_END
//--AgentGen END

//--AgentGen BEGIN=_CLASSES
//--AgentGen END

//--AgentGen BEGIN=_END
//--AgentGen END


// -----------------------------------------------------------------------------------------------------


    public void readConfig(){

        try(BufferedReader br = new BufferedReader())

    }

  }
