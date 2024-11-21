#include <stdio.h>

void print_1_to_n(int n) {
    if (n == 0) {
        return;
    }

    print_1_to_n(n - 1);

    printf("%d ", n);
}

int main() {
    print_1_to_n(10);
    printf("\n");
}
