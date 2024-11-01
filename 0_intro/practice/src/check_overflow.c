#include <stdio.h>
#include <limits.h>

int check_overflow(int a, int b) {
    return (b > INT_MAX - a) || (a > INT_MAX - b);
}

int main() {
    int a = 30;
    int b = 35;


    printf("a = %d \n", a);
    printf("b = %d \n", b);

    printf("will addition overflow - %d\n", check_overflow(a, b));

    printf("a + b = %d \n", a + b);
    printf("\n");

    a = INT_MAX - 30;
    b = 35;


    printf("a = %d \n", a);
    printf("b = %d \n", b);

    printf("will addition overflow - %d\n", check_overflow(a, b));

    printf("a + b = %d \n", a + b);

    return 0;
}
