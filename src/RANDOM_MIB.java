 

//--AgentGen BEGIN=_BEGIN
//--AgentGen END

import org.snmp4j.smi.*;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.agent.*;
import org.snmp4j.agent.mo.*;
import org.snmp4j.agent.mo.snmp.*;
import org.snmp4j.agent.request.*;
import org.snmp4j.log.LogFactory;
import org.snmp4j.log.LogAdapter;

import java.io.*;
import java.text.ParseException;
import org.snmp4j.smi.OctetString;


//--AgentGen BEGIN=_IMPORT
//--AgentGen END

public class RANDOM_MIB
//--AgentGen BEGIN=_EXTENDS
//--AgentGen END
implements MOGroup 
//--AgentGen BEGIN=_IMPLEMENTS
//--AgentGen END
{

  private static final LogAdapter LOGGER = 
      LogFactory.getLogger(RANDOM_MIB.class);

//--AgentGen BEGIN=_STATIC
//--AgentGen END

  // Factory
  private MOFactory moFactory = 
    DefaultMOFactory.getInstance();

  // Constants 

  /**
   * OID of this MIB module for usage which can be 
   * used for its identification.
   */
  public static final OID oidRandomMib =
    new OID(new int[] { 1,3,6,1,3,95 });

  // Identities
  // Scalars
  public static final OID oidFrequencia = 
    new OID(new int[] { 1,3,6,1,3,95,4,1,0 });
  public static final OID oidNumEntradas = 
    new OID(new int[] { 1,3,6,1,3,95,4,2,0 });
  public static final OID oidNumDigitosH = 
    new OID(new int[] { 1,3,6,1,3,95,4,3,0 });
  public static final OID oidReset = 
    new OID(new int[] { 1,3,6,1,3,95,4,4,0 });
  // Tables

  // Notifications

  // Enumerations




  // TextualConventions
  private static final String TC_MODULE_SNMPV2_TC = "SNMPv2-TC";
  private static final String TC_DISPLAYSTRING = "DisplayString";

  // Scalars
  private MOScalar<Integer32> frequencia ;
  private MOScalar<Integer32> numEntradas;
  private MOScalar<Integer32> numDigitosH;
  private MOScalar<OctetString> reset;

  private String seed;
  private int[] valoresEscalares = new int[100];
  private int port;
  private String community;

  // Tables
  public static final OID oidUnpredictableEntry = 
    new OID(new int[] { 1,3,6,1,3,95,5,1 });

  // Index OID definitions
  public static final OID oidIndice =
    new OID(new int[] { 1,3,6,1,3,95,5,1,1 });

  // Column TC definitions for unpredictableEntry:
  public static final String tcModuleSNMPv2Tc = "SNMPv2-TC";
  public static final String tcDefDisplayString = "DisplayString";
    
  // Column sub-identifier definitions for unpredictableEntry:
  public static final int colIndice = 1;
  public static final int colValueH = 2;

  // Column index definitions for unpredictableEntry:
  public static final int idxIndice = 0;
  public static final int idxValueH = 1;

  private MOTableSubIndex[] unpredictableEntryIndexes;
  private MOTableIndex unpredictableEntryIndex;
  
  private MOTable<UnpredictableEntryRow,
                  MOColumn,
                  MOTableModel<UnpredictableEntryRow>> unpredictableEntry;
  private MOTableModel<UnpredictableEntryRow> unpredictableEntryModel;


//--AgentGen BEGIN=_MEMBERS
//--AgentGen END

  /**
   * Constructs a RANDOM-MIB instance without actually creating its
   * <code>ManagedObject</code> instances. This has to be done in a
   * sub-class constructor or after construction by calling 
   * {@link #createMO(MOFactory moFactory)}. 
   */
  protected RANDOM_MIB() {
//--AgentGen BEGIN=_DEFAULTCONSTRUCTOR
//--AgentGen END
  }

  /**
   * Constructs a RANDOM-MIB instance and actually creates its
   * <code>ManagedObject</code> instances using the supplied 
   * <code>MOFactory</code> (by calling
   * {@link #createMO(MOFactory moFactory)}).
   * @param moFactory
   *    the <code>MOFactory</code> to be used to create the
   *    managed objects for this module.
   */
  public RANDOM_MIB(MOFactory moFactory) throws IOException, ParseException {
  	this();
    createMO(moFactory);
//--AgentGen BEGIN=_FACTORYCONSTRUCTOR
//--AgentGen END
  }

//--AgentGen BEGIN=_CONSTRUCTORS
//--AgentGen END

  /**
   * Create the ManagedObjects defined for this MIB module
   * using the specified {@link MOFactory}.
   * @param moFactory
   *    the <code>MOFactory</code> instance to use for object 
   *    creation.
   */
  protected void createMO(MOFactory moFactory) throws IOException, ParseException{
    loadConfig();

    addTCsToFactory(moFactory);
    frequencia = 
      moFactory.createScalar(oidFrequencia,
                             moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY), 
                             new Integer32(valoresEscalares[0]));
    numEntradas = 
      moFactory.createScalar(oidNumEntradas,
                             moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY), 
                             new Integer32(valoresEscalares[1]));
    numDigitosH = 
      moFactory.createScalar(oidNumDigitosH,
                             moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY), 
                             new Integer32(valoresEscalares[2]));

    reset =
      new Reset(oidReset, 
                moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE));
    reset.addMOValueValidationListener(new ResetValidator());
    createUnpredictableEntry(moFactory);
  }

  public MOScalar<Integer32> getFrequencia() {
    return frequencia;
  }
  public MOScalar<Integer32> getNumEntradas() {
    return numEntradas;
  }
  public MOScalar<Integer32> getNumDigitosH() {
    return numDigitosH;
  }
  public MOScalar<OctetString> getReset() {
    return reset;
  }


  public MOTable<UnpredictableEntryRow,MOColumn,MOTableModel<UnpredictableEntryRow>> getUnpredictableEntry() {
    return unpredictableEntry;
  }


  @SuppressWarnings(value={"unchecked"})
  private void createUnpredictableEntry(MOFactory moFactory) throws ParseException, IOException{
    // Index definition
    unpredictableEntryIndexes = 
      new MOTableSubIndex[] {
      moFactory.createSubIndex(oidIndice, 
                               SMIConstants.SYNTAX_INTEGER, 1, 1)    };

    unpredictableEntryIndex = 
      moFactory.createIndex(unpredictableEntryIndexes,
                            false,
                            new MOTableIndexValidator() {
      public boolean isValidIndex(OID index) {
        boolean isValidIndex = true;
     //--AgentGen BEGIN=unpredictableEntry::isValidIndex
     //--AgentGen END
        return isValidIndex;
      }

    });

    // Columns
    MOColumn[] unpredictableEntryColumns = new MOColumn[2];
    unpredictableEntryColumns[idxIndice] = 
      moFactory.createColumn(colIndice,
                             SMIConstants.SYNTAX_INTEGER32,
                             moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY));
    unpredictableEntryColumns[idxValueH] = 
      moFactory.createColumn(colValueH,
                             SMIConstants.SYNTAX_OCTET_STRING,
                             moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
                             TC_MODULE_SNMPV2_TC,
                             TC_DISPLAYSTRING);
    // Table model
    unpredictableEntryModel = 
      moFactory.createTableModel(oidUnpredictableEntry,
                                 unpredictableEntryIndex,
                                 unpredictableEntryColumns);
    ((MOMutableTableModel<UnpredictableEntryRow>)unpredictableEntryModel).setRowFactory(
      new UnpredictableEntryRowFactory());

    unpredictableEntry = 
      moFactory.createTable(oidUnpredictableEntry,
                            unpredictableEntryIndex,
                            unpredictableEntryColumns,
                            unpredictableEntryModel);




    Variable[] var = new Variable[1000];
    OID newOID;
    BufferedReader rd;
    File file = new File(seed);
    int i = 1;

    try{
      rd = new BufferedReader(new FileReader(file));
      String line;
      while ((line = rd.readLine()) != null  && i < 1000) {


        var[i] = new OctetString(line);
        newOID = new OID("" + "." + i);

        UnpredictableEntryRow row = ((MOMutableTableModel<UnpredictableEntryRow>) unpredictableEntryModel).
                createRow(newOID, new Variable[]{new Integer32(i), new OctetString(line)});
        if(row == null)
          System.out.println("foodz");

        System.out.println(row);
        ((MOMutableTableModel<UnpredictableEntryRow>) unpredictableEntryModel).addRow(row);
        i++;
      }
    }
    catch(Exception e){
      e.printStackTrace();
    }
  }



  public void loadSeed(String seed, Variable[] var) throws IOException{
    File file = new File(seed);
    int i = 0;
    BufferedReader rd = new BufferedReader(new FileReader(file));
    String line = rd.readLine();
    while (line != null && i < 1000){
      var[i] = new OctetString(line);
      i++;
      line = rd.readLine();
    }

  }



  public void registerMOs(MOServer server, OctetString context) 
    throws DuplicateRegistrationException 
  {
    // Scalar Objects
    server.register(this.frequencia, context);
    server.register(this.numEntradas, context);
    server.register(this.numDigitosH, context);
    server.register(this.reset, context);
    server.register(this.unpredictableEntry, context);
//--AgentGen BEGIN=_registerMOs
//--AgentGen END
  }

  public void unregisterMOs(MOServer server, OctetString context) {
    // Scalar Objects
    server.unregister(this.frequencia, context);
    server.unregister(this.numEntradas, context);
    server.unregister(this.numDigitosH, context);
    server.unregister(this.reset, context);
    server.unregister(this.unpredictableEntry, context);
//--AgentGen BEGIN=_unregisterMOs
//--AgentGen END
  }

  // Notifications

  // Scalars
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


  // Value Validators
  /**
   * The <code>ResetValidator</code> implements the value
   * validation for <code>Reset</code>.
   */
  static class ResetValidator implements MOValueValidationListener {
    
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


  // Rows and Factories

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
  
  class UnpredictableEntryRowFactory 
        implements MOTableRowFactory<UnpredictableEntryRow>
  {

    /*public UnpredictableEntryRowFactory(){
      OctetString value = new OctetString("123");
      Variable[] variavel = new Variable[20];
      variavel[0] = value;
      createRow(oidUnpredictableEntry, variavel);
    }
*/
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

  public void loadConfig() throws IOException {

    File file = new File("path/to/config.txt");
    BufferedReader br = new BufferedReader(new FileReader(file));
    String[] parametros;

    try {
      String line = br.readLine();

      while (line != null) {
        parametros = line.split(" ");
        switch (parametros[0]) {
          case "UDP-PORT":
            port = Integer.valueOf(parametros[1]);
            break;

          case "COMMUNITY-STRING":
            community = parametros[1];
            break;

          case "REFRESH-RATE":
            valoresEscalares[0] = Integer.valueOf(parametros[1]);
            break;

          case "TABLE-SIZE":
            valoresEscalares[1] = Integer.valueOf(parametros[1]);
            break;

          case "NUMBER-SIZE":
            valoresEscalares[2] = Integer.valueOf(parametros[1]);

          case "FIRST-SEED":
            seed = parametros[1];
            break;
        }
        line = br.readLine();

      }
    } catch (IOException e) {
    }
  }

}


