#include <stdio.h>

void print_octal(int value) {

    if(value > 1073741823) {
        return;
    }

    printf("octal = 0oct");

    int buffer[10];
    int buffer_index = 0;

    while (value != 0) {
        buffer[buffer_index] = value % 8;
        buffer_index++;

        value = value / 8;
    }

    for (int i = buffer_index - 1; i >= 0; i--) {
        printf("%d", buffer[i]);
    }

    printf("\n");
}

int main() {
    int value = 7;

    printf("decimal = %d\n", value);
    print_octal(value);

    value = 8;

    printf("decimal = %d\n", value);
    print_octal(value);

    value = 9;

    printf("decimal = %d\n", value);
    print_octal(value);

    value = 64 * 3 + 8 * 5 + 4;

    printf("decimal = %d\n", value);
    print_octal(value);


    return 0;
}

