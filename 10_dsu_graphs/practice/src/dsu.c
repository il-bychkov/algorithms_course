#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// implementation based on
// https://habr.com/ru/articles/104772/

typedef struct dsu {
    uint8_t* parent;
    uint8_t* rank;
    size_t max_val;
} dsu_t;

void init_dsu(dsu_t* dsu) {
    dsu->max_val = 8;

    dsu->parent = malloc(sizeof(uint8_t) * dsu->max_val);
    dsu->rank = malloc(sizeof(uint8_t) * dsu->max_val);

    for (size_t i = 0; i < dsu->max_val; i++) {
        dsu->parent[i] = 0;
        dsu->rank[i] = 0;
    }
}

int make_set(dsu_t* dsu, uint8_t value) {

    // resize and copy buffers if nedeed
    if (value >= dsu->max_val) {
        size_t old_max_val = dsu->max_val;
        dsu->max_val = value;

        uint8_t* new_parent = malloc(sizeof(uint8_t) * dsu->max_val);
        uint8_t* new_size = malloc(sizeof(uint8_t) * dsu->max_val);

        memcpy(new_parent, dsu->parent, old_max_val);
        memcpy(new_size, dsu->rank, old_max_val);

        free(dsu->parent);
        free(dsu->rank);

        dsu->parent = new_parent;
        dsu->rank = new_size;
    }

    uint8_t* parent = dsu->parent;

    if(parent[value] != 0) {
        return 1;
    }

    parent[value] = value;
    dsu->rank[value] = 1;

    return 0;
}

int find_set(uint8_t* result, dsu_t* dsu, uint8_t value) {

    uint8_t* parent = dsu->parent;

    if (parent[value] == 0) {
        return 1;
    };

	if (value == parent[value]) {
        *result = value;
        return 0;
    }

    int ret_val = find_set(result, dsu, parent[value]);

    parent[value] = *result;

	return ret_val;
}

int union_sets(dsu_t* dsu, uint8_t value_a, uint8_t value_b) {

    uint8_t parent_a;
    uint8_t parent_b;

    int ret = 0;

	ret += find_set(&parent_a, dsu, value_a);
	ret += find_set(&parent_b, dsu, value_b);

    if(ret != 0) {
        return ret;
    }

    uint8_t* parent = dsu->parent;
    uint8_t* rank = dsu->rank;

	if (parent_a != parent_b) {
		if (rank[parent_a] < rank[parent_b]) {
            uint8_t tmp = parent_a;
            parent_a = parent_b;
            parent_b = tmp;
        }
		parent[parent_b] = parent_a;
		if (rank[parent_a] == rank[parent_b]) {
            ++rank[parent_a];
        }

        return 0;
	} else {
        return 3;
    }
}

void main() {
    dsu_t dsu;
    dsu_t* p_dsu = &dsu;

    init_dsu(p_dsu);

    printf("Make sets 1 2 3 4\n");

    make_set(p_dsu, 1);
    make_set(p_dsu, 2);
    make_set(p_dsu, 3);
    make_set(p_dsu, 4);

    uint8_t result;

    find_set(&result, p_dsu, 1);

    printf("Find set 1, result %d\n", result);

    find_set(&result, p_dsu, 2);

    printf("Find set 2, result %d\n", result);

    printf("Union sets 1 and 2\n");

    union_sets(p_dsu, 1, 2);

    find_set(&result, p_dsu, 1);

    printf("Find set 1, result %d\n", result);

    find_set(&result, p_dsu, 2);

    printf("Find set 2, result %d\n", result);
}
