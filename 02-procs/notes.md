## PROCS ##

### FAMILY ###
#### Parent process does not wait ####
The children go to "State:  Z (zombie)" as the manual states: "A child that terminates, but has not been waited for becomes a "zombie"".
The kernel keeps minimal information about the zombie, however it also consumes one a slot in the kernel table, as a result, if many zombies are created, the kernel will not be able to create more processes.
If the parent finished, the zombie will be adopted by Init or by the nearest subreaper.

#### Adopting children processes ####

In this process prctl is involved, all the details about this process are overwhelming, but the most important to know now is: PR_SET_CHILD_SUBREAPER.
prctl(PR_SET_CHILD_SUBREAPER, set);
If set >= 0 this process is set to be a subreaper, this means that any zombie will be his child.
As a result of that if a getppid is run after being adopted by the subreaper it will get the pid of the subreaper.

The subreaper atribute won't be inheritated by fork children but it will be by execve.

#### Printf buffer ####
When calling a children with fork, if printf had something in the buffer, it will be printed by the parent and the first children called.
This is because all the data is copied and both will have the same in the buffer.
This can be fixed adding a "\n" to printf, or using fflush().

## Others ##

I am taking a long time to do this part of the roadmap, this is because the large amount of information and details needed to understand it, I wanted to delve into every part of it.
Things like cat returning 0 on success, but when input is not correct it returns 1. However, if 2 files or directions are used and none exit it will return 2, and successively.
What is an RTOS (partly related and learnt a lot about them: https://ubuntu.com/blog/real-time-linux-vs-rtos is really usefull).
And i'm new to fork and execve topics, so understanding processes, childrens and also pipes is something that takes time.
For some parts Libft is really useful as you can modify or reuse parts of it.
