#pragma once

#include <bitset>
#include <vector>
#define REG_WIDTH 32
using namespace std;

class Registry_File {
private:
		vector < bitset <REG_WIDTH> > registers;

public:
	Registry_File() {
		for (int i = 0;i<REG_WIDTH;i++) {
			registers.push_back(0);
		}

		registers[2] = 200000; // INTIAL VALUE OF STACK POINTER

	}

	void writeInt(int index, int value) {
		if (index != 0) registers[index] = value;
	}

	int readInt( int index ) {
		return registers[index].to_ulong();		
	}

	void writeBits (int index , bitset <REG_WIDTH> value) {
		if (index != 0) registers[index] = value;		
	}

	bitset <REG_WIDTH> readBits ( int index) {
		return registers[index];
	}

	void print () {
		cout << "###### Registry File ######"  <<endl;
		for (int i = 0;i<32;i+=4) {
			cout <<"Reg "<<i << " - " << registers[i].to_ulong() << "\t";
			cout <<"Reg "<<i+1 << " - " << registers[i+1].to_ulong() << "\t";
			cout <<"Reg "<<i+2 << " - " << registers[i+2].to_ulong() << "\t";
			cout <<"Reg "<<i+3 << " - " << registers[i+3].to_ulong() << endl; 
		}
		cout<< "############################"<<endl;
	}

};


