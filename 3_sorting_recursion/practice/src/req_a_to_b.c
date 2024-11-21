#include <stdio.h>

void print_a_to_b(int a, int b) {
    if (a == b) {

        printf("%d ", a);

        return;
    }

    if (a > b)
    {
        print_a_to_b(a - 1, b);

        printf("%d ", a);
    } else {

        print_a_to_b(a + 1, b);

        printf("%d ", a);
    }
}

int main() {
    print_a_to_b(10, 2);
    printf("\n");
    print_a_to_b(2, 8);
    printf("\n");
}
