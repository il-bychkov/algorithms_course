#include <stdio.h>

#define ARR_SIZE 1000
#define EXTREMUM_INDEX ARR_SIZE - ARR_SIZE / 3 + 14
#define VALUE_OFFSET 42


int binary_search_for_unimodal_func(int* a, int n) {
	int l = 0, r = n - 1;

	while (l <= r) {
		int c = (l + r) / 2;

        //checking borders
        if (c + 1 > n - 1 || c - 1 < 0) {
            return c;
        }
        
		if (a[c] < a[c + 1]) {
			l = c + 1;
		}
		else if (a[c] > a[c - 1] && a[c] > a[c + 1]) {
			return c;
		}
		else {
			r = c - 1;
		}

	}
	return -1;
}

int main() {
    int arr[ARR_SIZE];

    for (size_t i = 0; i <= EXTREMUM_INDEX; i++)
    {
        arr[i] = i + VALUE_OFFSET;
    }

    for (size_t i = EXTREMUM_INDEX + 1; i < ARR_SIZE; i++)
    {
        arr[i] = ARR_SIZE - i + VALUE_OFFSET;
    }

    printf("function extremum is: \n\n");
    printf("index: ... %d %d %d %d %d ...\n", EXTREMUM_INDEX - 2, EXTREMUM_INDEX - 1, EXTREMUM_INDEX, EXTREMUM_INDEX + 1, EXTREMUM_INDEX + 2);
    printf("value: ... %d %d %d %d %d ...\n", arr[EXTREMUM_INDEX - 2], arr[EXTREMUM_INDEX - 1], arr[EXTREMUM_INDEX], arr[EXTREMUM_INDEX + 1], arr[EXTREMUM_INDEX + 2]);

    int index = binary_search_for_unimodal_func(arr, ARR_SIZE);

    printf("\n");
    printf("Found extremum at index %d\n", index);
}
