#include "substr.h"

size_t substr_rabin_karp(char* str, size_t str_len, char* substr, size_t substr_len) {

    if (substr_len > str_len || !str || !substr) {
        return str_len+1;
    }

    size_t hash_substr = 0;

    for (size_t i = 0; i < substr_len - 1; i++) {
        hash_substr += (size_t)substr[i];
    }

    for (size_t i = 0; i < str_len - substr_len; i++) {

        size_t hash_str = 0;

        for (size_t j = 0; j < substr_len - 1; j++) {
            hash_str += (size_t)str[j + i];
        }

        if (hash_substr == hash_str) {
            bool is_match = true;

            for (size_t j = 0; j < substr_len - 1; j++) {
                is_match = str[j + i] == substr[j];
            }

            if (is_match) {
                return i;
            }

        }

    }

    return str_len+1;
}
