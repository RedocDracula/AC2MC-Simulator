#include <iostream>
#include <set>
#include <bitset>
#include <vector>
#include "MemoryAccess.h"
#include "InterStateBuffers.h"
#define NUMBER_SETS 64 
#define SET_SIZE 2
// Address is 16 BIT .
using namespace std;

class Block{
    private:
    int tag;
    int hits;
    vector <int> data;
    bool writeback;
    friend class Cache;
    public:
    Block(){
        tag = 0;
        data.resize(20); // 20 words in a block
        writeback = 0;
        hits = 0;
    }
};

class Cache{ // Cache has 128 Blocks, each Block has 16 words, each word is 32 bit.
    private: 
    vector < vector<Block> > CacheMemory;
    bitset <6> tag;
    bitset <6> set;
    bitset <4> word;
    int CacheSize = 0;

    public:
    Cache(){
        CacheMemory.resize(NUMBER_SETS);
    }

    bool isfull(int setindex){
       return  CacheMemory[setindex].size() == SET_SIZE; //2 - way set associate Cache.
    }

    int LeastUsed(int SetIndex){
        int LeastHitBlock;
        int mini = INT_FAST16_MAX;
        for(int i = 0 ; i < CacheMemory[SetIndex].size() ; i++){
            if(CacheMemory[SetIndex][i].hits < mini){
                LeastHitBlock = i;
                mini = CacheMemory[SetIndex][i].hits;
            }
        }

        return LeastHitBlock;
    }

    void ReadCache(bitset <16> address, MemoryAccess &memobject, InterStateBuffers & isb){ // read Word in Cache
        int k;
        bool found = 0;
        for(int i = 0 ; i <= 3 ; i++)
            word[i] = address[i];
        k = 0;
        for(int i = 4 ; i <= 9; i++)
            set[k++] = address[i] ;
        k = 0;
        for(int i =  10 ; i <= 15 ; i++ )
            tag[k++] = address[i];
        
        // tag , set number and word number(block offset ) has been found.
        int setindex = set.to_ulong();

        if(setindex >= NUMBER_SETS || setindex < 0)
        {
            cout<<"Setindex is going out of bound !  , SEGFAULT "<<endl;
        }
        // Check for hit in Cache
        for(int i = 0; i < CacheMemory[setindex].size() ; i++){
            if(CacheMemory[setindex][i].tag == tag.to_ulong()){ // A HIT in the Cache.
                found = true;
                CacheMemory[setindex][i].hits++;
                int wordindex = word.to_ulong();
                isb.mem_register = CacheMemory[setindex][i].data[wordindex];
                return;
            }
        }

        if(!found){ // MISS in the cache
            if(isfull(setindex)){
                int ToRemove = LeastUsed(setindex); // implement LRU here
                if(CacheMemory[setindex][ToRemove].writeback == 1){ // if we need to Write Back to Memory. (sorta like Lazy Update)
                    memobject.writeBlock(CacheMemory[setindex][ToRemove]);
                }

                CacheMemory[setindex].erase(CacheMemory[setindex].begin(), CacheMemory[setindex].begin() + ToRemove); // remove the least used block in the set
            }
            int Value = memobject.readByte(address.to_ulong()); // read from memory and write to Cache
            
            Block Read = memobject.readBlock(address.to_ulong());
            CacheMemory[setindex].push_back(Read);
            
            isb.mem_register =  Value;
            return;
        }
    }

    void WriteCache(){

    }


};