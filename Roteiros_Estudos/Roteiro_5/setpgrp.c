#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>

int main(int argc, char** argv) {
    pid_t cpid, pid, pgid, cpgid; //process id's and process groups

    cpid = fork();

    if(cpid == 0) {
        //child
        
        //set process group to itself
        setpgrp();

        //print the pid, and pgid of child from child
        pid = getpid();
        pgid = getpgrp();
        printf("[child] pid: %d, pgid: %d\n", pid, pgid);
    }
    else if(cpid > 0) {
        //parent
        
        setpgid(cpid, cpid);

        pid = getpid();
        pgid = getpgrp();
    
        cpgid = getpgid(cpid);

        printf("[parent] pid: %d, pgid: %d\n", pid, pgid);
        printf("[parent] child's pid: %d, child's pgid: %d\n", cpid, cpgid);
    }
    else {
        perror("fork");
        _exit(1);
    }

	return 0;
}
