#include<iostream>
#include"SBType.h"
#include<string.h>
#include<bitset>

using namespace std;

int main(){
    // Change path to your text file
    string path = "./instructions/SBType.txt";

    SBType obj;
    obj.initialise(path);

    string command;
    //Give in your instruction here
    getline(cin, command);
    cout<<command<<endl;
    bool isInst = obj.check(command);

    if(isInst){
        cout<<"Instruction present"<<endl;
        bitset<32> mc = obj.decode(command);
        cout<<mc<<endl;
    }
    else{
        cout<<"Instruction not there"<<endl;
    }

    return 0;
}