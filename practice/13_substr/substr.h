#ifndef SUBSTR_H
#define SUBSTR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

size_t substr_naive(char* str, size_t str_len, char* substr, size_t substr_len);
size_t substr_rabin_karp(char* str, size_t str_len, char* substr, size_t substr_len);
size_t substr_kmp(char* str, size_t str_len, char* substr, size_t substr_len);

#endif // SUBSTR_H
