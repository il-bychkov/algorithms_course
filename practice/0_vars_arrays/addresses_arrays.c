#include <stdio.h>
int main()
{
    const int arrLen = 10;
    int intArray[arrLen] = {10, 11, 12, 13 ,14 ,15 ,16 ,17, 18, 19};

    
    for (int i = 0; i < arrLen; i++)
        printf("int array element shift = [%d] -  value stored = %d  - address = %p\n",i, intArray[i], &intArray[i]);
    return 0;
}
