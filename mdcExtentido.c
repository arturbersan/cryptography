#include <stdio.h>

// C function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    printf("mdc = %d\n", b%a);
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

// Driver Program
int main()
{
    int x, y;
    int a , b;
    while(scanf("%d%d",&a,&b)!=EOF){
        int g = gcdExtended(a, b, &x, &y);
        printf("mdc(%d, %d) = %d, x = %d, y = %d\n", a, b, g, x, y);
    }
    return 0;
}
