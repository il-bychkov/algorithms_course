#include "knapsack.h"

// based on https://algocode.ru/page/c-8-knapsack/

void knapsack_unbounded(item_t* items, size_t n, size_t W) {

    size_t* m = malloc(sizeof(size_t) * (n + 1) * (W + 1));

    for (size_t j = 0; j < W + 1; j++) {
        m[j] = 0;

        if (items[0].w <= j ) {
            m[j] = max(m[j], m[j - items[0].w] + items[0].v);
        }
    }

    for (size_t i = 1; i < n + 1; i++) {
        for (size_t j = 0; j < W + 1; j++) {
            m[i * W + j] = m[(i - 1) * W + j];

            if (items[i].w <= j ) {
                m[i * W + j] = max(m[i * W + j], m[i * W + j - items[i].w] + items[i].v);
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < W; j++) {
            printf("%4ld ", m[i * W + j]);
        }
        printf("\n");
    }

    free(m);

}

int main() {

    item_t items[] = {
        {2, 2},
        {2, 3},
        {4, 10},
        {4, 5},
    };

    knapsack_unbounded(items, sizeof(items) / sizeof(item_t), 12);

    return 0;
}
