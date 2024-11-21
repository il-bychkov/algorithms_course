#include <stdio.h>

int req_check_pwr_2(float n) {
    if (n == 1) {

        return 1;
    }

    if (n > 1 && n < 2) {
        return 0;
    }

    return req_check_pwr_2(n / 2);
}

int main() {
    printf("is %f a power of 2 = %d\n", 31.0, req_check_pwr_2(31));
    printf("is %f a power of 2 = %d\n", 32.0, req_check_pwr_2(32));
}
