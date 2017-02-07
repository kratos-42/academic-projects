 

//--AgentGen BEGIN=_BEGIN
//--AgentGen END

import org.snmp4j.smi.*;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.agent.*;
import org.snmp4j.agent.mo.*;
import org.snmp4j.agent.mo.MOFactory;
import org.snmp4j.agent.mo.snmp.*;
import org.snmp4j.agent.mo.snmp.smi.*;
import org.snmp4j.agent.request.*;
import org.snmp4j.log.LogFactory;
import org.snmp4j.log.LogAdapter;
import org.snmp4j.agent.mo.snmp.tc.*;
import org.snmp4j.agent.mo.snmp.SnmpSshTmMib;


import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.String;

//--AgentGen BEGIN=_IMPORT
//--AgentGen END

public class RANDOM_MIB implements MOGroup{
//--AgentGen BEGIN=_EXTENDS
//--AgentGen END

//--AgentGen BEGIN=_IMPLEMENTS
//--AgentGen END


private static final LogAdapter LOGGER=LogFactory.getLogger(RANDOM_MIB.class);

//--AgentGen BEGIN=_STATIC
//--AgentGen END

// Factory
private MOFactory moFactory=DefaultMOFactory.getInstance();

// Constants

/**
 * OID of this MIB module for usage which can be
 * used for its identification.
 */
public static final OID oidRandomMib=
        new OID(new int[]{1,3,6,1,3,95});

// Identities
// Scalars
public static final OID oidFrequencia=
        new OID(new int[]{1,3,6,1,3,95,4,1,0});
public static final OID oidNumEntradas=
        new OID(new int[]{1,3,6,1,3,95,4,2,0});
public static final OID oidNumDigitosH=
        new OID(new int[]{1,3,6,1,3,95,4,3,0});
public static final OID oidReset=
        new OID(new int[]{1,3,6,1,3,95,4,4,0});
// Tables

// Notifications

// Enumerations


// TextualConventions
private static final String TC_MODULE_SNMPV2_TC="SNMPv2-TC";
private static final String TC_DISPLAYSTRING="DisplayString";

// Scalars
private MOScalar<Integer32> frequencia;
private MOScalar<Integer32> numEntradas;
private MOScalar<Integer32> numDigitosH;
private MOScalar<OctetString> reset;

// Tables
public static final OID oidUnpredictableEntry=
        new OID(new int[]{1,3,6,1,3,95,5,1});

// Index OID definitions
public static final OID oidIndice=
        new OID(new int[]{1,3,6,1,3,95,5,1,1});

// Column TC definitions for unpredictableEntry:
public static final String tcModuleSNMPv2Tc="SNMPv2-TC";
public static final String tcDefDisplayString="DisplayString";

// Column sub-identifier definitions for unpredictableEntry:
public static final int colIndice=1;
public static final int colValueH=2;

// Column index definitions for unpredictableEntry:
public static final int idxIndice=0;
public static final int idxValueH=1;

private MOTableSubIndex[]unpredictableEntryIndexes;
private MOTableIndex unpredictableEntryIndex;

private MOTable<UnpredictableEntryRow,
        MOColumn,
        MOTableModel<UnpredictableEntryRow>>unpredictableEntry;
private MOTableModel<UnpredictableEntryRow> unpredictableEntryModel;


//--AgentGen BEGIN=_MEMBERS
//--AgentGen END

/**
 * Constructs a RANDOM-MIB instance without actually creating its
 * <code>ManagedObject</code> instances. This has to be done in a
 * sub-class constructor or after construction by calling
 * {@link #createMO(MOFactory moFactory)}.
 */
protected RANDOM_MIB(){
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
public RANDOM_MIB(MOFactory moFactory){
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
protected void createMO(MOFactory moFactory){
        addTCsToFactory(moFactory);
        frequencia=
        moFactory.createScalar(oidFrequencia,
        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
        new Integer32());
        numEntradas=
        moFactory.createScalar(oidNumEntradas,
        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
        new Integer32());
        numDigitosH=
        moFactory.createScalar(oidNumDigitosH,
        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
        new Integer32());
        reset=
        new Reset(oidReset,
        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_WRITE));
        reset.addMOValueValidationListener(new ResetValidator());
        createUnpredictableEntry(moFactory);
        }

public MOScalar<Integer32> getFrequencia(){
        return frequencia;
        }
public MOScalar<Integer32> getNumEntradas(){
        return numEntradas;
        }
public MOScalar<Integer32> getNumDigitosH(){
        return numDigitosH;
        }
public MOScalar<OctetString> getReset(){
        return reset;
        }


public MOTable<UnpredictableEntryRow, MOColumn, MOTableModel<UnpredictableEntryRow>>getUnpredictableEntry(){
        return unpredictableEntry;
        }


@SuppressWarnings(value = {"unchecked"})
private void createUnpredictableEntry(MOFactory moFactory){
        // Index definition
        unpredictableEntryIndexes=
        new MOTableSubIndex[]{
        moFactory.createSubIndex(oidIndice,
        SMIConstants.SYNTAX_INTEGER,1,1)};

        unpredictableEntryIndex=
        moFactory.createIndex(unpredictableEntryIndexes,
        false,
        new MOTableIndexValidator(){
public boolean isValidIndex(OID index){
        boolean isValidIndex=true;
        //--AgentGen BEGIN=unpredictableEntry::isValidIndex
        //--AgentGen END
        return isValidIndex;
        }
        });

        // Columns
        MOColumn[]unpredictableEntryColumns=new MOColumn[2];
        unpredictableEntryColumns[idxIndice]=
        moFactory.createColumn(colIndice,
        SMIConstants.SYNTAX_INTEGER32,
        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY));
        unpredictableEntryColumns[idxValueH]=
        moFactory.createColumn(colValueH,
        SMIConstants.SYNTAX_OCTET_STRING,
        moFactory.createAccess(MOAccessImpl.ACCESSIBLE_FOR_READ_ONLY),
        tcModuleSNMPv2Tc,
        tcDefDisplayString);
        // Table model
        unpredictableEntryModel=
        moFactory.createTableModel(oidUnpredictableEntry,
        unpredictableEntryIndex,
        unpredictableEntryColumns);
        ((MOMutableTableModel<UnpredictableEntryRow>)unpredictableEntryModel).setRowFactory(
        new UnpredictableEntryRowFactory());
        unpredictableEntry=
        moFactory.createTable(oidUnpredictableEntry,
        unpredictableEntryIndex,
        unpredictableEntryColumns,
        unpredictableEntryModel);
        }


public void registerMOs(MOServer server,OctetString context)
        throws DuplicateRegistrationException
        {
        // Scalar Objects
        server.register(this.frequencia,context);
        server.register(this.numEntradas,context);
        server.register(this.numDigitosH,context);
        server.register(this.reset,context);
        server.register(this.unpredictableEntry,context);
//--AgentGen BEGIN=_registerMOs
//--AgentGen END
        }

public void unregisterMOs(MOServer server,OctetString context){
        // Scalar Objects
        server.unregister(this.frequencia,context);
        server.unregister(this.numEntradas,context);
        server.unregister(this.numDigitosH,context);
        server.unregister(this.reset,context);
        server.unregister(this.unpredictableEntry,context);
//--AgentGen BEGIN=_unregisterMOs
//--AgentGen END
        }
}
  // Notifications


// Value Validators


// Rows and Factories

public void parser(){
    BufferedReader br = new BufferedReader(new FileReader("config.txt"));
    String[] part;
    try{
        StringBuilder sb = new StringBuilder();
        String line = br.readLine();

        while(line != null){
            part.split(" ");
        }
    }
}
