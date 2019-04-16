// Handling assembler directives
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "MemoryAccess.h"

using namespace std;

vector <int> extractint(string str) { // recieves a string and extracts all the integers and returns them in a list (vector)
        vector <int> result;
        int sum,currentint;
        bool valid = 0;
        for(int strIndex = 0 ; strIndex < str.size() ; strIndex++) {
            
            sum = 0;
            bool intfound = 0;
            
            while(strIndex < str.size() && isdigit(str[strIndex]) && valid) {
                    currentint = str[strIndex] - '0';
                    sum = sum*10 + currentint;
                    strIndex++;
                    intfound = 1;
            }
            
            if(intfound)
                result.push_back(sum);

            if(str[strIndex] == ':'){
                valid = 1;
            }
        }

        return result; //returning vector of extracted parameters
    }

void  assembler_initiate(MemoryAccess &memobject)
{
    ifstream ifile("input.txt");
    ofstream ofile("input1.txt",ios::out);
    string current;
     // matches the label to address in the memory or value it is referring to.
    map <string , int > labelLookup;
    bool start = 0;
    bool starttext = 0;
    bool labeldef = 0 ;
    int address =  0;
    

    while(getline(ifile,current))
    {
        
        if(current == ".data"){
            start = 1;
            continue;
        }
        else if(current.size() == 0){
            continue;
        }
        else if(current == ".text"){
            starttext = 1;
            start = 0;
            continue;
        }
        else if(start == 1){ //.data portion has started 
            stringstream ss(current);
            vector <int> data;
            string token;
            ss >> token;

                if(token[token.size()-1] == ':'){
                    labeldef = 1;
                    token.pop_back();
                    data = extractint(current);
                }

            //write the array to memory  (if at all it is an array ). , else write the single value or byte.
            
            if(labeldef){
                
                if(data.size() > 1){
                    labelLookup.insert(make_pair(token,address));
                }
                else{
                    labelLookup.insert(make_pair(token,data[0]));
                }
                
                for(int i=0; i < data.size(); i++){
                    memobject.writeWord(address,data[i]); //Word $$$$$
                    address += 4;
                }
            }
            
            
            labeldef = 0;
        }
        else if(starttext == 1){
            string insname,regname,label;
            int i = 0;
            
            while(!isalnum(current[i])) i++;
            while(isalnum(current[i])){
                insname.push_back(current[i]);
                i++;
            }
            while(!isalnum(current[i])) i++;
            while(isalnum(current[i])){
                regname.push_back(current[i]);
                i++;
            }
            while(!isalnum(current[i])) i++;
            while(isalnum(current[i])){
                label.push_back(current[i]);
                i++;
            }
            

            if( (insname == "la" || insname == "lw" || insname == "lb") && label[1] != '(' ){
                ofile<<"addi "<<regname<<",x0,"<<labelLookup[label]<<endl;
                continue;
            }
           
            else
            {
                bool commline = 0;
                for(int i = 0; i < current.size()  ; i++)
                {
                    if(current[i] == '#'){
                        if(i == 0 )
                            commline = 1;
                        break;
                    }
                    ofile<<current[i];
                    
                }
                if(!commline)
                ofile<<endl;
            }
        }

        if(!start && !starttext){
                for(int i = 0; i < current.size() && current[i] != '#' ; i++)
                {
                    ofile<<current[i];
                }
                ofile<<endl;
        }
       
    }

    ofile.close();
    ifile.close();
    
}
