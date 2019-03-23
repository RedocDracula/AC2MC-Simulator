#include <bits/stdc++.h>

#define registerWidth 64

using namespace std;

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
		Register RA, RB, RY, RM, RZ;
		
		void resetAll(){
			RA.reset();
			RB.reset();
			RY.reset();
			RM.reset();
			RZ.reset();
		}
};


class ALU {

    private:
    vector <string> instructionName, relevantstr;  // here relevant str is  a string concatenated with funct7+funct3+opcode
    
    public:
    bool state;
    int result;

    void initialise() {
        ifstream ifile("instructions_opcodes_ALU.txt");
        string line,temp;
        
        while(getline(ifile,line))
        {
            stringstream ss(line);
            ss >> temp; // temp now has the instruction name ex : add, sub etc,
            instructionName.push_back(temp);
            ss >> temp ; // temp now has the concatenated string. we'll use this to map to name of instruction
            relevantstr.push_back(temp);
        }

        ifile.close();
    }


    void compute(bitset <32> funct7, bitset <32> funct3, bitset <32> opcode, InterStateBuffers &ISobject) {
        
        string relevant = funct7.to_string() + funct3.to_string() + opcode.to_string();
        vector <string> :: iterator it = find(relevantstr.begin(), relevantstr.end(),relevant);
        
        if(it == relevantstr.end())
        {
            cout<<"ALU : Error instruction not found!";
            return;
        }
        
        int index = it - relevantstr.begin();
        string ins = instructionName[index];

        if(ins == "add")
        {
            result =  ISobject.RA.readInt() + ISobject.RB.readInt();
            ISobject.RZ.writeInt(result);
        }
        else if(ins == "sub")
        {
            result =  ISobject.RA.readInt() - ISobject.RB.readInt();
            ISobject.RZ.writeInt(result);
        }
        else if(ins == "sll")
        {
            result =  ISobject.RA.readInt() << ISobject.RB.readInt();
            ISobject.RZ.writeInt(result);
        }
        else if(ins == "slt")
        {
            result =  (ISobject.RA.readInt() < ISobject.RB.readInt()) ? 1 : 0;
            ISobject.RZ.writeInt(result);
        }
        else if(ins == "sltu")
        {
            unsigned Ra = ISobject.RA.readInt();
            unsigned Rb = ISobject.RB.readInt();
            result =  (Ra < Rb) ? 1 : 0;
            ISobject.RZ.writeInt(result);
        }
        else if(ins == "xor")
        {
            result =  (ISobject.RA.readInt() ^ ISobject.RB.readInt());
            ISobject.RZ.writeInt(result);
        }
        else if(ins == "srl")
        {
            result =  (ISobject.RA.readInt() >> ISobject.RB.readInt());
            ISobject.RZ.writeInt(result);
        }
        else if(ins == "sra")
        {
            bitset <32> ra(ISobject.RA.readInt());
            int shift = ISobject.RB.readInt();
            int MSB = ra[ra.size()-1]; // extract MSB
            ra >> shift;

            for(int index = ra.size() - shift ; index < ra.size() ; index++)
                ra[index] = MSB;

            ISobject.RZ.writeInt(ra.to_ulong);
        }




    }

    
};


int main()
{
    ALU obj;
    obj.initialise();
    return 0;
}