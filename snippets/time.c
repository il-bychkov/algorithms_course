#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void measure_time_of_operation() {
    clock_t t;
    t = clock(); // hi-res clock counter
    printf("MEASURE MY TIME!\n");
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("executed in %f seconds \n", time_taken);
}

int main() {

    measure_time_of_operation();

    return 0;
}