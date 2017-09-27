# Operating-Systems

Stream processing creating multiple processes linked by pipes.

Abstract
========


This project was divided in 2 phases:
  - In a first aproach, implement some components to be used on processing data;
  - Then create the network where each node processes a single task.

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
![inout]()
