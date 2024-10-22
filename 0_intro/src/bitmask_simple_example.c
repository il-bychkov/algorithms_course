#include <stdio.h>
int main()
{
    const unsigned int MASK1 = 0x0000000F;
    const unsigned int MASK2 = 0x000000FF;
    const unsigned int MASK3 = 0x000F0000;

    unsigned int a = 0x0ACE; 
    
    printf("%d & %d = %d\n", a, MASK1, a & MASK1);
    printf("%d & %d = %d\n", a, MASK2, a & MASK2);
    printf("%d & %d = %d\n", a, MASK3, a & MASK3);
    
    return 0;    
}

