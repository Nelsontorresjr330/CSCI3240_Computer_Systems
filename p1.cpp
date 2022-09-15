#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv){

    ifstream FirstFile;
    ifstream SecondFile;

    int temp;
    int length;
    int longer;
    
    vector<char> FirstBytes;
    vector<char> SecondBytes;
    char Byte;

    FirstFile.open(argv[1]);
    SecondFile.open(argv[2]);

    temp = 0;

    while(FirstFile.get(Byte)){
        FirstBytes.push_back(Byte);
    }
    while(SecondFile.get(Byte)){
        SecondBytes.push_back(Byte);
    }

    length = FirstBytes.size();
    longer = 1;

    if (SecondBytes.size() > length){
        length = SecondBytes.size();
        longer = 2;
    }

    for(int i = 0; i < length; ++i){
        if(FirstBytes[i]!=SecondBytes[i]){
            cout << i;
            if(longer == 1 && i == SecondBytes.size()){
                cout << ": 0x" << hex << (int) FirstBytes[i] 
                << " EOF" << endl;
            }
            else if(longer == 2 && i == FirstBytes.size()) {
                cout << ": EOF" << hex  
                << " 0x" << (int) SecondBytes[i] << endl;
            }
            else { 
                cout << ": 0x" << hex << (int) FirstBytes[i] 
                << " 0x" << (int) SecondBytes[i] << endl;
            }
            temp = 1;
            break;
        }
    }
    
    if(temp == 0){
        cout << "IDENTICAL" << endl;
    }
  
    return 0;
}
