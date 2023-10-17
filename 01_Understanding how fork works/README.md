# Understanding how fork works 

```bash
pid1=fork();
if (pid1!=0)
{
    pid2=fork();
    pid3=fork();
}
else
{
    pid4=fork();
    if (pid4==0)
    {
        pid5=fork();
    }
}
```

The hierarchy between processes

![image](https://github.com/PaolaVlsc/OperatingSystem_ForkThreadsProjects_LINUX/assets/87998374/5ba6a601-91c9-47c8-98b1-a12bf40cad88)






• The initial process is P0.
• On line 1, P0 calls fork(), creating a child process, P1.
• The code for process P0 continues on lines 3-6.
• On line 4, P0 makes a second fork() call, creating another child process, P2. The code for P0 continues on line 5, where another child process, P3, is created.
• The code executed by process P2 will be the same as on line 5, so process P2 creates its child process, P6.
• The code executed by process P1 is on lines 7-14.
• On line 9, P1 calls fork(), creating a child process, P4.
• The code for P1 continues on lines 10-13, but due to a condition that determines which one executes it, these lines will not be executed by P1.
• As a result, lines 10-13 will be executed by process P4. On line 12, P4 calls fork(), creating another child process, P5.
