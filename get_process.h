#ifndef GET_PROCESS_H

#define GET_PROCESS_H
typedef struct proc
{
    int id;
    int ppid;
    char *name;
    char *state;
    double virtualSize;
    int threads;
} proces; 

proces get_process(int pid);
double get_cpu_usage();

#endif
