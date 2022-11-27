#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int alarmflag = 0;
void alarmhandler(int signo);

int main(void) {
    signal(SIGALRM, alarmhandler);
    alarm(5);
    printf("Looping ...\n");

    while(!alarmflag)
        pause();

    printf("Ending ...\n");
}

void alarmhandler(int signo) {
    printf("Alarm received ...\n");
    alarmflag = 1;
}
