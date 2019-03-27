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
		bool isjalr;	
		void initialise(){
			PC = 0;
			return_address = 0;
		}
		void resetAll(){
			RA.reset();
			RB.reset();
			RX.reset();
			RY.reset();
			RM.reset();
			RZ.reset();
		}
};
	

