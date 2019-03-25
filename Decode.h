#include "InterStateBuffers.h"
#include <bits/stdc++.h>

using namespace std;

class Decode{
    private:
    vector <string> instructionName, aluString, relevantstr;

    public:
    void initialise() {
        ifstream ifile("ALU.txt");
        string line,temp;
        
        while(getline(ifile,line))
        {
            stringstream ss(line);
            ss >> temp; // temp now has the instruction name ex : add, sub etc,
            instructionName.push_back(temp);
            ss >> temp;
            aluString.push_back(temp); // ALU INSTRUCTION given to the ALU guy
            ss >> temp ; // temp now has the concatenated string. we'll use this to map to name of instruction
            relevantstr.push_back(temp);
        }

        ifile.close();
    }

    bitset<7> opcode;
    bitset<3> func3;
    bitset<7> func7;
    bitset<12> imm1;
    bitset<20> imm2;
    bitset<5> rs1;
    bitset<5> rs2;
    bitset<5> rd;
    int locA, locB, locC;
    void decoder(InterStateBuffers &ibs){
        func3 = -1;
        func7 = -1;
        imm1 = -1;
        imm2 = -1;
        rs1 = 0;
        rs2 = 0;
        rd = 0;
        int insType = ibs.insType;
        bitset<32> IR(ibs.IR.readInt());

        if(insType == 1){
            // RType | opcode (7) | rd (5) | funct3 | rs1(5) | rs2 (5) | funct7 |
            for(int i=0;i<7;i++){
                opcode[i] = IR[i];
            }
            for(int i=0; i<5; i++){
                rd[i] = IR[7+i];
            }
            for(int i=0; i<3; i++){
                func3[i] = IR[12+i];
            }
            for(int i=0; i<5; i++){
                rs1[i] = IR[15+i];
            }
            for(int i=0; i<5; i++){
                rs2[i] = IR[20+i];
            }
            for(int i=0; i<7; i++){
                func7[i] = IR[25+i];
            }
        } 
        if(insType == 2){
            // IType 0->31 | opcode (7) | rd (5) | funct3 | rs1(5) | immediate(12) |
            for(int i=0;i<7;i++){
                opcode[i] = IR[i];
            }
            for(int i=0; i<5; i++){
                rd[i] = IR[7+i];
            }
            for(int i=0; i<3; i++){
                func3[i] = IR[12+i];
            }
            for(int i=0; i<5; i++){
                rs1[i] = IR[15+i];
            }
            for(int i=0; i<12; i++){
                imm1[i] = IR[20+i];
            }

        }
        if(insType == 3){
            // SBType imm[12] | imm [10:5] | rs2 | rs1 | funct3 | imm[4:1] | imm[11] | opcode
            for(int i=0;i<7;i++){
                opcode[i] = IR[i];
            }
            imm1[10] = IR[7];

            for(int i=0;i<4;i++){
                imm1[i] = IR[8+i];
            }
            for(int i=0;i<3;i++){
                func3[i] = IR[12+i];
            }
            for(int i=0;i<5;i++){
                rs1[i] = IR[15+i];
            }
            for(int i=0;i<5;i++){
                rs2[i] = IR[20+i];
            }
            for(int i=0;i<6;i++){
                imm1[i+4] = IR[25+i];
            }
            imm1[11] = IR[31];
        }
        if(insType == 4){
            // SType immediate (7) | rs2 (5) | rs1 (5) | func3 | immediate (5) | opcode (7) |
            for(int i=0;i<7;i++){
                opcode[i] = IR[i];
            }
            for(int i=0;i<5; i++){
                imm1[i] = IR[7+i];
            }
            for(int i=0; i<3; i++){
                func3[i] = IR[12+i];
            }
            for(int i=0; i<5; i++){
                rs1[i] = IR[15+i];
            }
            for(int i=0; i<5; i++){
                rs2[i] = IR[20+i];
            }
            for(int i=0; i<7; i++){
                imm1[i+5] = IR[25+i];
            }

        }
        if(insType == 5){
            // UJType imm[20][10:1][11][19:12] | rd[11:7] | opcode[6:0]	
            for(int i=0; i<7;i++){
                opcode[i] = IR[i];
            }
            for(int i=0; i<5; i++){
                rd[i] = IR[7+i];
            }
            for(int i=0; i<8; i++){
                imm2[11+i] = IR[12+i];
            }
            imm2[10] = IR[20];
            for(int i=0; i<10; i++){
                imm2[i] = IR[21+i];
            }
            imm2[31] = IR[31];
        }
        if(insType == 6){
            // UType imm[31:12] | rd[11:7] | opcode[6:0]
            for(int i=0;i<7;i++){
                opcode[i] = IR[i];
            }
            for(int i=0;i<5;i++){
                rd[i] = IR[i+7];
            }
            for(int i=0;i<20;i++){
                imm2[i] = IR[12+i];
            }
        }

        // Also add the same to the register files once made
        locA = rs1.to_ulong();
        locB = rs2.to_ulong();
        locC = rd.to_ulong();

        //Register file object will be passed and values will be read
        //Uncomment the following lines once the register file has been created and update the names.
        //ibs.RA.writeBitset(regFile.readValue(locA));
        //ibs.RB.writeBitset(regFile.readValue(locB));

    }

    //Function to concatenate opcode, func3 and func7



};