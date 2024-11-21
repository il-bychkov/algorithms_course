#include <stdio.h>

int req_sim_digits(int num) {
    if(num == 0) {
        return 0;
    }

    return num % 10 + (req_sim_digits(num / 10));
}

int main() {

    printf("%d\n", req_sim_digits(123));
}
