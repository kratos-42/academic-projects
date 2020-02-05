# UDP-Management

## REVERSE PROXY

Abstract
--------

Just as the name suggests, the purpose of this project is to create a Reverse Proxy to handle TCP connections (between a Web Server
and a remote client), by processing the state of the available servers using an UDP monitor. Let's take a look on a simple schema
describing the use case.  
     
![schema](https://github.com/ReiKratos/UDP-Management/blob/master/ReverseProxy/eqweq.png)

So, we got:  
- a client, trying to connect to a Web Server, via TCP;
- a Proxy, to handle those external connections;
- several Web Servers, which one is being handled by an UDP monitor.  

### Proxy

To get an easiest approach, lets look first to the UDP part of our system. As you can see, all servers are "linked"
to a monitor (UDP monitor) that is connect by UDP socket to a specific port of our Reverse Proxy, port 5555. First of all, 
the UDP monitor sends a message to Proxy (saying "I'm available") so it can register the Web Server linked to the sending monitor (This message will be periodically sent to Proxy) in a table containing information status of those Servers.
So that, the Proxy uses this info table and simple transport protocol (UDP) to request all the monitors, get information about the current state of Web Servers that they are related to, and update the table according to the these periodically polls. This process (regist, request and update) is important so we can further decide which server got the best conditions to connect.
Since a UDP monitor join the poll, it will receive probing messages coming from the Proxy and automatically send a response containing the serial number of that message. With this process, the Proxy can calculate and evaluate the correspondent Server of that monitor. 

With this, we could further add TCP servers to a monitor, and start handling TCP connections coming from clients via Reverse Proxy.

#### Getting Started

Just run the monitor and the Proxy.
