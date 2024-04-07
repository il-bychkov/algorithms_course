#include "substr.h"

void print_part(char* str, size_t start, size_t len) {
    for (size_t i = start; i < start + len; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int main() {

    char str[] = "aaaaa sssssssubstring string sub aaaaaa";
    char substr[] = "substring";

    size_t index_naive = substr_naive(str, sizeof(str)/sizeof(str[0]), substr, sizeof(substr)/sizeof(substr[0]));
    size_t index_rabin_karp = substr_rabin_karp(str, sizeof(str)/sizeof(str[0]), substr, sizeof(substr)/sizeof(substr[0]));
    size_t index_kmp = substr_kmp(str, sizeof(str)/sizeof(str[0]), substr, sizeof(substr)/sizeof(substr[0]));

    printf("naive:\n");
    print_part(str, index_naive, sizeof(substr)/sizeof(substr[0]));
    printf("Rabin-Karp:\n");
    print_part(str, index_rabin_karp, sizeof(substr)/sizeof(substr[0]));
    printf("Knuth-Morris-Pratt:\n");
    print_part(str, index_kmp, sizeof(substr)/sizeof(substr[0]));

    return 0;
}
