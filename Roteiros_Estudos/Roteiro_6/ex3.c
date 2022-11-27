#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    void (*oldhandler)(int);

    printf("I can be Crtl-C'ed\n");
    sleep(3);
    oldhandler = signal(SIGINT, SIG_IGN);
    printf("I'm protected from Crtl-C now\n");
    sleep(3);
    signal(SIGINT, oldhandler);
    printf("I'm vulnerable again!\n");
    sleep(3);
    printf("Bye.\n");
}
