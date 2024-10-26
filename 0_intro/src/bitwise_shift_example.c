#include <stdio.h>

int main()
{
    int a = 3;
    int b = -3;

    printf("Unsigned left shifts\n");
    printf("%d << %d = %d \n", a, 1, a << 1);
    printf("%d << %d = %d \n", a, 2, a << 2);
    
    printf("Signed left shifts\n");
    printf("%d << %d = %d \n", b, 1, b << 1);
    printf("%d << %d = %d \n", b, 2, b << 2);
       
    printf("Unsigned right shifts\n");
    printf("%d >> %d = %d \n", a, 1, a >> 1);
    printf("%d >> %d = %d \n", a, 2, a >> 2);

    printf("Signed right shifts\n");
    printf("%d >> %d = %d \n", b, 1, b >> 1);
    printf("%d >> %d = %d \n", b, 2, b >> 2);

    return 0;    
}
