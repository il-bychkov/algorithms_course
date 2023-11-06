#include <stdio.h>
int main()
{
	// Create 4 variables of different types
    int intVariable = 30;
    float floatVariable = 1.1;
    double doubleVariable = 1.1;
    char charVariable = 'c';
    
    printf("int start address = %p\n",&intVariable);
    printf("int size          = %lu\n",sizeof(int));
	// Int variable - address + 1 = address + one int
    printf("int end address   = %p\n\n",&intVariable + 1);

    printf("float start address = %p\n",&floatVariable);
    printf("float size          = %lu\n",sizeof(floatVariable));
	// Float variable - address + 1 = address + one float
    printf("float end   address = %p\n\n",&floatVariable + 1);

    printf("double start address = %p\n",&doubleVariable);
    printf("double size          = %lu\n",sizeof(doubleVariable));
	// Double variable - address + 1 = address + one double
    printf("double end address   = %p\n\n",&doubleVariable + 1);

    printf("char start address = %p\n",&charVariable);
    printf("char size          = %lu\n",sizeof(charVariable));
	// Char variable - address + 1 = address + one char
    printf("char end   address = %p\n\n",&charVariable + 1);
}
