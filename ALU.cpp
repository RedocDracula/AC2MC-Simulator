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

    public:
    bool state;
    int result;



    void compute(InterStateBuffers &object) {
        
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
