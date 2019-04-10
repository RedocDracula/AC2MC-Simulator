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
		cout << "====== Registry File ======"  <<endl;
		for (int i = 0;i<8;i++) {
			cout <<"Reg "<<i << " - " << registers[i].to_ulong() << "\t";
			cout <<"Reg "<<i+8 << " - " << registers[i+8].to_ulong() << "\t";
			cout <<"Reg "<<i+16 << " - " << registers[i+16].to_ulong() << "\t";
			cout <<"Reg "<<i+24 << " - " << registers[i+24].to_ulong() << endl; 
		}
		cout<< "============================"<<endl;
	}

};


