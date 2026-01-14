Network Planning

Network topology: 
- Master slave, 
- One master, all the others are backup
- Master disconnected: one of the slaves become the master

Is a slave becoming  a master a part of the network module?:
- Maybe, but we dont think so.
- Maybe a controller module also?

TCP or UDP? 
- TCP is good for master slave

Who connects to who in TCP?:
- Check for master flag? 
- Backup needs to listen to master
- Master needs to listen to everyone

n = recv(...)
if (n == 0 || n < 0) 
then 
//primary is dead








