// Read PC and fill Instruction Registers
 
#include "InterStateBuffers.h"

#include <bitset>
#include <map>
#include <fstream>
#include <sstream>

// TODO 
#define MEM_SRC ""
#define REG_WIDTH 32

using namespace std;

//Change Here, Global Interstate Buffer ka object
extern InterStateBuffers buf;

class Fetch {
	
	private:
		map <int , bitset <REG_WIDTH> > mem_map;
		map <int , int> itype_map;

	public:
	Fetch() {
		ifstream inpFile (MEM_SRC);
		string line;
		while(getline (inpFile , line ) ){
			string lineNo, command , type;
			stringstream ss (line);
			ss >> lineNo >> command >> type;
			mem_map[atoi(lineNo.c_str())] = atoi(command.c_str());
			itype_map[atoi(lineNo.c_str())] = atoi (type.c_str());
		}
		
	}
	
	
	void get() {
		buf.IR.writeBitset ( mem_map[buf.PC]);
		buf.insType = itype_map[ buf.PC ];
	}

};
