#include <stdio.h>

int req_rotate_digits(int num, int rotated) {
    if(num == 0) {
        return rotated;
    }

    return (req_rotate_digits(num / 10, rotated * 10 + num % 10));
}

int main() {

    printf("%d\n", req_rotate_digits(123, 0));
}
