#include <iostream>
#include <bitset>
#define registerWidth 64

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
		
		void resetAll(){
			RA.reset();
			RB.reset();
			RX.reset();
			RY.reset();
			RM.reset();
			RZ.reset();
		}
};
	

