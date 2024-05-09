#include "substr.h"

size_t substr_naive(char* str, size_t str_len, char* substr, size_t substr_len) {

    if (substr_len > str_len || !str || !substr) {
        return str_len+1;
    }


    for (size_t i = 0; i < str_len - substr_len; i++) {

        size_t substr_index = 0;

        while (str[i + substr_index] == substr[substr_index]) {
            substr_index++;
        }

        if(substr_index + 1 == substr_len) {
            return i;
        }
    }

    return str_len+1;
}
