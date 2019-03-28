#pragma once 
#include <bitset>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;
class  MemoryAccess {
private:
	
	map <int , int > MEM;
	
public:
	
	void writeMem(InterStateBuffers &isb) {
		MEM[isb.RZ.readInt()] = isb.RM.readInt();
	}

	void readMem (InterStateBuffers &ibf) {
		ibf.mem_register = MEM[ibf.RZ.readInt()];
	}

	void Test () {
		cout << "Printing Mem" <<endl;
		for (auto elem : MEM) {
			cout << elem.first << " " <<elem.second<< endl;
		}
	}
}; 

