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
	}

	void writeInt(int index, int value) {
		registers[index] = value;
	}

	int readInt( int index ) {
		return registers[index].to_ulong();
	}

	void writeBits (int index , bitset <REG_WIDTH> value) {
		registers[index] = value;		
	}

	bitset <REG_WIDTH> readBits ( int index) {
		return registers[index];
	}

};


