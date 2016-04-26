//http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
#include<bitset>
#include<iostream>
#include<stdint.h>
#include<vector>
#include"des_constants.h"

using namespace std;

uint64_t initialPermutationOfKey(int *pc1,uint64_t key){

    uint64_t newKey = 0x0;
    for(int i = 0; i<56;i++){
        //Permutate
        newKey |= key>>(64-pc1[i])&1;
        newKey = newKey<<1;
    }
    //Modular bit
    newKey = (newKey>>1)&((1l<<56)-1);


    return newKey;
}

vector< bitset<56> > generateKeys(bitset<56> key){
    int numberOfLeftShift[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

    vector< bitset<56> > arrayKeys;
    for(int i=0;i<16;i++){
        for(int j=0; j<numberOfLeftShift[i];j++){
            int leftBit = key[key.size()-1],rightBit = key[key.size()/2-1];
            key = key <<1;
            key[(key.size()/2)] = leftBit;
            key[0] = rightBit;
        }
        arrayKeys.push_back(key);
    }
    return arrayKeys;
}

int des(){
    uint64_t blockCipher = 0x0123456789ABCDEF;
    uint64_t key =  0x133457799BBCDFF1;

    int64_t newKey = initialPermutationOfKey(pc1,key);

    bitset<64> blockBitArray (blockCipher);
    bitset<56> newKeyBitArray (newKey);

    cout <<"Bloco "<< blockBitArray.to_string() << endl;
    cout <<"Chave permutada "<<newKeyBitArray.to_string() << endl;

    vector< bitset<56> > arrayKeys = generateKeys(newKey);

    for(int i =0;i<arrayKeys.size();i++){
        cout <<"Array key "<< arrayKeys[i] <<endl;
    }
    return 0;
}

int main(){
    des();
    return 0;
}

