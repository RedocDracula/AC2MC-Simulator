#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <algorithm>

using namespace std;

class Stype {
    private:
    vector <string> instructions;    // instruction : | immediate (7) | rs2 (5) | rs1 (5) | func3 | immediate (5) | opcode (7) |
    vector <string> opcode;
    vector <string> funct3;

    vector <int> extractint(string str) { // recieves a string and extracts all the integers and returns them in a list (vector)
        vector <int> result;
        int sum,currentint;
        for(int strIndex = 0 ; strIndex < str.size() ; strIndex++) {
            
            sum = 0;
            bool intfound = 0;

            while(strIndex < str.size() && isdigit(str[strIndex])) {
                currentint = str[strIndex] - '0';
                sum = sum*10 + currentint;
                strIndex++;
                intfound = 1;
            }
            
            if(intfound)
            result.push_back(sum);
        }

        return result;
    }
    
    public:

    void initialise (string filename) {
        ifstream ifile(filename.c_str());
        string line;
        while(getline(ifile,line)) {
            stringstream ss(line);
            string token;
            ss >> token;
            instructions.push_back(token);
            ss >> token;
            opcode.push_back(token);
            ss >> token;
            funct3.push_back(token);
        }
    }

    bool check(string command)
    {
        stringstream ss(command);
        string ins;
        ss >> ins;
        vector <string> :: iterator it = find(instructions.begin(),instructions.end(),ins);
        if(it == instructions.end())
        return false;
        else
        return true;
    }

    bitset <32> decode (string instruction) {
        bitset <32> MachineCode;
        stringstream ss(instruction);
        vector <int> parameters = extractint(instruction); // extracted all register names, offsets etc.
        string action;
        ss >> action;
        int index = find(instructions.begin(),instructions.end(),action) - instructions.begin();
        string opcodestr,funct3str,rs1str,rs2str;
        
        opcodestr = opcode[index];
        funct3str = funct3[index];
        bitset <12> immediate(parameters[1]); // loading offset
        bitset <5> rs2(parameters[0]),rs1(parameters[2]);

        for(int i=0;i<7;i++)
            MachineCode[i] = (opcodestr[opcodestr.size()-1-i] == '0') ? 0 : 1;
        
        for(int i=0;i<5;i++)
            MachineCode[i+7] = immediate[i];

        cout<<"funct3 : "<<funct3str<<endl;
        
        for(int i = 0; i<3; i++)
            MachineCode[i+12] = (funct3str[i] == '0') ? 0 : 1;

        for(int i=0;i<5;i++)
            MachineCode[i+15] = rs1[i];
        
        for(int i=0; i<5 ; i++)
            MachineCode[i+20] = rs2[i];
        
        for(int i=0;i<7;i++)
            MachineCode[i+25] = immediate[i+5];

        return MachineCode;

    }


    
};

