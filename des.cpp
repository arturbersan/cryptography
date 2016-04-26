#include<stdio.h>
//http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
#include<stdlib.h>
#include<string.h>
#include<inttypes.h>


void divideSliceBlock(uint64_t blockCipher,uint32_t &left_slice, uint32_t &right_slice){

    uint32_t *p = (uint32_t*) &blockCipher;

    const int SLICE_SIZE = sizeof(uint32_t);
    const int POINTER_STEP = SLICE_SIZE / sizeof(uint32_t);

    memcpy(&right_slice, p, SLICE_SIZE);
    memcpy(&left_slice, (p + POINTER_STEP), SLICE_SIZE);

}
uint64_t initialPermutationOfKey(int *pc1,uint64_t key){

    uint64_t newKey = 0x0;
    for(int i = 0; i<56;i++){
        newKey |= (key&(1l<<(64-pc1[i])))>>(64-pc1[i]);
        printf("%d ,", 64-pc1[i]);
        newKey = newKey<<1;
    }

    newKey = (newKey>>1)&((1l<<56)-1);
    printf("\n%"PRIx64"\n", newKey);


    return newKey;
}

int main(){
    uint64_t blockCipher = 0x0123456789ABCDEF;
    uint32_t left_slice, right_slice;
    uint64_t key =  0x133457799BBCDFF1;

    int pc1[56] = {57,   49,    41,   33,    25,    17,    9,
                   1,   58,    50,   42,    34,    26,   18,
                   10,    2,    59,   51,    43,    35,   27,
                   19,   11,     3,   60,    52,   44,  36,
                   63,   55,    47,   39,    31,    23,   15,
                    7,   62,    54,   46,    38,    30,   22,
                   14,    6,    61,   53,    45,    37,   29,
                   21,   13,     5,   28,    20,    12,   4};
    divideSliceBlock(blockCipher,left_slice,right_slice);
    initialPermutationOfKey(pc1,key);

    printf("%x %x\n", left_slice,right_slice);

return 0;
}


