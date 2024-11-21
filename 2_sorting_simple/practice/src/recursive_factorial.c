#include <stdio.h>

int fact(int n) {

    // BASE CONDITION
    if (n == 0 || n == 1)
        return 1;

    return n * fact(n - 1);
}

int main() {
    printf("Factorial of 5 : %d\n", fact(5));
    return 0;
}
