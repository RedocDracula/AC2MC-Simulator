#pragma once
#include "InterStateBuffers.h"

#include "Functions.h"
#include <bitset>
#include <map>
#include <fstream>
#include <sstream>

// TODO 
#define MEM_SRC "machineCode.txt"
#define REG_WIDTH 32

using namespace std;

/*
	Variable hazardType 
	0 -> OK
	1 -> jal
	2 -> jalr
	3 -> brach 
*/

class Fetch {
	
	private:
		map <int , bitset <REG_WIDTH> > mem_map;
		InterStateBuffers * buf;
		map <int , int> itype_map;
		
		int hazardType;
		bitset <REG_WIDTH > branch_address;
		bitset <REG_WIDTH > branch_address_def;
		
	

	int detectControlHazards(InterStateBuffers & buf) { //Return 0 for Ok, 1 jal , jalr 2  , 3 for branch
		bitset <REG_WIDTH > temp;
		bitset <7> opcode;
		temp = mem_map[buf.PC];
		
		for(int i=0;i<7;i++){
            opcode[i] = temp[i];
        }

		if (buf.insType == 3 ) {
			return 3;
		} else if (buf.insType == 5 ) {
			return  1;
		} else if (opcode.to_ulong() == 103 ) {
			return 2;
		} else {
			return 0;
		}	
	}

	void setBrachAddress (InterStateBuffers & buf , Registry_File reg) {
		bitset <20> imm2;
		bitset <12> imm;
		bitset <12> imm1;
		bitset <REG_WIDTH> IR;
		bitset <5> rs1;
		IR = buf.IR.readInt();
		if (hazardType == 1 ) {
			// jal instruction
            for(int i=0; i<8; i++){
                imm2[11+i] = IR[12+i];
            }
            imm2[10] = IR[20];
            for(int i=0; i<10; i++){
                imm2[i] = IR[21+i];
            }
            imm2[19] = IR[31];
			branch_address = bitsetRead(imm2) + buf.PC;  
			branch_address_def = buf.PC + 1;
			cout<<" $$$$$$$$$$$$ branchADDRESS"<<bitsetRead(branch_address)<<endl;
			cout<<" $$$$$$$$$$$$ offset : "<<bitsetRead(imm2)<<endl;
			
		} else if (hazardType == 2) {
			// jalr Instruction
			for(int i=0; i<12; i++){
                imm[i] = IR[20+i];
            }
            for(int i=0; i<5; i++){
                rs1[i] = IR[15+i];
            }
						cout<<"$$$$$$$$$$$$$ rs1 : "<<rs1<<"   value : "<<reg.readInt(bitsetRead(rs1))<<endl;
						branch_address = bitsetRead(imm) + reg.readInt(bitsetRead(rs1));    
						branch_address_def = buf.PC + 1;   
						cout<<" $$$$$$$$$$$$ branchADDRESS"<<branch_address<<endl;  
		} else { 
			// Branch Instructions
            imm1[10] = IR[7];

            for(int i=0;i<4;i++){
                imm1[i] = IR[8+i];
            }
            for(int i=0;i<6;i++){
                imm1[i+4] = IR[25+i];
            }
            imm1[11] = IR[31]; //imm1 contains offset
			branch_address = bitsetRead(imm1) + buf.PC;
			branch_address_def = buf.PC + 1; //  
		}
	
	}

	public:
	int getHazardType () {
		return hazardType; 
	}

	int getBrachAddress () {
		return bitsetRead(branch_address);
	}
	int getDefBrachAddress () {
		return bitsetRead(branch_address_def);
	}


	Fetch() {
		ifstream inpFile (MEM_SRC);
		string line;
		while(getline (inpFile , line ) ){
			string lineNo, command , type;
			stringstream ss (line);
			ss >> lineNo >> command >> type;
			bitset<REG_WIDTH> bitset(command.c_str());
			mem_map[atoi(lineNo.c_str())] = bitset;
			itype_map[atoi(lineNo.c_str())] = atoi (type.c_str());
		}
		
	}
	
	void updateBuffer(InterStateBuffers & buf) {
		buf.hazard_type = hazardType;
		buf.branch_address = getBrachAddress();
		buf.branch_address_def = getDefBrachAddress(); 
	}
	
	void get(InterStateBuffers & buf, Registry_File regs) {
		buf.IR.writeBitset ( mem_map[buf.PC]);
		buf.insType = itype_map[ buf.PC ]; // Instype and new intructions fetch completed
		 
		if (buf.enablePipe) {
			hazardType = detectControlHazards(buf);
			setBrachAddress(buf, regs);
			updateBuffer(buf);
			
		}
	}

};
