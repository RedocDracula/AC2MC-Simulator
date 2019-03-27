#pragma once 

#include <bitset>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;
#define MEM_SRC "a"
#define MAX_MEM int(1e6)
class  MemoryAccess {
private:
	fstream file;
	
public:
	MemoryAccess() {
		file.open(MEM_SRC,ios::out);
		for (int i =0;i<MAX_MEM ; i++) {
			file << i*4 << "0 \n";	
		}
		file.close();
	}
	
	void writeMem( int value , int address) {
		file.open(MEM_SRC, ios::);
		// while(getline() ){
		// 	//

		// }
		file.close();
	}

	int readMem (int address ) {
		// while(getline()){
			
		// }
		return 0;
	}
}; 

