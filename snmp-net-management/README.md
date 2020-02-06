# Net Management

Academic projects to introduction of a great but boring protocol that is SNMP and management of its information base - MIB.


## PACKET COUNTER

This is a simple project where we are monotoring the octects/info passing through the interfaces (in and out) relative to localhost
Agent SNMP, by giving an IP(that will be the localhost) and a port that we define on snmp configuration of our machine.

More info: [SNMP](https://kb.op5.com/display/HOWTOs/Configure+a+Linux+server+for+SNMP+monitoring#sthash.Loo8pPh7.dpbs)


----------------------------------


## MIBS-SNMP

After the brief intro to what is SNMP and how it works, we were proposed to create our own SNMP agent, that is a generator of 
random numbers, storing the information of those in an organized MIB. This was possible using the [MIBDesigner](http://agentpp.com/tools/mibdesigner.html)
and [AgenPro](http://agentpp.com/tools/agenpro.html) tools.

The config file defines the configuration of our SNMP agent (community string, port, path to seed,...); the seed contains the
values to be stored on the Agent's MIB.



