// A C program to demonstrate working of recursion
#include <stdio.h>

void printFun(int test)
{
    if (test < 1)
        return;
    else {
        printf("%d ", test);
        printFun(test - 1);
        printf("%d ", test);
        return;
    }
}

// Driver Code
int main()
{
    int test = 3;
    printFun(test);
    return 0;
}
