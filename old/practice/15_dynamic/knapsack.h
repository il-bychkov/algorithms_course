#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct item {
    uint32_t w; // weight
    uint32_t v; // value
} item_t;

#define max(a,b) (((a) > (b)) ? (a) : (b))

#endif // KNAPSACK_H
