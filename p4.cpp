#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]){

    if (argc <= 1){
        cout << "Not enough arguments" << endl;
        return 0;
    }
    else if(argc == 2){
        const char *progname = argv[1];
        char *args[] = {"", nullptr};
        execv(progname, args);

    }
    else if(argc == 3){
        const char *progname = argv[1];
        char *args[] = {argv[1],argv[2], nullptr};
        execvp(progname, args);
    }
    else if(argc == 4){
        const char *progname = argv[1];
        char *args[] = {argv[1],argv[2],argv[3], nullptr};
        execv(progname, args);
    }
    
    else{
        cout << "Too many arguments!" << endl;
        return 0;
    }

    return 0;
}