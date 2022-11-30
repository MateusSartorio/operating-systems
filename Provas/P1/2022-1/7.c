#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t cpid, pid, pgid, cpgid;

    cpid = fork();
    if(cpid == 0) {
        setpgrp();
        pid = getpid();
        pgid = getpgrp();
        printf("Child pid: %d pgid: %d\n", pid, pgid);
    }
    else if(cpid > 0) {
        setpgid(cpid, cpid);
        pid = getpid();
        pgid = getpgrp();
        printf("Parent pid: %d pgid: %d\n", pid, pgid);
        cpgid = getpgid(cpid);
        printf("Parent Child's pid: %d pgid: %d\n", cpid, cpgid);
    }
    else {
        perror("fork");
        exit(1);
    }

    return 0;
}