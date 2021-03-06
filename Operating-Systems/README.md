# Operating-Systems

Stream processing creating multiple processes linked by pipes.

Abstract
========


This project was divided in 2 phases:
  - In a first aproach, implement some components to be used on processing data;
  - Then, create the controller of the network where each node processes a single task.

The creation of this project came with a pratical exercise proposed in a class subject (more precisely, operating systems).
The intention here was to develop our knowledge on a fragile theme that is the direct interaction with the kernel of our system, by using some system calls, so we can understand how the processes communicate by each other and how the (powerful) things we use everyday when programming. Hence, the using language is our beloved C.
Just like the name of the project is saying, we are dealing with stream processing where there is possible to create a bunch of nodes, to be connected as desired, in which node is a single process running a specified command(by using one of the following component modules). 


 Component modules:
 - [Const](./StreamProcessing/const.c)  
 - [Filter](./StreamProcessing/filter.c)  
 - [Spawn](./StreamProcessing/spawn.c)  


Const
-----

Reproduces every line, adding a new collumn with a constant value at the end.  
**Example**: const 10     
![inout](https://github.com/ReiKratos/Operating-Systems/blob/master/StreamProcessing/imagem.png)

Filter
------

Reprouces every line that satisfies the indicated predicate.  
**Example**: filter 2 < 4  
![inout](https://github.com/ReiKratos/Operating-Systems/blob/master/StreamProcessing/filter.png)  


Spawn
-----

This component reproduces every line, executing the indicated command (one time for each line), adding a new collumn containing correspondent exit status. To specify the collumn(s) as argument of the command in use, the symbol '$' must appear before the number of the collumn(s) desired.  
**Example**: spawn ls -a $1 (command: ls, where arguments are an option and an other option or directory, depending what is on the collumn 1)  
![inout](https://github.com/ReiKratos/Operating-Systems/blob/master/StreamProcessing/spawn.png)  


[Controller](https://github.com/ReiKratos/Operating-Systems/blob/master/StreamProcessing/controlador.c)
==========

### Possible Commands  
#### node <id\> <cmd\> <args...\>  




#### connect <id\> <ids\>  





#### inject <id\> <cmd\> <args...\>  


### Example

To better explain how this net of processes is working let's take a look on the following example:

![inout](https://user-images.githubusercontent.com/12373116/31716940-ec7d95ca-b401-11e7-9c5c-35dbcd8a74cc.png)

####Controller
>node 1 const 10
>node 2 <cmd\> <args\>
>connect 1 2
>inject 1 echo msg

So, for each node we got 2 namedpipes (FIFOinID and FIFOoutID) to receive and to send, respectively. Hence, it's also created a process to read from FIFO and send the stream to the main process (the node) using an unnamed pipe; and a process just to read from the FIFOout and deliver that stream to all ohters connected nodes' FIFOin.
