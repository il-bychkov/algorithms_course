#include <stdio.h>

// - пример хранения float и double
// double - аналогично

// taken from https://stackoverflow.com/questions/15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number
typedef union {
    float f;
    struct {
        unsigned int mantisa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
} float_cast;

int main() {

    int intVariable = 16;
    float floatVariable = 16;

    printf("int value       = %d\n", intVariable);
    printf("int hex value   = %x\n", intVariable);
    printf("int size        = %lu\n", sizeof(int));

    printf("\n");

    printf("float value     = %f\n", floatVariable);
    printf("float hex value = %x\n", floatVariable);
    printf("float size      = %lu\n", sizeof(float));

    float_cast float_bits = { .f = floatVariable };

    printf("float sign               = %x\n", float_bits.parts.sign );
    printf("float exponent hex value = %x\n", float_bits.parts.exponent );
    printf("float mantisa hex value  = %x\n", float_bits.parts.mantisa );


    // inspiration taken from https://www.h-schmidt.net/FloatConverter/IEEE754.html
    // NOTE: works correctly only with powers of two
    // other values will require mantisa processing, that is not implemented here
    printf("float exponent actual value = %d\n", float_bits.parts.exponent - 127);
    printf("reconstructed integer value = %d\n", 1 << (float_bits.parts.exponent - 127));

    return 0;
}
