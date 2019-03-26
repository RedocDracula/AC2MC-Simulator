#include <bitset>
#include <vector>

using namespace std;

class Registry_File {
private:
		vector < bitset <32> > registers;

public:
	Registry_File() {
		for (int i = 0;i<32;i++) {
			registers.push_back(0);
		}
	}

	void writeInt(int index, int value) {
		registers[index] = value;
	}

	int readInt( int index ) {
		return registers[index].to_ulong();
	}

	void writeBits (int index , int value) {
		registers[index] = value;		
	}

	bitset <32> readBits ( int index) {
		return registers[index];
	}

};


