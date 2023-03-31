#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

// Ten plik zawiera przykład użycia funkcji:
int inverse_permutation(size_t n, int *p);

int main () {
	int arr[] = {0, 1, 2, 3, 4};
	int arr2[] = {1, -2, 3, -4};
	int arr3[] = {1, 2, 3, 1};
    int arr4[] = {0, 0, 1, 2};
    int arr5[] = {3, 1, 5, 0, 2, 4};

	assert(inverse_permutation(5, arr) == 1);
	assert(inverse_permutation(4, arr2) == 0);
    assert(inverse_permutation(4, arr3) == 0);
    assert(inverse_permutation(4, arr4) == 0);
    assert(inverse_permutation(6, arr5) == 1);
	return 0;
}
