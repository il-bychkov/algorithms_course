#include "substr.h"

size_t substr_kmp(char* str, size_t str_len, char* substr, size_t substr_len) {

    size_t* pi = malloc(substr_len * sizeof(size_t));
    pi[0] = 0;

    size_t l;

    for (l = 1; l < substr_len - 1; l++) {
        size_t j = pi[l-1];
        while ((j > 0) && (substr[l] != substr[j])) {
            j = pi[j-1];
        }

        if (substr[l] == substr[j]) {
            ++j;
        }

        pi[l] = j;
    }

    size_t j = 0;

    for (size_t i = 0; i < str_len; i++) {
        while ((j > 0) && (str[i] != substr[j])) {
            j = pi[j-1];
        }

        if (str[i] == substr[j]) {
            j++;
        }

        if (j==l) {
            free(pi);
            return i - l + 1;
        }
    }
}
