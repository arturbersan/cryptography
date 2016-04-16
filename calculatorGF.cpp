#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int additive(int x, int y){

    int result =  x^y;

    return result;
}

int multiplicativeByX(int x){

    int result = x<<1;
    result &= 255;
    //Operator "and" with integer 128 to verify the bit 7
    if(x&128){
        //27 is the polinomy x4 + x3 + x + 1 in binary
        result ^= 27;
    }
    return result;
}

int multiplicative(int x, int y){

    int result = 0;
    int i,resultVetor[8];

    //Atribute polinome y to init operate
    resultVetor[0]= y;
    for(i=1;i<8; i++){
        resultVetor[i] = multiplicativeByX(resultVetor[i-1]);
    }
    //Operate distributive of binary
    for(i=0;i<8;i++){
        //Verify if the bit is active
        if(x&(1<<i)){
            result = additive(resultVetor[i],result);
        }
    }

    return result;
}

int inverseMultiplicative(int x){
    int result = x;
    for (int i=1;i<7;i++){
        result = multiplicative(multiplicative(result,result),x);
    }
    result = multiplicative(result,result);
    printf("inverse = {%d}\n", result);

    return result;
}
int divisor(int x,int y){
    int inverseMultiplicativeY = inverseMultiplicative(y);
    int result = multiplicative(inverseMultiplicativeY,x);

    printf("Divisor = {%d}\n", result);
    return result;
}



int main(){
    int x,y,resultSom,resultMulitplic,resultDivide;
    scanf("%d%d", &x,&y);
    resultSom = additive(x,y);
    resultMulitplic = multiplicative(x,y);
    resultDivide = divisor(x,y);

    printf("Soma = {%d}\nMultiplica = {%d}\nDivide = {%d}\n", resultSom,resultMulitplic,resultDivide);

    return 0;
}

