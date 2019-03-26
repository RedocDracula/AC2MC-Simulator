#include<bits/stdc++.h>
#include"../Decode.h"

using namespace std;

int main(){
    InterStateBuffers buf;
    Registry_File regFile;
    Decode dec;
    dec.initialise();
    string instStr = "00000000010000010000000100010011";

    bitset<32> inst(instStr);

    buf.IR.writeBitset(inst);
    buf.insType = 2;

    dec.decoder(buf, regFile);

    return 0;
}