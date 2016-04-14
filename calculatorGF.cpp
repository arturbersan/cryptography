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
    for(i=0;i<8;i++) printf("%d ",resultVetor[i]);
    //Operate distributive of binary
    for(i=0;i<8;i++){
        if(x&(1<<i)){
            result = additive(resultVetor[i],result);
            printf("aqui!%d\n",i);
        }
    }

    return result;
}

int main(){
    int x,y,resultadoSoma,resultadoMulitplica;
    scanf("%d%d", &x,&y);
    resultadoSoma = additive(x,y);
    resultadoMulitplica = multiplicative(x,y);

    printf("Soma = {%d}\nMultiplica = {%d}\n", resultadoSoma,resultadoMulitplica);

}

