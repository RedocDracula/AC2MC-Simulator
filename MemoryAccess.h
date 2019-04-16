#pragma once 
#include <bitset>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

/* NOTE : LSB occupies lower address */
#define BYTE 8
#define WORD 32

class  MemoryAccess {
private:
	
	map <int , bitset <BYTE> > MEM; 
	
	void divide (bitset <32> source , bitset <8> & byte1 , bitset<8> & byte2 , bitset <8> & byte3 , bitset <8> & byte4) {
		int k,l,m,n=0;
		for (int i = 0;i<32;i++) {
			if (i<8) {
				byte1[k] = source[i];k++;
			} else if (i<16) {
				byte2[l] = source[i];l++;
			} else if (i<24) {
				byte3[m] = source[i];m++;
			} else {
				byte4[n] = source[i];n++;
			}
		}
	
	}

	void unite (bitset <32> & output , bitset <8> byte1 , bitset<8>  byte2 , bitset <8>  byte3 , bitset <8> byte4) {
		int k,l,m,n;
		for (int i =0;i< 32 ; i++) {
			if (i<8) {
				output[i] = byte1[k];k++;
			} else if (i<16) {
				output[i] = byte2[l];l++;
			} else if (i<24) {
				output[i] = byte3[m];m++;
			} else {
				output[i] = byte4[n];n++;
			}
		}
	}

	
public:

	void writeWord(InterStateBuffers &isb) { // WRITES RM value to RZ index

		bitset <8> byte1,byte2,byte3,byte4;
		bitset <32> source = isb.RM.readBitset();
		int index = isb.RZ.readInt();  
		divide(source,byte1, byte2, byte3 , byte4); // byte1 lsb
		
		// Write to its position
		MEM [index + 0] = byte1;
		MEM [index + 1] = byte2;
		MEM [index + 2] = byte3;
		MEM [index + 3] = byte4;
		
	}

		void writeWord(int address, int data ) { // Writes Data at Index, Basically Memory[index] = data( in bytes)
		
		bitset <8> byte1,byte2,byte3,byte4;
		bitset <32> source = data;
		int index = address;  
		divide(source,byte1, byte2, byte3 , byte4); // byte1 lsb
		
		// Write to its position
		MEM [index + 0] = byte1;
		MEM [index + 1] = byte2;
		MEM [index + 2] = byte3;
		MEM [index + 3] = byte4;
		
	}


	void readWord (InterStateBuffers & isb ) {  //INDEX at RZ , WRITE to isb.mem_register
		bitset <BYTE> byte1, byte2, byte3, byte4; 	
		bitset <WORD> output;
		int index = isb.RZ.readInt();

		byte1 = MEM [index + 0];
		byte2 = MEM [index + 1];
		byte3 = MEM [index + 2];
		byte4 = MEM [index + 3];

		unite (output, byte1, byte2, byte3, byte4);

		isb.mem_register = bitsetRead(output);
	}

	int readWord(int address){
		bitset <BYTE> byte1, byte2, byte3, byte4; 	
		bitset <WORD> output;
		int index = address;

		byte1 = MEM [index + 0];
		byte2 = MEM [index + 1];
		byte3 = MEM [index + 2];
		byte4 = MEM [index + 3];

		unite (output, byte1, byte2, byte3, byte4);

		return output.to_ulong();

	}

	int readByte(int address){
		bitset <WORD> output;
		bitset <BYTE> byte; 
		
		int index = address;
		byte = MEM[index];

		for (int i = 0;i<8;i++) {
			output[i] = byte[i];
		}

		return output.to_ulong();
	}

	void writeByte ( InterStateBuffers & isb ) { // WRITES RM value to RZ index
		bitset <BYTE> byte;
		bitset <WORD> source;
		
		source = isb.RZ.readBitset();
		int index = isb.RZ.readInt();

		for (int i = 0; i<8; i++) {
			byte[i] = source[i];
		}

		MEM[index] = byte;
	}

	void readByte (InterStateBuffers & isb ) {
		bitset <WORD> output;
		bitset <BYTE> byte; 
		
		int index = isb.RZ.readInt();
		byte = MEM[index];

		for (int i = 0;i<8;i++) {
			output[i] = byte[i];
		}
		isb.mem_register = bitsetRead(output);
	}


	void Test () {
		cout << "Printing Mem" <<endl;
		for (auto elem : MEM) {
			cout << elem.first << " " <<elem.second<< endl;
		}
	}
}; 

