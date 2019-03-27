#include <iostream>
#include "InterStateBuffers.h"
using namespace std;

class MUX_Y{

    private:
    int RZvalue,mem_register,return_address; //inputs to MUX
    
    public:
    int MUX_Y_SELECT; // select line from control signal. | 1 for RZ | 2 for memory register| 3 for return address |

    void set_mem_register(int val){ // give input Memory register to MUX
        mem_register = val;
    }
    void set_return_address(int val){ // give input return address to MUX
        return_address = val;
    }

    int MUX_Y_output(InterStateBuffers &ibf){
        if(MUX_Y_SELECT == 1){
            RZvalue =  ibf.RZ.readInt();
            return RZvalue;
        }
        else if(MUX_Y_SELECT == 2){
            return mem_register;
        }
        else if(MUX_Y_SELECT == 3){
            return return_address;
        }
        else{
            cout<<" the MUX_Y_SELECT IS SET WRONG!"<<endl;
        }
    }

}