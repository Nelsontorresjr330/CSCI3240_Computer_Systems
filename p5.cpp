#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
//#include "/nfshome/rbutler/public/courses/cs/p5siggy.o"



using namespace std;

static int test = 0;

void handler(int signum){
    cout << "handling SIG" << signum << endl;
    test++;
}

int main(){

    alarm(90);
    p5siggy();

    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    while (test < 7){
        sleep(1);
    }

    return 0;
}