#include<stdio.h>
#include<math.h>

int main() {
	int x = 0b11001; //25
	int n = 2; //bit, starts from 1
	int mask = pow(2, n - 1);

	printf("Add n bit: %d\n", mask | x);
	printf("Remove n bit: %d\n", ~mask & x);
	printf("Inversion n bit: %d\n", mask ^ x);
	printf("Check n bit: %s\n", mask & x ? "yes" : "no");
	return 0;
}

