#include <stdio.h>

int main() 
{

    int a = 42;
    int b = 800;

    printf("initial state\n");
    printf("a = %d, b = %d\n", a, b);

    // works ONLY with integers and chars
	// POTENTIAL PROBLEM: OVERFLOW
    a = a + b;
    b = a - b;
    a = a - b;

    printf("after add-sub-sub swap\n");
    printf("a = %d, b = %d\n", a, b);

    // works ONLY with integers and chars
    // least efficient
	// POTENTIAL PROBLEM: OVERFLOW
    a = a * b;
    b = a / b;
    a = a / b;

    printf("after mul-div-div swap\n");
    printf("a = %d, b = %d\n", a, b);

    // works ONLY with integers and chars
	// POTENTIAL PROBLEM: OVERFLOW
    a = a - b;
    b = a + b;
    a = -a + b;

    printf("after sub-add-add swap\n");
    printf("a = %d, b = %d\n", a, b);

    // works with ANY data types
    // most efficient
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;

    printf("after tripple xor swap\n");
    printf("a = %d, b = %d\n", a, b);

    return 0;
}
