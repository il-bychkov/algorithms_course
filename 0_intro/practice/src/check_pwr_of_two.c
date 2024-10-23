#include <stdio.h>

int check_is_pwr_of_two_naive(int val) {
    int n_bits = sizeof(int) * 8;
    int n_one_bits = 0;

    for (int i = 0; i < n_bits; i++) {
        n_one_bits += (val >> i) & 0x1;
    }

    if (n_one_bits == 1) {
        return 1;
    }

    return 0;
}

int check_is_pwr_of_two_substraction(int val) {

    if (val == 0) {
        return 0;
    }

    if ((val & (val - 1)) == 0) {
        return 1;
    }

    return 0;
}

int main() {
    int pwr = 128;
    int not_pwr = 345;

    printf("check by naive method\n");
    printf("value %d - check result %d\n", pwr, check_is_pwr_of_two_naive(pwr));
    printf("value %d - check result %d\n", not_pwr, check_is_pwr_of_two_naive(not_pwr));

    printf("check by substruction method\n");
    printf("value %d - check result %d\n", pwr, check_is_pwr_of_two_substraction(pwr));
    printf("value %d - check result %d\n", not_pwr, check_is_pwr_of_two_substraction(not_pwr));

    return 0;
}
