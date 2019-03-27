#pragma once 

#include "InterStateBuffers.h"
#include "MUX_Y.h"

#include <bitset>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;
#define MEM_SRC "a"
#define MAX_MEM int(1e6)

class  MemoryAccess {
private:
	
	map <int , int > MEM;
	
public:
	MemoryAccess();
	
	void writeMem( int value , int address) {
		MEM[address] = value;
	}

	int readMem (int address ) {
		return MEM[address];
	}
}; 

