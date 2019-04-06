#pragma once
#include <iostream>
#include <bitset>
#include <string>
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
		Register RA, RB, RX, RY, RM, RZ;
		int PC;
		int mem_register, return_address;
		Register IR;
		int pc_offset;
		int insType;
		string ALU_OP;
		bool isjalr, isMem;

		//Write back location:- stores register number for writeback, 
		//-1 for SB type where no write back occurs.
		int write_back_location;

		//inserting knobs as bool types, specification given with each knob
		//take in the value at runtime or hardcode it for development purposes

		bool k1;	// E/D pipelining
					// This would be used by the control unit
		bool k2;	// E/D data forwarding
					// Used by decode, execute, memory units
		bool k3;	// E/D printing register file values after each cycle
					// Used by control
		bool k4;	// E/D printing pipleline registers after each cycle
					// Control
		bool k5;	// E/D printing for a specific instruction, handle later
					// Control, decode(maybe)

		InterStateBuffers(){
			PC = 1;
			return_address = 1;
			mem_register = 0;
			pc_offset = 0;
			isjalr = false;
			isMem = false;
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
			cout<<"\tRY\t:\t"<<RY.readInt()<<endl;
			cout<<"\tRM\t:\t"<<RM.readInt()<<endl;
			cout<<"\tRZ\t:\t"<<RZ.readInt()<<endl;
			cout<<"\tpc_offset\t:\t"<<pc_offset<<endl;
			cout<<"\tisjalr\t:\t"<<isjalr<<endl;
			cout<<"\tmem_register\t:\t"<<mem_register<<endl;
			cout<<"\treturn_address\t:\t"<<mem_register<<endl;
			cout<<"\twrite_back_location\t:\t"<<mem_register<<endl;
			cout<<"*************************************************\n";

		}
};
	

