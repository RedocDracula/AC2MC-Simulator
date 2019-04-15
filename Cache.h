#include <iostream>
#include <set>
#include <bitset>
#include <vector>
#include "MemoryAccess.h"
#define CACHESIZE 256

using namespace std;

class Entry{
    private:
    int tag;
    int hits;
    vector <int> data;
    bool writeback;
    friend class Cache;
    public:
    Entry(){
        tag = 0;
        data.resize(20); // 20 words in a block
        writeback = 0;
        hits = 0;
    }
};

class Cache{
    private: // 8 MB Cache 
    vector < vector<Entry> > CacheMemory;
    bitset <8> tag;
    bitset <4> set;
    bitset <20> word;
    int CacheSize = 0;
    public:
    Cache(){
        CacheMemory.resize(CACHESIZE);
    }

    bool isfull(int setindex){
       return  CacheMemory[setindex].size() == 4;
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

    int ReadCache(bitset <32> address, MemoryAccess &memobject){
        int k;
        bool found = 0;
        for(int i = 0 ; i <= 19 ; i++)
            word[i] = address[i];
        k = 0;
        for(int i = 20 ; i <= 23; i++)
            set[k++] = address[i] ;
        k = 0;
        for(int i =  24 ; i <= 31 ; i++ )
            tag[k++] = address[i];
        
        // tag , set number and word number(block offset ) has been found.
        int setindex = set.to_ulong();

        if(setindex >= CACHESIZE || setindex < 0)
        {
            cout<<"Setindex is going out of bound !  , SEGFAULT "<<endl;
        }

        for(int i = 0; i < CacheMemory[setindex].size() ; i++){
            if(CacheMemory[setindex][i].tag == tag.to_ulong()){ // A HIT in the Cache.
                found = true;
                CacheMemory[setindex][i].hits++;
                int wordindex = word.to_ulong();
                return CacheMemory[setindex][i].data[wordindex];
            }
        }

        if(!found){ // MISS in the cache
            if(isfull(setindex)){
                int ToRemove = LeastUsed(setindex);
                if(CacheMemory[setindex][ToRemove].writeback == 1){ // if we need to Write Back to Memory. (sorta like Lazy Update)
                    memobject.writeBlock(CacheMemory[setindex][ToRemove]);
                }

                CacheMemory[setindex].erase(CacheMemory[setindex].begin(), CacheMemory[setindex].begin() + ToRemove); // remove the least used block in the set
            }
            int Value = memobject.readMem(address.to_ulong()); // read from memory and write to Cache
            Entry entry;
            entry.data[word.to_ulong()] = Value;
            entry.tag = tag.to_ulong();
            CacheMemory[setindex].push_back(entry); // write to cache.
            return Value;
        }

        
    }
};