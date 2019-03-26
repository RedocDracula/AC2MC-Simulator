#include<bits/stdc++.h>
#include"../Decode.h"

using namespace std;

int main(){
    InterStateBuffers buf;
    Registry_File regFile;
    Decode dec;
    dec.initialise();
    string instStr = "00000000001100010000001101100011";

    bitset<32> inst(instStr);

    buf.IR.writeBitset(inst);
    buf.insType = 3;

    dec.decoder(buf, regFile);

    return 0;
}