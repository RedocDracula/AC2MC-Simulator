#pragma once
#include <iostream>
#include <bitset>
#include <string>
#include <deque> 
#define registerWidth 32
using namespace std;

class Register{
	private:
		int value;
	public:
		Register(){
			value = 0;
		}
		
		void reset(){
			value = 0;
		}
		
		void writeInt(int x){
			value = x;
		}

		void writeBitset(bitset <registerWidth> x){
			value = x.to_ulong();
		}
		
		int readInt(){
			return value;
		}
		
		bitset<registerWidth> readBitset(){
			bitset <registerWidth> x(value);	
			return x;
		}
};

class InterStateBuffers{
	public:
		Register RA, RB, RX, RY, RM, RZ, RMD;
		int PC;
		int mem_register, return_address;
		Register IR;
		int pc_offset;
		int insType;
		string ALU_OP;
		bool isjalr, isMem;
		// For stalling
		bool stall;

		int hazard_type; /* 0 No Branch , 1 Jal ,  2 Jalr ,3 branch */
		int branch_address_def;
		int branch_address;

		int insTypeD,insTypeE,insTypeM,insTypeW;
		int isjalrD,isjalrE,isjalrM,isjalrW;
		int wblocD,wblocE,wblocM,wblocW;
		int isMemD,isMemE,isMemM,isMemW;
		int returnAddD,returnAddE,returnAddM,returnAddW;

		bool taken;
		int mispredNumber;
		bool isMispred;
		int nextPC;

		int pWrite;     // holds the write register value for the previous instruction
    	int ppWrite;    // the instruction before that
    	string pInst;      // instruction
    	string ppInst;     //





		//Write back location:- stores register number for writeback, 
		//-1 for SB type where no write back occurs.
		int write_back_location;


		//inserting knobs as bool types, specification given with each knob
		//take in the value at runtime or hardcode it for development purposes

		bool enablePipe ;	// E/D pipelining
					// This would be used by the control unit
		bool enableDF ;	// E/D data forwarding
					// Used by decode, execute, memory units
		bool printRegFile ;	// E/D printing register file values after each cycle
					// Used by control
		bool printISB;	// E/D printing pipleline registers after each cycle
					// Control
		bool printISBspecific;	// E/D printing for a specific instruction, handle later
					// Control, decode(maybe)

		InterStateBuffers(){
			PC = 1;
			return_address = 1;
			mem_register = 0;
			pc_offset = 0;
			isjalr = false;
			isMem = false;
			write_back_location = -1;

			enablePipe = true;
			enableDF = true; 
			printRegFile = true;
			printISB = true;
			printISBspecific = false;
			stall  = false;
			hazard_type = 0;

			wblocW = -1;
			wblocM = -1;
			wblocE = -1;
			wblocD = -1;
	
			returnAddW = -1;
			returnAddM = -1;
			returnAddE = -1;
			returnAddD = -1;	

			insTypeW = -1;
			insTypeM = -1;
			insTypeE = -1;
			insTypeD = -1;

			isjalrW = 0;
			isjalrM = 0;
			isjalrE = 0;
			isjalrD = 0;

			isMemW = 0;
			isMemM = 0;
			isMemE = 0;
			isMemD = 0;

			taken = true;
			mispredNumber = 0;
			isMispred = false;
			nextPC = 0;

			pWrite = 0;
			ppWrite = 0;
		}

		void resetAll(){
			RA.reset();
			RB.reset();
			RX.reset();
			RY.reset();
			RM.reset();
			RZ.reset();
			mem_register = 0;
			pc_offset = 0;
		}

		void printAll(){
			cout<<"********** Inter State Buffer Values ***********\n";
			cout<<"\tRA\t:\t"<<RA.readInt()<<endl;
			cout<<"\tRB\t:\t"<<RB.readInt()<<endl;
			cout<<"\tRMD\t:\t"<<RMD.readInt()<<endl;
			cout<<"\tRM\t:\t"<<RM.readInt()<<endl;
			cout<<"\tRZ\t:\t"<<RZ.readInt()<<endl;
			cout<<"\tRY\t:\t"<<RY.readInt()<<endl;
			cout<<"\tpc_offset\t:\t"<<pc_offset<<endl;
			cout<<"\tisjalr\t:\t"<<isjalr<<endl;
			cout<<"\tmem_register\t:\t"<<mem_register<<endl;
			cout<<"\treturn_address\t:\t"<<return_address<<endl;
			cout<<"\tbranch_address_def\t:\t"<<branch_address_def<<endl;
			cout<<"\tbranch_address\t:\t"<<branch_address<<endl;
			cout<<"\thazard_type\t:\t"<<hazard_type<<endl;
			cout<<"\twrite_back_location\t:\t"<<write_back_location<<endl;
			cout<<"\tmis prediction\t:\t"<<isMispred<<endl;
			cout<<"*************************************************\n";

		}
};
	

