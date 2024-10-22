#include <stdio.h>
int main()
{
    unsigned int a = 9; // 0b1001
    unsigned int b = 0b111;
  
    printf("Bitwise AND result = %d\n", a & b);
    printf("Bitwise OR  result = %d\n", a | b);
    printf("Bitwise XOR result = %d\n", a ^ b);
    printf("Bitwise NOT result = %d\n", ~ a);  

    return 0;    
}
