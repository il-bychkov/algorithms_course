#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

#define MAX_DIM 100

void lcm(char* a, size_t n, char* b, size_t m) {

    size_t max_len[MAX_DIM][MAX_DIM];

    for (size_t i = 1; i < n + 1; i++) {
        for (size_t j = 1; j < m + 1; j++) {
            if (a[i - 1] == b[j - 1]) {
                max_len[i][j] = max_len[i - 1][j - 1] + 1;
            } else {
                max_len[i][j] = max(max_len[i - 1][j], max_len[i][j - 1]);
            }

        }

    }

    printf("%4c ", ' ');
    printf("%4c ", ' ');

    for (size_t i = 0; i < n; i++)
    {
        printf("%4c ", a[i]);
    }

    printf("\n");

    for (size_t i = 0; i < m; i++) {
        if(i >= 1) {
            printf("%4c ", b[i - 1]);
        } else {
            printf("%4c ", ' ');
        }
        for (size_t j = 0; j < n; j++) {
            printf("%4ld ", max_len[j][i]);
        }

        printf("\n");
    }

    int i = n;
    int j = m;

    char result[MAX_DIM];
    size_t result_index = 0;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            result[result_index] = a[i - 1];
            result_index++;
            i--;
            j--;
        } else if(max_len[i - 1][j] == max_len[i][j]) {
            i--;
        } else {
            j--;
        }
    }

    printf("\n");

    for (size_t i = result_index - 1; i > 0; i--)
    {
        printf("%c", result[i]);
    }


    printf("\n");

}

int main() {

    char a[] = "HABRAHABR";
    char b[] = "HARBOUR";

    lcm(a, sizeof(a) / sizeof(char), b, sizeof(b) / sizeof(char));

    return 0;
}


